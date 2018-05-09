/************************************************************************

*************************************************************************/


// void DealKeyDown(void)
// {
// 	u8 key;
// 	if(fifo_GetCount(KB_FIFO) > 0)
// 	{
// 		key = fifo_DataOut(KB_FIFO);
// 		//tm16xx_Led2Disp(key,gb_mgIsOn,gb_uvIsOn,gb_batchIsOn,gb_addIsOn);
// 		switch(systemState)
// 		{
// 			case NORMAL:
// 				DealKeyDownOnNormal(key);
// 				break;
// 			case SENSOR_VIEW:
// 				DealKeyDownOnSensorView(key);
// 				break;
// 			case BATCH_STOP:
// 				DealKeyDownOnBatchStop(key);
// 				break;
// 			case SUSP_STOP:
// 				DealKeyDownOnJudgeStop(key);
// 				break;
// 			case DU_BI:
// 				DealKeyDownOnDubiStop(key);
// 				break;
// 			case SET_JUDGE_PARA:
// 				DealKeyDownOnJudgeGradeMenu(key);
// 				break;
// 			case USER_PARA:
// 				DealKeyDownOnUserParaMenu(key);
// 				break;
// 			case NOTEPASS_INFO:
// 				DealKeyDownOnNotepassInfoMenu(key);
// 				break;
// 			case DISP_VERSION:
// 				DealKeyDownOnVersionMenu(key);
// 				break;
// 			case MOTOR_SET:
// 				DealKeyDownOnMotorMenu(key);
// 				break;
// 			case TEST_SWITCH:
// 				DealKeyDownOnTestMenu(key);
// 				break;
// 			case PARA_VIEW:
// 				DealKeyDownOnParaViewMenu(key);
// 				break;
// 			case LAO_HUA:
// 				DealKeyDownOnLaoHuaMenu(key);
// 				break;
// 		}
// 	}
// }

