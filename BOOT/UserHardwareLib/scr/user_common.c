#include "user_common.h"
//------------------------------------------------------------

/***************************************************/
const _KeySetSensitivity g_KeySetSensitivity[]={
{&g_Sensitivity.Voice,					VOICE_VAULE,			VOICE_OFF},			
{&g_Sensitivity.FakeCnt,				FAKE_ADD_ON,			FAKE_ADD_OFF},/*假币计数否,0 1*/
{&g_Sensitivity.PcsCompare,				SHEET_COMPARE_ON,		SHEET_COMPARE_OFF},/*张数对比，0，关对比，显示面额，1，开对比*/
{&g_Sensitivity.DispSel,				DISP_SEL_NUM,			DISP_SEL_OFF},/*外显示选择，0，电脑通信，1. 3位侧显示+1616外显  2,合计金额侧显示，3，3位侧显示+合计金额外显*/	
{&g_Sensitivity.MRSideVol,				MRSIDEVOL_MAX,			MRSIDEVOL_MIN},/*斜度纠错，0，不纠错，1，中级纠错，2，高级纠错*/
{&g_Sensitivity.BLTime,					BLACKLIGHT_TIME_MAX,	BLACKLIGHT_TIME_MIN},/*液晶背光关闭时间，时间单位为分钟*/
{&g_Sensitivity.BreakTime,				BREAK_TIME_MAX,			BREAK_TIME_MIN},/*刹车时间40-100*/
//---------------------------------------------------------------------------------------
{&g_Sensitivity.StartVol,				IN_VOL_MAX,				IN_VOL_MIN},/*启动光耦灵敏度,越小灵敏度越高*/
{&g_Sensitivity.ResetVol,				RESET_VOL_MAX,			RESET_VOL_MIN},/*接钞光耦灵敏度,越小灵敏度越高*/
{&g_Sensitivity.IRCntVol,				LJ_RJ_VOL_MAX,			LJ_RJ_VOL_MIN},/*计数管门槛,幅面变大调大*/
{&g_Sensitivity.HoleTime,				HOLE_TIMES_MAX,			HOLE_TIMES_MIN},	/*单计数管补漏时间。*/
//----------------------------------------------------------------------------------------
{&g_Sensitivity.Double,					DOUBLE_BILL_MAX,		DOUBLE_BILL_MIN},/* 重张*/
{&g_Sensitivity.Chain,					LIAN_BILL_MAX,			LIAN_BILL_MIN},/*连张*/
{&g_Sensitivity.UVVol,					UV_VOL_MAX,			    UV_VOL_MIN},/*上荧光越大灵敏度越高*/
//-----------------------------------------------------------------------------------------------------
{&g_Sensitivity.MGINRNum,				CX_MID_INDIA_MAX,		CX_MID_INDIA_MIN},
{&g_Sensitivity.MGUSDNum,				CX_MID_USD_MAX,			CX_MID_USD_MIN},
{&g_Sensitivity.MGSIDENum,				CX_MG_SIDE_MAX,			CX_MG_SIDE_MIN},
{&g_Sensitivity.Width,					WIDTH_MAX,				WIDTH_MIN},

{&g_Sensitivity.LIRPWM,				    LIRPWM_MAX,			    LIRPWM_MIN},
{&g_Sensitivity.RIRPWM,				    RIRPWM_MAX,			    RIRPWM_MIN},
{&g_Sensitivity.UV1PWM,				    UV1PWM_MAX,			    UV1PWM_MIN},
{&g_Sensitivity.UV2PWM,				    UV2PWM_MAX,			    UV2PWM_MIN},
{&g_Sensitivity.Country,				COUNTRY_MAX,			COUNTRY_MIN},
};
/****************u32********************/
const u16  mpgs_tab[]=
{												   
1000,1000,1000,1000,999,999,999,998,998,997,
997,996,995,994,994,993,992,991,990,989,987, 
986,985,984,982,981,979,978,976,975,973,972, 
970,968,966,964,962,961,959,957,955,952,950, 
948,946,944,941,939,937,935,932,930,927,925, 
922,920,917,915,912,909,907,904,902,899,896, 
893,891,888,885,882,880,877,874,871,868,865, 
863,860,857,854,851,848,845,842,839,836,834, 
831,828,825,822,819,816,813,810,807,804,801, 
798,795,793,790,787,784,781,778,775,772,769, 
766,764,761,758,755,752,749,747,744,741,738, 
735,732,730,727,724,721,719,716,713,711,708, 
705,702,700,697,694,692,689,687,684,681,679, 
676,674,671,669,666,664,661,659,656,654,651	
};
//===================================================================
void IF_ERR_SEROR(void)
{
	if(g_KeyType.FlagSetMode)
	{
		g_KeyType.FlagSetMode = 0;
		Save_EEPROM();
		Display();
	}
	if(g_KeyType.FlagSetWidth|g_KeyType.FlagSetFAKE|g_KeyType.FlagSetUV|g_KeyType.FlagSetMGIND|g_KeyType.FlagSetDouble|g_KeyType.FlagSetVoice)
	{
		g_KeyType.FlagSetWidth = g_KeyType.FlagSetFAKE = g_KeyType.FlagSetUV = g_KeyType.FlagSetMGIND =g_KeyType.FlagSetDouble = g_KeyType.FlagSetVoice = 0;	
		Save_EEPROM();
		Display();
	}
	g_KeyType.FlagSetRST = 0;	
}
//-----------------小电机停转---------------------------
void stbj(void)
{
	if(g_SysType.stopn1++ >= 300)
	{
		g_SysType.stopn1 = 0;
		RUN2_OFF;
	}
}
//---------------------------------------------------------
void WidthAnaly(void)//分析幅面。
{	
	switch(g_SysType.CodeMPMsg)
	{					 
		case CODE_FIRST:	  //第一次入钞	  
			if(g_Sensitivity.Width==0) g_SysType.CodeMPMsg = CODE_FIRST;
			else 
			{
				g_SysType.CurMPFIR = g_MPType.mpgs;
				g_SysType.CodeMPMsg = CODE_NEXT;
			}
			break;
		case CODE_NEXT:		  //
			if(g_MPType.mpgs<(g_SysType.CurMPFIR-(WIDTH_MAX-g_Sensitivity.Width)*2))
			{
				g_InfType.f_stop = 1;	g_InfType.Bjxx = BJXX_ERRMP;	
			}
			break;
	}	
	if(g_Sensitivity.Double>0)
	{
		if(g_InfType.DoubleNums>40)
		{
			g_InfType.f_stop = 1;	g_InfType.Bjxx = BJXX_DOUBLE;return;	
		}	
	}
}
/***************幅面计算****************************/
void ScopeAnalysis(void)
{
	if(g_CISType.CurrentSlope>MPGS_XIE)
	{
		g_InfType.Bjxx = BJXX_XIE; 
		g_InfType.f_stop = 1;
	}
//	float  fdgs;
//	if(g_SensorTestTYPE.f_nobjhalf==0) 
//	{
//		if(g_MPType.PerLeftMpn>=g_MPType.PerRightMpn)
//		{
//			if((g_MPType.PerLeftMpn-g_MPType.PerRightMpn)>10)
//			{
//				g_MPType.mpgs = g_MPType.PerLeftMpn;
//			}
//			else
//			{
//				g_MPType.mpgs = (g_MPType.PerLeftMpn+g_MPType.PerRightMpn)/2;
//			}
//		}
//		else
//		{
//			if((g_MPType.PerRightMpn-g_MPType.PerLeftMpn)>10)
//			{
//				g_MPType.mpgs = g_MPType.PerRightMpn;
//			}
//			else
//			{
//				g_MPType.mpgs = (g_MPType.PerLeftMpn+g_MPType.PerRightMpn)/2;
//			}
//		}
//		if(g_SysType.f_inred)
//		{
//			if(g_MPType.PerRightMpn>g_MPType.PerLeftMpn)
//			{
//				if(g_MPType.mpn1>(g_MPType.PerRightMpn-g_MPType.PerLeftMpn))
//				{
//					g_MPType.mpxc = g_MPType.mpn1;
//				}
//				else
//				{
//					g_MPType.mpxc = g_MPType.PerRightMpn-g_MPType.PerLeftMpn;
//				}
//			}
//			else
//			{
//				if(g_MPType.mpn1>(g_MPType.PerLeftMpn-g_MPType.PerRightMpn))
//				{
//					g_MPType.mpxc = g_MPType.mpn1;
//				}
//				else
//				{
//					g_MPType.mpxc = g_MPType.PerLeftMpn-g_MPType.PerRightMpn;
//				}
//			}
//		}
//		else
//		{
//			if(g_MPType.PerRightMpn>g_MPType.PerLeftMpn)
//			{
//				if(g_MPType.mpn1>(g_MPType.PerRightMpn-g_MPType.PerLeftMpn))
//				{
//					g_MPType.mpxc = g_MPType.mpn1;
//				}
//				else
//				{
//					g_MPType.mpxc = g_MPType.PerRightMpn-g_MPType.PerLeftMpn;
//				}
//			}
//			else
//			{
//				if(g_MPType.mpn1>(g_MPType.PerLeftMpn-g_MPType.PerRightMpn))
//				{
//					g_MPType.mpxc = g_MPType.mpn1;
//				}
//				else
//				{
//					g_MPType.mpxc = g_MPType.PerLeftMpn-g_MPType.PerRightMpn;
//				}
//			}
//		}
//		fdgs = mpgs_tab[g_MPType.mpxc];
//		fdgs /= 1000;
//		g_MPType.mpgs = (u16)g_MPType.mpgs * fdgs;
//		
//	}
//	else 
//    {
//        if(g_SensorTestTYPE.f_ljerr==1)
//        {
//            g_MPType.mpgs = g_MPType.PerRightMpn;return; 
//        }
//        else
//        {
//            g_MPType.mpgs = g_MPType.PerLeftMpn;return;
//        }
//    }
//#ifdef _NOMP_
//    if(g_Sensitivity.Chain>0)
//	{
//		if(g_MPType.mpgs>300)
//		{ 
//			g_InfType.Bjxx = BJXX_LIAN; 
//			g_InfType.f_stop = 1;return;
//		}
//	}
//    if(g_InfType.Bjxx!=BJXX_NOHALFBILL)
//	{
//		if(g_MPType.mpgs<40) 
//		{
//			g_InfType.Bjxx = BJXX_NOHALFBILL; 
//			g_InfType.f_stop = 1;return;
//		}
//	}
//#else
//    if(g_MPType.mpxc>MPGS_XIE)
//    { 
//        g_InfType.Bjxx = BJXX_XIE; 
//        g_InfType.f_stop = 1;
//        return;
//    }
//	if(g_Sensitivity.Chain>0)
//	{
//		if(g_MPType.mpgs>MPGS_MAX+(LIAN_BILL_MAX-g_Sensitivity.Chain)*5)
//		{ 
//			g_InfType.Bjxx = BJXX_LIAN; 
//			g_InfType.f_stop = 1;return;
//		}
//	}
//	if(g_InfType.Bjxx!=BJXX_NOHALFBILL)
//	{
//		if(g_MPType.mpgs<10) 
//		{
//			g_InfType.Bjxx = BJXX_NOHALFBILL; 
//			g_InfType.f_stop = 1;return;
//		}
//		if(!g_SysType.f_inred)
//		{
//			if((g_MPType.mpgs<40)&&(g_MPType.mpgs>10))
//			{ 
//				g_InfType.Bjxx = BJXX_HALFBILL; 
//				g_InfType.f_stop = 1;return;
//			}
//		}
//	}
//#endif
}
//===================================================================
//===================================================================
void SwitchDecSensitivity(void)
{
    if(*(g_KeySetSensitivity[g_KeyType.SetNums].Param)==g_KeySetSensitivity[g_KeyType.SetNums].min)
		*(g_KeySetSensitivity[g_KeyType.SetNums].Param) = g_KeySetSensitivity[g_KeyType.SetNums].max;
	else (*(g_KeySetSensitivity[g_KeyType.SetNums].Param))--;	
	if((g_KeyType.SetNums==20)||(g_KeyType.SetNums==21))
	{
		TIM3->CCR1 = *(g_KeySetSensitivity[20].Param);
		TIM3->CCR2 = *(g_KeySetSensitivity[21].Param);
	}
}
//向上切换灵敏度参数值   
void SwitchAddSensitivity(void)		
{
	if(*(g_KeySetSensitivity[g_KeyType.SetNums].Param)==g_KeySetSensitivity[g_KeyType.SetNums].max)
		*(g_KeySetSensitivity[g_KeyType.SetNums].Param) = g_KeySetSensitivity[g_KeyType.SetNums].min;
	else (*(g_KeySetSensitivity[g_KeyType.SetNums].Param))++;
	if((g_KeyType.SetNums==20)||(g_KeyType.SetNums==21))
	{
		TIM3->CCR1 = *(g_KeySetSensitivity[20].Param);
		TIM3->CCR2 = *(g_KeySetSensitivity[21].Param);
	}
}
//--------------老化测试------------------------------------------------
void CheckOld(void)
{
	g_SysType.OldRunTimes = 0;g_SysType.OldStopTimes = 0;g_SysType.OldTotalTimes = 0;
	g_SysType.OldFlagRun = 1;g_SysType.OldFlagStop = 0;
	while(1)
	{
		if(g_SysType.b_2s)
		{
			g_SysType.b_2s = 0;
			if(g_SysType.OldFlagRun)
			{
				Motor_On();
				g_SysType.OldStopTimes = 0;
				g_SysType.OldFlagStop = 0;
				if(++g_SysType.OldRunTimes>30)
				{
					g_SysType.OldRunTimes = 0;
					g_SysType.OldFlagRun = 0;
					g_SysType.OldFlagStop = 1;
					if(++g_SysType.OldTotalTimes>=15)
					{
						g_SysType.OldRunTimes = 0;g_SysType.OldStopTimes = 0;g_SysType.OldTotalTimes = 0;
						g_SysType.OldFlagRun = 0;g_SysType.OldFlagStop = 0;
						break;
					}
				}
			}
			if(g_SysType.OldFlagStop)
			{
				Motor_Stop();
				g_SysType.OldRunTimes = 0;
				g_SysType.OldFlagRun = 0;
				if(++g_SysType.OldStopTimes>30)
				{
					g_SysType.OldStopTimes = 0;
					g_SysType.OldFlagStop = 0;
					g_SysType.OldFlagRun = 1;
				}
			}
		}
	}
}
//--------------------------------------------------------------



