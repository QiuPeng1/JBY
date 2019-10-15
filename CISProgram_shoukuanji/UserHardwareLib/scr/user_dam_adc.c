#include "user_dma_adc.h"


DMA_InitTypeDef DMA_InitStruct;
//----------------------------------------------------------------
void DMA_Config(void)
{
//------------------------------USART_ADC----------------------------------
    DMA_DeInit(DMA_CH_USART);   //��DMA��ͨ��x�Ĵ�������Ϊȱʡֵ	
    DMA_InitStruct.DMA_PeripheralBaseAddr 	= (u32)&USART1->DR;    	//DMA�������ַ
	DMA_InitStruct.DMA_MemoryBaseAddr 		= (uint32_t)&UsartDmaSendBuff;		//DMA�ڴ����ַ
	DMA_InitStruct.DMA_DIR 					= DMA_DIR_PeripheralDST;  			//���ݴ��䷽�򣬴������ȡ���͵��ڴ�
	DMA_InitStruct.DMA_BufferSize 			= sizeof(UsartDmaSendBuff); 								//DMAͨ����DMA����Ĵ�С
	DMA_InitStruct.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;  		//�����ַ�Ĵ�������
	DMA_InitStruct.DMA_MemoryInc 			= DMA_MemoryInc_Enable;  			//�ڴ��ַ�Ĵ�������
	DMA_InitStruct.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ16λ
	DMA_InitStruct.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Byte; 		//���ݿ��Ϊ16λ
	DMA_InitStruct.DMA_Mode 				= DMA_Mode_Normal;  				//������ѭ������ģʽ
	DMA_InitStruct.DMA_Priority 			= DMA_Priority_High; 				//DMAͨ�� xӵ�������ȼ�
	DMA_InitStruct.DMA_M2M 					= DMA_M2M_Disable;  				//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CH_USART, &DMA_InitStruct); 
    USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);   
 //----------------------------------------------------------------   
}
//����һ��DMA����
void UsartDMA_Enable(u16 DataLen)
{
    DMA_Cmd(DMA_CH_USART, DISABLE );  //�ر�USART1 TX DMA1 ��ָʾ��ͨ��      
 	DMA_SetCurrDataCounter(DMA_CH_USART,DataLen);//DMAͨ����DMA����Ĵ�С
 	DMA_Cmd(DMA_CH_USART, ENABLE);  //ʹ��USART1 TX DMA1 ��ָʾ��ͨ�� 
}



