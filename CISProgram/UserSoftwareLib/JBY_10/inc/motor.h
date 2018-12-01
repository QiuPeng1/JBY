/***************************************************************************


****************************************************************************/

/*��ֹ�ظ����� */
#ifndef MOTOR_H
#define MOTOR_H

#include "system.h"

/*���ⲿ�������ڲ������ֿ�*/
#ifdef _MOTOR_H_
    #define MOTOR_EXT_PARA
	#define MOTOR_EXT_FUNC
#else
	#ifdef __cplusplus
		#define MOTOR_EXT_PARA  EXTERN_C
		#define MOTOR_EXT_FUNC  extern
	#else
		#define MOTOR_EXT_PARA  extern
		#define MOTOR_EXT_FUNC  extern		
	#endif
#endif

//�����������оƬDVR8800
#define DVR8800

//---------------------------------------------------------------------
//ȫ�ֳ�������
//---------------------------------------------------------------------
enum
{
	MOTOR_STOP = 0,
	MOTOR_RUN,
	MOTOR_FORWARD_RUN,
	MOTOR_BACKWARD_RUN,
	MOTOR_BREAK
};

enum
{
	SPEED_800 = 0,
	SPEED_900,
	SPEED_1000,
	SPEED_NUM,
};

#define MOTOR1_ENABLE_GPIO_PORT              	GPIOB
#define MOTOR1_ENABLE_GPIO_PIN               	GPIO_Pin_0
#define MOTOR1_ENABLE_GPIO_MODE              	GPIO_Mode_AF_PP
// #define Motor1Enable() 	GPIO_SetBits(MOTOR1_ENABLE_GPIO_PORT, MOTOR1_ENABLE_GPIO_PIN)
// #define Motor1Disable() GPIO_ResetBits(MOTOR1_ENABLE_GPIO_PORT, MOTOR1_ENABLE_GPIO_PIN)

#define MOTOR1_PWM_GPIO_PORT              	GPIOB
#define MOTOR1_PWM_GPIO_PIN               	GPIO_Pin_1
#define MOTOR1_PWM_GPIO_MODE              	GPIO_Mode_AF_PP

#define MOTOR1_FORWARD_PWM (TIM3 -> CCR3)  
#define MOTOR1_BACKWARD_PWM (TIM3 -> CCR4)  

// #define MOTOR2_ENABLE (TIM3 -> CCR1)  
// #define MOTOR2_PHASE (TIM3 -> CCR2)  

// #define MOTOR3_ENABLE (TIM3 -> CCR3)  
// #define MOTOR3_PHASE (TIM3 -> CCR4)  


//#define UVLED_PWM (TIM3 -> CCR4)  //modify	UV���ƵĹܽ��޸ĵ�PC9,ʹ��TIM3��Channel4

//---------------------------------------------------------------------
//ȫ�����Ͷ���
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//ȫ�ֱ��������Ա��ⲿ����ֱ�ӷ���
//---------------------------------------------------------------------
MOTOR_EXT_PARA u8 g_motor1State;
MOTOR_EXT_PARA u8 currentSpeed;
// MOTOR_EXT_PARA u8 g_motor2State;
// MOTOR_EXT_PARA u8 g_motor3State;
MOTOR_EXT_PARA u16 g_motorSpeedCountVal;
MOTOR_EXT_PARA u16 g_codePanCountForCsMp;
MOTOR_EXT_PARA	u8	forwardPwmValue;
MOTOR_EXT_PARA	u8	backwardPwmValue;
MOTOR_EXT_PARA	u8	gb_enableSampleFlag;
// #define MOTOR_OVER_LOAD_CHECK_DELAY 30
// MOTOR_EXT_PARA u8 motor1OverLoadCheckDelay;
// MOTOR_EXT_PARA u8 motor2OverLoadCheckDelay;
// MOTOR_EXT_PARA u8 motor3OverLoadCheckDelay;
// MOTOR_EXT_PARA u8 motor1OverLoadCnt;
// MOTOR_EXT_PARA u8 motor2OverLoadCnt;
// MOTOR_EXT_PARA u8 motor3OverLoadCnt;
//MOTOR_EXT_PARA u16 motorBackwAgeTimeoutTimer;

//���ڵ�Ǯ״̬����ʱ��Ҫһ��ʱ�����Ͷ��ȥ,���Խ��ж϶±�ʱ���ӳ�
#define MOTOR_JAM_TIMEOUT (520*1)			//2.6
#define MOTOR_AGE_TIMEOUT 1000

//MOTOR_EXT_PARA u16 g_codePanTimeOutCounter;
#define MOTOR_DELAY_TIME 80
#define MOTOR_FAN_ZHUAN_DELAY_TIME 300 //

//---------------------------------------------------------------------
//�����ĺ���
//---------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif
	MOTOR_EXT_FUNC void motor_Init(void);
	MOTOR_EXT_FUNC void motor1_Stop(void);
// 	MOTOR_EXT_FUNC void motor_SetSpeed(u8 spd);
	MOTOR_EXT_FUNC void motor1_SetSpeed(u8 spd);
// 	MOTOR_EXT_FUNC void motor2_SetSpeed(u8 spd);
// 	MOTOR_EXT_FUNC void motor3_SetSpeed(u8 spd);
	MOTOR_EXT_FUNC void motor1_ForwardRun(void);
	MOTOR_EXT_FUNC void motor1_BackwardRun(void);
	//MOTOR_EXT_FUNC void motor1_AntiClockWiseRun(void);
//	MOTOR_EXT_FUNC void motor1_Break(void);
	MOTOR_EXT_FUNC void motor1_SetForwardPwm(void);
	MOTOR_EXT_FUNC void motor1_SetBackwardPwm(void);
// 	MOTOR_EXT_FUNC void motor2_Stop(void);
// 	MOTOR_EXT_FUNC void motor2_ClockWiseRun(void);
// 	MOTOR_EXT_FUNC void motor2_AntiClockWiseRun(void);
// 	MOTOR_EXT_FUNC void motor2_Break(void);
// 	MOTOR_EXT_FUNC void motor3_Stop(void);
// 	MOTOR_EXT_FUNC void motor3_ClockWiseRun(void);
// 	MOTOR_EXT_FUNC void motor3_AntiClockWiseRun(void);
// 	MOTOR_EXT_FUNC void motor3_Break(void);
#ifdef __cplusplus
}
#endif

#endif
