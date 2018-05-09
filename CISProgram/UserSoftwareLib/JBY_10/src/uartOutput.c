
#define ONE_MG_DATA_NUM 14 //MG2路 颜色12路
#define ONE_MG_LINE_NUM (ONE_MG_DATA_NUM+3)
void OutputMgColorDetailData(void)
{
	u16 i,maxLen;
	u8 j;
	u8 buffer[30];
	
	
	memset(buffer,0,sizeof(buffer));
	buffer[0] = 0xc6;
	buffer[1] = ONE_MG_LINE_NUM - 3;
	buffer[ONE_MG_LINE_NUM-1] = 0x55;
	
	maxLen = 0;
	if(maxLen < tempMgDataLen)
	{
		maxLen = tempMgDataLen;
	}
	if(maxLen < g_colorSampleIndex)
	{
		maxLen = g_colorSampleIndex;
	}
	//发数据
	for(i = 0;i < maxLen;i++)
	{
		if(i < tempMgDataLen)
		{
			for(j = 0;j < 2;j++)// 0 1
			{
				buffer[2+j] = tempMgData[j][i];
			}
		}
		else
		{
			memset(buffer + 2,0,6);
		}
		if(i < g_colorSampleIndex)
		{
			for(j = 0;j < 12;j++)//6-13 红外 14 UV预留
			{
				buffer[2+2+j] = colorData[j][i];
			}
		}
		else
		{
			memset(buffer + 2 + 2,0,12);
		}
				
		uart_SendDataToUart1(buffer,ONE_MG_LINE_NUM);
		while(uart1outfifo_count> 0)
		{
		}
	}	
	
	//发送附加输出1
	buffer[2] = HighByte(g_mgSampleIndex);
	buffer[3] = LowByte(g_mgSampleIndex);
	buffer[4] = HighByte(g_colorSampleIndex);
	buffer[5] = LowByte(g_colorSampleIndex);
	buffer[6] = 0;
	buffer[7] = 0;
	buffer[8] = 0;
	buffer[9] = 0;
	buffer[10] = 0;
	uart_SendDataToUart1(buffer,ONE_MG_LINE_NUM);
	
	//发送附加输出2
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0;
	buffer[5] = 0;
	buffer[6] = 0;//空
	buffer[7] = 0;//空
	buffer[8] = 0;//空
	buffer[9] = 0;//空
	buffer[10] = 0;//空
	uart_SendDataToUart1(buffer,ONE_MG_LINE_NUM);	
	
	//发送附加输出3
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0;
	buffer[5] = 0;
	buffer[6] = 0;//空
	buffer[7] = 0;//空
	buffer[8] = 0;//空
	buffer[9] = 0;//空
	buffer[10] = 0;//空
	uart_SendDataToUart1(buffer,ONE_MG_LINE_NUM);	
	
	//发送附加输出4
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0;
	buffer[5] = 0;
	buffer[6] = 0;//空
	buffer[7] = 0;//空
	buffer[8] = 0;//空
	buffer[9] = 0;//空
	buffer[10] = 0;//空
	uart_SendDataToUart1(buffer,ONE_MG_LINE_NUM);	
	
	//发送附加输出5
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0;
	buffer[5] = 0;
	buffer[6] = 0;//空
	buffer[7] = 0;//空
	buffer[8] = 0;//空
	buffer[9] = 0;//空
	buffer[10] = 0;//空
	uart_SendDataToUart1(buffer,ONE_MG_LINE_NUM);	
	
	
	//6行全为0xff的分隔符
	for (i=0; i<6; i++)
	{
		for(j = 0;j < ONE_MG_LINE_NUM - 3;j++)
		{
			buffer[2+j] = 0xff;
		}
		uart_SendDataToUart1(buffer,ONE_MG_LINE_NUM);

		//等待串口发送完毕
		while(uart1outfifo_count> 0)
		{
		}
	}
}

