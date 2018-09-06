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

// //SPI�жϷ������,��������Ŀ���ָ��
// void SPI2_IRQHandler(void)
// {

// /*	if(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) != RESET)
// 	{	
// 		spiDataIn = SPI_I2S_ReceiveData(SPI2);
// 		SPI_I2S_SendData(SPI2, 0xff);	//��û׼����ǰ���ȷ���0xff
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
		fifo_DataIn(UART1_IN_FIFO, USART_ReceiveData(USART1));	//�Զ����RXNE��־
		gb_needDealUart1Data = 1;
	}
	else if (USART_GetFlagStatus(USART1, USART_FLAG_TXE))
	{		
		if (fifo_GetCount(UART1_OUT_FIFO) > 0)
		{
			/* Write one byte to the transmit data register */
			USART_SendData(USART1, fifo_DataOut(UART1_OUT_FIFO));	//˳�����flag_TXE
		}				
		else
		{
		  	/* Disable the USARTy Transmit interrupt */
		  	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);		//ʵ���ϣ�����Ϊ�յı�־���ڣ�ֻ�ǹر��ж�
//			gb_uart1IsBusy = 0;
		}    
	}
}

//0.5ms��ʱ��
void TIM5_IRQHandler(void)
{
	u8 i;
	if (TIM_GetFlagStatus(TIM5, TIM_IT_Update))
  {
		TIM_ClearFlag(TIM5, TIM_IT_Update);	
		
		//����һ�βɼ�
		ADOneTime2();
		sampleStartNum ++;		
	}
}

u8 dubiIrCnt = 0;
//DMA�ж�
void DMA1_Channel1_IRQHandler(void)
{	
	u8 i,j;
	u8 index;
 	if(DMA_GetFlagStatus(DMA1_FLAG_TC1))
  {
		DMA_ClearFlag(DMA1_FLAG_TC1); //���ȫ���жϱ�־
		
		dmaEndNum ++;	
		/***************************************
		����1 PA0 IN0
		����2 PA1 IN1
		����3 PA2 IN2
		����4 PA3 IN3��Ԥ����
		�±Һ��� PA4 IN4 A0A1��00 HW1 01 HW2 10 HW4 11 HW3
		��Ͳ���⡢�����λ���� PA5 IN5 A0A1��00 DJ1 01 DJ3 10 DJ2 11 DJ4
		��Ͳ���⡢�����λ���� PA6 IN6 A0A1��00 DJ5 01 ��Ͳ 10 DJ6 11 ��
		ˮλ1 PA7 IN7
		ˮλ2 PC4 IN14
		ˮλ3 PB0 IN8
		ˮλ4 PB1 IN9
		ˮλ5 PC0 IN10 
		ˮλ6 PC1 IN11
		adData[0] ����1
		adData[1] ����2
		adData[2] ����3
		adData[3] ����4
		adData[4] A0A1��00 HW1 01 HW2 10 HW4 11 HW3
		adData[5] A0A1��00 DJ1 01 DJ3 10 DJ2 11 DJ4
		adData[6] A0A1��00 DJ5 01 ��Ͳ 10 DJ6 11 ��
		***************************************/
		for (i=0; i<CHANNELS_PER_DMA_GROUP; i++)
		{
			adData[i*2] = (u8)(adcResult[i] >> 8);//��16λ		
			adData[i*2+1] = (u8)(adcResult[i] >> 24);//��16λ	
		}
		
		//�������ݱ���
		if(needSampleIdleNum > 0)//���زɼ�
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
	
	if(adData[1] > f1BaseAdValue + F1_HAVE_COIN_OFFSET)//��ǰ������� ������͹
	{
		f1Flag ++;
	}
	
	f3Flag <<= 1;
	if(adData[0] < f3BaseAdValue - F3_HAVE_COIN_OFFSET)//���������� �����°�
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
				
				//��ʼ�ɼ�
				dataSampleIndex = 0;
				maxPassEddyTime = 0;			
			}
		}
	}
	else
	{
			if((f1Flag&0x0f) == 0x00)//�뿪f1
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
			if((f3Flag&0x0f) == 0x00)//�뿪f3
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
		//���ñ�־
		//ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	}
}

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
