/**
  ******************************************************************************
  * @file    usbh_usr.c
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    19-March-2012
  * @brief   This file includes the user application layer
  *			BY:	JOY
  *			Arduino板子按钮按下后，可以使用键盘输入，在串口2输出
  *			支持识别部分鼠标
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
//#include "lcd_log.h"
#include "usbh_usr.h"
#include <stdio.h>


uint8_t USBH_HID_EnumDone=0;

/** @addtogroup USBH_USER
* @{
*/

/** @addtogroup USBH_HID_DEMO_USER_CALLBACKS
* @{
*/

/** @defgroup USBH_HID_USR
* @brief This file is the Header file for usbh_usr.c
* @{
*/ 


/** @defgroup USBH_CORE_Exported_TypesDefinitions
* @{
*/ 
#define KYBRD_FIRST_COLUMN               (uint16_t)319
#define KYBRD_LAST_COLUMN                (uint16_t)7
#define KYBRD_FIRST_LINE                 (uint8_t)120
#define KYBRD_LAST_LINE                  (uint8_t)200


/**
* @}
*/ 
uint8_t  KeybrdCharXpos           = 0;
uint16_t KeybrdCharYpos           = 0;
int16_t  x_loc  = 0, y_loc  = 0; 
int16_t  prev_x = 0, prev_y = 0;
//extern  int16_t  x_loc, y_loc; 
//extern __IO int16_t  prev_x, prev_y;

/** @addtogroup USER
* @{
*/

/** @defgroup USBH_HID_USR 
* @brief    This file includes the user application layer
* @{
*/ 

/** @defgroup USBH_CORE_Exported_Types
* @{
*/ 



/** @defgroup USBH_HID_USR_Private_Defines
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_HID_USR_Private_Macros
* @{
*/ 
/**
* @}
*/ 

/** @defgroup USBH_HID_USR_Private_Variables
* @{
*/
extern USB_OTG_CORE_HANDLE           USB_OTG_Core_dev;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */

USBH_Usr_cb_TypeDef USR_HID_cb =
{
  USBH_HID_USR_Init,
  USBH_HID_USR_DeInit,
  USBH_HID_USR_DeviceAttached,
  USBH_HID_USR_ResetDevice,
  USBH_HID_USR_DeviceDisconnected,
  USBH_HID_USR_OverCurrentDetected,
  USBH_HID_USR_DeviceSpeedDetected,
  USBH_HID_USR_Device_DescAvailable,
  USBH_HID_USR_DeviceAddressAssigned,
  USBH_HID_USR_Configuration_DescAvailable,
  USBH_HID_USR_Manufacturer_String,
  USBH_HID_USR_Product_String,
  USBH_HID_USR_SerialNum_String,
  USBH_HID_USR_EnumerationDone,
  USBH_HID_USR_UserInput,
  NULL,
  USBH_HID_USR_DeviceNotSupported,
  USBH_HID_USR_UnrecoveredError
};

/**
* @}
*/

/** @defgroup USBH_HID_USR_Private_Constants
* @{
*/ 
/*--------------- LCD Messages ---------------*/
//const uint8_t MSG_HOST_INIT[]          = "> Host Library Initialized\r\n";
//const uint8_t MSG_DEV_ATTACHED[]       = "> Device Attached\r\n";
//const uint8_t MSG_DEV_DISCONNECTED[]   = "> Device Disconnected\r\n";
//const uint8_t MSG_DEV_ENUMERATED[]     = "> Enumeration completed\r\n";
//const uint8_t MSG_DEV_HIGHSPEED[]      = "> High speed device detected\r\n";
//const uint8_t MSG_DEV_FULLSPEED[]      = "> Full speed device detected\r\n";
//const uint8_t MSG_DEV_LOWSPEED[]       = "> Low speed device detected\r\n";
//const uint8_t MSG_DEV_ERROR[]          = "> Device fault \r\n";
//const uint8_t MSG_UNREC_ERROR[]        = "> UNRECOVERED ERROR STATE\r\n";

