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
uint32_t current_time;

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */

void GPIO_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main(void)
{
    #if (INTSYSCR_INEST == INTSYSCR_INEST_NoEN)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); // Use this when nesting is disabled
    #else
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // Use this when nesting is enabled
    #endif
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init( 9600 );
    printf("SystemClk:%d\r\n",SystemCoreClock);

    //SysTick_Init();  // Initialize the SysTick timer

    /* Initialize timer for Keyboard and mouse scan timing */
    TIM3_Init( 1, SystemCoreClock / 10000 - 1 );
    printf( "Timer Init\r\n" );
    
    GPIO_INIT();

    // //GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
    // //GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
    // //Delay_Ms(2000);

    // Set_USBConfig();
    // USB_Init();
    // USB_Interrupts_Config();
    // printf( "USBD Init\r\n" );

    // while( bDeviceState != CONFIGURED )
    // {
    // }
    // printf( "USBD Ready\r\n" );

    USBFS_RCC_Init( );
    USBFS_Host_Init( ENABLE );
    memset( &RootHubDev.bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
    memset( &HostCtl[ DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL ].InterfaceNum, 0, DEF_ONE_USB_SUP_DEV_TOTAL * sizeof( HOST_CTL ) );
    printf( "Host init\r\n" );

    //current_time = millis();

    while(1)
    {
        // GPIO_WriteBit(GPIOA, GPIO_Pin_12, Bit_SET);
        // Delay_Ms(2000);
        // GPIO_WriteBit(GPIOA, GPIO_Pin_12, Bit_RESET);
        // Delay_Ms(2000);
        //if( bDeviceState == CONFIGURED )
        {
            USBH_MainDeal( );
        }
    }
}