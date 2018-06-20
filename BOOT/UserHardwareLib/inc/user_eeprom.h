#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "user_includes.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
//------------------------------灵敏度参数结构体-------------------------
//定义码盘结构体
typedef  struct { 
//------------------------------一些开关信号参数-------------------------------------------------
	u16 Voice;			/*语音开关,0,1*/
	u16 FakeCnt;		/*假币计数否,0 1*/
	u16 PcsCompare;		/*张数对比，0，关对比，显示面额，1，开对比*/
	u16 DispSel;		/*外显示选择，0，电脑通信，1. 3位侧显示+1616外显  2,合计金额侧显示，3，3位侧显示+合计金额外显
					4.合计外显+合计侧显*/
	u16 MRSideVol;  	/*边磁电压*/
	u16 BLTime; 		/*液晶背光关闭时间，时间单位为分钟*/
	u16 BreakTime; 		/*刹车时间40-100*/

//-------------------------------与机器使用相关的传感器灵敏度设置，不影响抓假------------------------------------------------

	u16 StartVol;		/*启动光耦灵敏度,越小灵敏度越高*/
	u16 ResetVol;		/*接钞光耦灵敏度,越小灵敏度越高*/
	u16 IRCntVol;		/*计数管门槛,幅面变大调大*/
	u16 HoleTime;		/*单计数管补漏时间。*/

//---------------------------------与抓假相关的灵敏度设置-----------------------------------------

	u16 Double;			/* 重张*/
	u16 Chain;			/*连张*/
	u16 UVVol;			/*UV电压*/
	u16 MGINRNum;		/*磁性个数*/
	u16 MGUSDNum;		/*磁性个数*/
	u16 MGSIDENum;		/*边磁性个数*/
	u16 Width;			/*调节幅面*/
//-------------------------------------------------------------------------- 
//----------------------------------光亮度设置的参数PWM 占空比  %---------------------------------------------
	u16 LIRPWM;	/*左计数对管发射*/
	u16 RIRPWM;	/*右计数对管发射*/
	u16 UV1PWM;	/*荧光发射*/
	u16	UV2PWM;	/*码盘发射*/
//--------------------------------------设置默认清点国别 币种------------------------------------ 
	u16 Country;		/*0通用，1印度*/
//---------------------------------------校验值------------------------------------------

	u16	Res1;
	u16	Res2;
	u16	Res3;
	u16	Res4;
	u16	Res5;
	u16	Res6;
	u16 CRCH;
	u16 CRCL;
//------------------------------------END---------------------------------------------------------------------							 
}_Sensitivity;
extern _Sensitivity g_Sensitivity;
//-------------------------------------------------------------------------------
#define  CS_NUMS  	(sizeof(g_Sensitivity)/2)    //参数个数+2个u16的校验值
#define  CS_NUM  	(CS_NUMS-2)   		//参数个数    
#define  CS_CURNUM  (CS_NUM-6)			//当前参数个数
/****************************************************************/	
//------------------------------一些开关信号参数-------------------------------------------------	
#define		VOICE_VAULE					2	/*语音开关,0,1,2*/
#define		VOICE_ON					1
#define		VOICE_OFF					0	

#define		FAKE_ADD_ON					1	/*假币计数否,0 1*/
#define		FAKE_ADD_OFF				0

#define		SHEET_COMPARE_ON			1	/*张数对比，0，关对比，显示面额，1，开对比*/
#define		SHEET_COMPARE_OFF			0

#define		DISP_SEL_NUM				DISP_SEL_LCDC3W    		/*外显示选择，0，电脑通信，1. 3位侧显示+1616外显  2,合计金额侧显示，3，3位侧显示+合计金额外显*/						
#define		DISP_SEL_OFF				0	/*4.合计外显+合计侧显*/

#define		MRSIDEVOL_MIN				0	/*边磁电压*/
#define		MRSIDEVOL_MAX				250

#define		BLACKLIGHT_TIME_MIN			0	/*液晶背光关闭时间，时间单位为分钟*/
#define		BLACKLIGHT_TIME_MAX			10
	
#define		BREAK_TIME_MIN				10	/*刹车时间40-100*/
#define		BREAK_TIME_MAX				100	
//-------------------------------与机器使用相关的传感器灵敏度设置，不影响抓假------------------------------------------------
#define 	IN_VOL_MIN					0	/*启动光耦灵敏度,越小灵敏度越高*/
#define		IN_VOL_MAX					10

#define 	RESET_VOL_MIN				0	/*接钞光耦灵敏度,越小灵敏度越高*/
#define		RESET_VOL_MAX				10

#define 	LJ_RJ_VOL_MIN				0	/*计数管门槛,幅面变大调大*/
#define		LJ_RJ_VOL_MAX				200

#define 	HOLE_TIMES_MIN   			0 	/*单计数管补漏时间。*/
#define		HOLE_TIMES_MAX  			200
//---------------------------------与抓假相关的灵敏度设置-----------------------------------------
#define 	DOUBLE_BILL_MIN   			0 	/* 重张*/
#define		DOUBLE_BILL_MAX  			10

#define 	LIAN_BILL_MIN   			0 	/*连张*/
#define		LIAN_BILL_MAX  				10

#define 	UV_VOL_MIN					0	/*上荧光越小灵敏度越高*/
#define		UV_VOL_MAX					10	

#define 	CX_MID_INDIA_MIN			0
#define 	CX_MID_INDIA_MAX			10

#define 	CX_MID_USD_MIN				0
#define 	CX_MID_USD_MAX				10

#define 	CX_MG_SIDE_MIN				0
#define 	CX_MG_SIDE_MAX				30

#define 	UPIR_VOL_MIN				0	/*上红外*/
#define		UPIR_VOL_MAX				200	

#define 	DWUV_VOL_MIN				0	/*下荧光越小灵敏度越高*/
#define		DWUV_VOL_MAX				200	

#define 	DWIR_VOL_MIN				0	/*下红外*/
#define		DWIR_VOL_MAX				200	

#define 	WIDTH_MIN					0	/*调节幅面*/
#define		WIDTH_MAX					10	
	 
//----------------------------------光亮度设置的参数PWM 占空比  %---------------------------------------------

#define     UV1PWM_MIN					20	/*上UV发射*/
#define     UV1PWM_MAX					100

#define     UV2PWM_MIN					20	/*上红外反射管发射*/
#define     UV2PWM_MAX					100

#define     LIRPWM_MIN					20	/*左计数对管发射*/
#define     LIRPWM_MAX					100

#define     RIRPWM_MIN					20	/*右计数对管发射*/
#define     RIRPWM_MAX					100

#define     DWUVPWM_MIN					20	/*下UV发射*/
#define     DWUVPWM_MAX					100

#define     DWIRPWM_MIN					20	/*下红外反射管发射*/
#define     DWIRPWM_MAX					100

#define     RGBPWM_MIN					20	/*下三色RGB白光发射*/
#define     RGBPWM_MAX					80

#define		COUNTRY_MIN					0
#define		COUNTRY_MAX					2
//-----------------------------------------------------------------
/*******************************************************/
#define StartAddr  ((uint32_t)0x08038000)
/**********************************************************************/
#ifdef NOPAPER	
	#define IRCNT_H		45
	#define IRCNT_L		35
#else
	#define IRCNT_H		90
	#define IRCNT_L		80
#endif
/**********************************************************************/
void Save_EEPROM(void);
void Read_CS(void);
void First_Use(void);
void Restore_CS(void);
u8 CalibrPWM(void);
#endif
