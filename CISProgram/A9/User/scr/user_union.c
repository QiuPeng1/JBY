#include "user_union.h"
#include "math.h"

//--------------------------------------------
u8 UsartDmaSendBuff[320]={0};
/***************************************/
void YesResetRun(void)
{
	g_SysType.f_rest = 0;
	g_SysType.f_first = 0;//����������һ�ű�־����Ϊ�����¿�ʼ��һ���ܳ���
	g_SysType.f_inred = 0;//�������Թܱ�־����Ϊ���¿�ʼ��һ���ܳ��������ܳ����ڶԹ��С�
	g_KeyType.FlagSetRST= 0;
	g_KeyType.FlagKEY = 0;
	g_SysType.CodeMPMsg = g_SysType.CurMPFIR = 0;
	g_SysType.CurLENFIR = g_SysType.CodeLENMsg = 0;
	ClearCurPCS();//����ۼ�������	
	Display();
}
/********************************************************/
void clr_buff1(void)
{
    if(IN_LEFT||IN_RIGHT)   
	{
		g_SysType.f_inred = 1;//��ֻ�Թܾ��ѽ����־����1.
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
	if(!g_InfType.f_stop)	ScopeAnalysis();//����,���ȷ�������ȡ���̸�����MPGS
	if(!g_InfType.f_stop)	DataAnalysis();			//���������ԣ�ӫ��ȼ�⡣	
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
		Motor_Stop(); //���쳣��Ԥ����������ͣ���
		Motor_Break();//ɲ��
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
			g_SysType.FlagCISSendBigPic = 1; //����ʱ����ͼ
			CIS_DealCommand();
		}
	}
	Display();			//��ʾ����ܣ�����б���������ʾ������Ϣ��
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
		g_SysType.f_first = 1;	//�������һ�ű�־��
		while(!g_SysType.f_rest)
		{
			if(g_SysType.b_1ms) 
			{
				g_SysType.b_1ms = 0;
				KeyCode =  ReadKey(); 
				g_VoiceType.f_beepkey = 0;
				Beepcon();              //����������
				stbj();		
				if(KeyCode != KEY_SWITCH)
				{
					if((KeyCode > KEY_YES_MIN) &&(KeyCode < KEY_YES_MAX))
					{g_SysType.f_out = 0; g_SysType.f_rest = 1;}		//��������λ
					else	    	
						CheckReset();					//��λ�Թܸ�λ��
				}
				else
				{
					if(g_KeyType.FlagTestMode)
					{
						if(g_KeyType.TestNums==0) g_KeyType.TestNums = 1;
						else g_KeyType.TestNums = 0;
					}
					else
						{g_SysType.f_out = 0; g_SysType.f_rest = 1;}		//��������λ
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
	if(g_SysType.f_rest)	YesResetRun();//���н���ʱ�����޽ӳ�ʱ���������ݸ�λ�����¹���ִ�г���
	MultipleDeal();	
}



