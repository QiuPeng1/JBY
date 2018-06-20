#include "user_union.h"
#include "math.h"

//--------------------------------------------
u8 UsartDmaSendBuff[320]={0};
/***************************************/
void YesResetRun(void)
{
	g_SysType.f_rest = 0;
	g_SysType.f_first = 0;//清除报警后第一张标志，因为是重新开始的一次跑钞。
	g_SysType.f_inred = 0;//清除已入对管标志，因为重新开始的一次跑钞，不可能出现在对管中。
	g_KeyType.FlagSetRST= 0;
	g_KeyType.FlagKEY = 0;
	g_SysType.CodeMPMsg = g_SysType.CurMPFIR = 0;
	g_SysType.CurLENFIR = g_SysType.CodeLENMsg = 0;
	ClearCurPCS();//清除累计张数。	
	Display();
}
/********************************************************/
void clr_buff1(void)
{
    if(IN_LEFT||IN_RIGHT)   
	{
		g_SysType.f_inred = 1;//两只对管均已进入标志被置1.
	}
    else
    {
        g_SysType.f_inred = 0;
    }
	g_VoiceType.f_beepkey = RESET;LCDC_ON;
	g_SysType.f_rest = 0;g_SysType.f_star_voice = 0;
	Motor_On();
//	Display();	
}
//-----------------------------------------------------
void EndMeasure(void)
{
	u8  KeyCode = NOKEYPRESS;
	if(!g_InfType.f_stop)	ScopeAnalysis();//幅面,长度分析，读取码盘格数。MPGS
	if(!g_InfType.f_stop)	DataAnalysis();			//包括，磁性，荧光等检测。	
	if(g_InfType.f_stop)
	{
		if(g_InfType.Bjxx==BJXX_NOHALFBILL)
		{
			g_InfType.f_stop = 0;g_InfType.Bjxx = BJXX_NONE;return;
		}
	}
	Add_Jishu(); 
//-----------------------------------------------------	
	if(g_LCD.PRE)
	{
	 	if((g_SysType.jishu == g_SysType.yuzhi)&&(g_KeyType.FlagStudyRGB==0))  g_SysType.f_yzsd = 1;
	}		
	if(g_InfType.f_stop| g_SysType.f_yzsd)
	{
		Motor_Stop(); //有异常或预置数到，都停电机
		Motor_Break();//刹车
		if(g_InfType.f_stop)
		{
			LCDR_ON;
			switch(g_InfType.Bjxx)
			{
				case BJXX_HALFBILL: VoiceErr(_VOICE_HALF_); break;
				case BJXX_LIAN: VoiceErr(_VOICE_CHAIN_); break;
				case BJXX_DOUBLE: VoiceErr(_VOICE_DOUBLE_); break;
				case BJXX_ERRLEN:
				case BJXX_ERRMP:
				case BJXX_XIE: 	VoiceErr(_VOICE_ASK_);break;
				default:VoiceErr(_VOICE_ERR_);break;
			}
			Display();	
			DelayMs(200);
			WAIT_BUSY();
			g_SysType.FlagCISSendBigPic = 1; //报警时传大图
			CIS_DealCommand();
		}
	}
	Display();			//显示数码管，如果有报警，则显示报警信息。
//	if(g_Sensitivity.DispSel==DISP_SEL_OFF)
//	{
//        SendDataPC();
//	}
//    if(g_Sensitivity.DispSel==DISP_SEL_COM)
//    {
//        SendDataCom();  
//    }
//    if(g_Sensitivity.DispSel==DISP_SEL_COM_STOP)
//    {
//        if(g_InfType.f_stop) SendDataCom();  
//    }
	if(g_InfType.f_stop|g_SysType.f_yzsd)
	{
		g_SysType.f_first = 1;	//报警后第一张标志。
		while(!g_SysType.f_rest)
		{
			if(g_SysType.b_1ms) 
			{
				g_SysType.b_1ms = 0;
				KeyCode =  ReadKey(); 
				g_VoiceType.f_beepkey = 0;
				Beepcon();              //蜂鸣器控制
				stbj();		
				if(KeyCode != KEY_SWITCH)
				{
					if((KeyCode > KEY_YES_MIN) &&(KeyCode < KEY_YES_MAX))
					{g_SysType.f_out = 0; g_SysType.f_rest = 1;}		//按键至复位
					else	    	
						CheckReset();					//复位对管复位。
				}
				else
				{
					if(g_KeyType.FlagTestMode)
					{
						if(g_KeyType.TestNums==0) g_KeyType.TestNums = 1;
						else g_KeyType.TestNums = 0;
					}
					else
						{g_SysType.f_out = 0; g_SysType.f_rest = 1;}		//按键至复位
				}
			}
			if(g_SysType.b_200ms)
			{
				g_SysType.b_200ms = 0;
				if(g_InfType.f_stop)  g_LCD.BJ = !g_LCD.BJ;
				Display();
				Disp_TM1620();
			}
		}	
		g_InfType.Bjxx = 0;	g_InfType.f_stop = 0;g_InfType.Bjxx = BJXX_NONE; 
		g_LCD.BJ = DARK;
		if(g_SysType.f_yzsd) { g_SysType.f_yzsd = 0;g_SysType.jishu = 0; }  
		Display();		
	}
	else { g_SysType.f_first = 0; g_SysType.f_inred = 0;}	
	clr_buff1();
}
void MultipleDeal(void)
{
	if((!g_SensorTestTYPE.f_nobjhalf)&&(!g_SensorTestTYPE.f_bothljrj))
	{
		if(g_MPType.mptemp != g_MPType.mpn)
		{
			g_MPType.mptemp = g_MPType.mpn;
			if((IN_LEFT)||(IN_RIGHT))
			{
				DealJS();
				EndMeasure(); 
			}
		}
	}
}
/*****************************************/
void DealBill(void)
{
	g_KeyType.FlagKEY = 0;g_InfType.FlagTotal = 0;
	IF_ERR_SEROR();
	if(g_SysType.f_rest)	YesResetRun();//当有进钞时，并无接钞时，机器数据复位，按新功能执行程序。
	MultipleDeal();	
}



