#ifndef __SENSOR_H__
#define __SENSOR_H__
#include "user_includes.h"
//---------------------------------------------
#define SENSOR_NORMAL    0
#define SENSOR_BAD		 1
//-------------�������𻵱�־��������
#define SENSOR_ERR_NONE  	0x00000000      //�ޱ�����
#define SENSOR_ERR_IN  		0x00000001      //�������
#define SENSOR_ERR_LJ  		0x00000002		//������Թܻ�
#define SENSOR_ERR_RJ  		0x00000004		//�����ҶԹܻ�
#define SENSOR_ERR_RST  	0x00000008		//����Թܻ�
#define SENSOR_ERR_MP  		0x00000010		//MP������
#define SENSOR_ERR_KEY  	0x00000020		//������
#define SENSOR_ERR_CX1  	0x00000040		//����1��
#define SENSOR_ERR_CX2  	0x00000080		
#define SENSOR_ERR_CX3  	0x00000100		
#define SENSOR_ERR_UV  		0x00000200		//UV��
#define SENSOR_ERR_VOICE  	0x00000400		//������


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
