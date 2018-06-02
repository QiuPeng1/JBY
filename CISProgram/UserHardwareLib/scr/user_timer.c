/*���Ƹ���ԴPWM*/
#include "user_timer.h"


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;
TIM_OCInitTypeDef  TIM_OCInitStruct;
//---------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��Ϊ108MHZ
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//-------------------------------------------------------------	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
////ʹ�ܻ���ʧ��ָ����TIM�ж�
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
							 
}
//-------------------------------------------------------------
void Timer_Config(void)
{
	
	//----------------------------��ʱ�����IO����----------------------------------------
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
//-------------------------CH1-----������Թ�PWM----------------	
	TIM_OCInitStruct.TIM_Pulse = g_Sensitivity.LIRPWM;
	TIM_OC1Init(TIM3, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
//-------------------------CH2-----�Ҽ����Թ�PWM--------------------	
	TIM_OCInitStruct.TIM_Pulse = g_Sensitivity.RIRPWM;
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
//----------------------------------------------------------
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
//-----------------------------------------------------
	
	OpenLight();
//--------------------------------------------------------
	TIM2_Int_Init(80,108);//30US�ļ���Ƶ��
//------------------------------------------------------
}
/**********************���´򿪺͹ر�PWM����******************************/
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
/**********************�򿪹�Դ*********************/ 
void OpenLight(void)
{
	IRCMP_ON;		//�����̹�Դ
	
	TIM_OCPWMConfig(TIM3,TIM_Channel_1,TIM_OCMode_PWM1);
	TIM_OCPWMConfig(TIM3,TIM_Channel_2,TIM_OCMode_PWM1);	
}
/**********************�رչ�Դ*********************/ 
void CloseLight(void)
{
	IRCMP_OFF;		//�ر����̹�Դ
	
	TIM_OCPWMConfig(TIM3,TIM_Channel_1,TIM_OCMode_Inactive);
	TIM_OCPWMConfig(TIM3,TIM_Channel_2,TIM_OCMode_Inactive);
}	
//-------------------------------------------------------

