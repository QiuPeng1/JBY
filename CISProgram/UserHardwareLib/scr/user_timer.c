/*控制各光源PWM*/
#include "user_timer.h"


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;
TIM_OCInitTypeDef  TIM_OCInitStruct;
//---------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//通用定时器中断初始化
//这里时钟选择为108MHZ
//arr：自动重装值。
//psc：时钟预分频数
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
//-------------------------------------------------------------	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
////使能或者失能指定的TIM中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
							 
}
//-------------------------------------------------------------
void Timer_Config(void)
{
	
	//----------------------------定时器相关IO控制----------------------------------------
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin = PWM_IRR_PIN;
	GPIO_Init(PWM_IRR_PORT, &GPIO_InitStruct);//TIM3
	
	GPIO_InitStruct.GPIO_Pin = PWM_IRL_PIN;
	GPIO_Init(PWM_IRL_PORT, &GPIO_InitStruct);//TIM3
//---------------------------------------------------------------------------	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);	
//--------------------------------------------------------------------------	
	/* Time Base configuration */
	TIM_TimeBaseStruct.TIM_Period = 100;
	TIM_TimeBaseStruct.TIM_Prescaler = 5;
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);
//-------------------------------------------------------------------	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
//-------------------------CH1-----左计数对管PWM----------------	
	TIM_OCInitStruct.TIM_Pulse = g_Sensitivity.LIRPWM;
	TIM_OC1Init(TIM3, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
//-------------------------CH2-----右计数对管PWM--------------------	
	TIM_OCInitStruct.TIM_Pulse = g_Sensitivity.RIRPWM;
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
//----------------------------------------------------------
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
//-----------------------------------------------------
	
	OpenLight();
//--------------------------------------------------------
	TIM2_Int_Init(80,108);//30US的计数频率
//------------------------------------------------------
}
/**********************重新打开和关闭PWM功能******************************/
static void TIM_OCPWMConfig(TIM_TypeDef* TIMx, uint16_t TIM_Channel ,uint16_t TIM_OC_Mode)
{
	uint16_t tmpccmr1 = 0,tmpccmr2 = 0;
	switch(TIM_Channel)
	{
		case TIM_Channel_1:
			tmpccmr1 = TIMx->CCMR1;
			tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC1M);
			tmpccmr1 |= TIM_OC_Mode;
			TIMx->CCMR1 = tmpccmr1;
			break;
		case TIM_Channel_2:
			tmpccmr1 = TIMx->CCMR1;
			tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC2M);
			tmpccmr1 |= (TIM_OC_Mode<<8);
			TIMx->CCMR1 = tmpccmr1;
			break;
		case TIM_Channel_3:
			tmpccmr2 = TIMx->CCMR2;
			tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC3M);
			tmpccmr2 |= TIM_OC_Mode;
			TIMx->CCMR2 = tmpccmr2;
			break;
		case TIM_Channel_4:
			tmpccmr2 = TIMx->CCMR2;
			tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC4M);
			tmpccmr2 |= (TIM_OC_Mode<<8);
			TIMx->CCMR2 = tmpccmr2;
			break;
	}
	
	
}
/**********************打开光源*********************/ 
void OpenLight(void)
{
	IRCMP_ON;		//打开码盘光源
	
	TIM_OCPWMConfig(TIM3,TIM_Channel_1,TIM_OCMode_PWM1);
	TIM_OCPWMConfig(TIM3,TIM_Channel_2,TIM_OCMode_PWM1);	
}
/**********************关闭光源*********************/ 
void CloseLight(void)
{
	IRCMP_OFF;		//关闭码盘光源
	
	TIM_OCPWMConfig(TIM3,TIM_Channel_1,TIM_OCMode_Inactive);
	TIM_OCPWMConfig(TIM3,TIM_Channel_2,TIM_OCMode_Inactive);
}	
//-------------------------------------------------------

