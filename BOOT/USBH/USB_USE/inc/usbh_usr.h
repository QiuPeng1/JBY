/**
  ******************************************************************************
  * @file    usbh_usr.h
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    19-March-2012
  * @brief   This file is the header file for usb usr file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USH_USR_H__
#define __USH_USR_H__


/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "usb_conf.h"
#include <stdio.h>
#include "usbh_msc_core.h"

#define SMALL_FONT_COLUMN_WIDTH          8
#define SMALL_FONT_LINE_WIDTH            12

/*--------------- LCD Messages ---------------*/
//const uint8_t MSG_HOST_INIT[]          = "> Host Library Initialized\r\n";
//const uint8_t MSG_DEV_ATTACHED[]       = "> Device Attached\r\n";
//const uint8_t MSG_DEV_DISCONNECTED[]   = "> Device Disconnected\r\n";
//const uint8_t MSG_DEV_ENUMERATED[]     = "> Enumeration completed\r\n";
//const uint8_t MSG_DEV_HIGHSPEED[]      = "> High speed device detected\r\n";
//const uint8_t MSG_DEV_FULLSPEED[]      = "> Full speed device detected\r\n";
//const uint8_t MSG_DEV_LOWSPEED[]       = "> Low speed device detected\r\n";
//const uint8_t MSG_DEV_ERROR[]          = "> Device fault \r\n";
//const uint8_t MSG_UNREC_ERROR[]		   = "> UNRECOVERED ERROR STATE\r\n";

//const uint8_t MSG_MSC_CLASS[]          = "> Mass storage device connected\r\n";
//const uint8_t MSG_HID_CLASS[]          = "> HID device connected\r\n";

extern const uint8_t MSG_HOST_INIT[];			// "> Host Library Initialized\r\n";
extern const uint8_t MSG_DEV_ATTACHED[];		// "> Device Attached\r\n";
extern const uint8_t MSG_DEV_DISCONNECTED[];	// "> Device Disconnected\r\n";
extern const uint8_t MSG_DEV_ENUMERATED[];		// "> Enumeration completed\r\n";
extern const uint8_t MSG_DEV_HIGHSPEED[];		// "> High speed device detected\r\n";
extern const uint8_t MSG_DEV_FULLSPEED[];		// "> Full speed device detected\r\n";
extern const uint8_t MSG_DEV_LOWSPEED[];		// "> Low speed device detected\r\n";
extern const uint8_t MSG_DEV_ERROR[];			// "> Device fault \r\n";
extern const uint8_t MSG_UNREC_ERROR[]; 		// "> UNRECOVERED ERROR STATE\r\n";

extern const uint8_t MSG_MSC_CLASS[];			// "> Mass storage device connected\r\n";
extern const uint8_t MSG_HID_CLASS[];			// "> HID device connected\r\n";



/** @addtogroup USBH_USER
* @{
*/

/** @addtogroup USBH_HID_DEMO_USER_CALLBACKS
* @{
*/
  
/** @defgroup USBH_HID_USR 
  * @brief This file is the header file for user action
  * @{
  */ 


/** @defgroup USBH_CORE_Exported_Variables
  * @{
  */ 


extern  USBH_Usr_cb_TypeDef USR_HID_cb;
extern uint8_t USBH_HID_EnumDone;

/**
  * @}
  */ 


/** @defgroup USBH_CORE_Exported_FunctionsPrototype
  * @{
  */ 

void USBH_HID_USR_ApplicationSelected(void);
void USBH_HID_USR_Init(void);
void USBH_HID_USR_DeInit(void);
void USBH_HID_USR_DeviceAttached(void);
void USBH_HID_USR_ResetDevice(void);
void USBH_HID_USR_DeviceDisconnected (void);
void USBH_HID_USR_OverCurrentDetected (void);
void USBH_HID_USR_DeviceSpeedDetected(uint8_t DeviceSpeed); 
void USBH_HID_USR_Device_DescAvailable(void *);
void USBH_HID_USR_DeviceAddressAssigned(void);
void USBH_HID_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc);
void USBH_HID_USR_Manufacturer_String(void *);
void USBH_HID_USR_Product_String(void *);
void USBH_HID_USR_SerialNum_String(void *);
void USBH_HID_USR_EnumerationDone(void);
USBH_USR_Status USBH_HID_USR_UserInput(void);
void USBH_HID_USR_DeInit(void);
void USBH_HID_USR_DeviceNotSupported(void);
void USBH_HID_USR_UnrecoveredError(void);
int USBH_HID_USR_MSC_Application(void);
/**
  * @}
  */ 

#endif /* __USBH_HID_USR_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
