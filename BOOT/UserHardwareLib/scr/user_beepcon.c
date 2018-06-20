#include "user_beepcon.h"
/****************struct*****************/
//-------------------------------------------------------------------------
//void Beep_Config(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	GPIO_InitStructure.GPIO_Pin = PIN_BEEP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO输出频率10M,2M,
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//输出模式，输入模式IN,复用模式AF,模拟输入AN
//	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP ;	//推挽，开漏OD
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	
//	GPIO_Init(BEEPPORT, &GPIO_InitStructure);		//大电机启动
////	PRE_BEEP = BEEP_DOWN; 
//}
void Beepcon_Beep(void)
{
//	if(g_VoiceType.f_testbeep)	 //如果是自检
//	{
//		if(g_SysType.f_test_ok)	 //自检通过，响三声
//		{
//			g_VoiceType.BeepTime++;
//			if(g_VoiceType.BeepTime >= 50)
//			{
//				g_VoiceType.BeepTime = 0;
//				if(g_VoiceType.BeepTime1++<=6)
//				{
//					if(g_VoiceType.BeepTime1==6||g_VoiceType.BeepTime1==4||g_VoiceType.BeepTime1==2) PRE_BEEP = BEEP_WORK; 
//					else  PRE_BEEP = BEEP_DOWN; 
//				}
//				else
//				{
//					g_VoiceType.BeepTime1 = 0;
//					g_VoiceType.f_testbeep = 0;
//					PRE_BEEP = BEEP_DOWN; 
//				}
//			}	
//		 }
//		else			//自检不通过，响一声
//		{
//			g_VoiceType.BeepTime++;
//			PRE_BEEP = BEEP_WORK; 
//			if(g_VoiceType.BeepTime >= 100)
//			{
//				g_VoiceType.BeepTime = 0;
//				PRE_BEEP = BEEP_DOWN; 
//				g_VoiceType.f_testbeep = 0;
//			}	
//		}
//	}
//	else
//	{
//		if(g_VoiceType.f_beepkey)	  //如果有按键，
//		{
//			PRE_BEEP = BEEP_WORK; 
//			if(++g_VoiceType.BeepTime>150)
//			{
//				g_VoiceType.BeepTime = 0;
//				g_VoiceType.f_beepkey = RESET;
//				PRE_BEEP = BEEP_DOWN; 
//			}
//		}
//		else
//		{
//			if(g_KeyType.FlagPower3Key)
//			{
//				g_VoiceType.BeepTime++;
//				if(g_VoiceType.BeepTime >= 50)
//				{
//					g_VoiceType.BeepTime = 0;
//					if(g_VoiceType.BeepTime1++<=6)
//					{
//						if(g_VoiceType.BeepTime1==5||g_VoiceType.BeepTime1==3||g_VoiceType.BeepTime1==1) PRE_BEEP = BEEP_WORK; 
//						else  PRE_BEEP = BEEP_DOWN; 
//					}
//					else
//					{
//						g_VoiceType.BeepTime1 = 0;
//						g_VoiceType.f_testbeep = 0;
//						g_KeyType.FlagPower3Key = 0;
//						PRE_BEEP = BEEP_DOWN; 
//					}
//				}
//			}
//		}
//		if(g_InfType.Bjxx!=BJXX_NONE)
//		{
//			g_VoiceType.BeepTime++;
//			if(g_VoiceType.BeepTime >= 50)
//			{
//				g_VoiceType.BeepTime = 0;
//				if(g_VoiceType.BeepTime1++<=100)
//				{
//					if(g_VoiceType.BeepTime1==5||g_VoiceType.BeepTime1==3||g_VoiceType.BeepTime1==1) PRE_BEEP = BEEP_WORK; 
//					else PRE_BEEP = BEEP_DOWN; 
//				}
//				else
//				{
//					g_VoiceType.BeepTime1 = 0;
//					g_VoiceType.f_testbeep = 0;
//					PRE_BEEP = BEEP_DOWN; 
//				}
//			}	
//		}
//	}
}
void Beepcon_OTY(void)			//语音片声音
{
	if(g_VoiceType.f_testbeep)	 //如果是自检
	{
		if(g_SysType.f_test_ok)	 //自检通过，响三声
		{
			g_VoiceType.BeepTime++;
			if(g_VoiceType.BeepTime >= 50)
			{
				g_VoiceType.BeepTime = 0;
				if(g_VoiceType.BeepTime1++<=6)
				{
					if(g_VoiceType.BeepTime1==6||g_VoiceType.BeepTime1==4||g_VoiceType.BeepTime1==2) 
					{
						VoiceSeg(_VOICE_BEEP_);
					}
				}
				else
				{
					g_VoiceType.BeepTime1 = 0;
					g_VoiceType.f_testbeep = 0;
				}
			}	
		 }
		else			//自检不通过，响一声
		{
			VoiceSeg(_VOICE_BEEP_);
			g_VoiceType.f_testbeep = 0;	
		}
	}
	else
	{
		if(g_VoiceType.f_beepkey)	  //如果有按键，
		{
			VoiceSeg(_VOICE_BEEP_);
			g_VoiceType.f_beepkey = 0;	
		}
		else
		{
			if(g_KeyType.FlagPower3Key)
			{
				g_VoiceType.BeepTime++;
				if(g_VoiceType.BeepTime >= 50)
				{
					g_VoiceType.BeepTime = 0;
					if(g_VoiceType.BeepTime1++<=6)
					{
						if(g_VoiceType.BeepTime1==5||g_VoiceType.BeepTime1==3||g_VoiceType.BeepTime1==1)
						{
							VoiceSeg(_VOICE_BEEP_);
						}
					}
					else
					{
						g_VoiceType.BeepTime1 = 0;
						g_KeyType.FlagPower3Key = 0;
					}
				}
			}
		}
		if(g_InfType.Bjxx!=BJXX_NONE)
		{
			g_VoiceType.BeepTime++;
			if(g_VoiceType.BeepTime >= 50)
			{
				g_VoiceType.BeepTime = 0;
				if(g_VoiceType.BeepTime1++<=100)
				{
					if(g_VoiceType.BeepTime1==5||g_VoiceType.BeepTime1==3||g_VoiceType.BeepTime1==1) 
					{
						VoiceSeg(_VOICE_BEEP_);
					}
				}
				else
				{
					g_VoiceType.BeepTime1 = 0;
				}
			}	
		}
		if(g_SysType.f_yzwd==1)
		{
			g_VoiceType.BeepTime++;
			if(g_VoiceType.BeepTime >= 50)
			{
				g_VoiceType.BeepTime = 0;
				if(g_VoiceType.BeepTime1++<=6)
				{
					if(g_VoiceType.BeepTime1==5||g_VoiceType.BeepTime1==3||g_VoiceType.BeepTime1==1) 
					{
						VoiceSeg(_VOICE_BEEP_);
					}
				}
				else
				{
					g_VoiceType.BeepTime1 = 0;
					g_SysType.f_yzwd = 0;
				}
			}
		}
	}
}
void Beepcon(void)
{
	Beepcon_OTY();
//	Beepcon_Beep();
}
