/********************************** (C) COPYRIGHT *******************************
* File Name          : usb_desc.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2022/07/15
* Description        : USB Descriptors.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"
#include "usb_desc.h"

/* USB Device Descriptors */

// keyboard 
// 12 01 10 01 00 00 00 08 3c 41 11 20 00 59 01 02 00 01 
// 1811610008606517320891201
// new one
// uint8_t KB_USBD_DeviceDescriptor[18] = { 
//     USBD_SIZE_DEVICE_DESC,           // bLength
//     0x01,                            // bDescriptorType (Device)
//     0x10, 0x01,                      // bcdUSB 2.0
//     0x01,                            // bDeviceClass (HID)
//     0x00,                            // bDeviceSubClass (Boot Interface Subclass)
//     0x00,                            // bDeviceProtocol (Keyboard Protocol)
//     DEF_USBD_UEP0_SIZE,              // bMaxPacketSize0 (Typically 64 for USB 2.0)
//     0x3c, 0x41,                      // idVendor (Example Vendor ID, replace as needed)
//     0x05, 10,                      // idProduct (Example Product ID, replace as needed)
//     0x00, 0x59,                      // bcdDevice (Device release number)
//     0x01,                            // iManufacturer (String Index)
//     0x02,                            // iProduct (String Index)
//     0x00,                            // iSerialNumber (String Index)
//     0x01                             // bNumConfigurations (1 configuration)
// };

// uint8_t KB_USBD_DeviceDescriptor[18] = { 
//     USBD_SIZE_DEVICE_DESC,           // bLength
//     0x01,                            // bDescriptorType (Device)
//     0x00, 0x02,                      // bcdUSB 2.0
//     0x01,                            // bDeviceClass (HID)
//     0x01,                            // bDeviceSubClass (Boot Interface Subclass)
//     0x01,                            // bDeviceProtocol (Keyboard Protocol)
//     DEF_USBD_UEP0_SIZE,              // bMaxPacketSize0 (Typically 64 for USB 2.0)
//     0x86, 0x1A,                      // idVendor (Example Vendor ID, replace as needed)
//     0x07, 0xFE,                      // idProduct (Example Product ID, replace as needed)
//     0x00, 0x01,                      // bcdDevice (Device release number)
//     0x01,                            // iManufacturer (String Index)
//     0x02,                            // iProduct (String Index)
//     0x00,                            // iSerialNumber (String Index)
//     0x01                             // bNumConfigurations (1 configuration)
// };


// mouse
// 12 01 00 02 00 00 00 08 61 04 51 4d 17 07 00 02 00 01  // HEX
// 18 01 00 02 00 00 00 08 97 04 81 77 23 07 00 02 00 01  // DECIMAL

// WIRELESS MOUSE
// 12 01 10 01 00 00 00 08 6d 04 42 c5 03 03 01 02 00 01  // HEX
// 1811610008109466197331201    // DECIMAL

// updated device descripter

uint8_t MS_USBD_DeviceDescriptor[18]; //= 
// { 
//     0x12,           // bLength
//     0x01,                            // bDescriptorType (Device)
//     0x00, 0x02,                      // bcdUSB 1.10
//     0x00,                            // bDeviceClass (Use class information in the Interface Descriptors)
//     0x00,                            // bDeviceSubClass 
//     0x00,                            // bDeviceProtocol 
//     0x08,              // bMaxPacketSize0 8
//     0x61, 0x04,                      // idVendor 0x1A86
//     0x51, 0x4d,                      // idProduct 0xFE07
//     0x17, 0x07,                      // bcdDevice 2.00
//     0x00,                            // iManufacturer (String Index)
//     0x02,                            // iProduct (String Index)
//     0x00,                            //  iSerialNumber (String Index)
//     0x01,                            // bNumConfigurations 1
// };

// uint8_t MS_USBD_DeviceDescriptor[18] = { 
//     USBD_SIZE_DEVICE_DESC,           // bLength
//     0x01,                            // bDescriptorType (Device)
//     0x10, 0x01,                      // bcdUSB 1.10
//     0x00,                            // bDeviceClass (Use class information in the Interface Descriptors)
//     0x00,                            // bDeviceSubClass 
//     0x00,                            // bDeviceProtocol 
//     DEF_USBD_UEP0_SIZE,              // bMaxPacketSize0 8
//     0x86, 0x1A,                      // idVendor 0x1A86
//     0x07, 0xFE,                      // idProduct 0xFE07
//     0x00, 0x01,                      // bcdDevice 2.00
//     0x01,                            // iManufacturer (String Index)
//     0x02,                            // iProduct (String Index)
//     0x00,                            //  iSerialNumber (String Index)
//     0x01,                            // bNumConfigurations 1
// };

