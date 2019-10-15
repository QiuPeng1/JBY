/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
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
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Template_Project
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
  * @brief   This function handles NMI exception.
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
  {
  }
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
  {
  }
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
  {
  }
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
  {
  }
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
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

// //SPI中断服务程序,接收主板的控制指令
// void SPI2_IRQHandler(void)
// {

// /*	if(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) != RESET)
// 	{	
// 		spiDataIn = SPI_I2S_ReceiveData(SPI2);
// 		SPI_I2S_SendData(SPI2, 0xff);	//在没准备好前，先发出0xff
// //		gb_needDealSpiDataIn = 1;
// 		switch(spiDataIn)
// 		{
// 			case SPI_COMMAND_FROM_KZB_TO_CTB_ONE_NOTE_START:
// 				gb_enableSample = 1;
// 				sampleIndex = 0;
// 				lastSampleTimes = 0;
// 				break;
// 			case SPI_COMMAND_FROM_KZB_TO_CTB_ONE_NOTE_END:
// 				lastSampleTimes = 200;
// 				break;
// 			default:
// 				break;
// 		}
// 	} */
// }

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

u16 oneSecCnt = 0;
void SysTick_Handler(void)
{
	if (TimingDelay > 0)
	{
		TimingDelay --;
	}
	oneSecCnt ++;
	if(oneSecCnt >= 1000)
	{
		gb_oneSec = 1;
		oneSecCnt = 0;
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
void USART1_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE))
	{
		/* Read one byte from the receive data register */
		fifo_DataIn(UART1_IN_FIFO, USART_ReceiveData(USART1));	//自动清除RXNE标志
		gb_needDealUart1Data = 1;
	}
	else if (USART_GetFlagStatus(USART1, USART_FLAG_TXE))
	{		
		if (fifo_GetCount(UART1_OUT_FIFO) > 0)
		{
			/* Write one byte to the transmit data register */
			USART_SendData(USART1, fifo_DataOut(UART1_OUT_FIFO));	//顺便清除flag_TXE
		}				
		else
		{
		  	/* Disable the USARTy Transmit interrupt */
		  	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);		//实际上，发送为空的标志还在，只是关闭中断
//			gb_uart1IsBusy = 0;
		}    
	}
}

//0.5ms定时器
void TIM5_IRQHandler(void)
{
	u8 i;
	if (TIM_GetFlagStatus(TIM5, TIM_IT_Update))
  {
		TIM_ClearFlag(TIM5, TIM_IT_Update);	
		
		//开启一次采集
		ADOneTime2();
		sampleStartNum ++;		
	}
}

u8 dubiIrCnt = 0;
//DMA中断
void DMA1_Channel1_IRQHandler(void)
{	
	u8 i,j;
	u8 index;
 	if(DMA_GetFlagStatus(DMA1_FLAG_TC1))
  {
		DMA_ClearFlag(DMA1_FLAG_TC1); //清除全部中断标志
		
		dmaEndNum ++;	
		/***************************************
		涡流1 PA0 IN0
		涡流2 PA1 IN1
		涡流3 PA2 IN2
		涡流4 PA3 IN3（预留）
		堵币红外 PA4 IN4 A0A1：00 HW1 01 HW2 10 HW4 11 HW3
		币筒红外、电机定位红外 PA5 IN5 A0A1：00 DJ1 01 DJ3 10 DJ2 11 DJ4
		币筒红外、电机定位红外 PA6 IN6 A0A1：00 DJ5 01 币筒 10 DJ6 11 空
		水位1 PA7 IN7
		水位2 PC4 IN14
		水位3 PB0 IN8
		水位4 PB1 IN9
		水位5 PC0 IN10 
		水位6 PC1 IN11
		adData[0] 涡流1
		adData[1] 涡流2
		adData[2] 涡流3
		adData[3] 涡流4
		adData[4] A0A1：00 HW1 01 HW2 10 HW4 11 HW3
		adData[5] A0A1：00 DJ1 01 DJ3 10 DJ2 11 DJ4
		adData[6] A0A1：00 DJ5 01 币筒 10 DJ6 11 空
		***************************************/
		for (i=0; i<CHANNELS_PER_DMA_GROUP; i++)
		{
			adData[i*2] = (u8)(adcResult[i] >> 8);//低16位		
			adData[i*2+1] = (u8)(adcResult[i] >> 24);//高16位	
		}
		
		//涡流数据保存
		if(needSampleIdleNum > 0)//空载采集
		{
			needSampleIdleNum --;
			
			data[0][dataSampleIndex] = adData[1];//
			data[1][dataSampleIndex] = adData[3];
			data[2][dataSampleIndex] = adData[0];

			dataSampleIndex ++;
			if(gb_sampleBaseValue == 1)
			{
				sampleF1BaseSum += adData[1];
				sampleF2BaseSum += adData[3];
				sampleF3BaseSum += adData[0];
			}
			if(needSampleIdleNum == 0)
			{
				dataLen = dataSampleIndex;
				gb_sampleIdleOver = 1;			
			}
		}
		else
		{			
			DealEddyDataCollect();
		}
		
	}
}

void DealEddyDataCollect(void)
{	
	
	f1Flag <<= 1;
	
	if(adData[1] > f1BaseAdValue + F1_HAVE_COIN_OFFSET)//最前面的涡流 波形上凸
	{
		f1Flag ++;
	}
	
	f3Flag <<= 1;
	if(adData[0] < f3BaseAdValue - F3_HAVE_COIN_OFFSET)//最后面的涡流 波形下凹
	{
		f3Flag ++;
	}
	
	if(gb_f1HaveCoin == 0)
	{
		if((f1Flag&0x0f) == 0x0f)
		{
			gb_f1HaveCoin = 1;			

			if(gb_haveCoin == 0)
			{
				gb_haveCoin = 1;
				
				//开始采集
				dataSampleIndex = 0;
				maxPassEddyTime = 0;			
			}
		}
	}
	else
	{
			if((f1Flag&0x0f) == 0x00)//离开f1
			{
				gb_f1HaveCoin = 0;
				if(gb_haveCoin == 1)
				{
					maxPassEddyTime = MAX_PASS_EDDT_TIME;
				}
			}
	}

	
	if(gb_haveCoin == 1)//
	{
		if(gb_f3HaveCoin == 0)
		{
			if((f3Flag&0x0f) == 0x0f)
			{
				gb_f3HaveCoin = 1;
			}
		}
		else
		{
			if((f3Flag&0x0f) == 0x00)//离开f3
			{
				gb_f3HaveCoin = 0;
				gb_haveCoin = 0;

				dataLen = dataSampleIndex;	
				gb_coinPass = 1;

			}
		}
		if(maxPassEddyTime > 0)
		{
			maxPassEddyTime --;
			if(maxPassEddyTime == 0)
			{
				gb_f3HaveCoin = 0;
				gb_haveCoin = 0;

				gb_coinPass = 1;
				dataLen = dataSampleIndex;				
			}
		}
	}

	if(gb_haveCoin == 1)
	{
		if(dataSampleIndex < DATA_MAX_LEN)
		{			
			data[0][dataSampleIndex] = adData[1];//
			data[1][dataSampleIndex] = adData[3];
			data[2][dataSampleIndex] = adData[0];
			
			//data[2][dataSampleIndex] = adData[2];
			//data[3][dataSampleIndex] = adData[3];
			dataSampleIndex ++;		
		}
	}
}


void ADC1_2_IRQHandler(void)
{
	//if(ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET)
	if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
	{
		//设置标志
		//ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	}
}

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
