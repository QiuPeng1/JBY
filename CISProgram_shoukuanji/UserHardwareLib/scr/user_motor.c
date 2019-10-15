#include"user_motor.h"
//------------------------------------------------------------
void Motor_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_InitStruct.GPIO_Pin = RUN1_PIN;
	GPIO_Init(RUN1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = STOP_PIN;
	GPIO_Init(STOP_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = RUN2_PIN;
	GPIO_Init(RUN2_PORT, &GPIO_InitStruct);
	
	RUN1_OFF; 
	RUN2_OFF;
}

/*����������С�������*/
void  Motor_On(void)
{    
	RUN1_ON;
	RUN2_ON;
	g_SysType.f_run = 1;
	VOICE_SEG = 0;
	VOICE_RESET = 1;
//	EXTI_ENABLE();
}

/*���е���ƶ���ɲ������*/
void  Motor_Stop(void)
{     
	RUN1_OFF;
	g_SysType.f_run = 0;
//	EXTI_DISABLE();
}
/*���е�����Զ�ͣ��*/
void  Motor_AutoStop(void)
{    
	RUN1_OFF;
	RUN2_OFF;
	g_SysType.f_run = 0;
//	EXTI_DISABLE();
}
void Motor_Break(void)//ɲ��
{
	BREAK_ON;
	g_SysType.f_break = 1;
	while(g_SysType.f_break);
	BREAK_OFF;
}
