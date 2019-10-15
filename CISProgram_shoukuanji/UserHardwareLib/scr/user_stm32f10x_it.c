/**
  ******************************************************************************
  * @file    RTC/Calendar/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_it.h"
#include "user_includes.h"
/***********************************************************/
extern u8 uart3DelayTimer;
extern u8 gb_needDealUart3Data;
/****************u16********************/
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup RTC_Calendar
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*
	上口计数管，有钞高电压322，无钞低电压012    门槛   200
	下口计数管，有钞低电压150，无钞高电压322
*/
void SysTick_Handler(void)
{
	static u16 Time200ms=0,BreakTimes=0,Time2s = 0,Time1ms=0;
	static u32 count_1s=0;
	++Time1ms;
	if(Time1ms==1) g_SysType.b_1ms = 1;
	if(Time1ms>=2)
	{
		Time1ms = 0;
		if(g_SysType.f_break)
		{
			if(++BreakTimes>g_Sensitivity.BreakTime)
			{
				BreakTimes = 0;
				g_SysType.f_break = 0;
			}
		}
		if(!g_KeyType.FlagPowerReset) 
		{
			PER_HOPC = !PER_HOPC;
		}
		else
		{
			HOPC_ON;
		}	
		if(++Time200ms>200)
		{
			Time200ms = 0;
			g_SysType.b_200ms = 1;	
			if(++Time2s>10)
			{
				Time2s = 0;
				g_SysType.b_2s = 1;	
			}
		}
		if(!g_SysType.f_run)
		{
			
			if(g_Sensitivity.BLTime!=0)
			{
				 if(g_SysType.f_FreeLcdTimes)
				{
					if(++count_1s>=120000) //  1S
						{
							count_1s = 0;
							if(++g_SysType.FreeLcdTimes>=g_Sensitivity.BLTime)
								{
									g_SysType.f_FreeLcdTimes = 0;
									LCD_DARK;
								}
						}
				}
				else count_1s = 0;
			}
		}
		if(maxSpiRecvWaitTime > 0)
		{
			maxSpiRecvWaitTime --;
		}
	}
	
//--------------------------------------------------------------
//	if(uart3DelayTimer>0)
//	{
//		uart3DelayTimer--;
//		if(uart3DelayTimer==0)
//		{
//			gb_needDealUart3Data = 1;
//		}
//	}
	if(gb_inUpgrade == 0)
	{
		CISDealPackData();
	}
	
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles RTC global interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
	
}
//-----------------------------------
void EXTI0_IRQHandler(void)
{
	
}

//-----------------------------------
/**
  * @brief  This function handles EXTI2 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{

}
/**
  * @brief  This function handles EXTI3 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
}
/**
  * @brief  This function handles EXTI15_10_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
}
void EXTI9_5_IRQHandler(void)
{
	if((EXTI->PR & EXTI_MP) != RESET)
	{
		EXTI->PR = EXTI_MP;
		g_MPType.mpn++;
	}
}
/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/
void TIM2_IRQHandler(void)	//22US定时器，第一次设置138，第二次开启采集8路信号
{
	if((TIM2->SR & TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM2->SR = (uint16_t)~TIM_IT_Update;  //清除TIMx的中断待处理位:TIM 中断源 	
		
	}
}
//----------------DMA1中断------------------------
void DMA1_Channel1_IRQHandler()
{
	if(DMA_GetITStatus(DMA1_IT_TC1))
	{
		DMA_ClearITPendingBit(DMA1_IT_GL1);
	}
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
