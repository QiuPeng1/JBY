/**
  ******************************************************************************
  * @file    usbh_usr.c
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    19-March-2012
  * @brief   This file includes the usb host library user callbacks
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

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "usbh_msc_usr.h"
//#include "lcd_log.h"
#include "ff.h"       /* FATFS */
//#include "usbh_msc_core.h"
//#include "usbh_msc_scsi.h"
//#include "usbh_msc_bot.h"
#include "usb_conf.h"
#include "usbh_usr.h"
uint8_t USBH_MSC_EnumDone=0;

/** @addtogroup USBH_USER
* @{
*/

/** @addtogroup USBH_MSC_DEMO_USER_CALLBACKS
* @{
*/

/** @defgroup USBH_USR 
* @brief    This file includes the usb host stack user callbacks
* @{
*/ 

/** @defgroup USBH_USR_Private_TypesDefinitions
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_Private_Defines
* @{
*/ 
#define IMAGE_BUFFER_SIZE    512
/**
* @}
*/ 


/** @defgroup USBH_USR_Private_Macros
* @{
*/ 
extern USB_OTG_CORE_HANDLE          USB_OTG_Core;
/**
* @}
*/ 


/** @defgroup USBH_USR_Private_Variables
* @{
*/
uint8_t USBH_USR_ApplicationState = USH_USR_FS_INIT;	// 全局变量，USB标志

extern FATFS fs;
extern FIL file;
//char pathname[_MAX_LFN+1];
//uint8_t line_idx = 0;   

/**
* @}
*/ 
 

/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */

USBH_Usr_cb_TypeDef USR_MSC_cb =
{
  USBH_USR_Init,
  USBH_USR_DeInit,
  USBH_USR_DeviceAttached,
  USBH_USR_ResetDevice,
  USBH_USR_DeviceDisconnected,
  USBH_USR_OverCurrentDetected,
  USBH_USR_DeviceSpeedDetected,
  USBH_USR_Device_DescAvailable,
  USBH_USR_DeviceAddressAssigned,
  USBH_USR_Configuration_DescAvailable,
  USBH_USR_Manufacturer_String,
  USBH_USR_Product_String,
  USBH_USR_SerialNum_String,
  USBH_USR_EnumerationDone,
  USBH_USR_UserInput,
  USBH_USR_MSC_Application,
  USBH_USR_DeviceNotSupported,
  USBH_USR_UnrecoveredError
    
};

/**
* @}
*/

/** @defgroup USBH_USR_Private_Constants
* @{
*/ 
/*--------------- LCD Messages ---------------*/
//const uint8_t MSG_DEV_ATTACHED[]     = ">Port2:Device Attached \n";
//const uint8_t MSG_DEV_DISCONNECTED[] = ">Port2:Device Disconnected\n";
//const uint8_t MSG_DEV_ENUMERATED[]   = ">Port2:Enumeration completed \n";
//const uint8_t MSG_DEV_HIGHSPEED[]    = ">Port2:High speed device detected\n";
//const uint8_t MSG_DEV_FULLSPEED[]    = ">Port2:Full speed device detected\n";
//const uint8_t MSG_DEV_LOWSPEED[]     = ">Port2:Low speed device detected\n";
//const uint8_t MSG_DEV_ERROR[]        = ">Port2:Device fault \n";

//const uint8_t MSG_MSC_CLASS[]        = ">Port2:Mass storage device connected\n";
//const uint8_t MSG_DISK_SIZE[]        = ">Size of the disk in MBytes: \r\n";
//const uint8_t MSG_LUN[]              = ">LUN Available in the device:\r\n";
//const uint8_t MSG_ROOT_CONT[]        = ">Exploring disk flash ...\r\n";
//const uint8_t MSG_WR_PROTECT[]       = ">The disk is write protected\r\n";
//const uint8_t MSG_MSC_UNREC_ERROR[]  = ">Port2:UNRECOVERED ERROR STATE\n";

/**
* @}
*/



/** @defgroup USBH_USR_Private_FunctionPrototypes
* @{
*/
//FRESULT Explore_Disk (char* path, uint8_t recu_level);

/**
* @}
*/ 


/** @defgroup USBH_USR_Private_Functions
* @{
*/ 


/**
* @brief  USBH_USR_Init 
*         Displays the message on LCD for host lib initialization
* @param  None
* @retval None
*/
void USBH_USR_Init(void)
{
}

/**
* @brief  USBH_USR_DeviceAttached 
*         Displays the message on LCD on device attached
* @param  None
* @retval None
*/
void USBH_USR_DeviceAttached(void)
{
//	printf((void*)MSG_DEV_ATTACHED);
}


/**
* @brief  USBH_USR_UnrecoveredError
* @param  None
* @retval None
*/
void USBH_USR_UnrecoveredError (void)
{
  
//  /* Set default screen color*/ 
//  LCD_ErrLog((void *)MSG_MSC_UNREC_ERROR); 
//	printf((void*)MSG_UNREC_ERROR);
}


