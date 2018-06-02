#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "user_includes.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
//------------------------------�����Ȳ����ṹ��-------------------------
//�������̽ṹ��
typedef  struct { 
//------------------------------һЩ�����źŲ���-------------------------------------------------
	u16 Voice;			/*��������,0,1*/
	u16 FakeCnt;		/*�ٱҼ�����,0 1*/
	u16 PcsCompare;		/*�����Աȣ�0���ضԱȣ���ʾ��1�����Ա�*/
	u16 DispSel;		/*����ʾѡ��0������ͨ�ţ�1. 3λ����ʾ+1616����  2,�ϼƽ�����ʾ��3��3λ����ʾ+�ϼƽ������
					4.�ϼ�����+�ϼƲ���*/
	u16 MRSideVol;  	/*�ߴŵ�ѹ*/
	u16 BLTime; 		/*Һ������ر�ʱ�䣬ʱ�䵥λΪ����*/
	u16 BreakTime; 		/*ɲ��ʱ��40-100*/

//-------------------------------�����ʹ����صĴ��������������ã���Ӱ��ץ��------------------------------------------------

	u16 StartVol;		/*��������������,ԽС������Խ��*/
	u16 ResetVol;		/*�ӳ�����������,ԽС������Խ��*/
	u16 IRCntVol;		/*�������ż�,���������*/
	u16 HoleTime;		/*�������ܲ�©ʱ�䡣*/

//---------------------------------��ץ����ص�����������-----------------------------------------

	u16 Double;			/* ����*/
	u16 Chain;			/*����*/
	u16 UVVol;			/*UV��ѹ*/
	u16 MGINRNum;		/*���Ը���*/
	u16 MGUSDNum;		/*���Ը���*/
	u16 MGSIDENum;		/*�ߴ��Ը���*/
	u16 Width;			/*���ڷ���*/
//-------------------------------------------------------------------------- 
//----------------------------------���������õĲ���PWM ռ�ձ�  %---------------------------------------------
	u16 LIRPWM;	/*������Թܷ���*/
	u16 RIRPWM;	/*�Ҽ����Թܷ���*/
	u16 UV1PWM;	/*ӫ�ⷢ��*/
	u16	UV2PWM;	/*���̷���*/
//--------------------------------------����Ĭ�������� ����------------------------------------ 
	u16 Country;		/*0ͨ�ã�1ӡ��*/
//---------------------------------------У��ֵ------------------------------------------

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
#define  CS_NUMS  	(sizeof(g_Sensitivity)/2)    //��������+2��u16��У��ֵ
#define  CS_NUM  	(CS_NUMS-2)   		//��������    
#define  CS_CURNUM  (CS_NUM-6)			//��ǰ��������
/****************************************************************/	
//------------------------------һЩ�����źŲ���-------------------------------------------------	
#define		VOICE_VAULE					2	/*��������,0,1,2*/
#define		VOICE_ON					1
#define		VOICE_OFF					0	

#define		FAKE_ADD_ON					1	/*�ٱҼ�����,0 1*/
#define		FAKE_ADD_OFF				0

#define		SHEET_COMPARE_ON			1	/*�����Աȣ�0���ضԱȣ���ʾ��1�����Ա�*/
#define		SHEET_COMPARE_OFF			0

#define		DISP_SEL_NUM				DISP_SEL_LCDC3W    		/*����ʾѡ��0������ͨ�ţ�1. 3λ����ʾ+1616����  2,�ϼƽ�����ʾ��3��3λ����ʾ+�ϼƽ������*/						
#define		DISP_SEL_OFF				0	/*4.�ϼ�����+�ϼƲ���*/

#define		MRSIDEVOL_MIN				0	/*�ߴŵ�ѹ*/
#define		MRSIDEVOL_MAX				250

#define		BLACKLIGHT_TIME_MIN			0	/*Һ������ر�ʱ�䣬ʱ�䵥λΪ����*/
#define		BLACKLIGHT_TIME_MAX			10
	
#define		BREAK_TIME_MIN				10	/*ɲ��ʱ��40-100*/
#define		BREAK_TIME_MAX				100	
//-------------------------------�����ʹ����صĴ��������������ã���Ӱ��ץ��------------------------------------------------
#define 	IN_VOL_MIN					0	/*��������������,ԽС������Խ��*/
#define		IN_VOL_MAX					10

#define 	RESET_VOL_MIN				0	/*�ӳ�����������,ԽС������Խ��*/
#define		RESET_VOL_MAX				10

#define 	LJ_RJ_VOL_MIN				0	/*�������ż�,���������*/
#define		LJ_RJ_VOL_MAX				200

#define 	HOLE_TIMES_MIN   			0 	/*�������ܲ�©ʱ�䡣*/
#define		HOLE_TIMES_MAX  			200
//---------------------------------��ץ����ص�����������-----------------------------------------
#define 	DOUBLE_BILL_MIN   			0 	/* ����*/
#define		DOUBLE_BILL_MAX  			10

#define 	LIAN_BILL_MIN   			0 	/*����*/
#define		LIAN_BILL_MAX  				10

#define 	UV_VOL_MIN					0	/*��ӫ��ԽС������Խ��*/
#define		UV_VOL_MAX					10	

#define 	CX_MID_INDIA_MIN			0
#define 	CX_MID_INDIA_MAX			10

#define 	CX_MID_USD_MIN				0
#define 	CX_MID_USD_MAX				10

#define 	CX_MG_SIDE_MIN				0
#define 	CX_MG_SIDE_MAX				30

#define 	UPIR_VOL_MIN				0	/*�Ϻ���*/
#define		UPIR_VOL_MAX				200	

#define 	DWUV_VOL_MIN				0	/*��ӫ��ԽС������Խ��*/
#define		DWUV_VOL_MAX				200	

#define 	DWIR_VOL_MIN				0	/*�º���*/
#define		DWIR_VOL_MAX				200	

#define 	WIDTH_MIN					0	/*���ڷ���*/
#define		WIDTH_MAX					10	
	 
//----------------------------------���������õĲ���PWM ռ�ձ�  %---------------------------------------------

#define     UV1PWM_MIN					20	/*��UV����*/
#define     UV1PWM_MAX					100

#define     UV2PWM_MIN					20	/*�Ϻ��ⷴ��ܷ���*/
#define     UV2PWM_MAX					100

#define     LIRPWM_MIN					20	/*������Թܷ���*/
#define     LIRPWM_MAX					100

#define     RIRPWM_MIN					20	/*�Ҽ����Թܷ���*/
#define     RIRPWM_MAX					100

#define     DWUVPWM_MIN					20	/*��UV����*/
#define     DWUVPWM_MAX					100

#define     DWIRPWM_MIN					20	/*�º��ⷴ��ܷ���*/
#define     DWIRPWM_MAX					100

#define     RGBPWM_MIN					20	/*����ɫRGB�׹ⷢ��*/
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