// void DealKeyDownOnNormal(u8 key)
// {
// 	switch(key)
// 	{
// 		case KEY_MODE:
// 			if((gb_mgIsOn == 1)&&(gb_uvIsOn == 1))
// 			{
// 				gb_mgIsOn = 0;
// 				gb_uvIsOn = 1;
// 			}
// 			else if((gb_mgIsOn == 0)&&(gb_uvIsOn == 1))
// 			{
// 				gb_mgIsOn = 1;
// 				gb_uvIsOn = 0;
// 			}
// 			else if((gb_mgIsOn == 1)&&(gb_uvIsOn == 0))
// 			{
// 				gb_mgIsOn = 0;
// 				gb_uvIsOn = 0;
// 			}
// 			else if((gb_mgIsOn == 0)&&(gb_uvIsOn == 0))
// 			{
// 				gb_mgIsOn = 1;
// 				gb_uvIsOn = 1;
// 			}			
// 			tm16xx_SetInsturctLed(gb_mgIsOn,gb_uvIsOn,gb_batchIsOn,gb_addIsOn);
// 			tm16xx_Led2DispLastStr();//ָʾ�Ƹ��� LED2ά��ԭ��ʾ
// 			break;
// 		case KEY_BATCH://Ԥ�ü��л�Ԥ����
// 			/***************************************
// 			Ԥ�ð����߼�
// 			������ʾԤ���� �����л� �л���0�͹ر�Ԥ����
// 			������ʾԤ���� ������ʾԤ����
// 			***************************************/
// 			g_btachNumIndex ++;
// 			g_btachNumIndex %= sizeof(BATCH_NUM);
// 			g_yuZhiNum = BATCH_NUM[g_btachNumIndex];
// 			if(g_yuZhiNum == 0)
// 			{
// 				gb_batchIsOn = 0;
// 			}
// 			else
// 			{
// 				gb_batchIsOn = 1;
// 			}
// 			tm16xx_SetInsturctLed(gb_mgIsOn,gb_uvIsOn,gb_batchIsOn,gb_addIsOn);
// 			tm16xx_Led1Disp(g_yuZhiNum);	
// 			tm16xx_Led2DispLastStr();//ָʾ�Ƹ��� LED2ά��ԭ��ʾ
// 			//tm16xx_Led2Disp(g_yuZhiNum);	
// 			//tm16xx_Led2DispStr(led2CurDispStr);//ָʾ�Ƹ��� LED2ά��ԭ��ʾ
// 			break;
// 		case LONG_KEY_BATCH://����Ԥ��Ԥ������1
// 			if(gb_batchIsOn == 1)
// 			{
// 				g_yuZhiNum ++;
// 				//tm16xx_Led1Disp(g_yuZhiNum);	
// 				tm16xx_Led1Disp(g_yuZhiNum);	
// 			}				
// 			break;
// 		case KEY_ADD:
// 			if(gb_addIsOn == 1)
// 			{
// 				gb_addIsOn = 0;
// 			}
// 			else
// 			{
// 				gb_addIsOn = 1;
// 			}
// 			tm16xx_SetInsturctLed(gb_mgIsOn,gb_uvIsOn,gb_batchIsOn,gb_addIsOn);
// 			tm16xx_Led2DispLastStr();//ָʾ�Ƹ��� LED2ά��ԭ��ʾ
// 			break;
// 		case KEY_SETTING:
// 			selectedItemIndex = 0;
// 			gb_paraChanged = 0;
// 			menuPara[0] = &savedPara.userWorkPara.d[INDEX_RMB_MG_GRADE];
// 			menuMod[0] = 3;
// 			menuPara[1] = &savedPara.userWorkPara.d[INDEX_RMB_UV_GRADE];
// 			menuMod[1] = 3;
// 			menuPara[2] = &savedPara.userWorkPara.d[INDEX_RMB_DOUBLE_NOTE_THRES];
// 			menuMod[2] = 0xff;
// 			menuPara[3] = &savedPara.userWorkPara.d[INDEX_RMB_CHAIN_NOTE_THRES];
// 			menuMod[2] = 0xff;
// 			menuParaIndex = 4;
// 			SetSystemState(SET_JUDGE_PARA);
// 			DispJudgeGradeMenu();
// 			break;
// 		case KEY_START:
// 		case KEY_START2:
// 			//�ֶ�ģʽ�� ���ת 
// 			if (savedPara.userWorkPara.d[INDEX_MANUAL_IS_ON] > 0)
// 			{
// 				gb_keyFuWeiDown  = 1;
// 			}
// 			//�±ҽ���� תһ��
// 			
// 			//���ۼ�ģʽ�� �����
// 			if(gb_addIsOn == 0)
// 			{
// 				ClearNoteNum();
// 			}
// 			//����бģʽ
// 			if(g_machineTestMode == SLANT_TEST)
// 			{
// 				slantSum = 0;
// 				slantNum = 0;
// 				LongBeep(3);
// 			}
// 			else if(g_machineTestMode == NOTEGAP_TEST)
// 			{
// 				minGapWidthProp = 0xff;
// 				LongBeep(3);
// 			}
// 			break;
// 		case LONG_KEY_START:
// 		case LONG_KEY_START2:
// 			//�ۼ�ģʽ�� �����
// 			ClearNoteNum();
// 			break;
// 		case LONG_KEY_SETTING:
// 			/*
// 			�˵�  
// 			1����α����˵� 
// 			2���û����ò˵� 
// 			3���߳���Ϣ�鿴 
// 			4���汾��Ϣ
// 			5�����������Բ˵� 
// 			6������������� 
// 			7������ģʽ����
// 			8��ȫ�������鿴
// 			9���ϻ�
// 			*/
// // 			SetSystemState(SET_JUDGE_PARA);
// // 			DispJudgeGradeMenu();
// 		
// // 			gb_enableSample = 0;
// // 			g_turnOffHwfsDelayTimer = 0;
// // 			hwfs_On();
// // 			SetSystemState(SENSOR_VIEW);
// // 			DispSensorViewMenu();
// 			break;
// 		default:
// 			break;
// 	}
// }


