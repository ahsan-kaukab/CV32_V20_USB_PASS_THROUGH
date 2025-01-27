/********************************** (C) COPYRIGHT  *******************************
 * File Name          : app_km.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/09/01
 * Description        : The USB host operates the keyboard and mouse.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
*******************************************************************************/


/********************************************************************************/
/* Header File */
//#include "kite.h"
#include "usb_host_config.h"
#include "usbd_composite_km.h"
#include "usb_desc.h"
#include <math.h>
#include "ch32v20x_usb.h"
//#include <stdlib.h> // For malloc and free

#define ABS(x) ((x) < 0 ? -(x) : (x))

uint8_t new_descripter = 2;
uint8_t kb_ms;
uint8_t report_byte = 0;
/*******************************************************************************/
/* Variable Definition */
static uint8_t  DevDesc_Buf[ 18 ];                                                     // Device Descriptor Buffer
static uint8_t  Com_Buf[ DEF_COM_BUF_LEN ];                                            // General Buffer
uint8_t  KB_Data_Pack[ 8 ] = { 0x00 };                                          // Primary HID buffer
uint8_t  KB_Data_Buffer[ 8 ] = { 0x00 };                                        // Secondary HID buffer
//uint8_t  MS_Data_Pack[ 4 ] = { 0x00 };                                          // Primary HID buffer
//uint8_t  MS_Data_Buffer[ 4 ] = { 0x00 };                                        // Secondary HID buffer

uint8_t  KB_Data_Pack_Full = 0;                                                 // Primary HID buffer state
uint8_t  KB_Data_Buffer_Full = 0;                                               // Secondary HID buffer state
uint8_t  KB_Data_State = 0;                                                     // Current HID buffer

uint8_t  scroll_lock_led = 0;                                                   // Scroll lock LED state

struct   _ROOT_HUB_DEVICE RootHubDev;
struct   __HOST_CTL HostCtl[ DEF_TOTAL_ROOT_HUB * DEF_ONE_USB_SUP_DEV_TOTAL ];
volatile uint32_t millis_counter = 0;

// extern uint8_t USBD_DeviceDescriptor[18];
//extern uint8_t  USBD_ConfigDescriptor_KB[40];
//extern uint8_t  USBD_ConfigDescriptor_MS[];

// extern uint8_t USBD_MouseRepDesc[USBD_SIZE_REPORT_DESC_MS];

// extern uint8_t USBD_StringLangID[USBD_SIZE_STRING_LANGID];
// /* USB Device String Vendor */
// extern uint8_t USBD_StringVendor[USBD_SIZE_STRING_VENDOR]; 
// /* USB Device String Product */
// extern uint8_t USBD_StringProduct[USBD_SIZE_STRING_PRODUCT];
// /* USB Device String Serial */
// extern uint8_t USBD_StringSerial[USBD_SIZE_STRING_SERIAL];

ONE_DESCRIPTOR Report_Descriptor;  //[2] =
// {
// 	{(uint8_t*)USBD_KeyRepDesc, USBD_SIZE_REPORT_DESC_KB},
// 	{(uint8_t*)USBD_MouseRepDesc, sizeof(USBD_MouseRepDesc)},
// };

// ONE_DESCRIPTOR Hid_Descriptor[2] = 
// { 
//   {(uint8_t*)&USBD_ConfigDescriptor_KB[18], 0x09},
//   {(uint8_t*)&USBD_ConfigDescriptor_MS[43], 0x09},
// };

ONE_DESCRIPTOR Device_Descriptor = // ok (2)
{
	(uint8_t*)MS_USBD_DeviceDescriptor,
	USBD_SIZE_DEVICE_DESC
};


ONE_DESCRIPTOR Config_Descriptor_KB; // ok (2)
// {
// 	(uint8_t*)USBD_ConfigDescriptor_KB,
// 	USBD_SIZE_CONFIG_DESC
// };

//ONE_DESCRIPTOR Config_Descriptor_MS; //= // ok (2)
// {
// 	(uint8_t*)USBD_ConfigDescriptor_MS,
// 	USBD_SIZE_CONFIG_DESC
// };

ONE_DESCRIPTOR String_Descriptor[4];

/*******************************************************************************/
/* Interrupt Function Declaration */
void TIM3_IRQHandler(void) __attribute__((naked));

void SetLEDHighForDuration(int ms) 
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
    Delay_Ms(ms);               // Delay for the specified time
    GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
}

// void SysTick_Handler(void)
// {
//     millis_counter++; // Increment the millisecond counter every 1 ms
// }

// void SysTick_Init(void)
// {
//     // SystemCoreClock is typically set to 48MHz, adjust accordingly
//     // SysTick_Config(SystemCoreClock / 1000); // 1 ms tick
// }

// uint32_t millis(void)
// {
//     return millis_counter;
// }

/*********************************************************************
 * @fn      TIM3_Init
 *
 * @brief   Initialize timer3 for getting keyboard and mouse data.
 *
 * @param   arr - The specific period value.
 *          psc - The specifies prescaler value.
 *
 * @return  none
 */
void TIM3_Init( uint16_t arr, uint16_t psc )
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = { 0 };
    NVIC_InitTypeDef NVIC_InitStructure = { 0 };

    /* Enable timer3 clock */
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );

    /* Initialize timer3 */
    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );

    /* Enable updating timer3 interrupt */
    TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE );

    /* Configure timer3 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &NVIC_InitStructure );

    /* Enable timer3 */
    TIM_Cmd( TIM3, ENABLE );

    /* Enable timer3 interrupt */
    NVIC_EnableIRQ( TIM3_IRQn );
}

/*********************************************************************
 * @fn      TIM3_IRQHandler
 *
 * @brief   Wrapper function for TIM3_IRQHandler_Real
 *
 * @return  none
 */
void TIM3_IRQHandler( void )
{

    __asm volatile ("call TIM3_IRQHandler_Real; mret");
}

/*********************************************************************
 * @fn      TIM3_IRQHandler_Real
 *
 * @brief   This function handles TIM3 global interrupt request.
 *
 * @return  none
 */
