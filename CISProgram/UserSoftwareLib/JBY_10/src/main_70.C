/***************************************************************************


****************************************************************************/
#include "main.h"
#include "menu.h"

u8 readKey(void)
{
	//if((!readkey0())&&(!readkey1()))
	{
	//	return KEY_CUR_FUN;
	}
	if(!readkey0())
	{
		return KEY_RESTART;//KEY_CUR;
	}
	if(!readkey1())
	{
		return KEY_CUR;//KEY_FUN;
	}
	if(!readkey2())
	{
		return KEY_FUN;//KEY_RESTART;
	}
	return KEY_noKey;
}

void DealKeyDown(void)
{
	u8 key;
//	u8 commonMenuIndex,i;
	
	if(fifo_GetCount(KB_FIFO) > 0)
	{
		key = fifo_DataOut(KB_FIFO);
		if((g_motor1State != MOTOR_STOP)&&(systemState != ENG_MODE))
		{
			return;
		}
		switch(systemState)
		{
			case NORMAL:
				if(gb_incalibrationByKey == 0)
				{
					DealKeyDownOnNormal(key);
				}
				else
				{
					DealKeyDownOnCalibration(key);
				}
				break;
			case MENU1:
				DealKeyDownOnMenu1(key);
				break;
			case ENG_MODE:
				DealKeyDownOnEngMode(key);
				break;
			case SELFCHECK:
				if(key == KEY_RESTART)
				{
					gb_selfcheckErrorStateClearFlag = 1;
				}
				break;
		}
		//disp_num(key,0,0);
//		LCD_DispNum(0,0,WHITE,BLACK,key,24);
	}
}
void DealKeyDownOnEngMode(u8 key)
{
	switch(key)
	{
		case KEY_RESTART:
			//关传感器
			redFs_Off();
			greenFs_Off();
			blueFs_Off();
			g_colorFsRGB = FS_OFF;
			//开启红外灯
			//开始采样停止电机转动
			hwfs_On();
			jckfs_On();
			motor1_Stop();
			gb_enableSample = 1;
			
			noteState = 0;
			gb_noteState = 0;
			SetSystemState(NORMAL);
			eeprom_SaveData();
			ClearAllNoteNum();
			DispMainMenu();
		break;
		case KEY_CUR:	
			EngModeParaInc();
			DispEngModeSettingSelected();
		break;
		case KEY_FUN:
			lastSelectedItemIndex = selectedItemIndex;
			selectedItemIndex ++;
			selectedItemIndex %= 8;
			DispEngModeSettingSelected();
		break;
		case LONG_KEY_FUN:
			break;
	}
}
void DealKeyDownOnMenu1(u8 key)
{
	switch(key)
	{
		case KEY_RESTART:
			if(gb_paraChanged == 1)
			{
				gb_paraChanged = 0;
				eeprom_SaveData();
			}
			noteState = 0;
			gb_noteState = 0;
			SetSystemState(NORMAL);
			ClearAllNoteNum();
			DispMainMenu();
		break;
		case KEY_CUR:	
			SettingParaInc();
			if((gb_incalibrationByKey == 0)&&(systemState == MENU1))
			{
				DispSettingSelected();	
			}
			
		break;
		case KEY_FUN:
			lastSelectedItemIndex = selectedItemIndex;
			selectedItemIndex ++;
			selectedItemIndex %= 8;
			DispSettingSelected();
			if(gb_haveErrUdiskInforDisp == 1)
			{
				gb_haveErrUdiskInforDisp = 0;
				disp_setPenColor(BLACK);
				disp_setBackColor(BLACK);
				disp_setFont(24);
				disp_string("NO UDISK",320-96,0);
			}
		break;
		case LONG_KEY_FUN:
			break;
	}
}
void ChangeCurrency(void)
{
	u8 i,k;
	for(i = 0;i < openCurrencyNum;i++)
	{
		if(g_currency == openCurrency[i])
		{
			k = i;
			break;
		}
	}
	k ++;
	k %= openCurrencyNum;
	g_currency = openCurrency[k];
	//g_currency %= NOTE_NUM;
}
void DispCurrency(void)
{
	if(g_currency > NOTE_NUM)
	{
		g_currency = 	INDEX_USD;
	}
	disp_DrawPic(0,0,NationFlagBMP[g_currency][0]);
	disp_DrawPic(BMP_LIST_X,BMP_LIST_Y,NationFlagBMP[g_currency][1]);
	
	
	ClearAllNoteNum();
	DispNoteNumValSum();
}
void DealKeyDownOnNormal(u8 key)
{
	if(g_subStateOfNormal == NORMAL_CHA_KAN_CAN_SHU)
	{
		switch(key)
		{
			case KEY_RESTART:		
				g_subStateOfNormal = NORMAL_DIAN_CHAO; 
				DispMainMenu();
				break;
			default:
				break;
		}
	}
	else if(g_subStateOfNormal == NORMAL_DIAN_CHAO)
	{	
		switch(key)
		{
			case KEY_RESTART:
				SetSystemState(NORMAL);
				gb_enableSample = 1;
				noteState = 0;
				gb_isJammed = 0;
				ClearAllNoteNum();
				DispNoteNumValSum();

			break;
			case LONG_KEY_RESTART:			
				selectedItemIndex = 0;
				lastSelectedItemIndex = 0;
				SetSystemState(MENU1);
				DispMenu1();

				break;
			case KEY_CUR:
				ChangeCurrency();
				DispCurrency();	
				gb_ChangeCurrencyDelay = 500;
			break;
			case KEY_FUN:
#ifndef RUB_VERSION                
				modifiIdentificationWays();
#else
                savedPara.noteLeaveRoads++;
                savedPara.noteLeaveRoads%=2;
                DispDirectionInfo();
                gb_modifiIdentificationWaysDealy = 500;
#endif
			break;
			case LONG_KEY_FUN:
				if(g_needAddValue == WORK_ADD)
				{
					g_needAddValue = WORK_NOADD;
				}
				else
				{
					g_needAddValue = WORK_ADD;
				}
				g_funDispChanger = 1;

				break;
		}
	}
}

void modifiIdentificationWays(void)
{
	if(savedPara.identificationWays == ALL_WAYS)
	{
		savedPara.identificationWays = RGB_IR_WAYS;
	}
	else if(savedPara.identificationWays == RGB_IR_WAYS)
	{
		savedPara.identificationWays = RGB_IR_UV_WAYS;
	}
	else if(savedPara.identificationWays == RGB_IR_UV_WAYS)
	{
		savedPara.identificationWays = RGB_IR_MG_WAYS;
	}
	else if(savedPara.identificationWays == RGB_IR_MG_WAYS)
	{
		savedPara.identificationWays = ALL_WAYS;
	}	
	DispIdentificationWays();
	gb_modifiIdentificationWaysDealy = 500;
	//eeprom_SaveData();
}
void DealKeyDownOnCalibration(u8 key)
{
	
	switch(key)
	{
		case KEY_RESTART:
		case LONG_KEY_RESTART:		
			gb_incalibrationByKey = 0;			
			selectedItemIndex = 0;
			lastSelectedItemIndex = 0;
			SetSystemState(MENU1);
			DispMenu1();
			break;
		case KEY_CUR:
						
		break;
		case KEY_FUN:
			
		break;
		case LONG_KEY_FUN:
			break;
	}
}
u8 motorTest = 0;

u32 timeTest[8];
int main(void)
{
	u16 i;
	u8 r,k; 
	delay_DelayMs(1000);
	/*端口配置及
	初始化*/
	MainInit();
	delay_DelayMs(10);
	//delay_DelayMs(1500);
	gb_inCollabration = COLLABRATION_OFF;
	#ifdef USE_IWDG
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);		
	IWDG_SetPrescaler(IWDG_Prescaler_32);		
	IWDG_SetReload(40);	
	IWDG_ReloadCounter();		
	IWDG_Enable();
	#endif

#ifdef RUB_VERSION
    disp_DrawPic(0,0,BMP_CADSHUAEN);
#else	
	disp_clearScreen(BLACK);
	disp_setPenColor(RED);
	disp_setBackColor(BLACK);
	disp_setFont(24);
	disp_string("WELCOME",SCREEN_WIDTH/2-12*3,SCREEN_HEIGHT/2-12);
#endif
	delay_DelayMs(500);
	
	UpdateDataFromSavedData();
	SetSystemState(SELFCHECK);
	SystemSelfcheck();
	if(gb_selfcheckErrorState > 0)
	{
		dispSelfcheckError(gb_selfcheckErrorState);
		gb_selfcheckErrorStateOverTime = 5000;
	}
	else
	{
	SYS_NORMAL:
		entergatePulseNumCounter = 0 ;
		gb_haveNoteInEntergate = 0;
		gb_enableSampleFlag = 0;//0定时器采集，1码盘采集
		
		computeAdjustData();
		memcpy(lengthIdleOriginValue,savedPara.adjustPara.irIdleStandard,REAL_IR_NUM);
		
		SetSystemState(NORMAL);
		gb_enableSample = 1;
		g_subStateOfNormal = NORMAL_DIAN_CHAO; 
		ClearAllNoteNum();
		DispMainMenu();
		LongBeep(1);
		//gb_enableSample = 1;
		//
		redFs_Off();
		greenFs_Off();
		blueFs_Off();
		g_colorFsRGB = FS_OFF;
		lcdBackLightOffCnt = TURN_OFF_LCD_BACKLIGHT_TIME;
	}
//	g_colorFsStopWork = 1;
	while (1)
	{
		//喂狗
		#ifdef USE_IWDG
		IWDG_ReloadCounter();
		#endif
		if(gb_selfcheckErrorStateClearFlag == 1)
		{
			gb_selfcheckErrorStateClearFlag = 0;
			goto SYS_NORMAL;
		}
		if(g_motor1State == MOTOR_STOP)
		{
			gb_usbState = readUsbFault();
			if(gb_usbState == 1)
			{
				USB_CheckReady();//
			}
			else
			{
				Usben_Off();
			}
		}

		if(gb_oneSec == 1)
		{
			gb_oneSec = 0;
		}
		if(gb_needSetCurrency == 1)//根据U盘文件更新面额。
		{
			gb_needSetCurrency = 0;
			r = ReadUdiskFileSize(SetCurrencyFileName,&SetCurrencyFileLen);
			if(r == 0)//读取文件长度成功
			{
				if((SetCurrencyFileLen < 1024)&&(SetCurrencyFileLen > 3))
				{
					ReadUdiskFile(SetCurrencyFileName, read_txt_file_buff, 0, SetCurrencyFileLen);
					gb_udiskCurrencyCnt = (SetCurrencyFileLen-3)/4 + 1;
					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH1] = 0;
					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH2] = 0;
					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH3] = 0;
					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH4] = 0;
					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH5] = 0;

					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH6] = 0;
					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH7] = 0;
					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH8] = 0;
					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH9] = 0;
					savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH10] = 0;
					for(k=0; k<gb_udiskCurrencyCnt; k++)
					{
						CurrencyStr[0] = read_txt_file_buff[k*4];
						CurrencyStr[1] = read_txt_file_buff[k*4+1];
						CurrencyStr[2] = read_txt_file_buff[k*4+2];
						CurrencyStr[3] = '\0';
						updataCurrencySwitch();
					}
					eeprom_SaveData();
					GetOpenCurrency();
					DispMainMenu();
				}
			}
		}
		if(gb_modifiIdentificationWaysFlag == 1)
		{
			gb_modifiIdentificationWaysFlag = 0;
			eeprom_SaveData();
		}
		if(gb_ChangeCurrencyFlag == 1)
		{
			gb_ChangeCurrencyFlag = 0;
			savedPara.machineWorkPara.d[DEFAULT_CURRENCY] = g_currency;
			eeprom_SaveData();
		}
		if(gb_sampleIdleOver == 1)//输出空转采集
		{
			gb_sampleIdleOver = 0;
//			mgDataLen = g_mgSampleIndex;
//			irDataLenA = g_irSampleIndex;
//			memcpy(mgDataA,mgData,6*MG_DATA_MAX_LEN);
//			memcpy(irDataA,irData,8*IR_DATA_MAX_LEN);
//			OutputMgColorDetailData();
		}
		if(gb_udiskStateChanger == 1)
		{
			gb_udiskStateChanger = 0;
			if((systemState == NORMAL)&&(gb_incalibrationByKey == 0))
			{
				DispUdiskInfo();
			}
		}
		if(gb_dispJamInfo == 1)
		{
			gb_dispJamInfo = 0;
			DispJamInfo();
		}
		if(g_funDispChanger==1)
		{
			g_funDispChanger = 0;
			DispFunInfo();
		}
		if(gb_needTurnOffLed == 1)
		{
			gb_needTurnOffLed = 0;
			//gb_enableSample = 0;
			hwfs_Off();
		}
		
		if(systemState == DU_BI)//堵币恢复
		{
			if((gb_haveNoteInEntergate == 0)&&(gb_lengthCovered == 0))
			{
				dubiRecoverCnt ++;
				if(dubiRecoverCnt > 10)
				{
					//恢复normal
					hwfs_On();
					motor1_BackwardRun();
					delay_DelayMs(500);
					motor1_Stop();
					motor1StopRecord = 1;
					gb_isJammed = 0;
					gb_enableSample = 1;
					noteState = 0;
#ifdef DEBUG_MODE
					testflag[0] = 1;
					testflag2[0] = noteState;
#endif
					gb_noteState = NOTE_IDEL;
					ClearPSIrFlag();
					ClearJamFlag();
//					ClearAllNoteNum();
//					DispMainMenu();
					SetSystemState(NORMAL);
					gb_dispJamInfo = 1;
					LongBeep(1);
					dubiRecoverCnt = 0;
				}
				delay_DelayMs(10);
			}
			else
			{
				dubiRecoverCnt = 0;
			}
		}
		
		if(gb_needStopMotor == 1)
		{
			gb_needStopMotor = 0;
			motor1_Stop();
			motor1StopRecord = 2;
			if((noteState&STATE_FORWARD_NOTE_LEAVE) == STATE_FORWARD_NOTE_LEAVE)
			{
	 			noteState &= (~STATE_FORWARD_NOTE_LEAVE);
#ifdef DEBUG_MODE
				testflag[1] = 1;
				testflag2[1] = noteState;
#endif
				initEteranceSensor();
				ToggleJinChaoFaShe();
				ententernceCnt = 0;
			}
		}
		if(gb_errflagClearDisp == 1)
		{
			gb_errflagClearDisp = 0;
			noteDenoValue = 0;
			DispNoteSum();
			//DispMainMenu();
		}
		DealScanEnteracneSensor();
		//ScanKeyDown();
		DispAutoRefreshMenu();
		
		DealNotePass();
		
		DealPackageFromUart3();
			
		DealKeyDown();

	}
}
void updataCurrencySwitch(void)
{
	u8 res;
	u8 i;
	u8 d,k;
	
	for(i=0; i<NOTE_NUM; i++)
	{
		res = strcmp(CurrencyStr,CURRENCY_INFO_STR[i]);
		if(res == 0)
		{
			k = i/8;
			d = i%8;
			savedPara.machineWorkPara.d[k] |= 1<<d;
			break;
			
		}
	}
}
void ScanKeyDown(void)
{
	if(gb_needCheckKey == 1)
	{
		gb_needCheckKey = 0;

		currentLcdKey = readKey();//tm16xx_readKey();	

		keyFlag <<= 1;
		if(currentLcdKey != KEY_noKey)
		{
			keyFlag ++;
		}
				
		if (!gb_longLcdKey)
		{
			if (currentLcdKey == KEY_noKey)
			{
				if ((shortLcdKeyTimer == 0)&&shortLcdKey != 0)
				{			
					if(gb_lcdBacklightOn == 0)
					{
						disp_lcdBLC(60);	
						gb_lcdBacklightOn = 1;
						lcdBackLightOffCnt = TURN_OFF_LCD_BACKLIGHT_TIME;	
					}
					else
					{
						fifo_DataIn(KB_FIFO,shortLcdKey);	
						lcdBackLightOffCnt = TURN_OFF_LCD_BACKLIGHT_TIME;	
						LongBeep(1);
					}
				}
				enterLongLcdKeyTimer = ENTER_LONG_KEY_TIME;
				shortLcdKeyTimer = SHORT_KEY_TIME;
			}
			else
			{
				if (shortLcdKeyTimer > 0)
				{
					shortLcdKeyTimer --;
					if (shortLcdKeyTimer == 0)
					{
						shortLcdKey = currentLcdKey;
					}
				}
				
				if(enterLongLcdKeyTimer > 0)
				{
					enterLongLcdKeyTimer --;
					if (enterLongLcdKeyTimer == 0)
					{
						longLcdKeyIntervalTimer = LONG_KEY_INTERVAL_TIME;
						gb_longLcdKey = 1;
						longLcdKey = currentLcdKey;	
						if(gb_lcdBacklightOn == 0)
						{
							disp_lcdBLC(60);	
							gb_lcdBacklightOn = 1;
							lcdBackLightOffCnt = TURN_OFF_LCD_BACKLIGHT_TIME;
						}
						else
						{
							fifo_DataIn(KB_FIFO,longLcdKey+LONG_LCD_KEY_ADDVAL);
							lcdBackLightOffCnt = TURN_OFF_LCD_BACKLIGHT_TIME;							
							LongBeep(1);	
						}
					}
				}
			}
		}
		else
		{
			if (currentLcdKey == longLcdKey)
			{
				if (longLcdKeyIntervalTimer > 0)
				{
					longLcdKeyIntervalTimer --;
					if (longLcdKeyIntervalTimer == 0)
					{
						//kbfifo_DataIn(longLcdKey+LONG_LCD_KEY_ADDVAL);
						//KeyBeep(1);
						//sendOneKey(longLcdKey+LONG_LCD_KEY_ADDVAL);
						fifo_DataIn(KB_FIFO,longLcdKey+LONG_LCD_KEY_ADDVAL);				
						LongBeep(1);	
						
					}
				}
			}
			else
			{
				gb_longLcdKey = 0;
				longLcdKey = KEY_noKey;
				shortLcdKey = KEY_noKey;
				shortLcdKeyTimer = SHORT_KEY_TIME;
				enterLongLcdKeyTimer = ENTER_LONG_KEY_TIME;
				longLcdKeyIntervalTimer = LONG_KEY_INTERVAL_TIME;
			}
		}

	}
}


void DealPackageFromUart3(void)
{
	u8 cmd;
	u8 i;
	//处理usart3的数据包
	if(gb_needDealUart3Data == 1)
	{
		if (uart3infifo_count == 0)
		{
			gb_needDealUart3Data = 0;
		}
		else
		{	
			cmd = uart3infifo_DataOut();//命令
			if(gb_uartWorkMode == DEBUG_MODE)
			{
				switch (cmd)
				{
					case 0x42://磁性数据 手
						gb_autoOutputDetailData = 0;
						break;
					case 0x62://磁性数据 自
						gb_autoOutputDetailData = 1;
						savedPara.noteLeaveRoads = 0;
						break;
					case 'a'://输出数据 //磁性 获取当前纸币
						//OutputMgIrDetailData();
						//OutputLengthDetailData();
						OutputALLDetailData2();
						break;
	// 				case 
	// 				OutputMgColorDetailData();
	// 					break;
					case 0x65://磁性界面下按轮子空转	
						gb_enableSample = 0;
						hwfs_On();
						//motor1_ForwardRun();
						//motor1_Run();
						delay_DelayMs(100);
						gb_sampleIdleOver = 0;
						g_mgSampleIndex = 0;
						g_uvSampleIndex = 0;
						g_lengthSampleIndex = 0;
						g_colorSampleIndex = 0;
						gb_colorSampleEnable = 1;
						gb_lengthIrNeedStartSampleflag = 1;
						gb_uvNeedStartSampleflag = 1;
						needSampleIdleNum = 600;
						//delay_DelayMs(2000);
						//motor1_Stop();
						//hwfs_Off();			
						break;
					case 0x48://厚度下 手
						break;
					case 0x68://厚度下 自
						break;
					case 'g'://厚度下 获取当前纸币
						//OutputMgColorDetailData();
						OutPutPsHWRecordData();
						break;
					case 0xa0://采集一轮数据并输出
						DispSensorViewMenu();
						break;
					case 0xa1://定时采集并输出
						if(systemState == NORMAL)
						{
							//切换到传感器菜单
							SetSystemState(SENSOR_VIEW);
							motor1_Stop();
							//hwfs_On();
							jckfs_On();
							gb_enableSample = 0;
							DispString("SENSOR_VIEW_STATE",1);
							//DispSensorViewMenu();
						}
						else
						{
							//切换到NORMAL菜单
							SetSystemState(NORMAL);
							gb_enableSample = 1;
							g_subStateOfNormal = NORMAL_DIAN_CHAO; 
							DispMainMenu();
							DispString("NORMAL_STATE",1);							
						}
						break;
					case 0xa2:
						hwfs_On();
						break;
					case 0xa3:
						hwfs_Off();
						break;
					case 0xa4:
						LongBeep(1);
						DispString("beep",1);
						break;
					case 0xa5:
						beep_On();
						break;
					case 0xa6:
						beep_Off();
						break;
					case 0xa7:
						if(g_motor1State != MOTOR_STOP)
						{
							motor1_Stop();
						}
						else
						{
							motor1_ForwardRun();
						}
						break;
					case 0xa8:
						if(g_motor1State != MOTOR_STOP)
						{
							motor1_Stop();
						}
						else
						{
							motor1_BackwardRun();
						}
						break;	
					case 0xa9:
						savedPara.noteLeaveRoads = 1;
						break;
					case 0xaa:
						savedPara.noteLeaveRoads = 0;
						break;
					case 0xab:
						hwfs_On();
						SetSystemState(NORMAL);
						gb_enableSample = 1;
						delay_DelayMs(100);
						
						memcpy(savedPara.adjustPara.irIdleStandard,irValue,REAL_IR_NUM);
						DispString("空载红外值",1);
						for(i = 0;i < REAL_IR_NUM;i++)
						{
							dispStr[0] = ' ';
							U8ToStr(savedPara.adjustPara.irIdleStandard[i],dispStr+1);
							DispString(dispStr,0);
						}
						DispString(" ",1);
						memcpy(lengthIdleOriginValue,savedPara.adjustPara.irIdleStandard,REAL_IR_NUM);
						
						gb_inCollabration = COLLABRATION_80G_BZ;
						collabrationNoteNum = 0;
						memset(collabrationSum,0,REAL_IR_NUM*4);
						memset(collabrationNum,0,REAL_IR_NUM);
						memset(collabrationMax,0,REAL_IR_NUM*2);
						memset(collabrationMin,0xff,REAL_IR_NUM*2);
						DispString("开始厚白纸校正,放入127g厚白纸",1);
						break;
					case 0xac:
						if(gb_lengthInOriginData == 1)
						{
							gb_lengthInOriginData = 0;
							DispString("测长输出校正数据",1);
						}
						else
						{
							gb_lengthInOriginData = 1;
							DispString("测长输出原始数据",1);
						}
						break;
					case 0xad:
							if(g_colorFsStopWork == 1)
							{
								g_colorFsStopWork = 0;
								DispString("颜色灯打开",1);
							}
							else
							{
								g_colorFsStopWork = 1;
								DispString("颜色灯关闭",1);
								delay_DelayMs(1000);
								redFs_Off();
								greenFs_Off();
								blueFs_Off();
							}
						break;
					case 0xae:
						if(g_colorFsRGB == FS_BLUE)
						{
							redFs_Off();
							greenFs_Off();
							blueFs_Off();
							g_colorFsRGB = FS_OFF;
						}
						else if(g_colorFsRGB == FS_RED)
						{
							redFs_Off();
							greenFs_On();
							blueFs_Off();
							g_colorFsRGB = FS_GREEN;
						}
						else if(g_colorFsRGB == FS_GREEN)
						{
							redFs_Off();
							greenFs_Off();
							blueFs_On();
							g_colorFsRGB = FS_BLUE;
						}
						else
						{
							redFs_On();
							greenFs_Off();
							blueFs_Off();
							g_colorFsRGB = FS_RED;
						}
						break;
					case 0xb1: //开始颜色校正
						g_colorFsStopWork = 0;
						SetSystemState(NORMAL);
						gb_enableSample = 1;
						delay_DelayMs(100);
						gb_inCollabration = COLLABRATION_COLOR;
						gb_colorInOriginData = 1;
						DispString("开始颜色校正,放入A4纸",1);
						break;
					case 0xb2:
						if(gb_colorInOriginData == 1)
						{
							gb_colorInOriginData = 0;
							DispString("颜色输出校正数据",1);
						}
						else
						{
							gb_colorInOriginData = 1;
							DispString("颜色输出原始数据",1);
						}
						break;
					case 0xb3:
							if(gb_uvVccIsOn == 1)
							{
								uvfs_Off();
								DispString("UV灯关闭",1);
							}
							else
							{
								uvfs_On();
								DispString("UV灯打开",1);
							}			
						break;	
					case 0xb4:
							if(gb_jinChaoFaSheIsOn == 1)
							{
								jckfs_Off();
								DispString("进钞红外关闭",1);
							}
							else
							{
								jckfs_On();
								DispString("进钞红外打开",1);
							}			
						break;	
					case 0xb5:
							if(gb_hwVccIsOn == 1)
							{
								hwfs_Off();
								DispString("测长红外关闭",1);
							}
							else
							{
								hwfs_On();
								DispString("测长红外打开",1);
							}			
						break;	
						case 0xb6:
							if(gb_debugErrFlag == 1)
							{
								gb_debugErrFlag = 0;
								DispString("调试串口关闭",1);
							}
							else
							{
								gb_debugErrFlag = 1;
								DispString("调试串口打开",1);
							}			
						break;													
	 					case 0xf0:
							i = 0;
#ifdef DEBUG_MODE
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = testflag[i-1];i++;
							uart3toPCdebug[i] = 0x55;i++;
							uart_SendDataToUart3(uart3toPCdebug,i);
							i = 0;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = testflag2[i-1];i++;
							uart3toPCdebug[i] = 0x55;i++;
							uart_SendDataToUart3(uart3toPCdebug,i);
#endif
							break;
	// 					case 0x68:
	// 						gb_autoOutputDetailData2 = 1;
	// 						break;
	// 					case 0x48:
	// 						gb_autoOutputDetailData2 = 0;
	// 						break;
					default:
						break;
				}
			}
		}
	}	
}

