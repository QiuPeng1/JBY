#include "user_dma_adc.h"


DMA_InitTypeDef DMA_InitStruct;
//----------------------------------------------------------------
void DMA_Config(void)
{
//------------------------------USART_ADC----------------------------------
    DMA_DeInit(DMA_CH_USART);   //将DMA的通道x寄存器重设为缺省值	
    DMA_InitStruct.DMA_PeripheralBaseAddr 	= (u32)&USART1->DR;    	//DMA外设基地址
	DMA_InitStruct.DMA_MemoryBaseAddr 		= (uint32_t)&UsartDmaSendBuff;		//DMA内存基地址
	DMA_InitStruct.DMA_DIR 					= DMA_DIR_PeripheralDST;  			//数据传输方向，从外设读取发送到内存
	DMA_InitStruct.DMA_BufferSize 			= sizeof(UsartDmaSendBuff); 								//DMA通道的DMA缓存的大小
	DMA_InitStruct.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;  		//外设地址寄存器不变
	DMA_InitStruct.DMA_MemoryInc 			= DMA_MemoryInc_Enable;  			//内存地址寄存器递增
	DMA_InitStruct.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;  //数据宽度为16位
	DMA_InitStruct.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Byte; 		//数据宽度为16位
	DMA_InitStruct.DMA_Mode 				= DMA_Mode_Normal;  				//工作在循环缓存模式
	DMA_InitStruct.DMA_Priority 			= DMA_Priority_High; 				//DMA通道 x拥有中优先级
	DMA_InitStruct.DMA_M2M 					= DMA_M2M_Disable;  				//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CH_USART, &DMA_InitStruct); 
    USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);   
 //----------------------------------------------------------------   
}
//开启一次DMA传输
void UsartDMA_Enable(u16 DataLen)
{
    DMA_Cmd(DMA_CH_USART, DISABLE );  //关闭USART1 TX DMA1 所指示的通道      
 	DMA_SetCurrDataCounter(DMA_CH_USART,DataLen);//DMA通道的DMA缓存的大小
 	DMA_Cmd(DMA_CH_USART, ENABLE);  //使能USART1 TX DMA1 所指示的通道 
}



