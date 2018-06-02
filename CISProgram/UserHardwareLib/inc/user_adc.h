#ifndef __ADC_H__
#define __ADC_H__
#include "user_includes.h"

//---------------------------------------------
#define	MRM_ADC			ADC_Channel_1
#define	MRMS_ADC		ADC_Channel_3
#define	MRL_ADC			ADC_Channel_5
#define	MRR_ADC			ADC_Channel_6
//---------------------------------------------
#define IN_ADC 			ADC_Channel_10
#define RST_ADC 		ADC_Channel_11  
#define LJ_ADC			ADC_Channel_12 
#define RJ_ADC			ADC_Channel_13 
//---------------------------------------------
#define ADC_CHS			8
//---------------------------------------------
#define ValMRM			0
#define ValMRMS			1
#define ValMRL			2
#define ValMRR			3
#define ValStart		4
#define ValReset		5
#define ValIRLeft		6
#define ValIRRight		7
//----------------------------------------------
extern u16 ADCConvertedValue[ADC_CHS];
//---------------------------------------------
void ADC_Config(void);
void Read_CN(void);
#endif
