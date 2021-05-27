/***************************************************************************

版本   日期      修改内容                旧图库版本号        俄罗斯专用版本号
V1.7.8 20210426 1、优化美元和卢布            v8.0.6           
V1.7.7 20210426 1、开机logo显示时间加长      v8.0.6           V180RU
V1.7.7 20210426 1、开机logo显示              v8.0.6           V179RU
V1.7.7 20210420 1、不显示功能明细            v8.0.6           V178RU
V1.7.7 20210420 1、修改短按fun功能           v8.0.6
V1.7.6 20210420 1、修改短按fun功能           v8.0.5
V1.7.5 20210325 1、优化欧元                  v8.0.4
V1.7.4 20210227 1、KZT 新增20K               v8.0.3
V1.7.3 20200910 1、沙特新增5，20             v8.0.2
V1.7.2 20200910 1、增加白俄500  200          v8.0.1
V1.7.1 20200818 1、修改BYR明细显示           V8.0.0
****************************************************************************/
/*****************************历史改动记录***********************************
V2.7  20181016  1、创建     
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
V1.1.9 20190209 1、修改鉴伪算法
V1.2.0 20190213 1、修改堵币无法恢复，必须重启BUG（钱币上有孔洞）
V1.2.1 20190217 1、卢布假币更新
V1.2.3 20190310 1、修改美元抓假
V1.2.4 20190313 1、更新阿根廷
V1.2.5 20190314 1、增加泰铢
V1.2.7 20190407 1、更新欧元
V1.2.8 20190407 1、BUG
V1.2.9 20190408 1、更新泰铢增加台币
V1.3.0 20190409 1、更新算法
V1.3.1 20190410 1、更新伊拉克显示
V1.3.2 20190420 1、增加人民币
V1.3.3 20190615 1、更新算法
V1.3.4 20190616 1、更新土耳其算法
V1.3.5 20190616 1、更新土耳其算法2
V1.3.6 20190617 1、更新土耳其算法3
V1.3.7 20190617 1、更新土耳其算法4
V1.3.8 20190618 1、增加模式
V1.3.9 20190716 1、更新美元算法
V1.4.0 20190729 1、更新阿联酋
V1.4.1 20190801 1、更新阿联酋
V1.4.2 20190810 1、更新校正显示
V1.4.3 20190814 1、更新土耳其
                2、更新欧元
V1.4.4 20190814 1、更新欧元
V1.4.6 20190815 1、更新土耳其
V1.4.7 20190816 1、更新土耳其
                2、更新欧元
V1.4.8 20190817 1、更新欧元
V1.4.9 20190818 1、更新土耳其
V1.5.0 20190819 1、优化美元
                2、计数满时清零
V1.5.1 20190827 1、更新土耳其
V1.5.2 20190831 1、更新土耳其
V1.5.3 20190903 1、更新练功卷
V1.5.4 20190903 1、更新欧元
V1.5.5 20191005 1、优化算法
V1.5.6 20191009 1、UV级别
V1.5.8 20191011 1、UV显示
V1.5.9 20191022 1、优化人民币算法
V1.6.0 20191023 1、优化人民币算法
V1.6.1 20191023 1、优化人民币算法
V1.6.2 20191102 1、优化美元算法
V1.6.2 20200108 1、优化英镑算法
V1.6.3 20200112 1、优化人民币算法
V1.6.5 20200319 1、增加白俄罗斯BYR
                2、增加乌兹别克斯坦UZS
								3、增加哈沙克斯坦KZT
V1.6.6 20200321 1、修复BYR和UZS显示不出来BUG		
V1.6.7 20200324 1、UZS误报优化
V1.6.8 20200410 1、增加摩洛哥MAD
V1.6.9 20200411 1、修改图片地址
V1.7.0 20200411 1、修改明细显示
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

#define PIC_NEW_ADDR    //新图库
//#define RUB_VERSION     //俄罗斯专用版本
#ifdef PIC_NEW_ADDR
    #ifdef RUB_VERSION
        #define VERSION  "V180RU"
    #else
        #define VERSION  "V1.7.8"
    #endif
#else
#define VERSION  "V8.0.6"
#endif

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
