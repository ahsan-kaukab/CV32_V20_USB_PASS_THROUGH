/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2022/09/01
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/

/*
 * @Note
 * This example demonstrates the process of enumerating the keyboard and mouse 
 * by a USB host and obtaining data based on the polling time of the input endpoints 
 * of the keyboard and mouse. 
 * The USBFS port also supports enumeration of keyboard and mouse attached at tier
 * level 2(Hub 1).
*/

/*
 * @Note
 * The USBFS module uses the system clock as the clock source, so the SystemCoreClock can
 * only be set to 144MHz, 96MHz or 48MHz.
 */

/*******************************************************************************/
/* Header Files */
#include "usb_host_config.h"
#include "ch32v20x_usbfs_device.h"
// #include "debug.h"
// #include "usbd_compatibility_hid.h"

#define HID_REPORT_SIZE   8   // Example HID report size
#define ACTIVITY_FLAG_SIZE 1  // Size of the activity flag (1 byte)
#define BUFFER_SIZE       128 // Define buffer size for your application

//uint8_t forward_data[HID_REPORT_SIZE + ACTIVITY_FLAG_SIZE]; // Data to send on USB-2
uint8_t forward_data[HID_REPORT_SIZE]; // Data to send on USB-2

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
/*********************************************************************
 * @fn      Var_Init
 *
 * @brief   Software parameter initialisation
 *
 * @return  none
 */
void Var_Init(void)
{
    uint16_t i;
    RingBuffer_Comm.LoadPtr = 0;
    RingBuffer_Comm.StopFlag = 0;
    RingBuffer_Comm.DealPtr = 0;
    RingBuffer_Comm.RemainPack = 0;
    for(i=0; i<DEF_Ring_Buffer_Max_Blks; i++)
    {
        RingBuffer_Comm.PackLen[i] = 0;
    }
}

/* Function to process ring buffer and send data over USB-2 */
void Process_RingBuffer_To_USB2()
{
    uint8_t ret;
    
    if (RingBuffer_Comm.RemainPack > 0)
    {
        // Add activity flag (1 byte) before sending
        //forward_data[0] = 1; // Activity flag set to 1

        //DUG_PRINTF( "Hello-1 \r\n");

        // Copy data from ring buffer
        //memcpy(&forward_data[1], &Data_Buffer[(RingBuffer_Comm.DealPtr) * DEF_USBD_FS_PACK_SIZE], RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr]);
        memcpy(forward_data, &Data_Buffer[(RingBuffer_Comm.DealPtr) * DEF_USBD_FS_PACK_SIZE], RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr]);

        // Send data over USB-2
        //ret = USBFS_Endp_DataUp(DEF_UEP2, forward_data, RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr] + 1, DEF_UEP_DMA_LOAD);          
        ret = USBFS_Endp_DataUp(DEF_UEP2, forward_data, RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr], DEF_UEP_DMA_LOAD);
        
        if (ret == 0) // Transmission successful
        {
            //DUG_PRINTF( "Hello-2 \r\n");
            NVIC_DisableIRQ(USBHD_IRQn);
            RingBuffer_Comm.RemainPack--;
            RingBuffer_Comm.DealPtr++;
            if (RingBuffer_Comm.DealPtr == DEF_Ring_Buffer_Max_Blks)
            {
                RingBuffer_Comm.DealPtr = 0;
            }
            NVIC_EnableIRQ(USBHD_IRQn);
        }
    }
}

int main(void)
{
    /* Initialize system configuration */
    Delay_Init( );
    USART_Printf_Init( 9600 );
    DUG_PRINTF( "SystemClk:%d\r\n", SystemCoreClock );
    DUG_PRINTF( "USBFS HOST KM Test\r\n" );

    /* Initialize TIM3 */
    TIM3_Init( 9, SystemCoreClock / 10000 - 1 );
    DUG_PRINTF( "TIM3 Init OK!\r\n" );

    Var_Init();

    /* Initialize USBFS host */
#if DEF_USBFS_PORT_EN
    DUG_PRINTF( "USBFS Host Init\r\n" );
    USBFS_RCC_Init( );
    USBFS_Host_Init( ENABLE );
    //USBFS_Device_Init(ENABLE);
    NVIC_EnableIRQ(USBHD_IRQn);
    memset( &RootHubDev.bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
    memset( &HostCtl[ DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL ].InterfaceNum, 0, sizeof( HOST_CTL ) );
#endif    /* Initialize system configuration */

    /* Initialize RingBuffer */
    // Initialize USB device (USB-2)
    //USBFS_Device_Init(ENABLE);
    //NVIC_EnableIRQ(USBHD_IRQn);

    while (1)
    {
        // Poll USB-1 (host) to get HID data
        USBH_MainDeal();
    
        // Process data and send over USB-2
        Process_RingBuffer_To_USB2();
    }
}




