/***************************************************************************

****************************************************************************/

/*��ֹ�ظ����� */
#ifndef BILL_H
#define BILL_H

#include "system.h"
#include "mr.h"
/*���ⲿ�������ڲ������ֿ�*/
#ifdef _BILL_H_
    #define BILL_EXT_PARA
    #define BILL_EXT_FUNC
#else
	#ifdef __cplusplus
		#define BILL_EXT_PARA  EXTERN_C
		#define BILL_EXT_FUNC  extern
	#else
		#define BILL_EXT_PARA  extern
		#define BILL_EXT_FUNC  extern		
	#endif
#endif

#define BILL_VERSION "V1.0.5"

//---------------------------------------------------------------------
//ȫ�ֳ�������
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//ȫ�����Ͷ���
//---------------------------------------------------------------------
typedef struct
{
	u8 index;
	u8 val;
	u8 beforeVal;
	u8 afterVal;
	u8 mask;
	u8 ave;
	u16 arv;
	u16 pos;
	u16 fengVal;
	u16 blackCount;
}POS_INFOR;


typedef struct FvtRes
{
	u8 count;
	u8 noteClass;
	double dis;	
}FvtRes;

enum
{
	INDEX_RMB = 0,
	INDEX_USD,
	INDEX_EUR,
	INDEX_JPY,
	INDEX_GBP,
	INDEX_HKD,	//�۱�
	INDEX_AUD,
	INDEX_CAD,

	INDEX_SGD,	//8�¼���
	INDEX_KRW,	//9����
	INDEX_TWD,	//10̨��
	INDEX_RUB,	//11¬��
	INDEX_GHC,	//12��������
	INDEX_UAH,	//13�ڿ���
	INDEX_NGN,	//14��������
	INDEX_ALL,	//15����������

	INDEX_MKD,	//16����ٵ��ɶ�
	INDEX_MOP,  //17�й�����
	INDEX_CHF,	//18��ʿ����
	INDEX_SEK,	//19������
	INDEX_KZT,  //20������˹̹
	INDEX_TRY,  //21������
	INDEX_INR,	//22ӡ��
	INDEX_VND,	//23Խ��,

	INDEX_MYR,	//24��������
	INDEX_BRL,	//25����
	INDEX_TJS,	//26
	INDEX_CNY,	//27
	INDEX_BGN,  //28��������
	INDEX_MAD,  //29Ħ���
	INDEX_LYD, //30������
	INDEX_LAK,	//31
	INDEX_ZAR,	//32�Ϸ�
	INDEX_KES,	//33
	INDEX_ARS,	//34����͢
	INDEX_THB,	//35̩��
	INDEX_EGP,	//36������
	INDEX_LKR,	//37˹������
	INDEX_IDR,	//38ӡ��
	INDEX_ILS,	//39��ɫ��
	INDEX_AFN, //40������
	NOTE_NUM
};
#define PROCESS_GBP
#define PROCESS_INR
#define PROCESS_MYR
#define PROCESS_RUB
#define PROCESS_USD
#define PROCESS_CNY
#define PROCESS_KES
#define PROCESS_EUR
#define PROCESS_TRY
#define PROCESS_TWD
#define PROCESS_ARS
#define PROCESS_THB
#define PROCESS_EGP
#define PROCESS_BRL
#define PROCESS_LKR
#define PROCESS_ZAR
#define PROCESS_IDR
#define PROCESS_VND
#define PROCESS_ILS
#define PROCESS_AFN

//---------------------------------------------------------------------
//ȫ�ֱ��������Ա��ⲿ����ֱ�ӷ���
//---------------------------------------------------------------------
#define IRAD_DATA_RESIZE_W 40
#define IRAD_DATA_RESIZE_H 16
#define IRAD_FVT_DIM		(IRAD_DATA_RESIZE_W*IRAD_DATA_RESIZE_H)
BILL_EXT_PARA u8 lengthData_Tmp2[IRAD_FVT_DIM+100];

#define COLOR_DATA_RESIZE  48
BILL_EXT_PARA u8 colorData_tmp[12][COLOR_DATA_RESIZE+16];
BILL_EXT_PARA short colorFvtTotal[COLOR_DATA_RESIZE*2*4];


BILL_EXT_PARA u8 billIsFake;
BILL_EXT_PARA u8 billValue;
BILL_EXT_PARA u8 billFlag;
BILL_EXT_PARA u8 billUVFvt;
BILL_EXT_PARA u8 g_flag;
BILL_EXT_PARA u8 billIradMask;

BILL_EXT_PARA u8 irJudgeValue;
BILL_EXT_PARA u8 irJudgeFlag;
BILL_EXT_PARA u8 colorJudgeValue;
BILL_EXT_PARA u8 colorJudgeFlag;
BILL_EXT_PARA u8 g_IradRes;
BILL_EXT_PARA u8 noteType;

//BILL_EXT_PARA I32 projH[IRAD_DATA_MAX_LEN];
//BILL_EXT_PARA I32 projH1[IRAD_DATA_MAX_LEN];

/*�����Ĺ���/����*/
//---------------------------------------------------------------------
//��������
//---------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

BILL_EXT_FUNC u8 billRGB_Judge
(
	void		//��������
);

BILL_EXT_FUNC u8 billUV_Judge
(
	void		//��������
);

u8 billIrad_Judge
(
	u8 *dataIrad_Tmp		//��������
);

#ifdef __cplusplus
}
#endif
#endif
