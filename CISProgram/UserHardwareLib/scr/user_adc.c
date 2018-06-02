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
	
	
	/**ADC1配置**********************************************************************************/	
	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值		
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//模数转换工作在扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发转换关闭
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = ADC_CHS;//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1,&ADC_InitStructure);//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
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
	DMA_DeInit(DMA1_Channel1);   //将DMA的通道x寄存器重设为缺省值							
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (u32)&ADC1->DR;    				//DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr 		= (uint32_t)ADCConvertedValue;			//DMA内存基地址
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_PeripheralSRC;  			//数据传输方向，从外设读取发送到内存
	DMA_InitStructure.DMA_BufferSize 			= ADC_CHS; 								//DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;  		//外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;  			//内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_HalfWord;  //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_HalfWord; 		//数据宽度为16位
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Circular;  				//工作在循环缓存模式
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_High; 				//DMA通道 x拥有中优先级
	DMA_InitStructure.DMA_M2M 					= DMA_M2M_Disable;  				//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);
/******************************************************************************/	
	ADC_DMACmd(ADC1, ENABLE);// 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1	
	ADC_ResetCalibration(ADC1);	//使能复位校准  	 	
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束	
	ADC_StartCalibration(ADC1);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束		
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);  //连续转换开始，ADC通过DMA方式不断的更新RAM区。
/*********************************************************************/	
}



