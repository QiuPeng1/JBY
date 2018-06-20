/*******************************************************

*******************************************************/

/*防止重复引用 */
#ifndef TM1620_H
#define TM1620_H

#include "stm32f10x.h"

/*将外部包含和内部包含分开*/
#ifdef _TM1620_H_
    #define TM1620_EXT
#else
    #define TM1620_EXT  extern
#endif

#define LED1_LIGHT 0x8f
#define LED2_LIGHT 0x8f
// #define stb  GPIO_Pin_7 //pd7
// #define clk  GPIO_Pin_5 //pd5
// #define dio  GPIO_Pin_8 //pd8
 //按键的常量
enum
{
	KEY_A = 0x20,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	LONG_KEY_A = KEY_A + 0x20,
	LONG_KEY_B,
	LONG_KEY_C,
	LONG_KEY_D,
	LONG_KEY_E,
	LONG_KEY_F,
	KEY_noKey = 0xff,
	
	KEY_START = KEY_A,
	KEY_MODE = KEY_B,
	KEY_BATCH = KEY_C,
	KEY_ADD = KEY_D,
	KEY_SETTING = KEY_E,
	KEY_START2 = KEY_F,
	LONG_KEY_START = LONG_KEY_A,
	LONG_KEY_MODE = LONG_KEY_B,
	LONG_KEY_BATCH = LONG_KEY_C,
	LONG_KEY_ADD = LONG_KEY_D,
	LONG_KEY_SETTING = LONG_KEY_E,
	LONG_KEY_START2 = LONG_KEY_F,
};

TM1620_EXT u8 instructLed1;
TM1620_EXT u8 instructLed2;
TM1620_EXT u8 instructLed3;
TM1620_EXT u8 instructLed4;

TM1620_EXT u8 led1CurDispStr[3];
TM1620_EXT u8 led2CurDispStr[4];

TM1620_EXT u8 gb_led1FlashOn;
TM1620_EXT u8 led1FlashCnt;
TM1620_EXT u8 led1FlashStr[3];
TM1620_EXT u8 gb_led2FlashOn;
TM1620_EXT u8 led2FlashStr[4];
TM1620_EXT u8 led2FlashCnt;
TM1620_EXT s16 led2FlashStopTimes;
TM1620_EXT s16 led1FlashStopTimes;
/*公开的过程/函数*/
/************************************************************
延时模块初始化
************************************************************/
//TM1620_EXT void LED_DISPDATA(unsigned int js_num,unsigned int yz_num,unsigned char X);
TM1620_EXT void tm16xx_Init(void);
TM1620_EXT void tm16xx_Led1Disp(u16 num);//3位数码管
TM1620_EXT void tm16xx_Led2Disp(u16 num);//4位数码管
TM1620_EXT void tm16xx_DisableDP(void);
//TM1620_EXT void tm16xx_EnableDP(u8 d);
TM1620_EXT u8 tm16xx_readKey(void);
TM1620_EXT void tm16xx_Led1DispStr(u8 *str);
TM1620_EXT void tm16xx_Led2DispStr(u8 *str);
TM1620_EXT void tm16xx_SetInsturctLed(u8 d1,u8 d2,u8 d3,u8 d4);
TM1620_EXT void tm16xx_Led1Flash(u8 on);
TM1620_EXT void tm16xx_Led2Flash(u8 on);
TM1620_EXT void tm16xx_Led1DispLastStr(void);
TM1620_EXT void tm16xx_Led2DispLastStr(void);
//TM1620_EXT void tm16xx_Led3Disp(u8 d1,u8 d2,u8 d3,u8 d4);//指示LED

#endif
