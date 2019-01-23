/***************************************************************************

版本  日期      修改内容  修改人
V2.7  20181016  1、创建     Q
V2.8  20181019  1、增加误报采集
				2、增加伊拉克
V2.9 20181021   1、增加沙特SAR
				2、更改图片库地址
				3、增加阿联酋AED
V2.9 20181021   1、增加英镑GBP			
V3.1 20181023   1、更新沙特
v3.2 20181024   1、修改开机第二张误报
				2、修改开机第一张误报
				3、修改开盖关盖死机BUG
V3.3 20181025   1、更新鉴伪
V3.4 20181025   1、更新阿联酋
V3.5 20181026   1、增加阿根廷
				2、更新土耳其，欧元，沙特，阿联酋
V3.6 20181028   1、卢布假币更新	
V3.7 20181106   1、卢布假币更新	
V3.8 20181106   1、修改卢布显示
V3.9 20181106   1、卢布假币更新	
V4.0 20181106   1、卢布假币更新	
V4.1 20181106   1、卢布假币更新	
V4.2 20181107   1、卢布假币更新	
V4.3 20181108   1、卢布假币更新	
V4.4 20181115   1、增加自动采集英文版软件
V4.6 20181119   1、修改英镑逻辑
				2、增加校准显示
				3、增加U盘逻辑
v4.7 20181119   1、只有土耳其、美元、欧元版本
v4.8 20181120   1、修改U盘中断优先级
				2、修改采集BUG
v4.9 20181128   1、增加假币抓假
v5.0 20181201   1、按键位置修改
				2、校正显示修改
				4、MP修改 老码盘240us一个码盘。新码盘空转640US一个周期 美元有662个码盘改为2个码盘采集一个点。
				5、UDISK显示消失
v1.0.0 20181201 1、修改版本号为3位显示
				2、U盘图标只有主界面下会显示
v1.0.1 20181201 1、增加鉴伪切换功能。500ms保存
				2、增加U盘配置面额
				3、一分钟息屏，点钞时亮屏
v1.0.2 20181202 1、修改连续进钞逻辑BUG		
v1.0.3 20181203 1、修改连续进钞逻辑BUG		
				2、减少采集单次数据
V1.C.J 20181204 1、采集中文版
V1.0.4 20181205 1、更新新算法
V1.0.5 20181205 1、增加工程师模式
v1.0.8 20181210 1、默认关闭累加
V1.0.9 20181224 1、增加U盘控制信号PC10，检测信号PB15
V1.1.0 20181225 1、更新算法
V1.1.1 20181230 1、更新算法
V1.1.2 20190103 1、更新RUB_UV
V1.1.3 20190106 1、增加自检功能
				2、更改鉴伪报警显示
				3、更改UV鉴伪BUG
V1.1.4 20190107 1、增加RGB显示
				2、修改报警显示小图标
V1.1.5 20190108 1、修改鉴伪模式切换
V1.1.6 20190108 1、修改报警显示小图标BUG	
V1.1.8 20190119 1、增加UV开关和校正
**************************************************************************/

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
//#define DEBUG_MODE
#define LENGTH_HAVENOTE_VALUE_THRES 10
#define LENGTH_HAVENOTE_NUM_THRES 3
#define LENGTH_IR_CHANNEL_NUM (REAL_IR_NUM+1) //21路测长 1路码盘

#define VERSION  "V1.1.8"


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
	ENG_MODE,
	MENU12,
	MENU13,
	MENU14,
	MENU15,
	MENU16,
	MENU17,
	MENU18,
	STATE_NUM,
}STATE_T;


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
	#define max(a, b) (((a) > (b)) ? (a) : (b))
	#define min(a, b) (((a) < (b)) ? (a) : (b))
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
