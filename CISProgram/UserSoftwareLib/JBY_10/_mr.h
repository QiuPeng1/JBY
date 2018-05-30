/***************************************************************************

****************************************************************************/
//防止重复引用
#ifndef _MR_H_
#define _MR_H_

//包含文件
#ifdef __cplusplus
	#include "..\DebugDraw.h"
#endif
#include "system.h"

#ifdef VC_PLUS_PLUS
	#define _EEPROM_H_
	u8 * const ctmStr[]={"0000","DDDD","SSSS","DSDS","DDSS","3333","----"};
#endif

#include "mr.h"
//#include "eeprom.h"
//#include "flash.h"

#define CIS_LEN 183 

float const MGSENSOR_LOC[6][2] = 
{
	26.5,41.5,
	41.5,56.5,
	56.5,71.5,
	111.5,126.5,
	126.5,141.5,
	141.5, 156.5,
};
//30 75 95 115 160 91.5  
enum
{
	GZH_X_START = 4,
	GZH_Y_START = 13,
	GZH_W = 30,
	GZH_H = 10,

	GZH_50_X_START = 4,
	GZH_50_Y_START = 13,
	GZH_50_W = 29,
	GZH_50_H = 10,

	GZH_20_X_START = 5,
	GZH_20_Y_START = 13,
	GZH_20_W = 29,
	GZH_20_H = 10,

	GZH_10_X_START = 4,
	GZH_10_Y_START = 13,
	GZH_10_W = 29,
	GZH_10_H = 10,

	GZH_5_X_START = 4,
	GZH_5_Y_START = 13,
	GZH_5_W = 29,
	GZH_5_H = 10,

	CXYM_X_START = 40,
	CXYM_Y_START = 22,
	CXYM_W = 25,
	CXYM_H = 23,

	CXYM_50_X_START = 18,
	CXYM_50_Y_START = 12,
	CXYM_50_W = 34,
	CXYM_50_H = 40,

	PINYIN_X_START = 14,
	PINYIN_Y_START = 5,
	PINYIN_W = 30,
	PINYIN_H = 12,
};

//---------------------------------------------------------------------
//管脚及宏函数定义
//---------------------------------------------------------------------
#define TRACE(x)   
u8 const HEAD_MR_HIGH_VAL = 75;
//u8 const HEAD_MR_LOW_VAL  = 1;
u8 const MIN_HEAD_MR_WIDTH_OF_05_23XIANG_1 = 3;
u8 const MIN_HEAD_MR_WIDTH_OF_05_01XIANG_1 = 3;

u8 const MIN_HEAD_MR_WIDTH_OF_05_23XIANG_2 = 15;
u8 const MIN_HEAD_MR_WIDTH_OF_05_01XIANG_2 = 20;
	
u8 const MIN_HEAD_MR_WIDTH_OF_15 = 3;
	
u8 const MIN_MIDDLE_MR_HIGH_VAL = 100;
u8 const MIN_MIDDLE_MR_HIGH_VAL_100 = 160;
u8 const MIN_MIDDLE_MR_HIGH_VAL_NOT_100 = 160;
u8 const MAX_MIDDLE_MR_HIGH_VAL_100 = 200;
u8 test;
u8 speedIsSlow;
#define MIN_BO_FENG_DIS_OF_100 48

#define GZH_MR_START_POS 5

//#define STANDARD_SAMPLE_NUM_PER_FALLMP  15
//#define STANDARD_SAMPLE_NUM_PER_FALLMP  13//康亿1680 20150617
#define STANDARD_SAMPLE_NUM_PER_FALLMP  15 //老孔1680 20151209

u16 const MIN_MIDDLE_MR_WIDTH_100 = ((u16)(STANDARD_SAMPLE_NUM_PER_FALLMP * 40));
u16 const MIN_MIDDLE_MR_WIDTH_20  = ((u16)(STANDARD_SAMPLE_NUM_PER_FALLMP * 30));
u16 const MIN_MIDDLE_MR_WIDTH_5  = ((u16)(STANDARD_SAMPLE_NUM_PER_FALLMP * 20));