// void DealKeyDownOnBatchStop(u8 key)
// {
// 	switch(key)
// 	{
// 		case KEY_START:
// 		case KEY_START2:
// 			afterStopMg = 1;
// 			motorStopMpNum = g_motorStopMpNum;
// 			stopIrCovered = gb_irCovered;
// 			stopIrWidth = irWidth;
// 		
// 			gb_led2FlashOn = 0;
// 			InitCountIr();
// 			InitNoteNum();
// 			gb_enableSample = 1;
// 			SetSystemState(NORMAL);
// 			DispMainMenu();
// 			hwfs_On();
// 			delay_DelayMs(10);	
// 			motor1_Run();
// 			break;
// 		case KEY_MODE:
// 			break;
// 		case KEY_BATCH:
// 			break;
// 		case KEY_ADD:

// 			break;
// 		case KEY_SETTING:
// 	
// 			break;

// 		case LONG_KEY_SETTING:

// 			break;
// 		default:
// 			break;
// 	}
// }

// void DealKeyDownOnJudgeStop(u8 key)
// {
// 	switch(key)
// 	{
// 		case KEY_START:
// 		case KEY_START2:
// 			afterStopMg = 1;
// 			motorStopMpNum = g_motorStopMpNum;
// 			stopIrCovered = gb_irCovered;
// 			stopIrWidth = irWidth;
// 		
// 			gb_led2FlashOn = 0;
// 			//InitCountIr();
// 			//InitNoteNum();
// 			gb_enableSample = 1;
// 			SetSystemState(NORMAL);
// 			DispMainMenu();
// 			hwfs_On();
// 			delay_DelayMs(10);	
// 			motor1_Run();
// 			break;
// 		case KEY_MODE:
// 			break;
// 		case KEY_BATCH:
// 			break;
// 		case KEY_ADD:

// 			break;
// 		case KEY_SETTING:
// 	
// 			break;

// 		case LONG_KEY_SETTING:

// 			break;
// 		default:
// 			break;
// 	}
// }


// void DealKeyDownOnDubiStop(u8 key)
// {
// 	switch(key)
// 	{
// 		case KEY_START:
// 		case KEY_START2:
// 			if((ir2_HaveNote() > 0)
// 				||(ir3_HaveNote() > 0))//����±������
// 			{
// 				break;
// 			}	
// 			irHaveNoteContinuslyCnt = 0;
// 			csddjJamTimes = 0;
// 			//InitCountIr();
// 			//InitNoteNum();
// 			gb_oneNotePass = 0;
// 			gb_isJammed = 0;
// 			gb_enableSample = 1;
// 			if(gb_haveNoteInEntergate == 0)
// 			{
// 				motor1_Run();
// 				delay_DelayMs(1000);
// 				motor1_Stop();
// 			}
// 			if(gb_isJammed == 0)
// 			{
// 				gb_oneNotePass = 0;
// 				SetSystemState(NORMAL);
// 				DispMainMenu();				
// 			}
// 			break;
// 		case KEY_MODE:
// 			break;
// 		case KEY_BATCH:
// 			break;
// 		case KEY_ADD:

// 			break;
// 		case KEY_SETTING:
// 	
// 			break;
// 		default:
// 			break;
// 	}
// }

/*************************************
��ʾ��α����˵�
1 MG���� 
��������ģʽ��gb_mgIsOn ����ʶ�����رղ�ʶ�����˲˵��ļ�����Ч
�����ģʽ������KEY_D����LED1��ʾ����ң�gb_mgIsOn ����/�رմ��Լ�α���˲˵��ļ���Ϊ�������ֵ
2 UV����
gb_uvIsOn ����/�ر�UV��α �˲˵�Ϊ����
3 ���ż���
������ֵ
4 ���ż���
������ֵ
**************************************/
u8 *const JUDGE_MENU_STR[] = {" MG"," UV"," DB"," CH"};
void DispJudgeGradeMenu(void)
{
	tm16xx_Led1DispStr(JUDGE_MENU_STR[selectedItemIndex]);
	//tm16xx_Led1DispStr("JWJB");
	//delay_DelayMs(50);
	DispParaMenu();
}