void TIM3_IRQHandler_Real( void )
{
    uint8_t index;
    uint8_t hub_port;
    uint8_t intf_num, in_num;

    if( TIM_GetITStatus( TIM3, TIM_IT_Update ) != RESET )
    {
        /* Clear interrupt flag */
        TIM_ClearITPendingBit( TIM3, TIM_IT_Update );

        /* USB HID Device Input Endpoint Timing */
        if( RootHubDev.bStatus >= ROOT_DEV_SUCCESS )
        {
            index = RootHubDev.DeviceIndex;
            if( RootHubDev.bType == USB_DEV_CLASS_HID )
            {
                for( intf_num = 0; intf_num < HostCtl[ index ].InterfaceNum; intf_num++ )
                {
                    for( in_num = 0; in_num < HostCtl[ index ].Interface[ intf_num ].InEndpNum; in_num++ )
                    {
                        HostCtl[ index ].Interface[ intf_num ].InEndpTimeCount[ in_num ]++;
                    }
                }
            }
            else if( RootHubDev.bType == USB_DEV_CLASS_HUB )
            {
                HostCtl[ index ].Interface[ 0 ].InEndpTimeCount[ 0 ]++;
                for( hub_port = 0; hub_port < RootHubDev.bPortNum; hub_port++ )
                {
                    if( RootHubDev.Device[ hub_port ].bStatus >= ROOT_DEV_SUCCESS )
                    {
                        index = RootHubDev.Device[ hub_port ].DeviceIndex;

                        if( RootHubDev.Device[ hub_port ].bType == USB_DEV_CLASS_HID )
                        {
                            for( intf_num = 0; intf_num < HostCtl[ index ].InterfaceNum; intf_num++ )
                            {
                                for( in_num = 0; in_num < HostCtl[ index ].Interface[ intf_num ].InEndpNum; in_num++ )
                                {
                                    HostCtl[ index ].Interface[ intf_num ].InEndpTimeCount[ in_num ]++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/*********************************************************************
 * @fn      USBH_AnalyseType
 *
 * @brief   Simply analyze USB device type.
 *
* @para     pdev_buf: Device descriptor buffer
 *          pcfg_buf: Configuration descriptor buffer
 *          ptype: Device type.
 *
 * @return  none
 */
uint8_t temp_USBH_AnalyseType( uint8_t *pdev_buf)
{
    uint8_t  dv_cls;

    dv_cls = ( (PUSB_DEV_DESCR)pdev_buf )->bDeviceClass;

    //return dv_cls;

    if( ( dv_cls == USB_DEV_CLASS_HID ) )
    {
        return 1;
    }
    else if( ( dv_cls == USB_DEV_CLASS_HUB ) )
    {
        return 2;
    }
    return 0;

}

/*********************************************************************
 * @fn      USBH_AnalyseType
 *
 * @brief   Simply analyze USB device type.
 *
* @para     pdev_buf: Device descriptor buffer
 *          pcfg_buf: Configuration descriptor buffer
 *          ptype: Device type.
 *
 * @return  none
 */
void USBH_AnalyseType( uint8_t *pdev_buf, uint8_t *pcfg_buf, uint8_t *ptype )
{
    uint8_t  dv_cls, if_cls;

    dv_cls = ( (PUSB_DEV_DESCR)pdev_buf )->bDeviceClass;
    if_cls = ( (PUSB_CFG_DESCR_LONG)pcfg_buf )->itf_descr.bInterfaceClass;
    if( ( dv_cls == USB_DEV_CLASS_STORAGE ) || ( if_cls == USB_DEV_CLASS_STORAGE ) )
    {
        *ptype = USB_DEV_CLASS_STORAGE;
    }
    else if( ( dv_cls == USB_DEV_CLASS_PRINTER ) || ( if_cls == USB_DEV_CLASS_PRINTER ) )
    {
        *ptype = USB_DEV_CLASS_PRINTER;
    }
    else if( ( dv_cls == USB_DEV_CLASS_HID ) || ( if_cls == USB_DEV_CLASS_HID ) )
    {
        *ptype = USB_DEV_CLASS_HID;
    }
    else if( ( dv_cls == USB_DEV_CLASS_HUB ) || ( if_cls == USB_DEV_CLASS_HUB ) )
    {
        *ptype = USB_DEV_CLASS_HUB;
    }
    else
    {
        *ptype = DEF_DEV_TYPE_UNKNOWN;
    }
}

/*********************************************************************
 * @fn      USBH_EnumRootDevice
 *
 * @brief   Generally enumerate a device connected to host port.
 *
 * @para    index: USB host port
 *
 * @return  Enumeration result
 */
uint8_t USBH_EnumRootDevice( void )
{
    uint8_t  s;
    uint8_t  enum_cnt;
    uint8_t  cfg_val;
    uint16_t i;
    uint16_t len;

    DUG_PRINTF( "Enum:\r\n" );

    enum_cnt = 0;
ENUM_START:
    /* Delay and wait for the device to stabilize */
    Delay_Ms( 100 );
    enum_cnt++;
    Delay_Ms( 8 << enum_cnt );

    /* Reset the USB device and wait for the USB device to reconnect */
    USBFSH_ResetRootHubPort( 0 );
    for( i = 0, s = 0; i < DEF_RE_ATTACH_TIMEOUT; i++ )
    {
        if( USBFSH_EnableRootHubPort( &RootHubDev.bSpeed ) == ERR_SUCCESS )
        {
            i = 0;
            s++;
            if( s > 6 )
            {
                break;
            }
        }
        Delay_Ms( 1 );
    }
    if( i )
    {
        /* Determine whether the maximum number of retries has been reached, and retry if not reached */
        if( enum_cnt <= 5 )
        {
            goto ENUM_START;
        }
        return ERR_USB_DISCON;
    }

    /* Get USB device device descriptor */
    //DUG_PRINTF("Get DevDesc: ");
    uint8_t  t_DevDesc_Buf[ 18 ]; 

    // Declare variables
    uint16_t dev_desc_len = 0;            // Variable to hold the actual length of the device descriptor

    s = USBFSH_GetDeviceDescr(&RootHubDev.bEp0MaxPks, DevDesc_Buf, sizeof(DevDesc_Buf), &dev_desc_len);

    // Check if the call was successful
    if (s == ERR_SUCCESS) 
    {
        DUG_PRINTF("Device Descriptor received successfully, Length: %d\n", dev_desc_len);
        DUG_PRINTF("\r\n");
        
        Device_Descriptor.Descriptor_Size = 18;
        
        for( i = 0; i < dev_desc_len; i++ )
        {
            MS_USBD_DeviceDescriptor[i] = DevDesc_Buf[i];
        }
        MS_USBD_DeviceDescriptor[4] = 0x01;
        Device_Descriptor.Descriptor = MS_USBD_DeviceDescriptor;

        #if DEF_DEBUG_PRINTF_IMP

            DUG_PRINTF("DEVICE DESCRIPTER 1 ..........  \r\n");

            for( i = 0; i < dev_desc_len; i++ )
            {
                DUG_PRINTF( "%02x ", Device_Descriptor.Descriptor[ i ] );
            }
            DUG_PRINTF("\r\n");

        #endif
           
    } else {
    }

    if( s == ERR_SUCCESS )
    {
        /* Print USB device device descriptor */
    }

    /* Set the USB device address */
    DUG_PRINTF("Set DevAddr: ");
    RootHubDev.bAddress = (uint8_t)( USB_DEVICE_ADDR );
    s = USBFSH_SetUsbAddress( RootHubDev.bEp0MaxPks, RootHubDev.bAddress );
    if( s == ERR_SUCCESS )
    {
        DUG_PRINTF( "OK\r\n" );

        RootHubDev.bAddress = USB_DEVICE_ADDR;
    }
    else
    {
        /* Determine whether the maximum number of retries has been reached, and retry if not reached */
        DUG_PRINTF( "Err(%02x)\r\n", s );
        if( enum_cnt <= 5 )
        {
            goto ENUM_START;
        }
        return DEF_DEV_ADDR_SETFAIL;
    }
    Delay_Ms( 5 );

    /* Get the USB device configuration descriptor */

    uint8_t  temp_Com_Buf[ DEF_COM_BUF_LEN ];
    s = USBFSH_GetConfigDescr( RootHubDev.bEp0MaxPks, Com_Buf, DEF_COM_BUF_LEN, &len );

    //USBFSH_GetConfigDescr( RootHubDev.bEp0MaxPks, temp_Com_Buf, DEF_COM_BUF_LEN, &len );

    for( i = 0; i < 18; i++ )
    {
        USBD_ConfigDescriptor_KB[i] = Com_Buf[i];
    }
    USBD_ConfigDescriptor_KB[2] = 0x54;
    USBD_ConfigDescriptor_KB[6] = 0x00;
    USBD_ConfigDescriptor_KB[14] = 0x03;
    //if(temp_Com_Buf != NULL)
    {
        Config_Descriptor_KB.Descriptor = (uint8_t*)USBD_ConfigDescriptor_KB;
        //Config_Descriptor_KB.Descriptor = (uint8_t*)temp_Com_Buf;
        Config_Descriptor_KB.Descriptor_Size = 34; 
    }

    if( s == ERR_SUCCESS )
    {

        #if DEF_DEBUG_PRINTF_IMP
            
            DUG_PRINTF("CHECK CONFIG DESCRIPTER 1 ..........  \r\n");
            for( i = 0; i < 34; i++ )
            {
                DUG_PRINTF( "%02x ", Config_Descriptor_KB.Descriptor[ i ] );
            }
            DUG_PRINTF("\r\n");
        #endif

        cfg_val = ( (PUSB_CFG_DESCR)Com_Buf )->bConfigurationValue;
        
        /* Simply analyze USB device type  */
        USBH_AnalyseType( DevDesc_Buf, Com_Buf, &RootHubDev.bType );
        DUG_PRINTF( "DevType: %02x\r\n", RootHubDev.bType );
    }
    else
    {
        /* Determine whether the maximum number of retries has been reached, and retry if not reached */
        DUG_PRINTF( "Err(%02x)\r\n", s );
        if( enum_cnt <= 5 )
        {
            goto ENUM_START;
        }
        return DEF_CFG_DESCR_GETFAIL;
    }

    /* Set USB device configuration value */
    DUG_PRINTF("Set Cfg: ");
    s = USBFSH_SetUsbConfig( RootHubDev.bEp0MaxPks, cfg_val );
    if( s == ERR_SUCCESS )
    {
        DUG_PRINTF( "OK\r\n" );
    }
    else
    {
        /* Determine whether the maximum number of retries has been reached, and retry if not reached */
        DUG_PRINTF( "Err(%02x)\r\n", s );
        if( enum_cnt <= 5 )
        {
            goto ENUM_START;
        }
        return ERR_USB_UNSUPPORT;
    }

    return ERR_SUCCESS;
}

/*********************************************************************
 * @fn      KM_AnalyzeConfigDesc
 *
 * @brief   Analyze keyboard and mouse configuration descriptor.
 *
 * @para    index: USB host port
 *
 * @return  The result of the analysis.
 */
uint8_t KM_AnalyzeConfigDesc( uint8_t index, uint8_t ep0_size  )
{
    uint8_t  s = 0;
    uint16_t i;
    uint8_t  num, innum, outnum;

    num = 0;
    for( i = 0; i < ( Com_Buf[ 2 ] + ( (uint16_t)Com_Buf[ 3 ] << 8 ) ); )
    {
        if( Com_Buf[ i + 1 ] == DEF_DECR_CONFIG )
        {
            /* Save the number of interface of the USB device, only up to 4 */
            if( ( (PUSB_CFG_DESCR)( &Com_Buf[ i ] ) )->bNumInterfaces > DEF_INTERFACE_NUM_MAX )
            {
                HostCtl[ index ].InterfaceNum = DEF_INTERFACE_NUM_MAX;
            }
            else
            {
                HostCtl[ index ].InterfaceNum = ( (PUSB_CFG_DESCR)( &Com_Buf[ i ] ) )->bNumInterfaces;
            }
            i += Com_Buf[ i ];
        }
        else if( Com_Buf[ i + 1 ] == DEF_DECR_INTERFACE )
        {
            if( num == DEF_INTERFACE_NUM_MAX )
            {
                return s;
            }
            if( ( (PUSB_ITF_DESCR)( &Com_Buf[ i ] ) )->bInterfaceClass == 0x03 )
            {
                /* HID devices (such as USB keyboard and mouse) */
                if( ( (PUSB_ITF_DESCR)( &Com_Buf[ i ] ) )->bInterfaceSubClass <= 0x01 &&
                    ( (PUSB_ITF_DESCR)( &Com_Buf[ i ] ) )->bInterfaceProtocol <= 2 )
                {
                    if( ( (PUSB_ITF_DESCR)( &Com_Buf[ i ] ) )->bInterfaceProtocol == 0x01 ) // Keyboard
                    {
                        HostCtl[ index ].Interface[ num ].Type = DEC_KEY;
                        new_descripter = 0;
                        //HID_SetIdle( ep0_size, num, 0, 0 );
                    }
                    else if( ( (PUSB_ITF_DESCR)( &Com_Buf[ i ] ) )->bInterfaceProtocol == 0x02 ) // Mouse
                    {
                        HostCtl[ index ].Interface[ num ].Type = DEC_MOUSE;
                        new_descripter = 1;
                        //HID_SetIdle( ep0_size, num, 0, 0 );
                    }
                    s = ERR_SUCCESS;
                    i += Com_Buf[ i ];
                    innum = 0;
                    outnum = 0;
                    while( 1 )
                    {
                        if( ( Com_Buf[ i + 1 ] == DEF_DECR_INTERFACE ) || ( i >= Com_Buf[ 2 ] ) )
                        {
                            break;
                        }
                        else
                        {
                            /* Analyze each endpoint of the current interface */
                            if( Com_Buf[ i + 1 ] == DEF_DECR_ENDPOINT )
                            {
                                /* Save endpoint related information (endpoint address, attribute, max packet size, polling interval) */
                                if( ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bEndpointAddress & 0x80 )
                                {
                                    /* IN */
                                    HostCtl[ index ].Interface[ num ].InEndpAddr[ innum ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bEndpointAddress & 0x0F;
                                    HostCtl[ index ].Interface[ num ].InEndpType[ innum ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bmAttributes;
                                    HostCtl[ index ].Interface[ num ].InEndpSize[ innum ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->wMaxPacketSizeL +
                                                                              (uint16_t)( ( ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->wMaxPacketSizeH) << 8);
                                    HostCtl[ index ].Interface[ num ].InEndpInterval[ innum ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bInterval;
                                    HostCtl[ index ].Interface[ num ].InEndpNum++;
                                    
                                    innum++;
                                }
                                else
                                {
                                    /* OUT */
                                    HostCtl[ index ].Interface[ num ].OutEndpAddr[ outnum ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bEndpointAddress & 0x0f;
                                    HostCtl[ index ].Interface[ num ].OutEndpType[ outnum ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bmAttributes;
                                    HostCtl[ index ].Interface[ num ].OutEndpSize[ outnum ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->wMaxPacketSizeL +
                                                                                (uint16_t)( ( ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->wMaxPacketSizeH) << 8);
                                    HostCtl[ index ].Interface[ num ].OutEndpNum++;

                                    outnum++;
                                }

                                i += Com_Buf[ i ];
                            }
                            else if( Com_Buf[ i + 1 ] == DEF_DECR_HID )
                            {
                                /* Save the current interface HID report descriptor length */
                                HostCtl[ index ].Interface[ num ].HidDescLen = ( (PUSB_HID_DESCR)( &Com_Buf[ i ] ) )->wDescriptorLengthL | \
                                                                               ( (uint16_t)( ( (PUSB_HID_DESCR)( &Com_Buf[ i ] ) )->wDescriptorLengthH ) << 8 );
                                i += Com_Buf[ i ];
                            }
                            else
                            {
                                i += Com_Buf[ i ];
                            }
                        }
                    }

                    if( ( outnum == 1 ) && ( HostCtl[ index ].Interface[ num ].Type == DEC_KEY ) )
                    {
                        HostCtl[ index ].Interface[ num ].SetReport_Swi = 0xFF;
                    }
                }
                else
                {
                    HostCtl[ index ].Interface[ num ].Type = DEC_UNKNOW;
                    i += Com_Buf[ i ];
                }
            }
            else
            {
                /* USB device type unknown */
                HostCtl[ index ].Interface[ num ].Type = DEC_UNKNOW;
                i += Com_Buf[ i ];

                break;
            }
                  
            num++;
        }
        else
        {
            i += Com_Buf[ i ];
        }
    }
    
    return s;
}

/*********************************************************************
 * @fn      KM_AnalyzeHidReportDesc
 *
 * @brief   Analyze keyboard and mouse report descriptor.
 *
 * @para    index: USB host port
 *
 * @return  The result of the analysis.
 */
void KM_AnalyzeHidReportDesc( uint8_t index, uint8_t intf_num )
{
    uint8_t  id = 0x00;
    uint8_t  led = 0x00;
    uint8_t  size, type, tag;
    uint8_t  report_size;
    uint8_t  report_cnt;
    uint16_t report_bits;

    uint16_t i = 0;

    /* Usage Page(Generic Desktop), Usage(Kyeboard) */
    if( ( Com_Buf[ i + 0 ] == 0x05 ) && ( Com_Buf[ i + 1 ] == 0x01 ) &&
        ( Com_Buf[ i + 2 ] == 0x09 ) && ( Com_Buf[ i + 3 ] == 0x06 ) )
    {
        i += 4;
        report_size = 0;
        report_cnt = 0;
        report_bits = 0;

        while( i < HostCtl[ index ].Interface[ intf_num ].HidDescLen )
        {
            /* Item Size, Item Type, Item Tag */
            size = Com_Buf[ i ] & 0x03;
            type = Com_Buf[ i ] & 0x0C;
            tag = Com_Buf[ i ] & 0xF0;

            switch( type )
            {
                /* MAIN */
                case 0x00:
                    switch( tag )
                    {
                        /* Output */
                        case 0x90:
                            if( led )
                            {
                                report_bits += report_cnt * report_size;

                                /* Save report ID for output */
                                if( ( id != 0 ) && ( HostCtl[ index ].Interface[ intf_num ].IDFlag == 0 ) )
                                {
                                    HostCtl[ index ].Interface[ intf_num ].IDFlag = 1;
                                    HostCtl[ index ].Interface[ intf_num ].ReportID = id;
                                }
                            }
                            i++;
                            break;

                        default:
                            i++;
                            break;
                    }
                    break;

                /* Global */
                case 0x04:
                    switch( tag )
                    {
                        /* Report ID */
                        case 0x80:
                            i++;
                            id = Com_Buf[ i ];
                            break;

                        /* Report Count */
                        case 0x90:
                            i++;
                            report_cnt = Com_Buf[ i ];
                            break;

                        /* Report Size */
                        case 0x70:
                            i++;
                            report_size = Com_Buf[ i ];
                            //report_byte = (report_size * report_cnt) / 8;
                            break;

                        /* Usage Page */
                        case 0x00:
                            i++;
                            if( Com_Buf[ i ] == 0x08 )      // LED
                            {
                                led = 1;
                            }
                            else
                            {
                                led = 0;
                            }
                            break;

                        default:
                            i++;
                            break;
                    }
                    break;

                /* Local */
                case 0x08:
                    switch( tag )
                    {
                        /* Usage Minimum */
                        case 0x10:
                            i++;
                            if( led )
                            {
                                HostCtl[ index ].Interface[ intf_num ].LED_Usage_Min = Com_Buf[ i ];
                            }
                            break;

                        /* Usage Maximum */
                        case 0x20:
                            i++;
                            if( led )
                            {
                                HostCtl[ index ].Interface[ intf_num ].LED_Usage_Max = Com_Buf[ i ];
                            }
                            break;

                        default:
                            i++;
                            break;
                    }
                    break;

                default:
                    i++;
                    break;
            }
            i += size;
        }

        if( report_bits == 8 )
        {
            if( HostCtl[ index ].Interface[ intf_num ].SetReport_Swi == 0 )
            {
                HostCtl[ index ].Interface[ intf_num ].SetReport_Swi = 1;
            }
        }
        else
        {
            HostCtl[ index ].Interface[ intf_num ].SetReport_Swi = 0;
        }
    }
}

uint8_t* find_hid_descriptor(uint8_t* config_desc, uint16_t length) {
    uint16_t index = 0;
    while (index < length) {
        uint8_t desc_length = config_desc[index];
        uint8_t desc_type = config_desc[index + 1];

        // Check if this is the HID descriptor (Type 0x21)
        if (desc_type == 0x21) {
            return &config_desc[index];
        }

        // Move to the next descriptor
        index += desc_length;
    }
    return NULL; // Not found
}

int calculate_report_size(const uint8_t *report_descriptor, int length) {
    int report_size = 0;
    
    for (int i = 0; i < length; i++) {
        if (report_descriptor[i] == 0x75) {  // Report Size tag
            report_size = report_descriptor[i + 1];  // Next byte is the Report Size (in bits)
        }
        if (report_descriptor[i] == 0x95) {  // Report Count tag
            int report_count = report_descriptor[i + 1];  // Next byte is the Report Count
            return (report_count); 
        }
    }

    return 0;  // If no valid report size/count found
}

void processArray(uint8_t* arr, size_t* size) {
    size_t i = 0;
    while (i < *size) {
        // Check for condition at arr[50]
        if (i == 50 && arr[i] == 0x15) {
            // Remove arr[50] and arr[51]
            for (size_t j = i; j < *size - 2; j++) {
                arr[j] = arr[j + 2]; // Shift elements left by 2
            }
            *size -= 2; // Decrease the size by 2
            continue; // Restart loop
        }

        // Check for condition at arr[61]
        if (arr[i] == 0x2A) {
            arr[i] = 0x29;    // Set arr[61] to 0x29
            arr[i + 1] = 0x91; // Set arr[62] to 0x91
            // Remove arr[63] by shifting elements left by 1
            for (size_t j = i + 2; j < *size - 1; j++) {
                arr[j] = arr[j + 1]; // Shift elements left by 1
            }
            *size -= 1; // Decrease the size by 1
            continue; // Restart loop
        }
        i++; // Move to the next index
    }
    //size++;
}

/*********************************************************************
 * @fn      KM_DealHidReportDesc
 *
 * @brief   Get and analyze keyboard and mouse report descriptor.
 *
 * @para    index: USB host port
 *
 * @return  The result of the acquisition and analysis.
 */
uint8_t KM_DealHidReportDesc( uint8_t index, uint8_t ep0_size )
{
    uint8_t  s;
    uint8_t  num, num_tmp;
    uint8_t  getrep_cnt;
#if DEF_DEBUG_PRINTF
    uint16_t i;
#endif

    getrep_cnt = 0;
    num_tmp = HostCtl[ index ].InterfaceNum;
    while( num_tmp )
    {
        num = HostCtl[ index ].InterfaceNum - num_tmp;
        if( HostCtl[ index ].Interface[ num ].HidDescLen )
        {
GETREP_START:
            getrep_cnt++;
            
            /* Get HID report descriptor */
            //DUG_PRINTF("Get Interface%x RepDesc: ", num );
            uint8_t  temp_Com_Buf[ DEF_COM_BUF_LEN ];

            s = HID_GetHidDesr( ep0_size, num, Com_Buf, &HostCtl[ index ].Interface[ num ].HidDescLen );
            //HID_GetHidDesr( ep0_size, num, temp_Com_Buf, &HostCtl[ index ].Interface[ num ].HidDescLen );

            int size = HostCtl[ index ].Interface[ num ].HidDescLen;

            if(Report_Descriptor.Descriptor == NULL)
            {
                int i =0;

                for( i = 0; i < size; i++ )
                {
                    USBD_KeyRepDesc[i] = Com_Buf[i];
                }
                Report_Descriptor.Descriptor = USBD_KeyRepDesc;

                //Report_Descriptor.Descriptor = (uint8_t*)USBD_KeyRepDesc;
                //Report_Descriptor.Descriptor_Size = (sizeof(USBD_KeyRepDesc) / sizeof(USBD_KeyRepDesc[0]));
                
                //Report_Descriptor.Descriptor = (uint8_t*)temp_Com_Buf;

                processArray(Report_Descriptor.Descriptor,&size);

                //Report_Descriptor.Descriptor_Size =  size;

                for(i=0;i<size-1;i++)
                {
                    if(Report_Descriptor.Descriptor[i] == 0xc0 && Report_Descriptor.Descriptor[i+1] == 0xc0)
                    {
                        i = i + 2;
                        break;
                    }
                }

                Report_Descriptor.Descriptor_Size = i+1;

                report_byte = calculate_report_size(Report_Descriptor.Descriptor, size);

                /* Analyze Report Descriptor */
                KM_AnalyzeHidReportDesc( index, num );

                #if DEF_DEBUG_PRINTF_IMP
                        DUG_PRINTF("HID REPORT DESCRIPTER ..........  \r\n");
                        for( i = 0; i < Report_Descriptor.Descriptor_Size; i++ )
                        {
                            DUG_PRINTF( "%02x ", Report_Descriptor.Descriptor[ i ] );
                        }
                        DUG_PRINTF("\r\n");
                #endif
            }
            num_tmp--;
        }
        else
        {
            num_tmp--;
        }
    }

    return s;
}

/*********************************************************************
 * @fn      USBH_EnumHidDevice
 *
 * @brief   Enumerate HID device.
 *
 * @para    index: USB host port
 *
 * @return  The result of the enumeration.
 */
uint8_t USBH_EnumHidDevice( uint8_t index, uint8_t ep0_size )
{
    uint8_t  s;
    uint8_t  intf_num;
#if DEF_DEBUG_PRINTF
    uint8_t  i;
#endif


    DUG_PRINTF( "Enum Hid:\r\n" );
    
    /* Analyze HID class device configuration descriptor and save relevant parameters */
    DUG_PRINTF("Analyze CfgDesc: ");
    s = KM_AnalyzeConfigDesc( index, ep0_size );
    if( s == ERR_SUCCESS )
    {
        DUG_PRINTF( "OK\r\n" );
    }
    else
    {
        DUG_PRINTF( "Err(%02x)\r\n", s );
        return s;
    }

    /* Get the string descriptor contained in the configuration descriptor if it exists */
    if( Com_Buf[ 6 ] )
    {
        s = USBFSH_GetStrDescr( ep0_size, Com_Buf[ 6 ], Com_Buf );
        uint8_t size = Com_Buf[0]; // USBD_SIZE_STRING_LANGID

        //String_Descriptor[0].Descriptor = (uint8_t*)USBD_StringLangID;
        String_Descriptor[0].Descriptor = Com_Buf;
        String_Descriptor[0].Descriptor_Size = USBD_SIZE_STRING_LANGID;

        if( s == ERR_SUCCESS )
        {
            /* Print the string descriptor contained in the configuration descriptor */
#if DEF_DEBUG_PRINTF
            DUG_PRINTF("Get StringDesc4: ");
            for( i = 0; i < Com_Buf[ 0 ]; i++ )
            {
                DUG_PRINTF( "%02x ", Com_Buf[ i ] );
            }
            DUG_PRINTF("\r\n");
#endif
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
        }
    }

    /* Get HID report descriptor */
    s = KM_DealHidReportDesc( index, ep0_size );
    
    /* Get USB vendor string descriptor  */
    if( DevDesc_Buf[ 14 ] )
    {
        s = USBFSH_GetStrDescr( ep0_size, DevDesc_Buf[ 14 ], Com_Buf );
        uint8_t size = Com_Buf[0]; // USBD_SIZE_STRING_VENDOR

        //String_Descriptor[1].Descriptor = (uint8_t*)USBD_StringVendor;
        String_Descriptor[1].Descriptor = Com_Buf;
        String_Descriptor[1].Descriptor_Size = USBD_SIZE_STRING_VENDOR;

        if( s == ERR_SUCCESS )
        {
            /* Print USB vendor string descriptor */
#if DEF_DEBUG_PRINTF
            DUG_PRINTF("Get StringDesc1: ");
            for( i = 0; i < Com_Buf[ 0 ]; i++ )
            {
                DUG_PRINTF( "%02x ", Com_Buf[ i ]);
            }
            DUG_PRINTF("\r\n");
#endif
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
        }
    }

    /* Get USB product string descriptor */
    if( DevDesc_Buf[ 15 ] )
    {
        s = USBFSH_GetStrDescr( ep0_size, DevDesc_Buf[ 15 ], Com_Buf );
        uint8_t size = Com_Buf[0]; // USBD_SIZE_STRING_PRODUCT
 
        //String_Descriptor[2].Descriptor = (uint8_t*)USBD_StringProduct;
        String_Descriptor[2].Descriptor = (uint8_t*)Com_Buf;
        String_Descriptor[2].Descriptor_Size = USBD_SIZE_STRING_PRODUCT;

        if( s == ERR_SUCCESS )
        {
            /* Print USB product string descriptor */
#if DEF_DEBUG_PRINTF
            DUG_PRINTF("Get StringDesc2: ");
            for( i = 0; i < Com_Buf[ 0 ]; i++ )
            {
                DUG_PRINTF( "%02x ", Com_Buf[ i ] );
            }
            DUG_PRINTF("\r\n");
#endif
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
        }
    }

    /* Get USB serial number string descriptor */
    if( DevDesc_Buf[ 16 ] )
    {
        s = USBFSH_GetStrDescr( ep0_size, DevDesc_Buf[ 16 ], Com_Buf );
        uint8_t size = Com_Buf[0]; // USBD_SIZE_STRING_SERIAL

        //String_Descriptor[3].Descriptor = (uint8_t*)USBD_StringSerial;
        String_Descriptor[3].Descriptor = (uint8_t*)Com_Buf;
        String_Descriptor[3].Descriptor_Size = USBD_SIZE_STRING_SERIAL;
        
        if( s == ERR_SUCCESS )
        {
            /* Print USB serial number string descriptor */
#if DEF_DEBUG_PRINTF
            DUG_PRINTF("Get StringDesc3: ");
            for( i = 0; i < Com_Buf[ 0 ]; i++ )
            {
                DUG_PRINTF( "%02x ", Com_Buf[ i ] );
            }
            DUG_PRINTF("\r\n");
#endif
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
        }
    }
    /* Get USB serial number string descriptor */
    for( intf_num = 0; intf_num < HostCtl[ index ].InterfaceNum; intf_num++ )
    {
        if( HostCtl[ index ].Interface[ intf_num ].Type == DEC_KEY )
        {
            HostCtl[ index ].Interface[ intf_num ].SetReport_Value = 0x00;
            KB_SetReport( index, ep0_size, intf_num );
        }
    }

    //if(new_descripter == 0 || new_descripter == 1) 
    {
        Set_USBConfig();
        USB_Init();
        USB_Interrupts_Config();
        while( bDeviceState != CONFIGURED )
        {
        }
    }

    return ERR_SUCCESS;
}

/*********************************************************************
 * @fn      HUB_Analyse_ConfigDesc
 *
 * @brief   Analyze HUB configuration descriptor.
 *
 * @para
 *
 * @return  none
 */
uint8_t HUB_AnalyzeConfigDesc( uint8_t index )
{
    uint8_t  s = ERR_SUCCESS;
    uint16_t i;

    for( i = 0; i < ( Com_Buf[ 2 ] + ( (uint16_t)Com_Buf[ 3 ] << 8 ) ); )
    {
        if( Com_Buf[ i + 1 ] == DEF_DECR_CONFIG )
        {
            /* Save the number of interface of the USB device, only up to 4 */
            if( ( (PUSB_CFG_DESCR)( &Com_Buf[ i ] ) )->bNumInterfaces > 1 )
            {
                HostCtl[ index ].InterfaceNum = 1;
            }
            else
            {
                HostCtl[ index ].InterfaceNum = ( (PUSB_CFG_DESCR)( &Com_Buf[ i ] ) )->bNumInterfaces;
            }
            i += Com_Buf[ i ];
        }
        else if( Com_Buf[ i + 1 ] == DEF_DECR_INTERFACE )
        {
            if( ( (PUSB_ITF_DESCR)( &Com_Buf[ i ] ) )->bInterfaceClass == 0x09 )
            {
                i += Com_Buf[ i ];
                while( 1 )
                {
                    if( ( Com_Buf[ i + 1 ] == DEF_DECR_INTERFACE ) || ( i >= ( Com_Buf[ 2 ] + ( (uint16_t)Com_Buf[ 3 ] << 8 ) ) ) )
                    {
                        break;
                    }
                    else
                    {
                        /* Analyze each endpoint of the current interface */
                        if( Com_Buf[ i + 1 ] == DEF_DECR_ENDPOINT )
                        {
                            /* Save endpoint related information (endpoint address, attribute, max packet size, polling interval) */
                            if( ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bEndpointAddress & 0x80 )
                            {
                                /* IN */
                                HostCtl[ index ].Interface[ 0 ].InEndpAddr[ 0 ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bEndpointAddress & 0x0F;
                                HostCtl[ index ].Interface[ 0 ].InEndpType[ 0 ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bmAttributes;
                                HostCtl[ index ].Interface[ 0 ].InEndpSize[ 0 ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->wMaxPacketSizeL + \
                                                                                  (uint16_t)( ( ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->wMaxPacketSizeH ) << 8 );
                                HostCtl[ index ].Interface[ 0 ].InEndpInterval[ 0 ] = ( (PUSB_ENDP_DESCR)( &Com_Buf[ i ] ) )->bInterval;
                                HostCtl[ index ].Interface[ 0 ].InEndpNum++;
                            }

                            i += Com_Buf[ i ];
                        }
                        else
                        {
                            i += Com_Buf[ i ];
                        }
                    }
                }
            }
            else
            {
                /* USB device type unknown */
                i += Com_Buf[ i ];
            }
        }
        else
        {
            i += Com_Buf[ i ];
        }
    }
    return s;
}

/*********************************************************************
 * @fn      USBH_EnumHubDevice
 *
 * @brief   Enumerate HUB device.
 *
 * @para    index: USB host port
 *
 * @return  The result of the enumeration.
 */
uint8_t USBH_EnumHubDevice( void )
{
    uint8_t  s, retry;
    uint16_t len;
    uint16_t  i;

    DUG_PRINTF( "Enum Hub:\r\n" );

    /* Analyze HID class device configuration descriptor and save relevant parameters */
    DUG_PRINTF("Analyze CfgDesc: ");
    s = HUB_AnalyzeConfigDesc( RootHubDev.DeviceIndex );
    if( s == ERR_SUCCESS )
    {
        DUG_PRINTF( "OK\r\n" );
    }
    else
    {
        DUG_PRINTF( "Err(%02x)\r\n", s );
        return s;
    }

    /* Get the string descriptor contained in the configuration descriptor if it exists */
    if( Com_Buf[ 6 ] )
    {
        s = USBFSH_GetStrDescr( RootHubDev.bEp0MaxPks, Com_Buf[ 6 ], Com_Buf );
        uint8_t size = Com_Buf[0]; // USBD_SIZE_STRING_LANGID

        //String_Descriptor[0].Descriptor = (uint8_t*)USBD_StringLangID;
        String_Descriptor[0].Descriptor = Com_Buf;
        String_Descriptor[0].Descriptor_Size = USBD_SIZE_STRING_LANGID;

        if( s == ERR_SUCCESS )
        {
            /* Print the string descriptor contained in the configuration descriptor */
#if DEF_DEBUG_PRINTF
            DUG_PRINTF("Get StringDesc4: ");
            for( i = 0; i < Com_Buf[ 0 ]; i++ )
            {
                DUG_PRINTF( "%02x ", Com_Buf[ i ] );
            }
            DUG_PRINTF("\r\n");
#endif
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
        }
    }
    
    /* Get USB vendor string descriptor  */
    if( DevDesc_Buf[ 14 ] )
    {
        s = USBFSH_GetStrDescr( RootHubDev.bEp0MaxPks, DevDesc_Buf[ 14 ], Com_Buf );
        uint8_t size = Com_Buf[0];  // USBD_SIZE_STRING_VENDOR

        //String_Descriptor[1].Descriptor = (uint8_t*)USBD_StringVendor;
        String_Descriptor[1].Descriptor = Com_Buf;
        String_Descriptor[1].Descriptor_Size = USBD_SIZE_STRING_VENDOR;

        if( s == ERR_SUCCESS )
        {
            /* Print USB vendor string descriptor */
#if DEF_DEBUG_PRINTF
            DUG_PRINTF("Get StringDesc1: ");
            for( i = 0; i < Com_Buf[ 0 ]; i++ )
            {
                DUG_PRINTF( "%02x ", Com_Buf[ i ]);
            }
            DUG_PRINTF("\r\n");
#endif
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
        }
    }

    /* Get USB product string descriptor */
    if( DevDesc_Buf[ 15 ] )
    {
        s = USBFSH_GetStrDescr( RootHubDev.bEp0MaxPks, DevDesc_Buf[ 15 ], Com_Buf );
        uint8_t size = Com_Buf[0]; // USBD_SIZE_STRING_PRODUCT

        //String_Descriptor[2].Descriptor = (uint8_t*)USBD_StringProduct;
        String_Descriptor[2].Descriptor = Com_Buf;
        String_Descriptor[2].Descriptor_Size = USBD_SIZE_STRING_PRODUCT;

        if( s == ERR_SUCCESS )
        {
            /* Print USB product string descriptor */
#if DEF_DEBUG_PRINTF
            DUG_PRINTF("Get StringDesc2: ");
            for( i = 0; i < Com_Buf[ 0 ]; i++ )
            {
                DUG_PRINTF( "%02x ", Com_Buf[ i ] );
            }
            DUG_PRINTF("\r\n");
#endif
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
        }
    }

    /* Get USB serial number string descriptor */
    if( DevDesc_Buf[ 16 ] )
    {
        s = USBFSH_GetStrDescr( RootHubDev.bEp0MaxPks, DevDesc_Buf[ 16 ], Com_Buf );
        uint8_t size = Com_Buf[0]; // USBD_SIZE_STRING_SERIAL

        //String_Descriptor[3].Descriptor = (uint8_t*)USBD_StringSerial;
        String_Descriptor[3].Descriptor = Com_Buf;
        String_Descriptor[3].Descriptor_Size = USBD_SIZE_STRING_SERIAL;

        if( s == ERR_SUCCESS )
        {
            /* Print USB serial number string descriptor */
#if DEF_DEBUG_PRINTF
            DUG_PRINTF("Get StringDesc3: ");
            for( i = 0; i < Com_Buf[ 0 ]; i++ )
            {
                DUG_PRINTF( "%02x ", Com_Buf[ i ] );
            }
            DUG_PRINTF("\r\n");
#endif
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
        }
    }
    /* Get hub descriptor */
    DUG_PRINTF("Get Hub Desc: ");
    for( retry = 0; retry < 5; retry++ )
    {
        s = HUB_GetClassDevDescr( RootHubDev.bEp0MaxPks, Com_Buf, &len );
        if( s == ERR_SUCCESS )
        {
            /* Print USB device device descriptor */
#if DEF_DEBUG_PRINTF
            for( i = 0; i < len; i++ )
            {
                DUG_PRINTF( "%02x ", Com_Buf[ i ] );
            }
            DUG_PRINTF("\r\n");
#endif

            RootHubDev.bPortNum = ( (PUSB_HUB_DESCR)Com_Buf)->bNbrPorts;
            if( RootHubDev.bPortNum > DEF_NEXT_HUB_PORT_NUM_MAX )
            {
                RootHubDev.bPortNum = DEF_NEXT_HUB_PORT_NUM_MAX;
            }
            DUG_PRINTF( "RootHubDev.bPortNum: %02x\r\n", RootHubDev.bPortNum );
            break;
        }
        else
        {
            /* Determine whether the maximum number of retries has been reached, and retry if not reached */
            DUG_PRINTF( "Err(%02x)\r\n", s );

            if( retry == 4 )
            {
                return ERR_USB_UNKNOWN;
            }
        }
    }

    /* Set the HUB port to power on */
    for( retry = 0, i = 1; i <= RootHubDev.bPortNum; i++ )
    {
        s = HUB_SetPortFeature( RootHubDev.bEp0MaxPks, i, HUB_PORT_POWER );
        if( s == ERR_SUCCESS )
        {
            continue;
        }
        else
        {
            Delay_Ms( 5 );

            i--;
            retry++;
            if( retry >= 5 )
            {
                return ERR_USB_UNKNOWN;
            }
        }
    }

    return ERR_SUCCESS;
}

/*********************************************************************
 * @fn      HUB_Port_PreEnum1
 *
 * @brief
 *
 * @para
 *
 * @return  none
 */
uint8_t HUB_Port_PreEnum1( uint8_t hub_port, uint8_t *pbuf )
{
    uint8_t  s;
    uint8_t  buf[ 4 ];
    uint8_t  retry;

    if( ( *pbuf ) & ( 1 << hub_port ) )
    {
        s = HUB_GetPortStatus( RootHubDev.bEp0MaxPks, hub_port, &buf[ 0 ] );
        if( s != ERR_SUCCESS )
        {
            DUG_PRINTF( "HUB_PE1_ERR1:%x\r\n", s );
            return s;
        }
        else
        {
            if( buf[ 2 ] & 0x01 )
            {
                s = HUB_ClearPortFeature( RootHubDev.bEp0MaxPks, hub_port, HUB_C_PORT_CONNECTION );
                if( s != ERR_SUCCESS )
                {
                    DUG_PRINTF( "HUB_PE1_ERR2:%x\r\n", s );
                    return s;
                }

                retry = 0;
                do
                {
                    s = HUB_GetPortStatus( RootHubDev.bEp0MaxPks, hub_port, &buf[ 0 ] );
                    if( s != ERR_SUCCESS )
                    {
                        DUG_PRINTF( "HUB_PE1_ERR3:%x\r\n", s );
                        return s;
                    }
                    retry++;
                }while( ( buf[ 2 ] & 0x01 ) && ( retry < 10 ) );

                if( retry != 10 )
                {
                    if( !( buf[ 0 ] & 0x01 ) )
                    {
                        DUG_PRINTF( "Hub Port%x Out\r\n", hub_port );
                        return ERR_USB_DISCON;
                    }
                }
            }
        }
    }

    return ERR_USB_UNKNOWN;
}

/*********************************************************************
 * @fn      HUB_Port_PreEnum2
 *
 * @brief
 *
 * @para
 *
 * @return  none
 */
uint8_t HUB_Port_PreEnum2( uint8_t hub_port, uint8_t *pbuf )
{
    uint8_t  s;
    uint8_t  buf[ 4 ];
    uint8_t  retry = 0;

    if( ( *pbuf ) & ( 1 << hub_port ) )
    {
        s = HUB_SetPortFeature( RootHubDev.bEp0MaxPks, hub_port, HUB_PORT_RESET );
        if( s != ERR_SUCCESS )
        {
            DUG_PRINTF( "HUB_PE2_ERR1:%x\r\n", s );
            return s;
        }

        Delay_Ms( 10 );
        do
        {
            s = HUB_GetPortStatus( RootHubDev.bEp0MaxPks, hub_port, &buf[ 0 ] );
            if( s != ERR_SUCCESS )
            {
                DUG_PRINTF( "HUB_PE2_ERR2:%x\r\n", s );
                return s;
            }
            retry++;
        }while( ( !( buf[ 2 ] & 0x10 ) ) && ( retry <= 10 ) );

        if( retry != 10 )
        {
            retry = 0;
            s = HUB_ClearPortFeature( RootHubDev.bEp0MaxPks, hub_port, HUB_C_PORT_RESET  );

            do
            {
                s = HUB_GetPortStatus( RootHubDev.bEp0MaxPks, hub_port, &buf[ 0 ] );
                if( s != ERR_SUCCESS )
                {
                    DUG_PRINTF( "HUB_PE2_ERR3:%x\r\n", s );
                    return s;
                }
                retry++;
            }while( ( buf[ 2 ] & 0x10 ) && ( retry <= 10 ) );

            if( retry != 10 )
            {
                if( buf[ 0 ] & 0x01 )
                {
                    DUG_PRINTF( "Hub Port%x In\r\n", hub_port );
                    return ERR_USB_CONNECT;
                }
            }
        }
    }

    return ERR_USB_UNKNOWN;
}

/*********************************************************************
 * @fn      HUB_CheckPortSpeed
 *
 * @brief
 *
 * @para
 *
 * @return  none
 */
uint8_t HUB_CheckPortSpeed( uint8_t hub_port, uint8_t *pbuf )
{
    uint8_t  s;

    s = HUB_GetPortStatus( RootHubDev.bEp0MaxPks, hub_port, pbuf );
    if( s )
    {
        return s;
    }

    if( pbuf[ 1 ] & 0x02 )
    {
        return USB_LOW_SPEED;
    }
    else
    {
        if( pbuf[ 1 ] & 0x04 )
        {
            return USB_HIGH_SPEED;
        }
        else
        {
            return USB_FULL_SPEED;
        }
    }
}

/*********************************************************************
 * @fn      USBH_EnumHubPortDevice
 *
 * @brief
 *
 * @para
 *
 * @return  none
 */
uint8_t USBH_EnumHubPortDevice( uint8_t hub_port, uint8_t *paddr, uint8_t *ptype )
{
    uint8_t  s;
    uint8_t  enum_cnt;
    uint16_t len;
    uint8_t  cfg_val;
#if DEF_DEBUG_PRINTF
    uint16_t i;
#endif

    /* Get USB device descriptor */
    //DUG_PRINTF("(S1)Get DevDesc: \r\n");
    enum_cnt = 0;
    do
    {
        enum_cnt++;
        //DUG_PRINTF("Get DevDesc: ");
        uint8_t  t_DevDesc_Buf[ 48 ]; 
        // Declare variables
        uint16_t dev_desc_len = 0;            // Variable to hold the actual length of the device descriptor

        s = USBFSH_GetDeviceDescr(&RootHubDev.bEp0MaxPks, DevDesc_Buf, sizeof(DevDesc_Buf), &dev_desc_len);

        // Check if the call was successful
        if (s == ERR_SUCCESS) 
        {
            DUG_PRINTF("Device Descriptor received successfully, Length: %d\n", dev_desc_len);
            DUG_PRINTF("\r\n");

        } else {
        }

        if( s == ERR_SUCCESS )
        {
#if DEF_DEBUG_PRINTF
            for( i = 0; i < 18; i++ )
            {
                DUG_PRINTF( "%02x ", DevDesc_Buf[ i ] );
            }
            DUG_PRINTF( "\r\n" );
#endif
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
            if( enum_cnt >= 10 )
            {
                return DEF_DEV_DESCR_GETFAIL;
            }
        }
    }while( ( s != ERR_SUCCESS ) && ( enum_cnt < 10 ) );

    /* Set the USB device address */
    //DUG_PRINTF( "Set DevAddr: \r\n" );
    enum_cnt = 0;
    do
    {
        enum_cnt++;
        s = USBFSH_SetUsbAddress( RootHubDev.Device[ hub_port ].bEp0MaxPks, \
                                  RootHubDev.Device[ hub_port ].DeviceIndex + USB_DEVICE_ADDR );
        if( s == ERR_SUCCESS )
        {
            /* Save address */
            *paddr = RootHubDev.Device[ hub_port ].DeviceIndex + USB_DEVICE_ADDR;
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
            if( enum_cnt >= 10 )
            {
                return DEF_DEV_ADDR_SETFAIL;
            }
        }
    }while( ( s != ERR_SUCCESS ) && ( enum_cnt < 10 ) );
    Delay_Ms( 5 );

    /* Get USB configuration descriptor */
    //DUG_PRINTF( "Get DevCfgDesc: \r\n" );
    enum_cnt = 0;
    do
    {
        enum_cnt++;

        //uint8_t  temp_Com_Buf[ DEF_COM_BUF_LEN ]; 
        s = USBFSH_GetConfigDescr( RootHubDev.Device[ hub_port ].bEp0MaxPks, Com_Buf, DEF_COM_BUF_LEN, &len );
        
        if( s == ERR_SUCCESS )
        {
            /* Save configuration value */
            cfg_val = ( (PUSB_CFG_DESCR)Com_Buf )->bConfigurationValue;

            /* Analyze USB device type */
            USBH_AnalyseType( DevDesc_Buf, Com_Buf, ptype );

            DUG_PRINTF( "DevType: %02x\r\n", *ptype );
        }
        else
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
            if( enum_cnt >= 10 )
            {
                return DEF_DEV_DESCR_GETFAIL;
            }
        }
    }while( ( s != ERR_SUCCESS ) && ( enum_cnt < 10 ) );

    /* Set USB device configuration value */
    //DUG_PRINTF( "Set CfgValue: \r\n" );
    enum_cnt = 0;
    do
    {
        enum_cnt++;
        s = USBFSH_SetUsbConfig( RootHubDev.Device[ hub_port ].bEp0MaxPks, cfg_val );
        if( s != ERR_SUCCESS )
        {
            DUG_PRINTF( "Err(%02x)\r\n", s );
            if( enum_cnt >= 10 )
            {
                return DEF_CFG_VALUE_SETFAIL;
            }
        }
    }while( ( s != ERR_SUCCESS ) && ( enum_cnt < 10 ) );

    return( ERR_SUCCESS );
}

/*********************************************************************
 * @fn      KB_AnalyzeKeyValue
 *
 * @brief   Handle keyboard lighting.
 *
 * @para    index: USB host port
 *          intfnum: Interface number.
 *          pbuf: Data buffer.
 *          len: Data length.
 *
 * @return  The result of the analysis.
 */
void KB_AnalyzeKeyValue( uint8_t index, uint8_t intf_num, uint8_t *pbuf, uint16_t len )
{
    uint8_t  i;
    uint8_t  value;
    uint8_t  bit_pos = 0x00;

    value = HostCtl[ index ].Interface[ intf_num ].SetReport_Value;

    for( i = HostCtl[ index ].Interface[ intf_num ].LED_Usage_Min; i <= HostCtl[ index ].Interface[ intf_num ].LED_Usage_Max; i++ )
    {
        if( i == 0x01 )
        {
            if( memchr( pbuf, DEF_KEY_NUM, len ) )
            {
                HostCtl[ index ].Interface[ intf_num ].SetReport_Value ^= ( 1 << bit_pos );
            }
        }
        else if( i == 0x02 )
        {
            if( memchr( pbuf, DEF_KEY_CAPS, len ) )
            {
                HostCtl[ index ].Interface[ intf_num ].SetReport_Value ^= ( 1 << bit_pos );
            }
        }
        else if( i == 0x03 )
        {
            if( memchr( pbuf, DEF_KEY_SCROLL, len ) )
            {
                HostCtl[ index ].Interface[ intf_num ].SetReport_Value ^= ( 1 << bit_pos );
            }
        }

        bit_pos++;
    }

    if( value != HostCtl[ index ].Interface[ intf_num ].SetReport_Value )
    {
        HostCtl[ index ].Interface[ intf_num ].SetReport_Flag = 1;
    }
    else
    {
        HostCtl[ index ].Interface[ intf_num ].SetReport_Flag = 0;
    }
}

/*********************************************************************
 * @fn      KB_LED_Handle
 *
 * @brief   Handle keyboard lighting.
 *
 * @return  none
 */
void KB_LED_Handle( uint8_t index, uint8_t intf_num )
{
    if( HostCtl[ index ].Interface[ intf_num ].SetReport_Swi)
    {
#if DEF_DEBUG_PRINTF
            DUG_PRINTF( "LED status %d\r\n", KB_LED_Cur_Status );
#endif
        HostCtl[ index ].Interface[ intf_num ].SetReport_Value = scroll_lock_led ? ( KB_LED_Cur_Status | 0x04) : KB_LED_Cur_Status;
        HostCtl[ index ].Interface[ intf_num ].SetReport_Flag = 1;
        KB_SetReport( index, RootHubDev.bEp0MaxPks, intf_num );
        HostCtl[ index ].Interface[ intf_num ].SetReport_Flag = 0;
    }
}

/*********************************************************************
 * @fn      KB_SetReport
 *
 * @brief   Handle keyboard lighting.
 *
 * @para    index: USB device number.
 *          intf_num: Interface number.
 *
 * @return  The result of the handling keyboard lighting.
 */
uint8_t KB_SetReport( uint8_t index, uint8_t ep0_size, uint8_t intf_num )
{
    uint8_t  dat[ 2 ];
    uint16_t len;
    uint8_t  s = ERR_SUCCESS;

    if( HostCtl[ index ].Interface[ intf_num ].IDFlag )
    {
        dat[ 0 ] = HostCtl[ index ].Interface[ intf_num ].ReportID;
        dat[ 1 ] = HostCtl[ index ].Interface[ intf_num ].SetReport_Value;
        len = 2;
    }
    else
    {
        dat[ 0 ] = HostCtl[ index ].Interface[ intf_num ].SetReport_Value;
        len = 1;
    }

    if( HostCtl[ index ].Interface[ intf_num ].SetReport_Swi == 1 ) // Perform lighting operation through endpoint0
    {
        /* Send set report command */
        s = HID_SetReport( ep0_size, intf_num, dat, &len );
    }
    else if( HostCtl[ index ].Interface[ intf_num ].SetReport_Swi == 0xFF )  // Perform lighting operation through other endpoint
    {
        s = USBFSH_SendEndpData( HostCtl[ index ].Interface[ intf_num ].OutEndpAddr[ 0 ],
                                 &HostCtl[ index ].Interface[ intf_num ].OutEndpTog[ 0 ], dat, len);
    }

    return s;
}

/*********************************************************************
 * @fn      USBH_MainDeal
 *
 * @brief   Provide a simple enumeration process for USB devices and
 *          obtain keyboard and mouse data at regular intervals.
 *
 * @return  none
 */
void USBH_MainDeal( void )
{
    uint8_t  s;
    uint8_t  index;
    uint8_t  hub_port;
    uint8_t  hub_dat;
    uint8_t  intf_num, in_num;
    uint16_t len;
    uint16_t i;
    
    s = USBFSH_CheckRootHubPortStatus( RootHubDev.bStatus ); // Check USB device connection or disconnection
    if( s == ROOT_DEV_CONNECTED )
    {
        DUG_PRINTF( "USB Port Dev In.\r\n" );

        /* Set root device state parameters */
        RootHubDev.bStatus = ROOT_DEV_CONNECTED;
        RootHubDev.DeviceIndex = DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL;

        s = USBH_EnumRootDevice( ); // Simply enumerate root device
        if( s == ERR_SUCCESS )
        {
            if( RootHubDev.bType == USB_DEV_CLASS_HID ) // Further enumerate it if this device is a HID device
            {
                DUG_PRINTF("Root Device Is HID. ");

                s = USBH_EnumHidDevice( RootHubDev.DeviceIndex, RootHubDev.bEp0MaxPks );
                DUG_PRINTF( "Further Enum Result: " );
                if( s == ERR_SUCCESS )
                {
                    DUG_PRINTF( "OK\r\n" );

                    /* Set the connection status of the device  */
                    RootHubDev.bStatus = ROOT_DEV_SUCCESS;
                }
                else if( s != ERR_USB_DISCON )
                {
                    DUG_PRINTF( "Err(%02x)\r\n", s );
                    
                    RootHubDev.bStatus = ROOT_DEV_FAILED;
                }
            }
            else if( RootHubDev.bType == USB_DEV_CLASS_HUB )
            {
                DUG_PRINTF("Root Device Is HUB. ");

                s = USBH_EnumHubDevice( );
                DUG_PRINTF( "Further Enum Result: " );
                if( s == ERR_SUCCESS )
                {
                    DUG_PRINTF( "OK\r\n" );

                    /* Set the connection status of the device  */
                    RootHubDev.bStatus = ROOT_DEV_SUCCESS;
                }
                else if( s != ERR_USB_DISCON )
                {
                    DUG_PRINTF( "Err(%02x)\r\n", s );

                    RootHubDev.bStatus = ROOT_DEV_FAILED;
                }
            }
            else // Detect that this device is a NON-HID device
            {
                DUG_PRINTF( "Root Device Is " );
                switch( RootHubDev.bType )
                {
                    case USB_DEV_CLASS_STORAGE:
                        DUG_PRINTF("Storage. ");
                        break;
                    case USB_DEV_CLASS_PRINTER:
                        DUG_PRINTF("Printer. ");
                        break;
                    case DEF_DEV_TYPE_UNKNOWN:
                        DUG_PRINTF("Unknown. ");
                        break;
                }
                DUG_PRINTF( "End Enum.\r\n" );

                RootHubDev.bStatus = ROOT_DEV_SUCCESS;
            }
        }
        else if( s != ERR_USB_DISCON )
        {
            /* Enumeration failed */
            DUG_PRINTF( "Enum Fail with Error Code:%x\r\n",s );
            RootHubDev.bStatus = ROOT_DEV_FAILED;
        }
    }
    else if( s == ROOT_DEV_DISCONNECT )
    {
        DUG_PRINTF( "USB Port Dev Out.\r\n" );

        /* Clear parameters */
        index = RootHubDev.DeviceIndex;
        memset( &RootHubDev.bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
        memset( &HostCtl[ index ].InterfaceNum, 0, sizeof( HOST_CTL ) );
    }

    /* Get the data of the HID device connected to the USB host port */
    if( RootHubDev.bStatus >= ROOT_DEV_SUCCESS )
    {
        index = RootHubDev.DeviceIndex;

        if( RootHubDev.bType == USB_DEV_CLASS_HID )
        {
            for( intf_num = 0; intf_num < HostCtl[ index ].InterfaceNum; intf_num++ )
            {
                for( in_num = 0; in_num < HostCtl[ index ].Interface[ intf_num ].InEndpNum; in_num++ )
                {
                    /* Get endpoint data based on the interval time of the device */
                    if( HostCtl[ index ].Interface[ intf_num ].InEndpTimeCount[ in_num ] >= HostCtl[ index ].Interface[ intf_num ].InEndpInterval[ in_num ] )
                    {
                        HostCtl[ index ].Interface[ intf_num ].InEndpTimeCount[ in_num ] %= HostCtl[ index ].Interface[ intf_num ].InEndpInterval[ in_num ];

                        /* Get endpoint data */
                        s = USBFSH_GetEndpData( HostCtl[ index ].Interface[ intf_num ].InEndpAddr[ in_num ],
                                                &HostCtl[ index ].Interface[ intf_num ].InEndpTog[ in_num ], Com_Buf, &len );
                        if( s == ERR_SUCCESS )
                        {
                            for( i = 0; i < len; i++ )
                            {
#if DEF_DEBUG_PRINTF
                                DUG_PRINTF( "%02x ", Com_Buf[ i ] );
#endif
                                if( len >= report_byte )
                                //if( len >= kb_ms )
                                {
                                    if(KB_Data_State)
                                    {
                                        //if(new_descripter == 0)
                                            KB_Data_Buffer[ i ] = Com_Buf[ i ];
                                        //else
                                        //    MS_Data_Buffer[ i ] = Com_Buf[ i ];

                                        KB_Data_Buffer_Full = 1;
                                    }
                                    else
                                    {
                                        //if(new_descripter == 0)
                                            KB_Data_Pack[ i ] = Com_Buf[ i ];
                                        //else
                                        //    MS_Data_Pack[ i ] = Com_Buf[ i ];
                                        
                                        KB_Data_Pack_Full = 1;
                                    }
                                }
                            }
#if DEF_DEBUG_PRINTF
                            DUG_PRINTF( " <--\r\n" );
#endif
                        }
                        else if( s == ERR_USB_DISCON )
                        {
                            break;
                        }
                        else if( s == ( USB_PID_STALL | ERR_USB_TRANSFER ) )
                        {
                            /* USB device abnormal event */
                            DUG_PRINTF("Abnormal\r\n");

                            /* Clear endpoint */
                            USBFSH_ClearEndpStall( RootHubDev.bEp0MaxPks, HostCtl[ index ].Interface[ intf_num ].InEndpAddr[ in_num ] | 0x80 );
                            HostCtl[ index ].Interface[ intf_num ].InEndpTog[ in_num ] = 0x00;

                            /* Judge the number of error */
                            HostCtl[ index ].ErrorCount++;
                            if( HostCtl[ index ].ErrorCount >= 10 )
                            {
                                /* Re-enumerate the device and clear the endpoint again */
                                memset( &RootHubDev.bStatus, 0, sizeof( struct _ROOT_HUB_DEVICE ) );
                                s = USBH_EnumRootDevice( );
                                if( s == ERR_SUCCESS )
                                {
                                    USBFSH_ClearEndpStall( RootHubDev.bEp0MaxPks, HostCtl[ index ].Interface[ intf_num ].InEndpAddr[ in_num ] | 0x80 );
                                    HostCtl[ index ].ErrorCount = 0x00;

                                    RootHubDev.bStatus = ROOT_DEV_CONNECTED;
                                    RootHubDev.DeviceIndex = DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL;

                                    memset( &HostCtl[ index ].InterfaceNum, 0, sizeof( struct __HOST_CTL ) );
                                    s = USBH_EnumHidDevice( index, RootHubDev.bEp0MaxPks );
                                    if( s == ERR_SUCCESS )
                                    {
                                        RootHubDev.bStatus = ROOT_DEV_SUCCESS;
                                    }
                                    else if( s != ERR_USB_DISCON )
                                    {
                                        RootHubDev.bStatus = ROOT_DEV_FAILED;
                                    }
                                }
                                else if( s != ERR_USB_DISCON )
                                {
                                    RootHubDev.bStatus = ROOT_DEV_FAILED;
                                }
                            }
                        }
                        if( KB_Data_Pack_Full + KB_Data_Buffer_Full )
                        {
                            // uint8_t report[4]; // 1 byte for buttons, 1 byte for constant, 3 bytes for axes
                            // report[0] = 1; // Buttons (3 bits)
                            // report[1] = 0; // Constant data
                            // report[2] = 12; // X movement
                            // report[3] = 13; // Y movement
                            // report[4] = 10; // Wheel movement

                            if(KB_Data_State)
                            {
                                //if(new_descripter == 0)
                                    s = USBD_ENDPx_DataUp(ENDP1, KB_Data_Buffer,report_byte);
                                // else if (new_descripter == 1)
                                // {
                                //     // = Com_Buf[1] / 2;  // X movement (signed byte)
                                //     //Com_Buf[2] = Com_Buf[2] / 2;  // Y movement (signed byte)
                                //     s = USBD_ENDPx_DataUp(ENDP1, KB_Data_Buffer, 5*sizeof(uint8_t));
                                // }
                            }
                            else
                            {
                                //if(new_descripter == 0)
                                    s = USBD_ENDPx_DataUp(ENDP1, KB_Data_Buffer, report_byte);
                                // else if (new_descripter == 1)
                                // {
                                //     //Com_Buf[1] = Com_Buf[1] / 2;  // X movement (signed byte)
                                //     //Com_Buf[2] = Com_Buf[2] / 2;  // Y movement (signed byte)
                                //     s = USBD_ENDPx_DataUp(ENDP1, KB_Data_Buffer, 5*sizeof(uint8_t));
                                // }
                            }
                            int i =0;
                            // #if DEF_DEBUG_PRINTF_IMP
                            //         DUG_PRINTF("DATAAAAAAAAA 2 ..........  \r\n");
                            //         for( i = 0; i < report_byte; i++ )
                            //         {
                            //             DUG_PRINTF( "%02x ", KB_Data_Buffer[ i ] );
                            //         }
                            //         DUG_PRINTF("\r\n");
                            // #endif

                            if(s == NoREADY)
                            {
#if DEF_DEBUG_PRINTF
                                DUG_PRINTF( "Busy \r\n" );
#endif
                            }
                            else
                            {
                                if(KB_Data_State)
                                {
                                    //if(new_descripter == 0)
                                        memset( KB_Data_Buffer, 0x00, sizeof( KB_Data_Buffer ) );
                                    //else
                                        //memset( MS_Data_Buffer, 0x00, sizeof( MS_Data_Buffer ) );

                                    KB_Data_State = 0;
                                    KB_Data_Buffer_Full = 0;
                                }
                                else
                                {   
                                    //if(new_descripter == 0) 
                                        memset( KB_Data_Pack, 0x00, sizeof( KB_Data_Pack ) );
                                    //else
                                    //    memset( MS_Data_Pack, 0x00, sizeof( MS_Data_Pack ) );

                                    KB_Data_State = 1;
                                    KB_Data_Pack_Full = 0;
                                }
                            }
                        }
                    }
                }

                if( s == ERR_USB_DISCON )
                {
                    break;
                }
            }
        }
        else if( RootHubDev.bType == USB_DEV_CLASS_HUB )
        {
           /* Query port status change */
           if( HostCtl[ index ].Interface[ 0 ].InEndpTimeCount[ 0 ] >= HostCtl[ index ].Interface[ 0 ].InEndpInterval[ 0 ] )
           {
               HostCtl[ index ].Interface[ 0 ].InEndpTimeCount[ 0 ] %= HostCtl[ index ].Interface[ 0 ].InEndpInterval[ 0 ];

               /* Select HUB port */
               USBFSH_SetSelfAddr( RootHubDev.bAddress );
               USBFSH_SetSelfSpeed( RootHubDev.bSpeed );

               /* Get HUB interrupt endpoint data */
               s = USBFSH_GetEndpData( HostCtl[ index ].Interface[ 0 ].InEndpAddr[ 0 ], &HostCtl[ index ].Interface[ 0 ].InEndpTog[ 0 ], Com_Buf, &len );
               if( s == ERR_SUCCESS )
               {
                   hub_dat = Com_Buf[ 0 ];
                   DUG_PRINTF( "Hub Int Data:%02x\r\n", hub_dat );

                   for( hub_port = 0; hub_port < RootHubDev.bPortNum; hub_port++ )
                   {
                       /* HUB Port PreEnumate Step 1: C_PORT_CONNECTION */
                       s = HUB_Port_PreEnum1( ( hub_port + 1 ), &hub_dat );
                       if( s == ERR_USB_DISCON )
                       {
                           hub_dat &= ~( 1 << ( hub_port + 1 ) );

                           /* Clear parameters */
                           memset( &HostCtl[ RootHubDev.Device[ hub_port ].DeviceIndex ], 0, sizeof( HOST_CTL ) );
                           memset( &RootHubDev.Device[ hub_port ].bStatus, 0, sizeof( HUB_DEVICE ) );
                           continue;
                       }

                       /* HUB Port PreEnumate Step 2: Set/Clear PORT_RESET */
                       Delay_Ms( 100 );
                       s = HUB_Port_PreEnum2( ( hub_port + 1 ), &hub_dat );
                       if( s == ERR_USB_CONNECT )
                       {
                           /* Set parameters */
                           RootHubDev.Device[ hub_port ].bStatus = ROOT_DEV_CONNECTED;
                           RootHubDev.Device[ hub_port ].bEp0MaxPks = DEFAULT_ENDP0_SIZE;
                           RootHubDev.Device[ hub_port ].DeviceIndex = DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL + hub_port + 1;
                       }
                       else
                       {
                           hub_dat &= ~( 1 << ( hub_port + 1 ) );
                       }

                       /* Enumerate HUB Device */
                       if( RootHubDev.Device[ hub_port ].bStatus == ROOT_DEV_CONNECTED )
                       {
                        //    /* Check device speed */
                           RootHubDev.Device[ hub_port ].bSpeed = HUB_CheckPortSpeed( ( hub_port + 1 ), Com_Buf );
                           DUG_PRINTF( "Dev Speed:%x\r\n", RootHubDev.Device[ hub_port ].bSpeed );

                           /* Select the specified port */
                           USBFSH_SetSelfAddr( RootHubDev.Device[ hub_port ].bAddress );
                           USBFSH_SetSelfSpeed( RootHubDev.Device[ hub_port ].bSpeed );
                           if( RootHubDev.bSpeed != USB_LOW_SPEED )
                           {
                               USBOTG_H_FS->HOST_CTRL &= ~USBFS_UH_LOW_SPEED;
                           }

                           /* Enumerate the USB device of the current HUB port */
                           DUG_PRINTF("Enum_HubDevice\r\n");
                           s = USBH_EnumHubPortDevice( hub_port, &RootHubDev.Device[ hub_port ].bAddress, \
                                                       &RootHubDev.Device[ hub_port ].bType );
                           if( s == ERR_SUCCESS )
                           {
                               if( RootHubDev.Device[ hub_port ].bType == USB_DEV_CLASS_HID )
                               {
                                   DUG_PRINTF( "HUB port%x device is HID! Further Enum:\r\n", hub_port );

                                   /* Perform HID class enumeration on the current device */
                                   s = USBH_EnumHidDevice( RootHubDev.Device[ hub_port ].DeviceIndex, \
                                                           RootHubDev.Device[ hub_port ].bEp0MaxPks );
                                   if( s == ERR_SUCCESS )
                                   {
                                       RootHubDev.Device[ hub_port ].bStatus = ROOT_DEV_SUCCESS;
                                       DUG_PRINTF( "OK!\r\n" );
                                   }
                               }
                               else // Detect that this device is a Non-HID device
                               {
                                   DUG_PRINTF( "HUB port%x device is ", hub_port );
                                   switch( RootHubDev.Device[ hub_port ].bType )
                                   {
                                       case USB_DEV_CLASS_STORAGE:
                                           DUG_PRINTF("storage!\r\n");
                                           break;
                                       case USB_DEV_CLASS_PRINTER:
                                           DUG_PRINTF("printer!\r\n");
                                           break;
                                       case USB_DEV_CLASS_HUB:
                                           DUG_PRINTF("printer!\r\n");
                                           break;
                                       case DEF_DEV_TYPE_UNKNOWN:
                                           DUG_PRINTF("unknown!\r\n");
                                           break;
                                   }
                                   RootHubDev.Device[ hub_port ].bStatus = ROOT_DEV_SUCCESS;
                               }
                           }
                           else
                           {
                               RootHubDev.Device[ hub_port ].bStatus = ROOT_DEV_FAILED;
                               DUG_PRINTF( "HUB Port%x Enum Err!\r\n", hub_port );
                           }
                       }
                   }
               }
           }

           /* Get HUB port HID device data */
           for( hub_port = 0; hub_port < RootHubDev.bPortNum; hub_port++ )
           {
               if( RootHubDev.Device[ hub_port ].bStatus == ROOT_DEV_SUCCESS )
               {
                   index = RootHubDev.Device[ hub_port ].DeviceIndex;

                   if( RootHubDev.Device[ hub_port ].bType == USB_DEV_CLASS_HID )
                   {
                       for( intf_num = 0; intf_num < HostCtl[ index ].InterfaceNum; intf_num++ )
                       {
                           for( in_num = 0; in_num < HostCtl[ index ].Interface[ intf_num ].InEndpNum; in_num++ )
                           {
                               /* Get endpoint data based on the interval time of the device */
                               if( HostCtl[ index ].Interface[ intf_num ].InEndpTimeCount[ in_num ] >= HostCtl[ index ].Interface[ intf_num ].InEndpInterval[ in_num ] )
                               {
                                   HostCtl[ index ].Interface[ intf_num ].InEndpTimeCount[ in_num ] %= HostCtl[ index ].Interface[ intf_num ].InEndpInterval[ in_num ];

                                   /* Select HUB device port */
                                   USBFSH_SetSelfAddr( RootHubDev.Device[ hub_port ].bAddress );
                                   USBFSH_SetSelfSpeed( RootHubDev.Device[ hub_port ].bSpeed );
                                   if( RootHubDev.bSpeed != USB_LOW_SPEED )
                                   {
                                       USBOTG_H_FS->HOST_CTRL &= ~USBFS_UH_LOW_SPEED;
                                   }

                                   /* Get endpoint data */
                                   s = USBFSH_GetEndpData( HostCtl[ index ].Interface[ intf_num ].InEndpAddr[ in_num ], \
                                                           &HostCtl[ index ].Interface[ intf_num ].InEndpTog[ in_num ], Com_Buf, &len );
                                   if( s == ERR_SUCCESS )
                                   {
                                        //DUG_PRINTF("Working Test len is %d \r\n",len);

                                        //current_time = millis(); 
                                        for( i = 0; i < len; i++ )
                                        {
#if DEF_DEBUG_PRINTF
                                            DUG_PRINTF( "%02x ", Com_Buf[ i ] );
#endif
                                            if (HostCtl[index].Interface[intf_num].Type == DEC_MOUSE && len >= 3) 
                                            {
                                                // int8_t x_movement = (int8_t)Com_Buf[1];  // X movement (signed byte)
                                                // int8_t y_movement = (int8_t)Com_Buf[2];  // Y movement (signed byte)

                                                // // Determine the greater movement, x or y
                                                // int movement = ABS(x_movement) > ABS(y_movement) ? ABS(x_movement) : ABS(y_movement);

                                                // // Control LED based on movement
                                                // if (movement <= 5) 
                                                // {
                                                //     SetLEDHighForDuration(1);  // LED high for 1 ms
                                                // } 
                                                // else if (movement < 15) 
                                                // {
                                                //     SetLEDHighForDuration(2);  // LED high for 2 ms
                                                // } 
                                                // else 
                                                // {
                                                //     SetLEDHighForDuration(3);  // LED high for 3 ms
                                                // }
                                            }

                                            // lets see if its needed or not
                                            if( len >= report_byte )
                                            //if( len >= kb_ms )
                                            {
                                                if(KB_Data_State)
                                                {
                                                    //if(new_descripter == 0 )
                                                        KB_Data_Buffer[ i ] = Com_Buf[ i ];
                                                    //else
                                                    //    MS_Data_Buffer[ i ] = Com_Buf[ i ];

                                                    KB_Data_Buffer_Full = 1;
                                                }
                                                else
                                                {
                                                    //if(new_descripter == 0 )
                                                        KB_Data_Pack[ i ] = Com_Buf[ i ];
                                                    //else
                                                    //    MS_Data_Pack[ i ] = Com_Buf[ i ];

                                                    KB_Data_Pack_Full = 1;
                                                }
                                            }
                                        }
#if DEF_DEBUG_PRINTF
                                       DUG_PRINTF( " <--\r\n" );
#endif
                                   }
                                   else if( s == ERR_USB_DISCON )
                                   {
                                       break;
                                   }
                                   if( KB_Data_Pack_Full + KB_Data_Buffer_Full )
                                    {
                                        // uint8_t report[4]; // 1 byte for buttons, 1 byte for constant, 3 bytes for axes
                                        // report[0] = 1; // Buttons (3 bits)
                                        // report[1] = 0; // Constant data
                                        // report[2] = 12; // X movement
                                        // report[3] = 13; // Y movement
                                        // report[4] = 10; // Wheel movement

                                        if(KB_Data_State)
                                        {
                                            //if(new_descripter == 0)
                                                s = USBD_ENDPx_DataUp(ENDP1, KB_Data_Buffer,report_byte);
                                            // else if (new_descripter == 1)
                                            // {
                                            //     //Com_Buf[1] = Com_Buf[1] / 2;  // X movement (signed byte)
                                            //     //Com_Buf[2] = Com_Buf[2] / 2;  // Y movement (signed byte)
                                            //     s = USBD_ENDPx_DataUp(ENDP1, KB_Data_Buffer, 5*sizeof(uint8_t));
                                            // }
                                        }
                                        else
                                        {
                                            //if(new_descripter == 0)
                                                s = USBD_ENDPx_DataUp(ENDP1, KB_Data_Buffer,report_byte);
                                            //else if (new_descripter == 1)
                                            {
                                                //Com_Buf[1] = Com_Buf[1] / 2;  // X movement (signed byte)
                                                //Com_Buf[2] = Com_Buf[2] / 2;  // Y movement (signed byte)
                                                //s = USBD_ENDPx_DataUp(ENDP1, KB_Data_Buffer, 5*sizeof(uint8_t));
                                            }
                                        }
                                        int i =0;
                                        // #if DEF_DEBUG_PRINTF_IMP
                                        //         DUG_PRINTF("DATAAAAAAAAA ..........  \r\n");
                                        //         for( i = 0; i < report_byte; i++ )
                                        //         {
                                        //             DUG_PRINTF( "%02x ", KB_Data_Buffer[ i ] );
                                        //         }
                                        //         DUG_PRINTF("\r\n");
                                        // #endif

                                        if(s == NoREADY)
                                        {
#if DEF_DEBUG_PRINTF
                                            DUG_PRINTF( "Busy \r\n" );
#endif
                                        }
                                        else
                                        {
                                            if(KB_Data_State)
                                            {
                                                //if(new_descripter == 0)
                                                    memset( KB_Data_Buffer, 0x00, sizeof( KB_Data_Buffer ) );
                                                //else   
                                                //    memset( MS_Data_Buffer, 0x00, sizeof( MS_Data_Buffer ) );

                                                KB_Data_State = 0;
                                                KB_Data_Buffer_Full = 0;
                                            }
                                            else
                                            {
                                                //if(new_descripter == 0)
                                                    memset( KB_Data_Pack, 0x00, sizeof( KB_Data_Pack ) );
                                                //else
                                                //    memset( MS_Data_Pack, 0x00, sizeof( MS_Data_Pack ) );
                                                KB_Data_State = 1;
                                                KB_Data_Pack_Full = 0;
                                            }
                                        }
                                    }
                               }
                               // Inactivity logic added
                               if (HostCtl[index].Interface[intf_num].InEndpTimeCount[in_num] >= 3600000) 
                               {
                                    // TurnOffLED
                                    GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
                               }
                               else
                               {
                                    // TurnOnLED
                                    GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
                               }
                           }

                           if( s == ERR_USB_DISCON )
                           {
                               break;
                           }
                       }
                   }
               }
           }
        }
    }
}

