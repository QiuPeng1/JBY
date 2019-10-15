#ifndef __USER_SYSCONFIG_H__
#define __USER_SYSCONFIG_H__
#include "user_includes.h"

//------------------------------------------------------
/*************************����************************************/
#define 	MPGS_XIE			20
#define		MPGS_MAX			100


#define     MP_MAX      		100
#define     MP_MIN				g_Sensitivity.Width        

//----------------------�ְ�ʱ���ڳ��ȿ��ʵ��ſ�������-----------------------------

/******************������Ϣ����************************************/
#define		BJXX_COL			0x72			//��ɫ���ݱ���
#define		BJXX_CIS			0x73			//��ɫ���ݱ���
#define		BJXX_HALFBILL  		0x41			//���ű���
#define		BJXX_BADBILL  		0x42			//�бұ���
#define		BJXX_ERRMP  		0x43			//���汨��
#define		BJXX_ERRLEN  		0x44			//���ű���
#define		BJXX_DOUBLE  		0x45			//���ű���
#define		BJXX_UV        		0x10			//UV����
#define		BJXX_CX_NUMS 		0x63			//�д����岻�㱨��
#define     BJXX_CX_BESIDE_NUMS 0x5c			//�ߴű���
#define		BJXX_LIAN	   		0x80			//���ű���
#define		BJXX_XIE	   		0x81			//����б������
#define		BJXX_NONE	   		0x00			//�ޱ���
#define 	BJXX_FAULT			0x46			//��Ʊ����
#define 	BJXX_IR				0x20			//���⴩͸����

#define     BJXX_NOHALFBILL     0x46            //�Ǽٰ��ţ����Բ�����.

/**********************************************************************/
#define 	CXNUMS 				60
#define 	CX_MID_MAX 			30

/********************************************/

#define 	TRUE 				1
#define 	FALSE 				0
/**********************************************************/

