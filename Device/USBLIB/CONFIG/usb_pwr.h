/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_pwr.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : Connection/disconnection & power management header 
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
*******************************************************************************/ 
#ifndef __USB_PWR_H
#define __USB_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "ch32v20x.h"
typedef enum _RESUME_STATE
{
  RESUME_EXTERNAL,
  RESUME_INTERNAL,
  RESUME_LATER,
  RESUME_WAIT,
  RESUME_START,
  RESUME_ON,
  RESUME_OFF,
  RESUME_ESOF
} RESUME_STATE;

typedef enum _DEVICE_STATE
{
  UNCONNECTED,
  ATTACHED,
  POWERED,
  SUSPENDED,
  ADDRESSED,
  CONFIGURED
} DEVICE_STATE;


void Suspend(void);
void Resume_Init(void);
void Resume(RESUME_STATE eResumeSetVal);
RESULT PowerOn(void);
RESULT PowerOff(void);

extern  __IO uint32_t bDeviceState; /* USB device status */
extern __IO bool fSuspendEnabled;  /* true when suspend is possible */

#ifdef __cplusplus
}
#endif

#endif  /*__USB_PWR_H*/






