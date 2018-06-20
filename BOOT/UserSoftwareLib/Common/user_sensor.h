#ifndef __SENSOR_H__
#define __SENSOR_H__
#include "user_includes.h"
//---------------------------------------------
#define SENSOR_NORMAL    0
#define SENSOR_BAD		 1
//-------------传感器损坏标志常量定义
#define SENSOR_ERR_NONE  	0x00000000      //无报警。
#define SENSOR_ERR_IN  		0x00000001      //进钞光耦坏
#define SENSOR_ERR_LJ  		0x00000002		//计数左对管坏
#define SENSOR_ERR_RJ  		0x00000004		//计数右对管坏
#define SENSOR_ERR_RST  	0x00000008		//清零对管坏
#define SENSOR_ERR_MP  		0x00000010		//MP或电机坏
#define SENSOR_ERR_KEY  	0x00000020		//按键坏
#define SENSOR_ERR_CX1  	0x00000040		//磁性1坏
#define SENSOR_ERR_CX2  	0x00000080		
#define SENSOR_ERR_CX3  	0x00000100		
#define SENSOR_ERR_UV  		0x00000200		//UV坏
#define SENSOR_ERR_VOICE  	0x00000400		//语音坏


void OutBill(void);
void CheckReset(void);
void CheckStar(void);
//--------------------------------------------
void LenAnalysis(void);
void CTAnalysis(void);
void UVAnalysis(void);
void Read_CN(void);
void Read_Len(void);
void Test(void);
/*************************************************/
void DealJS(void);
void StartRun(void);
/**************************************************/
#endif
