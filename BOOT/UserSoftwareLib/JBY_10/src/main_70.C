/***************************************************************************


****************************************************************************/
#include "main.h"
//#include "menu.h"

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
//	u8 tmpBuf[10];
//	u16 temp;
	if(g_subStateOfNormal == NORMAL_CHA_KAN_CAN_SHU)
	{
		switch(key)
		{
			case KEY_RESTART:		
//				g_subStateOfNormal = NORMAL_DIAN_CHAO; 
//				DispMainMenu();
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
//					SetSystemState(NORMAL);
//					gb_enableSample = 1;
//					noteState = 0;
//					DispMainMenu();			
				break;
		}
	}
}

u8 motorTest = 0;


int main(void)
{
	u16 i;
	u8 needUpGrade;
	u32 upgradeFlag;
	u8 tmpBuf[32];
	u8 allZeroNum,all0xffNum;
	u8 emptyFlash = 0;
	u8 r;
	u32 fileLen;
	u32 n,k;
	u32 appdate[4];
	
	delay_DelayMs(10);
	//读升级标志
	upgradeFlag = flash_ReadUpdateFlag();
	if(upgradeFlag==0xffffffff)//第一次使用
	{
		appdate[0] = flash_ReadAPPdate(APP_DATA_ADDR);
		appdate[1] = flash_ReadAPPdate(APP_DATA_ADDR+4);
		appdate[2] = flash_ReadAPPdate(APP_DATA_ADDR+8);
		appdate[3] = flash_ReadAPPdate(APP_DATA_ADDR+12);

		if(appdate[0]==0xffffffff&&appdate[1]==0xffffffff&&appdate[2]==0xffffffff&&appdate[3]==0xffffffff)
		{
			
		}
		else
		{
			goto RUN_APP;
			flash_SaveUpdateFlag(0);
		}
	}
	//upgradeFlag = flash_ReadUpdateFlag();
	if(NEED_UPGRADE_FLAG == upgradeFlag)
	{
		needUpGrade = 1;
	}
	else if(0 != upgradeFlag)
	{
		needUpGrade = 1;
		flash_SaveUpdateFlag(NEED_UPGRADE_FLAG);
	}
	else
	{
			//读app区域数据 
		flash_ReadData(APP_ADDR,(u32 *)tmpBuf,32);
		allZeroNum = 0;
		all0xffNum = 0;
		for(i = 0;i < 32;i++)
		{
			if(tmpBuf[i] == 0xff)
			{
				all0xffNum ++;
			}
			if(tmpBuf[i] == 0)
			{
				allZeroNum ++;
			}		
		}
		if((all0xffNum == 32)||(allZeroNum == 32))
		{
			emptyFlash = 1;
			//upgradeFlag = NEED_UPGRADE_FLAG;
			//flash_ReadUpdateFlag(upgradeFlag);
			needUpGrade = 1;
		}	
	}
	
	if(needUpGrade == 0)//不需要升级 跳转
	{
		RUN_APP:
		RunProgramme(APP_ADDR);
	}
	
	//需要升级
	/*端口配置及
	初始化*/
	MainInit();
	//delay_DelayMs(10);

	#ifdef USE_IWDG
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);		
	IWDG_SetPrescaler(IWDG_Prescaler_32);		
	IWDG_SetReload(40);	
	IWDG_ReloadCounter();		
	IWDG_Enable();
	#endif
	
	delay_DelayMs(1500);
	
	dispIndex = 0;
	disp_clearScreen(WHITE);
	disp_setPenColor(RED);
	disp_setBackColor(WHITE);
	disp_setFont(24);
	disp_string("BootloaderV12",0,dispIndex++*ONE_LINE_H);
	disp_string(upgradeFileName,0,dispIndex++*ONE_LINE_H);
	
	readBuffer[0] = 0;
	
//	disp_clearScreen(WHITE);
//	disp_setPenColor(RED);
//	disp_setBackColor(WHITE);
//	disp_setFont(24);
//	disp_string("WELCOME",SCREEN_WIDTH/2-12*3,SCREEN_HEIGHT/2-12);
//	delay_DelayMs(500);
	
//	hwfs_On();
	//jckfs_On();