/*//测长数据疏忽从
void OutputLengthDetailData(void)
{
	u16 i,maxLen;
	u8 j;
	u8 buffer[30];
	
	buffer[0] = 0xc6;
	buffer[1] = LENGTH_IR_CHANNEL_NUM;
	buffer[LENGTH_IR_CHANNEL_NUM+2] = 0x55;
	
	for(i = 0;i < g_lengthSampleIndex;i++)
	{
		for(j = 0;j < LENGTH_IR_CHANNEL_NUM;j++)
		{
			buffer[2+j] = lengthData[j][i];
		}
		
		uart_SendDataToUart1(buffer,LENGTH_IR_CHANNEL_NUM+3);

		//等待串口发送完毕
		while(uart1outfifo_count> 0)
		{
		}		
	}
	//6行全为0xff的分隔符
	for (i=0; i<6; i++)
	{
		for(j = 0;j < LENGTH_IR_CHANNEL_NUM;j++)
		{
			buffer[2+j] = 0xff;
		}
		uart_SendDataToUart1(buffer,LENGTH_IR_CHANNEL_NUM+3);

		//等待串口发送完毕
		while(uart1outfifo_count> 0)
		{
		}
	}
}*/
//第一二路磁性，第3到23路为红外，第3到14为颜色
void OutputALLDetailData(void)
{
	u16 i,maxLen;
	u8 j;
	u8 buffer[30];
	
	buffer[0] = 0xc6;
	buffer[1] = LENGTH_IR_CHANNEL_NUM+3;
	buffer[LENGTH_IR_CHANNEL_NUM+5] = 0x55;
	//先发送数据高度
	for(i=0; i<900; i++)
	{
		if(i == 0)
		{
				buffer[2] = HighByte(g_mgSampleIndex);
				buffer[3] = HighByte(g_mgSampleIndex);
				for(j = 0;j < LENGTH_IR_CHANNEL_NUM;j++)
				{
					buffer[4+j] = HighByte(g_lengthSampleIndex);
				}
				buffer[4+j] = HighByte(g_uvSampleIndex);
		}
		else if(i == 1)
		{
				buffer[2] = LowByte(g_mgSampleIndex);
				buffer[3] = LowByte(g_mgSampleIndex);
				for(j = 0;j < LENGTH_IR_CHANNEL_NUM;j++)
				{
					buffer[4+j] = LowByte(g_lengthSampleIndex);
				}	
				buffer[4+j] = HighByte(g_uvSampleIndex);				
		}
		else
		{
			//磁性
			if(i<(g_mgSampleIndex+2))
			{
				for(j = 0;j < 2;j++)// 0 1
				{
					buffer[2+j] = mgData[j][i-2];
				}
			}
			else
			{
				for(j = 0;j < 2;j++)// 0 1
				{
					buffer[2+j] = 0;
				}
			}
			//UV
			if(i<(g_uvSampleIndex+2))
			{
					buffer[4+LENGTH_IR_CHANNEL_NUM] = uvData[i-2];
			}
			else
			{
					buffer[4+LENGTH_IR_CHANNEL_NUM] = 0;
			}
			//测长红外
			if(i <= 600)
			{
				if(i < (g_lengthSampleIndex+2))
				{
					for(j = 0;j < LENGTH_IR_CHANNEL_NUM;j++)
					{
						buffer[4+j] = lengthData[j][i-2];
					}
				}
				else
				{
					for(j = 0;j < LENGTH_IR_CHANNEL_NUM;j++)
					{
						buffer[4+j] = 0;
					}
				}
			}
			else//颜色
			{
				if(i==601)
				{
					for(j=0; j<LENGTH_IR_CHANNEL_NUM; j++)
					{
						if(j < 12)
						{
							buffer[4+j] = HighByte(g_colorSampleIndex);
						}
						else
						{
							buffer[4+j] = 0;
						}
					}
				}
				else if(i==602)
				{
					for(j=0; j<LENGTH_IR_CHANNEL_NUM; j++)
					{
						if(j < 12)
						{
							buffer[4+j] = LowByte(g_colorSampleIndex);
						}
						else
						{
							buffer[4+j] = 0;
						}
					}
				}
				else
				{
					for(j=0; j<12; j++)
					{
						if((i-600)<(g_colorSampleIndex+2))
						{
							buffer[4+j] = colorData[j][i-600-2];
						}
						else
						{
							buffer[4+j] = 0;
						}
					
					}
					for(j=12;j<LENGTH_IR_CHANNEL_NUM;j++)
					{
							buffer[4+j] = 0;
					}
				}
			}
		}
		uart_SendDataToUart1(buffer,LENGTH_IR_CHANNEL_NUM+6);

		//等待串口发送完毕
		while(uart1outfifo_count> 0)
		{
		}		
	}
	//6行全为0xff的分隔符
	for (i=0; i<6; i++)
	{
		for(j = 0;j < LENGTH_IR_CHANNEL_NUM+3;j++)
		{
			buffer[2+j] = 0xff;
		}
		uart_SendDataToUart1(buffer,LENGTH_IR_CHANNEL_NUM+6);

		//等待串口发送完毕
		while(uart1outfifo_count> 0)
		{
		}
	}
}
void OutputSensorView(void)
{
	u8 buf[20];
	
	buf[0] = CMD_SENSOR_VIEW;
	buf[1] = 0x04;
	buf[2] = irValue[0];
	buf[3] = irValue[1];
	buf[4] = irValue[2];
	buf[5] = irValue[3];
	buf[6] = 0x55;
	uart_SendDataToUart1(buf,7);
}