// 09 02 19 00 01 01 02 a0 32 09 04 00 00 01 09 00 00 02 09 21 11 01 00 01 22 40 00 07 05 81 03 08 00 01 
// 09 02 54 00 01 01 00 a0 32 09 04 00 00 01 03 01 01 00 09 21 11 01 00 01 22 40 00 07 05 81 03 08 00 01
// new
// /* USB Configration Descriptors */
uint8_t  USBD_ConfigDescriptor_KB[40] = { 
     /* Configuration Descriptor */
    0x09,                           // bLength
    0x02,                           // bDescriptorType
    0x19, 0x00,   // 0x19           // lets check
    //0x19,                     // 
    //USBD_SIZE_CONFIG_DESC & 0xFF, USBD_SIZE_CONFIG_DESC >> 8, // wTotalLength
    0x01,                           // bNumInterfaces
    0x01,                           // bConfigurationValue
    0x02,  // 02                          // iConfiguration
    0xA0,                           // bmAttributes: Bus Powered; Remote Wakeup
    0x32,                           // MaxPower: 100mA

    /* Interface Descriptor */
    0x09,                           // bLength
    0x04,                           // bDescriptorType
    0x00,                           // bInterfaceNumber
    0x00,                           // bAlternateSetting
    0x01,                           // bNumEndpoints
    0x09,    // 09                      // bInterfaceClass
    0x00,                        // bInterfaceSubClass
    0x00,                           // bInterfaceProtocol: Keyboard
    0x02,                           // iInterface

    /* HID Descriptor*/
    0x09,                           // bLength
    0x21,                           // bDescriptorType
    0x11, 0x01,                     // bcdHID
    0x00,                           // bCountryCode
    0x01,                           // bNumDescriptors
    0x22,                           // bDescriptorType
    0x40, 0x00,
    //USBD_SIZE_REPORT_DESC_KB & 0xFF, USBD_SIZE_REPORT_DESC_KB >> 8, // wDescriptorLength

    /* Endpoint Descriptor*/
    0x07,                           // bLength
    0x05,                           // bDescriptorType
    0x81,                           // bEndpointAddress: IN Endpoint 1
    0x03,                           // bmAttributes
    0x08, 0x00,                           // OKK
    //DEF_ENDP_SIZE_KB & 0xFF, DEF_ENDP_SIZE_KB >> 8, // wMaxPacketSize
    0x01  // 05                          // bInterval: 5mS
};

// /* USB Configration Descriptors */
// uint8_t  USBD_ConfigDescriptor_KB[34] = { 
//      /* Configuration Descriptor */
//     0x09,                           // bLength
//     0x02,                           // bDescriptorType
//     USBD_SIZE_CONFIG_DESC & 0xFF, USBD_SIZE_CONFIG_DESC >> 8, // wTotalLength
//     0x01,                           // bNumInterfaces
//     0x01,                           // bConfigurationValue
//     0x00,                           // iConfiguration
//     0xA0,                           // bmAttributes: Bus Powered; Remote Wakeup
//     0x32,                           // MaxPower: 100mA

//     /* Interface Descriptor */
//     0x09,                           // bLength
//     0x04,                           // bDescriptorType
//     0x00,                           // bInterfaceNumber
//     0x00,                           // bAlternateSetting
//     0x01,                           // bNumEndpoints
//     0x03,                           // bInterfaceClass
//     0x01,                           // bInterfaceSubClass
//     0x01,                           // bInterfaceProtocol: Keyboard
//     0x00,                           // iInterface

//     /* HID Descriptor*/
//     0x09,                           // bLength
//     0x21,                           // bDescriptorType
//     0x11, 0x01,                     // bcdHID
//     0x00,                           // bCountryCode
//     0x01,                           // bNumDescriptors
//     0x22,                           // bDescriptorType
//     USBD_SIZE_REPORT_DESC_KB & 0xFF, USBD_SIZE_REPORT_DESC_KB >> 8, // wDescriptorLength

//     /* Endpoint Descriptor*/
//     0x07,                           // bLength
//     0x05,                           // bDescriptorType
//     0x81,                           // bEndpointAddress: IN Endpoint 1
//     0x03,                           // bmAttributes
//     DEF_ENDP_SIZE_KB & 0xFF, DEF_ENDP_SIZE_KB >> 8, // wMaxPacketSize
//     0x05                            // bInterval: 5mS
// };

// /* USB Configration Descriptors */
// uint8_t  USBD_ConfigDescriptor_MS[34] = { 
//      /* Configuration Descriptor */
//     0x09,                           // bLength
//     0x02,                           // bDescriptorType
//     USBD_SIZE_CONFIG_DESC & 0xFF, USBD_SIZE_CONFIG_DESC >> 8, // wTotalLength
//     0x01,                           // bNumInterfaces
//     0x01,                           // bConfigurationValue
//     0x00,                           // iConfiguration
//     0xA0,                           // bmAttributes: Bus Powered; Remote Wakeup
//     0x32,                           // MaxPower: 100mA