//const uint8_t MSG_MSC_CLASS[]          = "> Mass storage device connected\r\n";
//const uint8_t MSG_HID_CLASS[]          = "> HID device connected\r\n";

//const uint8_t USB_HID_MouseStatus[]    = "> HID Demo Device : Mouse\r\n";
//const uint8_t USB_HID_KeybrdStatus[]   = "> HID Demo Device : Keyboard\r\n";
/**
* @}
*/



/** @defgroup USBH_HID_USR_Private_FunctionPrototypes
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_HID_USR_Private_Functions
* @{
*/ 
void HID_MOUSE_UpdatePosition (int8_t x, int8_t y);
void HID_MOUSE_ButtonPressed(uint8_t button_idx);
void HID_MOUSE_ButtonReleased(uint8_t button_idx);
/**
* @}
*/




/**
* @brief  USBH_HID_USR_Init 
*         Displays the message on LCD for host lib initialization
* @param  None
* @retval None
*/
void USBH_HID_USR_Init(void)
{
}

/**
* @brief  USBH_HID_USR_DeviceAttached 
*         Displays the message on LCD on device attached
* @param  None
* @retval None
*/
void USBH_HID_USR_DeviceAttached(void)
{  
//  LCD_UsrLog ((void*)MSG_DEV_ATTACHED);
//	printf((void*)MSG_DEV_ATTACHED);

}

/**
* @brief  USBH_HID_USR_UnrecoveredError
* @param  None
* @retval None
*/
void USBH_HID_USR_UnrecoveredError (void)
{
//  LCD_ErrLog((void*)MSG_UNREC_ERROR);
//	printf((void*)MSG_UNREC_ERROR);
}

/**
* @brief  USBH_DisconnectEvent
*         Device disconnect event
* @param  None
* @retval None
*/
void USBH_HID_USR_DeviceDisconnected (void)
{
  
//  LCD_SetBackColor(Black); 
//  LCD_SetTextColor(Black);   
//  
//  LCD_LOG_ClearTextZone();

//  LCD_DrawRect(MOUSE_WINDOW_X,
//               MOUSE_WINDOW_Y, 
//               MOUSE_WINDOW_HEIGHT,
//               MOUSE_WINDOW_WIDTH);
//  LCD_SetTextColor(White);    
//  
//  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 42, "                                   ");
//  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 30, "                                   ");  
//  
//  LCD_ErrLog((void *)MSG_DEV_DISCONNECTED);
//	printf((void*)MSG_DEV_DISCONNECTED);
	USBH_HID_EnumDone = 0;

}

/**
* @brief  USBH_HID_USR_ResetUSBDevice 
*         Reset USB Device
* @param  None
* @retval None
*/
void USBH_HID_USR_ResetDevice(void)
{
  /* Users can do their application actions here for the USB-Reset */
}