void DispParaMenu(void)
{
	if(selectedItemIndex < menuParaIndex)
	{
		tm16xx_Led2Disp(*menuPara[selectedItemIndex]);
	}
}

void ParaInc(void)
{
	u8 d;
	if(selectedItemIndex < menuParaIndex)
	{
		d = *menuPara[selectedItemIndex];
		d ++;
		d %= menuMod[selectedItemIndex];
		*menuPara[selectedItemIndex] = d;
	}
}

void ParaDec(void)
{
	u8 d;
	if(selectedItemIndex < menuParaIndex)
	{
		d = *menuPara[selectedItemIndex];
		if(d > 0)
		{
			d --;
		}
		else
		{
			d = menuMod[selectedItemIndex]-1;
		}
		*menuPara[selectedItemIndex] = d;
	}
}

// void DealKeyDownOnJudgeGradeMenu(u8 key)
// {
// 	u8 i;
// 	switch(key)
// 	{
// 		case KEY_START:
// 		case KEY_START2:			
// 			if(gb_paraChanged == 1)
// 			{
// 				eeprom_SaveData();
// 				UpdateDataFromSavedData();
// 			}
// 			gb_enableSample = 1;
// 			SetSystemState(NORMAL);
// 			DispMainMenu();
// 			break;
// 		case KEY_MODE://�л�������Ŀ
// 			selectedItemIndex ++;
// 			selectedItemIndex %= menuParaIndex;
// 			DispJudgeGradeMenu();
// 			break;
// 		case KEY_BATCH://��Ŀ����++
// 			ParaDec();
// 			gb_paraChanged = 1;
// 			DispParaMenu();
// 			break;
// 		
// 		case KEY_ADD://��Ŀ����--
// 			ParaInc();
// 			gb_paraChanged = 1;
// 			DispParaMenu();
// 			break;
// 		case KEY_SETTING://���в˵�
// 			selectedItemIndex = 0;
// 			gb_paraChanged = 0;
// 			menuParaIndex = 0;
// 			for(i = 0;i < sizeof(savedPara.userWorkPara);i++)
// 			{
// 				menuPara[i] = &savedPara.userWorkPara.d[i];
// 				if(i < sizeof(userWorkParaMod))
// 				{
// 					menuMod[i] = userWorkParaMod[i];
// 				}
// 				else
// 				{
// 					menuMod[i] = 0xff;
// 				}
// 				menuParaIndex ++;
// 			}
// 			SetSystemState(USER_PARA);
// 			DispUserParaMenu();
// 			break;
// 		
// 		default:
// 			break;
// 	}	
// }

/**********************************************
�û������˵� 
savedPara.userWorkPara

***********************************************/
void DispUserParaMenu(void)
{
	U8ToStr(selectedItemIndex,dispStr);
	dispStr[0] = 'P';
	tm16xx_Led1DispStr(dispStr);

	DispParaMenu();
}
void DealKeyDownOnUserParaMenu(u8 key)
{
	switch(key)
	{
		case KEY_START:
		case KEY_START2:
			if(gb_paraChanged == 1)
			{
				eeprom_SaveData();
				UpdateDataFromSavedData();
			}
			gb_enableSample = 1;
			SetSystemState(NORMAL);
			DispMainMenu();
			break;
		case KEY_MODE://�л�������Ŀ
			selectedItemIndex ++;
			selectedItemIndex %= menuParaIndex;
			DispUserParaMenu();
			break;
		case LONG_KEY_MODE:
			selectedItemIndex = 0;
			DispUserParaMenu();
			break;
		case KEY_BATCH://��Ŀ����++
			ParaDec();
			gb_paraChanged = 1;
			DispParaMenu();
			break;
		
		case KEY_ADD://��Ŀ����--
			ParaInc();
			gb_paraChanged = 1;
			DispParaMenu();
			break;
		case KEY_SETTING://���в˵�
			SetSystemState(NOTEPASS_INFO);
			DispNotepassInfoMenu();
			break;
		
		default:
			break;
	}	
}