void DealScanEnteracneSensor(void)
{
	u16 i;
	if(systemState == NORMAL)
	{
		if(gb_haveNoteInEntergate == 1)
		{
			if((noteState == 0)&&(g_motor1State == MOTOR_STOP))//&&(gb_notebackInEnteranceFlag == 0))//空闲态
			{
				//开传感器
				if(gb_lcdBacklightOn == 0)
				{
					disp_lcdBLC(60);	
					gb_lcdBacklightOn = 1;
				}
				if(gb_errflagOverTime > 0)
				{
					gb_errflagOverTime = 0;
					noteDenoValue = 0;
					DispNoteSum();
					//DispMainMenu();
				}
				lcdBackLightOffCnt = TURN_OFF_LCD_BACKLIGHT_TIME;		
				memset(mpCntRecode, 0, sizeof(mpCntRecode));
				memset(msCntRecode, 0, sizeof(msCntRecode));
#ifdef DEBUG_MODE
				memset(testflag,0,sizeof(testflag));
				memset(testflag2,0,sizeof(testflag2));
				testflag2Cnt = 0;
#endif
				hwfs_On();
				uvfs_On();
				redFs_On();
				greenFs_Off();
				blueFs_Off();
				
				mpCnt = 0;
				timeCnt = 0;
				gb_noteState = NOTE_FORWARD;
				motor1_ForwardRun();
				//test_Off();
				motor1SataRecord2 = 3; 
				motor1SataRecord = 0; 
				PS2ValueRecordCnt = 0;
				PS1ValueRecordCnt = 0;
				noteState |= STATE_FORWARD_COVER_ENTERANCE;
#ifdef DEBUG_MODE
				testflag[2] = 1;
				testflag2[2] = testflag2Cnt++;
#endif
				g_maxMpFromEnteranceToPs1 = MP_FROM_ENTERANCE_TO_Ps1;
				tempMgDataLen = 0;
				gb_haveNoteInEntergate = 0;
				gb_needScanEteranceSensor = 0;
				
			}
		}
		else
		{
			if((noteState&STATE_BACKWARD_COVER_ENTERANCE) > 0)
			{
				noteState &= (~STATE_BACKWARD_COVER_ENTERANCE);
//				gb_notebackInEnteranceFlag = 0;
#ifdef DEBUG_MODE
				testflag[3] = 1;
				testflag2[3] = testflag2Cnt++;
#endif
			}
		}
	}
	
}

u8 GetAdjustedData(u8 value,u8 index)
{
	float y,x;
	u8 a;
	if(value >= lengthIdleOriginValue[index] - LENGTH_HAVENOTE_VALUE_THRES)
	{
		return value;
	}
	
	x = value;
	y = kAdjust[index]*x + bAdjust[index];
	

	if(y <= 0.00)
	{
		y = 0;
	}
	else if(y > 255.0)
	{
		y = 0xff;
	}
	a = (u8)y;
	return a;
}

void computeAdjustData(void)
{
	u8 bz40gStdVal;
	u8 bz80gStdVal;
	float irBz40g,irBz80g;

	u8 index;
	float k,b;

	bz40gStdVal = CCHWMAXVALUE;
	bz80gStdVal = CCHWMINVALUE;
	
	for(index = 0;index<REAL_IR_NUM;index++)
	{
		irBz40g = (float)savedPara.adjustPara.irBz40gStandard[index]/10;
		irBz80g = (float)savedPara.adjustPara.irBz80gStandard[index]/10;
		
	 	if(irBz40g != irBz80g)
		{
	 		k = ((float)bz40gStdVal - bz80gStdVal)/(irBz40g -irBz80g);
		}
		else
		{
			k = 0;
		}
		b = bz40gStdVal-k*irBz40g;

		kAdjust[index] = k;
		bAdjust[index] = b;
	}
// 	for(i=0; i<REAL_IR_NUM; i++)
// 	{
// 			gb_irStandard[i] = (u8)(kAdjust[i]*machineWorkPara.irStandard[i]+bAdjust[i]);
// 	}
}

// void ScanKeyDown(void)
// {
// 	if(gb_needCheckKey == 1)
// 	{
// 		gb_needCheckKey = 0;
// 		currentLcdKey = tm16xx_readKey();						
// 		if (!gb_longLcdKey)
// 		{
// 			if (currentLcdKey == KEY_noKey)
// 			{
// 				if (shortLcdKeyTimer == 0)
// 				{			
// 					fifo_DataIn(KB_FIFO,shortLcdKey);	
// 					LongBeep(1);					
// 				}
// 				enterLongLcdKeyTimer = ENTER_LONG_KEY_TIME;
// 				shortLcdKeyTimer = SHORT_KEY_TIME;
// 			}
// 			else
// 			{
// 				if (shortLcdKeyTimer > 0)
// 				{
// 					shortLcdKeyTimer --;
// 					if (shortLcdKeyTimer == 0)
// 					{
// 						shortLcdKey = currentLcdKey;
// 					}
// 				}
// 				
// 				if(enterLongLcdKeyTimer > 0)
// 				{
// 					enterLongLcdKeyTimer --;
// 					if (enterLongLcdKeyTimer == 0)
// 					{
// 						longLcdKeyIntervalTimer = LONG_KEY_INTERVAL_TIME;
// 						gb_longLcdKey = 1;
// 						longLcdKey = currentLcdKey;	
// 						
// 						fifo_DataIn(KB_FIFO,longLcdKey+LONG_LCD_KEY_ADDVAL);		
// 						LongBeep(1);	
// 					}
// 				}
// 			}
// 		}
// 		else
// 		{
// 			if (currentLcdKey == longLcdKey)
// 			{
// 				if (longLcdKeyIntervalTimer > 0)
// 				{
// 					longLcdKeyIntervalTimer --;
// 					if (longLcdKeyIntervalTimer == 0)
// 					{
// 						//kbfifo_DataIn(longLcdKey+LONG_LCD_KEY_ADDVAL);
// 						//KeyBeep(1);
// 						//sendOneKey(longLcdKey+LONG_LCD_KEY_ADDVAL);
// 						fifo_DataIn(KB_FIFO,longLcdKey+LONG_LCD_KEY_ADDVAL);				
// 						LongBeep(1);	
// 					}
// 				}
// 			}
// 			else
// 			{
// 				gb_longLcdKey = 0;
// 				longLcdKey = KEY_noKey;
// 				shortLcdKey = KEY_noKey;
// 				shortLcdKeyTimer = SHORT_KEY_TIME;
// 				enterLongLcdKeyTimer = ENTER_LONG_KEY_TIME;
// 				longLcdKeyIntervalTimer = LONG_KEY_INTERVAL_TIME;
// 			}
// 		}
// 		lastLcdKey = currentLcdKey;	
// 	}
// }

u8 GetCertainStrFromLongStr(u8 *pStr,u8 index,u8 *pCertainStr)
{
	u16 j;
	u8 num;
	u8 * pd;
	u8 valueStrNum;
	u8 k;
	u8 oneStr;
	u8 tempString[MAX_ITEM_STR_NUM];
	
	pd = pStr;
	num = ((*(pd+0)) - '0')*10+((*(pd+1)) - '0');//有几个可以切换的选项
	if(num == 0)//直接显示数值的
	{
		*pCertainStr = '\0';
		return 0;
	}
	else//显示项目的
	{
		if(index >= num)//如果键值大于模值 置零
		{
			index = 0;
		}
		//解析出num个字符串
		k = 0;
		oneStr = 0;
		valueStrNum = 0;
	
		//读出可切换的字符串
		for(j=2; j<strlen(pd); j++)
		{
			if(*(pd + j) == '|')
			{
				if(oneStr == 0)
				{
					k = 0;
					oneStr = 1;
					memset(tempString,'\0',sizeof(tempString));
				}
				else
				{
					//上一个结束
					if(index == valueStrNum)
					{
						memcpy(pCertainStr,tempString,k+1);
						return 1;
					}
					valueStrNum ++;
	
					k = 0;
					oneStr = 1;		
					memset(tempString,'\0',sizeof(tempString));
				}
			}
			else
			{
				if(k < MAX_ITEM_STR_NUM-1)
				{
					tempString[k] = *(pd + j);
					k ++;
				}
			}
		}
		if(oneStr == 1)
		{
			if(index == valueStrNum)
			{
				memcpy(pCertainStr,tempString,k+1);
				return 1;
			}
		}
	}
}

void DispClassicBar(u16 color,u8 type)
{
	switch(type)
	{
		case 0://TOP BAR
			disp_drawRectangle(TOP_BAR_X,TOP_BAR_Y,TOP_BAR_W,TOP_BAR_H,color);
			break;
		case 1://MID BAR
			disp_drawRectangle(MID_BAR_X,MID_BAR_Y,MID_BAR_W,MID_BAR_H,color);
			break;
		case 2://BOTTOM BAR
			disp_drawRectangle(BOTTOM_BAR_X,BOTTOM_BAR_Y,BOTTOM_BAR_W,BOTTOM_BAR_H,color);
			break;
		default:
			break;
	}
}
void DispIdentificationWays(void)
{
	if((savedPara.identificationWays&IR_WAY) == IR_WAY)
	{
		disp_DrawPic(BMP_FIR_X,BMP_FIR_Y,BMP_AFIR);
	}
	else
	{
		disp_DrawPic(BMP_FIR_X,BMP_FIR_Y,BMP_AFB);
	}
	if((savedPara.identificationWays&UV_WAY) == UV_WAY)
	{
		disp_DrawPic(BMP_FUV_X,BMP_FUV_Y,BMP_AFUV);
	}
	else
	{
		disp_DrawPic(BMP_FUV_X,BMP_FUV_Y,BMP_AFB);
	}
	if((savedPara.identificationWays&MG_WAY) == MG_WAY)
	{
		disp_DrawPic(BMP_FMG_X,BMP_FMG_Y,BMP_AFMG);
	}
	else
	{
		disp_DrawPic(BMP_FMG_X,BMP_FMG_Y,BMP_AFB);
	}
	if((savedPara.identificationWays&RGB_WAY) == RGB_WAY)
	{
		disp_DrawPic(BMP_FCIS_X,BMP_FUV_Y,BMP_CFRGB);
	}
	else
	{
		disp_DrawPic(BMP_FCIS_X,BMP_FUV_Y,BMP_AFB);
	}
	disp_DrawPic(BMP_FCIS_X,BMP_FCIS_Y,BMP_AFCIS);

}
void DispMainMenuBackground(void)
{

		disp_DrawPic(0,0,BMP_BOPENBLACK);

//		DispIdentificationWays();
		if(g_currency > NOTE_NUM)
		{
			g_currency = 	INDEX_USD;
		}
		disp_DrawPic(0,0,NationFlagBMP[g_currency][0]);
		disp_DrawPic(BMP_LIST_X,BMP_LIST_Y,NationFlagBMP[g_currency][1]);
		
		disp_DrawPic(BMP_PCS_X,BMP_PCS_Y,BMP_APCS);
}
#define IR_X 45
void DispIRCalibration(void)
{
	u8 i;
	if(gb_incalibrationByKey == 1)
	{
		disp_clearScreen(BLACK);
		disp_setPenColor(WHITE);
		disp_setBackColor(BLACK);
		disp_setFont(24);

		if(gb_irCalibrationDisp == 0)
		{
			disp_string("Start Ir Calibration",0,30);
			disp_setPenColor(RED);
			disp_string("Please Use 127G",0,190);
			disp_setPenColor(WHITE);
			disp_string("Ir Value:",0,60);
			for(i=0; i<7; i++)
			{
				U8ToStr(savedPara.adjustPara.irIdleStandard[20-i],dispStr);
				disp_string(dispStr,2+IR_X*i,90);
			}
			for(i=0; i<7; i++)
			{
				U8ToStr(savedPara.adjustPara.irIdleStandard[13-i],dispStr);
				disp_string(dispStr,2+IR_X*i,120);
			}
			for(i=0; i<7; i++)
			{
				U8ToStr(savedPara.adjustPara.irIdleStandard[6-i],dispStr);
				disp_string(dispStr,2+IR_X*i,150);
			}
		}
		else if(gb_irCalibrationDisp == 1)
		{
			disp_string("127G Ir Calibration",0,30);
			disp_string("Ir Value:",0,60);
			for(i=0; i<7; i++)
			{
				U16ToStr(collabrationValue[20-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,90);
			}
			for(i=0; i<7; i++)
			{
				U16ToStr(collabrationValue[13-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,120);
			}
			for(i=0; i<7; i++)
			{
				U16ToStr(collabrationValue[6-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,150);
			}
		}
		else if(gb_irCalibrationDisp == 2)
		{
			disp_string("127G Ir Calibration End",0,30);
			disp_setPenColor(RED);
			disp_string("Please Use 80G",0,190);
			disp_setPenColor(WHITE);
			disp_string("Ir Value:",0,60);
			for(i=0; i<7; i++)
			{
				U16ToStr(savedPara.adjustPara.irBz80gStandard[20-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,90);
			}
			for(i=0; i<7; i++)
			{
				U16ToStr(savedPara.adjustPara.irBz80gStandard[13-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,120);
			}
			for(i=0; i<7; i++)
			{
				U16ToStr(savedPara.adjustPara.irBz80gStandard[6-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,150);
			}
		}
		else if(gb_irCalibrationDisp == 3)
		{
			disp_string("80G Ir Calibration",0,30);
			disp_string("Ir Value:",0,60);
			for(i=0; i<7; i++)
			{
				U16ToStr(collabrationValue[20-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,90);
			}
			for(i=0; i<7; i++)
			{
				U16ToStr(collabrationValue[13-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,120);
			}
			for(i=0; i<7; i++)
			{
				U16ToStr(collabrationValue[6-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,150);
			}
		}
		else if(gb_irCalibrationDisp == 4)
		{
			disp_setPenColor(RED);
			disp_string("Finish Ir Calibration",0,30);
			disp_setPenColor(WHITE);
			disp_string("Ir Value:",0,60);
			for(i=0; i<7; i++)
			{
				U16ToStr(savedPara.adjustPara.irBz40gStandard[20-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,90);
			}
			for(i=0; i<7; i++)
			{
				U16ToStr(savedPara.adjustPara.irBz40gStandard[13-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,120);
			}
			for(i=0; i<7; i++)
			{
				U16ToStr(savedPara.adjustPara.irBz40gStandard[6-i],dispStr,3);
				disp_string(dispStr,2+IR_X*i,150);
			}
		}
	}
}
#define COLOR_X 50
void DispColorCalibration(void)
{
	u8 i; 
	if(gb_incalibrationByKey == 1)
	{	
		disp_clearScreen(BLACK);
		disp_setPenColor(WHITE);
		disp_setBackColor(BLACK);
		disp_setFont(24);

		if(gb_inCollabration == COLLABRATION_COLOR)//开始校正
		{
			disp_setPenColor(RED);
			disp_string("Please USE A4",0,5);
			disp_setPenColor(WHITE);
			disp_string("Start Color Calibration",0,30);
		}
		else
		{
			disp_string("Finish Color Calibration",0,30);
			for(i=0; i<6; i++)
			{
				U8ToStr(savedPara.adjustPara.colorAdjust[i],dispStr);
				disp_string(dispStr,10+COLOR_X*i,60);
			}
			for(i=0; i<6; i++)
			{
				U8ToStr(savedPara.adjustPara.colorAdjust[i+6],dispStr);
				disp_string(dispStr,10+COLOR_X*i,90);
			}
			
		}
	}	
}

#define UV_X 50
void DispUVCalibration(void)
{
	u8 i; 
	if(gb_incalibrationByKey == 1)
	{	
		disp_clearScreen(BLACK);
		disp_setPenColor(WHITE);
		disp_setBackColor(BLACK);
		disp_setFont(24);

		if(gb_inCollabration == COLLABRATION_UV)//开始校正
		{
			disp_setPenColor(RED);
			disp_string("Please USE A4",0,5);
			disp_setPenColor(WHITE);
			disp_string("Start UV Calibration",0,30);
		}
		else
		{
			disp_string("Finish UV Calibration",0,30);

			U8ToStr(savedPara.uvWhiteValue,dispStr);
			disp_string(dispStr,10+UV_X,60);
			
		}
	}	
}

u8 * const ONOFF_STR[] = 
{
	"OFF",
	"ON ",
	"ALL",
};
u8 * const Direction_STR[] = 
{
	"Forward ",
	"Backward",
	"MODE3   ",
	"OFF     ",
};
u8 * const UVgrade_STR[] = 
{
	"UV0 ",
	"UV1 ",
	"UV2 ",
	"UV3 ",
	"UV4 ",
	"UV5 ",
	"UV6 ",
	"UV7 ",
	"UV8 ",
	"UV9 ",	
	"UV10",
	"UV11",
	"UV12",
	"UV13",
	"UV14",
	"UV15",
	"UV16",
	"UV17",
	"UV18",
	"UV19",
	"UV20",
	"UV21",
	"UV22",
	"UV23",
	"UV24",
	"UV25",
	"UV26",
	"UV27",
	"UV28",
	"UV29",
};
u8 * const Color_STR[] = 
{
	"R  ",
	"G  ",
	"B  ",
	"OFF",
};
#define ENGMODE_X 180
#define ENGMODE_Y 0
#define ENGMODE_W 8
#define ENGMODE_H 20
void DispEngMode(void)
{
	disp_clearScreen(BLACK);
	disp_setPenColor(WHITE);
	disp_setBackColor(BLACK);
	disp_setFont(16);
	
	disp_string("EN",0,0);
	disp_string("PS1",ENGMODE_W*12,0);
	disp_string("PS2",ENGMODE_W*25,0);
	disp_string("RGB",0,ENGMODE_H);
	disp_string("IR",0,ENGMODE_H*4);
	disp_string("MG",0,ENGMODE_H*9);
	disp_string("UV",ENGMODE_W*13,ENGMODE_H*9);
	disp_string("MOTOR",0,ENGMODE_H*10);
	SampleOneRow();
	DispEngModeValue();
	DispEngModeSetting();
	DispEngModeSettingSelected();
}
void DispEngModeValue(void)
{
	u8 i;
	disp_setPenColor(WHITE);
	disp_setBackColor(BLACK);
	disp_setFont(16);

	U8ToStr(enteranceSensorVal,dispStr);
	disp_string(dispStr,ENGMODE_W*7,0);

	U8ToStr(tdjsValue[0],dispStr);
	disp_string(dispStr,ENGMODE_W*20,0);

	U8ToStr(tdjsValue[1],dispStr);
	disp_string(dispStr,ENGMODE_W*33,0);

	//RGB
	U8ToStr(colorRGB[0][0],dispStr);
	disp_string(dispStr,ENGMODE_W*8,ENGMODE_H);
	
	U8ToStr(colorRGB[0][1],dispStr);
	disp_string(dispStr,ENGMODE_W*12,ENGMODE_H);
	
	U8ToStr(colorRGB[0][2],dispStr);
	disp_string(dispStr,ENGMODE_W*16,ENGMODE_H);
	
	U8ToStr(colorRGB[1][0],dispStr);
	disp_string(dispStr,ENGMODE_W*20,ENGMODE_H);
	
	U8ToStr(colorRGB[1][1],dispStr);
	disp_string(dispStr,ENGMODE_W*24,ENGMODE_H);
	
	U8ToStr(colorRGB[1][2],dispStr);
	disp_string(dispStr,ENGMODE_W*28,ENGMODE_H);
	
	U8ToStr(colorRGB[2][0],dispStr);
	disp_string(dispStr,ENGMODE_W*8,ENGMODE_H*2);
	
	U8ToStr(colorRGB[2][1],dispStr);
	disp_string(dispStr,ENGMODE_W*12,ENGMODE_H*2);
	
	U8ToStr(colorRGB[2][2],dispStr);
	disp_string(dispStr,ENGMODE_W*16,ENGMODE_H*2);
	
	U8ToStr(colorRGB[3][0],dispStr);
	disp_string(dispStr,ENGMODE_W*20,ENGMODE_H*2);
	
	U8ToStr(colorRGB[3][1],dispStr);
	disp_string(dispStr,ENGMODE_W*24,ENGMODE_H*2);
	
	U8ToStr(colorRGB[3][2],dispStr);
	disp_string(dispStr,ENGMODE_W*28,ENGMODE_H*2);
	//IR
	for(i=0;i<7;i++)
	{
		U8ToStr(irValue[i],dispStr);
		disp_string(dispStr,ENGMODE_W*(8+4*i),ENGMODE_H*4);
		
		U8ToStr(irValue[i+7],dispStr);
		disp_string(dispStr,ENGMODE_W*(8+4*i),ENGMODE_H*5);
		
		U8ToStr(irValue[i+14],dispStr);
		disp_string(dispStr,ENGMODE_W*(8+4*i),ENGMODE_H*6);
	}
	U8ToStr(mrValue[0],dispStr);
	disp_string(dispStr,ENGMODE_W*3,ENGMODE_H*9);
	U8ToStr(mrValue[1],dispStr);
	disp_string(dispStr,ENGMODE_W*7,ENGMODE_H*9);
	U8ToStr(UvValue,dispStr);
	disp_string(dispStr,ENGMODE_W*20,ENGMODE_H*9);
	
	//disp_string(UVgrade_STR[savedPara.uvGrade],ENGMODE_W*23,ENGMODE_H*9);
	U8ToStr(gb_uvTher[savedPara.uvGrade],dispStr);
	disp_string(dispStr,ENGMODE_W*28,ENGMODE_H*9);
}
void DispEngModeSetting(void)
{
	u16 x,y;
	disp_setPenColor(WHITE);
	disp_setBackColor(BLACK);
	disp_setFont(16);	
	
	x = ENGMODE_W*3;
	y = 0;
	disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);

	x = ENGMODE_W*16;
	y = 0;
	disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);

	x = ENGMODE_W*29;
	y = 0;
	disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);
	
	x = ENGMODE_W*4;
	y = ENGMODE_H;
	disp_string(Color_STR[g_colorFsRGB],x,y);

	x = ENGMODE_W*4;
	y = ENGMODE_H*4;
	disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);

	x = ENGMODE_W*16;
	y = ENGMODE_H*9;
	disp_string(ONOFF_STR[gb_uvVccIsOn],x,y);
	
	x = ENGMODE_W*24;
	y = ENGMODE_H*9;
	disp_string(UVgrade_STR[savedPara.uvGrade],x,y);
	
	x = ENGMODE_W*6;
	y = ENGMODE_H*10;
	disp_string(Direction_STR[g_motorRunState],x,y);
}

void DispEngModeSettingSelected(void)
{
	u16 x,y;
	disp_setPenColor(BLACK);
	disp_setBackColor(WHITE);
	disp_setFont(16);

	switch(selectedItemIndex)
	{
		case 0:
			x = ENGMODE_W*3;
			y = 0;
			disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);
			break;
		case 1:
			x = ENGMODE_W*16;
			y = 0;
			disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);
			break;
		case 2:
			x = ENGMODE_W*29;
			y = 0;
			disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);
			break;
		case 3:
			x = ENGMODE_W*4;
			y = ENGMODE_H;
			disp_string(Color_STR[g_colorFsRGB],x,y);
			break;
		case 4:
			x = ENGMODE_W*4;
			y = ENGMODE_H*4;
			disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);
			break;
		case 5:
			x = ENGMODE_W*16;
			y = ENGMODE_H*9;
			disp_string(ONOFF_STR[gb_uvVccIsOn],x,y);
			break;
		case 6:
			x = ENGMODE_W*24;
			y = ENGMODE_H*9;
			disp_string(UVgrade_STR[savedPara.uvGrade],x,y);
		break;
		case 7:
			x = ENGMODE_W*6;
			y = ENGMODE_H*10;
			disp_string(Direction_STR[g_motorRunState],x,y);
			break;
		default:
			break;						
	}
	
	if(lastSelectedItemIndex == selectedItemIndex)
	{
		return;
	}
	disp_setPenColor(WHITE);
	disp_setBackColor(BLACK);	
	switch(lastSelectedItemIndex)
	{
		case 0:
			x = ENGMODE_W*3;
			y = 0;
			disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);
			break;
		case 1:
			x = ENGMODE_W*16;
			y = 0;
			disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);
			break;
		case 2:
			x = ENGMODE_W*29;
			y = 0;
			disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);
			break;
		case 3:
			x = ENGMODE_W*4;
			y = ENGMODE_H;
			disp_string(Color_STR[g_colorFsRGB],x,y);
			break;
		case 4:
			x = ENGMODE_W*4;
			y = ENGMODE_H*4;
			disp_string(ONOFF_STR[gb_hwVccIsOn],x,y);
			break;
		case 5:
			x = ENGMODE_W*16;
			y = ENGMODE_H*9;
			disp_string(ONOFF_STR[gb_uvVccIsOn],x,y);
			break;
		case 6:
			x = ENGMODE_W*24;
			y = ENGMODE_H*9;
			disp_string(UVgrade_STR[savedPara.uvGrade],x,y);
		break;
		case 7:
			x = ENGMODE_W*6;
			y = ENGMODE_H*10;
			disp_string(Direction_STR[g_motorRunState],x,y);
			break;
		default:
			break;								
	}
}

