#include "user_eeprom.h"

uint32_t EraseCounter = 0x00, Address = 0x00;

#define R_CAL_VOL	290

volatile FLASH_Status FLASHStatus;
volatile TestStatus MemoryProgramStatus; 
//-------------------------------------------------------
_Sensitivity 	g_Sensitivity; //���������Ȳ���������
//-------------------------------------------------------
extern u16 const DATA_RESTORE[CS_NUM];
//-------------------------------------------------------
/*���������*/
u32 GetCheck(u16 *arr,u16 len)
{
	u32 vlu=0;
	u16 loop=0;
	for(loop=0;loop<len;loop++)
	{
		vlu += arr[loop];
	}
	return vlu;
}		
//---------------------------------------------------------
void Save_Sensitivity(void)
{
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
	switch(g_Sensitivity.ResetVol)
	{
		case 0:g_SysType.SysValReset = 90;break;
		case 1:g_SysType.SysValReset = 100;break;
		case 2:g_SysType.SysValReset = 110;break;
		case 3:g_SysType.SysValReset = 121;break;
		case 4:g_SysType.SysValReset = 130;break;
		case 5:g_SysType.SysValReset = 140;break;
		case 6:g_SysType.SysValReset = 150;break;
		case 7:g_SysType.SysValReset = 160;break;
		case 8:g_SysType.SysValReset = 170;break;
		case 9:g_SysType.SysValReset = 180;break;
	}
	switch(g_Sensitivity.UVVol)
	{
		case 0:g_SysType.SysValUV = 240;break;
		case 1:g_SysType.SysValUV = 220;break;
		case 2:g_SysType.SysValUV = 190;break;
		case 3:g_SysType.SysValUV = 170;break;
		case 4:g_SysType.SysValUV = 150;break;
		case 5:g_SysType.SysValUV = 130;break;
		case 6:g_SysType.SysValUV = 110;break;
		case 7:g_SysType.SysValUV = 90;break;
		case 8:g_SysType.SysValUV = 75;break;
		case 9:g_SysType.SysValUV = 60;break;
	}
	switch(g_Sensitivity.Double)
	{
		case 0:g_SysType.SysValDouble = 20;break;
		case 1:g_SysType.SysValDouble = 30;break;
		case 2:g_SysType.SysValDouble = 40;break;
		case 3:g_SysType.SysValDouble = 50;break;
		case 4:g_SysType.SysValDouble = 55;break;
		case 5:g_SysType.SysValDouble = 60;break;
		case 6:g_SysType.SysValDouble = 65;break;
		case 7:g_SysType.SysValDouble = 70;break;
		case 8:g_SysType.SysValDouble = 75;break;
		case 9:g_SysType.SysValDouble = 80;break;
	}
//	DISP_TM1620_Config();
}
void Save_EEPROM(void)
{
	u16 i;
	u32 temp;
	u16* Array;
	Address = StartAddr;
	temp = GetCheck((u16*)&g_Sensitivity,CS_CURNUM);  //����У��ֵ����
	g_Sensitivity.CRCH = temp>>16;	
	g_Sensitivity.CRCL = temp;	//��д2��u16У������	
	Array = (u16*)&g_Sensitivity;
	FLASH_Unlock();
	/* Clear All pending flags */
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASHStatus = FLASH_ErasePage(StartAddr);			 //�ָ��������á�
	for(i=0;i<CS_NUMS;i++)
	{
		FLASHStatus = FLASH_ProgramHalfWord(Address,Array[i]);
		while(FLASHStatus != FLASH_COMPLETE);
		Address = Address + 2;
	}
	FLASH_Lock();
//------------------------------------------------------
	Read_CS();
}	
//---------------------------------------------------------
void Read_CS(void)
{
	u8 i;
	u16* Array;
	Array = (u16*)&g_Sensitivity;
	Address = StartAddr;
	for(i=0;i<CS_NUMS;i++)
	{
		Array[i] = *(__IO uint32_t*) Address;
		Address += 2;
	}
	Save_Sensitivity();
}
void Restore_CS(void)
{
	u16 i;
	u16* Array;
	Array = (u16*)&g_Sensitivity;
	for(i=0;i<CS_NUM;i++)
	{
		if((i!=18)&&(i!=19)&&(i!=13))
			Array[i] = DATA_RESTORE[i];		   //�ָ�����Ĭ�ϡ�
	}
	//-------------------------------------------------------------------------------
	Save_EEPROM();
}
//---------------------------������һ��ʹ�û���----------------
void First_Use(void)
{
	u16 i;
	u32 temp,temp1;
	u16* Array;
	Array = (u16*)&g_Sensitivity;
	Address = StartAddr;
	Read_CS();		//��ȡ�����Ȳ�����
	temp = GetCheck((u16*)&g_Sensitivity,CS_CURNUM);  //����У��ֵ����
	temp1 = (((u32)g_Sensitivity.CRCH)<<16)+((u32)g_Sensitivity.CRCL);
	if(temp != temp1)  //���У�鲻ͨ������ָ�����Ĭ�����ݡ�
	{
		for(i=0;i<CS_CURNUM;i++)
		{
			Array[i] = DATA_RESTORE[i];		   //�ָ�����Ĭ�ϡ�
		}  
		//-------------------------------------------------------------------------------
		Save_EEPROM();
		Read_CS();		//��ȡ�����Ȳ�����
	}
	DISP_TM1620_Config();
}
//---------------------------------------------------------------
u8 CalibrPWM(void)//PWMУ׼
{
	u16 VolIRLeft = 0,VolIRRight = 0;
	u8 	CalibFlagOK = 0;
	u8	IRPostion = 0,IRPostionOK = 0;//IRλ�û�����־
	u8  b_20ms = 0;
//--------------------------------------------------	
	g_Sensitivity.RIRPWM = RIRPWM_MIN;
	g_Sensitivity.LIRPWM = LIRPWM_MIN;
	TIM3->CCR1 = g_Sensitivity.LIRPWM;
	TIM3->CCR2 = g_Sensitivity.RIRPWM;
//--------------------------------------------------
	if(g_Sensitivity.DispSel==DISP_SEL_OFF) SendStr("���ڵ���������Թ�\r\n");
//-------------------------------------���������Թܷ���------------------------------------------		
	while((g_SysType.FlagCalibIRLeftPass==0)&&(g_SysType.FlagCalibIRLeftErrComfirm==0))//���ȷ������������²�У׼����Ĵ�����
	{
		if(g_SysType.b_1ms)
		{
			g_SysType.b_1ms = 0;
			if(++b_20ms>=20)
			{
				b_20ms = 0;
//----------------------------------------------------------------------------
				VolIRLeft	 = ADCConvertedValue[ValIRLeft]*330/4096;
				VolIRRight	 = ADCConvertedValue[ValIRRight]*330/4096;
				DispVolIR(VolIRLeft,VolIRRight);	//��ʾIR��ѹֵ
//----------------------------------------------------------------------------
				if((g_SysType.FlagCalibIRLeftPass==0)&&(g_SysType.FlagCalibIRLeftErr==0))//���û��У׼��ɲ���û�д����־������У׼
				{
					if(VolIRLeft<IRCNT_L)
					{
						if(++g_Sensitivity.LIRPWM>LIRPWM_MAX)
						{
							g_Sensitivity.LIRPWM = LIRPWM_MIN;
							g_SysType.FlagCalibIRLeftErr = 1;//��ѧϰ������Թܴ���
							g_SysType.FlagCalibIRLeftPass = 0;
							g_SysType.FlagCalibIRLeftErrComfirm = 0;
							IRPostion = 1;//�������λ�û���
							IRPostionOK = 0;
						}
					}
					else
					{
						g_SysType.FlagCalibIRLeftPass = 1;
						g_SysType.FlagCalibIRLeftErr = 0;
						g_SysType.FlagCalibIRLeftErrComfirm = 0;
						IRPostion = 0;//ȷ�Ϻ���λ�ò�����
						IRPostionOK = 0;
					}
				}
				if(IRPostion==1)//�����һ��У׼ʧ�ܣ����п����Ƿ���λ�ò�����
				{																	//�����λ�ú����У׼
					if(VolIRLeft<IRCNT_L)
					{
						if(++g_Sensitivity.RIRPWM>RIRPWM_MAX)
						{
							g_Sensitivity.RIRPWM = RIRPWM_MIN;
							g_SysType.FlagCalibIRLeftErrComfirm = 1;//��ѧϰ������Թܴ���
							g_SysType.FlagCalibIRLeftPass = 0;
							g_SysType.FlagCalibIRLeftErr = 0;
							IRPostion = 0;//����λ�û���ʧ�ܣ��п����Ǻ������
							IRPostionOK = 0;//Ҳ�����ǵ���������
						}
					}
					else
					{
						g_SysType.FlagCalibIRLeftPass = 1;
						g_SysType.FlagCalibIRLeftErr = 0;
						g_SysType.FlagCalibIRLeftErrComfirm = 0;
						IRPostion = 1;
						IRPostionOK = 1;//����λ�û����ɹ�
					}
				}
				TIM3->CCR1 = g_Sensitivity.LIRPWM;
				TIM3->CCR2 = g_Sensitivity.RIRPWM;
			}
		}
	}
	if(g_Sensitivity.DispSel==DISP_SEL_OFF) SendStr("���ڵ����Ҽ����Թ�\r\n");
	while((g_SysType.FlagCalibIRRightPass==0)&&(g_SysType.FlagCalibIRRightErrComfirm==0))//���ȷ������������²�У׼����Ĵ�����
	{
		if(g_SysType.b_1ms)
		{
			g_SysType.b_1ms = 0;
			if(++b_20ms>=20)
			{
				b_20ms = 0;
//----------------------------------------------------------------------------
				VolIRLeft	 = ADCConvertedValue[ValIRLeft]*330/4096;
				VolIRRight	 = ADCConvertedValue[ValIRRight]*330/4096;
				DispVolIR(VolIRLeft,VolIRRight);	//��ʾIR��ѹֵ
//----------------------------------------------------------------------------
				if(IRPostionOK==1)//����ȷ�����Ƿ���У׼�����ʱ������λ�û���������ǣ����Һ��⣬��Ҫ�õ�����������
				{
					if(VolIRRight<IRCNT_L)
					{
						if(++g_Sensitivity.LIRPWM>LIRPWM_MAX)
						{
							g_Sensitivity.LIRPWM = LIRPWM_MIN;
							g_SysType.FlagCalibIRRightErrComfirm = 1;//��ѧϰ�Ҽ����Թܴ���
							g_SysType.FlagCalibIRRightPass = 0;
						}
					}
					else
					{
						g_SysType.FlagCalibIRRightPass = 1;
						g_SysType.FlagCalibIRRightErrComfirm = 0;
					}
				}
//-----------------------�����Һ���Թܷ���---------------------------------------------
				else  // λ�ò�û�з�������
				{
					if((g_SysType.FlagCalibIRRightPass==0)&&(g_SysType.FlagCalibIRRightErr==0))//���û��У׼��ɲ���û�д����־������У׼
					{
						if(VolIRRight<IRCNT_L)
						{
							if(++g_Sensitivity.RIRPWM>RIRPWM_MAX)
							{
								g_Sensitivity.RIRPWM = RIRPWM_MIN;
								if(g_SysType.FlagCalibIRLeftErrComfirm==1)	//���������Թܴ������п����ǵ������Թܣ���Ҫ����λ��
								{
									g_SysType.FlagCalibIRRightErr = 1;//��ѧϰ�Ҽ����Թܴ���
									g_SysType.FlagCalibIRRightPass = 0;
									g_SysType.FlagCalibIRRightErrComfirm = 0;
									IRPostion = 1;//�������λ�û���
									IRPostionOK = 0;
								}
								else	//���������Թ���������ȷ�����Ҽ����Թܻ���
								{
									g_SysType.FlagCalibIRRightErr = 0;
									g_SysType.FlagCalibIRRightPass = 0;
									g_SysType.FlagCalibIRRightErrComfirm = 1;//��ѧϰ�Ҽ����Թܴ���
								}
								
							}
						}
						else
						{
							g_SysType.FlagCalibIRRightPass = 1;
							g_SysType.FlagCalibIRRightErr = 0;
							g_SysType.FlagCalibIRRightErrComfirm = 0;
							IRPostion = 0;//ȷ�Ϻ���λ�ò�����
							IRPostionOK = 0;
						}
					}
					if(IRPostion==1)//�����һ��У׼ʧ�ܣ����п����Ƿ���λ�ò�����
					{																	//�����λ�ú����У׼
						if(VolIRRight<IRCNT_L)
						{
							if(++g_Sensitivity.LIRPWM>LIRPWM_MAX)
							{
								g_Sensitivity.LIRPWM = LIRPWM_MIN;
								g_SysType.FlagCalibIRRightErr = 0;//��ѧϰ�Ҽ����Թܴ���
								g_SysType.FlagCalibIRRightPass = 0;
								g_SysType.FlagCalibIRRightErrComfirm = 1;
								IRPostion = 1;//�������λ�û���
								IRPostionOK = 0;
							}
						}
						else
						{
							g_SysType.FlagCalibIRRightErr = 0;
							g_SysType.FlagCalibIRRightPass = 1;
							g_SysType.FlagCalibIRRightErrComfirm = 0;
							IRPostion = 1;
							IRPostionOK = 1;//����λ�û����ɹ�
						}
					}
				}
				TIM3->CCR1 = g_Sensitivity.LIRPWM;
				TIM3->CCR2 = g_Sensitivity.RIRPWM;
			}
		}
	}
//--------------------------------------------------------------------
	if(((g_SysType.FlagCalibIRLeftPass==1)&&(g_SysType.FlagCalibIRLeftErrComfirm==0))&&
		((g_SysType.FlagCalibIRRightPass==1)&&(g_SysType.FlagCalibIRRightErrComfirm==0)))
	{
		CalibFlagOK = 1;
		Save_EEPROM();
	}
	else
	{
		Read_CS();
		CalibFlagOK = 0;
	}
	VolIRLeft	 = ADCConvertedValue[ValIRLeft]*330/4096;
	VolIRRight	 = ADCConvertedValue[ValIRRight]*330/4096;
	DispVolIR(VolIRLeft,VolIRRight);	//��ʾIR��ѹֵ
	DelayMs(1000); //��ʱ1S���˳�ѭ��
	if(CalibFlagOK)	 //�Լ�ͨ����������
	{
		DispCalibOK();
		DelayMs(500); //��ʱ1S���˳�ѭ��
		g_SysType.FlagCalibIRLeftPass = g_SysType.FlagCalibIRLeftErrComfirm = g_SysType.FlagCalibIRRightErr = g_SysType.FlagCalibIRLeftErr = 
		g_SysType.FlagCalibIRRightPass = g_SysType.FlagCalibIRRightErrComfirm = 0;
		return 1;
	}	
	else
	{
		DispCalibErr();
		VoiceSeg(_VOICE_BEEP_);
		DelayMs(500); //��ʱ1S���˳�ѭ��
		g_SysType.FlagCalibIRLeftPass = g_SysType.FlagCalibIRLeftErrComfirm = g_SysType.FlagCalibIRRightErr = g_SysType.FlagCalibIRLeftErr = 
		g_SysType.FlagCalibIRRightPass = g_SysType.FlagCalibIRRightErrComfirm = 0;
		return 0;
	}
//-------------------------------------------------------------------------------------------------------------
}
//---------------------------------------------------------------