/**********************************************
��һ��ֽ����Ϣ�鿴
0��currentNoteType
1��curNoteValue
2��errorCode
3��noteWidth
4��slant
5��aqxWaveCnt
6��leftMgNum
7��rightMgNum
8��uvCnt

**********************************************/
void DispNotepassInfoMenu(void)
{
	U8ToStr(selectedItemIndex,dispStr);
	dispStr[0] = 'N';
	tm16xx_Led1DispStr(dispStr);

	switch(selectedItemIndex)
	{
		case 0:
			tm16xx_Led2Disp(currentNoteType);
			break;
		case 1:
			tm16xx_Led2Disp(curNoteValue);
			break;
		case 2:
			tm16xx_Led2Disp(errorCode);
			break;
		case 3:
			tm16xx_Led2Disp(noteWidth);
			break;
		case 4:
			U16ToStr(abs(slant),dispStr+1,3);
			if(slant < 0)
			{
				dispStr[0] = '-';
			}
			else
			{
				dispStr[0] = ' ';
			}
			tm16xx_Led2DispStr(dispStr);
			break;
		case 5:
			tm16xx_Led2Disp(aqxWaveCnt);
			break;
		case 6:
			tm16xx_Led2Disp(leftMgNum);
			break;
		case 7:
			tm16xx_Led2Disp(rightMgNum);
			break;
		case 8:
			tm16xx_Led2Disp(uvCnt);
			break;

	}
}

void DealKeyDownOnNotepassInfoMenu(u8 key)
{
	switch(key)
	{
		case KEY_START:
		case KEY_START2:
			gb_enableSample = 1;
			SetSystemState(NORMAL);
			DispMainMenu();
			break;
		case KEY_MODE:
			selectedItemIndex ++;
			selectedItemIndex %= 9;
			DispNotepassInfoMenu();
			break;
		case KEY_BATCH:
			if(selectedItemIndex > 0)
			{
				selectedItemIndex --;
				DispNotepassInfoMenu();
			}
			break;
		
		case KEY_ADD:

			break;
		case KEY_SETTING://���в˵�
			SetSystemState(DISP_VERSION);
			DispVersionMenu();
			break;
		
		default:
			break;
	}	
}

void DispVersionMenu(void)
{
	tm16xx_Led1DispStr("Ver");
	tm16xx_Led2Disp(VERSION);
}
void DealKeyDownOnVersionMenu(u8 key)
{
	switch(key)
	{
		case KEY_START:
		case KEY_START2:
			gb_enableSample = 1;
			SetSystemState(NORMAL);
			DispMainMenu();
			break;
		case KEY_MODE:
			
			break;
		case KEY_BATCH:
			break;
		
		case KEY_ADD:

			break;
		case KEY_SETTING://���в˵�
			gb_enableSample = 0;
			g_turnOffHwfsDelayTimer = 0;
			selectedItemIndex = 0;
			hwfs_On();
			jckfs_On();
			SetSystemState(SENSOR_VIEW);
			DispSensorViewMenu();
			break;
		
		default:
			break;
	}	
}

u8 *const SENSORVIEW_MENU_STR[] = {"IR1","IR2","IR3","IR4"," UV","FED"," MP"};
void DispSensorViewMenu(void)
{
	tm16xx_Led1DispStr(SENSORVIEW_MENU_STR[selectedItemIndex]);
	SampleOneRow();	
	switch(selectedItemIndex)
	{
		case 0://IR1
			tm16xx_Led2Disp(irValue[0]);
			break;
		case 1://IR2
			tm16xx_Led2Disp(irValue[1]);
			break;
		case 2://IR3
			tm16xx_Led2Disp(irValue[2]);
			break;
		case 3://IR4
			tm16xx_Led2Disp(irValue[3]);
			break;
		case 4://UV
			tm16xx_Led2Disp(uvValue);
			break;
		case 5://����
			tm16xx_Led2Disp(enteranceSensorVal);
			break;
		case 6://����
			tm16xx_Led2Disp(mpCnt);
			break;		
	}
	OutputSensorView();
}