#define SETTING_X 180
#define SETTING_Y 0
#define SETTING_H 30

void DispMenu1(void)
{
	disp_clearScreen(BLACK);
	disp_setPenColor(WHITE);
	disp_setBackColor(BLACK);
	disp_setFont(24);
	disp_string("Beep         :",0,SETTING_Y);
	disp_string("NoteLeave    :",0,SETTING_Y+SETTING_H);
	disp_string("ErrDataOutput:",0,SETTING_Y+SETTING_H*2);
	disp_string("CoCalibration:",0,SETTING_Y+SETTING_H*3);
	disp_string("IRCalibration:",0,SETTING_Y+SETTING_H*4);
	disp_string("UVCalibration:",0,SETTING_Y+SETTING_H*5);
	disp_string("EngMode      :",0,SETTING_Y+SETTING_H*6);
	disp_string("Upgrade      :",0,SETTING_Y+SETTING_H*7);
	disp_string(VERSION,320-72,240-24);
	DispSetting();
	DispSettingSelected();
}

void DispSetting(void)
{
	u16 x,y;
	disp_setPenColor(WHITE);
	disp_setBackColor(BLACK);
	disp_setFont(24);	
	
	x = SETTING_X;
	y = SETTING_Y;
	disp_string(ONOFF_STR[savedPara.beepSwitch],x,y);

	x = SETTING_X;
	y = SETTING_Y+SETTING_H;
	disp_string(Direction_STR[savedPara.noteLeaveRoads],x,y);

	x = SETTING_X;
	y = SETTING_Y+SETTING_H*2;
	disp_string(ONOFF_STR[gb_needOutPutErrData],x,y);
	
	x = SETTING_X;
	y = SETTING_Y+SETTING_H*3;
	disp_string("Enter",x,y);
	
	x = SETTING_X;
	y = SETTING_Y+SETTING_H*4;
	disp_string("Enter",x,y);
	
	x = SETTING_X;
	y = SETTING_Y+SETTING_H*5;
	disp_string("Enter",x,y);
	
	x = SETTING_X;
	y = SETTING_Y+SETTING_H*6;
	disp_string("Enter",x,y);

	x = SETTING_X;
	y = SETTING_Y+SETTING_H*7;
	disp_string("Enter",x,y);
}

void DispSettingSelected(void)
{
	u16 x,y;
	disp_setPenColor(BLACK);
	disp_setBackColor(WHITE);
	disp_setFont(24);

	switch(selectedItemIndex)
	{
		case 0:
			x = SETTING_X;
			y = SETTING_Y;
			disp_string(ONOFF_STR[savedPara.beepSwitch],x,y);
			break;
		case 1:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H;
			disp_string(Direction_STR[savedPara.noteLeaveRoads],x,y);
			break;
		case 2:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*2;
			disp_string(ONOFF_STR[gb_needOutPutErrData],x,y);
			break;
		case 3:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*3;
			disp_string("Enter",x,y);
			break;
		case 4:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*4;
			disp_string("Enter",x,y);
			break;
		case 5:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*5;
			disp_string("Enter",x,y);
			break;
		case 6:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*6;
			disp_string("Enter",x,y);
			break;
		case 7:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*7;
			disp_string("Enter",x,y);
			break;
		default:
			break;						
	}
	
	if(lastSelectedItemIndex == selectedItemIndex)
	{
		return;
	}
	disp_setPenColor(WHITE);
	disp_setBackColor(BLACK);	
	switch(lastSelectedItemIndex)
	{
		case 0:
			x = SETTING_X;
			y = SETTING_Y;
			disp_string(ONOFF_STR[savedPara.beepSwitch],x,y);
			break;
		case 1:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H;
			disp_string(Direction_STR[savedPara.noteLeaveRoads],x,y);
			break;
		case 2:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*2;
			disp_string(ONOFF_STR[gb_needOutPutErrData],x,y);
			break;
		case 3:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*3;
			disp_string("Enter",x,y);
			break;
		case 4:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*4;
			disp_string("Enter",x,y);
			break;
		case 5:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*5;
			disp_string("Enter",x,y);
			break;
		case 6:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*6;
			disp_string("Enter",x,y);
			break;
		case 7:
			x = SETTING_X;
			y = SETTING_Y+SETTING_H*7;
			disp_string("Enter",x,y);
			break;
		default:
			break;						
	}
}

void EngModeParaInc(void)
{
	u8 i,r;
	switch(selectedItemIndex)
	{
		case 0:
		case 1:
		case 2:
		case 4:		
			if(gb_hwVccIsOn == 1)
			{
				hwfs_Off();
				jckfs_Off();
			}
			else
			{
				hwfs_On();
				jckfs_On();
			}
		break;
		case 3:
			if(g_colorFsRGB == FS_BLUE)
			{
				redFs_On();
				greenFs_Off();
				blueFs_Off();
				//g_colorFsRGB = FS_RED;
			}
			else if(g_colorFsRGB == FS_RED)
			{
				redFs_Off();
				greenFs_On();
				blueFs_Off();
				//g_colorFsRGB = FS_GREEN;
			}
			else if(g_colorFsRGB == FS_GREEN)
			{
				redFs_Off();
				greenFs_Off();
				blueFs_Off();
				g_colorFsRGB = FS_OFF;
				//g_colorFsRGB = FS_BLUE;
			}	
			else
			{
				redFs_Off();
				greenFs_Off();
				blueFs_On();					
			}
		break;
		case 5://UV
			if(gb_uvVccIsOn == 1)
			{
				uvfs_Off();
			}
			else
			{
				uvfs_On();
			}
		break;
		case 6:
			savedPara.uvGrade++;
			savedPara.uvGrade %= 30;//NUMBER_OF_ARRAY(gb_uvTher);
			
		break;
		case 7://MOTOR
			if(g_motorRunState == 0)
			{
				motor1_BackwardRun();
				g_motorRunState = 1;
			}
			else if(g_motorRunState == 2)
			{
				motor1_ForwardRun();
				g_motorRunState = 0;
			}
			else
			{
				motor1_Stop();
				g_motorRunState = 2;
			}
		break;
		default:
			break;						
	}
	
}

void SettingParaInc(void)
{
	u8 i,r;
	u32 fileLen;
	switch(selectedItemIndex)
	{
		case 0:
 			savedPara.beepSwitch ++;
 			savedPara.beepSwitch %= 2;
			gb_paraChanged = 1;
		break;
		case 1:
 			savedPara.noteLeaveRoads ++;
 			savedPara.noteLeaveRoads %= 3;
			gb_paraChanged = 1;
		break;
		case 2:
 			gb_needOutPutErrData ++;
 			gb_needOutPutErrData %= 3;
		break;
		case 3://进入颜色校正界面
			g_colorFsStopWork = 0;
			SetSystemState(NORMAL);
			gb_enableSample = 1;
			delay_DelayMs(100);
			gb_inCollabration = COLLABRATION_COLOR;
			gb_colorInOriginData = 1;
			DispString("开始颜色校正,放入A4纸",1);
			gb_incalibrationByKey = 1;
			DispColorCalibration();
		break;
		case 4://进入红外校正界面
			hwfs_On();
			SetSystemState(NORMAL);
			gb_enableSample = 1;
			delay_DelayMs(100);
			
			memcpy(savedPara.adjustPara.irIdleStandard,irValue,REAL_IR_NUM);
			DispString("空载红外值",1);
			for(i = 0;i < REAL_IR_NUM;i++)
			{
				dispStr[0] = ' ';
				U8ToStr(savedPara.adjustPara.irIdleStandard[i],dispStr+1);
				DispString(dispStr,0);
			}
			DispString(" ",1);
			memcpy(lengthIdleOriginValue,savedPara.adjustPara.irIdleStandard,REAL_IR_NUM);
			
			gb_inCollabration = COLLABRATION_80G_BZ;
			collabrationNoteNum = 0;
			memset(collabrationSum,0,REAL_IR_NUM*4);
			memset(collabrationNum,0,REAL_IR_NUM);
			memset(collabrationMax,0,REAL_IR_NUM*2);
			memset(collabrationMin,0xff,REAL_IR_NUM*2);
			DispString("开始厚白纸校正,放入127g厚白纸",1);
			gb_incalibrationByKey = 1;
			DispIRCalibration();
			gb_irCalibrationDisp = 1;
		break;
		case 5:
			SetSystemState(NORMAL);
			gb_enableSample = 1;
			delay_DelayMs(100);
			gb_inCollabration = COLLABRATION_UV;
			DispString("开始UV校正,放入白纸",1);
			gb_incalibrationByKey = 1;
			DispUVCalibration();
		break;
		case 6://工程师模式
			selectedItemIndex = 0;
			lastSelectedItemIndex = 0;
			//停止自动采集
			motor1_Stop();
			gb_enableSample = 0;
			g_motorRunState = 2;
			SetSystemState(ENG_MODE);
			DispEngMode();
		break;
		case 7:
	#ifdef BOOT_APP
			if(gb_udsikIsOnLine == 0)
			{
				disp_setPenColor(RED);
				disp_setBackColor(BLACK);
				disp_setFont(24);
				disp_string("NO UDISK",320-96,0);
				gb_haveErrUdiskInforDisp = 1;
			}
			else
			{
				r = f_open(&file, upgradeFileName, FA_OPEN_EXISTING);
				if(r == 0)
				{
					flash_SaveUpdateFlag(NEED_UPGRADE_FLAG);
					delay_DelayMs(100);
					NVIC_SystemReset();
				}
				else
				{
					disp_setPenColor(RED);
					disp_setBackColor(BLACK);
					disp_setFont(24);
					disp_string("NO FILE ",320-96,0);
					gb_haveErrUdiskInforDisp = 1;
				}
			}

	#endif
		break;
		default:
			break;						
	}
	
}


void DispMainMenu(void)
{
	DispMainMenuBackground();
	//disp_clearScreen(WHITE);
	//DispCurrency();
	DispFunInfo();
	//LCD_DispString(0,100,WHITE,RED,16,"WELCOME");
	DispNoteNumValSum();
	
	DispJamInfo();
    DispDirectionInfo();
}
void DispUdiskInfo(void)
{
	if(gb_udsikIsOnLine == 1)
	{
		disp_setFont(FONT_24);
		disp_setBackColor(BLACK);
		disp_setPenColor(WHITE);			
	}
	else
	{
		disp_setFont(FONT_24);
		disp_setBackColor(BLACK);
		disp_setPenColor(BLACK);
	}
	disp_string("U",BMP_FADD_X,BMP_FADD_Y-24);
}
void DispDirectionInfo(void)
{
    disp_setFont(FONT_24);
    disp_setBackColor(BLACK);
    disp_setPenColor(WHITE);
	if(savedPara.noteLeaveRoads == 1)
	{
		disp_string("B",BMP_FADD_X,BMP_FADD_Y+24);	
	}
	else
	{
        disp_string("F",BMP_FADD_X,BMP_FADD_Y+24);
	}
}
void DispFunInfo(void)
{
	if(g_needAddValue == WORK_ADD)
	{
		disp_DrawPic(BMP_FADD_X,BMP_FADD_Y,BMP_AFADD);
	}
	else
	{
		disp_DrawPic(BMP_FADD_X,BMP_FADD_Y,BMP_FADD_OFF);
	}
	
	if(savedPara.beepSwitch == 1)
	{
		disp_DrawPic(BMP_VOICE_X,BMP_VOICE_Y,BMP_ASPEAK_ON);
	}
	else
	{
		disp_DrawPic(BMP_VOICE_X,BMP_VOICE_Y,BMP_ASPEAK_OFF);
	}
}
//void DispCurrency(void)
//{
//	u8 r;
//	
//	disp_setBackColor(TOP_BAR_ICON_BACK_COLOR);
//	disp_drawRectangle(CURRENCY_ICON_X,CURRENCY_ICON_Y,CURRENCY_ICON_W,CURRENCY_ICON_H,TOP_BAR_ICON_BACK_COLOR);	
//	disp_setPenColor(TOP_BAR_ICON_PEN_COLOR);		
//	if(g_languageIndex == INDEX_ENGLISH)
//	{
//		disp_setFont(CURRENCY_FONT);
//		r = GetCertainStrFromLongStr(CURRENCY_TITLE_STR_ENGLISH,g_currency,dispStr);
//		disp_string(dispStr,CURRENCY_X,CURRENCY_Y);			
//	}
//	else
//	{
//		disp_setFont(CURRENCY_CHINESE_FONT);
//		r = GetCertainStrFromLongStr(CURRENCY_TITLE_STR_CHINESE,g_currency,dispStr);
//		disp_string(dispStr,CURRENCY_CHINESE_X,CURRENCY_CHINESE_Y);				
//	}
//}

void DispJamInfo(void)
{
	if(gb_isJammed > 0)
	{
		disp_setFont(FONT_24);
		disp_setBackColor(BLACK);
		disp_setPenColor(RED);
		memcpy(dispStr,"JAM:",4);
		U16ToStr(gb_isJammed,dispStr+4,2);
		disp_string(dispStr,0,BOTTOM_BAR_Y+4);	
	}
	else
	{
		disp_setFont(FONT_24);
		disp_setBackColor(BLACK);
		disp_setPenColor(BLACK);		
		memcpy(dispStr,"JAM:88",7);
		disp_string(dispStr,0,BOTTOM_BAR_Y+4);	
	}
}

void DispAutoRefreshMenu(void)//1秒钟显示一些需要自动刷新的界面
{
	if(gb_oneSecAutoRefresh == 1)
	{
		gb_oneSecAutoRefresh = 0;
		
		switch(systemState)
		{
			case NORMAL:
				break;
			case SENSOR_VIEW:
//				if(g_colorFsRGB == FS_BLUE)
//				{
//					redFs_On();
//					greenFs_Off();
//					blueFs_Off();
//				}
//				else if(g_colorFsRGB == FS_RED)
//				{
//					redFs_Off();
//					greenFs_On();
//					blueFs_Off();
//				}
//				else
//				{
//					redFs_Off();
//					greenFs_Off();
//					blueFs_On();
//				}
				SampleOneRow();
				DispSensorViewMenu();
				break;
			case ENG_MODE:
				SampleOneRow();
				DispEngModeValue();
			break;
			case LAO_HUA:
/*				if(gb_inLaoHua == 1)
				{
					if(laoHuaSingleTime > 0)
					{
						laoHuaSingleTime --;
						if(laoHuaSingleTime == 0)
						{
							if(g_motor1State == MOTOR_RUN)
							{
								hwfs_Off();	
								motor1_Stop();
								laoHuaSingleTime = LAOHUA_SINGLE_STOP_TIME;
								
								oneMinLaoHuaTime --;								
								if(oneMinLaoHuaTime == 0)
								{
									laoHuaTime --;
									DispLaoHuaTime();
									oneMinLaoHuaTime = ONE_MIN_LAOHUA;
									
									if(laoHuaTime == 0)
									{
										gb_inLaoHua = 0;
									}
								}
							}
							else
							{
								hwfs_On();	
								motor1_Run();
								laoHuaSingleTime = LAOHUA_SINGLE_RUN_TIME;													
							}																				
						}
					}				
				}*/
				break;
		}			
	}
}

