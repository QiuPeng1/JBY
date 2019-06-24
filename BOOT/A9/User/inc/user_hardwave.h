#ifndef __HARDWAVE_H__
#define __HARDWAVE_H__
#include "user_includes.h"
//-----------------码盘接收中断配置------------------------
#define 	MP_PORT				GPIOA
#define 	MP_PIN				GPIO_Pin_7
#define 	READ_MP   			PAin(7)
//----中断配置
#define   	EXTI_MP     		EXTI_Line7
#define   	MP_PORTSOURCE   	GPIO_PortSourceGPIOA  //中断线port
#define   	MP_PINSOURCE		GPIO_PinSource7
//-----------------码盘发射控制------------------------
#define 	MPC_PORT 			GPIOC
#define 	MPC_PIN	 			GPIO_Pin_4
#define 	PER_MPC				PCout(4)

#define 	IRCMP_ON			PER_MPC = 1	
#define 	IRCMP_OFF			PER_MPC = 0
//-----------------中间长磁中断配置------------------------
#define 	MRM_PORT			GPIOA
#define 	MRM_PIN				GPIO_Pin_6
#define 	READ_MRM   			PAin(6)
//----中断配置
#define   	EXTI_MRM     		EXTI_Line6
#define   	MRM_PORTSOURCE   	GPIO_PortSourceGPIOA  //中断线port
#define   	MRM_PINSOURCE		GPIO_PinSource6
//------------------按键配置-----------------------
#define 	KEY1_PORT 			GPIOB
#define 	KEY1_PIN	 		GPIO_Pin_2
#define 	READ_KEY1			PBin(2)

#define 	KEY2_PORT 			GPIOB
#define 	KEY2_PIN	 		GPIO_Pin_1
#define 	READ_KEY2			PBin(1)

#define 	KEY3_PORT 			GPIOB
#define 	KEY3_PIN	 		GPIO_Pin_0
#define 	READ_KEY3			PBin(0)

#define 	KEY4_PORT 			GPIOC
#define 	KEY4_PIN	 		GPIO_Pin_5
#define 	READ_KEY4			PCin(5)
//------------------CIS SPI配置-----------------------
#define 	CIS_MISO_PORT 		GPIOB
#define 	CIS_MISO_PIN	 	GPIO_Pin_15
#define 	PER_CIS_MISO		PBout(15)
#define 	READ_CIS_MISO		PBin(15)

#define 	CIS_MOSI_PORT 		GPIOB
#define 	CIS_MOSI_PIN	 	GPIO_Pin_14
#define 	PER_CIS_MOSI		PBout(14)

#define 	CIS_CLK_PORT 		GPIOB
#define 	CIS_CLK_PIN	 		GPIO_Pin_13
#define 	PER_CIS_CLK			PBout(13)

#define 	CIS_SS_PORT 		GPIOB
#define 	CIS_SS_PIN	 		GPIO_Pin_12
#define 	PER_SS_MOSI			PBout(12)
//----------------PWM IRL IRR-------------------------
#define 	PWM_IRR_PORT 		GPIOC
#define 	PWM_IRR_PIN	 		GPIO_Pin_6
#define 	PER_PWM_IRR			PBout(6)

#define 	PWM_IRL_PORT 		GPIOC
#define 	PWM_IRL_PIN	 		GPIO_Pin_7
#define 	PER_PWM_IRL			PCout(7)
//-----------------U盘供电及监测--------------------------
#define 	USB_FAULT_PORT 		GPIOC
#define 	USB_FAULT_PIN	 	GPIO_Pin_9
#define 	READ_USB_FAULT		PCin(9)

#define 	USB_SW_PORT 		GPIOC
#define 	USB_SW_PIN	 		GPIO_Pin_8
#define 	PER_USB_SW			PCout(8)

#define 	USB_SW_ON			PER_USB_SW = 0;
#define 	USB_SW_OFF			PER_USB_SW = 1;
//------------------外显示接口----------------------
#define 	TM1616_STB_PORT 	GPIOA
#define 	TM1616_STB_PIN	 	GPIO_Pin_8
#define 	TM1616_STB			PAout(8)

#define 	TM1616_CLK_PORT 	GPIOA
#define 	TM1616_CLK_PIN	 	GPIO_Pin_9
#define 	TM1616_CLK			PAout(9)

#define 	TM1616_DIO_PORT 	GPIOA
#define 	TM1616_DIO_PIN	 	GPIO_Pin_10
#define 	TM1616_DIO			PAout(10)
//-------------------侧显示-------------------------
#define 	TM1638_STB_PORT 	GPIOA
#define 	TM1638_STB_PIN	 	GPIO_Pin_15
#define 	TM1638_STB			PAout(15)

#define 	TM1638_CLK_PORT 	GPIOC
#define 	TM1638_CLK_PIN	 	GPIO_Pin_10
#define 	TM1638_CLK			PCout(10)