u8 headMrStartPos = 0;

u8 m_gzhMrIndex = 0;
u16 frontGzhStartPos, frontGzhEndPos;
u16 backGzhStartPos, backGzhEndPos;
	
u8 const MAX_LOW_GZH_MR2_VAL[] = {10,10,10,10,10,40,40,40};
u8 const MAX_LOW_HEAD_MR2_VAL[] = {10,10,10,10,10,10,10,10};

enum
{
	MIN_CTM_INTERVAL_VAL_OF_100 = 50,
	MAX_CTM_INTERVAL_VAL_OF_100 = 70,
	MAX_CTM_INTERVAL_ERROR_NUM = 2,
	MIN_HD_INTERVAL_VAL_OF_100 = 48,
	MAX_HD_INTERVAL_VAL_OF_100 = 100,
	MIN_CTM_INTERVAL_VAL_OF_100_2 = 40,
};

#define MIN_DIS_OF_50 (STANDARD_SAMPLE_NUM_PER_FALLMP*2)

//---------------------------------------------------------------------
//类型定义
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//常量定义
//---------------------------------------------------------------------
static u8 const HD_STANDARD_VAL[] = {1,0,1,1,0};
enum
{
	DIRECT_0,		//平的
	DIRECT_INC,		//上升
	DIRECT_DEC,		//下降
};

u8 const MIN_CTM_WIDTH_100 = 3;
u8 const MIN_CTM_WIDTH_NOT_100 = 2;

u8 *pdGzhMrData;

//#define MIN_GZH_MR_VAL 150
#define MIN_GZH_MR_VAL 110

#define GAN_RAO_CTM_DIV  12
enum
{
	CTM_DOUBLE_STANDARD = 7,	//磁条码前后进行比较的（1+2/x）的x的大小
	CTM_LITTLE_DOUBLE_STANDARD = 5,	//专门用于判断50元的磁条码的（1+1/x）的x的大小
	RESERVED
};
#define MIN_CTM_TIME 15
#define SHIFT_NUM 2
#define MIN_CTM_TIME2 5
#define MIN_GZH_DIFF_VAL 25
enum
{
	LOWEST_MIN_LOW_DELTA = 15,		//小于2边时，小于最小值的限度
	LOWEST_MAX_LOW_DELTA = 40,		//小于2边时，小于最大值的限度
	MIDDLE_MAX_HIGH_DELTA = 65,		//小于1边时，小于最大值的限度
	MAX_11_NUM = 4,
	MIN_NUM = 7,
	MAX_LOW_VAL = 130,
	MAX_LOW_VAL_V = 100,
	MAX_LOW_VAL_L = 80,
	MIN_01 = 30,
	MIN_02 = 60
};
enum
{
	MAX_HD_ERROR_NUM = 2,
	MIN_CONTINOUS_OK_NUM = 11,
};

u8 const diffOf10And20 = 27;


#define CTM_START_INDEX 1


u8 aqxCodeNum;

// #define MAX_MP_NUM_ONE_NOTE 150
// u16 mpPos[MAX_MP_NUM_ONE_NOTE];
// u16 mpNum;

//u8 aqxCodeScale[MAX_AQX_WAVE_NUM][5];

//---------------------------------------------------------------------
//引用的全局变量及输入函数
//---------------------------------------------------------------------


static u8 widthNoteType = WID_ARTI;

//---------------------------------------------------------------------
//文件内部模块私有变量
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//文件内部模块私有函数
//---------------------------------------------------------------------
void GetAqxWave(u8 *d,u16 start,u16 end,u8 waveThres,u8 combineDis);
u8 JudgeAqxCode(u16 *aqxCode,u8 n,u16 *coreCode,u8 coreCodeNum,u8 matchRange);
void PredealMpCount(void);
#endif

