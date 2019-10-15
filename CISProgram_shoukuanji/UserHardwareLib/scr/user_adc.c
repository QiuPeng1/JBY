#include "user_adc.h"


GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
//---------------------------------------------------------------
u16 ADCConvertedValue[ADC_CHS];
/***************************************************/
void ADC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	/**ADC1����**********************************************************************************/	
	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ		
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//ģ��ת��������ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�ⲿ����ת���ر�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = ADC_CHS;//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1,&ADC_InitStructure);//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
/******************************************************************************/
	ADC_RegularChannelConfig(ADC1, MRM_ADC,   	1, 	ADC_SampleTime_239Cycles5);//
	ADC_RegularChannelConfig(ADC1, MRMS_ADC,   	2,  ADC_SampleTime_239Cycles5);//
	ADC_RegularChannelConfig(ADC1, MRL_ADC,   	3,  ADC_SampleTime_239Cycles5);//	
	ADC_RegularChannelConfig(ADC1, MRR_ADC,  	4,	ADC_SampleTime_239Cycles5);//
	ADC_RegularChannelConfig(ADC1, IN_ADC,   	5, 	ADC_SampleTime_239Cycles5);//
	ADC_RegularChannelConfig(ADC1, RST_ADC,   	6, 	ADC_SampleTime_239Cycles5);//
	ADC_RegularChannelConfig(ADC1, LJ_ADC,   	7, 	ADC_SampleTime_239Cycles5);//
	ADC_RegularChannelConfig(ADC1, RJ_ADC,  	8, 	ADC_SampleTime_239Cycles5);//
/******************************************************************************/	
	DMA_DeInit(DMA1_Channel1);   //��DMA��ͨ��x�Ĵ�������Ϊȱʡֵ							
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (u32)&ADC1->DR;    				//DMA�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr 		= (uint32_t)ADCConvertedValue;			//DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_PeripheralSRC;  			//���ݴ��䷽�򣬴������ȡ���͵��ڴ�
	DMA_InitStructure.DMA_BufferSize 			= ADC_CHS; 								//DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;  		//�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;  			//�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_HalfWord;  //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_HalfWord; 		//���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Circular;  				//������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_High; 				//DMAͨ�� xӵ�������ȼ�
	DMA_InitStructure.DMA_M2M 					= DMA_M2M_Disable;  				//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);
/******************************************************************************/	
	ADC_DMACmd(ADC1, ENABLE);// ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  	 	
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����		
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);  //����ת����ʼ��ADCͨ��DMA��ʽ���ϵĸ���RAM����
/*********************************************************************/	
}



