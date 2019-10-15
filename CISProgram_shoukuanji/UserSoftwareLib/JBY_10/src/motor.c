/***************************************************************************


****************************************************************************/

/*包含私有头文件 */
#include "_motor.h"

/*公开的子程序*/ 
//---------------------------------------------------------------------
//显示模块初始化，管脚初始化，清0，打开背光灯
//---------------------------------------------------------------------
void motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//管脚配置
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	

	GPIO_InitStructure.GPIO_Pin = MOTOR1_ENABLE_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode =MOTOR1_ENABLE_GPIO_MODE; 
	GPIO_Init(MOTOR1_ENABLE_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = MOTOR1_PWM_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode =MOTOR1_PWM_GPIO_MODE; 
	GPIO_Init(MOTOR1_PWM_GPIO_PORT, &GPIO_InitStructure);
	
// 	GPIO_InitStructure.GPIO_Pin = MOTOR2_ENABLE_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode =MOTOR2_ENABLE_GPIO_MODE; 
// 	GPIO_Init(MOTOR2_ENABLE_GPIO_PORT, &GPIO_InitStructure);

// 	GPIO_InitStructure.GPIO_Pin = MOTOR2_PHASE_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode =MOTOR2_PHASE_GPIO_MODE; 
// 	GPIO_Init(MOTOR2_PHASE_GPIO_PORT, &GPIO_InitStructure);
// 	
// 	GPIO_InitStructure.GPIO_Pin = MOTOR3_ENABLE_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode =MOTOR3_ENABLE_GPIO_MODE; 
// 	GPIO_Init(MOTOR3_ENABLE_GPIO_PORT, &GPIO_InitStructure);

// 	GPIO_InitStructure.GPIO_Pin = MOTOR3_PHASE_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode =MOTOR3_PHASE_GPIO_MODE; 
// 	GPIO_Init(MOTOR3_PHASE_GPIO_PORT, &GPIO_InitStructure);	

	//把TIME3的4个通道重定位
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);	   //modify 管脚重定义
	
	//把TIME4的4个通道重定位
	//GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);	   //modify 管脚重定义
		
	//PWM配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler = 720-1;//240-1;
	TIM_TimeBaseStructure.TIM_Period = 254;		
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	

	//72M/24 = 6M 6M /256 =  12K
	//72M/240 = 0.6M 0.6M /256 =  1.2K
	
// 	///TIM3_CH1
// 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
// 	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
// 	TIM_OCInitStructure.TIM_Pulse = 0;	//相当于输出常0
// 	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
// 	
// 	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	
// 	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

// 	///TIM3_CH2
// 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
// 	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
// 	TIM_OCInitStructure.TIM_Pulse = 0;	//相当于输出常0
// 	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
// 	
// 	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
// 	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
// 	
	///TIM3_CH3
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 0;	//相当于输出常0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	///TIM3_CH4
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 0;	//相当于输出常0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);	

	TIM_Cmd(TIM3, ENABLE);		

	motor1_Stop();
// 	motor3_Stop();
	TIM_CtrlPWMOutputs(TIM3, ENABLE);	
// 	
	//TIM4
	//PWM配置
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

// 	TIM_TimeBaseStructure.TIM_Prescaler = 80-1;//
// 	TIM_TimeBaseStructure.TIM_Period = 254;		
// 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
// 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
// 	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);	


// 	///TIM4_CH3
// 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
// 	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
// 	TIM_OCInitStructure.TIM_Pulse = 0;	//相当于输出常0
// 	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
// 	
// 	TIM_OC3Init(TIM4, &TIM_OCInitStructure);	
// 	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
// 	
	///TIM4_CH4
// 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
// 	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
// 	TIM_OCInitStructure.TIM_Pulse = 0;	//相当于输出常0
// 	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
// 	
// 	TIM_OC4Init(TIM4, &TIM_OCInitStructure);	
// 	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
// 	
// 	TIM_Cmd(TIM4, ENABLE);		

// 	motor1_Stop();
// 	TIM_CtrlPWMOutputs(TIM4, ENABLE);	
	
	motor1_SetSpeed(savedPara.userWorkPara.d[INDEX_SPEED]);
}

//---------------------------------------------------------------------
//停止转动
//---------------------------------------------------------------------
void motor1_Stop(void)
{
	if(g_motor1State != MOTOR_STOP)
	{
		gb_enableSampleFlag = 0;
		g_motor1State = MOTOR_STOP;	
		MOTOR1_FORWARD_PWM = 0;
		MOTOR1_BACKWARD_PWM = 0;
	}
}

void motor1_ForwardRun(void)
{
	//if(g_motor1State == MOTOR_STOP)
	{
		gb_enableSampleFlag = 1;
		g_motor1State = MOTOR_FORWARD_RUN;
		MOTOR1_BACKWARD_PWM = 0;
		MOTOR1_FORWARD_PWM = forwardPwmValue;//forwardPwmValue;
	}
}

void motor1_BackwardRun(void)
{
	//if(g_motor1State == MOTOR_STOP)
	{
		gb_enableSampleFlag = 1;
		g_motor1State = MOTOR_BACKWARD_RUN;
		MOTOR1_BACKWARD_PWM = backwardPwmValue;
		MOTOR1_FORWARD_PWM = 0;
	}
}

void motor1_Break(void)//刹车
{
	//if(g_motor1State == MOTOR_RUN)
	{
		motor1_Stop();
		delay_DelayMs(1);
	}
}

// void motor1_ClockWiseRun(void)//左电机 转盘顺时针转动
// {
// 	g_motor1State = MOTOR_BACKWARD_RUN;
// 	MOTOR1_PHASE = 0;
// 	MOTOR1_ENABLE = pwmValOfBackward1;
// 	motor1OverLoadCheckDelay = MOTOR_OVER_LOAD_CHECK_DELAY;
// 	motor1OverLoadCnt = 0;
// }

// void motor1_Break(void)
// {
// 	motor1_Stop();
// 	//motorJamTimeoutTimer = 0;
// }
void motor1_SetForwardPwm(void)
{
	MOTOR1_FORWARD_PWM = forwardPwmValue;
}

void motor1_SetBackwardPwm(void)
{
	MOTOR1_BACKWARD_PWM = backwardPwmValue;
}

void motor1_SetSpeed(u8 spd)
{
	currentSpeed = spd;
	switch (spd)
	{
		case SPEED_800:
			forwardPwmValue = 255;//255;//savedPara.adjustPara.csddjInitVal[spd][0];
			backwardPwmValue = 255;//220;//savedPara.adjustPara.csddjInitVal[spd][1];
			break;
		case SPEED_900:
		case SPEED_1000:
			forwardPwmValue = 255;//savedPara.adjustPara.csddjInitVal[spd][0];
			backwardPwmValue = 220;//savedPara.adjustPara.csddjInitVal[spd][1];
			break;
		default:
			currentSpeed = SPEED_800;
			forwardPwmValue = savedPara.adjustPara.csddjInitVal[SPEED_800][0];
			backwardPwmValue = savedPara.adjustPara.csddjInitVal[SPEED_800][1];
			break;
	}
	SetSmpleRatioTimer(currentSpeed);
}
