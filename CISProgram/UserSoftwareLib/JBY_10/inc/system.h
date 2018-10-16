/***************************************************************************

版本  日期      修改内容  修改人
V2.7  20181016  1、创建     Q
****************************************************************************/

/*防止重复引用 */
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

//#define VC_PLUS_PLUS

//gd
typedef unsigned char  bit;
typedef int            I32;
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

enum
{
	ERROR_NONE,
	ERROR_F1_ERROR,
	ERROR_F2_ERROR,
	ERROR_CONTINUS_COIN,
};

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define NEED_UPGRADE_FLAG 0x1127

#define REAL_IR_NUM 21
#define BOOT_APP
#define LENGTH_HAVENOTE_VALUE_THRES 10
#define LENGTH_HAVENOTE_NUM_THRES 3
#define LENGTH_IR_CHANNEL_NUM (REAL_IR_NUM+1) //21路测长 1路码盘

#define VERSION  "V2.7"


typedef enum
{
	NORMAL,
	DU_BI,
	DISP_VERSION,
	SENSOR_VIEW,
	SET_JUDGE_PARA,
	LAO_HUA,
	SET_TIME,
	MOTOR_SET,
	NOTEPASS_INFO,
	SELFCHECK,
	USER_PARA,
	PARA_VIEW,
	BATCH_STOP,
	TEST_SWITCH,
	SUSP_STOP,
	MENU1,
	MENU11,
	MENU12,
	MENU13,
	MENU14,
	MENU15,
	MENU16,
	MENU17,
	MENU18,
	STATE_NUM,
}STATE_T;

//enum
//{
//	INDEX_RMB = 0,//0 - currency0
//	INDEX_USD,//1
//	INDEX_EUR,//2
//	INDEX_JPY,//3
//	INDEX_GBP,//4
//	INDEX_HKD,//5
//	INDEX_AUD,//6
//	INDEX_CAD,//7
//	INDEX_SGD,//0 - currency1
//	INDEX_KRW,//1
//	INDEX_TWD,//2
//	INDEX_RUB,//3
//  INDEX_GHC,//4
//	INDEX_UAH,//5
//	INDEX_NGN,//6
//	INDEX_ALL,//7
//	INDEX_MKD,//0 - currency2
//	INDEX_MOP,//1
//	INDEX_CHF,//2
//	INDEX_SEK,//3
//	INDEX_KZT,//4
//	INDEX_TRY,//5
//	INDEX_INR,//6
//	INDEX_VND,//7
//	INDEX_MYR,//0 - currency3
//	INDEX_BRL,//1
//	INDEX_TJS,//2
//	INDEX_CNY,//3
//	INDEX_BGN,//4
//	INDEX_MAD,//5
//	NOTE_NUM
//};

enum
{
	ERROR_FEED_SENSOR = 0x01,
	ERROR_IR1_ON,//1
	ERROR_IR2_ON,//2
	ERROR_IR3_ON,//3
	ERROR_IR4_ON,//4
	ERROR_IR1_OFF,//5
	ERROR_IR2_OFF,//6
	ERROR_IR3_OFF,//7
	ERROR_IR4_OFF,//8
	ERROR_MOTOR_OR_MP,//9
	ERROR_IR_JAM,//10
	ERROR_MT,//11
	ERROR_LEFT_MR,//12
	ERROR_RIGHT_MR,//13
};
enum
{
	ERROR_JAM1 = 20,
	ERROR_JAM2,
	ERROR_MOTOR_STOP_NOTEPASS,
};
enum
{
	ERROR_WIDTH = 30,
	ERROR_MG_DATALEN,
	ERROR_HALF_NOTE,
	ERROR_WORN_NOTE,//左右红外差距过大
	ERROR_CHAIN_NOTE,
	ERROR_DOUBLE_NOTE,
	ERROR_AQX_NUM,
	ERROR_RMB100_05_MG_ERR,
	ERROR_RMB100_15_MG_ERR,
	ERROR_RMB50_MG_ERR,
	ERROR_RMB10_20_MG_ERR,
	ERROR_RMB10_MG_ERR,
	ERROR_RMB20_MG_ERR,
	ERROR_RMB10_20_MG_UNKNOWN,
};

//enum
//{
//	INDEX_USD,
//	INDEX_EUR,
//	ALL_NOTE_TYPE,
//};


#ifdef VC_PLUS_PLUS

	#define DRAW_STATE

	#define LEFT_AXIS 0

	#define DRAW_CROSS_ALL
	//#define DRAW_SCOPE
	#define DRAW_AVG
	//#define DRAW_AVG2

//	#define DRAW_FVT_10AND20

	#define DRAW_CROSS_CONNECT

	#ifndef __USERTYPE_H__
		#define __USERTYPE_H__
	
		typedef  unsigned char uchar;
		typedef  unsigned int uint;
		
		typedef unsigned char u8;
		typedef unsigned char U8;
		typedef char s8;
		typedef char S8;
		typedef unsigned char uint8;
		
		
		typedef unsigned short u16;
		typedef unsigned short uint16;
		typedef unsigned short U16;
		typedef short s16;
		typedef short S16;
		
		typedef unsigned int u32;
		typedef unsigned int uint32;
		typedef unsigned int U32;
		typedef int s32;
		typedef int S32;
		typedef int I32;
		
		#define ArrayLen(x) (sizeof(x)/sizeof(x[0]))
		#define MAX(a, b) (((a) > (b)) ? (a) : (b))
		#define MIN(a, b) (((a) < (b)) ? (a) : (b))
		#define RowNum(x) (sizeof(x)/sizeof(x[0]))
		#define ColNum(x) (sizeof(x[0]))
		#define HighByte(x) ((u8)(x>>8))
		#define LowByte(x) ((u8)(x))
		#define BIN_DATA(a,b,c,d,e,f,g,h) (a<<7 | b<<6 | c<<5 | d<<4 | e<<3 | f<<2 | g<<1 | h<<0)
		
		#define HUAN_HANG_STR "\r\n"	
	#endif
	
#else
	
	/*包含文件 */
	#include "stm32f10x.h"
	#include "math.h"
	
//	typedef unsigned char bit;

	
//	#define USE_IWDG
	
	//主板版本配置
	#define nop() 
	#define _nop_()
	#define ArrayLen(x) (sizeof(x)/sizeof(x[0]))
	#define MAX(a, b) (((a) > (b)) ? (a) : (b))
	#define MIN(a, b) (((a) < (b)) ? (a) : (b))
	#define RowNum(x) (sizeof(x)/sizeof(x[0]))
	#define ColNum(x) (sizeof(x[0]))
	#define HighByte(x) ((u8)(x>>8))
	#define LowByte(x) ((u8)(x))
	#define BIN_DATA(a,b,c,d,e,f,g,h) (a<<7 | b<<6 | c<<5 | <<4 | e<<3 | f<<2 | g<<1 | h<<0)
	
	
	/* Private typedef -----------------------------------------------------------*/
	/* Private define ------------------------------------------------------------*/
	#define RAM_BASE       0x20000000
	#define RAM_BB_BASE    0x22000000
	 
	/* Private macro -------------------------------------------------------------*/
	#define  Var_ResetBit_BB(VarAddr, BitNumber)    \
	          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)
	   
	#define Var_SetBit_BB(VarAddr, BitNumber)       \
	          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)
	
	#define Var_GetBit_BB(VarAddr, BitNumber)       \
	          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))

#endif
#endif
