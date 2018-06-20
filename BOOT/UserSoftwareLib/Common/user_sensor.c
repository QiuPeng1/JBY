#include "user_sensor.h"
#include "math.h"
_SensorTestTYPE 	g_SensorTestTYPE;//传感器错误相关类型
//-----------------------------------------------------
//----------------------------------------------------------

/***************************************/
/**********************************************************/
//清除进钞前的数据.
void clr_buff0(void)
{
	g_SysType.StartNoMaxTime = g_SysType.StartNoTimes = 0;//无钞启动时间清零。
	g_SysType.stopn1=g_SysType.stopn2 =0;g_SysType.f_CountPass = 1;
	g_VoiceType.f_beepkey = RESET;
	g_SysType.INN0 = 0;
	g_SysType.INN1 = 0;g_SysType.INN2 = 0;
	memset((void *)&g_MPType,0x0,sizeof(g_MPType));
	memset((void *)&g_VoiceType,0x0,sizeof(g_VoiceType));	
	memset((void *)&g_InfType,0x0,sizeof(g_InfType));		
}
/******************机器开始启动**************************/
void StartRun(void)
{
	u8 i;
	if((g_InfType.f_stop==0)&&(g_SysType.f_yzsd==0))
	{
		g_SysType.INN0 = 0;
		g_SysType.INN1 = 0;g_SysType.INN2 = 0;
		g_SysType.f_star = 1;
		g_SysType.f_star1 = 1;
		MP_ENABLE();
		OpenLight();
		DispOpenBL();
		DelayMs(300);
	}
	else
	{
		g_SysType.CryBuffNums = 0; 
		for(i=0;i<240;i++)
		{
			g_SysType.CryBuff[i] = 0;
		}
		DelayMs(100);
	}
	if(g_KeyType.f_manual_mode==0)
	{
		if(g_KeyType.f_manual_enable==1)
		{
			g_VoiceType.f_beepkey = 0;
			Motor_On(); 
		}
	}
	else
	{
		g_VoiceType.f_beepkey = 0;
		Motor_On(); 
	}
}
/******************机器自动停机**************************/
void StopRun(void)
{
	
	Motor_AutoStop(); 
	MP_DISABLE();
	CloseLight();
	if(g_SensorTestTYPE.ErrorSenor&SENSOR_ERR_RST) g_SysType.f_rest = 1;
	g_KeyType.f_manual_enable = 0;	 //使能手动
	g_SysType.f_star = 0;g_SysType.f_CountPass = 0;
	g_SysType.f_star1 = 0;
	g_InfType.FlagTotalEnable = 0;
	DispOpenBL();
	if(g_LCD.TOTAL) g_InfType.FlagTotalEnable = 1;//如果刚才是合计功能，则标记起来，可以用按键切换。
	g_SysType.FlagDenDisp = 0;
	VoiceJishu();
//	//向U盘存储小图
//	if(g_SysType.jishu>0) g_SysType.FlagCISSendSmallPic = 1;
	//----------------------------------------------------------------
	g_SysType.f_FreeLcdTimes = 1;//使能LCD空闲时间，时间到时，就黑屏
	g_SysType.FreeLcdTimes = 0;
}
/****************************************/
void OutBill(void)
{
	static u8 outn1=0,outn2=0;
	u16 Val = 0;
	Val = ADCConvertedValue[ValReset]*330/4096;
	if(!g_SysType.f_run)
	{
		if(Val>(g_SysType.SysValReset))		
		{
			if(++outn2>10)
			{
				outn2 = 0;outn1 = 0;
				g_SysType.f_rest = 0;
			}
		}
		else
		{
			outn2 = 0;
			if(++outn1>10)
			{
				outn1 = 0;
				g_SysType.f_rest = 1;
			}
		}
	}
	else 
	{
		outn1 = 0;outn2 = 0;
	}
}
void CheckReset(void)
{
	static u16	rstn1=0,rstn2=0;
	u16 Val = 0;
	Val = ADCConvertedValue[ValReset]*330/4096;
	if(!g_SysType.f_run)
	{
		if(g_SysType.f_out)
		{
			if(Val<(g_SysType.SysValReset))			
			{	
				if(++rstn2>10)
				{
					rstn2 = 0;
					StartRun();
					g_SysType.f_out = 0;g_SysType.f_rest = 1;
					g_SensorTestTYPE.ErrorSenor &= ~SENSOR_ERR_RST;
				}
			}	     
		}
		else
		{ 	
			if(Val>(g_SysType.SysValReset))			
			{	
				if(++rstn1>10)
				{
					rstn1 = 0;
					g_SysType.f_out = 1;
				}
			}	     
			else  {g_SysType.f_out = 0;rstn1 = 0;rstn2 = 0;}
		}
	}
	else{g_SysType.f_out = 0;rstn1 = 0;rstn2 = 0;}
}
/***************************************************
进钞判断	  高电平10MS  1MS一次，应该是10次。
			  低电平10ms  1ms一次，应该是10次。
*****************************************************/
void CheckStar(void)
{
	static long PreVal = 0;
	u16 MAX_CNT;
	long Val = 0,FabsVol = 0;
	if(g_SysType.f_CountPass==1)
	{
		MAX_CNT = 300;
	}
	else
	{
		MAX_CNT = 1000;
		if(g_SensorTestTYPE.ErrorSenor&SENSOR_ERR_RST)
		{
			MAX_CNT = 1500;	
		}
	}
	Val = ADCConvertedValue[ValStart]*330/4096;
	FabsVol = fabs(Val-PreVal);
	if(g_SysType.f_run)
	{ 
		if(FabsVol<g_SysType.SysValStart)
		{
			g_SysType.INN0++;
			g_SysType.INN1 = 0; 
			if(g_SysType.INN0>MAX_CNT)
			{
				g_SysType.INN0 = 0;
				StopRun();
			}
		}
		else
		{
            if(g_SysType.StartNoMaxTime>=5)//2S*5 = 10S
            {
                g_SysType.StartNoMaxTime = 0;
                StopRun();
                if(++g_SysType.StartNoTimes>=5)
                {
                    g_SysType.StartNoTimes = 0;
                    g_SysType.SysValStart = FabsVol + 50;//设置新的启动灵敏度
                }
            }
			g_SysType.INN0 = g_SysType.INN1 = 0; 
		}
	}
	else
	{  
		if(FabsVol>=g_SysType.SysValStart)
		{
			g_SysType.INN0++;
			g_SysType.INN1 = 0; 
			if(g_SysType.INN0>50)
			{
				g_SysType.INN0 = 0;
				StartRun();
			}
			else
			{
				g_SysType.f_star = 0;
			}
		}
		else
		{
			if(g_SysType.SysValStart>150)
            {
                if(FabsVol<(g_SysType.SysValStart-100))  //恢复原先的灵敏度
                {
                    if(++g_SysType.INN2>100)
                    {
                        g_SysType.INN2 = 0;
                        g_SysType.StartNoMaxTime = 0;
                        g_SysType.StartNoTimes = 0;
                        switch(g_Sensitivity.StartVol)
                        {
                            case 0:g_SysType.SysValStart = 140;break;
                            case 1:g_SysType.SysValStart = 130;break;
                            case 2:g_SysType.SysValStart = 120;break;
                            case 3:g_SysType.SysValStart = 110;break;
                            case 4:g_SysType.SysValStart = 100;break;
                            case 5:g_SysType.SysValStart = 90;break;
                            case 6:g_SysType.SysValStart = 80;break;
                            case 7:g_SysType.SysValStart = 70;break;
                            case 8:g_SysType.SysValStart = 60;break;
                            case 9:g_SysType.SysValStart = 50;break;
                        }
                    }
                }
            }
			g_SysType.INN0 = g_SysType.INN1 = 0;g_SysType.f_star = g_SysType.f_star1 = 0; 
		}
	} 
	PreVal = Val;
//---------------------------------------------------------
}
//---------------------------------------------------------------------------------------
void Read_MRL(void)
{
	u16 val;
    val = ADCConvertedValue[ValMRL]*330/4096;
	if(val>(g_Sensitivity.MRSideVol+20))
	{
		g_InfType.CxLSIDEFlag = 1; 
		if(g_InfType.CxLSIDENum<200) 
		{
			g_InfType.CxLSIDENum++;
			g_InfType.CxLSIDENum +=g_InfType.CxLSIDETempNum;
			g_InfType.CxLSIDETempNum = 0;
		}
	} 
	else
	{
		if(g_InfType.CxLSIDEFlag)
		{
			if(++g_InfType.CxLSIDETempNum>10)
			{
				g_InfType.CxLSIDEFlag = 0;
				g_InfType.CxLSIDETempNum = 0;
			}
		}
	}

}
//---------------------------------------------------------------------------------------
void Read_MRM(void)
{
	u16 val;
    val = ADCConvertedValue[ValMRM]*330/4096;
	if(val>g_Sensitivity.MRSideVol)
	{
		if(g_InfType.CxMRMNum<200) 
		{
			g_InfType.CxMRMNum++;
		}
	} 
}
//---------------------------------------------------------------------------------------
void Read_MRMS(void)
{
	u16 val;
    val = ADCConvertedValue[ValMRMS]*330/4096;
	if(val>g_Sensitivity.MRSideVol)
	{
		g_InfType.CxMSIDEFlag = 1; 
		if(g_InfType.CxMSIDENum<200) 
		{
			g_InfType.CxMSIDENum++;
		}
	} 
}
//-----------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void Read_MRR(void)
{
	u16 val;
    val = ADCConvertedValue[ValMRR]*330/4096;
	if(val>(g_Sensitivity.MRSideVol+20))
	{
		g_InfType.CxRSIDEFlag = 1; 
		if(g_InfType.CxRSIDENum<200) 
		{
			g_InfType.CxRSIDENum++;
			g_InfType.CxRSIDENum +=g_InfType.CxRSIDETempNum;
			g_InfType.CxRSIDETempNum = 0;
		}
	} 
	else
	{
		if(g_InfType.CxRSIDEFlag)
		{
			if(++g_InfType.CxRSIDETempNum>10)
			{
				g_InfType.CxRSIDEFlag = 0;
				g_InfType.CxRSIDETempNum = 0;
			}
		}
	}
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void Read_CN(void)
{
	Read_MRL();
	Read_MRR();
	Read_MRM();
	Read_MRMS();
}
//-----------------------------------------------------------------------
//===================各传感器自检=================================================
u32 SensorTest(void)
{
	u8 i=0;
	u16 ADResult=0;
	u32 ErrCode = 0;
	long PreVal = 0,Val = 0,FabsVol = 0;
	u16 temp=0;
/*********************进钞光耦***************/	
	for(i=101;i>0;i--)
	{
		while(g_SysType.b_1ms==0);
		g_SysType.b_1ms = 0;
		Val = ADCConvertedValue[ValStart]*330/4096;
		if(i<101) FabsVol += fabs(Val-PreVal);
		PreVal = Val;
	}
	FabsVol = FabsVol/100;
	temp = ((FabsVol+100)<250)?(FabsVol+100):150;
	if((g_SysType.SysValStart<temp)&&(g_Sensitivity.StartVol<=4))
	{
		g_SysType.SysValStart = temp;
	}
	if(FabsVol>200) {ErrCode |= SENSOR_ERR_IN;}	
/********************左计数对管********************/
	g_SensorTestTYPE.ErrCount=0;
	for(i=100;i>0;i--)
	{
		if(IN_LEFT) g_SensorTestTYPE.ErrCount++; 
	}
	if(g_SensorTestTYPE.ErrCount>20) {ErrCode |= SENSOR_ERR_LJ;g_SensorTestTYPE.f_ljerr=1;}
/********************右计数对管*******************/
	g_SensorTestTYPE.ErrCount = 0;
	for(i=100;i>0;i--)
	{
		if(IN_RIGHT) g_SensorTestTYPE.ErrCount++; 
	}
	if(g_SensorTestTYPE.ErrCount>20)	{ErrCode |= SENSOR_ERR_RJ;g_SensorTestTYPE.f_rjerr=1;}	
/**********************测试两只对管的完整性****************************/
	if(((g_SensorTestTYPE.f_ljerr==0)&(g_SensorTestTYPE.f_rjerr==1))||((g_SensorTestTYPE.f_ljerr==1)&&(g_SensorTestTYPE.f_rjerr==0)))   
	{
		g_SensorTestTYPE.f_nobjhalf = 1;
		g_SensorTestTYPE.f_bothljrj = 0;
	}
	else 
	{
		if(g_SensorTestTYPE.f_ljerr&g_SensorTestTYPE.f_rjerr)	 
		{
			g_SensorTestTYPE.f_bothljrj = 1;
			g_SensorTestTYPE.f_nobjhalf = 0;
		}
		else 
		{
			g_SensorTestTYPE.f_nobjhalf = 0;
			g_SensorTestTYPE.f_bothljrj = 0;
		}
	}
/********************清零光耦*********************/
	g_SensorTestTYPE.ErrCount = 0;
 	for(i=100;i>0;i--)
    {
		ADResult = ADCConvertedValue[ValReset]*330/4096;
		if(ADResult>g_SysType.SysValReset) 
		{
			g_SensorTestTYPE.ErrCount++;
		}
		else
		{
			g_SensorTestTYPE.ErrCount = 0;
		}
		DelayMs(1);//延时1ms
	}
	if(g_SensorTestTYPE.ErrCount>60)	{ErrCode |= SENSOR_ERR_RST;}
/*********************UV1*******************/
	g_SensorTestTYPE.ErrCount = 0;
//	for(i=50;i>0;i--)
//    {
//		ADResult = ADCConvertedValue[ValUV]*330/4096;
//		if(ADResult>g_SysType.SysValUV) g_SensorTestTYPE.ErrCount++;
//		DelayMs(1);
//	}
//	if(g_SensorTestTYPE.ErrCount>20) {ErrCode |= SENSOR_ERR_UV;}	
/********码盘光耦*************************/
	if(g_MPType.mpn<100) ErrCode |= SENSOR_ERR_MP;	
/******************************************************/    	
	return	ErrCode;	
}
/*******************************************************/
void Test(void)
{
	u8 i = 0;
	g_SysType.Currency = INDEX_INR;
	g_SensorTestTYPE.ErrorSenor |= SensorTest();
    Motor_AutoStop();
    ClearLCDData();//清除显示结构体
    DisplayID();
	DelayMs(1000);
	g_VoiceType.f_testbeep = 1;
	while(g_SysType.FlagCISInitOK==0)
	{
		DisplayCISInit(0);//显示CIS初始化
		DelayMs(1000);
		if(++i>20) break;
	}
	if(g_SysType.FlagCISInitOK==1)
	{
		DisplayCISInit(1);
	}
	else
	{
		DisplayCISInit(2);
	}
	DelayMs(2000);
	if(g_SensorTestTYPE.ErrorSenor == SENSOR_ERR_NONE)
	{			    
		g_SysType.f_test_ok  = 1;
	}
	else
	{
		ERR_Display(g_SensorTestTYPE.ErrorSenor);
		g_SysType.f_test_ok  = 0;
	}
	ClearLCDData();//清除显示结构体
	Login_Display();
	Disp_TM1620();
	CloseLight();
	g_KeyType.f_manual_mode = 1;//开机默认自动下钞模式
	DispOpenBL();
}
//--------------------------------------------------
//---------------------------------------------------------------------------------------
void DealJS(void)
{
	clr_buff0();
    while(1)
	{
		if(g_MPType.mptemp != g_MPType.mpn)
		{
			g_MPType.mptemp = g_MPType.mpn;
            if(IN_LEFT && (g_InfType.f_in_lj==0))
            {
                g_InfType.f_in_lj = 1;
				g_MPType.leftmpn = 0;
            }
            else
            {
                if(OUT_LEFT &&(g_InfType.f_in_lj==1))
                {
                    if(g_InfType.f_lout==0)
					{
						g_InfType.f_lout = 1;
						g_MPType.PerLeftMpn = g_MPType.leftmpn;
						if(g_InfType.f_in_rj==0 && g_MPType.leftmpn>80) 
						{
							g_InfType.Bjxx = BJXX_HALFBILL;
							g_InfType.f_stop = 1;
							g_InfType.f_rout = 1;  //判断到半张，设置右边出去；
						}
					}
                }
                else
				{
					if(g_InfType.f_in_lj) g_InfType.f_lout = 0; 
				}
            }
 //--------------------------------------------------------------------------------------
            if(IN_RIGHT && (g_InfType.f_in_rj==0))
            {
                g_InfType.f_in_rj= 1;
				g_MPType.rightmpn = 0;
            }
            else
            {
                if(OUT_RIGHT && (g_InfType.f_in_rj==1))
                {
                    if(g_InfType.f_rout==0)
					{
						g_InfType.f_rout = 1;
						g_MPType.PerRightMpn = g_MPType.rightmpn;
						if(g_InfType.f_in_lj==0 && g_MPType.rightmpn>80) 
						{
							g_InfType.Bjxx = BJXX_HALFBILL;
							g_InfType.f_stop = 1;
							g_InfType.f_lout = 1;  //判断到半张，设置右边出去；
						}
					}
                }
                else
				{
					if(g_InfType.f_in_rj) g_InfType.f_rout = 0; 
				}
            }
 //--------------------------------------------------------------------------------------
            if(g_InfType.f_rout==1&&g_InfType.f_lout==1)
			{
				break;
			}
			if(g_InfType.f_rout==0 || g_InfType.f_lout==0)
			{
				g_MPType.leftmpn++;g_MPType.rightmpn++;
				if((g_MPType.leftmpn>1000)||(g_MPType.rightmpn>1000))
                {
                    g_InfType.Bjxx = BJXX_FAULT;
					g_InfType.f_stop = 1;
                    break;
                }
			}
			if(g_InfType.f_in_rj^g_InfType.f_in_lj) //斜钞
			{
				g_MPType.mpn1++;
			}
			Read_CN();//
        }
    }
}
//==========================================================================================
void DealJS_Left(void)
{
	clr_buff0();
    while(1)
	{
		if(g_MPType.mptemp != g_MPType.mpn)
		{
			g_MPType.mptemp = g_MPType.mpn;
            if(IN_LEFT && (g_InfType.f_in_lj==0))
            {
                g_InfType.f_in_lj = 1;
				g_MPType.leftmpn = 0;
            }
            else
            {
                if(OUT_LEFT &&(g_InfType.f_in_lj==1))
                {
                    if(g_InfType.f_lout==0)
                    {
                        g_InfType.f_lout = 1;
                        g_MPType.PerLeftMpn = g_MPType.leftmpn;
                    }
                    else
                    {
                        if(g_InfType.f_out_lj==1)       //补漏后判断为钞票出钞
                        {
                            break;
                        }
                    }
                }
                else
				{
					if(g_InfType.f_in_lj) g_InfType.f_lout = 0; 
				}
            }
 //--------------------------------------------------------------------------------------
			if(g_InfType.f_out_lj==0)
			{
				g_MPType.leftmpn++;
			}
			Read_CN();//
        }
    }
}
//==========================================================================================
void DealJS_Right(void)
{
	clr_buff0();
    while(1)
	{
		if(g_MPType.mptemp != g_MPType.mpn)
		{
			g_MPType.mptemp = g_MPType.mpn;
 //--------------------------------------------------------------------------------------
            if(IN_RIGHT && (g_InfType.f_in_rj==0))
            {
                g_InfType.f_in_rj= 1;
				g_MPType.rightmpn = 0;
            }
            else
            {
                if(OUT_RIGHT && (g_InfType.f_in_rj==1))
                {
                    if(g_InfType.f_rout==0)
					{
						g_InfType.f_rout = 1;
						g_MPType.PerRightMpn = g_MPType.rightmpn;
					}
                    else
                    {
                        if(g_InfType.f_out_rj==1)       //补漏后判断为钞票出钞
                        {
                            break;
                        }
                    }
                }
                else
				{
					if(g_InfType.f_in_rj) g_InfType.f_rout = 0; 
				}
            }
 //--------------------------------------------------------------------------------------
			if(g_InfType.f_out_rj==0)
			{
				g_MPType.rightmpn++;
			}
			Read_CN();//
        }
    }    
}



