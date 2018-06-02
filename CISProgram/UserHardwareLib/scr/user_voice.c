#include "user_voice.h"
#include "math.h"
//==========================delay=================================
_VoiceType    	g_VoiceType;//声音结构体变量
//==========================delay=================================

//==========================delay=================================
void Delay100us(void) //1us 8MHz __NOP()=0.12us
{
	u32 time = 700;
	while(time--)
	{
		__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();	
	}
}
void VoiceReset(void)
{
	VOICE_RESET = 0;
	Delay100us();
	VOICE_RESET = 1; 
}
void Voice_CheckStar(void)
{
	static long PreVal = 0;
	long Val = 0,FabsVol = 0;
	Val = ADCConvertedValue[ValStart]*330/4096;
	FabsVol = fabs(Val-PreVal);
	if(FabsVol>=g_SysType.SysValStart)
	{
		g_SysType.INN0++;
		g_SysType.INN1 = 0; 
		if(g_SysType.INN0>50)
		{
			g_SysType.INN0 = 0;
			g_SysType.INN0 = 0;
			g_SysType.f_star_voice = 1;
		}
		else
		{
			g_SysType.f_star_voice = 0;
		}
	}
	else
	{
		g_SysType.INN0 = g_SysType.INN1 = 0;g_SysType.f_star_voice = 0;
	}
	PreVal = Val;
//---------------------------------------------------------
}
void WAIT_BUSY(void)
{ 	
	u16 count = 0;
	while(VOICE_BUSY==SET)
	{
		if(g_SysType.b_1ms)
		{
			g_SysType.b_1ms = 0;
			if(++count>2000) 
			{
				count = 0;
				break;
			}
			if(!g_SysType.f_yzsd)
			{
				if(!g_VoiceType.f_voicekey)
				{
					Voice_CheckStar();
					if((g_SysType.f_star_voice==1)&&(!g_InfType.f_stop))
					{
						VoiceReset();
						break;
					}
				}
				OutBill();
				if((g_InfType.f_stop)||(g_SysType.f_yzsd))
				{
					if(g_SysType.f_rest)
					{
						g_InfType.f_stop = 0;g_InfType.Bjxx = BJXX_NONE;
						VoiceReset();
						break;
					}
				}
			}
		}
	}
	g_VoiceType.f_voicekey = 0;
}
void Voice_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct; 
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_InitStruct.GPIO_Pin = VOICE_SEG_PIN;
	GPIO_Init(VOICE_SEG_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = VOICE_RESET_PIN;
	GPIO_Init(VOICE_RESET_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = VOICE_BUSY_PIN;
	GPIO_Init(VOICE_BUSY_PORT,&GPIO_InitStruct);

	
	VoiceReset();
}
//播放指定首
void VoiceSeg(u8 Current)
{
	u8 CurrentSeg;
	if(g_SysType.f_star_voice==0)
	{
		CurrentSeg = Current;
		VOICE_RESET = 0;
		VOICE_SEG = 0;
		Delay100us();
		VOICE_RESET = 1;
		Delay100us();
		VOICE_RESET = 0;
		Delay100us();
		while(CurrentSeg--)
		{
			VOICE_SEG = 0;
			Delay100us();
			VOICE_SEG = 1; 
			Delay100us();
		}
	}
//	WAIT_BUSY;	
}
void VoiceWelcome(void)
{
	VoiceSeg(_VOICE_NC_);
	DelayMs(1000);
	if(g_Sensitivity.Voice>=VOICE_ON)
	{
		VoiceSeg(_VOICE_WELCOME_);	
	}
}
//-----------------------------------------------------------
void VoiceErr(u8 seg)
{
    if(g_Sensitivity.Voice>=VOICE_ON)
	{
		if(!g_SensorTestTYPE.f_errvoice)
		{
			VoiceSeg(seg);
		}
	}
}
//------播放1-19----------------
void PlayGe(u8 shi,u8 ge)
{
	u8 total;
	total = shi*10+ge;
	VoiceSeg(total+1); //	
	WAIT_BUSY();		
}
//------播放>20----------------
void PlayShi(u8 shi,u8 ge)
{
	VoiceSeg(shi+19); //	
	WAIT_BUSY();
	if(ge>0)	
	{
		VoiceSeg(ge+1); //	
		WAIT_BUSY();
	}
		
}
//------播放100<999----------------
void PlayBai(u8 bai,u8 shi,u8 ge)
{
	VoiceSeg(bai+1); //
	WAIT_BUSY();		
	if(shi>0||ge>0)
	{
		VoiceSeg(_VOICE_HRD1_); //
		WAIT_BUSY();
		if(shi<2)	//播放1-19
		{
			PlayGe(shi,ge);//播放1-19			
		}
		else   //播放十，个
		{
			PlayShi(shi,ge);//播放十位		
		}
	}
	else
	{
		VoiceSeg(_VOICE_HRD_); //
	}
}
//------播放100<999999----------------
void PlayQian(u8 swan,u8 wan,u8 qian,u8 bai,u8 shi,u8 ge)
{
	if(swan>0) PlayBai(swan,wan,qian);
	else
	{
		if(wan>0||qian>0)
		{
			if(wan<2)	//播放1-19
			{
				PlayGe(wan,qian);//播放1-19			
			}
			else   //播放十，个
			{
				PlayShi(wan,qian);//播放十位		
			}
		}
	}
	WAIT_BUSY();
	if(bai>0) 
	{
		VoiceSeg(_VOICE_THD_); //
		WAIT_BUSY();
		PlayBai(bai,shi,ge);
	}
	else
	{
		if(shi>0||ge>0)
		{
			VoiceSeg(_VOICE_THD1_); //
			WAIT_BUSY();
			if(shi<2)	//播放1-19
			{
				PlayGe(shi,ge);//播放1-19			
			}
			else   //播放十，个
			{
				PlayShi(shi,ge);//播放十位		
			}
		}	
		else
		{
			VoiceSeg(_VOICE_THD_); //
		}
	}		
}
void NumToVoice(u8 *NumArr)
{
	if(NumArr[3]==0&&NumArr[4]==0&&NumArr[5]==0)  //千位为0
	{
		if(NumArr[2]==0)  //百位为0 
		{
			if(NumArr[1]<2)	//播放1-19
			{
				PlayGe(NumArr[1],NumArr[0]);//播放1-19			
			}
			else   //播放十，个
			{
				PlayShi(NumArr[1],NumArr[0]);//播放十位		
			}
		}
		else	//播放百，十，个
		{
			PlayBai(NumArr[2],NumArr[1],NumArr[0]);//播放百位	
		}	
	}
	else   //播放千，百，十，个
	{
		PlayQian(NumArr[5],NumArr[4],NumArr[3],NumArr[2],NumArr[1],NumArr[0]);//播放千位
	}
}
//-----------------------------------------
void VoiceNums(u16 jishu)
{
	u8 NumArr[6]={0};
	if(!g_SensorTestTYPE.f_errvoice)		//如果语音片正常。
	{
		if(jishu>0)
		{
			NumArr[3] = jishu%10000/1000;
			NumArr[2] = jishu%1000/100;										
			NumArr[1] = jishu%100/10;
			NumArr[0] = jishu%10;
			NumToVoice(NumArr);
			WAIT_BUSY();
			if(jishu==1) VoiceSeg(_VOICE_PIECE_);
			else  VoiceSeg(_VOICE_PIECES_);
			WAIT_BUSY();
		}
		if(g_Sensitivity.Voice==VOICE_VAULE)
		{
			if(g_LCD.TOTAL)
			{
				if(g_SysType.total==0) return;
				VoiceSeg(_VOICE_TOTAL_);
				WAIT_BUSY();
				NumArr[5] = g_SysType.total/100000;
				NumArr[4] = g_SysType.total%100000/10000;
				NumArr[3] = g_SysType.total%10000/1000;
				NumArr[2] = g_SysType.total%1000/100;										
				NumArr[1] = g_SysType.total%100/10;
				NumArr[0] = g_SysType.total%10;
				NumToVoice(NumArr);
			}
		}
	}
}
//----------------------------------------------------------
void VoicePre(u8 yuzhi)
{
	switch(yuzhi)
	{
		case 100:  	
				if(g_Sensitivity.Voice>VOICE_OFF)
				{
					g_VoiceType.f_beepkey = 0;
					if(!g_SensorTestTYPE.f_errvoice)
					{
						g_VoiceType.f_voicekey = 1;
						VoiceSeg(_VOICE_YZ_);
						WAIT_BUSY();
						VoiceSeg(_VOICE_1_);
						WAIT_BUSY();
						VoiceSeg(_VOICE_HRD_);
					}
				}
				break;
		case 50: 	
				if(g_Sensitivity.Voice>VOICE_OFF)
				{
					g_VoiceType.f_beepkey = 0;
					if(!g_SensorTestTYPE.f_errvoice)
					{
						g_VoiceType.f_voicekey = 1;
						VoiceSeg(_VOICE_YZ_);
						WAIT_BUSY();
						VoiceSeg(_VOICE_50_);
					}
				}
				break; 
		case 20: 
				if(g_Sensitivity.Voice>VOICE_OFF)
				{
					g_VoiceType.f_beepkey = 0;
					if(!g_SensorTestTYPE.f_errvoice)
					{
						g_VoiceType.f_voicekey = 1;
						VoiceSeg(_VOICE_YZ_);
						WAIT_BUSY();
						VoiceSeg(_VOICE_20_);
					}
				}
				break;
		case 10: 	
				if(g_Sensitivity.Voice>VOICE_OFF)
				{
					g_VoiceType.f_beepkey = 0;
					if(!g_SensorTestTYPE.f_errvoice)
					{
						g_VoiceType.f_voicekey = 1;
						VoiceSeg(_VOICE_YZ_);
						WAIT_BUSY();
						VoiceSeg(_VOICE_10_);
					}
				}
				break;
	}
}
//----------------------------------------------------------
void VoiceJishu(void)
{
    if(g_Sensitivity.Voice>=VOICE_ON)
	{
		if(!g_VoiceType.f_voice)
		{
			g_VoiceType.f_voice = 1;
			VoiceNums(g_SysType.jishu);  //电机停下来，根据所需播放语音
		}
	}
}
//----------------------------------------------------------
void VoiceYuzhi(void)
{
    if(g_Sensitivity.Voice>=VOICE_ON)
	{
		if(!g_VoiceType.f_voice)
		{
			g_VoiceType.f_voice = 1;
			VoiceNums(g_SysType.yuzhi);  //电机停下来，根据所需播放语音
		}
	}
}
//----------------------------------------------------------
void VoicePlay(u8 seg)
{
    if(g_Sensitivity.Voice>=VOICE_ON)
	{
		g_VoiceType.f_beepkey = 0;
		if(!g_SensorTestTYPE.f_errvoice)
		{
			g_VoiceType.f_voicekey = 1;
			VoiceSeg(seg);
		}
	}
}
//----------------------------------------------------------
void VoiceBeepTimes(u8 times)
{
    u8 i;
    for(i=times;i>0;i--)
    {
        VoiceSeg(_VOICE_BEEP_);
        DelayMs(300);
    }
}
//----------------------------------------------------------

//----------------------------------------------------------
//----------------------------------------------------------


