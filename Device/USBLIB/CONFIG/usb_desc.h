/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_desc.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : This file contains all the functions prototypes for the  
 *                      USB description firmware library.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
*******************************************************************************/ 
#ifndef __USB_DESC_H
#define __USB_DESC_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "ch32v20x.h"
	 
	 
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define DEF_USBD_UEP0_SIZE          8
#define DEF_ENDP_SIZE_KB            8  // 8
#define DEF_ENDP_SIZE_MS            5  // 4  
#define DEF_USBD_MAX_PACK_SIZE      64
       
#define USBD_SIZE_DEVICE_DESC        18
#define USBD_SIZE_CONFIG_DESC        40
//#define USBD_SIZE_REPORT_DESC        54 // 54
#define USBD_SIZE_REPORT_DESC_KB     62 // 64
#define USBD_SIZE_REPORT_DESC_MS     52 // 54
#define USBD_SIZE_STRING_LANGID      4
#define USBD_SIZE_STRING_VENDOR      14
#define USBD_SIZE_STRING_PRODUCT     18
#define USBD_SIZE_STRING_SERIAL      22


#define STANDARD_ENDPOINT_DESC_SIZE             0x09

// extern uint8_t USBD_ConfigDescriptor_MS[USBD_SIZE_CONFIG_DESC];
extern uint8_t USBD_ConfigDescriptor_KB[USBD_SIZE_CONFIG_DESC];

//extern uint8_t KB_USBD_DeviceDescriptor[18];
extern uint8_t MS_USBD_DeviceDescriptor[18];
extern uint8_t USBD_KeyRepDesc[68];

//extern uint8_t USBD_MouseRepDesc[USBD_SIZE_REPORT_DESC_MS];

// extern uint8_t USBD_StringLangID[USBD_SIZE_STRING_LANGID];
// /* USB Device String Vendor */
// extern uint8_t USBD_StringVendor[USBD_SIZE_STRING_VENDOR]; 
// /* USB Device String Product */
// extern uint8_t USBD_StringProduct[USBD_SIZE_STRING_PRODUCT];
// /* USB Device String Serial */
// extern uint8_t USBD_StringSerial[USBD_SIZE_STRING_SERIAL];

// extern uint8_t USBD_KeyRepDesc[USBD_SIZE_REPORT_DESC_KB];
// extern uint8_t USBD_MouseRepDesc[USBD_SIZE_REPORT_DESC_MS];

extern uint8_t new_descripter;

#ifdef __cplusplus
}
#endif

#endif /* __USB_DESC_H */