u8 const *DENO_STR[] = 
{
"100元 2005版",
"100元 2015版",
" 50元       ",
" 20元       ",
" 10元       ",
"  5元       ",
"  1元       ",
"可疑币 E"};
void outputJudgeRlt(void)
{
	u8 k;
	//currentNoteType;
	//errorCode
	k = 0;
	U16ToStr04(irNoteNum,dispStr+k);
	k += 4;
	dispStr[k] = ' ';
	k += 1;
	
	if(currentNoteType == RMB_ARTI)
	{
		memcpy(dispStr+k,DENO_STR[currentNoteType],8);
		k += 8;
		U16ToTimeStr(errorCode,dispStr+k,2);
		k += 2;
	}
	else
	{
		memcpy(dispStr+k,DENO_STR[currentNoteType],12);
		k += 12;
	}
	dispStr[k] = '\0';
	k += 1;	
	DispString(dispStr,1);
}
void color_whiteStandard(void)
{
	u8 i, j, n;
	u32 colorDataSum[12];
	colorDataLen = g_colorSampleIndex;
	for(j=0; j<12; j++)
	{
		colorDataSum[j] = 0;
	}
	n=0;
	for(i=20; i<colorDataLen-20; i++)
	{
		n++;
		for(j=0; j<12; j++)
		{
			colorDataSum[j] += colorData[j][i];
		}
	}
	for(j=0; j<12; j++)
	{
		if(n > 0)
		{
			savedPara.adjustPara.colorAdjust[j] = colorDataSum[j]/n;
		}
		else
		{
			savedPara.adjustPara.colorAdjust[j] = 0;
		}
		dispStr[0] = ' ';
		U8ToStr(savedPara.adjustPara.colorAdjust[j],dispStr+1);
		DispString(dispStr,0);
	}
	
	gb_inCollabration = COLLABRATION_OFF;
	DispString("校正完成",1);
	DispColorCalibration();
	eeprom_SaveData();	
}
void uv_whiteStandard(void)
{
	u16 i, n;
	u32 uvDataSum;
	uvDataLen = g_uvSampleIndex;

	uvDataSum = 0;
	
	n=0;
	for(i=40; i<uvDataLen-40; i++)
	{
		n++;
		uvDataSum += uvData[i];
	}
	if(n > 0)
	{
		savedPara.uvWhiteValue = uvDataSum/n;
	}
	else
	{
		savedPara.uvWhiteValue = 180;
	}
	dispStr[0] = ' ';
	U8ToStr(savedPara.uvWhiteValue,dispStr+1);
	DispString(dispStr,0);
	
	gb_inCollabration = COLLABRATION_OFF;
	DispString("校正完成",1);
	DispUVCalibration();
	eeprom_SaveData();	
}
void lengthCollabrationProcess(void)
{
	u8 i;
	u8 k;
	
// 	dispStr[0] = ' ';
// 	U8ToStr(collabrationNoteNum+1,dispStr+1);
// 	DispString(dispStr,0);
// 	collabrationNoteNum ++;
	
	k = 0;
	for(i = 0;i < REAL_IR_NUM;i++)
	{
		dispStr[0] = ' ';
		U16ToStr(collabrationNum[REAL_IR_NUM-1-i],dispStr+1,5);
		DispString(dispStr,0);
		if(i < 1||i > REAL_IR_NUM-2)//最边上那个放弃校正
		{
			//if(collabrationNum[i] >= 1)
			{
				k ++;
			}
		}
		else
		{
			if(collabrationNum[i] >= COLLABRATION_FINSH_POINT_NUM)
			{
				k ++;
			}
		}
	}
	DispString(" ",1);
	for(i = 0;i < REAL_IR_NUM;i++)
	{
		dispStr[0] = ' ';
		U16ToStr(collabrationValue[REAL_IR_NUM-1-i],dispStr+1,5);
		DispString(dispStr,0);
	}
	DispString(" ",1);
	for(i = 0;i < REAL_IR_NUM;i++)
	{
		dispStr[0] = ' ';
		U16ToStr(collabrationSum[REAL_IR_NUM-1-i],dispStr+1,5);
		DispString(dispStr,0);
	}
	DispString(" ",1);
	for(i = 0;i < REAL_IR_NUM;i++)
	{
		dispStr[0] = ' ';
		U16ToStr(collabrationMax[REAL_IR_NUM-1-i],dispStr+1,5);
		DispString(dispStr,0);
	}
	DispString(" ",1);
	for(i = 0;i < REAL_IR_NUM;i++)
	{
		dispStr[0] = ' ';
		U16ToStr(collabrationMin[REAL_IR_NUM-1-i],dispStr+1,5);
		DispString(dispStr,0);
	}
	DispString(" ",1);
	DispString(" ",1);
	DispIRCalibration();
	if(k == REAL_IR_NUM)
	{
		if(gb_inCollabration == COLLABRATION_80G_BZ)
		{
			DispString(" ",1);
			//保存厚白纸数据
			for(i = 0;i < REAL_IR_NUM;i++)
			{
				if(collabrationNum[i] > 2)
				{
					collabrationNum[i] -= 2;
					collabrationSum[i] -= collabrationMax[i];
					collabrationSum[i] -= collabrationMin[i];
					savedPara.adjustPara.irBz80gStandard[i] = collabrationSum[i]/collabrationNum[i];
				}
				else
				{
					savedPara.adjustPara.irBz80gStandard[i] = CCHWMINVALUE*10;
				}
			}	
			
			for(i = 0;i < REAL_IR_NUM;i++)
			{
				dispStr[0] = ' ';
				U16ToStr(savedPara.adjustPara.irBz80gStandard[REAL_IR_NUM-1-i],dispStr+1,5);
				DispString(dispStr,0);
			}
			DispString(" ",1);
			
			DispString(" ",1);
			gb_irCalibrationDisp++;
			DispIRCalibration();
			//切换到40g白纸校正
			gb_inCollabration = COLLABRATION_40G_BZ;
			collabrationNoteNum = 0;
			memset(collabrationSum,0,REAL_IR_NUM*4);
			memset(collabrationNum,0,REAL_IR_NUM);
			memset(collabrationMax,0,REAL_IR_NUM*2);
			memset(collabrationMin,0xff,REAL_IR_NUM*2);
			DispString("开始薄白纸校正,放入80g薄白纸",1);
			gb_irCalibrationDisp++;			
		}
		else if(gb_inCollabration == COLLABRATION_40G_BZ)
		{
			DispString(" ",1);
			//保存薄白纸数据
			for(i = 0;i < REAL_IR_NUM;i++)
			{
				if(collabrationNum[i] > 2)
				{
					collabrationNum[i] -= 2;
					collabrationSum[i] -= collabrationMax[i];
					collabrationSum[i] -= collabrationMin[i];
					savedPara.adjustPara.irBz40gStandard[i] = collabrationSum[i]/collabrationNum[i];
				}
				else
				{
					savedPara.adjustPara.irBz40gStandard[i] = CCHWMAXVALUE*10;
				}
			}		
			
			for(i = 0;i < REAL_IR_NUM;i++)
			{
				dispStr[0] = ' ';
				U16ToStr(savedPara.adjustPara.irBz40gStandard[REAL_IR_NUM-1-i],dispStr+1,5);
				DispString(dispStr,0);
			}
			DispString(" ",1);
	
			DispString(" ",1);

			//完成 保存参数
			gb_inCollabration = COLLABRATION_OFF;
			DispString("校正完成",1);
			eeprom_SaveData();	
			computeAdjustData();
			gb_irCalibrationDisp++;
			DispIRCalibration();
		}		
	}
	
}
void DealNoteType(void)
{
	g_errFlag = 0;
	
	if(billValue != colorJudgeValue)
	{
		if(((savedPara.identificationWays&IR_WAY) == IR_WAY)&&((savedPara.identificationWays&RGB_WAY) == RGB_WAY))
		{
			if(g_currency == INDEX_USD)
			{
				g_errFlag = 0;
			}
			else if(g_currency == INDEX_CNY)
			{
				switch(billValue)
				{
				case 0:
				case 1:
				case 2:
					if(colorJudgeValue == 0)
					{
						g_errFlag = 0;
					}
					else
					{
						g_errFlag = 1;
					}
					break;
				case 3:
				case 4:
				case 5:
					if(colorJudgeValue == 3)
					{
						g_errFlag = 0;
					}
					else
					{
						g_errFlag = 1;
					}
					break;
					break;
				case 6:
				case 7:
				case 8:
					if(colorJudgeValue == 6)
					{
						g_errFlag = 0;
					}
					else
					{
						g_errFlag = 1;
					}
					break;
					break;
				case 9:
				case 10:
				case 11:
					if(colorJudgeValue == 9)
					{
						g_errFlag = 0;
					}
					else
					{
						g_errFlag = 1;
					}
					break;
					break;
				case 12:
				case 13:
				case 14:
					if(colorJudgeValue == 12)
					{
						g_errFlag = 0;
					}
					else
					{
						g_errFlag = 1;
					}
					break;
					break;
				case 15:
				case 16:
				case 17:
					if(colorJudgeValue == 15)
					{
						g_errFlag = 0;
					}
					else
					{
						g_errFlag = 1;
					}
					break;
					break;
				default:
					g_errFlag = 1;
					break;
				}			
			}
			else
			{
				g_errFlag = 1;
			}
		}
	}
	
	if(billIradMask == 1)
	{
		if((savedPara.identificationWays&IR_WAY) == IR_WAY)
		{
			g_errFlag |= ERR_IR;
		}
	}
	if(mgFvtFlag == 1)
	{
		if((savedPara.identificationWays&MG_WAY) == MG_WAY)
		{
			g_errFlag |= ERR_MG;
		}
	}
	if(billUVFvt == 1)
	{
		if((savedPara.identificationWays&UV_WAY) == UV_WAY)
		{	
			g_errFlag |= ERR_UV;
		}
	}
	if(g_errFlag == 0)
	{
		if((savedPara.identificationWays&IR_WAY) == IR_WAY)
		{
			gb_billValue = billValue;
		}
		else if((savedPara.identificationWays&RGB_WAY) == RGB_WAY)
		{
			if(g_currency == INDEX_USD)
			{
				gb_billValue = billValue;
			}
			else
			{
				gb_billValue = colorJudgeValue;
			}
		}
		else
		{
			gb_billValue = billValue;
		}
		switch(g_currency)
		{
			case INDEX_USD:
				{
				switch(gb_billValue)
				{
					case 0:
					case 1:
					case 2:
						currentNoteType = 0;
						break;
					case 3:
					case 4:
					case 5:
						currentNoteType = 1;
						break;
					case 6:
					case 7:
					case 8:
						currentNoteType = 2; 
						break;
					case 9:
					case 10:
					case 11:
						currentNoteType = 3;
						break;
					case 12:
					case 13:
					case 14:
						currentNoteType = 4;
						break;
					case 15:
						currentNoteType = 5;
						break;	
					case 18:
						currentNoteType = 6;
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}	
				}
			break;
				case INDEX_EUR:
					{
						switch(gb_billValue)
						{
						case 0:
						case 1:
							currentNoteType = 0;//500
							break;
						case 2:
						case 3:
							currentNoteType = 1;//200
							break;
						case 4:
						case 5:
							currentNoteType = 2; //100
							break;
						case 6:
						case 7:
							currentNoteType = 3;//50
							break;
						case 8:
						case 9:
							currentNoteType = 4;//20
							break;
						case 10:
						case 11:
							currentNoteType = 5;//10
							break;	
						case 12:
						case 13:		
							currentNoteType = 6;//5
							break;
						default:
							currentNoteType = 0xFF;
							g_errFlag |= ERR_VALUE;
							break;
						}
					}
				break;
				case INDEX_RUB:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
					case 2:			
						currentNoteType = 0;//5000
						break;
					case 3:
					case 4:
					case 5:
					case 6:
						currentNoteType = 1;//2000
						break;
					case 9:
					case 7:
					case 8:
						currentNoteType = 2; //1000
						break;
					case 12:
					case 10:
					case 11:
						currentNoteType = 3;//500
						break;
					case 15:
					case 13:
					case 14:
					case 16:
						currentNoteType = 4;//200
						break;
					case 17:
					case 18:
					case 19:
						currentNoteType = 5;//100
						break;	
					case 20:
					case 21:
					case 22:	
						currentNoteType = 6;//50
						break;	
					case 23:
					case 24:
					case 25:	
						currentNoteType = 7;//10
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_TRY:
				{
					switch(gb_billValue)
					{
					case 0:
						currentNoteType = 0;//200
						break;
					case 1:
						currentNoteType = 1;//100
						break;
					case 2:
						currentNoteType = 2; //50
						break;
					case 3:
						currentNoteType = 3;//20
						break;
					case 4:
						currentNoteType = 4;//10
						break;
					case 5:
						currentNoteType = 5;//5
						break;	
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}
				}
				break;
				case INDEX_IQD:
				{
					switch(gb_billValue)
					{
					case 0:
						currentNoteType = 0;//50000
						break;
					case 2:
					case 3:
						currentNoteType = 1;//25000
						break;
					case 4:
					case 5:	
						currentNoteType = 2; //10000
						break;
					case 6:
					case 7:
						currentNoteType = 3;//5000
						break;
					case 8:
					case 9:
						currentNoteType = 4;//1000
						break;
					case 10:
					case 11:
						currentNoteType = 5;//250
						break;	
					case 12:
					case 13:
						currentNoteType = 6;//50
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_SAR:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
                    case 16:
						currentNoteType = 0;//500
						break;
					case 2:
					case 3:
						currentNoteType = 1;//100
						break;
					case 4:
					case 5:	
                    case 20:
						currentNoteType = 2; //50
						break;
					case 6:
					case 7:
                    case 24:
						currentNoteType = 3;//20
						break;
					case 8:
					case 9:
                    case 26:
						currentNoteType = 4;//10
						break;
					case 10:
					case 11:
                    case 28:
						currentNoteType = 5;//5
						break;	
					case 12:
					case 13:
                    case 30:
						currentNoteType = 6;//1
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_AED:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
						currentNoteType = 0;//1000
						break;
					case 2:
					case 3:
						currentNoteType = 1;//500
						break;
					case 4:
					case 5:	
						currentNoteType = 2; //200
						break;
					case 6:
					case 7:
						currentNoteType = 3;//100
						break;
					case 8:
					case 9:
						currentNoteType = 4;//50
						break;
					case 10:
					case 11:
						currentNoteType = 5;//20
						break;	
					case 12:
					case 13:
						currentNoteType = 6;//10
						break;
					case 14:
					case 15:
						currentNoteType = 7;//5
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_GBP:
				{
					switch(gb_billValue)
					{
					case 0:
						currentNoteType = 0;//50
						break;
					case 1:
						currentNoteType = 1;//20
						break;
					case 2:
						currentNoteType = 2; //10
						break;
					case 3:
						currentNoteType = 3;//5
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_ARS:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
						currentNoteType = 0;//1000
						break;
					case 2:
					case 3:
						currentNoteType = 1;//500
						break;
					case 4:
					case 5:
						currentNoteType = 2; //200
						break;
					case 6:
					case 7:
						currentNoteType = 3;//100
						break;
					case 8:
					case 9:
						currentNoteType = 4;//50
						break;
					case 10:
					case 11:
						currentNoteType = 5;//20
						break;
					case 12:
					case 13:
						currentNoteType = 6;//10
						break;
					case 14:
					case 15:
						currentNoteType = 7;//5
						break;
					case 16:
					case 17:
						currentNoteType = 8;//2
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_THB:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
					case 10:
						currentNoteType = 0;//1000
						break;
					case 2:
					case 3:
					case 11:
						currentNoteType = 1;//500
						break;
					case 4:
					case 5:
					case 12:
						currentNoteType = 2; //100
						break;
					case 6:
					case 7:
					case 13:
						currentNoteType = 3;//50
						break;
					case 8:
					case 9:
					case 14:
						currentNoteType = 4;//20
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_TWD:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
						currentNoteType = 0;//2000
						break;
					case 2:
					case 3:
						currentNoteType = 1;//1000
						break;
					case 4:
					case 5:
						currentNoteType = 2; //500
						break;
					case 6:
					case 7:
						currentNoteType = 3;//200
						break;
					case 8:
					case 9:
						currentNoteType = 4;//100
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_CNY:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
					case 2:
						currentNoteType = 0;//100
						break;
					case 3:
					case 4:
					case 5:
						currentNoteType = 1;//50
						break;
					case 6:
					case 7:
					case 8:
						currentNoteType = 2; //20
						break;
					case 9:
					case 10:
					case 11:
						currentNoteType = 3;//10
						break;
					case 12:
					case 13:
					case 14:
						currentNoteType = 4;//5
						break;
					case 15:
					case 16:
					case 17:
						currentNoteType = 5;//1
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_BYR:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
						currentNoteType = 2;//100
						break;
					case 2:
					case 3:
						currentNoteType = 3;//50
						break;
					case 4:
					case 5:
						currentNoteType = 4; //20
						break;
					case 6:
					case 7:
						currentNoteType = 5;//10
						break;
					case 8:
					case 9:
						currentNoteType = 6;//5
						break;
                    case 10:
                        currentNoteType = 1;
                    break;
                    case 12:
                         currentNoteType = 0;
                    break;                      
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_UZS:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
						currentNoteType = 0;//100000
						break;
					case 2:
					case 3:
						currentNoteType = 1;//50000
						break;
					case 4:
					case 5:
						currentNoteType = 2; //10000
						break;
					case 6:
					case 7:
						currentNoteType = 3;//5000
						break;
					case 8:
					case 9:
						currentNoteType = 4;//1000
						break;
					case 10:
					case 11:
						currentNoteType = 5;//500
						break;
					case 12:
					case 13:
						currentNoteType = 6;//200
						break;
					case 14:
					case 15:
						currentNoteType = 7;//100
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}				
				}
				break;
				case INDEX_KZT:
				{
					switch(gb_billValue)
					{
                    case 14:
					case 15:
						currentNoteType = 0;//20000
						break;
					case 0:
					case 1:
						currentNoteType = 1;//10000
						break;
					case 2:
					case 3:
						currentNoteType = 2;//5000
						break;
					case 4:
					case 5:
                    case 16:
						currentNoteType = 3; //2000
						break;
					case 6:
					case 7:
						currentNoteType = 4;//1000
						break;
					case 8:
					case 9:
						currentNoteType = 5;//500
						break;
					case 10:
					case 11:
						currentNoteType = 6;//200
						break;
					case 12:
					case 13:
						currentNoteType = 7;//100
						break;

					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}	
				}					
				break;
				case INDEX_MAD:
				{
					switch(gb_billValue)
					{
					case 0:
					case 1:
					case 2:
						currentNoteType = 0;//200
						break;
					case 3:
					case 4:
					case 5:
						currentNoteType = 1;//100
						break;
					case 6:
					case 7:
					case 8:
						currentNoteType = 2; //50
						break;
					case 9:
					case 10:
					case 11:
						currentNoteType = 3;//20
						break;
					case 12:
					case 13:
					case 14:
						currentNoteType = 4;//10
						break;
					case 15:
					case 16:
					case 17:
						currentNoteType = 5;//5
						break;
					default:
						currentNoteType = 0xFF;
						g_errFlag |= ERR_VALUE;
						break;
					}		
				}
				break;
				default:
					break;
		}
	}
}
void DealNotePass(void)
{
	if(gb_oneNotePass == 1)
	{
		gb_oneNotePass = 0;
		//关传感器
		hwfs_On();
		uvfs_Off();
		redFs_Off();
		greenFs_Off();
		blueFs_Off();
		g_colorFsRGB = FS_OFF;
		mgDataLen = g_mgSampleIndex;
		if(systemState == NORMAL)
		{
			if(gb_inCollabration == COLLABRATION_COLOR)
			{
				color_whiteStandard();
			}
			else if(gb_inCollabration == COLLABRATION_UV)
			{
				uv_whiteStandard();
			}
			else if(gb_inCollabration > 1)
			{
				//测长校正计算函数
				length_collabrationCompute();
				lengthCollabrationProcess();			
			}
			else
			{
				//计算函数
				//billUVFvt = 0;
				delay_DelayMs(100);
				//billUV_Judge(g_currency,gb_uvTher[savedPara.uvGrade]);
				
				g_timetest[0] = timeCnt;
				billIrad_Judge(IRlengthBuffer,g_currency);//0909改U16注释
				g_timetest[1] = timeCnt;
				billRGB_Judge(g_currency);//0909改U16注释
				g_timetest[2] = timeCnt;
				billMG_Judge(g_currency);//0909改U16注释
				g_timetest[3] = timeCnt;

				billUV_Judge(g_currency,gb_uvTher[savedPara.uvGrade]);
				delay_DelayMs(100);

				DealNoteType();
				//真币
				if(g_errFlag == 0)
				{		
					IncNoteNum();
					LongBeep(1);
					DispNoteNumValSum();
				}
				else
				{
					//假币
					LongBeep(3);

					/*disp_DrawPic(BMP_YA_X, BMP_YA_Y, BMP_AYB);
					disp_DrawPic(BMP_YB_X, BMP_YB_Y, BMP_AYB);	
					disp_DrawPic(BMP_YC_X, BMP_YC_Y, BMP_AYB);
					disp_DrawPic(BMP_YD_X, BMP_YD_Y, BMP_AHE);
					disp_DrawPic(BMP_YE_X, BMP_YE_Y, BMP_AHG);
					disp_DrawPic(BMP_YF_X, BMP_YF_Y, BMP_AY1);*/
					if((g_errFlag == ERR_VALUE)||(g_errFlag == ERR_IR)||(g_errFlag == ERR_COLOR))
					{
						disp_DrawPic(80, 240-72, BMP_CGCIS);
					}
					else if(g_errFlag == ERR_MG)
					{
						disp_DrawPic(80, 240-72, BMP_CGMG);
					}			
					else if(g_errFlag == ERR_UV)
					{
						disp_DrawPic(80, 240-72, BMP_CGUV);
					}
					else
					{
						disp_DrawPic(80, 240-72, BMP_CGDEN);
					}					
					gb_errflagOverTime = 5000;
					if(gb_debugErrFlag == 1)
					{
						gb_testbuf[0] = colorJudgeValue;
						gb_testbuf[1] = billValue;
						gb_testbuf[2] = billIradMask;
						gb_testbuf[3] = mgFvtFlag;
						gb_testbuf[4] = colorDataLen;
						gb_testbuf[5] = billUVFvt;
						gb_testbuf[6] = 0x55;
						uart_SendDataToUart3(gb_testbuf,7);
						
					}
					//disp_setFont(DENO_NUM_STR_FONT); 
					//disp_setPenColor(RED);  	
					//disp_setBackColor(MID_BAR_COLOR);
					//disp_string(" SUSP",DENO_NUM_X,DENO_NUM_Y);		
				}

				
				if(gb_autoOutputDetailData == 1||gb_needOutPutErrData == 2)
				{
//					OutputLengthDetailData();
					OutputALLDetailData2();
				}
				else if(gb_needOutPutErrData == 1)
				{
					if(g_errFlag > 0)
					{
						OutputALLDetailData2();
					}
				}
			}
			//计算结束
			noteState &= (~STATE_COMPUTE);
#ifdef DEBUG_MODE			
			testflag[4] = 1;
			testflag2[4] = testflag2Cnt++;
#endif			
			//根据计算结果来决定钱去前面还是回转  
			if(savedPara.noteLeaveRoads == 0)
			{
				noteState |= STATE_FORWARD_NOTE_LEAVE;
				motor1_ForwardRun();//向前转
				motor1SataRecord2 = 2; 
				g_maxMpFromPs2ToLeave = MP_FROM_PS2_TO_LEAVE;
				gb_noteState = NOTE_IDEL;
			}
			else if(savedPara.noteLeaveRoads == 1)
			{
				noteState |= STATE_BACKWARD_NOTE_LEAVE;
				gb_haveNoteInPS3 = 0;
				PS3FlagCnt = 0;
				motor1SataRecord = 1;
				motor1_BackwardRun();//向后转
				gb_noteState = NOTE_BACKWARD;

				g_maxMpFromComputeToPS1 = MP_FROM_COMPUTE_TO_PS1;			
			}
			else
			{
				if(g_errFlag > 0)//假币向后走，真币向前走
				{
					noteState |= STATE_BACKWARD_NOTE_LEAVE;
					gb_haveNoteInPS3 = 0;
					PS3FlagCnt = 0;
					motor1SataRecord = 1;
					motor1_BackwardRun();//向后转
					gb_noteState = NOTE_BACKWARD;

					g_maxMpFromComputeToPS1 = MP_FROM_COMPUTE_TO_PS1;			
				}
				else
				{
					noteState |= STATE_FORWARD_NOTE_LEAVE;
					motor1_ForwardRun();//向前转
					motor1SataRecord2 = 2; 
					g_maxMpFromPs2ToLeave = MP_FROM_PS2_TO_LEAVE;
					gb_noteState = NOTE_IDEL;
				}
			}
		}
	}
}

void DispString(u8 *str,u8 enter)
{
	u16 len;
	u8 buf[8];
	
	if(gb_uartWorkMode != DEBUG_MODE)
	{
		return;
	}
	len = strlen(str);	
	uart_SendDataToUart3(str,len);
	if(enter > 0)
	{
		buf[0] = 0x0d;
		buf[1] = 0x0a;
		uart_SendDataToUart3(buf,2);
	}
}

//输出到串口
void DispSensorViewMenu(void)
{
	u8 i,j;
	u8 u8Temp;

	i = 0;
	memcpy(dispStr+i,"测长:",5);
	i += 5;
	for(j = 0;j < LENGTH_IR_CHANNEL_NUM;j++)
	{
		u8Temp = irValue[j];
		U8ToHexstr(u8Temp,dispStr+i);
		i += 2;		
		dispStr[i++] = ' ';
	}
	dispStr[i++] = '\0';
	DispString(dispStr,1);
	
	i = 0;
	memcpy(dispStr+i,"磁性1:",6);
	i += 6;
	u8Temp = mrValue[0];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);	
	
	i = 0;
	memcpy(dispStr+i,"磁性2:",6);
	i += 6;
	u8Temp = mrValue[1];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);	
	
	i = 0;
	memcpy(dispStr+i,"颜色1: ",6);
	i += 6;
	u8Temp = colorRGB[0][0];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	u8Temp = colorRGB[0][1];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	u8Temp = colorRGB[0][2];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);	
	
	i = 0;
	memcpy(dispStr+i,"颜色2: ",6);
	i += 6;
	u8Temp = colorRGB[1][0];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	u8Temp = colorRGB[1][1];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	u8Temp = colorRGB[1][2];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);	
	
	i = 0;
	memcpy(dispStr+i,"颜色3: ",6);
	i += 6;
	u8Temp = colorRGB[2][0];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	u8Temp = colorRGB[2][1];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	u8Temp = colorRGB[2][2];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);	
	
	i = 0;
	memcpy(dispStr+i,"颜色4: ",6);
	i += 6;
	u8Temp = colorRGB[3][0];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	u8Temp = colorRGB[3][1];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	u8Temp = colorRGB[3][2];
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,1);	
	
	i = 0;
	memcpy(dispStr+i,"红外发射 :",10);
	i += 10;
	u8Temp = gb_hwVccIsOn;
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);
	
	//码盘
	i = 0;
	memcpy(dispStr+i,"码盘:",5);
	i += 5;
	u8Temp = mpCnt;
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);
	
	//进钞
	i = 0;
	memcpy(dispStr+i,"进钞:",5);
	i += 5;
	u8Temp = enteranceSensorVal;
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,1);
	//UV
	i = 0;
	memcpy(dispStr+i,"UV:",3);
	i += 3;
	u8Temp = UvValue;
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,1);
	
//	//PS1 PS2
	i = 0;
	memcpy(dispStr+i,"PS:",3);
	i += 3;
	U8ToStr(tdjsValue[0],dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);
	
	i = 0;
	U8ToStr(tdjsValue[1],dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,1);
	
	i = 0;
	memcpy(dispStr+i,"KEY:",4);
	i += 4;
	u8Temp = readkey0();
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);
	
	i = 0;
	u8Temp = readkey1();
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);
	
	i = 0;
	u8Temp = readkey2();
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,1);
	
	DispString("************************************************************************************",1);	
}

//预置停机
void BatchMotorStop(void)
{
	DispNoteNumValSum();
	LongBeep(1);
	//显示预置停机
// 	gb_led2FlashOn = 1;
// 	led2FlashStopTimes = 10;
// 	led2FlashCnt = 0;
// 	memcpy(led2FlashStr," BAT",4);
	
	motor1_Break();
	SetSystemState(BATCH_STOP);
}

//假币停机
void JudgeMotorStop(void)
{
	//DispNoteNumValSum();
	LongBeep(1);
	//显示假币停机
// 	gb_led2FlashOn = 1;
// 	led2FlashStopTimes = -1;
// 	led2FlashCnt = 0;
// 	dispStr[0] = ' ';
// 	dispStr[1] = 'E';
// 	U8ToStrNoSpace(errorCode,dispStr+2);
// 	memcpy(led2FlashStr,dispStr,4);
	
	motor1_Break();
	SetSystemState(SUSP_STOP);
}