#define 	TM1638_DIO_PORT 	GPIOC
#define 	TM1638_DIO_PIN	 	GPIO_Pin_11
#define 	TM1638_DIO			PCout(11)
//---------------------------
#define 	LCD418_DIO_PORT 	GPIOA
#define 	LCD418_DIO_PIN	 	GPIO_Pin_15
#define 	LCD418_DIO   		PAout(15)

#define 	LCD418_STB_PORT 	GPIOC
#define 	LCD418_STB_PIN	 	GPIO_Pin_10
#define 	LCD418_STB			PCout(10)

#define 	LCD418_CLK_PORT 	GPIOC
#define 	LCD418_CLK_PIN	 	GPIO_Pin_11
#define 	LCD418_CLK			PCout(11)
//-------------------主显示-------------------------
#define 	LCD_STB_PORT 		GPIOC
#define 	LCD_STB_PIN	 		GPIO_Pin_5
#define 	LCD_STB				PCout(5)


#define 	LCD_CLK_PORT 		GPIOB
#define 	LCD_CLK_PIN	 		GPIO_Pin_5
#define 	LCD_CLK				PBout(5)

#define 	LCD_DIO_PORT 		GPIOB
#define 	LCD_DIO_PIN	 		GPIO_Pin_3
#define 	LCD_DIO				PBout(3)
//---------------------------------------------------
#define 	KEY0832_STB_PORT 	GPIOB
#define 	KEY0832_STB_PIN	 	GPIO_Pin_4
#define 	KEY0832_STB			PBout(4)

#define 	KEY0832_CLK_PORT 	GPIOB
#define 	KEY0832_CLK_PIN	 	GPIO_Pin_5
#define 	KEY0832_CLK			PBout(5)

#define 	KEY0832_DIO_PORT 	GPIOB
#define 	KEY0832_DIO_PIN	 	GPIO_Pin_3
#define 	KEY0832_DIO			PBout(3)
#define 	KEY0832_DIOR		PBin(3)
//--------------------背光源控制-------------------------
#define		LCDC_PORT			GPIOC
#define 	LCDC_PIN			GPIO_Pin_12
#define 	PER_LCDC			PCout(12)

#define		LCDR_PORT			GPIOD
#define 	LCDR_PIN			GPIO_Pin_2
#define 	PER_LCDR			PDout(2)

#define 	LCDC_ON				PER_LCDC = 0;PER_LCDR = 1 		
#define 	LCDC_OFF			PER_LCDC = 1;PER_LCDR = 1 		 	 

#define 	LCDR_ON				PER_LCDC = 1;PER_LCDR = 0 	
#define 	LCDR_OFF			PER_LCDC = 0;PER_LCDR = 1 	

#define 	LCD_DARK			PER_LCDC = 1;PER_LCDR = 1 
//----------------语音芯片-------------------------
#define 	VOICE_SEG_PORT 		GPIOB
#define 	VOICE_SEG_PIN	 	GPIO_Pin_8
#define 	VOICE_SEG			PBout(8)

#define 	VOICE_RESET_PORT 	GPIOB
#define 	VOICE_RESET_PIN	 	GPIO_Pin_7
#define 	VOICE_RESET			PBout(7)

#define 	VOICE_BUSY_PORT 	GPIOB
#define 	VOICE_BUSY_PIN	 	GPIO_Pin_6
#define 	VOICE_BUSY			PBin(6)
//-----------------------------------------
#define 	HOPC_PORT			GPIOB
#define 	HOPC_PIN			GPIO_Pin_9
#define 	PER_HOPC   			PBout(9)

#define 	HOPC_ON				PER_HOPC = 0	
#define 	HOPC_OFF			PER_HOPC = 1
//--------------------------------------------------
//电机控制接口
#define 	RUN1_PORT 			GPIOC
#define 	RUN1_PIN 			GPIO_Pin_13
#define 	PER_RUN1			PCout(14)

#define 	STOP_PORT 			GPIOC
#define 	STOP_PIN 			GPIO_Pin_14
#define 	PER_STOP			PCout(13)

#define 	RUN2_PORT 			GPIOC
#define 	RUN2_PIN 			GPIO_Pin_15
#define 	PER_RUN2			PCout(15)


#define 	RUN1_ON 			PER_RUN1 = 0;PER_STOP = 1
#define 	RUN1_OFF 			PER_RUN1 = 1;PER_STOP = 1

#define 	BREAK_ON 			PER_RUN1 = 1;PER_STOP = 0
#define 	BREAK_OFF 			PER_RUN1 = 1;PER_STOP = 1

#define 	RUN2_ON 			PER_RUN2 = 1
#define 	RUN2_OFF 			PER_RUN2 = 0
//--------------------------------------------------------------------------------------------
//开机代码的编号
#define     VIET_A12
//#define     VIET_A12_2804
//#define     VIET_A12_3000A
#endif
