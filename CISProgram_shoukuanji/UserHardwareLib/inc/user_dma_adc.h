#ifndef __DMA_ADC_H__
#define	__DMA_ADC_H__   
#include "user_includes.h"
	    	
#define DMA_CH_ADC      DMA1_Channel1			
#define DMA_CH_USART    DMA1_Channel4	

void DMA_Config(void);//≈‰÷√DMA1_CHx
void UsartDMA_Enable(u16);
		   
#endif