/**
* @brief  USBH_HID_USR_DeviceSpeedDetected 
*         Displays the message on LCD for device speed
* @param  Devicespeed : Device Speed
* @retval None
*/
void USBH_HID_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
  if(DeviceSpeed == HPRT0_PRTSPD_HIGH_SPEED)
  {
//    LCD_UsrLog((void *)MSG_DEV_HIGHSPEED);
//	  printf((void*)MSG_DEV_HIGHSPEED);
  }  
  else if(DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
  {
//    LCD_UsrLog((void *)MSG_DEV_FULLSPEED);
//	  printf((void*)MSG_DEV_FULLSPEED);
  }
  else if(DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
  {
//    LCD_UsrLog((void *)MSG_DEV_LOWSPEED);
//	  printf((void*)MSG_DEV_LOWSPEED);
  }
  else
  {
//    LCD_UsrLog((void *)MSG_DEV_ERROR);
//	  printf((void*)MSG_DEV_ERROR);
  }
}

/**
* @brief  USBH_HID_USR_Device_DescAvailable 
*         Displays the message on LCD for device descriptor
* @param  DeviceDesc : device descriptor
* @retval None
*/
void USBH_HID_USR_Device_DescAvailable(void *DeviceDesc)
{
//  uint8_t temp[50];    
//  USBH_DevDesc_TypeDef *hs;
//  hs = DeviceDesc;  
//  
  
//  sprintf((char *)temp , "VID : %04Xh\n" , (uint32_t)(*hs).idVendor); 
//  LCD_UsrLog((void *)temp);
//	printf("VID : %04Xh \r\n" , (uint32_t)(*hs).idVendor);
  
  
//  sprintf((char *)temp , "PID : %04Xh\n" , (uint32_t)(*hs).idProduct); 
//  LCD_UsrLog((void *)temp);
//	printf("PID : %04Xh \r\n" , (uint32_t)(*hs).idProduct);
}

/**
* @brief  USBH_HID_USR_DeviceAddressAssigned 
*         USB device is successfully assigned the Address 
* @param  None
* @retval None
*/
void USBH_HID_USR_DeviceAddressAssigned(void)
{
  
}


/**
* @brief  USBH_HID_USR_Conf_Desc 
*         Displays the message on LCD for configuration descriptor
* @param  ConfDesc : Configuration descriptor
* @retval None
*/
void USBH_HID_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc)
{
  USBH_InterfaceDesc_TypeDef *id;
  
  id = itfDesc;  
  
  if((*id).bInterfaceClass  == 0x08)
  {
//    LCD_UsrLog((void *)MSG_MSC_CLASS);
//	  printf((void *)MSG_MSC_CLASS);
  }
  else if((*id).bInterfaceClass  == 0x03)
  {
//    LCD_UsrLog((void *));
//	  printf((void *)MSG_HID_CLASS);
  }   
}

/**
* @brief  USBH_HID_USR_Manufacturer_String 
*         Displays the message on LCD for Manufacturer String 
* @param  ManufacturerString : Manufacturer String of Device
* @retval None
*/
void USBH_HID_USR_Manufacturer_String(void *ManufacturerString)
{
//  char temp[100];
//  sprintf(temp, "Manufacturer : %s\n", (char *)ManufacturerString);
//  LCD_UsrLog((void *)temp);
 // printf("Manufacturer : %s \r\n", (char *)ManufacturerString);
}

/**
* @brief  USBH_HID_USR_Product_String 
*         Displays the message on LCD for Product String
* @param  ProductString : Product String of Device
* @retval None
*/
void USBH_HID_USR_Product_String(void *ProductString)
{
//  char temp[100];
//  sprintf((char *)temp, "Product : %s\n", (char *)ProductString);  
//  LCD_UsrLog((void *)temp);
//	printf("Product : %s \r\n", (char *)ProductString);
  
}

/**
* @brief  USBH_HID_USR_SerialNum_String 
*         Displays the message on LCD for SerialNum_String 
* @param  SerialNumString : SerialNum_String of device
* @retval None
*/
void USBH_HID_USR_SerialNum_String(void *SerialNumString)
{
//  uint8_t temp[100];
//  sprintf((char *)temp, "Serial Number : %s\n", (char *)SerialNumString);    
//  LCD_UsrLog((void *)temp);
//	printf("Serial Number : %s \r\n", (char *)SerialNumString);
} 

/**
* @brief  EnumerationDone 
*         User response request is displayed to ask for
*         application jump to class
* @param  None
* @retval None
*/
void USBH_HID_USR_EnumerationDone(void)
{
  /* Enumeration complete */
//  LCD_UsrLog((void *)MSG_DEV_ENUMERATED);
//  LCD_SetTextColor(Green);
//  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 42, "To start the HID class operations: " );
//  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 30, "Press Key...                       ");
//  LCD_SetTextColor(LCD_LOG_DEFAULT_COLOR);   
//	printf((void *)MSG_DEV_ENUMERATED);
//	printf("\r\n");
//	printf("To start the HID class operations: \r\n");
//	printf("Press Key...                       \r\n");
	USBH_HID_EnumDone = 1;
} 

