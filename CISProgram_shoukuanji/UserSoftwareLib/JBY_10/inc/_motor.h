/***************************************************************************


****************************************************************************/
//防止重复引用
#ifndef _MOTOR_H_
#define _MOTOR_H_

//包含文件
#ifdef __cplusplus
	#include "..\DebugDraw.h"
#endif

#include "system.h"
#include "motor.h"
#include "eeprom.h"
#include "delay.h"


//---------------------------------------------------------------------
//管脚及宏函数定义
//---------------------------------------------------------------------
// #define MOTOR2_ENABLE_GPIO_PORT              	GPIOC
// #define MOTOR2_ENABLE_GPIO_PIN               	GPIO_Pin_6
// #define MOTOR2_ENABLE_GPIO_MODE              	GPIO_Mode_AF_PP

// #define MOTOR2_PHASE_GPIO_PORT              	GPIOC
// #define MOTOR2_PHASE_GPIO_PIN               	GPIO_Pin_7
// #define MOTOR2_PHASE_GPIO_MODE              	GPIO_Mode_AF_PP

// #define MOTOR3_ENABLE_GPIO_PORT              	GPIOC
// #define MOTOR3_ENABLE_GPIO_PIN               	GPIO_Pin_8
// #define MOTOR3_ENABLE_GPIO_MODE              	GPIO_Mode_AF_PP

// #define MOTOR3_PHASE_GPIO_PORT              	GPIOC
// #define MOTOR3_PHASE_GPIO_PIN               	GPIO_Pin_9
// #define MOTOR3_PHASE_GPIO_MODE              	GPIO_Mode_AF_PP





/*
#define SetRLow() 	GPIO_ResetBits(R_GPIO_PORT, R_GPIO_PIN)
#define SetRHigh() GPIO_SetBits(R_GPIO_PORT, R_GPIO_PIN)

#define SetFLow() 	GPIO_ResetBits(F_GPIO_PORT, F_GPIO_PIN)
#define SetFHigh() GPIO_SetBits(F_GPIO_PORT, F_GPIO_PIN)	  */

//---------------------------------------------------------------------
//类型定义
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//常量定义
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//引用的全局变量及输入函数
//---------------------------------------------------------------------
//extern volatile STATE_T systemState;

extern u16 yuZhiNum;

extern u8 gb_cntMotorStopMp;
extern u8 g_motorStopMpNum;
#define MOTOR_STOP_ONE_MP_TIME 10
extern u8 g_motorStopTime;

//---------------------------------------------------------------------
//文件内部模块私有变量
//---------------------------------------------------------------------

//static	u8	pwmValOfBackward1 = 128;
// static	u8	pwmValOfForward2 = 128;
// static	u8	pwmValOfBackward2 = 128;
// static	u8	pwmValOfForward3 = 128;
// static	u8	pwmValOfBackward3 = 128;

//---------------------------------------------------------------------
//文件内部模块私有函数
//---------------------------------------------------------------------
extern void SetSmpleRatioTimer(u8 spd);
#endif