/**
* @brief  USBH_DisconnectEvent
*         Device disconnect event
* @param  None
* @retval Staus
*/
void USBH_USR_DeviceDisconnected (void)
{
//  LCD_ErrLog((void *)MSG_DEV_DISCONNECTED);
//	printf((void*)MSG_DEV_DISCONNECTED);
	USBH_MSC_EnumDone = 0;
}
/**
* @brief  USBH_USR_ResetUSBDevice 
* @param  None
* @retval None
*/
void USBH_USR_ResetDevice(void)
{
  /* callback for USB-Reset */
}


/**
* @brief  USBH_USR_DeviceSpeedDetected 
*         Displays the message on LCD for device speed
* @param  Device speed
* @retval None
*/
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
	if(DeviceSpeed == HPRT0_PRTSPD_HIGH_SPEED)
	{
	//    LCD_UsrLog((void *)MSG_DEV_HIGHSPEED);
//		printf((void*)MSG_DEV_HIGHSPEED);
	}  
	else if(DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
	{
	//    LCD_UsrLog((void *)MSG_DEV_FULLSPEED);
//		printf((void*)MSG_DEV_FULLSPEED);
	}
	else if(DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
	{
	//    LCD_UsrLog((void *)MSG_DEV_LOWSPEED);
//		printf((void*)MSG_DEV_LOWSPEED);
	}
	else
	{
	//    LCD_UsrLog((void *)MSG_DEV_ERROR);
//		printf((void*)MSG_DEV_ERROR);
	}
}

/**
* @brief  USBH_USR_Device_DescAvailable 
*         Displays the message on LCD for device descriptor
* @param  device descriptor
* @retval None
*/
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{ 
//	USBH_DevDesc_TypeDef *hs;
//	hs = DeviceDesc;  

//	printf("VID : %04Xh \r\n" , (uint32_t)(*hs).idVendor);
//	printf("PID : %04Xh \r\n" , (uint32_t)(*hs).idProduct);
}

/**
* @brief  USBH_USR_DeviceAddressAssigned 
*         USB device is successfully assigned the Address 
* @param  None
* @retval None
*/
void USBH_USR_DeviceAddressAssigned(void)
{
  
}


/**
* @brief  USBH_USR_Conf_Desc 
*         Displays the message on LCD for configuration descriptor
* @param  Configuration descriptor
* @retval None
*/
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc)
{
	USBH_InterfaceDesc_TypeDef *id;

	id = itfDesc;  

	if((*id).bInterfaceClass  == 0x08)
	{
	//    LCD_UsrLog((void *)MSG_MSC_CLASS);
//		printf((void *)MSG_MSC_CLASS);
	}
	else if((*id).bInterfaceClass  == 0x03)
	{
	//    LCD_UsrLog((void *));
//		printf((void *)MSG_HID_CLASS);
	}   
}

/**
* @brief  USBH_USR_Manufacturer_String 
*         Displays the message on LCD for Manufacturer String 
* @param  Manufacturer String 
* @retval None
*/
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
//  LCD_UsrLog(">Port2:Manufacturer : %s\n", (char *)ManufacturerString);
//	printf("Manufacturer : %s \r\n", (char *)ManufacturerString);
}

/**
* @brief  USBH_USR_Product_String 
*         Displays the message on LCD for Product String
* @param  Product String
* @retval None
*/
void USBH_USR_Product_String(void *ProductString)
{
//  LCD_UsrLog(">Port2:Product : %s\n", (char *)ProductString);  
//	printf("Product : %s \r\n", (char *)ProductString);
}

/**
* @brief  USBH_USR_SerialNum_String 
*         Displays the message on LCD for SerialNum_String 
* @param  SerialNum_String 
* @retval None
*/
void USBH_USR_SerialNum_String(void *SerialNumString)
{
//  LCD_UsrLog( ">Port2:Serial Number : %s\n", (char *)SerialNumString);    
//	printf("Serial Number : %s \r\n", (char *)SerialNumString);
} 



/**
* @brief  EnumerationDone 
*         User response request is displayed to ask application jump to class
* @param  None
* @retval None
*/
void USBH_USR_EnumerationDone(void)
{ 
  /* Enumeration complete */
//  LCD_UsrLog((void *)MSG_DEV_ENUMERATED);
//	printf((void *)MSG_DEV_ENUMERATED);
//	printf("\r\n");
//	printf("To see the root content of the disk : ");
//	printf("Press Key...                       \r\n");
	USBH_MSC_EnumDone = 1; 
} 


/**
* @brief  USBH_USR_DeviceNotSupported
*         Device is not supported
* @param  None
* @retval None
*/
void USBH_USR_DeviceNotSupported(void)
{
//  LCD_UsrLog (">Port2:Device not supported : LUN >Port2:0 "); 
//	printf("> Device not supported : LUN > Port2:0. \r\n");
}  