void IncNoteNum(void)
{
	noteNum ++;
	if(noteNum > 999)
	{
		noteNum = 0;
	}		
	switch(g_currency)
	{
		case INDEX_USD:
			noteDenoValue = USD_NOTE_VALUE[currentNoteType];
			break;
		case INDEX_EUR:
			noteDenoValue = EUR_NOTE_VALUE[currentNoteType];
			break;
		case INDEX_RUB:
			noteDenoValue = RUB_NOTE_VALUE[currentNoteType];
			break;		
		case INDEX_TRY:
			noteDenoValue = TRY_NOTE_VALUE[currentNoteType];
			break;	
		case INDEX_IQD:
			noteDenoValue = IQD_NOTE_VALUE[currentNoteType];
			break;			
		case INDEX_SAR:
			noteDenoValue = SAR_NOTE_VALUE[currentNoteType];
			break;		
		case INDEX_AED:
			noteDenoValue = AED_NOTE_VALUE[currentNoteType];
			break;	
		case INDEX_GBP:
			noteDenoValue = GBP_NOTE_VALUE[currentNoteType];
			break;
		case INDEX_ARS:
			noteDenoValue = ARS_NOTE_VALUE[currentNoteType];
			break;		
		case INDEX_THB:
			noteDenoValue = THB_NOTE_VALUE[currentNoteType];
			break;		
		case INDEX_TWD:
			noteDenoValue = TWD_NOTE_VALUE[currentNoteType];
			break;
		case INDEX_CNY:
			noteDenoValue = CNY_NOTE_VALUE[currentNoteType];
			break;
		case INDEX_BYR:
			noteDenoValue = BYR_NOTE_VALUE[currentNoteType];
			break;		
		case INDEX_UZS:
			noteDenoValue = UZS_NOTE_VALUE[currentNoteType];
			break;	
		case INDEX_KZT:
			noteDenoValue = KZT_NOTE_VALUE[currentNoteType];
			break;	
		case INDEX_MAD:
			noteDenoValue = MAD_NOTE_VALUE[currentNoteType];
			break;			
		default:
			noteDenoValue = USD_NOTE_VALUE[currentNoteType];
			break;
		
	}


	noteSum += noteDenoValue;
	if(noteSum > 9999999)
	{
		noteSum = 0;
	}
	denoNoteNum[currentNoteType] ++;
	if(denoNoteNum[currentNoteType] > 999)
	{
		denoNoteNum[currentNoteType] = 0;
	}
}

void ClearAllNoteNum(void)
{
	noteNum = 0;
	noteDenoValue = 0;
	noteSum = 0;
	memset(denoNoteNum,0,24);
}

void DispNoteNumValSum(void)
{
	if(systemState == NORMAL && g_subStateOfNormal == NORMAL_DIAN_CHAO)
	{
		DispNoteNum();//显示张数
		DispNoteSum();//显示金额
		//DispUpNoteNum();
		//DispNoteDenoValue();//显示币值
		DispDetailNoteNum();//显示明细
	}
}


void DispNoteNum(void)//显示张数
{
//	disp_setFont(NOTENUM_FONT);
//	disp_setPenColor(BLACK);
// 	disp_setBackColor(MID_BAR_COLOR);
//	U32ToStr(noteNum,dispStr,DOWN_NOTE_NUM_BITS);
//	disp_string(dispStr,NOTENUM_X,NOTENUM_Y);
	u32 d;
	u8 i;
	u8 result;
	d = noteNum;
	if(noteNum == 0)
	{
		disp_DrawPic(BMP_JC_X-48*2,BMP_JC_Y,JbmpAddress[10]);
		disp_DrawPic(BMP_JC_X-48,BMP_JC_Y,JbmpAddress[10]);
		disp_DrawPic(BMP_JC_X,BMP_JC_Y,JbmpAddress[0]);
	}	
	else
	{
		if(d > 999)
		{
			d = 999;
		}
		i = 0;
		while(d > 0)
		{
			result = d%10;
			disp_DrawPic(BMP_JC_X-48*i, BMP_JC_Y, JbmpAddress[result]);
			i++;
			d /= 10;
		}
	}
}

void DispNoteSum(void)//显示金额
{
//	disp_setFont(NOTESUM_FONT);
//	disp_setPenColor(BLACK);
// 	disp_setBackColor(MID_BAR_COLOR);
//	U32ToStr(noteSum,dispStr,DOWN_NOTE_SUM_BITS);
//	disp_string(dispStr,NOTESUM_X,NOTESUM_Y);
	u32 d;
	u8 i;
	u8 result;
	if(g_needAddValue == WORK_ADD)
	{
		d = noteSum;
	}
	else
	{
		d = noteDenoValue;
	}
	for(i=0; i<7; i++)
	{
		if(d > 0)
		{
			result = d%10;
			disp_DrawPic(BMP_YG_X-32*i, BMP_YG_Y, YbmpAddress[result]);
			d /= 10;
		}
		else
		{
			if(i == 0)
			{
				disp_DrawPic(BMP_YG_X-32*i, BMP_YG_Y, YbmpAddress[0]);
			}
			else
			{
				disp_DrawPic(BMP_YG_X-32*i, BMP_YG_Y, YbmpAddress[10]);
			}
		}
	}
}

/*void DispNoteDenoValue(void)//显示币值
{
	disp_setFont(DENO_NUM_STR_FONT); 
	disp_setPenColor(BLACK);  	
	disp_setBackColor(MID_BAR_COLOR);
	U16ToStr(noteDenoValue,dispStr,5);
	if(g_currency == INDEX_USD)
	{
		dispStr[0] = '$';
		disp_string(dispStr,DENO_NUM_X,DENO_NUM_Y);
	}
	else
	{
		dispStr[0] = ' ';
		disp_string(dispStr,DENO_NUM_X,DENO_NUM_Y);
	}
}*/
void DispDetailNoteNum(void)//显示明细
{
	u8 i,j;
	u32 d;
	u8 result;
	u8 noteMaxNum;
	u8 noteCnt1,note1PositionOffset,note2PositionOffset;
	u8 noteCnt2;
	
	//disp_setFont(DETAIL_NOTE_CHART_FONT);
	//disp_setPenColor(BLACK);
	//disp_setBackColor(MID_BAR_COLOR);
	j=0;
	switch(g_currency)
	{
		case INDEX_GBP:
			noteMaxNum = 4;
		break;
		case INDEX_IQD:
		case INDEX_THB:
		case INDEX_TWD:
				noteMaxNum = 5;
		break;		
		case INDEX_TRY:
		case INDEX_CNY:
		case INDEX_MAD:
            noteMaxNum = 6;
		break;				
		case INDEX_EUR:
		case INDEX_USD:
		case INDEX_SAR:
		case INDEX_BYR:
        case INDEX_KZT:
			noteMaxNum = 7;
		break;			
		case INDEX_RUB:
		case INDEX_AED:
			noteMaxNum = 8;
		break;	
		case INDEX_ARS:
		case INDEX_UZS:
			noteMaxNum = 9;
		break;		
		default:
			noteMaxNum = 0;
		break;
	}
	/***********************************************************************
	明细排列             总共面额数/2  有余数放后一列
	××0   ××5        
	××1   ××6
	××2   ××7
	××3   ××8
	××4   ××9
	***********************************************************************/
	if(noteMaxNum > 0)
	{
		noteCnt1 = noteMaxNum/2;
		noteCnt2 = noteMaxNum%2;
        if(g_currency == INDEX_KZT)
        {
            noteCnt1++;
        }
		note1PositionOffset = 5-noteCnt1;
        if(g_currency == INDEX_KZT)
        {
            note2PositionOffset = note1PositionOffset+(5-(noteCnt1-noteCnt2));
        }
        else
        {
            note2PositionOffset = note1PositionOffset+(5-(noteCnt1+noteCnt2));
        }
		for(i = 0;i < noteMaxNum;i++)
		{
			d = denoNoteNum[i];
			if(d == 0)
			{	
				if(i<noteCnt1)
				{
					disp_DrawPic(SBmpDispXY[(i+note1PositionOffset)*2]-24,SBmpDispXY[(i+note1PositionOffset)*2+1],SbmpAddress[10]);
					disp_DrawPic(SBmpDispXY[(i+note1PositionOffset)*2]-12,SBmpDispXY[(i+note1PositionOffset)*2+1],SbmpAddress[10]);
					disp_DrawPic(SBmpDispXY[(i+note1PositionOffset)*2],SBmpDispXY[(i+note1PositionOffset)*2+1],SbmpAddress[0]);
				}
				else
				{
					disp_DrawPic(SBmpDispXY[(i+note2PositionOffset)*2]-24,SBmpDispXY[(i+note2PositionOffset)*2+1],SbmpAddress[10]);
					disp_DrawPic(SBmpDispXY[(i+note2PositionOffset)*2]-12,SBmpDispXY[(i+note2PositionOffset)*2+1],SbmpAddress[10]);
					disp_DrawPic(SBmpDispXY[(i+note2PositionOffset)*2],SBmpDispXY[(i+note2PositionOffset)*2+1],SbmpAddress[0]);					
				}
			}	
			else
			{
				if(i < noteCnt1)
				{
					for(j=0; j<3; j++)
					{
						if(d > 0)
						{
							result = d%10;
							disp_DrawPic(SBmpDispXY[(i+note1PositionOffset)*2]-12*j, SBmpDispXY[(i+note1PositionOffset)*2+1], SbmpAddress[result]);
							d /= 10;
						}
						else
						{
							disp_DrawPic(SBmpDispXY[(i+note1PositionOffset)*2]-12*j,SBmpDispXY[(i+note1PositionOffset)*2+1], SbmpAddress[10]);
						}
					}
				}
				else
				{
					for(j=0; j<3; j++)
					{
						if(d > 0)
						{
							result = d%10;
							disp_DrawPic(SBmpDispXY[(i+note2PositionOffset)*2]-12*j, SBmpDispXY[(i+note2PositionOffset)*2+1], SbmpAddress[result]);
							d /= 10;
						}
						else
						{
							disp_DrawPic(SBmpDispXY[(i+note2PositionOffset)*2]-12*j,SBmpDispXY[(i+note2PositionOffset)*2+1],SbmpAddress[10]);
						}
					}
				}	
			}
		}
	}

//	if((g_currency == INDEX_THB)||(g_currency == INDEX_TWD))//5
//	{
//		for(i = 0;i < 5;i++)
//		{
//			d = denoNoteNum[i];
//			if(d == 0)
//			{	
//				disp_DrawPic(SBmpDispXY[(i+5)*2]-24,SBmpDispXY[(i+5)*2+1],SbmpAddress[10]);
//				disp_DrawPic(SBmpDispXY[(i+5)*2]-12,SBmpDispXY[(i+5)*2+1],SbmpAddress[10]);
//				disp_DrawPic(SBmpDispXY[(i+5)*2],SBmpDispXY[(i+5)*2+1],SbmpAddress[0]);
//			}	
//			else
//			{
//				for(j=0; j<3; j++)
//				{
//					if(d > 0)
//					{
//						result = d%10;
//						disp_DrawPic(SBmpDispXY[(i+5)*2]-12*j, SBmpDispXY[(i+5)*2+1], SbmpAddress[result]);
//						d /= 10;
//					}
//					else
//					{
//						disp_DrawPic(SBmpDispXY[(i+5)*2]-12*j,SBmpDispXY[(i+5)*2+1],SbmpAddress[10]);
//					}
//				}
//			}
//		}
//	}
	
}
		

void LongBeep(u8 times)
{
	if(savedPara.beepSwitch == 1)
	{
		beepTimes = times;	//蜂鸣器该响的次数
		beepType = LONG_BEEP_LENGTH;
	}
}

void adjustMotorSpeed(void)
{
	InitMotorMuBiaoSpeed();
	
	//校正800 显示
	motor1_Stop();
	motor1_SetSpeed(SPEED_800);
// 	tm16xx_Led2Disp(SPEED_800);	
	motor1_ForwardRun();
	delay_DelayMs(3000);
	//保存
	savedPara.adjustPara.csddjInitVal[currentSpeed][0] = forwardPwmValue;
	motor1_Stop();
	motor1_BackwardRun();
	delay_DelayMs(3000);	
	savedPara.adjustPara.csddjInitVal[currentSpeed][1] = backwardPwmValue;
	
	motor1_Stop();
	motor1_SetSpeed(SPEED_900);
// 	tm16xx_Led2Disp(SPEED_900);	
	motor1_ForwardRun();
	delay_DelayMs(3000);
	//保存
	savedPara.adjustPara.csddjInitVal[currentSpeed][0] = forwardPwmValue;
	motor1_Stop();
	motor1_BackwardRun();
	delay_DelayMs(3000);	
	savedPara.adjustPara.csddjInitVal[currentSpeed][1] = backwardPwmValue;
	
	motor1_Stop();
	motor1_SetSpeed(SPEED_1000);
// 	tm16xx_Led2Disp(SPEED_1000);	
	motor1_ForwardRun();
	delay_DelayMs(3000);
	//保存
	savedPara.adjustPara.csddjInitVal[currentSpeed][0] = forwardPwmValue;
	motor1_Stop();
	motor1_BackwardRun();
	delay_DelayMs(3000);	
	savedPara.adjustPara.csddjInitVal[currentSpeed][1] = backwardPwmValue;
	
	motor1_Stop();
	
	eeprom_SaveData();
	
	motor1_SetSpeed(savedPara.userWorkPara.d[INDEX_SPEED]);
// 	tm16xx_Led2Disp(savedPara.userWorkPara.d[INDEX_SPEED]);	
}

void dispSelfcheckError(u8 code)
{
	u8 i;
	disp_setFont(FONT_24);
	disp_setBackColor(BLACK);
	disp_setPenColor(RED);
	disp_clearScreen(BLACK);
//	U8ToStr(code,dispStr);
//	disp_string(dispStr,200,0);
	
	dispStr[0] = ' ';
	dispStr[1] = 'E';
	dispStr[2] = '0';
	i=0;
	if((code&ERROR_ENIR) == ERROR_ENIR)
	{
		dispStr[3] = '1';
		dispStr[4] = '\0';
		disp_string(dispStr,0,0);
		i++;
	}
	if((code&ERROR_PSIR) == ERROR_PSIR)
	{
		dispStr[3] = '2';
		dispStr[4] = '\0';
		disp_string(dispStr,0,0+i*24);
		i++;		
	}
	if((code&ERROR_MP) == ERROR_MP)
	{
		dispStr[3] = '3';
		dispStr[4] = '\0';
		disp_string(dispStr,0,0+i*24);
		i++;		
	}	
	if((code&ERROR_RGB1) == ERROR_RGB1)
	{
		dispStr[3] = '4';
		dispStr[4] = '\0';
		disp_string(dispStr,0,0+i*24);
		i++;		
	}	
	if((code&ERROR_RGB2) == ERROR_RGB2)
	{
		dispStr[3] = '5';
		dispStr[4] = '\0';
		disp_string(dispStr,0,0+i*24);
		i++;		
	}
	if((code&ERROR_RGB3) == ERROR_RGB3)
	{
		dispStr[3] = '6';
		dispStr[4] = '\0';
		disp_string(dispStr,0,0+i*24);
		i++;		
	}
	if((code&ERROR_RGB4) == ERROR_RGB4)
	{
		dispStr[3] = '7';
		dispStr[4] = '\0';
		disp_string(dispStr,0,0+i*24);
		i++;		
	}
	if((code&ERROR_IR) == ERROR_IR)
	{
		dispStr[3] = '8';
		dispStr[4] = '\0';
		disp_string(dispStr,0,0+i*24);
		i++;		
	}
}
void SystemSelfcheck(void)
{
	u32 mpcnt1,mpcnt2;
	u8 i,j;
	
	gb_enableSample = 0;
	gb_selfcheckErrorState = 0;
	
	jckfs_On();
	hwfs_On();
 	delay_DelayMs(100);
 	SampleOneRow();
	if(enteranceSensorVal > 50)
	{
		gb_selfcheckErrorState |= ERROR_ENIR;
	}
	if(tdjsValue[0]<200||tdjsValue[1]<200)
	{
		gb_selfcheckErrorState |= ERROR_PSIR;
	}
	for(i=0;i<20;i++)
	{
		if(irValue[i]<200)
		{
			gb_selfcheckErrorState |= ERROR_IR;
		}
	}
	redFs_On();
	greenFs_Off();
	blueFs_Off();
	delay_DelayMs(100);
 	SampleOneRow();
	for(i=0;i<4;i++)
	{
		if(colorRGB[i][0]<200)
		{
			gb_selfcheckErrorState |= (ERROR_RGB1<<i);
		}
	}
	redFs_Off();
	greenFs_On();
	blueFs_Off();
	delay_DelayMs(100);
 	SampleOneRow();
	for(i=0;i<4;i++)
	{
		if(colorRGB[i][1]<200)
		{
			gb_selfcheckErrorState |= (ERROR_RGB1<<i);
		}
	}
	redFs_Off();
	greenFs_Off();
	blueFs_On();
	delay_DelayMs(100);
 	SampleOneRow();
	for(i=0;i<4;i++)
	{
		if(colorRGB[i][2]<200)
		{
			gb_selfcheckErrorState |= (ERROR_RGB1<<i);
		}
	}
	jckfs_Off();
	hwfs_Off();
	redFs_Off();
	greenFs_Off();
	blueFs_Off();
	g_colorFsRGB = FS_RED;
	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			colorRGB[i][j] = 0;
		}
	}
	delay_DelayMs(100);
 	SampleOneRow();
	if(enteranceSensorVal < 200)
	{
		gb_selfcheckErrorState |= ERROR_ENIR;
	}
	if(tdjsValue[0]>50||tdjsValue[1]>50)
	{
		gb_selfcheckErrorState |= ERROR_PSIR;
	}
	for(i=0;i<20;i++)
	{
		if(irValue[i]>50)
		{
			gb_selfcheckErrorState |= ERROR_IR;
		}
	}
	for(i=0;i<4;i++)
	{
		if(colorRGB[i][0]>50)
		{
			gb_selfcheckErrorState |= (ERROR_RGB1<<i);
		}
	}
 	hwfs_On();
	mpCnt = 0;
 	motor1_ForwardRun();
 	delay_DelayMs(100);
 	g_mgSampleIndex = 0;
 	g_lengthSampleIndex = 0;
 	//needSampleIdleNum = 500;
 	delay_DelayMs(1000);
	//motor1_BackwardRun();
	//delay_DelayMs(1000);
	motor1_Stop();
	mpcnt1 = mpCnt;
	if(mpcnt1<20)
	{
		gb_selfcheckErrorState |= ERROR_MP;
	}
// 	hwfs_Off();
 	if(gb_isJammed == JAM_CSDDJ)
 	{
 		//dispSelfcheckError(ERROR_MOTOR_OR_MP);//码盘 电机
 		gb_isJammed = 0;
 	}
}

// void InitIrData(void)
// {
// 	ir2.sum = 0;
// 	ir2.num = 0;
// 	ir2.max = 0;
// 	ir2.min = 0xff;
// 	ir2.avg = 0;
// 	ir2.scope = 0;
// 	ir3.sum = 0;
// 	ir3.num = 0;
// 	ir3.max = 0;
// 	ir3.min = 0xff;
// 	ir3.avg = 0;
// 	ir3.scope = 0;
// }

// void SaveIr2Data(void)
// {
// 	if(ir2.num != 0)
// 	{
// 		ir2.avg = ir2.sum/ir2.num;
// 	}
// 	if(ir2.max > ir2.min)
// 	{
// 		ir2.scope = ir2.max - ir2.min;
// 	}
// 	ir2Saved = ir2;
// }
// void SaveIr3Data(void)
// {
// 	if(ir3.num != 0)
// 	{
// 		ir3.avg = ir3.sum/ir3.num;
// 	}
// 	if(ir3.max > ir3.min)
// 	{
// 		ir3.scope = ir3.max - ir3.min;
// 	}
// 	ir3Saved = ir3;
// }
// void DealIr2Data(u8 d)
// {
// 	ir2.sum += d;
// 	ir2.num ++;
// 	if(ir2.max < d)
// 	{
// 		ir2.max = d;
// 	}
// 	if(ir2.min > d)
// 	{
// 		ir2.min = d;
// 	}	
// }
// void DealIr3Data(u8 d)
// {
// 	ir3.sum += d;
// 	ir3.num ++;
// 	if(ir3.max < d)
// 	{
// 		ir3.max = d;
// 	}
// 	if(ir3.min > d)
// 	{
// 		ir3.min = d;
// 	}		
// }

void UpdateDataFromSavedData(void)
{

}
void U8ToStrNoSpace(u8 d, u8 * str)
{

	if(d >= 100)
	{
		str[3] = '\0';
		str[2] = d%10+'0';
		d /= 10;
		str[1] = d%10+'0';
		d /= 10;
		str[0] = d%10+'0';
	}
	else if(d >= 10)
	{
		str[2] = '\0';
		str[1] = d%10+'0';
		d /= 10;
		str[0] = d%10+'0';
	}
	else
	{
		str[1] = '\0';
		str[0] = d%10+'0';
	}

}


void U16ToTimeStr(u16 d, u8 * str, u8 len)
{
	u8 i;

	str[len-1] = '0';
	str[len] = '\0';
	i = len;
	while(d > 0)
	{
		str[i-1] = (d%10) + '0';	
		i --;
		if (i == 0)
		{
			break;
		}
		d /= 10;
	}

	if (i == len)
	{
		i --;
	}

	while (i > 0)
	{
		str[i-1] = '0';
		i--;
	}
}

void U32ToStr(u32 d, u8 * str, u8 len)
{
	u8 i;

	str[len-1] = '0';
	str[len] = '\0';
	i = len;
	while(d > 0)
	{
		str[i-1] = (d%10) + '0';	
		i --;
		if (i == 0)
		{
			break;
		}
		d /= 10;
	}

	if (i == len)
	{
		i --;
	}

	while (i > 0)
	{
		str[i-1] = ' ';
		i--;
	}
}


void U16ToStr04(u16 d1, u8 *pStr)
{
	u16 d;
	d = d1;
	if (d<10)
	{
		pStr[0] = '0';
		pStr[1] = '0';
		pStr[2] = '0';
		pStr[3] = d+'0';
	}
	else if (d<100)
	{
		pStr[0] = '0';
		pStr[1] = '0';
		pStr[2] = d/10+'0';
		pStr[3] = d%10+'0';
	}
	else if (d<1000)
	{
		pStr[0] = '0';
		pStr[1] = d/100+'0';
		d %= 100;
		pStr[2] = d/10+'0';
		pStr[3] = d%10+'0';
	}
	else
	{
		pStr[0] = d/1000+'0';
		d %= 1000;
		pStr[1] = d/100+'0';
		d %= 100;
		pStr[2] = d/10+'0';
		pStr[3] = d%10+'0';
	}

	pStr[4] = '\0';
}

void U16ToStr(u16 d, u8 * str, u8 len)
{
	u8 i;

	str[len-1] = '0';
	str[len] = '\0';
	i = len;
	while(d > 0)
	{
		str[i-1] = (d%10) + '0';	
		i --;
		if (i == 0)
		{
			break;
		}
		d /= 10;
	}

	if (i == len)
	{
		i --;
	}

	while (i > 0)
	{
		str[i-1] = ' ';
		i--;
	}
}

