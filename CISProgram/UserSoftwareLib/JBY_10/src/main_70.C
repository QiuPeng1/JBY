/***************************************************************************


****************************************************************************/
#include "main.h"
#include "menu.h"

u8 readKey(void)
{
	if(!readkey0())
	{
		return KEY_CUR;
	}
	if(!readkey1())
	{
		return KEY_FUN;
	}
	if(!readkey2())
	{
		return KEY_RESTART;
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
		switch(systemState)
		{
			case NORMAL:
				DealKeyDownOnNormal(key);
				break;
		}
		//disp_num(key,0,0);
//		LCD_DispNum(0,0,WHITE,BLACK,key,24);
	}
}

void DealKeyDownOnNormal(u8 key)
{
	u8 i,k;
	u8 tmpBuf[10];
	u16 temp;
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
			case LONG_KEY_RESTART:
					SetSystemState(NORMAL);
					gb_enableSample = 1;
					noteState = 0;
					ClearAllNoteNum();
					DispMainMenu();			
				break;
		}
	}
}

u8 motorTest = 0;


int main(void)
{
	u8 buffer[10];
	u8 d;
	u16 j,k;
	u32 sum;
	
	delay_DelayMs(1000);
	/*端口配置及
	初始化*/
	MainInit();
	

	#ifdef USE_IWDG
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);		
	IWDG_SetPrescaler(IWDG_Prescaler_32);		
	IWDG_SetReload(40);	
	IWDG_ReloadCounter();		
	IWDG_Enable();
	#endif
	
	disp_clearScreen(WHITE);
	disp_setPenColor(RED);
	disp_setBackColor(WHITE);
	disp_setFont(24);
	disp_string("WELCOME",SCREEN_WIDTH/2-12*3,SCREEN_HEIGHT/2-12);
	delay_DelayMs(500);
	
	UpdateDataFromSavedData();
	SystemSelfcheck();
	
	entergatePulseNumCounter = 0 ;
	gb_haveNoteInEntergate = 0;
	
	computeAdjustData();
	memcpy(lengthIdleOriginValue,savedPara.adjustPara.irIdleStandard,REAL_IR_NUM);
	
	hwfs_On();
	//jckfs_On();
	SetSystemState(NORMAL);
	gb_enableSample = 1;
	g_subStateOfNormal = NORMAL_DIAN_CHAO; 
	ClearAllNoteNum();
	DispMainMenu();
	LongBeep(1);
	//gb_enableSample = 1;
	//
	
	while (1)
	{
		//喂狗
		#ifdef USE_IWDG
		IWDG_ReloadCounter();
		#endif
		
		if(gb_oneSec == 1)
		{
			gb_oneSec = 0;
// 			if(gb_haveNoteInEntergate > 0)
// 			{
// 				LongBeep(1);
// 			}
// 			if(gb_ledIsOn == 1)
// 			{
// 				LED_OFF();
// 				
// 			}
// 			else
// 			{
// 				LED_ON();			
// 			}		
// 				if(g_colorFsRGB == FS_BLUE)
// 				{
// 					redFs_On();
// 					greenFs_Off();
// 					blueFs_Off();
// 				}
// 				else if(g_colorFsRGB == FS_RED)
// 				{
// 					redFs_Off();
// 					greenFs_On();
// 					blueFs_Off();
// 				}
// 				else
// 				{
// 					redFs_Off();
// 					greenFs_Off();
// 					blueFs_On();
// 				}
// 			motorTest ++;
// 			if(motorTest == 5)
// 			{
// 				motor1_ForwardRun();
// 			}
// 			else if(motorTest == 10)
// 			{
// 				motor1_BackwardRun();
// 			}
// 			else if(motorTest == 15)
// 			{
// 				motor1_Stop();
// 				motorTest = 0;
// 			}
		}
		
		if(gb_sampleIdleOver == 1)//输出空转采集
		{
			gb_sampleIdleOver = 0;
			mgDataLen = g_mgSampleIndex;
//			irDataLenA = g_irSampleIndex;
//			memcpy(mgDataA,mgData,6*MG_DATA_MAX_LEN);
//			memcpy(irDataA,irData,8*IR_DATA_MAX_LEN);
//			OutputMgColorDetailData();
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
					SetSystemState(NORMAL);
					gb_enableSample = 1;
					noteState = 0;
					ClearAllNoteNum();
					DispMainMenu();
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
		}
		
		DealScanEnteracneSensor();
		ScanKeyDown();
		DispAutoRefreshMenu();
		
		DealNotePass();
		
		DealPackageFromUart1();
		
	//	ScanKeyDown();
		
		DealKeyDown();

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
					fifo_DataIn(KB_FIFO,shortLcdKey);	
					LongBeep(1);					
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

						fifo_DataIn(KB_FIFO,longLcdKey+LONG_LCD_KEY_ADDVAL);		
						LongBeep(1);	
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


void DealPackageFromUart1(void)
{
	u8 cmd;
	u8 i;
	//处理usart1的数据包
	if(gb_needDealUart1Data == 1)
	{
		if (uart1infifo_count == 0)
		{
			gb_needDealUart1Data = 0;
		}
		else
		{	
			cmd = uart1infifo_DataOut();//命令
			if(gb_uartWorkMode == DEBUG_MODE)
			{
				switch (cmd)
				{
					case 0x42://磁性数据 手
						gb_autoOutputDetailData = 0;
						break;
					case 0x62://磁性数据 自
						gb_autoOutputDetailData = 1;
						break;
					case 'a'://输出数据 //磁性 获取当前纸币
						//OutputMgIrDetailData();
						//OutputLengthDetailData();
						OutputALLDetailData();
						break;
	// 				case 
	// 				OutputMgColorDetailData();
	// 					break;
					case 0x65://磁性界面下按轮子空转	
						//hwfs_On();
						//motor1_Run();
						//delay_DelayMs(100);
						gb_sampleIdleOver = 0;
						g_mgSampleIndex = 0;
						g_uvSampleIndex = 0;
						g_lengthSampleIndex = 0;
						needSampleIdleNum = 1000;
						//delay_DelayMs(2000);
						//motor1_Stop();
						//hwfs_Off();			
						break;
					case 0x48://厚度下 手
						break;
					case 0x68://厚度下 自
						break;
					case 'g'://厚度下 获取当前纸币
						OutputMgColorDetailData();
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
							hwfs_On();
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
						gb_noteBackLeave = 1;
						break;
					case 0xaa:
						gb_noteBackLeave = 0;
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
						DispString("开始厚白纸校正,放入80g厚白纸",1);
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
	// 					case 0x67:
	// 						OutputIrDetailData();
	// 						break;
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
	if(systemState == NORMAL)
	{
		if(gb_haveNoteInEntergate == 1)
		{
			if((noteState == 0)&&(g_motor1State == MOTOR_STOP))//空闲态
			{
				motor1_ForwardRun();
				noteState |= STATE_FORWARD_COVER_ENTERANCE;
				g_maxMpFromEnteranceToLength = MP_FROM_ENTERANCE_TO_LENGTH;
				uvfs_On();
				gb_uvNeedStartSampleCnt = 20;
				tempMgDataLen = 0;
			}
		}
		else
		{
			if((noteState&STATE_BACKWARD_COVER_ENTERANCE) > 0)
			{
				noteState &= (~STATE_BACKWARD_COVER_ENTERANCE);
			}
		}
	}
/*	
	{
	//如果手动模式，就检测有无按下复位键
	//if (savedPara.userWorkPara.d[INDEX_MANUAL_IS_ON] > 0)
	if (savedPara.userWorkPara.d[INDEX_MANUAL_IS_ON] > 0)
	{
		if ((gb_keyFuWeiDown == 0) && (gb_runInManual == 0))//没按复位键 且不是在运转中 就退出
		{
			return;
		}
		gb_keyFuWeiDown = 0;
	}

AUTO_FEED:		
	if(gb_haveNoteInEntergate == 1)
	{
		//if ((g_needStopWork > 0) || (g_needPreStopWork > 0)||g_waittingSnrPkg > 0||gb_isJammed > 0||gb_autoGetImg > 0)	//如果有错误不能启动电机，就不启动
		if(gb_isJammed > 0)
		{
			goto DEAL_NO_NOTE_IN_ENTERGATE;
		}

		if(gb_needStopCsddj != 1)
		{
			if(g_motor1State == MOTOR_STOP)
			{
				gb_runInManual = 1;
				g_turnOffHwfsDelayTimer = 0;
				hwfs_On();
				delay_DelayMs(500);
				motor1_ForwardRun();
				gb_enableSample = 1;
				//delay_DelayMs(500);
				InitNoteNum();
				DispNoteNumValSum();
//				gb_zouChaoInfoIsChanged = 1;

				g_haveNoNoteCounter = HAVE_NO_NOTE_MAX_COUNTER_START;
			}
		}
	}
	else
	{
DEAL_NO_NOTE_IN_ENTERGATE:
			if(g_haveNoNoteCounter == 0)
			{				
				if(g_motor1State == MOTOR_RUN)
				{
					//CIS停止工作
					//小板停止工作
					motor1_Stop();
					gb_runInManual = 0;
					g_turnOffHwfsDelayTimer = HWFS_OFF_DELAY;		
					if(outputDeatalDataCnt > 0)
					{
						outputDeatalDataCnt --;
						OutputMgIrDetailData();
					}
				}
			}			
		}
	}*/
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
	u8 i;
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
	u16 i,j;
	u16 x,y;
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

void DispMainMenuBackground(void)
{
	u8 i;
	DispClassicBar(TOP_BAR_COLOR,0);
	DispClassicBar(MID_BAR_COLOR,1);
	DispClassicBar(BOTTOM_BAR_COLOR,2);
	disp_drawRectangle(0,TOP_BAR_Y+TOP_BAR_H,SCREEN_WIDTH,BAR_LINE_H,BAR_LINE_COLOR);
	disp_drawRectangle(0,BOTTOM_BAR_Y-BAR_LINE_H,SCREEN_WIDTH,BAR_LINE_H,BAR_LINE_COLOR);
	
	//detailNote
	disp_DrawChart(DETAIL_NOTE_CHART_X,DETAIL_NOTE_CHART_Y,DETAIL_NOTE_CHART_ONE_COL_W*DETAIL_NOTE_CHART_COL_NUM,DETAIL_NOTE_CHART_ONE_ROW_H*DETAIL_NOTE_CHART_ROW_NUM+8,DETAIL_NOTE_CHART_COL_NUM,DETAIL_NOTE_CHART_ROW_NUM,BLACK);
//		DETAIL_NOTE_CHART_X = 8,
//	DETAIL_NOTE_CHART_Y = 34+6,
//	DETAIL_NOTE_CHART_FONT = FONT_16,
//	DETAIL_NOTE_CHART_H = 16,
//	DETAIL_NOTE_CHART_ONE_ROW_H = 20,
//	DETAIL_NOTE_CHART_ONE_COL_W = 8*5,
//	DETAIL_NOTE_CHART_ROW_NUM = 8,
//	DETAIL_NOTE_CHART_COL_NUM = 3,
	//显示面额
	
	disp_setFont(DETAIL_NOTE_CHART_FONT);
	disp_setPenColor(BLACK);
	disp_setBackColor(MID_BAR_COLOR);
	for(i = 0;i < 7;i++)
	{
		U32ToStr(USD_NOTE_VALUE[i],dispStr,4);
		disp_string(dispStr,DETAIL_NOTE_CHART_X+DETAIL_NOTE_CHART_ONE_COL_W*0+1,DETAIL_NOTE_CHART_Y+DETAIL_NOTE_CHART_ONE_ROW_H*i+2);
	}
	disp_string(" SUM ",DETAIL_NOTE_CHART_X+DETAIL_NOTE_CHART_ONE_COL_W*0+1,DETAIL_NOTE_CHART_Y+DETAIL_NOTE_CHART_ONE_ROW_H*i+2);

	disp_setFont(NOTESUM_FONT);
	disp_setPenColor(BLACK);
 	disp_setBackColor(MID_BAR_COLOR);
	disp_string(" SUM:",NOTESUM_TITLE_X,NOTESUM_Y);
	disp_string(" PCS:",NOTENUM_TITLE_X,NOTENUM_Y);
	disp_string("DENO:",DENO_NUM_TITLE_X,DENO_NUM_Y);
}

void DispMainMenu(void)
{
	DispMainMenuBackground();
	//disp_clearScreen(WHITE);
	DispCurrency();
	
	
	//LCD_DispString(0,100,WHITE,RED,16,"WELCOME");
/*	if(gb_batchIsOn > 0)
	{
		tm16xx_Led1Disp(g_yuZhiNum);
		delay_DelayMs(100);
	}*/
	DispNoteNumValSum();
}

void DispCurrency(void)
{
	u8 r;
	
	disp_setBackColor(TOP_BAR_ICON_BACK_COLOR);
	disp_drawRectangle(CURRENCY_ICON_X,CURRENCY_ICON_Y,CURRENCY_ICON_W,CURRENCY_ICON_H,TOP_BAR_ICON_BACK_COLOR);	
	disp_setPenColor(TOP_BAR_ICON_PEN_COLOR);		
	if(g_languageIndex == INDEX_ENGLISH)
	{
		disp_setFont(CURRENCY_FONT);
		r = GetCertainStrFromLongStr(CURRENCY_TITLE_STR_ENGLISH,g_currency,dispStr);
		disp_string(dispStr,CURRENCY_X,CURRENCY_Y);			
	}
	else
	{
		disp_setFont(CURRENCY_CHINESE_FONT);
		r = GetCertainStrFromLongStr(CURRENCY_TITLE_STR_CHINESE,g_currency,dispStr);
		disp_string(dispStr,CURRENCY_CHINESE_X,CURRENCY_CHINESE_Y);				
	}
}

void DispAutoRefreshMenu(void)//1秒钟显示一些需要自动刷新的界面
{
	u8 oneMin;
	u16 u16Tmp;
	oneMin = 0;
	if(gb_oneSecAutoRefresh == 1)
	{
		gb_oneSecAutoRefresh = 0;
		
		switch(systemState)
		{
			case NORMAL:
				break;
			case SENSOR_VIEW:
				if(g_colorFsRGB == FS_BLUE)
				{
					redFs_On();
					greenFs_Off();
					blueFs_Off();
				}
				else if(g_colorFsRGB == FS_RED)
				{
					redFs_Off();
					greenFs_On();
					blueFs_Off();
				}
				else
				{
					redFs_Off();
					greenFs_Off();
					blueFs_On();
				}
				SampleOneRow();
				DispSensorViewMenu();
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
			
			//切换到40g白纸校正
			gb_inCollabration = COLLABRATION_40G_BZ;
			collabrationNoteNum = 0;
			memset(collabrationSum,0,REAL_IR_NUM*4);
			memset(collabrationNum,0,REAL_IR_NUM);
			memset(collabrationMax,0,REAL_IR_NUM*2);
			memset(collabrationMin,0xff,REAL_IR_NUM*2);
			DispString("开始薄白纸校正,放入40g薄白纸",1);				
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
		}		
	}
	
}
void DealNoteType(void)
{
	switch(billValue)
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
		case 16:
		case 17:
			currentNoteType = 5;
			break;	
		case 18:
			currentNoteType = 6;
			break;
		default:
			currentNoteType = 7;
			break;
		
	}
}
void DealNotePass(void)
{
	u8 r;
	if(gb_oneNotePass == 1)
	{
		gb_oneNotePass = 0;
		if(systemState == NORMAL)
		{
			motor1_Stop();//停转
			if(gb_inCollabration == COLLABRATION_COLOR)
			{
				color_whiteStandard();
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
				billIrad_Judge(IRlengthBuffer);
				//billRGB_Judge();
				//colorJudgeValue //颜色面额
				//colorJudgeFlag  //颜色方向
				//billValue       //红外面额
				//billFlag		  //红外方向
				disp_setFont(FONT_16);
				//disp_num(colorJudgeValue,160,BOTTOM_BAR_Y-18);
				//disp_num(colorJudgeFlag,190,BOTTOM_BAR_Y-18);
				//disp_num(billValue,220,BOTTOM_BAR_Y-18);			
				//disp_num(billFlag,250,BOTTOM_BAR_Y-18);
				
				
				U32ToStr(billValue,dispStr,3);
				disp_string(dispStr,220,BOTTOM_BAR_Y-18);	
				U32ToStr(billFlag,dispStr,3);
				disp_string(dispStr,250,BOTTOM_BAR_Y-18);					
				
				//currentNoteType = 0;//转换到美元的面额 范围 0 - 6
				DealNoteType();
				//真币
				if(currentNoteType < 7)
				{		
					IncNoteNum();
					LongBeep(1);
					DispNoteNumValSum();
				}
				else
				{
					//假币
					LongBeep(3);
					disp_setFont(DENO_NUM_STR_FONT); 
					disp_setPenColor(RED);  	
					disp_setBackColor(MID_BAR_COLOR);
					disp_string(" SUSP",DENO_NUM_X,DENO_NUM_Y);		
				}

				
				if(gb_autoOutputDetailData == 1)
				{
//					OutputLengthDetailData();
					OutputALLDetailData();
				}
			}
			//计算结束
			noteState &= (~STATE_COMPUTE);
			//根据计算结果来决定钱去前面还是回转  
			if(gb_noteBackLeave == 0)
			{
				noteState |= STATE_FORWARD_NOTE_LEAVE;
				motor1_ForwardRun();//向前转
				g_maxMpFromLengthToLeave = MP_FROM_LENGTH_TO_LEAVE;
			}
			else
			{
				noteState |= STATE_BACKWARD_NOTE_LEAVE;
				motor1_BackwardRun();//向后转
				g_maxMpFromComputeToLength = MP_FROM_COMPUTE_TO_LENGTH;			
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
	uart_SendDataToUart1(str,len);
	if(enter > 0)
	{
		buf[0] = 0x0d;
		buf[1] = 0x0a;
		uart_SendDataToUart1(buf,2);
	}
}

//输出到串口
void DispSensorViewMenu(void)
{
	u8 i,j,k;
	u8 u8Temp;
	
// 	i = 0;
// 	memcpy(dispStr+i,"位置1:",6);
// 	i += 6;
// 	u8Temp = ps1_HaveNote();
// 	U8ToStr(u8Temp,dispStr+i);
// 	i += 3;
// 	dispStr[i++] = ' ';
// 	dispStr[i++] = '\0';
// 	DispString(dispStr,0);
// 	
// 	i = 0;
// 	memcpy(dispStr+i,"位置2:",6);
// 	i += 6;
// 	u8Temp = ps2_HaveNote();
// 	U8ToStr(u8Temp,dispStr+i);
// 	i += 3;
// 	dispStr[i++] = ' ';
// 	dispStr[i++] = '\0';
// 	DispString(dispStr,0);	
// 	
// 	i = 0;
// 	memcpy(dispStr+i,"位置3:",6);
// 	i += 6;
// 	u8Temp = ps3_HaveNote();
// 	U8ToStr(u8Temp,dispStr+i);
// 	i += 3;
// 	dispStr[i++] = ' ';
// 	dispStr[i++] = '\0';
// 	DispString(dispStr,0);
// 	
// 	i = 0;
// 	memcpy(dispStr+i,"位置4:",6);
// 	i += 6;
// 	u8Temp = ps4_HaveNote();
// 	U8ToStr(u8Temp,dispStr+i);
// 	i += 3;
// 	dispStr[i++] = ' ';
// 	dispStr[i++] = '\0';
// 	DispString(dispStr,0);
// 	
// 	i = 0;
// 	memcpy(dispStr+i,"位置5:",6);
// 	i += 6;
// 	u8Temp = psValue[0];
// 	U8ToStr(u8Temp,dispStr+i);
// 	i += 3;
// 	dispStr[i++] = ' ';
// 	dispStr[i++] = '\0';
// 	DispString(dispStr,0);
// 	
// 	i = 0;
// 	memcpy(dispStr+i,"位置6:",6);
// 	i += 6;
// 	u8Temp = psValue[1];
// 	U8ToStr(u8Temp,dispStr+i);
// 	i += 3;
// 	dispStr[i++] = ' ';
// 	dispStr[i++] = '\0';
// 	DispString(dispStr,0);
// 	
// 	i = 0;
// 	memcpy(dispStr+i,"位置7:",6);
// 	i += 6;
// 	u8Temp = ps7_HaveNote();
// 	U8ToStr(u8Temp,dispStr+i);
// 	i += 3;
// 	dispStr[i++] = ' ';
// 	dispStr[i++] = '\0';
// 	DispString(dispStr,0);

// 	i = 0;
// 	memcpy(dispStr+i,"位置8:",6);
// 	i += 6;
// 	u8Temp = ps8_HaveNote();
// 	U8ToStr(u8Temp,dispStr+i);
// 	i += 3;
// 	dispStr[i++] = ' ';
// 	dispStr[i++] = '\0';
// 	DispString(dispStr,1);

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
	
	//PS1 PS2
	i = 0;
	memcpy(dispStr+i,"PS:",3);
	i += 3;
	u8Temp = ps1_HaveNote();
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);
	
	i = 0;
	u8Temp = ps2_HaveNote();
	U8ToStr(u8Temp,dispStr+i);
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
	
	u8Temp = readkey1();
	U8ToStr(u8Temp,dispStr+i);
	i += 3;
	dispStr[i++] = ' ';
	dispStr[i++] = '\0';
	DispString(dispStr,0);
	
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
	noteDenoValue = USD_NOTE_VALUE[currentNoteType];
	noteSum += noteDenoValue;
	denoNoteNum[currentNoteType] ++;
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
		DispNoteDenoValue();//显示币值
		DispDetailNoteNum();//显示明细
	}
}


void DispNoteNum(void)//显示张数
{
	disp_setFont(NOTENUM_FONT);
	disp_setPenColor(BLACK);
 	disp_setBackColor(MID_BAR_COLOR);
	U32ToStr(noteNum,dispStr,DOWN_NOTE_NUM_BITS);
	disp_string(dispStr,NOTENUM_X,NOTENUM_Y);
}

void DispNoteSum(void)//显示金额
{
	disp_setFont(NOTESUM_FONT);
	disp_setPenColor(BLACK);
 	disp_setBackColor(MID_BAR_COLOR);
	U32ToStr(noteSum,dispStr,DOWN_NOTE_SUM_BITS);
	disp_string(dispStr,NOTESUM_X,NOTESUM_Y);
}

void DispNoteDenoValue(void)//显示币值
{
	disp_setFont(DENO_NUM_STR_FONT); 
	disp_setPenColor(BLACK);  	
	disp_setBackColor(MID_BAR_COLOR);
	U16ToStr(noteDenoValue,dispStr,5);
	dispStr[0] = '$';
 	disp_string(dispStr,DENO_NUM_X,DENO_NUM_Y);
}
void DispDetailNoteNum(void)//显示明细
{
	u8 i;
	u32 denoSum;
	
	disp_setFont(DETAIL_NOTE_CHART_FONT);
	disp_setPenColor(BLACK);
	disp_setBackColor(MID_BAR_COLOR);
	for(i = 0;i < 7;i++)
	{
		U32ToStr(denoNoteNum[i],dispStr,4);
		disp_string(dispStr,DETAIL_NOTE_CHART_X+DETAIL_NOTE_CHART_ONE_COL_W*1+1,DETAIL_NOTE_CHART_Y+DETAIL_NOTE_CHART_ONE_ROW_H*i+2);
		denoSum = denoNoteNum[i]*USD_NOTE_VALUE[i];
		U32ToStr(denoSum,dispStr,5);
		disp_string(dispStr,DETAIL_NOTE_CHART_X+DETAIL_NOTE_CHART_ONE_COL_W*2+1,DETAIL_NOTE_CHART_Y+DETAIL_NOTE_CHART_ONE_ROW_H*i+2);
	}
	U32ToStr(noteNum,dispStr,4);
	disp_string(dispStr,DETAIL_NOTE_CHART_X+DETAIL_NOTE_CHART_ONE_COL_W*1+1,DETAIL_NOTE_CHART_Y+DETAIL_NOTE_CHART_ONE_ROW_H*i+2);
	U32ToStr(noteSum,dispStr,5);
	disp_string(dispStr,DETAIL_NOTE_CHART_X+DETAIL_NOTE_CHART_ONE_COL_W*2+1,DETAIL_NOTE_CHART_Y+DETAIL_NOTE_CHART_ONE_ROW_H*i+2);

}
		

void LongBeep(u8 times)
{
//	if(savedPara.userWorkPara.d[INDEX_BEEP_ON] == 1)
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
	u8 key;
	dispStr[0] = ' ';
	dispStr[1] = 'E';
	U16ToTimeStr(code,dispStr+2,2);
// 	tm16xx_Led2DispStr(dispStr);
//	fifo_Clear(KB_FIFO);
// 	while(1)
// 	{
// 		ScanKeyDown();
// 		if(fifo_GetCount(KB_FIFO) > 0)
// 		{
// 			key = fifo_DataOut(KB_FIFO);	
// 			if(key == KEY_START2||key == KEY_START)
// 			{
// 				fifo_Clear(KB_FIFO);
// 				break;
// 			}
// 		}
// 		delay_DelayMs(15);
// 		gb_needCheckKey = 1;
// 	}
}
void SystemSelfcheck(void)
{
// 	u16 k;
// 	u16 i;
// 	//自检 
// 	SetSystemState(SELFCHECK);
// 	//进钞
// //	jckfs_On();
// 	delay_DelayMs(10);
// 	SampleOneRow();
// 	if(enteranceSensorVal > savedPara.machineWorkPara.d[INDEX_RMB_ENTERANCE_COVER_THRES])
// 	{
// 		dispSelfcheckError(ERROR_FEED_SENSOR);
// 	}
// //	jckfs_Off();
// 	
// 	//红外关 值为低
// 	hwfs_Off();
// 	SampleOneRow();
// 	if(irValue[0] >= irHaveNoteThres)
// 	{
// 		dispSelfcheckError(ERROR_IR1_OFF);
// 	}
// 	if(irValue[1] >= irHaveNoteThres)
// 	{
// 		dispSelfcheckError(ERROR_IR2_OFF);
// 	}
// 	if(irValue[2] >= irHaveNoteThres)
// 	{
// 		dispSelfcheckError(ERROR_IR3_OFF);
// 	}
// 	if(irValue[3] >= irHaveNoteThres)
// 	{
// 		dispSelfcheckError(ERROR_IR4_OFF);
// 	}
// 	//红外开 
// 	hwfs_On();
// 	SampleOneRow();
// 	if(irValue[0] < irHaveNoteThres)
// 	{
// 		dispSelfcheckError(ERROR_IR1_ON);
// 	}
// 	if(irValue[1] < irHaveNoteThres)
// 	{
// 		dispSelfcheckError(ERROR_IR2_ON);
// 	}
// 	if(irValue[2] < irHaveNoteThres)
// 	{
// 		dispSelfcheckError(ERROR_IR3_ON);
// 	}
// 	if(irValue[3] < irHaveNoteThres)
// 	{
// 		dispSelfcheckError(ERROR_IR4_ON);
// 	}	
// 	
// 	//转电机 	
// 	//磁性空转采集

 	hwfs_On();
 	motor1_ForwardRun();
 	delay_DelayMs(100);
 	g_mgSampleIndex = 0;
 	g_lengthSampleIndex = 0;
 	//needSampleIdleNum = 500;
 	delay_DelayMs(1000);
	motor1_BackwardRun();
	delay_DelayMs(1000);
		motor1_Stop();
 	hwfs_Off();
// 	if(gb_isJammed == JAM_CSDDJ)
// 	{
// 		dispSelfcheckError(ERROR_MOTOR_OR_MP);//码盘 电机
// 		gb_isJammed = 0;
// 	}
// 	else if(gb_isJammed == JAM_PS2_IR)
// 	{
// 		dispSelfcheckError(ERROR_IR_JAM);//红外长时间覆盖
// 		gb_isJammed = 0;
// 	}
// 	//磁性波形检查
// 	k = 0;
// 	for(i = 0;i < g_mgSampleIndex;i++)
// 	{
// 		if(mgData[0][i] > savedPara.machineWorkPara.d[INDEX_SELCHECK_MT_THRES])
// 		{
// 			k ++;
// 		}
// 	}
// 	if(k > 5)
// 	{
// 		dispSelfcheckError(ERROR_MT);
// 	}
// 	k = 0;
// 	for(i = 0;i < g_mgSampleIndex;i++)
// 	{
// 		if(mgData[1][i] > savedPara.machineWorkPara.d[INDEX_SELCHECK_MR_THRES])
// 		{
// 			k ++;
// 		}
// 	}
// 	if(k > 5)
// 	{
// 		dispSelfcheckError(ERROR_LEFT_MR);
// 	}
// 	k = 0;
// 	for(i = 0;i < g_mgSampleIndex;i++)
// 	{
// 		if(mgData[2][i] > savedPara.machineWorkPara.d[INDEX_SELCHECK_MR_THRES])
// 		{
// 			k ++;
// 		}
// 	}
// 	if(k > 5)
// 	{
// 		dispSelfcheckError(ERROR_RIGHT_MR);
// 	}
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
	u8 i;

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

void DealJamAtOnce(void)
{
	if(systemState != SELFCHECK)//自检中堵币不显示 由自检统一显示
	{
		//显示 JAM 及刹车原因
		memcpy(dispStr," E",2);
		U16ToStr(gb_isJammed+ERROR_JAM1-1,dispStr+2,2);
// 		tm16xx_Led2DispStr(dispStr);
		SetSystemState(DU_BI);
	}
	hwfs_On();
	motor1_Stop();
	LongBeep(3);
	//gb_dispJamInfo = 1;
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
}

/*
	rmb50AqxCodeThres[0] = 50;//50块安全线的阈值
	rmb50AqxCodeThres[1] = 60;
	rmb20_10AqxCodeThres[0] = 10;//10、20块安全线的阈值
	rmb20_10AqxCodeThres[1] = 25;

	rmb50ScaleThres[0] = 64;
	rmb50ScaleThres[1] = 74;

	rmb20ScaleThres[0][0] = 29;
	rmb20ScaleThres[0][1] = 41;
	rmb20ScaleThres[1][0] = 25;
	rmb20ScaleThres[1][1] = 35;

	rmb10ScaleThres[0][0] = 42;
	rmb10ScaleThres[0][1] = 50;
	rmb10ScaleThres[1][0] = 45;
	rmb10ScaleThres[1][1] = 57;

	rmb100AqxCodeThres[0] = 48;
	rmb100AqxCodeThres[1] = 58;

	rmb100ScaleThres[0] = 90;
	rmb100ScaleThres[1] = 115;
*/
void InitMachineWorkPara(void)
{
	savedPara.machineWorkPara.d[INDEX_JAM_TYPE] = CSDDJ_JAM_CHECK|IR_COVER_TIME_JAM_CHECK;
	
	savedPara.machineWorkPara.d[INDEX_RMB_WIDTHTHRES1] = 70;//68 100元
	savedPara.machineWorkPara.d[INDEX_RMB_WIDTHTHRES2] = 65;//63 50 20 10  
	savedPara.machineWorkPara.d[INDEX_RMB_WIDTHTHRES3] = 60;//58
	savedPara.machineWorkPara.d[INDEX_RMB_WIDTHTHRES4] = 55;

	savedPara.machineWorkPara.d[INDEX_RMB_AQX_CODE_NUM_THRES] = 10;
	savedPara.machineWorkPara.d[INDEX_RMB_AQX_WAVE_THRES] = 150;
	savedPara.machineWorkPara.d[INDEX_RMB_AQX_WAVE_COMBINE_THRES] = 10;
	savedPara.machineWorkPara.d[INDEX_RMB_IR_NOTE_COVER_THRES] = 150;
	
	savedPara.machineWorkPara.d[INDEX_RMB_ENTERANCE_COVER_THRES] = 100;

	savedPara.machineWorkPara.d[INDEX_RMB100_05_AQX_THRES_MIN] = 55;
	savedPara.machineWorkPara.d[INDEX_RMB100_05_AQX_THRES_MAX] = 65;
	savedPara.machineWorkPara.d[INDEX_RMB100_05_AQX_SCALE_MIN] = 90;
	savedPara.machineWorkPara.d[INDEX_RMB100_05_AQX_SCALE_MAX] = 115;
	savedPara.machineWorkPara.d[INDEX_RMB50_AQX_THRES_MIN] = 60;
	savedPara.machineWorkPara.d[INDEX_RMB50_AQX_THRES_MAX] = 70;
	savedPara.machineWorkPara.d[INDEX_RMB50_AQX_SCALE_MIN] = 60;
	savedPara.machineWorkPara.d[INDEX_RMB50_AQX_SCALE_MAX] = 80;
	savedPara.machineWorkPara.d[INDEX_RMB20_10_AQX_THRES_MIN] = 12;
	savedPara.machineWorkPara.d[INDEX_RMB20_10_AQX_THRES_MAX] = 23;
	savedPara.machineWorkPara.d[INDEX_RMB20_AQX_SCALE1_MIN] = 29;
	savedPara.machineWorkPara.d[INDEX_RMB20_AQX_SCALE1_MAX] = 46;
	savedPara.machineWorkPara.d[INDEX_RMB20_AQX_SCALE2_MIN] = 22;
	savedPara.machineWorkPara.d[INDEX_RMB20_AQX_SCALE2_MAX] = 36;
	savedPara.machineWorkPara.d[INDEX_RMB10_AQX_SCALE1_MIN] = 39;
	savedPara.machineWorkPara.d[INDEX_RMB10_AQX_SCALE1_MAX] = 52;
	savedPara.machineWorkPara.d[INDEX_RMB10_AQX_SCALE2_MIN] = 43;
	savedPara.machineWorkPara.d[INDEX_RMB10_AQX_SCALE2_MAX] = 60;
	
	savedPara.machineWorkPara.d[INDEX_SELCHECK_MT_THRES] = 145;
	savedPara.machineWorkPara.d[INDEX_SELCHECK_MR_THRES] = 130;
	
	 savedPara.machineWorkPara.d[INDEX_RMB_UV_THRES] = 120;
//	savedPara.machineWorkPara.d[INDEX_FEED_MOTOR_AUTO_CONTROL_CHAINNOTE] = 0;
	
// 	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH1] = 0xE0;
// 	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH2] = 0;
// 	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH3] = 0;
// 	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH4] = 0;
// 	savedPara.machineWorkPara.d[INDEX_OPEN_CURRENCY_SWITCH5] = 0;
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
	u16  g;

	if (x < 10)
	{
		return (WIDTH_BETWEEN_IR2_IR3);
	}
	
	g = WIDTH_BETWEEN_IR2_IR3;

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


void MainInit(void)
{
	u8 i;

	NVIC_InitTypeDef NVIC_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
//	ADC_InitTypeDef ADC_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;


	//时钟
	SystemInit();
	#ifdef BOOT_APP
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000); 
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

	//main.c及中断的管脚初始化
	InitGpioInMain();
	
// 	tm16xx_Init();
// 	tm16xx_SetInsturctLed(gb_mgIsOn,gb_uvIsOn,gb_batchIsOn,gb_addIsOn);
//	tm16xx_DisableDP();
// 	tm16xx_Led1DispStr("L88");
//	tm16xx_Led2Disp(VERSION);
	//adc_init();
	
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	adc_init();

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
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	InitDMA();
	//配置DMA中断
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);        //DMA通道1传输完成中断

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
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
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_7Cycles5);//填充
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_7Cycles5);//MG-RGB
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_7Cycles5);//IR8-14

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

	ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 1, ADC_SampleTime_7Cycles5);//IR1-7
	ADC_RegularChannelConfig(ADC2, ADC_Channel_13, 2, ADC_SampleTime_7Cycles5);//IR15-21
	ADC_RegularChannelConfig(ADC2, ADC_Channel_15, 3, ADC_SampleTime_7Cycles5);//HOPPER
	
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
	u8 i,j,k;
	u8 index;
	u8 colorBg;
	
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
	PC0		填充									adData[0]
	MG-RGB	PA4	ADC4	4051六选1 adData[2]
	IR8-14	PC2	ADC12	4051七选1 adData[4]

	ADC2 
	IR1-7	PC1	ADC11	4051七选1		adData[1]
	IR15-21	PC3	ADC13	4051七选1	adData[3]
	HOPPER	PC5	ADC15	不选			adData[5]
	*/
	
// 	irValue[0] = adData[0];
// 	irValue[1] = adData[1];
// 	irValue[2] = adData[2];
// 	irValue[3] = adData[3];
// 	irValue[4] = adData[4];
// 	irValue[5] = adData[5];
// 	
// 	mrValue[0] = adData[10];//MT
// 	mrValue[1] = adData[6];
// 	mrValue[2] = adData[7];
// 	mrValue[3] = adData[8];
// 	mrValue[4] = adData[9];
// 	uvValue[0] = adData[11];
// 	psValue[0] = adData[12];//PS5
// 	psValue[1] = adData[13];//PS6
// 	//enteranceSensorVal = adData[8];
		enteranceSensorVal = adData[5];
		switch(chanelIndexOf4051)
		{
			case 0:
				irValue[0] = adData[1];
				irValue[7] = adData[4];
				irValue[14] = adData[3];
				mrValue[0] = adData[2];
				break;
			case 1:
				irValue[1] = adData[1];
				irValue[8] = adData[4];
				irValue[15] = adData[3];
				mrValue[1] = adData[2];
				break;
			case 2:
				irValue[2] = adData[1];
				irValue[9] = adData[4];
				irValue[16] = adData[3];
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
				irValue[3] = adData[1];
				irValue[10] = adData[4];
				irValue[17] = adData[3];
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
				irValue[4] = adData[1];
				irValue[11] = adData[4];
				irValue[18] = adData[3];
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
				irValue[5] = adData[1];
				irValue[12] = adData[4];
				irValue[19] = adData[3];
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
				irValue[6] = adData[1];
				irValue[13] = adData[4];
				irValue[20] = adData[3];
				UvValue = adData[2];
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
	u16 Period;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_Cmd(TIM4, DISABLE);
	//定时器 50us adc扫描使用
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	switch(spd)
	{
		case SPEED_800:
			Period = SPEED800_PERIOD;
			break;
		case SPEED_900:
			Period = SPEED800_PERIOD*8/9;
			break;
		case SPEED_1000:
			Period = SPEED800_PERIOD*8/10;
			break;
		default:
			break;
	}
	//APB1的预分频数不为1的时候 定时器时钟是APB1的2倍
	//PCLK1 = 36Mhz，TIM2CLK = 36M/180 * 2 = 400K, Period = 100, 除以 TIM_Period TIM2 counter定时器频率 = 4k Hz, 周期为250us
	//PCLK1 = 36Mhz，TIM2CLK = 36M/180 * 2 = 400K, Period = 300, 除以 TIM_Period TIM2 counter定时器频率 = 1.33k Hz, 周期为750us
	//PCLK1 = 36Mhz，TIM2CLK = 36M/180 * 2 = 400K, Period = 400, 除以 TIM_Period TIM2 counter定时器频率 = 1 k Hz, 周期为1ms
// 	TIM_TimeBaseStructure.TIM_Prescaler = 180-1;
// 	TIM_TimeBaseStructure.TIM_Period = 200-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 180-1;
	TIM_TimeBaseStructure.TIM_Period = 400-1;//Period-1;
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);	

	// TIM IT enable
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
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
	//PCLK1 = 36Mhz，TIM2CLK = 36M/90 * 2 = 400K, Period = 2000, TIM2 counter定时器频率 = 200 Hz, 周期为5ms
	TIM_TimeBaseStructure.TIM_Prescaler = 180-1;
	TIM_TimeBaseStructure.TIM_Period = 2000-1;
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	

	// TIM IT enable
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);	
	
	//TIM2 enable counter
	TIM_Cmd(TIM2, ENABLE);
	/*
	//扫描对管的定时器 1ms
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	//APB1的预分频数不为1的时候 定时器时钟是APB1的2倍
	//PCLK1 = 36Mhz，TIM4CLK = 36M/180 * 2 = 400K, Period = 40, 除以 TIM_Period TIM4 counter定时器频率 = 2k Hz, 周期为0.5ms
	TIM_TimeBaseStructure.TIM_Prescaler = 180-1;
	TIM_TimeBaseStructure.TIM_Period = 400-1;
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);	

	// TIM IT enable
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);	
	
	//TIM4 enable counter
	TIM_Cmd(TIM4, ENABLE);
	*/
}

void InitGpioInMain(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	//管脚配置：打开所有的时钟频率
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	

	//红外灯发射
// 	GPIO_InitStructure.GPIO_Pin = HWFS_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode =HWFS_GPIO_MODE; 
// 	GPIO_Init(HWFS_GPIO_PORT, &GPIO_InitStructure);
// 	HWFS_ON();
	
// 	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode = LED_GPIO_MODE; 
// 	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
// 	LED_ON();
	
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
	
//		//进钞发射
//	GPIO_InitStructure.GPIO_Pin = TEST_FS_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = TEST_FS_GPIO_MODE; 
//	GPIO_Init(TEST_FS_GPIO_PORT, &GPIO_InitStructure);
//	test_On();
//	test_Off();
	
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
	//红外对管
 	GPIO_InitStructure.GPIO_Pin = PS1_GPIO_PIN;
 	GPIO_InitStructure.GPIO_Mode = PS1_GPIO_MODE; 
 	GPIO_Init(PS1_GPIO_PORT, &GPIO_InitStructure);
 	
 	GPIO_InitStructure.GPIO_Pin = PS2_GPIO_PIN;
 	GPIO_InitStructure.GPIO_Mode = PS2_GPIO_MODE; 
 	GPIO_Init(PS2_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY0_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = KEY0_GPIO_MODE; 
	GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = KEY1_GPIO_MODE; 
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = KEY2_GPIO_MODE; 
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);		

// 	GPIO_InitStructure.GPIO_Pin = PS3_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode = PS3_GPIO_MODE; 
// 	GPIO_Init(PS3_GPIO_PORT, &GPIO_InitStructure);

// 	GPIO_InitStructure.GPIO_Pin = PS4_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode = PS4_GPIO_MODE; 
// 	GPIO_Init(PS4_GPIO_PORT, &GPIO_InitStructure);

// 	GPIO_InitStructure.GPIO_Pin = PS7_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode = PS7_GPIO_MODE; 
// 	GPIO_Init(PS7_GPIO_PORT, &GPIO_InitStructure);
// 	
// 	GPIO_InitStructure.GPIO_Pin = PS8_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode = PS8_GPIO_MODE; 
// 	GPIO_Init(PS8_GPIO_PORT, &GPIO_InitStructure);
	
		//翻板电磁铁
// 	GPIO_InitStructure.GPIO_Pin = FBDCT_UP_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode  = FBDCT_UP_GPIO_MODE; 
// 	GPIO_Init(FBDCT_UP_GPIO_PORT, &GPIO_InitStructure);
// 	
// 	GPIO_InitStructure.GPIO_Pin = FBDCT_DOWN_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode  = FBDCT_DOWN_GPIO_MODE; 
// 	GPIO_Init(FBDCT_DOWN_GPIO_PORT, &GPIO_InitStructure);
// 	FBDCT_STOP();

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
		jckfs_Off();
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
u8 fiveMsCnt = 0;
void SysTick_Handler(void)
{
	if (TimingDelay > 0)
	{
		TimingDelay --;
	}
	oneSecCnt ++;
	if(oneSecCnt >= 1000)
	{
		gb_oneSec = 1;
		gb_oneSecAutoRefresh = 1;
		oneSecCnt = 0;
	}
	
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
	
	if(g_turnOffHwfsDelayTimer > 0)
	{
		g_turnOffHwfsDelayTimer --;
		if(g_turnOffHwfsDelayTimer == 0)
		{
			gb_needTurnOffLed = 1;
		}
	}
	
// 	if(checkKeyCnt > 0)
// 	{
// 		checkKeyCnt --;
// 		if(checkKeyCnt == 0)
// 		{
// 			gb_needCheckKey = 1;
// 			checkKeyCnt = CHECK_KEY_TIME;
// 		}
// 	}
	
// 	if(g_motorStopTime > 0)
// 	{
// 		g_motorStopTime --;
// 		if(g_motorStopTime == 0)
// 		{
// 			gb_cntMotorStopMp = 0;
// 			if(g_motor1State == MOTOR_STOP)
// 			{
// 				Motor1Enable();//STOP高电平 断开刹车mos管
// 			}
// 			if(g_machineTestMode == MOTOR_STOP_TEST)
// 			{
// 				gb_needOutputMotorStopInfo = 1;
// 			}
// 		}
// 	}
	//ScanKeyDown();
	
	if((gb_enableSample == 1)&&(systemState != SENSOR_VIEW))
	{
		//检测进钞接收
		//开灯无钞为低值 开灯有钞为高值 关灯为低值
		if (gb_jinChaoFaSheIsOn)//开灯
		{
			lastFsOnVal = enteranceSensorVal;
			//enteranceSensorValall[g_enteranceSensorValcnt++] = enteranceSensorVal;
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
		if(fiveMsCnt >= 5)
		{
			fiveMsCnt = 0;
			//控制段码液晶的进钞传感器发射
			//if(systemState != SELFCHECK)
			{
				ToggleJinChaoFaShe();		
			}
			
			scanEntergateTimer ++;
			if(scanEntergateTimer >= SCAN_ENTERGATE_TIME)
			{
				scanEntergateTimer = 0;
				
				//进钞编码统计
				if (entergatePulseNumCounter >= MIN_HAVEMONEY_PULSENUM_COUNT)
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

// void USART3_IRQHandler(void)
// {
// 	if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE))
// 	{
// 		/* Read one byte from the receive data register */
// 		uart3infifo_DataIn(USART_ReceiveData(USART3));	//自动清除RXNE标志
// // 		uart3DelayTimer = UART1_DATA_DELAY;
// // 		gb_needDealUart3Data = 1;

// 	}
// 	else if (USART_GetFlagStatus(USART3, USART_FLAG_TXE))
// 	{		
// 		if (uart3outfifo_count > 0)
// 		{
// 			/* Write one byte to the transmit data register */
// 			USART_SendData(USART3, uart3outfifo_DataOut());	//顺便清除flag_TXE
// 		}				
// 		else
// 		{
// 		  /* Disable the USARTy Transmit interrupt */
// 		  USART_ITConfig(USART3, USART_IT_TXE, DISABLE);		//实际上，发送为空的标志还在，只是关闭中断
// 		}    
// 	}
// }


//50us定时器
void TIM4_IRQHandler(void)
{
	u8 i;
	if (TIM_GetFlagStatus(TIM4, TIM_IT_Update))
  {
		TIM_ClearFlag(TIM4, TIM_IT_Update);	
		
		if((gb_enableSample == 1)||(needSampleIdleNum > 0))
		{
			//开启一次采集
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

void DealLengthIrINT(void)
{
	u8 i;
	//测长自触发采集
	if(gb_hwVccIsOn == 0)
	{
		return;
	}
	
	lengthFlag <<= 1;
	if(1 == isLengthIrHaveNote())
	{
		lengthFlag ++;
		gb_lengthCovered = 1;
	}
	else
	{
		gb_lengthCovered = 0;
	}
	
	if(gb_lengthHaveNote == 0)
	{
		if((lengthFlag&0x03) == 0x03)
		{
			gb_lengthHaveNote = 1;	
			
			if(g_motor1State == MOTOR_BACKWARD_RUN)
			{
				g_maxMpFromComputeToLength = 0;
				noteState &= (~STATE_BACKWARD_NOTE_LEAVE);
				noteState |= STATE_BACKWARD_COVER_LENGTH;
			}
			else if(g_motor1State == MOTOR_FORWARD_RUN)
			{
				g_maxMpFromEnteranceToLength = 0;
				noteState |= STATE_FORWARD_COVER_LENGTH;
				noteState &= (~STATE_FORWARD_COVER_ENTERANCE);

				g_lengthSampleIndex = 0;
				g_lengthIrMpNum = 0;	
				lengthMpCnt = 0;
				//memset(lengthData[21],0,IR_DATA_MAX_LEN);
				
				g_mgSampleIndex = 0;
				for(i = 0;i < 2;i++)//空闲的磁性拷贝过来
				{
					memcpy(mgData[i],lastMgData[i]+lastMgDataIndex,LAST_MG_DATA_MAX-lastMgDataIndex);
					memcpy(mgData[i]+LAST_MG_DATA_MAX-lastMgDataIndex,lastMgData[i],lastMgDataIndex);
				}
				g_mgSampleIndex += LAST_MG_DATA_MAX;
				g_colorSampleIndex = 0;
			}
		}
	}
	else
	{
		if((lengthFlag&0x0f) == 0x00)//离开f1
		{
			gb_uvNeedStartSampleflag = 0;
			gb_lengthHaveNote = 0;
			if(g_motor1State == MOTOR_FORWARD_RUN)
			{
				lengthDataLen = g_lengthSampleIndex;
				gb_oneNotePass = 1;	
				noteState |= STATE_COMPUTE;	
				noteState &= (~STATE_FORWARD_COVER_LENGTH);
			}
			else if(g_motor1State == MOTOR_BACKWARD_RUN)
			{
				g_maxMpFromLengthToEnterance = MP_FROM_LENGTH_TO_ENTERANCE;
				noteState &= (~STATE_BACKWARD_COVER_LENGTH);				
			}
		}
	}	
	if((gb_lengthHaveNote == 1)&&(g_motor1State == MOTOR_FORWARD_RUN))
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
	if(g_motor1State == MOTOR_FORWARD_RUN)
	{
		if(tempMgDataLen < TEMP_MG_DATA_MAX_LEN)
		{
				tempMgData[0][tempMgDataLen] = mrValue[0]; 
				tempMgData[1][tempMgDataLen] = mrValue[1]; 				
				tempMgDataLen ++;
		}

		if(gb_lengthHaveNote == 1)
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
}

void DealUVSampleINT(void)
{
	if(g_motor1State == MOTOR_FORWARD_RUN)
	{
		if(gb_uvNeedStartSampleflag == 1)
		{
			if(g_uvSampleIndex < UV_DATA_MAX_LEN)
			{
				uvData[g_uvSampleIndex] = UvValue;  				
				g_uvSampleIndex ++;
			}
		}
	}
}
//colorRGB[4][3];//4个颜色通道 RGB值
void DealColorSampleINT(void)
{
	if(g_motor1State == MOTOR_FORWARD_RUN)
	{
		if(gb_lengthHaveNote == 1)
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
						colorData[2][g_colorSampleIndex] = MIN(colorRGB[0][2]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[2],255);
						colorData[5][g_colorSampleIndex] = MIN(colorRGB[1][2]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[5],255);
						colorData[8][g_colorSampleIndex] = MIN(colorRGB[2][2]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[8],255);
						colorData[11][g_colorSampleIndex] = MIN(colorRGB[3][2]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[11],255);
						g_colorSampleIndex ++;
					}
					else if(g_colorFsRGB == FS_RED)
					{
						colorData[0][g_colorSampleIndex] = MIN(colorRGB[0][0]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[0],255);
						colorData[3][g_colorSampleIndex] = MIN(colorRGB[1][0]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[3],255);
						colorData[6][g_colorSampleIndex] = MIN(colorRGB[2][0]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[6],255);
						colorData[9][g_colorSampleIndex] = MIN(colorRGB[3][0]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[9],255);
					}
					else//GREEN
					{
						colorData[1][g_colorSampleIndex] = MIN(colorRGB[0][1]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[1],255);
						colorData[4][g_colorSampleIndex] = MIN(colorRGB[1][1]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[4],255);
						colorData[7][g_colorSampleIndex] = MIN(colorRGB[2][1]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[7],255);
						colorData[10][g_colorSampleIndex] = MIN(colorRGB[3][1]*MAX_RGB_VALUE/savedPara.adjustPara.colorAdjust[10],255);
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
	u8 i,j;
	u8 index;
	
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

		enteranceSensorVal = adData[5];
		switch(chanelIndexOf4051)
		{
			case 0:
				irValue[0] = adData[1];
				irValue[7] = adData[4];
				irValue[14] = adData[3];
				mrValue[0] = adData[2];
				break;
			case 1:
				irValue[1] = adData[1];
				irValue[8] = adData[4];
				irValue[15] = adData[3];
				mrValue[1] = adData[2];
				break;
			case 2:
				irValue[2] = adData[1];
				irValue[9] = adData[4];
				irValue[16] = adData[3];
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
				irValue[3] = adData[1];
				irValue[10] = adData[4];
				irValue[17] = adData[3];
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
				irValue[4] = adData[1];
				irValue[11] = adData[4];
				irValue[18] = adData[3];
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
				irValue[5] = adData[1];
				irValue[12] = adData[4];
				irValue[19] = adData[3];
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
				irValue[6] = adData[1];
				irValue[13] = adData[4];
				irValue[20] = adData[3];
				UvValue = adData[2];
				break;
		}
		chanelIndexOf4051 ++;
		//chanelIndexOf4051 %= 7;
		set4051Chanel(chanelIndexOf4051);
		if(chanelIndexOf4051 == 7)//切换一轮 所有数据更新后再处理
		{
// 			DealEnteranceIr1INT();
// 			DealEnteranceIr2INT();
 			DealLengthIrINT();
			DealMgSampleINT();
			DealColorSampleINT();
			DealUVSampleINT();
// 			DealColorIrINT();
// 			DealOtherIrINT();
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
				}
				else if(g_colorFsRGB == FS_RED)
				{
					redFs_Off();
					greenFs_On();
					blueFs_Off();
				}
				else
				{
					redFs_Off();
					greenFs_Off();
					blueFs_On();
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
		
		//检测进钞接收
// 		if (gb_jinChaoFaSheIsOn)
// 		{
// 			if(enteranceSensorVal > savedPara.machineWorkPara.d[INDEX_RMB_ENTERANCE_COVER_THRES])
// 			{
// 				entergatePulseNumCounter ++;
// 			}
// 			else
// 			{
// 				if (entergatePulseNumCounter > 0)
// 				{
// 					entergatePulseNumCounter --;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			if(enteranceSensorVal <= savedPara.machineWorkPara.d[INDEX_RMB_ENTERANCE_COVER_THRES])
// 			{
// 				entergatePulseNumCounter ++;
// 			}
// 			else
// 			{
// 				if (entergatePulseNumCounter > 0)
// 				{
// 					entergatePulseNumCounter --;
// 				}
// 			}
// 		}
		
		//控制段码液晶的进钞传感器发射
// 		if((systemState != SENSOR_VIEW)&&(systemState != SELFCHECK))
// 		{
// 			ToggleJinChaoFaShe();		
// 		}
		
// 		scanEntergateTimer ++;
// 		if(scanEntergateTimer >= SCAN_ENTERGATE_TIME)
// 		{
// 			scanEntergateTimer = 0;
			
			//进钞编码统计
// 			if (entergatePulseNumCounter >= MIN_HAVEMONEY_PULSENUM_COUNT)
// 			{
// 				gb_haveNoteInEntergate = 1;
// 			}
// 			else
// 			{
// 				gb_haveNoteInEntergate = 0;
// 			}
// 			entergatePulseNumCounter = 0;		
			
			//大电机调速
/*			if (g_motor1State == MOTOR_FORWARD_RUN)
			{
				if(csmpNumCnt < 100)
				{
					csmpNumRecord[csmpNumCnt] = csmpNumInCurrentCycle;
					csmpNumCnt ++;
				}
				if (csmpNumInCurrentCycle < savedPara.adjustPara.csmpNumIn50ms[currentSpeed] - 1)//速度太慢
				{
					if(pwmValOfmotor1 < 0xff)
					{
						pwmValOfmotor1 ++;
						motor1_SetPwm();
					}
				}
				else if (csmpNumInCurrentCycle > savedPara.adjustPara.csmpNumIn50ms[currentSpeed] + 1)//速度太快
				{
					if(pwmValOfmotor1 > 55)
					{
						pwmValOfmotor1 --;
						motor1_SetPwm();
					}
				}
				if(gb_isJammed == 0)
				{
					if((savedPara.machineWorkPara.d[INDEX_JAM_TYPE]&CSDDJ_JAM_CHECK) > 0)				
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
			else if (g_motor1State == MOTOR_BACKWARD_RUN)
			{
				
			}
			else
			{
				csddjJamTimes = 0;
			}
			csmpNumInCurrentCycle=0;	
			*/
// 		}
		
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
//码盘中断
void EXTI9_5_IRQHandler(void)
{
	u8 i;
//	if(EXTI_GetITStatus(CSMP_EXTI_LINE) != RESET)//码盘
	if(EXTI_GetFlagStatus(MP_EXTI_LINE))// != RESET)//码盘
	{
		//EXTI_ClearITPendingBit(CSMP_EXTI_LINE);
		EXTI_ClearFlag(MP_EXTI_LINE);
		
		mpCnt ++;
		
		csmpNumInCurrentCycle ++;
		
		maxSampleNumOneMp = MAX_SAMPLE_NUM_ONE_MP;
		if(gb_cntMgComputeTime == 1)
		{			
			mgComputeMpNum ++;
		}
		
		if((gb_lengthHaveNote == 1)&&(g_motor1State == MOTOR_FORWARD_RUN))
		{
			lengthMpCnt ++;
// 			if(g_lengthSampleIndex < IR_DATA_MAX_LEN)
// 			{
// 				lengthData[21][g_lengthSampleIndex] = 0xff;
// 			}
		}
// 		if(gb_needSampleMr == 1)
// 		{
// 			mgData[5][g_mgSampleIndex] = 0xff;
// 		}
		

		if(g_haveNoNoteCounter > 0)
		{
			g_haveNoNoteCounter --;
		}
		
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
		if(g_maxMpFromEnteranceToLength > 0)
		{
			g_maxMpFromEnteranceToLength --;
			if(g_maxMpFromEnteranceToLength == 0)
			{
				noteState &= (~STATE_FORWARD_COVER_ENTERANCE);
				//gb_needStopMotor = 1;
				//开盖或堵币 切到堵币状态 堵币状态下扫描全部红外无遮挡 就恢复normal
				gb_isJammed = JAM_ENTERANCE_TO_LENGTH;	
				DealJamAtOnce();
			}
		}
		if(g_maxMpFromLengthToEnterance > 0)
		{
			g_maxMpFromLengthToEnterance --;
			if(g_maxMpFromLengthToEnterance == 0)
			{
				if(gb_haveNoteInEntergate == 1)
				{
					noteState |= STATE_BACKWARD_COVER_ENTERANCE;
				}
				gb_needStopMotor = 1;
				//开盖或堵币 切到堵币状态 堵币状态下扫描全部红外无遮挡 就恢复normal
			}
		}	
		if(g_maxMpFromLengthToLeave > 0)
		{
			g_maxMpFromLengthToLeave --;
			if(g_maxMpFromLengthToLeave == 0)
			{
				noteState &= (~STATE_FORWARD_NOTE_LEAVE);
				gb_needStopMotor = 1;			
			}
		}
		if(g_maxMpFromComputeToLength > 0)
		{
			g_maxMpFromComputeToLength --;
			if(g_maxMpFromComputeToLength == 0)
			{
				noteState &= (~STATE_BACKWARD_NOTE_LEAVE);
				gb_needStopMotor = 1;			
			}
		}		
		
	//	DealInMp();
		
		if((savedPara.machineWorkPara.d[INDEX_JAM_TYPE]&IR_COVER_TIME_JAM_CHECK) > 0)
		{
			if(gb_isJammed == 0)
			{			
				if(irHaveNoteContinuslyCnt > IR_COVER_JAM_NUM)
				{
					gb_isJammed = JAM_PS2_IR;	
					DealJamAtOnce();
					irHaveNoteContinuslyCnt = 0;						
				}
			}
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