void DealKeyDownOnSensorView(u8 key)
{
	switch(key)
	{
		case KEY_START:
		case KEY_START2:
			hwfs_Off();
			jckfs_Off();
			gb_enableSample = 1;
			SetSystemState(NORMAL);
			DispMainMenu();
			break;
		case KEY_MODE:
			selectedItemIndex ++;
			selectedItemIndex %= 7;
			DispSensorViewMenu();
			break;
		case KEY_BATCH:
			if(g_motor1State == MOTOR_RUN)
			{
				motor1_Stop();	
			}
			else
			{
				motor1_Run();
			}
			break;
		case KEY_ADD:
			//adjustMotorSpeed();
			break;
		case KEY_SETTING://���в˵�
			hwfs_On();
			gb_enableSample = 1;
			selectedItemIndex = 0;
			gb_paraChanged = 0;
			SetSystemState(MOTOR_SET);
			DispMotorMenu();		
			break;

		case LONG_KEY_SETTING:

			break;
		default:
			break;
	}
}

void DispMotorMenu(void)
{
// 	tm16xx_Led2Disp(1005);
// 	delay_DelayMs(1000);
	DispMotorParaMenu();

}
void DispMotorParaMenu(void)
{
	/*************
	1 �ٶȼ��� savedPara.userWorkPara.d[INDEX_SPEED]
	2 800 ����Ŀ��ֵ savedPara.adjustPara.csmpNumIn50ms
	3 900 ����Ŀ��ֵ savedPara.adjustPara.csmpNumIn50ms
	4 1000 ����Ŀ��ֵ savedPara.adjustPara.csmpNumIn50ms
	*************/
	switch(selectedItemIndex)
	{
		case 0:
			tm16xx_Led1DispStr("SPD");
			tm16xx_Led2Disp(savedPara.userWorkPara.d[INDEX_SPEED]);
			break;
		case 1:
			tm16xx_Led1DispStr("P 1");
			tm16xx_Led2Disp(savedPara.adjustPara.csmpNumIn50ms[SPEED_800]);
			break;
		case 2:
			tm16xx_Led1DispStr("P 2");
			tm16xx_Led2Disp(savedPara.adjustPara.csmpNumIn50ms[SPEED_900]);
			break;
		case 3:
			tm16xx_Led1DispStr("P 3");
			tm16xx_Led2Disp(savedPara.adjustPara.csmpNumIn50ms[SPEED_1000]);
			break;
		case 4:
			tm16xx_Led1DispStr("P 4");
			tm16xx_Led2Disp(savedPara.adjustPara.csddjInitVal[SPEED_800]);
			break;
		case 5:
			tm16xx_Led1DispStr("P 5");
			tm16xx_Led2Disp(savedPara.adjustPara.csddjInitVal[SPEED_900]);
			break;
		case 6:
			tm16xx_Led1DispStr("P 6");
			tm16xx_Led2Disp(savedPara.adjustPara.csddjInitVal[SPEED_1000]);
			break;
		default:
			break;
	}
}