//     /* Interface Descriptor (Mouse) */
//     0x09,                           // bLength
//     0x04,                           // bDescriptorType
//     0x00,                           // bInterfaceNumber
//     0x00,                           // bAlternateSetting
//     0x01,                           // bNumEndpoints
//     0x03,                           // bInterfaceClass
//     0x01,                           // bInterfaceSubClass
//     0x02,                           // bInterfaceProtocol: Mouse
//     0x00,                           // iInterface

//     /* HID Descriptor (Mouse) */
//     0x09,                           // bLength
//     0x21,                           // bDescriptorType
//     0x11, 0x01,                     // bcdHID
//     0x00,                           // bCountryCode
//     0x01,                           // bNumDescriptors
//     0x22,                           // bDescriptorType
//    sizeof(USBD_MouseRepDesc) & 0xFF, sizeof(USBD_MouseRepDesc) >> 8,

//     /* Endpoint Descriptor (Keyboard) */
//     0x07,                           // bLength
//     0x05,                           // bDescriptorType
//     0x81,                           // bEndpointAddress: IN Endpoint 1
//     0x03,                           // bmAttributes
//     DEF_ENDP_SIZE_MS & 0xFF, DEF_ENDP_SIZE_MS >> 8, // wMaxPacketSize
//     0x05                            // bInterval: 5mS
// };

// /* USB String Descriptors */
// uint8_t USBD_StringLangID[USBD_SIZE_STRING_LANGID] = {
// 	USBD_SIZE_STRING_LANGID,
// 	USB_STRING_DESCRIPTOR_TYPE,
// 	0x09,
// 	0x04 
// };

// // /* USB Device String Vendor */
// uint8_t USBD_StringVendor[USBD_SIZE_STRING_VENDOR] = {
// 	USBD_SIZE_STRING_VENDOR,    
// 	USB_STRING_DESCRIPTOR_TYPE,           
// 	'w',0,'c',0,'h',0,'.',0,'c',0,'n',0
// };

// // /* USB Device String Product */
// uint8_t USBD_StringProduct[USBD_SIZE_STRING_PRODUCT] = {
// 	USBD_SIZE_STRING_PRODUCT,         
// 	USB_STRING_DESCRIPTOR_TYPE,        
//     'C', 0, 'H', 0, '3', 0, '2', 0, 'F', 0, '2', 0 , '0', 0, 'x', 0
// };

// // /* USB Device String Serial */
// uint8_t USBD_StringSerial[USBD_SIZE_STRING_SERIAL] = {
// 	USBD_SIZE_STRING_SERIAL,          
// 	USB_STRING_DESCRIPTOR_TYPE,                   
// 	'0', 0, '1', 0, '2', 0, '3', 0, '4', 0, '5', 0 , '6', 0, '7', 0, '8', 0, '9', 0
// };

// 05 01 09 06 a1 01 05 07 19 e0 29 e7 15 00 25 01 75 01 95 08 81 02 95 01 
// 75 08 81 01 95 05 75 01 05 08 19 01 29 05 91 02 95 01 75 03 91 01 95 06 75 08 26 ff 00 05 07 19 00 29 91 81 00 c0 

// new
uint8_t USBD_KeyRepDesc[68]; //=
// {
//     0x05, 0x01,                     // Usage Page (Generic Desktop)
//     0x09, 0x06,                     // Usage (Keyboard)
//     0xA1, 0x01,                     // Collection (Application)
//     0x05, 0x07,                     // Usage Page (Key Codes)
//     0x19, 0xE0,                     // Usage Minimum (224)
//     0x29, 0xE7,                     // Usage Maximum (231)
//     0x15, 0x00,                     // Logical Minimum (0)
//     0x25, 0x01,                     // Logical Maximum (1)
//     0x75, 0x01,                     // Report Size (1)
//     0x95, 0x08,                     // Report Count (8)
//     0x81, 0x02,                     // Input (Data,Variable,Absolute)
//     0x95, 0x01,                     // Report Count (1)
//     0x75, 0x08,                     // Report Size (8)
//     0x81, 0x01,                     // Input (Constant)
//     0x95, 0x05,                     // Report Count (5)
//     0x75, 0x01,                     // Report Size (1)
//     0x05, 0x08,                     // Usage Page (LEDs)
//     0x19, 0x01,                     // Usage Minimum (1)
//     0x29, 0x05,                     // Usage Maximum (5)
//     0x91, 0x02,                     // Output (Data,Variable,Absolute)
//     0x95, 0x01,                    // Report Count (1)
//     0x75, 0x03,                     // Report Size (3)
//     0x91, 0x01,                     // Output (Constant,Array,Absolute)
//     0x95, 0x06,                    // Report Count (6)
//     0x75, 0x08,                     // Report Size (8)
//     //0x15, 0x00,                     // Logical Minimum (0)
//     0x26, 0xff, 0x00,               // Logical Maximum (255)
//     0x05, 0x07,                     // Usage Page (Key Codes)
//     0x19, 0x00,                     // Usage Minimum (0)
//     0x29, 0x91,
//     //0x2a, 0xff, 0x00,               // Usage Maximum (255)
//     0x81, 0x00,                     // Input (Data,Array,Absolute)
//     0xC0 
// };