/**
* @brief  USBH_HID_USR_DeviceNotSupported
*         Device is not supported
* @param  None
* @retval None
*/
void USBH_HID_USR_DeviceNotSupported(void)
{
//  LCD_UsrLog ("> Device not supported.\r\n");              
//	printf("> Device not supported. \r\n");
}  


/**
* @brief  USBH_HID_USR_UserInput
*         User Action for application state entry
* @param  None
* @retval USBH_HID_USR_Status : User response for key button
*/
USBH_USR_Status USBH_HID_USR_UserInput(void)
{
  return USBH_USR_RESP_OK;  
//  USBH_USR_Status usbh_usr_status;
//  
//  usbh_usr_status = USBH_USR_NO_RESP;  
//  
//  /*Key B3 is in polling mode to detect user action */
////  if(Button_GetState() == RESET) 
//	if(Button_GetState() != RESET) 	// Arduino 板子上的唤醒键，按下为高电平
//	{

//		usbh_usr_status = USBH_USR_RESP_OK;

//	}
//  
//  return usbh_usr_status;
  
} 

/**
* @brief  USBH_HID_USR_OverCurrentDetected
*         Device Overcurrent detection event
* @param  None
* @retval None
*/
void USBH_HID_USR_OverCurrentDetected (void)
{
//   LCD_ErrLog ("Overcurrent detected.\r\n");
//	printf("Overcurrent detected. \r\n");
}

/**
* @brief  USR_MOUSE_Init
*         Init Mouse window
* @param  None
* @retval None
*/
void USR_MOUSE_Init	(void)
{
////  LCD_UsrLog((void*)USB_HID_MouseStatus); 
////  LCD_UsrLog("\n\n\n\n\n\n\n\n");
////  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 42, "                                   ");
////  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 30, "                                   ");
////    
////  /* Display Mouse Window */
////  LCD_DrawRect(MOUSE_WINDOW_X,
////               MOUSE_WINDOW_Y, 
////               MOUSE_WINDOW_HEIGHT,
////               MOUSE_WINDOW_WIDTH);
////  
//	HID_MOUSE_ButtonReleased(0);
//	HID_MOUSE_ButtonReleased(1);
//	HID_MOUSE_ButtonReleased(2);
////  

////  LCD_SetTextColor(LCD_COLOR_GREEN);
////  LCD_SetBackColor(LCD_COLOR_BLACK);
////  
////  LCD_DisplayChar(MOUSE_WINDOW_X + 1,
////                            MOUSE_WINDOW_Y - 1,
////                            'x');
//	x_loc  = 0;
//	y_loc  = 0; 
//	prev_x = 0;
//	prev_y = 0;


//	printf((void*)USB_HID_MouseStatus);
// 	printf("\r\n");
//  
}

/**
* @brief  USR_MOUSE_ProcessData
*         Process Mouse data
* @param  data : Mouse data to be displayed
* @retval None
*/
//void USR_MOUSE_ProcessData(HID_MOUSE_Data_TypeDef *data)
//{
//  
//	uint8_t idx = 1;   
//	static uint8_t b_state[3] = {0, 0, 0};

////	LEDOn(LED3);
//	if ((data->x != 0) && (data->y != 0))
//	{
//		HID_MOUSE_UpdatePosition(data->x , data->y);
//	}

//	for ( idx = 0 ; idx < 3 ; idx ++)
//	{

//		if(data->button & 1 << idx) 
//		{
//			if(b_state[idx] == 0)
//			{
//				HID_MOUSE_ButtonPressed (idx);
//				b_state[idx] = 1;
//			}
//		}
//		else
//		{
//			if(b_state[idx] == 1)
//			{
//				HID_MOUSE_ButtonReleased (idx);
//				b_state[idx] = 0;
//			}
//		}
//	}
////	LEDOff(LED3);

//}

/**
* @brief  USR_KEYBRD_Init
*         Init Keyboard window
* @param  None
* @retval None
*/
//void  USR_KEYBRD_Init (void)
//{