//	SetSystemState(NORMAL);
//	gb_enableSample = 1;
//	g_subStateOfNormal = NORMAL_DIAN_CHAO; 
//	DispMainMenu();
//	LongBeep(1);
	//gb_enableSample = 1;
	//
	
	while (1)
	{
		//喂狗
		#ifdef USE_IWDG
		IWDG_ReloadCounter();
		#endif
		
		USB_CheckReady();//
		
		if(gb_oneSec == 1)
		{
			gb_oneSec = 0;
		}
		
		//U盘插入
		if(gb_udiskPlugIn == 1)
		{
			gb_udiskPlugIn = 0;
			//读取升级文件长度 判断文件是否在
			r = ReadUdiskFileSize(upgradeFileName,&fileLen);
			if(r == 0)//读取成功
			{
				upgradeFileSize = fileLen;
				disp_string("File Size:",0,dispIndex*ONE_LINE_H);
				U32ToStr(upgradeFileSize,dispStr,6);
				disp_string(dispStr,12*12,dispIndex*ONE_LINE_H);
				dispIndex ++;	
				disp_string("Write Flash:",0,dispIndex*ONE_LINE_H);
				//依次读取文件写入flash
				readLen = 0;
				for(k = 0;k < upgradeFileSize;)
				{
					if(k + READ_LEN_ONE_TIME < upgradeFileSize)
					{
						currentReadLen = READ_LEN_ONE_TIME;
					}
					else
					{
						currentReadLen = (upgradeFileSize-k);
						memset(readBuffer,0xff,((currentReadLen/FLASH2_ONE_SECTOR)+1)*FLASH2_ONE_SECTOR);//最后一个不满2K的后面补0xff
					}
					r = ReadUdiskFile(upgradeFileName,readBuffer,readLen,currentReadLen);
					if(r == 0)
					{
						U32ToStr(k,dispStr,6);
						disp_string(dispStr,12*13,dispIndex*ONE_LINE_H);
						//写入flash
						for(n = 0;n < currentReadLen;)
						{
							if((APP_ADDR+readLen+n)<USER_FLASH_BANK1_END_ADDRESS)
							{
								flash_WriteData(APP_ADDR+readLen+n,(u32 *)(readBuffer+n),FLASH_ONE_SECTOR);
								n += FLASH_ONE_SECTOR;	
							}
							else
							{
								flash_WriteData(APP_ADDR+readLen+n,(u32 *)(readBuffer+n),FLASH2_ONE_SECTOR);
								n += FLASH2_ONE_SECTOR;	
							}
							//delay_DelayMs(10);
							U32ToStr(n,dispStr,6);
							disp_string(dispStr,12*13+12*7,dispIndex*ONE_LINE_H);
						}
					}
					else
					{
						disp_string("ERROR1",12*13+12*7,dispIndex*ONE_LINE_H);
						goto UPGRADE_ERROR;	
					}
					k += currentReadLen;
					readLen += currentReadLen;
				}
				if(readLen == upgradeFileSize)//写完成
				{
					//校验
					dispIndex ++;	
					disp_string("Verify Flash:",0,dispIndex*ONE_LINE_H);
					readLen = 0;
					for(k = 0;k < upgradeFileSize;)
					{
						if(k + READ_LEN_ONE_TIME < upgradeFileSize)
						{
							currentReadLen = READ_LEN_ONE_TIME;
						}
						else
						{
							currentReadLen = (upgradeFileSize-k);
							memset(readBuffer,0xff,((currentReadLen/FLASH2_ONE_SECTOR)+1)*FLASH2_ONE_SECTOR);//最后一个不满2K的后面补0xff
						}
						r = ReadUdiskFile(upgradeFileName,readBuffer,readLen,currentReadLen);
						if(r == 0)//读取文件成功
						{
							U32ToStr(k,dispStr,6);
							disp_string(dispStr,12*14,dispIndex*ONE_LINE_H);
							//写入flash
							for(n = 0;n < currentReadLen;)
							{
								if((APP_ADDR+readLen+n)<USER_FLASH_BANK1_END_ADDRESS)
								{
									flash_ReadData(APP_ADDR+readLen+n,(u32 *)(flashBuffer),FLASH_ONE_SECTOR);
									//校验
									for(i = 0;i < FLASH_ONE_SECTOR;i++)
									{
										if(*(flashBuffer+i) != *(readBuffer+n+i))
										{
											break;
										}
									}
									if(i == FLASH_ONE_SECTOR)
									{
										n += FLASH_ONE_SECTOR;		
										delay_DelayMs(10);
										U32ToStr(n,dispStr,6);
										disp_string(dispStr,12*14+12*7,dispIndex*ONE_LINE_H);
									}
									else
									{
										disp_string("ERROR1",12*14+12*7,dispIndex*ONE_LINE_H);
										goto UPGRADE_ERROR;							
									}
								}
								else
								{
									flash_ReadData(APP_ADDR+readLen+n,(u32 *)(flashBuffer),FLASH2_ONE_SECTOR);
									//校验
									for(i = 0;i < FLASH2_ONE_SECTOR;i++)
									{
										if(*(flashBuffer+i) != *(readBuffer+n+i))
										{
											break;
										}
									}
									if(i == FLASH2_ONE_SECTOR)
									{
										n += FLASH2_ONE_SECTOR;		
										delay_DelayMs(10);
										U32ToStr(n,dispStr,6);
										disp_string(dispStr,12*14+12*7,dispIndex*ONE_LINE_H);
									}
									else
									{
										disp_string("ERROR3",12*14+12*7,dispIndex*ONE_LINE_H);
										goto UPGRADE_ERROR;							
									}
								}
							}
						}
						else
						{
							disp_string("ERROR2",12*14+12*7,dispIndex*ONE_LINE_H);
							goto UPGRADE_ERROR;	
						}
						k += currentReadLen;
						readLen += currentReadLen;
					}
					if(readLen == upgradeFileSize)//校验完成
					{
						dispIndex ++;
						disp_string("Jump To App",0,dispIndex*ONE_LINE_H);
						delay_DelayMs(500);
						//改升级标志 跳转
						flash_SaveUpdateFlag(0);
						__disable_irq();		
						NVIC_SystemReset();	
					}
				}
			}
		}
		UPGRADE_ERROR:		
		//读取升级文件 每次读取
		
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
//	u8 i;
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
					default:
						break;
				}
			}
		}
	}	
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
//	u8 i;

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