/**
* @brief  USBH_USR_UserInput
*         User Action for application state entry
* @param  None
* @retval USBH_USR_Status : User response for key button
*/
USBH_USR_Status USBH_USR_UserInput(void)
{
	return USBH_USR_RESP_OK;
	
//	USBH_USR_Status usbh_usr_status;

//	usbh_usr_status = USBH_USR_NO_RESP;  

//	if(Button_GetState() != RESET) 	// Arduino 板子上的唤醒键，按下为高电平
//	{

//		usbh_usr_status = USBH_USR_RESP_OK;

//	}

//	return usbh_usr_status;
}  

/**
* @brief  USBH_USR_OverCurrentDetected
*         Over Current Detected on VBUS
* @param  None
* @retval Staus
*/
void USBH_USR_OverCurrentDetected (void)
{
//  LCD_ErrLog (">Port2:Overcurrent detected.");
//	printf("Overcurrent detected. \r\n");
}


/**
* @brief  USBH_USR_MSC_Application 
*         Demo application for mass storage
* @param  None
* @retval Staus
*/
int USBH_USR_MSC_Application(void)
{	
	switch(USBH_USR_ApplicationState)
	{
		case USH_USR_FS_INIT: 
		{
			/* Initialises the File System*/
			if ( f_mount(&fs, "", 1) !=  FR_OK ) 
			{
				/* fs initialisation fails*/
//				printf("> Cannot initialize File System.\r\n");
				return(-1);
			}
//			printf("> File System initialized.\r\n");
//			printf("> Disk capacity : %lu MB\r\n", ((USBH_MSC_Param.MSCapacity/1024 * (uint32_t)USBH_MSC_Param.MSPageLength) / 1024)); 

			if(USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED)
			{
//				printf((void *)MSG_WR_PROTECT);
			}

			USBH_USR_ApplicationState = USH_USR_FS_READY;
		}
		break;
		
		default: 
			break;
	}
	return(0);
}

/**
* @brief  USBH_USR_DeInit
*         Deint User state and associated variables
* @param  None
* @retval None
*/
void USBH_USR_DeInit(void)
{
	USBH_USR_ApplicationState = USH_USR_FS_INIT;
}

///**
//* @brief  Explore_Disk 
//*         Displays disk content
//* @param  path: pointer to root path
//* @retval None
//*/
//FRESULT Explore_Disk (char* path, uint8_t recu_level)
//{

//	FRESULT res;
//	FILINFO fno;
//	DIR dir;
//	char *fn;
//	char tmp[14];
//    int i;
//	uint16_t FileCount=0;

//#if _USE_LFN
//    static char lfn[_MAX_LFN + 1];   /* Buffer to store the LFN */
//    fno.lfname = lfn;
//    fno.lfsize = sizeof lfn;
//#endif

//	res = f_opendir(&dir, path);
//	if (res == FR_OK) 
//	{
//		while(HCD_IsDeviceConnected(&USB_OTG_Core)) 
//		{
//			res = f_readdir(&dir, &fno);
//			if (res != FR_OK || fno.fname[0] == 0) 
//			{
//				break;
//			}
//			if (fno.fname[0] == '.')
//			{
//				continue;
//			}
//			
//#if _USE_LFN
//            fn = *fno.lfname ? fno.lfname : fno.fname;
//#else
//            fn = fno.fname;
//#endif
//			strcpy(tmp, fn); 

//			if(recu_level == 1)
//			{
//				printf("   |__");
//			}
//			else if(recu_level == 2)
//			{
//				printf("   |   |__");
//			}
//			
//			if((fno.fattrib & AM_MASK) == AM_DIR)
//			{
//				strcat(tmp, "\r\n");
//				printf((void *)tmp);
//			}
//			else
//			{
//				strcat(tmp, "\r\n");        
//				printf((void *)tmp);
//			}

//			if(((fno.fattrib & AM_MASK) == AM_DIR)&&(recu_level == 1))
//			{
//				Explore_Disk(fn, 2);
//			}

////			if((fno.fattrib & AM_MASK) == AM_DIR) /* It is a directory */
////			{
////				sprintf(&path[i], "/%s", fn);
////				res = Explore_Disk(path,2);       //函数递归调用
////                if (res != FR_OK) break;
////				path[i] = 0;	// 结尾加结束符
////			}
////			else
////			{
////				memset(pathname,0,_MAX_LFN+1);
////				sprintf(pathname, "%s/%s",path,fn);
//// 				printf("%s\t",pathname);//	printf("%s/%s\t", path, fn);
////				printf("%lu\r\n", fno.fsize);
////				
//////				FileCount++;
////			}

//		}
////		f_closedir(&dir);
////		dir_remove(&dir);
//	}
//	
////	if(FileCount) res = FR_OK;	
//	return res;
//}

/**
* @}
*/ 

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