////  LCD_UsrLog((void*)USB_HID_KeybrdStatus); 
////  LCD_UsrLog("> Use Keyboard to tape characters: \n\n");   
////  LCD_UsrLog("\n\n\n\n\n\n");
////  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 42, "                                   ");
////  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 30, "                                   ");  
////    
////  LCD_SetTextColor(Green);

//	printf((void*)USB_HID_KeybrdStatus); 
//	printf("> Use Keyboard to tape characters: \r\n");
//	printf("\r\n\r\n");
//	
//	KeybrdCharXpos = KYBRD_FIRST_LINE;
//	KeybrdCharYpos = KYBRD_FIRST_COLUMN;
//}


/**
* @brief  USR_KEYBRD_ProcessData
*         Process Keyboard data
* @param  data : Keyboard data to be displayed
* @retval None
*/
//void  USR_KEYBRD_ProcessData (uint8_t data)
//{
////	LEDOn(LED2);
//  
//	if(data == '\n')
//	{
//	//    KeybrdCharYpos = KYBRD_FIRST_COLUMN;
//	//    
//	//    /*Increment char X position*/
//	//    KeybrdCharXpos+=SMALL_FONT_LINE_WIDTH;
//		printf("\r\n");
//	}
//	else if (data == '\r')	// 退格键
//	{
//	/* Manage deletion of charactter and upadte cursor location*/
//	//    if( KeybrdCharYpos == KYBRD_FIRST_COLUMN) 
//	//    {
//	//      /*First character of first line to be deleted*/
//	//      if(KeybrdCharXpos == KYBRD_FIRST_LINE)
//	//      {  
//	//        KeybrdCharYpos =KYBRD_FIRST_COLUMN; 
//	//      }
//	//      else
//	//      {
//	//        KeybrdCharXpos-=SMALL_FONT_LINE_WIDTH;
//	//        KeybrdCharYpos =(KYBRD_LAST_COLUMN+SMALL_FONT_COLUMN_WIDTH); 
//	//      }
//	//    }
//	//    else
//	//    {
//	//      KeybrdCharYpos +=SMALL_FONT_COLUMN_WIDTH;                  
//	//      
//	//    } 
//	//    LCD_DisplayChar(KeybrdCharXpos,KeybrdCharYpos, ' '); 
//		printf("\r");
//	}
//	else
//	{
//		//    LCD_DisplayChar(KeybrdCharXpos,KeybrdCharYpos, data);    
//		printf("%c", (data));
//		/* Update the cursor position on LCD */

////		/*Increment char Y position*/
////		KeybrdCharYpos -=SMALL_FONT_COLUMN_WIDTH;

////		/*Check if the Y position has reached the last column*/
////		if(KeybrdCharYpos == KYBRD_LAST_COLUMN)
////		{
////			KeybrdCharYpos = KYBRD_FIRST_COLUMN;

////			/*Increment char X position*/
////			KeybrdCharXpos+=SMALL_FONT_LINE_WIDTH;
////		}
//	}
//	DelayMs(100);
////	LEDOff(LED2);
//}

/**
* @brief  USBH_HID_USR_DeInit
*         Deint User state and associated variables
* @param  None
* @retval None
*/
void USBH_HID_USR_DeInit(void)
{
}

///////////////////////////////////////////////////////////////////////////////////
#define MOUSE_WINDOW_HEIGHT             90
#define MOUSE_WINDOW_WIDTH              128

/**
* @brief  HID_MOUSE_UpdatePosition
*         The function is to handle mouse scroll to upadte the mouse position 
*         on display window
* @param   x : USB HID Mouse X co-ordinate
* @param   y :  USB HID Mouse Y co-ordinate
* @retval None
*/
//void HID_MOUSE_UpdatePosition (int8_t x, int8_t y)
//{
////   /* Set the color for button press status */
////  LCD_SetTextColor(LCD_COLOR_GREEN);
////  LCD_SetBackColor(LCD_COLOR_BLACK);
//	if ((x != 0) || (y != 0)) 
//	{
//		x_loc += x/2;
//		y_loc += y/2;

