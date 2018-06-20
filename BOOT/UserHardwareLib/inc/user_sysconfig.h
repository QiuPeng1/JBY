#ifndef __USER_SYSCONFIG_H__
#define __USER_SYSCONFIG_H__
#include "user_includes.h"

//------------------------------------------------------
/*************************幅面************************************/
#define 	MPGS_XIE			20
#define		MPGS_MAX			100


#define     MP_MAX      		100
#define     MP_MIN				g_Sensitivity.Width        

//----------------------分版时对于长度可适当放宽，避免误报-----------------------------

/******************报警信息代码************************************/
#define		BJXX_COL			0x72			//蓝色数据报警
#define		BJXX_CIS			0x73			//蓝色数据报警
#define		BJXX_HALFBILL  		0x41			//半张报警
#define		BJXX_BADBILL  		0x42			//残币报警
#define		BJXX_ERRMP  		0x43			//幅面报警
#define		BJXX_ERRLEN  		0x44			//重张报警
#define		BJXX_DOUBLE  		0x45			//重张报警
#define		BJXX_UV        		0x10			//UV报警
#define		BJXX_CX_NUMS 		0x63			//中磁脉冲不足报警
#define     BJXX_CX_BESIDE_NUMS 0x5c			//边磁报警
#define		BJXX_LIAN	   		0x80			//连张报警
#define		BJXX_XIE	   		0x81			//过度斜钞报警
#define		BJXX_NONE	   		0x00			//无报警
#define 	BJXX_FAULT			0x46			//钞票折张
#define 	BJXX_IR				0x20			//红外穿透报警

#define     BJXX_NOHALFBILL     0x46            //是假半张，忽略不计数.

/**********************************************************************/
#define 	CXNUMS 				60
#define 	CX_MID_MAX 			30

/********************************************/

#define 	TRUE 				1
#define 	FALSE 				0
/**********************************************************/

