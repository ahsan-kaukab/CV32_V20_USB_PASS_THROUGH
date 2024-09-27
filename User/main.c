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
#include "debug.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_prop.h"
#include "usbd_composite_km.h"
#include "usb_host_config.h"
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
// DUG_PRINTF( "Hello-1 \r\n");
/* Function to process ring buffer and send data over USB-2 */
void Process_RingBuffer_To_USB1()
{
    uint8_t ret;
    
    /* Determine if enumeration is complete, perform data transfer if completed */
    if(USBFS_DevEnumStatus)
    {
        /* Data Transfer */
        if(RingBuffer_Comm.RemainPack)
        {
            DUG_PRINTF( "Hello-1 \r\n");
            ret = USBFS_Endp_DataUp(DEF_UEP1, &Data_Buffer[(RingBuffer_Comm.DealPtr) * DEF_USBD_FS_PACK_SIZE], RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr], DEF_UEP_DMA_LOAD);
            if( ret == 0 )
            {
                DUG_PRINTF( "Hello-2 \r\n");
                NVIC_DisableIRQ(USBHD_IRQn);
                RingBuffer_Comm.RemainPack--;
                RingBuffer_Comm.DealPtr++;
                if(RingBuffer_Comm.DealPtr == DEF_Ring_Buffer_Max_Blks)
                {
                    RingBuffer_Comm.DealPtr = 0;
                }
                NVIC_EnableIRQ(USBHD_IRQn);
            }
        }

        /* Monitor whether the remaining space is available for further downloads */
        if(RingBuffer_Comm.RemainPack < (DEF_Ring_Buffer_Max_Blks - DEF_RING_BUFFER_RESTART))
        {
            if(RingBuffer_Comm.StopFlag)
            {
                NVIC_DisableIRQ(USBHD_IRQn);
                RingBuffer_Comm.StopFlag = 0;
                NVIC_EnableIRQ(USBHD_IRQn);
                USBOTG_FS->UEP1_RX_CTRL = (USBOTG_FS->UEP1_RX_CTRL & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_ACK;
            }
        }
    }
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init( 115200 );
    printf("SystemClk:%d\r\n",SystemCoreClock);

    /* Initialize timer for Keyboard and mouse scan timing */
    TIM3_Init( 1, SystemCoreClock / 10000 - 1 );
    printf( "Timer Init\r\n" );

    Set_USBConfig();
    USB_Init();
    USB_Interrupts_Config();
    printf( "USBD Init\r\n" );

    while( bDeviceState != CONFIGURED )
    {
    }
    printf( "USBD Ready\r\n" );

    USBFS_RCC_Init( );
    USBFS_Host_Init( ENABLE );
    memset( &RootHubDev.bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
    memset( &HostCtl[ DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL ].InterfaceNum, 0, DEF_ONE_USB_SUP_DEV_TOTAL * sizeof( HOST_CTL ) );
    printf( "Host init\r\n" );

    while(1)
    {
        if( bDeviceState == CONFIGURED )
        {
            USBH_MainDeal( );
        }
    }
}




