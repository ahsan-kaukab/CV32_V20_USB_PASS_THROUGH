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

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
// int main( void )
// {
//     /* Initialize system configuration */
//     Delay_Init( );
//     USART_Printf_Init( 9600 );
//     DUG_PRINTF( "SystemClk:%d\r\n", SystemCoreClock );
//     DUG_PRINTF( "USBFS HOST KM Test\r\n" );

//     /* Initialize TIM3 */
//     TIM3_Init( 9, SystemCoreClock / 10000 - 1 );
//     DUG_PRINTF( "TIM3 Init OK!\r\n" );

//     /* Initialize USBFS host */
// #if DEF_USBFS_PORT_EN
//     DUG_PRINTF( "USBFS Host Init\r\n" );
//     USBFS_RCC_Init( );
//     USBFS_Host_Init( ENABLE );
//     memset( &RootHubDev.bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
//     memset( &HostCtl[ DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL ].InterfaceNum, 0, sizeof( HOST_CTL ) );
// #endif

//     while( 1 )
//     {
//         USBH_MainDeal();
//     }
// }

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

    /* Initialize USBFS host */
#if DEF_USBFS_PORT_EN
    DUG_PRINTF( "USBFS Host Init\r\n" );
    USBFS_RCC_Init( );
    USBFS_Host_Init( ENABLE );
    memset( &RootHubDev.bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
    memset( &HostCtl[ DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL ].InterfaceNum, 0, sizeof( HOST_CTL ) );
#endif    /* Initialize system configuration */
    Delay_Init( );
    USART_Printf_Init( 9600 );
    DUG_PRINTF( "SystemClk:%d\r\n", SystemCoreClock );
    DUG_PRINTF( "USBFS HOST KM Test\r\n" );

    /* Initialize TIM3 */
    TIM3_Init( 9, SystemCoreClock / 10000 - 1 );
    DUG_PRINTF( "TIM3 Init OK!\r\n" );

    /* Initialize USBFS host */
#if DEF_USBFS_PORT_EN
    DUG_PRINTF( "USBFS Host Init\r\n" );
    USBFS_RCC_Init( );
    USBFS_Host_Init( ENABLE );
    memset( &RootHubDev.bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
    memset( &HostCtl[ DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL ].InterfaceNum, 0, sizeof( HOST_CTL ) );
#endif

    // Initialize USB device (USB-2)
    USBFS_Device_Init(ENABLE);
    NVIC_EnableIRQ(USBHD_IRQn);

    //int HID_report_size = 1;

    // Variable to hold HID data
    //uint8_t HID_data[HID_report_size];
    //uint8_t forward_data[HID_report_size + 1];  // +1 for data activity flag

    while (1)
    {
        // Poll USB-1 (host) to get HID data
        USBH_MainDeal();
        
        // Assuming HID_data is filled by USBH_MainDeal()
        //if (data_received_from_USB1)  // Check if new data is available
        // {
        //     // Set the data activity flag
        //     forward_data[0] = 1;  // 1 indicates activity
            
        //     // Copy HID data
        //     memcpy(&forward_data[1], HID_data, HID_report_size);

        //     // Forward data to USB-2
        //     USBFS_Device_Send(forward_data, HID_report_size + 1);
        // }
    }
}