////新函数
//void SetSystemState(u8 d)
//{
//	systemState = d;
//}

void LongBeep(u8 times)
{
//	if(savedPara.userWorkPara.d[INDEX_BEEP_ON] == 1)
	{
		beepTimes = times;	//蜂鸣器该响的次数
		beepType = LONG_BEEP_LENGTH;
	}
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
//	u8 i;

//	NVIC_InitTypeDef NVIC_InitStructure;	
//	EXTI_InitTypeDef EXTI_InitStructure;
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
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  	
	
	//子模块初始化
	uart_Init();	
	fifo_Init();
	delay_Init();	
//	eeprom_Init();
//	eeprom_ReadData();
//	if (savedPara.flag != DATA_FLAG)
//	{
//		if ((savedPara.flag&0xf0000000) != (DATA_FLAG & 0xf0000000))
//		{
//			InitAllPara();//初始化所有参数
//			#ifdef BOOT_APP	
//			flash_SaveUpdateFlag(0);
//			#endif
//		}
//		else//初始化用户设置的参数
//		{
//			InitMachineWorkPara();
//			InitUserWorkPara();
//		}
//		savedPara.flag = DATA_FLAG;
//		eeprom_SaveData();
//	}

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
//	GPIO_EXTILineConfig(MP_GPIO_EXTI_PORT_SOURCE, MP_GPIO_EXTI_PIN_SOURCE);

//	EXTI_InitStructure.EXTI_Line = MP_EXTI_LINE;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = MP_EXTI_TRIGGER;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);

//	NVIC_InitStructure.NVIC_IRQChannel = MP_EXTI_IRQ;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure); 
//	
//	adc_init();
	
			  /* Init Host Library */
	USB_Config();

}




//void ADOneTime2(void)
//{														
//	//开始一组转换
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//}

//void ADOneTime(void)
//{
////	DMA_ClearFlag(DMA1_FLAG_TC1);														
//	ADOneTime2();
//	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
//	DMA_ClearFlag(DMA1_FLAG_TC1);
//}		

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
 	GPIO_InitStructure.GPIO_Pin = USB_EN_GPIO_PIN;
 	GPIO_InitStructure.GPIO_Mode = USB_EN_GPIO_MODE; 
 	GPIO_Init(USB_EN_GPIO_PORT, &GPIO_InitStructure);
 	UsbEn_Off();
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
//	u8 i;
	if (TIM_GetFlagStatus(TIM4, TIM_IT_Update))
  {
		TIM_ClearFlag(TIM4, TIM_IT_Update);	
		

	}
}

//DMA中断
//u8 cnt;
//void DMA1_Channel1_IRQHandler(void)
//{	
//	u8 i,j;
//	u8 index;
//	
// 	if(DMA_GetFlagStatus(DMA1_FLAG_TC1))
//  {
//		DMA_ClearFlag(DMA1_FLAG_TC1); //清除全部中断标志
//		
//		dmaEndNum ++;

//	}
//}

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