void MotorParaInc(void)
{
	switch(selectedItemIndex)
	{
		case 0:
			savedPara.userWorkPara.d[INDEX_SPEED] ++;
			savedPara.userWorkPara.d[INDEX_SPEED] %= SPEED_NUM;
			break;
		case 1:
			savedPara.adjustPara.csmpNumIn50ms[SPEED_800] ++;
			savedPara.adjustPara.csmpNumIn50ms[SPEED_800] %= 200;
			break;
		case 2:
			savedPara.adjustPara.csmpNumIn50ms[SPEED_900] ++;
			savedPara.adjustPara.csmpNumIn50ms[SPEED_900] %= 200;
			break;
		case 3:
			savedPara.adjustPara.csmpNumIn50ms[SPEED_1000] ++;
			savedPara.adjustPara.csmpNumIn50ms[SPEED_1000] %= 200;
			break;
		default:
			break;
	}
}
void MotorParaDec(void)
{
	switch(selectedItemIndex)
	{
		case 0:
			if(savedPara.userWorkPara.d[INDEX_SPEED] > 50)
			{
				savedPara.userWorkPara.d[INDEX_SPEED] --;
			}	
			break;
		case 1:
			if(savedPara.adjustPara.csmpNumIn50ms[SPEED_800] > 50)
			{
				savedPara.adjustPara.csmpNumIn50ms[SPEED_800] --;
			}
			break;
		case 2:
			if(savedPara.adjustPara.csmpNumIn50ms[SPEED_900] > 50)
			{
				savedPara.adjustPara.csmpNumIn50ms[SPEED_900] --;
			}
			break;
		case 3:
			if(savedPara.adjustPara.csmpNumIn50ms[SPEED_1000] > 50)
			{
				savedPara.adjustPara.csmpNumIn50ms[SPEED_1000] --;
			}
			break;
		default:
			break;
	}
}
void DealKeyDownOnMotorMenu(u8 key)
{
	switch(key)
	{
		case KEY_START:
		case KEY_START2:
			if(gb_paraChanged == 1)
			{
				eeprom_SaveData();
				UpdateDataFromSavedData();
			}
			gb_enableSample = 1;
			hwfs_Off();
			SetSystemState(NORMAL);
			DispMainMenu();
			break;
		case KEY_MODE://�л�������Ŀ
			selectedItemIndex ++;
			selectedItemIndex %= 7;
			DispMotorParaMenu();
			break;
		case KEY_BATCH://��Ŀ����++
			MotorParaInc();
			gb_paraChanged = 1;
			DispMotorParaMenu();
			break;
		
		case KEY_ADD://��Ŀ����--
			MotorParaDec();
			gb_paraChanged = 1;
			DispMotorParaMenu();
			break;
		case LONG_KEY_SETTING:
			
			adjustMotorSpeed();
			break;
		case KEY_SETTING://���в˵� 
			SetSystemState(TEST_SWITCH);
			DispTestMenu();
			break;
		
		default:
			break;
	}	
}

void DispTestMenu(void)
{
	tm16xx_Led1DispStr("TST");
	//delay_DelayMs(1000);
	tm16xx_Led2Disp(g_machineTestMode);
}
void DealKeyDownOnTestMenu(u8 key)
{
	u8 i;
	switch(key)
	{
		case KEY_START:
		case KEY_START2:
			gb_enableSample = 1;
			SetSystemState(NORMAL);
			DispMainMenu();
			break;
		case KEY_MODE:
			g_machineTestMode ++;
			g_machineTestMode %= TEST_MODE_MAX;
			tm16xx_Led2Disp(g_machineTestMode);
			if(g_machineTestMode == 0)
			{
				tm16xx_DisableDP();
			}
			else
			{
				tm16xx_EnableDP(g_machineTestMode - 1);
			}
			break;
		case KEY_BATCH:
			if(g_machineTestMode > 0)
			{
				g_machineTestMode --;
			}
			tm16xx_Led2Disp(g_machineTestMode);
			if(g_machineTestMode == 0)
			{
				tm16xx_DisableDP();
			}
			else
			{
				tm16xx_EnableDP(g_machineTestMode - 1);
			}
			break;
		
		case KEY_ADD:
			g_machineTestMode = 0;
			tm16xx_Led2Disp(g_machineTestMode);
			tm16xx_DisableDP();		
			break;
		case KEY_SETTING://���в˵�  ȫ�������鿴
			selectedItemIndex = 0;
			gb_paraChanged = 0;
			menuParaIndex = 0;
			for(i = 0;i < sizeof(savedPara.machineWorkPara);i++)
			{
				menuPara[i] = &savedPara.machineWorkPara.d[i];
				if(i < sizeof(machineWorkParaMod))
				{
					menuMod[i] = machineWorkParaMod[i];
				}
				else
				{
					menuMod[i] = 0xff;
				}
				menuParaIndex ++;
			}		
			SetSystemState(PARA_VIEW);
			DispParaViewMenu();
			break;
		
		default:
			break;
	}	
}

/*****************************************************
�������в���
savedPara.machineWorkPara
*****************************************************/
void DispParaViewMenu(void)
{
	U8ToStr(selectedItemIndex,dispStr);
	dispStr[0] = 'A';
	tm16xx_Led1DispStr(dispStr);

	DispParaMenu();
}

