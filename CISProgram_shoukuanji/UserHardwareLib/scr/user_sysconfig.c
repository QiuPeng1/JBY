#include "user_sysconfig.h"
//--------------------------------------------------------
/****************struct*****************/
_MPType 			g_MPType;//MP�ṹ�����
_InfType			g_InfType;//�ɼ���Ϣ�ṹ�����
_SysType 	 		g_SysType;//ϵͳ��־λ
/**************************************/
//--------------------------------------------------------
EXTI_InitTypeDef EXTI_InitStruct;
//==========================delay=================================
void DelayUS(u32 time) //1us 8MHz __NOP()=0.12us
{
	while(time--)
	{
		__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();
	}
}
//========================================
void DelayMs(u16 val) //
{
	u16 i;
	for(i=val;i>0;i--)
	{
		while(!g_SysType.b_1ms);
		g_SysType.b_1ms = 0;
	}
}
/*******************************************************************************
* Function Name  : InterruptConfig
* Description    : Configures the used IRQ Channels and sets their priority.
* Input          : None
* Output         : None r 
* Return         : None
*******************************************************************************/
void InterruptConfig(void)
{   
  /* Set the Vector Table base address at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0A000);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

}
//ʹ��ʱ�ӳ�ʼ��
void RCC_Config(void)
{
	RCC_LSEConfig(RCC_LSE_OFF);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|
							RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO|RCC_APB2Periph_ADC1|
							RCC_APB2Periph_ADC2|RCC_APB2Periph_USART1,ENABLE);	 //������IO�Ͷ�ʱ��1��ADC1������1ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_USART3,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);//����ADC��Ƶ,���ó���14MHZ
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //��ӳ������JTAG�ӿ�ΪIO��SWJ�ӿ���Ϊ����ʹ��
}
//����Ӳ��IO����
void SysHardwave_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; 
	NVIC_InitTypeDef NVIC_InitStruct;
//----------------------------------------------------------------	
//------------------------���̿�������----------------------------------------	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;			  //MP ������ƿ���
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = MPC_PIN;
	GPIO_Init(MPC_PORT, &GPIO_InitStruct);
	
	IRCMP_ON;
//-------------------------U�̹��翪������---------------------------------------	
	GPIO_InitStruct.GPIO_Pin = USB_SW_PIN;
	GPIO_Init(USB_SW_PORT, &GPIO_InitStruct);
	
	USB_SW_ON;
	//U���쳣����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;			  //MP ������ƿ���
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = USB_FAULT_PIN;
	GPIO_Init(USB_FAULT_PORT, &GPIO_InitStruct);
//----------------------------------------------------------------		
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;			  //�������� ������ƿ���
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = HOPC_PIN;
	GPIO_Init(HOPC_PORT, &GPIO_InitStruct);
	HOPC_ON;
//----------------------------------------------------------------	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;			  //LCD�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_InitStruct.GPIO_Pin = LCDC_PIN;
	GPIO_Init(LCDC_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LCDR_PIN;
	GPIO_Init(LCDR_PORT, &GPIO_InitStruct);
//----------------------------------------------------------------		
	DispOpenBL();
//-----------------------MG,MRM�ж�����-----------------------------------------	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //����MP 
	GPIO_InitStruct.GPIO_Pin = MP_PIN;
	GPIO_Init(MP_PORT, &GPIO_InitStruct);
	
//	GPIO_InitStruct.GPIO_Pin = MRM_PIN;
//	GPIO_Init(MRM_PORT, &GPIO_InitStruct);
	
 	GPIO_EXTILineConfig(MP_PORTSOURCE, MP_PINSOURCE);//
//	GPIO_EXTILineConfig(MRM_PORTSOURCE, MRM_PINSOURCE);//
 	
 	EXTI_InitStruct.EXTI_Line = EXTI_MP;
 	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
 	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
 	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
 	EXTI_Init(&EXTI_InitStruct);
	
//	EXTI_InitStruct.EXTI_Line = EXTI_MRM;
// 	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
// 	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
// 	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
// 	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn; //MP �ж�ͨ������
 	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
 	NVIC_InitStruct.NVIC_IRQChannelSubPriority= 1;
 
 	NVIC_Init(&NVIC_InitStruct);

}
//---------------------------------------------------------
void MP_DISABLE(void)
{
 	EXTI_InitStruct.EXTI_Line = EXTI_MP;     //��ֹMP�ж�
 	EXTI_InitStruct.EXTI_LineCmd = DISABLE;
 	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
 	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
 	EXTI_Init(&EXTI_InitStruct);
}
void MP_ENABLE(void)
{
 	EXTI_InitStruct.EXTI_Line = EXTI_MP; //ʹ��MP�ж�
 	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
 	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
 	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
 	EXTI_Init(&EXTI_InitStruct);
}
//---------------------------------------------------------
//ʱ������1MS
void Systick_Config(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
//	SysTick->LOAD=SystemCoreClock/8000-1;						//1ms��ʱ��  //SystemCoreClock/8000000;
	SysTick->LOAD=SystemCoreClock/16000-1;						//0.5ms��ʱ��  //SystemCoreClock/8000000;	
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж�
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK 
}
void Struct_Init(void)
{
	memset((void *)&g_MPType,0x0,sizeof(g_MPType));
	memset((void *)&g_SysType,0x0,sizeof(g_SysType));	
	memset((void *)&g_InfType,0x0,sizeof(g_InfType));
	memset((void *)&g_Sensitivity,0x0,sizeof(g_Sensitivity));
}