//U8变成16进制字符串
u8 const HEX_CODE[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
void U8ToHexstr(u8 d, u8 * str)
{
	str[0] = HEX_CODE[d/16];
	str[1] = HEX_CODE[d%16];
	str[2] = '\0';
}

void U8ToStr(u8 d, u8 * str)
{
	U16ToStr((u16)d, str, 3);
}

//新函数
void SetSystemState(u8 d)
{
	systemState = d;
}
void initEteranceSensor(void)
{
	entergatePulseNumCounter = 0;
	fiveMsCnt = 0;
	scanEntergateTimer = 0;
	gb_needScanEteranceSensor = 1;
}
void DealJamAtOnce(void)
{
	if(systemState != SELFCHECK)//自检中堵币不显示 由自检统一显示
	{
		//显示 JAM 及刹车原因
		memcpy(dispStr," E",2);
		U16ToStr(gb_isJammed+ERROR_JAM1-1,dispStr+2,2);
// 		tm16xx_Led2DispStr(dispStr);
		initEteranceSensor();
		SetSystemState(DU_BI);
		ClearPSIrFlag();
		ClearJamFlag();
	}
	hwfs_On();
	redFs_Off();
	greenFs_Off();
	blueFs_Off();
	g_colorFsRGB = FS_OFF;
	uvfs_Off();
	motor1_Stop();
	motor1StopRecord = 4;
	if(gb_isJammed != JAM_ENTERANCE_TO_LENGTH)
	{
		LongBeep(3);
		gb_dispJamInfo = 1;
	}
	//gb_needRecordIr = 0;
	//irSampleDelayNum = 20;
}

void InitAllPara(void)
{
	InitAdjustPara();
	InitMachineWorkPara();
	InitUserWorkPara();
}

void InitAdjustPara()
{
	InitMotorSpeedData();
	savedPara.adjustPara.widthAdjust = WIDTH_JZ_BASE;
// 	savedPara.adjustPara.irAdjust[1] = 57;
// 	savedPara.adjustPara.irAdjust[2] = 57;
	memset(savedPara.adjustPara.irBz40gStandard,0,REAL_IR_NUM*2);
	memset(savedPara.adjustPara.irBz80gStandard,0,REAL_IR_NUM*2);
	memset(savedPara.adjustPara.irIdleStandard,0xff,REAL_IR_NUM);
	savedPara.uvGrade = 5;
	savedPara.uvWhiteValue = 180;
}


void InitMachineWorkPara(void)
{
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH1] = 0x06;
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH2] = 0;
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH3] = 0;
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH4] = 0;
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH5] = 0;
	
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH6] = 0;
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH7] = 0;
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH8] = 0;
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH9] = 0;
	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH10] = 0;
	savedPara.machineWorkPara.d[DEFAULT_CURRENCY] = INDEX_USD;
	savedPara.identificationWays = ALL_WAYS;
}

void InitUserWorkPara()
{
	savedPara.userWorkPara.d[INDEX_DOWN_STACKER_CAPACITY] = 200;
	savedPara.userWorkPara.d[INDEX_SPEED] = SPEED_800;
	savedPara.userWorkPara.d[INDEX_ADD_IS_ON] = 0;
	savedPara.userWorkPara.d[INDEX_WORKMODE] = WORKMODE_1;
	savedPara.userWorkPara.d[INDEX_MANUAL_IS_ON] = 0;
	savedPara.userWorkPara.d[INDEX_BEEP_ON] = 1;
	savedPara.userWorkPara.d[INDEX_BATCH] = 0;
	savedPara.userWorkPara.d[INDEX_SELFCHECK] = 1;
	
	savedPara.userWorkPara.d[INDEX_MONEY_TYPE] = INDEX_RMB;
	savedPara.userWorkPara.d[INDEX_4thRMB_SUPPORT] = 0;
	
	savedPara.userWorkPara.d[INDEX_YU_ZHI_STOP_CLEAR_RESULT] = 0;
	savedPara.userWorkPara.d[INDEX_RMB_MG_GRADE] = 1;
	savedPara.userWorkPara.d[INDEX_RMB_UV_GRADE] = 1;
	savedPara.userWorkPara.d[INDEX_RMB_DOUBLE_NOTE_THRES] = 50;
	savedPara.userWorkPara.d[INDEX_RMB_CHAIN_NOTE_THRES] = 100;
	savedPara.beepSwitch = 1;
	savedPara.noteLeaveRoads = 1;
}

void InitMotorSpeedData(void)
{
	u8 i;
	for (i=0; i < SPEED_NUM; i++)
	{
		savedPara.adjustPara.csddjInitVal[i][0] = CHUANGSHU_MOTOR_PWM_PARA[i];	
		savedPara.adjustPara.csddjInitVal[i][1] = CHUANGSHU_MOTOR_PWM_PARA[i];	
	}
	InitMotorMuBiaoSpeed();
}

void InitMotorMuBiaoSpeed(void)
{
	u8 i;
	for(i=0; i< SPEED_NUM; i++)
	{
		savedPara.adjustPara.csmpNumIn50ms[i] = CSMP_NUM_IN_50MS[i];
	}
}

#define WIDTH_BETWEEN_IR2_IR3 76
u16 WIDTH_BETWEEN_IR2_IR3_EXP2 = (WIDTH_BETWEEN_IR2_IR3*WIDTH_BETWEEN_IR2_IR3);
//(g*m)/sqrt(s^2 + g^2)
//m:测量到的宽度，g：ir2和ir3的间距，s斜率
u16 ComputeWidth(u16 m, u8 s)
{
//	u8 g;
	u32 sum;

	sum = WIDTH_BETWEEN_IR2_IR3;
 	sum *= m;

	sum /= Sqrt(s);

	return((u16)sum);
}

//计算(X^2 + Y^2)开根号的值,y确定为IR2、IR3间的间距
#define MIN_DIFF 20
u16 Sqrt(u8 x)
{
	u32 sum;
//	u16 diffL,diffM;
	u16 r;
	u16 rr;
	u16 start,end;

	if (x < 10)
	{
		return (WIDTH_BETWEEN_IR2_IR3);
	}
	
	//g = WIDTH_BETWEEN_IR2_IR3;

	sum = WIDTH_BETWEEN_IR2_IR3_EXP2 + x*x;

	start = WIDTH_BETWEEN_IR2_IR3;
	end = WIDTH_BETWEEN_IR2_IR3 + x;

	while (1)
	{
		r = ((u16)(end + start))/2;
		if (r > 255)
		{
			r = 255;
			end = 255;
			r = (end + start)/2;
		}
		rr = r * r;

		//如果结果和sum几乎相等，就退出；
		if ((rr >= (sum - MIN_DIFF)) && (rr <= (sum + MIN_DIFF)))
		{
			return (r);
		}
		else	
		{
			//如果start和end只差一个数，就退出；
			if (end <= (start + 3))
			{
				return ((u16)(((u16)(end + start)) / 2));
			}
			else
			{
				if (rr < sum)
				{
					start = r;
				}
				else
				{
					end = r;
					
				}
			}
		}
		
	}
}
// void OutputCoinDetailData(void)
// {
// 	u16 i;
// 	u8 buffer[10];
// 	u16 maxLen;
// 	
// 	memset(buffer,0,sizeof(buffer));
// 	buffer[0] = 0xc6;
// 	buffer[1] = 4;
// 	buffer[6] = 0x55;

// 	{
// 		for(i = 0;i < dataLen;i++)
// 		{
// 			buffer[2] = data[0][i];
// 			buffer[3] = data[1][i];
// 			buffer[4] = data[2][i];
// 			buffer[5] = data[3][i];

// 			uart_SendDataToUart1(buffer,7);
// 			while(uart1outfifo_count> 0)
// 			{
// 				
// 			}
// 		}	
// 	}
// 	for (i=0; i<6; i++)
// 	{
// 		buffer[2] = 0xff;
// 		buffer[3] = 0xff;
// 		buffer[4] = 0xff;
// 		buffer[5] = 0xff;
// 		uart_SendDataToUart1(buffer,7);

// 		//等待串口发送完毕
// 		while(uart1outfifo_count> 0)
// 		{
// 		}
// 	}
// }

void GetOpenCurrency(void)
{
	u8 d,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,i;
	u8 offset;
	u8 c;
	
	d1 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH1];
	d2 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH2];
	d3 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH3];
	d4 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH4];
	d5 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH5];
	d6 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH6];
	d7 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH7];
	d8 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH8];
	d9 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH9];
	d10 = savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH10];
	
	openCurrencyNum = 0;
	for(i = 0;i < 8;i++)
	{
		d = 1<<i;
		if((d1&d) > 0)
		{
			openCurrency[openCurrencyNum] = i;
			openCurrencyNum++;
		}
	}
	for(i = 0;i < 8;i++)
	{
		d = 1<<i;
		if((d2&d) > 0)
		{
			openCurrency[openCurrencyNum] = i+8;
			openCurrencyNum++;
		}
	}
	for(i = 0;i < 8;i++)
	{
		d = 1<<i;
		if((d3&d) > 0)
		{
			if(i+16 < NOTE_NUM)
			{
			openCurrency[openCurrencyNum] = i+16;
			openCurrencyNum++;
			}
		}
	}
	
	for(i = 0;i < 8;i++)
	{
		d = 1<<(i);
		if((d4&d) > 0)
		{
			if(i+24 < NOTE_NUM)
			{
				openCurrency[openCurrencyNum] = i+24;
				openCurrencyNum++;
			}
		}
	}
	
	for(i = 0;i < 8;i++)
	{
		{
			d = 1<<(i);
			if((d5&d) > 0)
			{
				if(i+32 < NOTE_NUM)
				{
				openCurrency[openCurrencyNum] = i+32;
				openCurrencyNum++;
				}
			}
		}
	}
	
	offset = 40;
	c = d6;
	for(i = 0;i < 8;i++)
	{
		//if(i+32 < NOTE_NUM)
		{
			d = 1<<(i);
			if((c&d) > 0)
			{
				if(i+offset < NOTE_NUM)
				{
					openCurrency[openCurrencyNum] = i+offset;
					openCurrencyNum++;
				}
			}
		}
	}
	
	offset = 48;
	c = d7;
	for(i = 0;i < 8;i++)
	{
		//if(i+32 < NOTE_NUM)
		{
			d = 1<<(i);
			if((c&d) > 0)
			{
				if(i+offset < NOTE_NUM)
				{
					openCurrency[openCurrencyNum] = i+offset;
					openCurrencyNum++;
				}
			}
		}
	}
	
	offset = 56;
	c = d8;
	for(i = 0;i < 8;i++)
	{
		//if(i+32 < NOTE_NUM)
		{
			d = 1<<(i);
			if((c&d) > 0)
			{
				if(i+offset < NOTE_NUM)
				{
					openCurrency[openCurrencyNum] = i+offset;
					openCurrencyNum++;
				}
			}
		}
	}
	
	offset = 64;
	c = d9;
	for(i = 0;i < 8;i++)
	{
		//if(i+32 < NOTE_NUM)
		{
			d = 1<<(i);
			if((c&d) > 0)
			{
				if(i+offset < NOTE_NUM)
				{
					openCurrency[openCurrencyNum] = i+offset;
					openCurrencyNum++;
				}
			}
		}
	}
	
	offset = 72;
	c = d10;
	for(i = 0;i < 8;i++)
	{
		//if(i+32 < NOTE_NUM)
		{
			d = 1<<(i);
			if((c&d) > 0)
			{
				if(i+offset < NOTE_NUM)
				{
					openCurrency[openCurrencyNum] = i+offset;
					openCurrencyNum++;
				}
			}
		}
	}

	if(openCurrencyNum == 0)
	{
		openCurrency[0] = INDEX_USD;
		openCurrencyNum = 1;
	}
	
	for(i = 0;i < openCurrencyNum;i++)
	{
		if(g_currency == openCurrency[i])
		{
			break;
		}
	}
	if(i == openCurrencyNum)
	{
		g_currency = openCurrency[0];
	}
}

void MainInit(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
//	ADC_InitTypeDef ADC_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;


	//时钟
	SystemInit();
	#ifdef BOOT_APP
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x10000); 
	#endif
	
	RCC_PCLK1Config(RCC_HCLK_Div2);	//36M
	RCC_PCLK2Config(RCC_HCLK_Div1);	//72M，AD的速度72M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12Mhz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOD |RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  	
	
	//子模块初始化
	uart_Init();	
	fifo_Init();
	delay_Init();	
	eeprom_Init();
	eeprom_ReadData();
	if (savedPara.flag != DATA_FLAG)
	{
		if ((savedPara.flag&0xf0000000) != (DATA_FLAG & 0xf0000000))
		{
			InitAllPara();//初始化所有参数
			#ifdef BOOT_APP	
			flash_SaveUpdateFlag(0);
			#endif
		}
		else//初始化用户设置的参数
		{
			InitMachineWorkPara();
			InitUserWorkPara();
		}
		savedPara.flag = DATA_FLAG;
		eeprom_SaveData();
	}
	if(savedPara.uvGrade > 30)
	{
		savedPara.uvGrade = 5;
		eeprom_SaveData();
	}
	//更新面额
	GetOpenCurrency();
	g_currency = savedPara.machineWorkPara.d[DEFAULT_CURRENCY];
	//main.c及中断的管脚初始化
	InitGpioInMain();
	
	tim_init();
	
	motor_Init();
	
		//码盘中断
	GPIO_EXTILineConfig(MP_GPIO_EXTI_PORT_SOURCE, MP_GPIO_EXTI_PIN_SOURCE);

	EXTI_InitStructure.EXTI_Line = MP_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = MP_EXTI_TRIGGER;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = MP_EXTI_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	adc_init();
	USB_Config();
}

void InitDMA(void)
{
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_ADDRESS;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)adcResult;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = CHANNELS_PER_DMA_GROUP;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
}

void adc_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	
//	EXTI_InitTypeDef EXTI_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	InitDMA();
	//配置DMA中断
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);        //DMA通道1传输完成中断

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	ADC_DeInit(ADC1); 
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	 //只有软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
	ADC_InitStructure.ADC_NbrOfChannel = CHANNELS_PER_DMA_GROUP;
	ADC_Init(ADC1, &ADC_InitStructure);
	/* ADC1 regular channels configuration */ 
	/*
ADC1
PC0		填充
MG-RGB	PA4	ADC4	4051六选1
IR8-14	PC2	ADC12	4051七选1 

ADC2 
IR1-7	PC1	ADC11	4051七选1
IR15-21	PC3	ADC13	4051七选1	
HOPPER	PC5	ADC15	不选
*/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_7Cycles5);//UV
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_7Cycles5);//RGB
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 3, ADC_SampleTime_7Cycles5);//MGR
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 4, ADC_SampleTime_7Cycles5);//IR8-14
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 5, ADC_SampleTime_7Cycles5);//MGL

	/* Enable ADC1 DMA */
	
	/* ADC2 configuration ------------------------------------------------------*/
	ADC_DeInit(ADC2); 
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	 //只有软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
	ADC_InitStructure.ADC_NbrOfChannel = CHANNELS_PER_DMA_GROUP;
	ADC_Init(ADC2, &ADC_InitStructure);
	/* ADC2 regular channels configuration */ 

	ADC_RegularChannelConfig(ADC2, ADC_Channel_1, 1, ADC_SampleTime_7Cycles5);//TDJS2
	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 2, ADC_SampleTime_7Cycles5);//TDJS1
	ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 3, ADC_SampleTime_7Cycles5);//IR1-7
	ADC_RegularChannelConfig(ADC2, ADC_Channel_13, 4, ADC_SampleTime_7Cycles5);//IR15-21
	ADC_RegularChannelConfig(ADC2, ADC_Channel_15, 5, ADC_SampleTime_7Cycles5);//HOPPER
	
	
	/* Enable ADC2 external trigger conversion */
	ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	/* Enable ADC2 */
	ADC_Cmd(ADC2, ENABLE);
	ADC_ResetCalibration(ADC2);
	while(ADC_GetResetCalibrationStatus(ADC2));
	ADC_StartCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2));

	ADC_DMACmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);

	DMA_ClearFlag(DMA1_FLAG_TC1);
}

void SampleOneRow(void)
{
	u8 i,j;
	
	//关闭中断，采集一行数据
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, DISABLE);

	delay_DelayMs(3);
	chanelIndexOf4051 = 0;
	set4051Chanel(chanelIndexOf4051);
	
	for(j = 0;j < 7;j++)
	{
		ADOneTime();

		//读取DMA传给数组的值，并保存到对应的位置的数组中 高16位为ADC2接收的数据,低16位位ADC1接收到的数据
		for (i=0; i<CHANNELS_PER_DMA_GROUP; i++)
		{
			adData[i*2] = (u8)(adcResult[i] >> 8);//低16位		ADC1
			adData[i*2+1] = (u8)(adcResult[i] >> 24);//高16位	ADC2
		}
	/*
	ADC1
	UV		  PA0	ADC0						adData[0]
	RGB	    PA4	ADC4	4051 4选1 adData[2]
	MGR	    PC0	ADC10	          adData[4]
	IR8-14	PC2	ADC12	4051 7选1 adData[6]
	MGL	    PC4	ADC14	          adData[8]
	

	ADC2 
	TDJS2 	PA1	ADC1 	不选			  adData[1]
	TDJS1 	PA2	ADC2	不选			  adData[3]
	IR1-7 	PC1	ADC11	4051七选1		adData[5]
	IR15-21	PC3	ADC13	4051七选1	  adData[7]
	HOPPER	PC5	ADC15	不选			  adData[9]
	*/
	
// 	//enteranceSensorVal = adData[8];
		if(j == 0)
		{
			enteranceSensorVal = adData[9];
			tdjsValue[0] = adData[1];
			tdjsValue[1] = adData[3];
			UvValue = adData[0];
			mrValue[0] = adData[4];
			mrValue[1] = adData[8];
		}
		switch(chanelIndexOf4051)
		{
			case 0:
				irValue[0] = adData[5];
				irValue[7] = adData[6];
				irValue[14] = adData[7];
				break;
			case 1:
				irValue[1] = adData[5];
				irValue[8] = adData[6];
				irValue[15] = adData[7];
				break;
			case 2:
				irValue[2] = adData[5];
				irValue[9] = adData[6];
				irValue[16] = adData[7];
				if(g_colorFsRGB == FS_RED)
				{
					colorRGB[0][0] = adData[2];
				}
				else if(g_colorFsRGB == FS_GREEN)
				{
					colorRGB[0][1] = adData[2];
				}
				else if(g_colorFsRGB == FS_BLUE)
				{
					colorRGB[0][2] = adData[2];
				}
				break;
			case 3:
				irValue[3] = adData[5];
				irValue[10] = adData[6];
				irValue[17] = adData[7];
				if(g_colorFsRGB == FS_RED)
				{
					colorRGB[1][0] = adData[2];
				}
				else if(g_colorFsRGB == FS_GREEN)
				{
					colorRGB[1][1] = adData[2];
				}
				else if(g_colorFsRGB == FS_BLUE)
				{
					colorRGB[1][2] = adData[2];
				}
				break;
			case 4:
				irValue[4] = adData[5];
				irValue[11] = adData[6];
				irValue[18] = adData[7];
				if(g_colorFsRGB == FS_RED)
				{
					colorRGB[2][0] = adData[2];
				}
				else if(g_colorFsRGB == FS_GREEN)
				{
					colorRGB[2][1] = adData[2];
				}
				else if(g_colorFsRGB == FS_BLUE)
				{
					colorRGB[2][2] = adData[2];
				}
				break;
			case 5:
				irValue[5] = adData[5];
				irValue[12] = adData[6];
				irValue[19] = adData[7];
				if(g_colorFsRGB == FS_RED)
				{
					colorRGB[3][0] = adData[2];
				}
				else if(g_colorFsRGB == FS_GREEN)
				{
					colorRGB[3][1] = adData[2];
				}
				else if(g_colorFsRGB == FS_BLUE)
				{
					colorRGB[3][2] = adData[2];
				}
				break;
			case 6:
				irValue[6] = adData[5];
				irValue[13] = adData[6];
				irValue[20] = adData[7];
				break;
		}
		chanelIndexOf4051 ++;
		chanelIndexOf4051 %= 7;
		set4051Chanel(chanelIndexOf4051);
		delay_DelayUs(500);
	}
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
}


void ADOneTime2(void)
{														
	//开始一组转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void ADOneTime(void)
{
//	DMA_ClearFlag(DMA1_FLAG_TC1);														
	ADOneTime2();
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
	DMA_ClearFlag(DMA1_FLAG_TC1);
}		

#define SPEED800_PERIOD 450
void SetSmpleRatioTimer(u8 spd)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_Cmd(TIM4, DISABLE);
	//定时器 50us adc扫描使用
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	switch(spd)
	{
		case SPEED_800:
//			Period = SPEED800_PERIOD;
			break;
		case SPEED_900:
//			Period = SPEED800_PERIOD*8/9;
			break;
		case SPEED_1000:
	//		Period = SPEED800_PERIOD*8/10;
			break;
		default:
			break;
	}
	//APB1的预分频数不为1的时候 定时器时钟是APB1的2倍
	//PCLK1 = 36Mhz，TIM2CLK = 36M/180 * 2 = 400K, Period = 100, 除以 TIM_Period TIM2 counter定时器频率 = 4k Hz, 周期为250us
	//PCLK1 = 36Mhz，TIM2CLK = 36M/180 * 2 = 400K, Period = 300, 除以 TIM_Period TIM2 counter定时器频率 = 1.33k Hz, 周期为750us
	//PCLK1 = 36Mhz，TIM2CLK = 36M/180 * 2 = 400K, Period = 400, 除以 TIM_Period TIM2 counter定时器频率 = 1 k Hz, 周期为1ms
// 	TIM_TimeBaseStructure.TIM_Prescaler = 720-1;
// 	TIM_TimeBaseStructure.TIM_Period = 200-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 180-1;
	TIM_TimeBaseStructure.TIM_Period = 300-1;//Period-1;
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);	

	// TIM IT enable
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);	
	
	//TIM1 enable counter
	TIM_Cmd(TIM4, ENABLE);
}

void tim_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	//定时器5ms，通用定时器
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//PCLK1 = 36Mhz，TIM2CLK = 36M/180 * 2 = 400K, Period = 2000, TIM2 counter定时器频率 = 200 Hz, 周期为5ms
	TIM_TimeBaseStructure.TIM_Prescaler = 180-1;
	TIM_TimeBaseStructure.TIM_Period = 2000-1;
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	

	// TIM IT enable
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);	
	
	//TIM2 enable counter
	TIM_Cmd(TIM2, ENABLE);
	
	//电机脉宽计数器
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	//APB1的预分频数不为1的时候 定时器时钟是APB1的2倍
	//PCLK1 = 36Mhz，TIM4CLK = 36M/720 * 2 = 100K, Period = 500, 除以 TIM_Period TIM4 counter定时器频率 = 10k Hz, 周期为100us
	TIM_TimeBaseStructure.TIM_Prescaler = 720-1;//100us
	TIM_TimeBaseStructure.TIM_Period = 10000-1;
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);	

	// TIM IT enable
	//TIM_SetCounter(TIM5,0);
	//TIM_ARRPreloadConfig(TIM5, ENABLE);
	//TIM5 enable counter
	TIM_Cmd(TIM5, DISABLE);
}