//		if(y_loc > MOUSE_WINDOW_HEIGHT - 12)
//		{
//			y_loc = MOUSE_WINDOW_HEIGHT - 12;
//		}  
//		if(x_loc > MOUSE_WINDOW_WIDTH - 10)
//		{
//			x_loc = MOUSE_WINDOW_WIDTH - 10;
//		}    
//		if(y_loc < 2)
//		{
//			y_loc = 2;
//		}  
//		if(x_loc < 2)
//		{
//			x_loc = 2;
//		} 

//		if ((prev_x != 0) && (prev_y != 0))
//		{
////			LCD_DisplayChar(MOUSE_WINDOW_X + prev_y ,\
////			MOUSE_WINDOW_Y - prev_x, ' ');
//		}
//		else if((prev_x == 0) && ( prev_y == 0))
//		{
////			LCD_DisplayChar(MOUSE_WINDOW_X + 1,
////								MOUSE_WINDOW_Y - 1,
////								' ');    
//		}

////		LCD_DisplayChar  (MOUSE_WINDOW_X + y_loc ,\
////		MOUSE_WINDOW_Y - x_loc, 'x');
//		printf("Mouse position: x=%d, y=%d\r\n", x, y);

//		prev_x = x_loc;
//		prev_y = y_loc;
//	}
//}  

/**
* @brief  HID_MOUSE_ButtonPressed
*         The function is to handle mouse button press
* @param  button_idx : mouse button pressed
* @retval None
*/
//void HID_MOUSE_ButtonPressed(uint8_t button_idx)
//{
//  
////	/* Set the color for button press status */
////	LCD_SetTextColor(LCD_COLOR_GREEN);
////	LCD_SetBackColor(LCD_COLOR_GREEN);

//	/* Change the color of button pressed to indicate button press*/
//	switch (button_idx)
//	{
//		/* Left Button Pressed */
//		case 0 :
////			LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD, HID_MOUSE_BUTTON1_YCHORD,\
////			HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT );
//			printf("Mouse Action: Left Button Pressed.\r\n");
//			break;

//		/* Right Button Pressed */  
//		case 1 :
////			LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD,HID_MOUSE_BUTTON2_YCHORD,\
////			HID_MOUSE_BUTTON_WIDTH,HID_MOUSE_BUTTON_HEIGHT);
//			printf("Mouse Action: Right Button Pressed.\r\n");
//			break; 

//		/* Middle button Pressed */  
//		case 2 :
////			LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD,HID_MOUSE_BUTTON3_YCHORD,\
////			HID_MOUSE_BUTTON_WIDTH,HID_MOUSE_BUTTON_HEIGHT);
//			printf("Mouse Action: Middle Button Pressed.\r\n");
//			break;    
//	}
//}

/**
* @brief  HID_Mouse_ButtonReleased
*         The function is to handle mouse button release
* @param  button_idx : mouse button released
* @retval None
*/
//void HID_MOUSE_ButtonReleased(uint8_t button_idx)
//{  
////	/* Set the color for release status */
////	LCD_SetTextColor(LCD_COLOR_WHITE);
////	LCD_SetBackColor(LCD_COLOR_WHITE);

//	/* Change the color of button released to default button color*/
//	switch (button_idx)
//	{
//		/* Left Button Released */
//		case 0 :
////			LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD, HID_MOUSE_BUTTON1_YCHORD,\
////			HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT);
//			printf("Mouse Action: Left Button Released.\r\n");
//			break;

//		/* Right Button Released */  
//		case 1 :
////			LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD, HID_MOUSE_BUTTON2_YCHORD,\
////			HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT);
//			printf("Mouse Action: Right Button Released.\r\n");
//			break;

//		/* Middle Button Released */  
//		case 2 :
////			LCD_DrawFullRect (HID_MOUSE_BUTTON_XCHORD, HID_MOUSE_BUTTON3_YCHORD,\
////			HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT);
//			printf("Mouse Action: Middle Button Released.\r\n");
//			break;
//	}
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

