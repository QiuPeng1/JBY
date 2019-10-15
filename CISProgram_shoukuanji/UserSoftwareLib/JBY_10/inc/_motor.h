/***************************************************************************


****************************************************************************/
//��ֹ�ظ�����
#ifndef _MOTOR_H_
#define _MOTOR_H_

//�����ļ�
#ifdef __cplusplus
	#include "..\DebugDraw.h"
#endif

#include "system.h"
#include "motor.h"
#include "eeprom.h"
#include "delay.h"


//---------------------------------------------------------------------
//�ܽż��꺯������
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
//���Ͷ���
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//��������
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//���õ�ȫ�ֱ��������뺯��
//---------------------------------------------------------------------
//extern volatile STATE_T systemState;

extern u16 yuZhiNum;

extern u8 gb_cntMotorStopMp;
extern u8 g_motorStopMpNum;
#define MOTOR_STOP_ONE_MP_TIME 10
extern u8 g_motorStopTime;

//---------------------------------------------------------------------
//�ļ��ڲ�ģ��˽�б���
//---------------------------------------------------------------------

//static	u8	pwmValOfBackward1 = 128;
// static	u8	pwmValOfForward2 = 128;
// static	u8	pwmValOfBackward2 = 128;
// static	u8	pwmValOfForward3 = 128;
// static	u8	pwmValOfBackward3 = 128;

//---------------------------------------------------------------------
//�ļ��ڲ�ģ��˽�к���
//---------------------------------------------------------------------
extern void SetSmpleRatioTimer(u8 spd);
#endif