void InitGpioInMain(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	//管脚配置：打开所有的时钟频率
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	
		//测试管脚
//	GPIO_InitStructure.GPIO_Pin = TEST_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode  = TEST_GPIO_MODE; 
//	GPIO_Init(TEST_GPIO_PORT, &GPIO_InitStructure);
//	test_Off();

	//USB
	GPIO_InitStructure.GPIO_Pin = USB_EN_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = USB_EN_GPIO_MODE; 
	GPIO_Init(USB_EN_GPIO_PORT, &GPIO_InitStructure);
	Usben_On();
	
	GPIO_InitStructure.GPIO_Pin = USB_FAULT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = USB_FAULT_GPIO_MODE; 
	GPIO_Init(USB_FAULT_GPIO_PORT, &GPIO_InitStructure);	
	
	//红外发射控制
	GPIO_InitStructure.GPIO_Pin = HW_FS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = HW_FS_GPIO_MODE; 
	GPIO_Init(HW_FS_GPIO_PORT, &GPIO_InitStructure);
	
	//UV发射控制
	GPIO_InitStructure.GPIO_Pin = UV_FS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = UV_FS_GPIO_MODE; 
	GPIO_Init(UV_FS_GPIO_PORT, &GPIO_InitStructure);
	uvfs_Off();
	
	//进钞发射
	GPIO_InitStructure.GPIO_Pin = ENTERANCE_FS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = ENTERANCE_FS_GPIO_MODE; 
	GPIO_Init(ENTERANCE_FS_GPIO_PORT, &GPIO_InitStructure);
	jckfs_Off();
	//蜂鸣器
	GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = BEEP_GPIO_MODE; 
	GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);	
	
	//RGB发射控制
	GPIO_InitStructure.GPIO_Pin = R_FS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = R_FS_GPIO_MODE; 
	GPIO_Init(R_FS_GPIO_PORT, &GPIO_InitStructure);	
	redFs_Off();	
	
	GPIO_InitStructure.GPIO_Pin = G_FS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = G_FS_GPIO_MODE; 
	GPIO_Init(G_FS_GPIO_PORT, &GPIO_InitStructure);	
	greenFs_Off();
	
	GPIO_InitStructure.GPIO_Pin = B_FS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = B_FS_GPIO_MODE; 
	GPIO_Init(B_FS_GPIO_PORT, &GPIO_InitStructure);		
	blueFs_Off();
	
	//hwfs_On();
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);  //使能禁止JTAG	   用到了 PB3
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);    

	GPIO_InitStructure.GPIO_Pin = A_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = A_GPIO_MODE; 
	GPIO_Init(A_GPIO_PORT, &GPIO_InitStructure);		
	GPIO_InitStructure.GPIO_Pin = B_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = B_GPIO_MODE; 
	GPIO_Init(B_GPIO_PORT, &GPIO_InitStructure);		
	GPIO_InitStructure.GPIO_Pin = C_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = C_GPIO_MODE; 
	GPIO_Init(C_GPIO_PORT, &GPIO_InitStructure);		
	set4051Chanel(0);
	
	GPIO_InitStructure.GPIO_Pin = KEY0_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = KEY0_GPIO_MODE; 
	GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = KEY1_GPIO_MODE; 
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = KEY2_GPIO_MODE; 
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);		

	//码盘
	GPIO_InitStructure.GPIO_Pin = MP_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = MP_GPIO_MODE; 
	GPIO_Init(MP_GPIO_PORT, &GPIO_InitStructure);
	
}

void set4051Chanel(u8 index)
{
	switch(index)
	{
		case 0:
			C_LOW();
			B_LOW();
			A_LOW();
			break;
		case 1:
			C_LOW();
			B_LOW();
			A_HIGH();
			break;
		case 2:
			C_LOW();
			B_HIGH();
			A_LOW();
			break;
		case 3:
			C_LOW();
			B_HIGH();
			A_HIGH();
			break;
		case 4:
			C_HIGH();
			B_LOW();
			A_LOW();
			break;
		case 5:
			C_HIGH();
			B_LOW();
			A_HIGH();
			break;
		case 6:
			C_HIGH();
			B_HIGH();
			A_LOW();
			break;
		case 7:
			C_HIGH();
			B_HIGH();
			A_HIGH();
			break;
	}
}

u8 ctlSend=0;
u8 const SEND[] = {1,1,1,1,1};//{1,0,1,0,0};
void ToggleJinChaoFaShe(void) 
{
	ctlSend ++;
	ctlSend %= sizeof(SEND);
	if (SEND[ctlSend] == 0)
	{
//		jckfs_Off();
	}
	else
	{
		jckfs_On();
	}
}

typedef void (*pFunction)(void);
static pFunction Jump_To_Application;
static unsigned int JumpAddress;

void RunProgramme(unsigned int Address)
{
    /* Test if user code is programmed starting from address "ApplicationAddress" */
    if (((*(__IO uint32_t*)Address) & 0x2FFE0000 ) == 0x20000000)
    { /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (Address + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) Address);
      Jump_To_Application();
    }
}
//-----------------------------------------------------------------------
//中断函数
//-----------------------------------------------------------------------
//#include "stm32f10x_it.c"
/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

// //SPI中断服务程序,接收主板的控制指令
// void SPI2_IRQHandler(void)
// {

// /*	if(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) != RESET)
// 	{	
// 		spiDataIn = SPI_I2S_ReceiveData(SPI2);
// 		SPI_I2S_SendData(SPI2, 0xff);	//在没准备好前，先发出0xff
// //		gb_needDealSpiDataIn = 1;
// 		switch(spiDataIn)
// 		{
// 			case SPI_COMMAND_FROM_KZB_TO_CTB_ONE_NOTE_START:
// 				gb_enableSample = 1;
// 				sampleIndex = 0;
// 				lastSampleTimes = 0;
// 				break;
// 			case SPI_COMMAND_FROM_KZB_TO_CTB_ONE_NOTE_END:
// 				lastSampleTimes = 200;
// 				break;
// 			default:
// 				break;
// 		}
// 	} */
// }

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

u16 oneSecCnt = 0;
u16 gb_SecCnt = 0;


void SysTick_Handler(void)
{
	if (TimingDelay > 0)
	{
		TimingDelay --;
	}
	timeCnt++;
//	if(gb_testGpioC6On == 1)
//	{
//		test_Off();
//	}
//	else
//	{
//		test_On();
//	}
	if(gb_errflagOverTime > 0)
	{
		gb_errflagOverTime--;
		if(gb_errflagOverTime == 0)
		{
			gb_errflagClearDisp = 1;
		}
	}
	if(gb_selfcheckErrorStateOverTime > 0)
	{
		gb_selfcheckErrorStateOverTime--;
		if(gb_selfcheckErrorStateOverTime==0)
		{
			gb_selfcheckErrorStateClearFlag = 1;
		}
	}
	msecCnt++;
	oneSecCnt ++;
	if(oneSecCnt >= 1000)
	{
		oneSecCnt = 0;	
		gb_oneSec = 1;
		gb_oneSecAutoRefresh = 1;
		if(systemState != ENG_MODE)
		{
			if(lcdBackLightOffCnt > 0)
			{
				lcdBackLightOffCnt --;
				if(lcdBackLightOffCnt == 0)
				{
					disp_lcdBLC(0);
					gb_lcdBacklightOn = 0;
				}
			}
		}
	}
	//电机减速超时处理
	if(gb_needStopMotorTimeout > 0)
	{
		gb_needStopMotorTimeout--;
		if(gb_needStopMotorTimeout == 0)
		{
			if(systemState == NORMAL)
			{
				motor1_Stop();//停转
				g_needSaveMpPeriodFlag = 0;
				//test_Off();
				if (gb_noteState == NOTE_FORWARD)
				{
					gb_noteState = NOTE_IDEL;
					mpEndCnt = mpCnt;
					time2 = timeCnt;
					motor1StopRecord = 6;
					gb_oneNotePass = 1;	
					noteState |= STATE_COMPUTE;	
					noteState &= (~STATE_FORWARD_COVER_PS1);
#ifdef DEBUG_MODE	
					testflag[7] = 1;
					testflag2[7] = testflag2Cnt++;
#endif
					gb_needOutPutLength = MAX(PS1ValueRecordCnt,PS2ValueRecordCnt);
				}
				else if (gb_noteState == NOTE_BACKWARD)
				{
					gb_noteState = NOTE_IDEL;
					mpEndCnt = mpCnt;
					time2 = timeCnt;
					motor1StopRecord = 9;
					//gb_notebackInEnteranceFlag = 1;
					//gb_haveNoteInEntergate = 1;
					noteState |= STATE_BACKWARD_COVER_ENTERANCE;
					noteState &= (~STATE_BACKWARD_COVER_PS1);	
#ifdef DEBUG_MODE	
					testflag[8] = 1;
					testflag2[8] = testflag2Cnt++;
#endif					
					initEteranceSensor();
					ententernceCnt = 0;
				}
			}		
		}
	}		
	//按键扫描延时
	if(checkKeyCnt > 0)
	{
		checkKeyCnt --;
		if(checkKeyCnt == 0)
		{
			gb_needCheckKey = 1;
			//gb_needCheckTpClick = 1;
			checkKeyCnt = CHECK_KEY_TIME;
		}
	}
	if(gb_modifiIdentificationWaysDealy > 0)
	{
		gb_modifiIdentificationWaysDealy --;
		if(gb_modifiIdentificationWaysDealy == 0)
		{
			gb_modifiIdentificationWaysFlag = 1;
		}
	}
	if(gb_ChangeCurrencyDelay > 0)
	{
		gb_ChangeCurrencyDelay -- ;
		if(gb_ChangeCurrencyDelay == 0)
		{
			gb_ChangeCurrencyFlag = 1;
		}
	}

	if((gb_enableSample == 1)&&((systemState == NORMAL)||(systemState == DU_BI))&&(gb_needScanEteranceSensor == 1))
	{
		//检测进钞接收
		//开灯无钞为低值 开灯有钞为高值 关灯为低值
		if (gb_jinChaoFaSheIsOn)//开灯
		{
			lastFsOnVal = enteranceSensorVal;
			if(ententernceCnt < 500)
			{
				ententernce[ententernceCnt++] = enteranceSensorVal;
			}
			
			if(//(enteranceSensorVal > lastFsOffVal + ENTERANCE_HAVENOTE_CHAZHI)&&
				(enteranceSensorVal > ENTERANCE_HAVENOTE_THRES))
			{
				entergatePulseNumCounter ++;
			}
			else
			{
				if (entergatePulseNumCounter > 0)
				{
					entergatePulseNumCounter --;
				}
			}
		}
		else//关灯
		{
			lastFsOffVal = enteranceSensorVal;//关灯为高
			if(enteranceSensorVal < (ENTERANCE_HAVENOTE_THRES))
			{
				entergatePulseNumCounter ++;
			}
			else
			{
				if (entergatePulseNumCounter > 0)
				{
					entergatePulseNumCounter --;
				}
			}
		}
		
		fiveMsCnt ++;
		if(g_currency != INDEX_GBP)
		{
			if(fiveMsCnt >= 5)
			{
				fiveMsCnt = 0;
				ToggleJinChaoFaShe();		

				scanEntergateTimer ++;
				if(scanEntergateTimer >= SCAN_ENTERGATE_TIME)
				{
					scanEntergateTimer = 0;
					//进钞编码统计
	
					if (entergatePulseNumCounter >= MIN_HAVEMONEY_PULSENUM_COUNT)
					{
						gb_haveNoteInEntergate = 1;
					}
					else
					{
					
						gb_haveNoteInEntergate = 0;
					}
					entergatePulseNumCounter = 0;	
				}					
			}	
		}
		else
		{
			if(fiveMsCnt >= 5)
			{
				fiveMsCnt = 0;
				ToggleJinChaoFaShe();		

				scanEntergateTimer ++;
				if(scanEntergateTimer >= SCAN_ENTERGATE_TIME)
				{
					scanEntergateTimer = 0;
					//进钞编码统计
	
					if (entergatePulseNumCounter >= (MIN_HAVEMONEY_PULSENUM_COUNT))
					{
						gb_haveNoteInEntergate = 1;
						//noMoneyOnEntergateCounter = 0;
					}
					else
					{
						gb_haveNoteInEntergate = 0;
						//noMoneyOnEntergateCounter = 5;
					}
					entergatePulseNumCounter = 0;	
				}					
			}	
		}
	}
	
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
void USART1_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE))
	{
		/* Read one byte from the receive data register */
		uart1infifo_DataIn(USART_ReceiveData(USART1));	//自动清除RXNE标志
		gb_needDealUart1Data = 1;
	}
	else if (USART_GetFlagStatus(USART1, USART_FLAG_TXE))
	{		
		if (uart1outfifo_count > 0)
		{
			/* Write one byte to the transmit data register */
			USART_SendData(USART1, uart1outfifo_DataOut());	//顺便清除flag_TXE
		}				
		else
		{
		  	/* Disable the USARTy Transmit interrupt */
		  	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);		//实际上，发送为空的标志还在，只是关闭中断
//			gb_uart1IsBusy = 0;
		}    
	}
}

 void USART3_IRQHandler(void)
 {
 	if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE))
 	{
 		/* Read one byte from the receive data register */
 		uart3infifo_DataIn(USART_ReceiveData(USART3));	//自动清除RXNE标志
 // 		uart3DelayTimer = UART1_DATA_DELAY;
		gb_needDealUart3Data = 1;

 	}
 	else if (USART_GetFlagStatus(USART3, USART_FLAG_TXE))//USART_FLAG_TXE
 	{		
 		if (uart3outfifo_count > 0)
 		{
 			/* Write one byte to the transmit data register */
 			USART_SendData(USART3, uart3outfifo_DataOut());	//顺便清除flag_TXE
 		}				
 		else
 		{
 		  /* Disable the USARTy Transmit interrupt */
 		  USART_ITConfig(USART3, USART_IT_TXE, DISABLE);		//实际上，发送为空的标志还在，只是关闭中断
 		}    
 	}
 }


//50us定时器
void TIM4_IRQHandler(void)
{
	if (TIM_GetFlagStatus(TIM4, TIM_IT_Update))
  {
		TIM_ClearFlag(TIM4, TIM_IT_Update);	
		
		if(((gb_enableSample == 1)||(needSampleIdleNum > 0))&&(gb_enableSampleFlag == 0))
		{
			if(needSampleIdleNum > 0)
			{
				needSampleIdleNum--;
				if(needSampleIdleNum == 0)
				{
					motor1_Stop();
					gb_colorSampleEnable = 0;
					gb_lengthIrNeedStartSampleflag = 0;
					lengthDataLen = g_lengthSampleIndex;
					gb_uvNeedStartSampleflag = 0;
				}
			}
			//开启一次采集
//			timeCnt++;
			ADOneTime2();
			sampleStartNum ++;		
		}
	}
}

u8 isLengthIrHaveNote(void)
{
	u8 i,k;
	u8 max = 0;
	
	if(gb_hwVccIsOn == 0)
	{
		return 0;
	}
	max = 0;
	k = 0;
	for(i = 0;i < LENGTH_IR_CHANNEL_NUM;i++)
	{
		if(irValue[i] < lengthIdleOriginValue[i] - LENGTH_HAVENOTE_VALUE_THRES)
		{
			k ++;
		}
		else
		{		
			if(k > max)
			{
				max = k;
			}
			k = 0;
		}
	}
	if(k > max)
	{
		max = k;
	}
	if(max >= LENGTH_HAVENOTE_NUM_THRES)
	{
		return 1;
	}
// 	if((g_lengthSampleIndex < 150)&&(gb_lengthHaveNote == 1))
// 	{
// 		k = 0;
// 	}
	return 0;
}
void ClearPSIrFlag(void)
{
	PS1Flag = 0;
	gb_haveNoteInPS1 = 0;
	PS2Flag = 0;
	gb_haveNoteInPS2 = 0;
	PS3Flag = 0;
	gb_haveNoteInPS3 = 0;
}
void ClearJamFlag(void)
{
	g_maxMpFromPs1ToPs2 = 0;
	g_maxMpFromEnteranceToPs1 = 0;
	g_maxMpFromPs1ToEnterance = 0;
	g_maxMpFromPs2ToLeave = 0;
	g_maxMpFromComputeToPS1 = 0;
	gb_needStopMotorTimeout = 0;
	
}
//位置管1，给测长触发 给颜色触发
void DealPS1INT(void)
{
	if(gb_hwVccIsOn == 1)//开灯时
	{
		PS1Flag <<= 1;
		if(PS1ValueRecordCnt < 1500)
		{
			PS1ValueRecord[PS1ValueRecordCnt++] = tdjsValue[0];
		}
		if(tdjsValue[0] < (TONGDAO_HAVENOTE_THRES))
		{
			PS1Flag ++;
		}
		if(systemState == NORMAL)
		{
			if(gb_haveNoteInPS1 == 0)
			{
				if((PS1Flag&0x0000000f) == 0x0000000f)//ir2进币
				{
					gb_haveNoteInPS1 = 1;		
					if(gb_noteState == NOTE_BACKWARD)
					{
						if(g_currency != INDEX_GBP)
						{
							g_maxMpFromComputeToPS1 = 0;
							gb_haveNoteInEntergate = 1;
							noteState |= STATE_BACKWARD_COVER_PS1;
							noteState &= (~STATE_BACKWARD_NOTE_LEAVE);
#ifdef DEBUG_MODE	
							testflag[9] = 1;
							testflag2[9] = testflag2Cnt++;
#endif							
						}
					}
					else if(gb_noteState == NOTE_FORWARD)
					{
						if(g_currency != INDEX_GBP)
						{
							g_maxMpFromEnteranceToPs1 = 0;
							g_maxMpFromPs1ToPs2 = MP_FROM_PS1_TO_PS2;
							noteState |= STATE_FORWARD_COVER_PS1;
							noteState &= (~STATE_FORWARD_COVER_ENTERANCE);
#ifdef DEBUG_MODE	
							testflag[10] = 1;
							testflag2[10] = testflag2Cnt++;
#endif
							//开始采集
							gb_uvNeedStartSampleCnt = 55;
							gb_lengthIrNeedStartSampleCnt = 25;
							gb_colorSampleEnable = 1;
							g_colorSampleIndex = 0;
							g_lengthSampleIndex = 0;
							g_lengthIrMpNum = 0;	
							lengthMpCnt = 0;
							g_mgSampleIndex = 0;
						}
						if(mpCnt < 1000)
						{
							mpCntRecode[mpCnt] = 20;
						}
						if(timeCnt < 1000)
						{
							msCntRecode[timeCnt] = 20;
						}
					}
				}
			}
			else if(gb_haveNoteInPS1 == 1)
			{
				if((PS1Flag&0x000fffff) == 0x00000000)//离开ir2
				{
					gb_haveNoteInPS1 = 0;
					if(gb_noteState == NOTE_FORWARD)
					{
						if(g_currency != INDEX_GBP)
						{
							gb_colorSampleEnd = 2;
						}
						if(mpCnt < 1000)
						{
							mpCntRecode[mpCnt] = 60;
						}
						if(timeCnt < 1000)
						{
							msCntRecode[timeCnt] = 60;
						}
					}
					else if(gb_noteState == NOTE_BACKWARD)
					{

					}
				}
			}
		}
	}
	else
	{
		PS1Flag = 0;
		gb_haveNoteInPS1 = 0;
	}
}
//位置红外2   使用红外管
void DealPS2INT(void)
{
	if(gb_hwVccIsOn == 1)//开灯时
	{
		PS2Flag <<= 1;
		if(1 == isLengthIrHaveNote())
		{
			gb_lengthCovered = 1;
		}
		else
		{
			gb_lengthCovered = 0;
		}

		if(gb_lengthCovered == 1)
		{
			PS2Flag ++;
		}
		if(PS2ValueRecordCnt < 1500)
		{
			//PS2ValueRecord2[PS2ValueRecordCnt] = PS2FlagCnt;
			PS2ValueRecord[PS2ValueRecordCnt++] = irValue[13];
		}
		if(systemState == NORMAL)
		{
			if(gb_haveNoteInPS2 == 0)
			{
				if((PS2Flag&0x0f) == 0x0f)//ps2进币
				{
					gb_haveNoteInPS2 = 1;		
					PS2FlagCnt = 0;
					if(gb_noteState == NOTE_BACKWARD)
					{
						if(g_currency == INDEX_GBP)
						{
							gb_haveNoteInEntergate = 1;
							g_maxMpFromComputeToPS1 = 0;
							noteState |= STATE_BACKWARD_COVER_PS1;
							noteState &= (~STATE_BACKWARD_NOTE_LEAVE);
#ifdef DEBUG_MODE	
							testflag[11] = 1;
							testflag2[11] = testflag2Cnt++;
#endif							
						}
					}
					else if(gb_noteState == NOTE_FORWARD)
					{
						g_maxMpFromEnteranceToPs1 = 0;
						if(g_currency == INDEX_GBP)
						{
							g_maxMpFromEnteranceToPs1 = 0;
							g_maxMpFromPs1ToPs2 = MP_FROM_PS1_TO_PS2;
							noteState |= STATE_FORWARD_COVER_PS1;
							noteState &= (~STATE_FORWARD_COVER_ENTERANCE);
#ifdef DEBUG_MODE		
							testflag[12] = 1;
							testflag2[12] = testflag2Cnt++;	
#endif
							//开始采集
							gb_uvNeedStartSampleCnt = 30;
							//gb_lengthIrNeedStartSampleCnt = 25;
							gb_lengthIrNeedStartSampleflag = 1;
							gb_colorSampleEnable = 1;
							g_colorSampleIndex = 0;
							g_lengthSampleIndex = 0;
							g_lengthIrMpNum = 0;	
							lengthMpCnt = 0;
							g_mgSampleIndex = 0;
						}
						if(mpCnt < 1000)
						{
							mpCntRecode[mpCnt] = 100;
						}
						if(timeCnt < 1000)
						{
							msCntRecode[timeCnt] = 100;
						}
					} 
				}
			}
			else if(gb_haveNoteInPS2 == 1)
			{
				if(gb_noteState == NOTE_FORWARD)
				{
					if((PS2Flag&0x0f) == 0x00 && gb_haveNoteInPS1 == 0)//离开PS2
					{
						PS2FlagCnt = 0;
						gb_haveNoteInPS2 = 0;
						if(g_currency == INDEX_GBP)
						{
							//gb_colorSampleEnd = 2;
							gb_colorSampleEnable = 0;
							colorDataLen = g_colorSampleIndex;
						}
						gb_uvNeedEndSampleCnt = 30;//40;//50;
						gb_needBackMotorCnt = 20;
						gb_lengthIrNeedEndSampleCnt = 2;//30;
						if(mpCnt < 1000)
						{
							mpCntRecode[mpCnt] = 80;
						}
						if(timeCnt < 1000)
						{
							msCntRecode[timeCnt] = 80;
						}
					}
				}
				else if(gb_noteState == NOTE_BACKWARD)
				{
					//gb_motorNeedEndOneNoteCnt = 10;
					if((PS2Flag&0x0f) == 0x00)
					{
						PS2FlagCnt = 0;
						gb_haveNoteInPS2 = 0;
						//开始刹车
						motor1_ForwardRun();
						g_needSaveMpPeriodFlag = 1;
						gb_mpPeriodRecordCnt = 0;
						
						gb_needStopMotorTimeout = 50;//35;

					}
				}
			}
		}
	}
	else
	{
		PS2Flag = 0;
		gb_haveNoteInPS2 = 0;
	}
}
//位置红外3