//�������̽ṹ��
typedef struct { 
		u16 		mpn;		//MP��
		u16 		mpn1;		//�Ƚ���Թ�
		u16 		mpn2;		//���Թ�λ��
		u16 		mpn0;		//����Թ�
		u16 		PerLeftMpn;		//��Թ����̸���
		u16 		PerRightMpn;	//�ҶԹ����̸���
		u16 		leftmpn;		//��Թ����̸���
		u16 		rightmpn;	//�ҶԹ����̸���
		u16 		mpgs;		//���̸���
		u16 		uvmpn;		//UV���̸���
		u16 		ctmpn;		//��͸���̸���
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
//�������ð�����־
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
		u8  		FlagPower3Key		;  //����ͬ�����ָ�����ֵ
		u8   	 	FlagPowerReset		; //ֻ�����ܼ����������ģʽ��
        u8   	 	FlagTFTCheck   		; 
		u8    		FlagTestMode		;	  //�����������ģʽ��
		u8    		FlagSetMode			;	  //�л�����ģʽ������������ģʽ
		u8			FlagKEY				;
		u8    		f_manual_enable		;//�˹���ʱ���Ƿ������³���ȡ����RESET
		u8 			f_manual_mode 		;//MANUAL���ܱ�־
		u8 			FlagPowerOld		;
		u8 	 		FlagOLD				;
		u8  		FlagNEW				;
		u8 			TestNums ;
		u8    		SetNums ;	 //�л������ļ�����
		u8 			UvSetVol;
		u8   		ModeKind;
		u8   		KeyCode;
		u8   		FunKind;
		u8			TotalKind;
		u8 			KeyNums;//key�İ������������Ϊ���Ρ�
//------------------------------------------------------------------        
        u8          FlagStudyRGB        ;//ѧϰRGB�Ŵ���
        u8          StudyRGBBill        ;//ѧϰRGB��Ʊ��λ
//------------------------------------------------------------------     		
}_KeyType;
extern _KeyType 	g_KeyType;
//�������÷���������
typedef struct { 
		u8 			f_beepkey			;// ��������
		u8 			f_testbeep			;//��������
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
		u8   		b_1ms				;// 1MSʱ��
		u8 			b_200ms				;
		u8 			b_2s				;
		u8 			f_run				;//������б�־
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
		u8 			f_first				;//����������һ�ű�־����Ϊ�����¿�ʼ��һ���ܳ���
		u8 			f_inred				;//�������Թܱ�־����Ϊ���¿�ʼ��һ���ܳ��������ܳ����ڶԹ��С�
		u8 			f_FreeLcdTimes   	;//���LCD���п�ʼ
		u8			f_CountPass			;//�������Ѿ��й���
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		u8			FlagCalibIRLeftErr	;//������Թ���ѧϰ��ͨ��
		u8			FlagCalibIRRightErr	;//�Ҽ����Թ���ѧϰ��ͨ��
		u8			FlagCalibIRLeftPass	;//������Թ���ѧϰͨ��
		u8			FlagCalibIRRightPass ;//�Ҽ����Թ���ѧϰͨ��
		u8			FlagCalibIRLeftErrComfirm	 ;//������Թ���ѧϰ��ͨ��---ȷ��
		u8			FlagCalibIRRightErrComfirm	 ;//�Ҽ����Թ���ѧϰ��ͨ��---ȷ��
		u8			FlagCalibUPUVPass	 ;//UV��ѧϰͨ��
		u8			FlagCalibUPUVErr		 ;//UV��ѧϰ��ͨ��
		u8			FlagCalibDOWNUPPass	 ;//UV��ѧϰͨ��
		u8			FlagCalibDOWNUPErr		 ;//UV��ѧϰ��ͨ��
        u8			FlagCalibRGBPass	 ;//UV��ѧϰͨ��
		u8			FlagCalibRGBErr		 ;//UV��ѧϰ��ͨ��
        
        u8			FlagCalibDWIRPass	 ;//UV��ѧϰͨ��
		u8			FlagCalibDWIRErr	;//UV��ѧϰ��ͨ��
        
        u8          FlagCalibLenSendPass;
        u8          FlagCalibLenSendErr;
		u8			FlagDenDisp			;
//-----------------------------------------------------------------------------
        u16         UVUPStartVol;
        u16         UVDNStartVol;
        u16         RGBStartVol;
//-----------------------------------------------------------------------------
		u8			FlagADC1Used		;//ADC1���ڲɼ����
//-----------------------------------------------------------------------------
		u16 		LenMaxFirst;//�����󣬲ɼ�������ֵ
		u16 		FreeLcdTimes;    //����ʱ�����
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
		u16  		CurrentKind;		//���
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
        u8          StartNoTimes;//�޳��������������
        u32         StartNoMaxTime;//�޳�����ĵ��������ʱ�䡣
//-------------------------------------------------
}_SysType;
extern _SysType 	g_SysType;//ϵͳ��־λ
//�������ð�����־
typedef struct {
		u16  		CurrentKind;		//���
		u16  		CurrentWidth;		//���
		u16  		CurrentHigh;		//�߶�
		u16			CurrentDir;			//����
		u16			CurrentSlope;		//б��
		u16  		CurrentDenVer;		//�汾
}_CISType;
extern _CISType g_CISType;
//�������ð�����־
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
//�ɼ���Ϣ�ṹ�����
//-------------------------------------------
typedef struct { 
//--------------������Ϣ�ṹ��--------------------------
		u8			f_in_lj			;
		u8			f_lout			;
		u8			f_in_rj			;
		u8			f_rout			;
		u8 			f_stop			;
		u8			f_out_lj		;
		u8 			f_out_rj		;
		u8			FlagWriteLen	;	//�����¼��������
		u8			FlagTotalEnable	;	//Total�������ı��������ʾ���
		u8			FlagTotal		;	//Total�������ı��
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
		u8   	f_nobjhalf			;      //�������ܻ������������ж�
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

