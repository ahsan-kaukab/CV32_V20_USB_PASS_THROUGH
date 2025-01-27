/********************************** (C) COPYRIGHT  *******************************
 * File Name          : usbhd_host_km.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2020/04/30
 * Description        : This file contains all the functions prototypes for the USB
 *                      firmware library.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
*******************************************************************************/


#ifndef __APP_KM_H
#define __APP_KM_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Header File */
#include "stdint.h"

/*******************************************************************************/
/* Macro Definition */

/* General */
#define DEF_COM_BUF_LEN                 1024                                    

/* USB HID Device Interface Type */
#define DEC_KEY                         0x01
#define DEC_MOUSE                       0x02
#define DEC_UNKNOW                      0xFF

/* USB Keyboard Lighting Key */
#define DEF_KEY_NUM                     0x53
#define DEF_KEY_CAPS                    0x39
#define DEF_KEY_SCROLL                  0x47


/*******************************************************************************/
/* Variable Declaration */
// extern uint8_t  DevDesc_Buf[];                                         
// extern uint8_t  Com_Buf[];  
//extern volatile uint32_t millis_counter;
// extern uint32_t current_time; 
                                         
/*******************************************************************************/
/* Function Declaration */
extern void TIM3_Init( uint16_t arr, uint16_t psc );
extern void USBH_AnalyseType( uint8_t *pdev_buf, uint8_t *pcfg_buf, uint8_t *ptype );
extern uint8_t USBH_EnumRootDevice( void );
extern uint8_t KM_AnalyzeConfigDesc( uint8_t index, uint8_t ep0_size );
extern void KM_AnalyzeHidReportDesc( uint8_t index, uint8_t intf_num );
extern uint8_t KM_DealHidReportDesc( uint8_t index, uint8_t ep0_size );
extern uint8_t USBH_EnumHidDevice( uint8_t index, uint8_t ep0_size );
extern uint8_t HUB_AnalyzeConfigDesc( uint8_t index );
extern uint8_t HUB_Port_PreEnum1( uint8_t hub_port, uint8_t *pbuf );
extern uint8_t HUB_Port_PreEnum2( uint8_t hub_port, uint8_t *pbuf );
extern uint8_t HUB_CheckPortSpeed( uint8_t hub_port, uint8_t *pbuf );
extern uint8_t USBH_EnumHubPortDevice( uint8_t hub_port, uint8_t *paddr, uint8_t *ptype );
extern void KB_AnalyzeKeyValue( uint8_t index, uint8_t intf_num, uint8_t *pbuf, uint16_t len );
extern uint8_t KB_SetReport( uint8_t index, uint8_t ep0_size, uint8_t intf_num );
extern void USBH_MainDeal( void );
// extern void SysTick_Init(void);
// extern uint32_t millis(void);
extern void SetLEDHighForDuration(int ms); 


#ifdef __cplusplus
}
#endif

#endif