void DealPS3INT(void)
{
	if(gb_hwVccIsOn == 1)//开灯时
	{
		PS3Flag <<= 1;

		if(tdjsValue[1] < (TONGDAO_HAVENOTE_THRES))
		{
			PS3Flag ++;
			PS3FlagCnt = 0;
		}
		else
		{
			PS3FlagCnt++;
		}

		if(systemState == NORMAL)
		{
			if(gb_haveNoteInPS3 == 0)
			{
				if((PS3Flag&0x0f) == 0x0f)//ps3进币
				{
					gb_haveNoteInPS3 = 1;		
					PS3FlagCnt = 0;
					if(gb_noteState == NOTE_BACKWARD)
					{

					}
					else if(gb_noteState == NOTE_FORWARD)
					{
						g_maxMpFromPs1ToPs2 = 0;
						if(mpCnt < 1000)
						{
							mpCntRecode[mpCnt] = 40;
						}
						if(timeCnt < 1000)
						{
							msCntRecode[timeCnt] = 40;
						}
					} 
				}
			}
			else if(gb_haveNoteInPS3 == 1)
			{
				if((PS3Flag&0x0f) == 0x00)//离开PS2
				{
					PS3FlagCnt = 0;
					gb_haveNoteInPS3 = 0;

					if(gb_noteState == NOTE_FORWARD)
					{
						if(mpCnt < 1000)
						{
							mpCntRecode[mpCnt] = 120;
						}
						if(timeCnt < 1000)
						{
							msCntRecode[timeCnt] = 120;
						}
					}
					else if(gb_noteState == NOTE_BACKWARD)
					{
						//gb_motorNeedEndOneNoteCnt = 10;
					}
				}
			}
		}
	}
	else
	{
		PS3Flag = 0;
		gb_haveNoteInPS3 = 0;
	}
}
void DealLengthIrINT(void)
{
	u8 i;
	//测长自触发采集
//	if(gb_hwVccIsOn == 0)
//	{
//		return;
//	}
	
	if(gb_lengthHaveNote == 0)
	{
//		if((lengthFlag&0x03) == 0x03)
//		{
//			gb_lengthHaveNote = 1;	
//			timeTest[4] = mpCnt;
//		}
	}
	else
	{
//		if((lengthFlag&0x0f) == 0x00)//离开f1
//		{
//			gb_uvNeedEndSampleCnt = 6;
//			gb_lengthHaveNote = 0;
//			if(g_motor1State == MOTOR_FORWARD_RUN)
//			{
//				lengthDataLen = g_lengthSampleIndex;
////				gb_oneNotePass = 1;	
////				noteState |= STATE_COMPUTE;	
////				noteState &= (~STATE_FORWARD_COVER_LENGTH);
//			}
//			else if(g_motor1State == MOTOR_BACKWARD_RUN)
//			{
//				g_maxMpFromLengthToEnterance = MP_FROM_LENGTH_TO_ENTERANCE;
//				noteState &= (~STATE_BACKWARD_COVER_LENGTH);				
//			}
//		}
	}	
	if((gb_lengthIrNeedStartSampleflag == 1))//&&(g_motor1State == MOTOR_FORWARD_RUN))
	{
		if(g_lengthSampleIndex < IR_DATA_MAX_LEN)
		{
			//保存数据
			for(i = 0;i < 21;i++)
			{
				if((gb_lengthInOriginData == 1)||(gb_inCollabration > 0))
				{
					lengthData[i][g_lengthSampleIndex] = irValue[i];//irValue[20-i];
				}
				else
				{
					//校正后数据
					lengthData[i][g_lengthSampleIndex] = GetAdjustedData(irValue[i],i);//irValue[20-i];
				}
			}
			lengthData[21][g_lengthSampleIndex] = lengthMpCnt;
			g_lengthSampleIndex ++;
		}
		
	}
}

void DealMgSampleINT(void)
{
	if(gb_uvNeedStartSampleflag == 1)
	{
		if(g_mgSampleIndex < MG_DATA_MAX_LEN)
		{
			mgData[0][g_mgSampleIndex] = mrValue[0]; 
			mgData[1][g_mgSampleIndex] = mrValue[1]; 				
			g_mgSampleIndex ++;
		}
	}
	else
	{
		//保存空闲态数据
		lastMgData[0][lastMgDataIndex] = mrValue[0]; 
		lastMgData[1][lastMgDataIndex] = mrValue[1]; 

		lastMgDataIndex ++;	
		lastMgDataIndex %= LAST_MG_DATA_MAX;
	}
}


void DealUVSampleINT(void)
{
	//if(g_motor1State == MOTOR_FORWARD_RUN)
	{
		if(gb_uvNeedStartSampleflag == 1)
		{
			if(g_uvSampleIndex < UV_DATA_MAX_LEN)
			{
				if(gb_inCollabration == COLLABRATION_UV)
				{
					uvData[g_uvSampleIndex] = UvValue;
				}
				else
				{
					uvData[g_uvSampleIndex] = MIN(UvValue*MAX_UV_VALUE/savedPara.uvWhiteValue,255);  
				}					
				g_uvSampleIndex ++;
			}
		}
	}
}
//colorRGB[4][3];//4个颜色通道 RGB值
void DealColorSampleINT(void)
{
	//if(g_motor1State == MOTOR_FORWARD_RUN)
	{
		if(gb_colorSampleEnable == 1)
		{
			if(g_colorSampleIndex < COLOR_DATA_MAX_LEN)
			{
				if(gb_colorInOriginData == 1)
				{
					if(g_colorFsRGB == FS_BLUE)
					{
						colorData[2][g_colorSampleIndex] = colorRGB[0][2];
						colorData[5][g_colorSampleIndex] = colorRGB[1][2];
						colorData[8][g_colorSampleIndex] = colorRGB[2][2];
						colorData[11][g_colorSampleIndex] = colorRGB[3][2];
						g_colorSampleIndex ++;
					}
					else if(g_colorFsRGB == FS_RED)
					{
						colorData[0][g_colorSampleIndex] = colorRGB[0][0];
						colorData[3][g_colorSampleIndex] = colorRGB[1][0];
						colorData[6][g_colorSampleIndex] = colorRGB[2][0];
						colorData[9][g_colorSampleIndex] = colorRGB[3][0];
					}
					else//GREEN
					{
						colorData[1][g_colorSampleIndex] = colorRGB[0][1];
						colorData[4][g_colorSampleIndex] = colorRGB[1][1];
						colorData[7][g_colorSampleIndex] = colorRGB[2][1];
						colorData[10][g_colorSampleIndex] = colorRGB[3][1];
					}				
				}
				else
				{
					if(g_colorFsRGB == FS_BLUE)
					{
						colorData[2][g_colorSampleIndex] = MIN(colorRGB[0][2]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[2],65535);
						colorData[5][g_colorSampleIndex] = MIN(colorRGB[1][2]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[5],65535);
						colorData[8][g_colorSampleIndex] = MIN(colorRGB[2][2]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[8],65535);
						colorData[11][g_colorSampleIndex] = MIN(colorRGB[3][2]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[11],65535);
						g_colorSampleIndex ++;
					}
					else if(g_colorFsRGB == FS_RED)
					{
						colorData[0][g_colorSampleIndex] = MIN(colorRGB[0][0]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[0],65535);
						colorData[3][g_colorSampleIndex] = MIN(colorRGB[1][0]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[3],65535);
						colorData[6][g_colorSampleIndex] = MIN(colorRGB[2][0]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[6],65535);
						colorData[9][g_colorSampleIndex] = MIN(colorRGB[3][0]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[9],65535);
					}
					else//GREEN
					{
						colorData[1][g_colorSampleIndex] = MIN(colorRGB[0][1]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[1],65535);
						colorData[4][g_colorSampleIndex] = MIN(colorRGB[1][1]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[4],65535);
						colorData[7][g_colorSampleIndex] = MIN(colorRGB[2][1]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[7],65535);
						colorData[10][g_colorSampleIndex] = MIN(colorRGB[3][1]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[10],65535);
					}				
				}
			}
		}
	}
}
//DMA中断
u8 cnt;
void DMA1_Channel1_IRQHandler(void)
{	
	u8 i;
	
 	if(DMA_GetFlagStatus(DMA1_FLAG_TC1))
  {
		DMA_ClearFlag(DMA1_FLAG_TC1); //清除全部中断标志
		
		dmaEndNum ++;
		
		//读取DMA传给数组的值，并保存到对应的位置的数组中 高16位为ADC2接收的数据,低16位位ADC1接收到的数据
		for (i=0; i<CHANNELS_PER_DMA_GROUP; i++)
		{
			adData[i*2] = (u8)(adcResult[i] >> 8);//低16位		ADC1 偶数通道
			adData[i*2+1] = (u8)(adcResult[i] >> 24);//高16位	ADC2 奇数通道
		}

		/*
	ADC1
	UV		PA0	ADC0			  adData[0]
	RGB	    PA4	ADC4	4051 4选1 adData[2]
	MGR	    PC0	ADC10	          adData[4]
	IR8-14	PC2	ADC12	4051 7选1 adData[6]
	MGL	    PC4	ADC14	          adData[8]
	

	ADC2 
	TDJS2 	PA1	ADC1 	不选			adData[1]
	TDJS1 	PA2	ADC2	不选			adData[3]
	IR1-7 	PC1	ADC11	4051七选1		adData[5]
	IR15-21	PC3	ADC13	4051七选1	 	adData[7]
	HOPPER	PC5	ADC15	不选			adData[9]
	*/
	
// 	//enteranceSensorVal = adData[8];
		if(chanelIndexOf4051 == 0)
		{
			enteranceSensorVal = adData[9];
			tdjsValue[0] = adData[1];
			tdjsValue[1] = adData[3];
			UvValue = adData[0];
			mrValue[0] = adData[4];
			mrValue[1] = adData[8];
		}
		switch(chanelIndexOf4051)
		{
			case 0:
				irValue[0] = adData[5];
				irValue[7] = adData[6];
				irValue[14] = adData[7];
				break;
			case 1:
				irValue[1] = adData[5];
				irValue[8] = adData[6];
				irValue[15] = adData[7];
				break;
			case 2:
				irValue[2] = adData[5];
				irValue[9] = adData[6];
				irValue[16] = adData[7];
				if(g_colorFsRGB == FS_RED)
				{
					colorRGB[0][0] = adData[2];
				}
				else if(g_colorFsRGB == FS_GREEN)
				{
					colorRGB[0][1] = adData[2];
				}
				else if(g_colorFsRGB == FS_BLUE)
				{
					colorRGB[0][2] = adData[2];
				}
				break;
			case 3:
				irValue[3] = adData[5];
				irValue[10] = adData[6];
				irValue[17] = adData[7];
				if(g_colorFsRGB == FS_RED)
				{
					colorRGB[1][0] = adData[2];
				}
				else if(g_colorFsRGB == FS_GREEN)
				{
					colorRGB[1][1] = adData[2];
				}
				else if(g_colorFsRGB == FS_BLUE)
				{
					colorRGB[1][2] = adData[2];
				}
				break;
			case 4:
				irValue[4] = adData[5];
				irValue[11] = adData[6];
				irValue[18] = adData[7];
				if(g_colorFsRGB == FS_RED)
				{
					colorRGB[2][0] = adData[2];
				}
				else if(g_colorFsRGB == FS_GREEN)
				{
					colorRGB[2][1] = adData[2];
				}
				else if(g_colorFsRGB == FS_BLUE)
				{
					colorRGB[2][2] = adData[2];
				}
				break;
			case 5:
				irValue[5] = adData[5];
				irValue[12] = adData[6];
				irValue[19] = adData[7];
				if(g_colorFsRGB == FS_RED)
				{
					colorRGB[3][0] = adData[2];
				}
				else if(g_colorFsRGB == FS_GREEN)
				{
					colorRGB[3][1] = adData[2];
				}
				else if(g_colorFsRGB == FS_BLUE)
				{
					colorRGB[3][2] = adData[2];
				}
				break;
			case 6:
				irValue[6] = adData[5];
				irValue[13] = adData[6];
				irValue[20] = adData[7];
				break;
		}
		chanelIndexOf4051 ++;
		//chanelIndexOf4051 %= 7;
		set4051Chanel(chanelIndexOf4051);
		if(chanelIndexOf4051 == 7)//切换一轮 所有数据更新后再处理
		{
		  	DealPS1INT();
		  	DealPS2INT();
		  	DealPS3INT();
			DealLengthIrINT();
			DealMgSampleINT();
			DealColorSampleINT();
			DealUVSampleINT();
		}

		if(chanelIndexOf4051 < 7)//切换完4052后开始下次采集
		{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		}
		if(chanelIndexOf4051 == 7)
		{
			chanelIndexOf4051 = 0;
			set4051Chanel(chanelIndexOf4051);
			//切换颜色光源
			if(g_colorFsStopWork == 0)
			{
				if(g_colorFsRGB == FS_BLUE)
				{
					redFs_On();
					greenFs_Off();
					blueFs_Off();
					//g_colorFsRGB = FS_RED;
				}
				else if(g_colorFsRGB == FS_RED)
				{
					redFs_Off();
					greenFs_On();
					blueFs_Off();
					//g_colorFsRGB = FS_GREEN;
				}
				else if(g_colorFsRGB == FS_GREEN)
				{
					redFs_Off();
					greenFs_Off();
					blueFs_On();
					//g_colorFsRGB = FS_BLUE;
				}	
				else
				{
					redFs_Off();
					greenFs_Off();
					blueFs_Off();					
				}
			}			
		}
	}
}

//5ms定时器
void TIM2_IRQHandler(void)
{
	if (TIM_GetFlagStatus(TIM2, TIM_IT_Update))
	{
		TIM_ClearFlag(TIM2, TIM_IT_Update);

		//串口等待
		if (uart1DelayTimer > 0)
		{
			uart1DelayTimer --;
			if (uart1DelayTimer == 0)
			{
				gb_needDealUart1Data = 1;
			}
		}
		ScanKeyDown();
		
 		scanMotorTimer ++;
 		if(scanMotorTimer >= SCAN_MOTOR_TIME)
 		{
 			scanMotorTimer = 0;
			//大电机调速
			if (((g_motor1State == MOTOR_FORWARD_RUN)||(g_motor1State == MOTOR_BACKWARD_RUN))&&(systemState == NORMAL))
			{
				if(csmpNumCnt < 100)
				{
					csmpNumRecord[csmpNumCnt] = csmpNumInCurrentCycle;
					csmpNumCnt ++;
				}
//				if (csmpNumInCurrentCycle < savedPara.adjustPara.csmpNumIn50ms[currentSpeed] - 1)//速度太慢
//				{
//					if(pwmValOfmotor1 < 0xff)
//					{
//						pwmValOfmotor1 ++;
//						motor1_SetPwm();
//					}
//				}
//				else if (csmpNumInCurrentCycle > savedPara.adjustPara.csmpNumIn50ms[currentSpeed] + 1)//速度太快
//				{
//					if(pwmValOfmotor1 > 55)
//					{
//						pwmValOfmotor1 --;
//						motor1_SetPwm();
//					}
//				}
				if(gb_isJammed == 0)
				{
					//if((savedPara.machineWorkPara.d[INDEX_JAM_TYPE]&CSDDJ_JAM_CHECK) > 0)				
					{
						if (csmpNumInCurrentCycle < JAM_COUNT_VAL)
						{
							csddjJamTimes ++;
							
							if (csddjJamTimes >= MAX_JAM_TIME)
							{
								gb_isJammed = JAM_CSDDJ;
								DealJamAtOnce();		
							}
						}
						else
						{
							csddjJamTimes = 0;
						}
					}
				}
			}
//			else if (g_motor1State == MOTOR_BACKWARD_RUN)
//			{
//				
//			}
			else
			{
				csddjJamTimes = 0;
			}
			csmpNumInCurrentCycle=0;	
			
 		}
		
		if (beepTimes > 0)
		{
			timerForBeep ++;
			//先响和类型对应的一段时间
			if(timerForBeep < beepType)
			{
				beep_On();
			}
			else if (timerForBeep < (beepType+INTERVAL_BEEP_LENGTH))	//然后再关闭一段和间隔对应的时间
			{
				beep_Off();
			}
			else		//将次数减1
			{
				timerForBeep = 0;
				beepTimes --;
				if (beepTimes == 0)
				{
					beep_Off();
				}
			}
		}
	}
}

void DealInMp(void)
{
//	u8 i;
	
// 	if((gb_enableSample == 1)//AD采集进行中
// 		&&(gb_hwVccIsOn == 1))//红外灯开启
// 	{

// 	}
// 	else
// 	{
// 		currentCountNum = -1;
// 		irHaveNoteContinuslyCnt = 0;
// 	}
}
//码盘中断'
u8 mpValue;
u16 mpPeriodCnt;
u8 validMp = 0;
void EXTI9_5_IRQHandler(void)
{
//	if(EXTI_GetITStatus(CSMP_EXTI_LINE) != RESET)//码盘
	if(EXTI_GetFlagStatus(MP_EXTI_LINE))// != RESET)//码盘
	{
		//EXTI_ClearITPendingBit(CSMP_EXTI_LINE);
		EXTI_ClearFlag(MP_EXTI_LINE);
		validMp++;
		if(validMp == 2)
		{
			validMp = 0;
			if(((gb_enableSample == 1)||(needSampleIdleNum > 0))&&(gb_enableSampleFlag == 1))
			{
				if(needSampleIdleNum > 0)
				{
					needSampleIdleNum--;
					if(needSampleIdleNum == 0)
					{
						motor1_Stop();
						gb_colorSampleEnable = 0;
						gb_lengthIrNeedStartSampleflag = 0;
						lengthDataLen = g_lengthSampleIndex;
						gb_uvNeedStartSampleflag = 0;
					}
				}
				//开启一次采集
	//			timeCnt++;
				ADOneTime2();
				sampleStartNum ++;		
			}
			TIM_Cmd(TIM5, DISABLE);
			mpPeriodCnt = TIM5->CNT;
			if(g_needSaveMpPeriodFlag == 1)
			{
				if(gb_mpPeriodRecordCnt < 100)
				{
					gb_mpPeriodRecord[gb_mpPeriodRecordCnt++] = mpPeriodCnt;
				}
				if (mpPeriodCnt > 160)
				{
					motor1_Stop();//停转
					gb_needStopMotorTimeout = 0;
					g_needSaveMpPeriodFlag = 0;
					//test_Off();
					if (gb_noteState == NOTE_FORWARD)
					{
						gb_noteState = NOTE_IDEL;
						mpEndCnt = mpCnt;
						time2 = timeCnt;
						motor1StopRecord = 7;
						gb_oneNotePass = 1;	
						noteState |= STATE_COMPUTE;	
						noteState &= (~STATE_FORWARD_COVER_PS1);
#ifdef DEBUG_MODE
						testflag[13] = 1;
						testflag2[13] = testflag2Cnt++;
#endif						
						gb_needOutPutLength = MAX(PS1ValueRecordCnt,PS2ValueRecordCnt);
					}
					else if (gb_noteState == NOTE_BACKWARD)
					{
						gb_noteState = NOTE_IDEL;
						mpEndCnt = mpCnt;
						time2 = timeCnt;
						motor1StopRecord = 8;
//						gb_notebackInEnteranceFlag = 1;
//						gb_haveNoteInEntergate = 1;
						noteState |= STATE_BACKWARD_COVER_ENTERANCE;
						noteState &= (~STATE_BACKWARD_COVER_PS1);
#ifdef DEBUG_MODE
						testflag[14] = 1;
						testflag2[14] = testflag2Cnt++;
#endif						
						initEteranceSensor();
						ententernceCnt = 0;
					}
				}
			}
			TIM_SetCounter(TIM5, 0);
			TIM_Cmd(TIM5, ENABLE);
			mpCnt ++;
			mpValue = ReadMp();
			csmpNumInCurrentCycle ++;
			
			maxSampleNumOneMp = MAX_SAMPLE_NUM_ONE_MP;
			if(gb_cntMgComputeTime == 1)
			{			
				mgComputeMpNum ++;
			}
			
			if((gb_lengthIrNeedStartSampleflag == 1)&&(g_motor1State == MOTOR_FORWARD_RUN))
			{
				lengthMpCnt ++;
			}

			//颜色采集结束
			if(gb_colorSampleEnd > 0)
			{
				gb_colorSampleEnd--;
				if(gb_colorSampleEnd == 0)
				{
					gb_colorSampleEnable = 0;
					colorDataLen = g_colorSampleIndex;
				}
			}
			//通道中是否有钱计数
			if(g_haveNoNoteCounter > 0)
			{
				g_haveNoNoteCounter --;
			}
			//长度有钱计数
			if((gb_lengthHaveNote == 1)&&(g_motor1State == MOTOR_FORWARD_RUN))
			{
				g_lengthIrMpNum ++;
			}
			if(gb_uvNeedStartSampleCnt > 0)
			{
				gb_uvNeedStartSampleCnt--;
				if(gb_uvNeedStartSampleCnt == 0)
				{
					g_uvSampleIndex = 0;
					gb_uvNeedStartSampleflag = 1;
				}
			}
			if(gb_needBackMotorCnt > 0)
			{
				gb_needBackMotorCnt--;
				if(gb_needBackMotorCnt == 0)
				{
				//	test_On();
					motor1_BackwardRun();
					g_needSaveMpPeriodFlag = 1;
					gb_mpPeriodRecordCnt = 0;
					gb_needStopMotorTimeout = 35;
				}
			}
			if(gb_uvNeedEndSampleCnt > 0)
			{
				gb_uvNeedEndSampleCnt--;
				if(gb_uvNeedEndSampleCnt == 0)
				{
					uvDataLen = g_uvSampleIndex;
					mgDataLen = g_mgSampleIndex;
					gb_uvNeedStartSampleflag = 0;
				}
			}

			if(gb_lengthIrNeedStartSampleCnt > 0)
			{
				gb_lengthIrNeedStartSampleCnt--;
				if(gb_lengthIrNeedStartSampleCnt == 0)
				{
					g_lengthSampleIndex = 0;
					gb_lengthIrNeedStartSampleflag = 1;
				}
			}
			if(gb_lengthIrNeedEndSampleCnt > 0)
			{
				gb_lengthIrNeedEndSampleCnt--;
				if(gb_lengthIrNeedEndSampleCnt == 0)
				{
					lengthDataLen = g_lengthSampleIndex;
					gb_lengthIrNeedStartSampleflag = 0;
				}
			}
			
			if(g_maxMpFromPs1ToPs2 > 0)
			{
				g_maxMpFromPs1ToPs2 --;
				if(g_maxMpFromPs1ToPs2 == 0)
				{
					noteState &= (~STATE_FORWARD_COVER_PS1);
					//gb_needStopMotor = 1;
					//开盖或堵币 切到堵币状态 堵币状态下扫描全部红外无遮挡 就恢复normal
					gb_isJammed = JAM_ENTERANCE_TO_LENGTH;	
					DealJamAtOnce();
				}
			}
			if(g_maxMpFromEnteranceToPs1 > 0)
			{
				g_maxMpFromEnteranceToPs1 --;
				if(g_maxMpFromEnteranceToPs1 == 0)
				{
					noteState &= (~STATE_FORWARD_COVER_ENTERANCE);
					//gb_needStopMotor = 1;
					//开盖或堵币 切到堵币状态 堵币状态下扫描全部红外无遮挡 就恢复normal
					gb_isJammed = JAM_ENTERANCE_TO_LENGTH;	
					DealJamAtOnce();
				}
			}
			//-----------------------------------------------------------------------
//			if(g_maxMpFromPs1ToEnterance > 0)
//			{
//				g_maxMpFromPs1ToEnterance --;
//				if(g_maxMpFromPs1ToEnterance == 0)
//				{
//					if(gb_haveNoteInEntergate == 1)
//					{
//						noteState |= STATE_BACKWARD_COVER_ENTERANCE;
//						initEteranceSensor();
//					}
//					gb_needStopMotor = 1;
//					//开盖或堵币 切到堵币状态 堵币状态下扫描全部红外无遮挡 就恢复normal
//				}
//			}	
			if(g_maxMpFromPs2ToLeave > 0)
			{
				g_maxMpFromPs2ToLeave --;
				if(g_maxMpFromPs2ToLeave == 0)
				{
					gb_needStopMotor = 1;					
				}
			}
			if(g_maxMpFromComputeToPS1 > 0)
			{
				g_maxMpFromComputeToPS1 --;
				if(g_maxMpFromComputeToPS1 == 0)
				{
					noteState &= (~STATE_BACKWARD_NOTE_LEAVE);
					//gb_needStopMotor = 1;	
					gb_isJammed = JAM_LENGTH_TO_ENTERANCE;	
					DealJamAtOnce();		
				}
			}		
			
		//	DealInMp();
			
//			if((savedPara.machineWorkPara.d[INDEX_JAM_TYPE]&IR_COVER_TIME_JAM_CHECK) > 0)
//			{
//				if(gb_isJammed == 0)
//				{			
//					if(irHaveNoteContinuslyCnt > IR_COVER_JAM_NUM)
//					{
//						gb_isJammed = JAM_PS2_IR;	
//						DealJamAtOnce();
//						irHaveNoteContinuslyCnt = 0;						
//					}
//				}
//			}
		}
	}
}

void InitCountIr(void)
{
// 	currentCountNum = -1;
// 	countIrNum = 0;
// 	ir2IrNum = 0;
// 	ir3IrNum = 0;		
// 	gb_irCovered = 0;				
// 	lowCountNum = 0;
// 	gb_needSampleMr = 0;
}

void ADC1_2_IRQHandler(void)
{
	//if(ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET)
	if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
	{
		//设置标志
		//ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	}
}

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