//定义码盘结构体
typedef struct { 
		u16 		mpn;		//MP数
		u16 		mpn1;		//先进入对管
		u16 		mpn2;		//出对管位置
		u16 		mpn0;		//后进对管
		u16 		PerLeftMpn;		//左对管码盘格数
		u16 		PerRightMpn;	//右对管码盘格数
		u16 		leftmpn;		//左对管码盘格数
		u16 		rightmpn;	//右对管码盘格数
		u16 		mpgs;		//码盘格数
		u16 		uvmpn;		//UV码盘格数
		u16 		ctmpn;		//穿透码盘格数
		u16			mrrmpn;
		u16 		mrlmpn;
		u16 		mrm1mpn;
		u16 		mrm2mpn;
		u16     	doublempn;
		u16     	ljmpn;
		u16     	rjmpn;
		u16     	f_mpn;
		u16			mpxc;
		u16			mptemp;		
}_MPType;
extern _MPType 	g_MPType;
//定义设置按键标志
typedef struct { 
        u8 			KeyBuffer[4];
		u8 			FlagSetChain		;
		u8 			FlagSetFAKE			;
		u8 			FlagSetUV			;
		u8 			FlagSetMGIND		;
		u8 			FlagSetMGUSD		;
		u8 			FlagSetDouble		;
		u8 			FlagSetRST			;
		u8 			FlagSetVoice		;
		u8 			FlagDispVoice		;
		u8 			FlagDispRestore		;
		u8  		FlagSetWidth 		;
		u8  		FlagPower3Key		;  //三键同按，恢复功能值
		u8   	 	FlagPowerReset		; //只按功能键，进入调试模式。
        u8   	 	FlagTFTCheck   		; 
		u8    		FlagTestMode		;	  //按键进入测试模式。
		u8    		FlagSetMode			;	  //切换正常模式和设置灵敏度模式
		u8			FlagKEY				;
		u8    		f_manual_enable		;//人工档时，是否允许下钞，取决于RESET
		u8 			f_manual_mode 		;//MANUAL功能标志
		u8 			FlagPowerOld		;
		u8 	 		FlagOLD				;
		u8  		FlagNEW				;
		u8 			TestNums ;
		u8    		SetNums ;	 //切换各档的计数器
		u8 			UvSetVol;
		u8   		ModeKind;
		u8   		KeyCode;
		u8   		FunKind;
		u8			TotalKind;
		u8 			KeyNums;//key的按键次数，最多为三次。
//------------------------------------------------------------------        
        u8          FlagStudyRGB        ;//学习RGB放大倍数
        u8          StudyRGBBill        ;//学习RGB钞票档位
//------------------------------------------------------------------     		
}_KeyType;
extern _KeyType 	g_KeyType;
//定义设置蜂鸣器类型
typedef struct { 
		u8 			f_beepkey			;// 按键声音
		u8 			f_testbeep			;//测试声音
		u8 			f_voicekey			;
		u8  		f_voice				;
		u16 		BeepTime;
		u16 		BeepTime1;
		u16 		CurrentSeg;
}_VoiceType;
extern _VoiceType 	g_VoiceType;
/****************bit********************/
typedef struct { 
		u16			CryBuff[240]		;
		u16			CryBuffNums			;
//-------------------------------------------------
		u8   		b_1ms				;// 1MS时基
		u8 			b_200ms				;
		u8 			b_2s				;
		u8 			f_run				;//电机运行标志
		u8 			f_test_ok			;
		u8 			f_rest				;
		u8			f_break				;
		u8 			f_out				;
		u8 			f_reset_run			; 
		u8 			f_star				;
		u8			f_star1				;
		u8 			f_mpn				;
		u8 			f_yzsd				;
		u8 			f_yzwd				;
		u8 			f_inerr				;
		u8			f_star_voice		;
		u8 			f_first				;//清除报警后第一张标志，因为是重新开始的一次跑钞。
		u8 			f_inred				;//清除已入对管标志，因为重新开始的一次跑钞，不可能出现在对管中。
		u8 			f_FreeLcdTimes   	;//标记LCD空闲开始
		u8			f_CountPass			;//计数管已经有过钞
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		u8			FlagCalibIRLeftErr	;//左计数对管自学习不通过
		u8			FlagCalibIRRightErr	;//右计数对管自学习不通过
		u8			FlagCalibIRLeftPass	;//左计数对管自学习通过
		u8			FlagCalibIRRightPass ;//右计数对管自学习通过
		u8			FlagCalibIRLeftErrComfirm	 ;//左计数对管自学习不通过---确认
		u8			FlagCalibIRRightErrComfirm	 ;//右计数对管自学习不通过---确认
		u8			FlagCalibUPUVPass	 ;//UV自学习通过
		u8			FlagCalibUPUVErr		 ;//UV自学习不通过
		u8			FlagCalibDOWNUPPass	 ;//UV自学习通过
		u8			FlagCalibDOWNUPErr		 ;//UV自学习不通过
        u8			FlagCalibRGBPass	 ;//UV自学习通过
		u8			FlagCalibRGBErr		 ;//UV自学习不通过
        
        u8			FlagCalibDWIRPass	 ;//UV自学习通过
		u8			FlagCalibDWIRErr	;//UV自学习不通过
        
        u8          FlagCalibLenSendPass;
        u8          FlagCalibLenSendErr;
		u8			FlagDenDisp			;
//-----------------------------------------------------------------------------
        u16         UVUPStartVol;
        u16         UVDNStartVol;
        u16         RGBStartVol;
//-----------------------------------------------------------------------------
		u8			FlagADC1Used		;//ADC1正在采集标记
//-----------------------------------------------------------------------------
		u16 		LenMaxFirst;//报警后，采集到的新值
		u16 		FreeLcdTimes;    //空闲时间计数
		u16 		LastBill;
		u16  		stopn1;
		u16  		stopn2;
		u16 		INN0;
		u16 		INN1;
        u16 		INN2;
		u16 		jishu;
		u16 		yuzhi;
		u32 		total;
		u16 		pcs2000;
		u16 		pcs1000;
		u16 		pcs500;
		u16 		pcs200;
		u16 		pcs100;
		u16 		pcs50;
		u16 		pcs20;
		u16 		pcs10;
		u16 		pcs5;
		u16 		pcs2;
		u16 		pcs1;
//---------------------------------------------------
		u16  		DenoKind;
		u16  		CurrentKind;		//面额
//---------------------------------------------------
		u8  		CodeMPMsg;
		u8  		CodeLENMsg;
		u8  		CurMPFIR;
		u8  		CurLENFIR;
//---------------------------------------------------
		u16			SysValStart;
		u16			SysValReset;
		u16			SysValUV;
		u16			SysValDouble;
		u16			SysValIRLeft;
		u16			SysValIRRight;
//---------------------------------------------------
		u32 		OldStopTimes;
		u32			OldRunTimes;
		u32			OldTotalTimes;
		u8 			OldFlagRun;
		u8			OldFlagStop;
//---------------------------------------------------
		u8			FlagCISSendBigPic;
		u8			FlagCISSendSmallPic;
		u8			FlagUDiscOnline;
		u8			FlagCISConfig;
		u8			FlagCISInitOK;
		u8			FlagCISUpgrade;
//---------------------------------------------------
		u8			Currency;
		u8			CurKind;
//---------------------------------------------------
        u8          StartNoTimes;//无钞进入的启动次数
        u32         StartNoMaxTime;//无钞进入的单次最长启动时间。
//-------------------------------------------------
}_SysType;
extern _SysType 	g_SysType;//系统标志位
//定义设置按键标志
typedef struct {
		u16  		CurrentKind;		//面额
		u16  		CurrentWidth;		//宽度
		u16  		CurrentHigh;		//高度
		u16			CurrentDir;			//方向
		u16			CurrentSlope;		//斜度
		u16  		CurrentDenVer;		//版本
}_CISType;
extern _CISType g_CISType;
//定义设置按键标志
typedef struct {
		u16 	lj_adc_result;
		u16 	rj_adc_result;
		u16 	uv_adc_result;
		u16 	in_adc_result;
		u16 	reset_adc_result;
}_KeyDebugType;
extern _KeyDebugType g_KeyDebugType;
/***************************/
/***************************/
//采集信息结构体变量
//-------------------------------------------
typedef struct { 
//--------------基础信息结构体--------------------------
		u8			f_in_lj			;
		u8			f_lout			;
		u8			f_in_rj			;
		u8			f_rout			;
		u8 			f_stop			;
		u8			f_out_lj		;
		u8 			f_out_rj		;
		u8			FlagWriteLen	;	//允许记录长度数据
		u8			FlagTotalEnable	;	//Total刚清点过的标记允许显示标记
		u8			FlagTotal		;	//Total刚清点过的标记
		u8			DispTotalSW     ;
        
        u16 		HoleTimes;
		u16     	DoubleNums;  
//--------------------------------------------------------------------------
		u16			CxLSIDENum;
		u16			CxLSIDETempNum;
		u16			CxLSIDEFlag;
	
		u16			CxRSIDENum;
        u16			CxRSIDETempNum;
        u16			CxRSIDEFlag;
		
        u16			CxMSIDENum;
        u16			CxMSIDETempNum;
        u16			CxMSIDEFlag;
		
		u16			CxMRMNum;
        u16			CxMRMTempNum;
        u16			CxMRMFlag;
//---------------------------------------------------------------------------
		u8 			Bjxx;
		u16			UVFace;
//---------------------------------------------------------------------------
}_InfType;
extern _InfType 	g_InfType;
//-------------------------------------------
typedef struct {
//--------------------------------------------------  
		u8   	f_nobjhalf			;      //若计数管坏，不作半张判断
		u8   	f_bothljrj			;
		u8   	f_ljerr				;
		u8   	f_rjerr				;
		u8   	f_errvoice			;	
		u8 		f_len_disp			;
		u8 		f_len_bad			;
//-------------------------------------------	
		u32	 	ErrorSenor;
		u32	 	ErrCount;
//-------------------------------------------	
	
}_SensorTestTYPE;
extern _SensorTestTYPE 	g_SensorTestTYPE;
extern u8 spi2WorkInMasterMode;
extern u16 maxSpiRecvWaitTime;
//-------------------------------------------------------------------
void InterruptConfig(void);
void RCC_Config(void);
void DelayMs(u16); 
void DelayUS(u32);
void Systick_Config(void);
void Struct_Init(void);
void SYSTICK_IT_DISABLE(void);
void SYSTICK_IT_ENABLE(void);
void SysHardwave_Config(void);
void MP_DISABLE(void);
void MP_ENABLE(void);
#endif