void DealKeyDownOnParaViewMenu(u8 key)
{
	switch(key)
	{
		case KEY_START:
		case KEY_START2:
			if(gb_paraChanged == 1)
			{
				eeprom_SaveData();
				UpdateDataFromSavedData();
			}
			gb_enableSample = 1;
			SetSystemState(NORMAL);
			DispMainMenu();
			break;
		case KEY_MODE://�л�������Ŀ
			selectedItemIndex ++;
			selectedItemIndex %= menuParaIndex;
			DispParaViewMenu();
			break;
		case LONG_KEY_MODE:
			selectedItemIndex = 0;
			DispParaViewMenu();
			break;
		case KEY_BATCH://��Ŀ����++
			ParaDec();
			gb_paraChanged = 1;
			DispParaMenu();
			break;
		
		case KEY_ADD://��Ŀ����--
			ParaInc();
			gb_paraChanged = 1;
			DispParaMenu();
			break;
		case LONG_KEY_ADD:
			InitMachineWorkPara();
			eeprom_SaveData();
			LongBeep(3);
			break;
		case KEY_SETTING://���в˵�  �ϻ�
			laoHuaTime = MAX_LAO_HUA_TIME;
			SetSystemState(LAO_HUA);
			DispLaoHuaMenu();
			break;
		
		default:
			break;
	}	
}
void DispLaoHuaMenu(void)
{
	tm16xx_Led1DispStr(" LH");
	DispLaoHuaTime();
}
void DispLaoHuaTime(void)
{
	tm16xx_Led2Disp(laoHuaTime);
}
void DealKeyDownOnLaoHuaMenu(u8 key)
{
	if(gb_inLaoHua == 1)
	{
		switch(key)
		{
			case KEY_START:
			case KEY_START2://�������˵�
				gb_inLaoHua = 0;
				hwfs_Off();
				motor1_Stop();
				laoHuaTime = MAX_LAO_HUA_TIME;
				DispLaoHuaMenu();
				break;
			default:
				break;
		}
		return;
	}
	
	switch(key)
	{
		case KEY_START:
		case KEY_START2:
			
			gb_inLaoHua = 0;
			hwfs_Off();
			motor1_Stop();
		
			gb_enableSample = 1;
			SetSystemState(NORMAL);
			DispMainMenu();
			
			break;
		case KEY_MODE:
			if(laoHuaTime > 0)
			{
				gb_inLaoHua = 1;
				laoHuaSingleTime = LAOHUA_SINGLE_RUN_TIME;
				oneMinLaoHuaTime = ONE_MIN_LAOHUA;
				//laoHuaTime = MAX_LAO_HUA_TIME;
				hwfs_On();
				motor1_Run();
			}
			else
			{
				gb_inLaoHua = 0;
				hwfs_Off();
				motor1_Stop();
			}
			break;
		case KEY_BATCH:
			if(gb_inLaoHua == 0)
			{
				laoHuaTime += 60;
				DispLaoHuaTime();
			}
			break;
		
		case KEY_ADD:
			if(gb_inLaoHua == 0)
			{
				if(laoHuaTime > 60)
				{
					laoHuaTime -= 60;
					DispLaoHuaTime();
				}
			}
			break;
		case KEY_SETTING://���в˵� ��α����
			selectedItemIndex = 0;
			gb_paraChanged = 0;
			menuPara[0] = &savedPara.userWorkPara.d[INDEX_RMB_MG_GRADE];
			menuMod[0] = 3;
			menuPara[1] = &savedPara.userWorkPara.d[INDEX_RMB_UV_GRADE];
			menuMod[1] = 3;
			menuPara[2] = &savedPara.userWorkPara.d[INDEX_RMB_DOUBLE_NOTE_THRES];
			menuMod[2] = 0xff;
			menuPara[3] = &savedPara.userWorkPara.d[INDEX_RMB_CHAIN_NOTE_THRES];
			menuMod[2] = 0xff;
			menuParaIndex = 4;
			SetSystemState(SET_JUDGE_PARA);
			DispJudgeGradeMenu();
			break;
		
		default:
			break;
	}	
}