// uint8_t USBD_KeyRepDesc[USBD_SIZE_REPORT_DESC_KB] =
// {
//     0x05, 0x01,                     // Usage Page (Generic Desktop)
//     0x09, 0x06,                     // Usage (Keyboard)
//     0xA1, 0x01,                     // Collection (Application)
//     0x05, 0x07,                     // Usage Page (Key Codes)
//     0x19, 0xE0,                     // Usage Minimum (224)
//     0x29, 0xE7,                     // Usage Maximum (231)
//     0x15, 0x00,                     // Logical Minimum (0)
//     0x25, 0x01,                     // Logical Maximum (1)
//     0x75, 0x01,                     // Report Size (1)
//     0x95, 0x08,                     // Report Count (8)
//     0x81, 0x02,                     // Input (Data,Variable,Absolute)
//     0x95, 0x01,                     // Report Count (1)
//     0x75, 0x08,                     // Report Size (8)
//     0x81, 0x01,                     // Input (Constant)
//     0x95, 0x03,                     // Report Count (3)
//     0x75, 0x01,                     // Report Size (1)
//     0x05, 0x08,                     // Usage Page (LEDs)
//     0x19, 0x01,                     // Usage Minimum (1)
//     0x29, 0x03,                     // Usage Maximum (3)
//     0x91, 0x02,                     // Output (Data,Variable,Absolute)
//     0x95, 0x05,                     // Report Count (5)
//     0x75, 0x01,                     // Report Size (1)
//     0x91, 0x01,                     // Output (Constant,Array,Absolute)
//     0x95, 0x06,                     // Report Count (6)
//     0x75, 0x08,                     // Report Size (8)
//     0x26, 0xFF, 0x00,               // Logical Maximum (255)
//     0x05, 0x07,                     // Usage Page (Key Codes)
//     0x19, 0x00,                     // Usage Minimum (0)
//     0x29, 0x91,                     // Usage Maximum (145)
//     0x81, 0x00,                     // Input(Data,Array,Absolute)
//     0xC0                            // End Collection
// };

// // /* HID Report Descriptor */
// uint8_t USBD_MouseRepDesc[] =
// {
//     0x05, 0x01,                     // Usage Page (Generic Desktop)
//     0x09, 0x02,                     // Usage (Mouse)
//     0xA1, 0x01,                     // Collection (Application)
    
//     0x09, 0x01,                     // Usage (Pointer)
//     0xA1, 0x00,                     // Collection (Physical)
    
//     // Button States
//     0x05, 0x09,                     // Usage Page (Button)
//     0x19, 0x01,                     // Usage Minimum (Button 1)
//     0x29, 0x06,                     // Usage Maximum (Button 5, adjust if you have more)
//     0x15, 0x00,                     // Logical Minimum (0)
//     0x25, 0x01,                     // Logical Maximum (1)
//     0x75, 0x01,                     // Report Size (1)
//     0x95, 0x06,                     // Report Count (5) - total number of buttons
//     0x81, 0x02,                     // Input (Data, Variable, Absolute)
    
//     // Padding for alignment
//     0x75, 0x03,                     // Report Size (3)
//     0x95, 0x01,                     // Report Count (1)
//     0x81, 0x01,                     // Input (Constant, Array, Absolute)
    
//     // Movement Data
//     0x05, 0x01,                     // Usage Page (Generic Desktop)
//     0x09, 0x30,                     // Usage (X)
//     0x09, 0x31,                     // Usage (Y)
//     0x09, 0x38,                     // Usage (Wheel)
    
//     // Scroll Wheel Data
//     0x15, 0x81,                     // Logical Minimum (-127)
//     0x25, 0x7F,                     // Logical Maximum (127)
//     0x75, 0x08,                     // Report Size (8)
//     0x95, 0x03,                     // Report Count (3) - X, Y, and Wheel
//     0x81, 0x06,                     // Input (Data, Variable, Relative)

//     0xC0,                           // End Collection
//     0xC0                            // End Collection
// };