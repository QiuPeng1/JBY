#include "user_sysconfig.h"
//--------------------------------------------------------
/****************struct*****************/
_MPType 			g_MPType;//MP结构体变量
_InfType			g_InfType;//采集信息结构体变量
_SysType 	 		g_SysType;//系统标志位
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
//使用时钟初始化
void RCC_Config(void)
{
	RCC_LSEConfig(RCC_LSE_OFF);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|
							RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO|RCC_APB2Periph_ADC1|
							RCC_APB2Periph_ADC2|RCC_APB2Periph_USART1,ENABLE);	 //打开所有IO和定时器1，ADC1，串口1时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_USART3,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);//配置ADC分频,不得超过14MHZ
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //重映射设置JTAG接口为IO，SWJ接口作为仿真使用
}
//基础硬件IO配置
void SysHardwave_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; 
	NVIC_InitTypeDef NVIC_InitStruct;
//----------------------------------------------------------------	
//------------------------码盘开关配置----------------------------------------	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;			  //MP 发射控制开关
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = MPC_PIN;
	GPIO_Init(MPC_PORT, &GPIO_InitStruct);
	
	IRCMP_ON;
//-------------------------U盘供电开关配置---------------------------------------	
	GPIO_InitStruct.GPIO_Pin = USB_SW_PIN;
	GPIO_Init(USB_SW_PORT, &GPIO_InitStruct);
	
	USB_SW_ON;
	//U盘异常反馈
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;			  //MP 发射控制开关
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = USB_FAULT_PIN;
	GPIO_Init(USB_FAULT_PORT, &GPIO_InitStruct);
//----------------------------------------------------------------		
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;			  //启动光耦 发射控制开关
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = HOPC_PIN;
	GPIO_Init(HOPC_PORT, &GPIO_InitStruct);
	HOPC_ON;
//----------------------------------------------------------------	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;			  //LCD背光控制
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_InitStruct.GPIO_Pin = LCDC_PIN;
	GPIO_Init(LCDC_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LCDR_PIN;
	GPIO_Init(LCDR_PORT, &GPIO_InitStruct);
//----------------------------------------------------------------		
	DispOpenBL();
//-----------------------MG,MRM中断配置-----------------------------------------	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //设置MP 
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
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn; //MP 中断通道配置
 	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
 	NVIC_InitStruct.NVIC_IRQChannelSubPriority= 1;
 
 	NVIC_Init(&NVIC_InitStruct);

}
//---------------------------------------------------------
void MP_DISABLE(void)
{
 	EXTI_InitStruct.EXTI_Line = EXTI_MP;     //禁止MP中断
 	EXTI_InitStruct.EXTI_LineCmd = DISABLE;
 	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
 	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
 	EXTI_Init(&EXTI_InitStruct);
}
void MP_ENABLE(void)
{
 	EXTI_InitStruct.EXTI_Line = EXTI_MP; //使能MP中断
 	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
 	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
 	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
 	EXTI_Init(&EXTI_InitStruct);
}
//---------------------------------------------------------
//时基控制1MS
void Systick_Config(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
//	SysTick->LOAD=SystemCoreClock/8000-1;						//1ms定时器  //SystemCoreClock/8000000;
	SysTick->LOAD=SystemCoreClock/16000-1;						//0.5ms定时器  //SystemCoreClock/8000000;	
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//开启SYSTICK中断
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//开启SYSTICK 
}
void Struct_Init(void)
{
	memset((void *)&g_MPType,0x0,sizeof(g_MPType));
	memset((void *)&g_SysType,0x0,sizeof(g_SysType));	
	memset((void *)&g_InfType,0x0,sizeof(g_InfType));
	memset((void *)&g_Sensitivity,0x0,sizeof(g_Sensitivity));
}



