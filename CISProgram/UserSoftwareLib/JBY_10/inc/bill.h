/***************************************************************************

****************************************************************************/

/*防止重复引用 */
#ifndef BILL_H
#define BILL_H

#include "system.h"
#include "mr.h"
/*将外部包含和内部包含分开*/
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

//#define DRAW_STATE1

#define BILL_INDEX_USD
#define BILL_INDEX_EUR
#define BILL_INDEX_TRY
#define BILL_INDEX_RUB
#define BILL_INDEX_IQD

#define BILL_INDEX_SAR
#define BILL_INDEX_AED
#define BILL_INDEX_GBP
#define BILL_INDEX_ARS
#define BILL_VERSION "V1.0.5"

//---------------------------------------------------------------------
//全局常量定义
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//全局类型定义
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
	INDEX_HKD,	//港币
	INDEX_AUD,
	INDEX_CAD,

	INDEX_SGD,	//8新加坡
	INDEX_KRW,	//9韩国
	INDEX_TWD,	//10台湾
	INDEX_RUB,	//11卢布
	INDEX_GHC,	//12加纳塞第
	INDEX_UAH,	//13乌克兰
	INDEX_NGN,	//14尼日利亚
	INDEX_ALL,	//15阿尔巴尼亚

	INDEX_MKD,	//16马其顿第纳尔
	INDEX_MOP,  //17中国澳门
	INDEX_CHF,	//18瑞士法郎
	INDEX_SEK,	//19瑞典克郎
	INDEX_KZT,  //20哈萨克斯坦
	INDEX_TRY,  //21土耳其
	INDEX_INR,	//22印度
	INDEX_VND,	//23越南,

	INDEX_MYR,	//24马来西亚
	INDEX_BRL,	//25巴西
	INDEX_TJS,	//26
	INDEX_CNY,	//27
	INDEX_BGN,  //28保加利亚
	INDEX_MAD,  //29摩洛哥
	INDEX_LYD, //30利比亚
	INDEX_LAK,	//31
	INDEX_ZAR,	//32南非
	INDEX_KES,	//33
	INDEX_ARS,	//34阿根廷
	INDEX_THB,	//35泰铢
	INDEX_EGP,	//36埃及镑
	INDEX_LKR,	//37斯里兰卡
	INDEX_IDR,	//38印尼
	INDEX_ILS,	//39以色列
	INDEX_AFN, 	//40阿富汗
	INDEX_JOD, 	//41约旦
	INDEX_IQD, 	//42伊拉克
	INDEX_LBP, 	//43黎巴嫩
	INDEX_SAR, 	//43沙特
	INDEX_AED, 	//43阿联酋
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
#define PROCESS_IQD
//---------------------------------------------------------------------
//全局变量，可以被外部程序直接访问
//---------------------------------------------------------------------
#define IRAD_DATA_RESIZE_W 40
#define IRAD_DATA_RESIZE_H 16
#define IRAD_FVT_DIM		(IRAD_DATA_RESIZE_W*IRAD_DATA_RESIZE_H)
BILL_EXT_PARA u8 lengthData_Tmp2[IRAD_FVT_DIM+100];

#define COLOR_DATA_NUM		3
#define COLOR_DATA_RESIZE  72

#define COLOR_FIV_DIM		3
BILL_EXT_PARA u16 colorData_tmp[12][COLOR_DATA_RESIZE+8];

BILL_EXT_PARA int colorFvtTotal[COLOR_DATA_RESIZE*COLOR_FIV_DIM*COLOR_DATA_NUM];

BILL_EXT_PARA int projH[900];
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
BILL_EXT_PARA u8 mgFvtFlag;


BILL_EXT_PARA u16 iradImgW;
BILL_EXT_PARA u16 iradImgH;
//BILL_EXT_PARA I32 projH[IRAD_DATA_MAX_LEN];
//BILL_EXT_PARA I32 projH1[IRAD_DATA_MAX_LEN];

/*公开的过程/函数*/
//---------------------------------------------------------------------
//函数介绍
//---------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

BILL_EXT_FUNC u8 billRGB_Judge(int noteType);

BILL_EXT_FUNC u8 billUV_Judge
(
	void		//参数含义
);
BILL_EXT_FUNC u8 billIrad_Judge(u8 *lengthData_Tmp, int noteType);
BILL_EXT_FUNC u8 billMG_Judge(int noteType);
#ifdef __cplusplus
}
#endif
#endif
