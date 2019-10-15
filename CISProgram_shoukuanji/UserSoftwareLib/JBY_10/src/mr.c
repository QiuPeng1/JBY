/***************************************************************************


****************************************************************************/

/*包含私有头文件 */
#include "_mr.h"
#include <math.h>

#define X_OFFSET 1000
#define X_OFFSET2 1200

/*公开的子程序*/ 

void length_collabrationCompute(void)
{
	u16 i,j,k;
	u16 channelStart,channelEnd;
	u32 sum,num;
	u16 d; 
	u8 max,min;
	
	memset(collabrationValue,0,REAL_IR_NUM*2);
	for(i = 0;i < REAL_IR_NUM;i ++)
	{
		channelStart = lengthDataLen-1;
		channelEnd = 0;
		for(j = 0;j < lengthDataLen/2;j++)
		{
			if((lengthData[i][j] < lengthIdleOriginValue[i] - LENGTH_HAVENOTE_VALUE_THRES)
				&&(lengthData[i][j+1] < lengthIdleOriginValue[i] - LENGTH_HAVENOTE_VALUE_THRES)
				&&(lengthData[i][j+2] < lengthIdleOriginValue[i] - LENGTH_HAVENOTE_VALUE_THRES))
			{
				channelStart = j;
				break;
			}
		}
		for(j = lengthDataLen-1;j > lengthDataLen/2;j--)
		{
			if((lengthData[i][j] < lengthIdleOriginValue[i] - LENGTH_HAVENOTE_VALUE_THRES)
				&&(lengthData[i][j-1] < lengthIdleOriginValue[i] - LENGTH_HAVENOTE_VALUE_THRES)
				&&(lengthData[i][j-2] < lengthIdleOriginValue[i] - LENGTH_HAVENOTE_VALUE_THRES))
			{
				channelEnd = j;
				break;
			}
		}	
		
		if(channelStart + lengthDataLen/2 <= channelEnd)
		{
			sum = 0;
			num = 0;
			d = channelEnd - channelStart;
			max = 0;
			min = 0xff;
			for(j = channelStart+d/4;j <= channelStart+3*d/4;j ++)
			{
				sum += lengthData[i][j];
				num ++;
				if(lengthData[i][j] > max)
				{
					max = lengthData[i][j];
				}
				if(lengthData[i][j] < min)
				{
					min = lengthData[i][j];
				}			
			}
			
			if((max > min)&&(max - min < 60))
			{			
				sum *= 10;
				sum /= num;
				if(sum >= collabrationMax[i])
				{
					collabrationMax[i] = sum;
				}
				if(sum <= collabrationMin[i])
				{
					collabrationMin[i] = sum;
				}
				
				collabrationSum[i] += sum;
				collabrationNum[i] ++;
				collabrationValue[i] = sum;
			}
		}
		else 
		{

		}
	}
}

#define DIRECT_INC 0
#define DIRECT_DEC 1
#define DIRECT_IDLE 2
#define WAVE_THRES1 230
#define WAVE_THRES2 0
// void GetAqxWave(u8 *d,u16 start,u16 end,u8 waveThres,u8 combineDis)
// {
// 	u16 i,k,j;
// 	u8 direct;
// 	u8 currentVal,lastVal;
// 	u16 maxStart,maxEnd;
// 	u16 minStart,minEnd;
// 	u8 max,min;
// 	u16 maxPos,minPos;

// 	direct = DIRECT_IDLE;
// 	min = 0Xff;
// 	max = 0;
// 	aqxMinWaveNum = 0;
// 	aqxMaxWaveNum = 0;

// 	for(i = 0;i < MAX_AQX_WAVE_NUM;i++)
// 	{
// 		aqxMaxWave[i].val = 0xffff;
// 		aqxMinWave[i].val = 0;
// 	}
// 	for(j = start;j <= end;j++)
// 	{
// 		lastVal = d[j-1];
// 		currentVal = d[j];
// 		if(currentVal > waveThres)
// 		{
// 			currentVal = waveThres;
// 		}
// 		if(lastVal > waveThres)
// 		{
// 			lastVal = waveThres;
// 		}
// 		if(currentVal < lastVal)
// 		{
// 			if (direct == DIRECT_INC)	//如果前面是上升阶段，就定格最大值点
// 			{
// 				maxPos = (maxStart + maxEnd + 1) / 2;	
// 				aqxMaxWave[aqxMaxWaveNum].pos = maxPos;
// 				aqxMaxWave[aqxMaxWaveNum].val = max;
// 				if((max >= waveThres)&&(aqxMaxWave[aqxMaxWaveNum].val - aqxMinWave[aqxMinWaveNum].val) > 10)
// 				{
// 					if(aqxMaxWaveNum > 0)
// 					{
// 						if(aqxMaxWave[aqxMaxWaveNum].pos - aqxMaxWave[aqxMaxWaveNum - 1].pos < combineDis)//合并波峰的阈值
// 						{
// 							aqxMaxWave[aqxMaxWaveNum - 1].pos = (aqxMaxWave[aqxMaxWaveNum].pos+aqxMaxWave[aqxMaxWaveNum - 1].pos)/2;
// 							aqxMaxWave[aqxMaxWaveNum - 1].val = (aqxMaxWave[aqxMaxWaveNum].val+aqxMaxWave[aqxMaxWaveNum - 1].val)/2;
// 						}
// 						else
// 						{
// 							if(aqxMaxWaveNum < MAX_AQX_WAVE_NUM - 1)
// 							{
// 								aqxMaxWaveNum ++;
// 							}
// 						}
// 					}
// 					else
// 					{
// 						if(aqxMaxWaveNum < MAX_AQX_WAVE_NUM - 1)
// 						{
// 							aqxMaxWaveNum ++;
// 						}
// 					}
// 				}
// 			}
// 			direct = DIRECT_DEC;
// 			max = 0;	
// 			
// 			if (currentVal < min)
// 			{
// 				min = currentVal;
// 				minStart = j;
// 				minEnd = j;
// 			}			
// 			else if ((currentVal > min + 2) && (currentVal < min + 10))
// 			{
// 				min = currentVal;
// 				minStart = j;
// 				minEnd = j;
// 			}
// 		}
// 		else if(currentVal > lastVal)
// 		{
// 			if (direct == DIRECT_DEC)	//如果前面是下降阶段，就定格最小值点
// 			{
// 				minPos = (minStart + minEnd + 1) / 2;
// 				aqxMinWave[aqxMinWaveNum].pos = minPos;
// 				aqxMinWave[aqxMinWaveNum].val = min;
// 				if((min <= WAVE_THRES2)&&(aqxMaxWave[aqxMaxWaveNum].val - aqxMinWave[aqxMinWaveNum].val) > 10)
// 				{
// 					if(aqxMinWaveNum < MAX_AQX_WAVE_NUM - 1)
// 					{
// 						aqxMinWaveNum ++;
// 					}
// 				}
// 			}
// 			direct = DIRECT_INC;
// 			min = 0xff;
// 			
// 			if (currentVal > max)
// 			{
// 				max = currentVal;
// 				maxStart = j;
// 				maxEnd = j;
// 			}
// 		}
// 		else//相等
// 		{
// 			if (currentVal == max)//相等
// 			{
// 				maxEnd = j;
// 			}
// 			
// 			if (currentVal == min)
// 			{
// 				minEnd = j;
// 			}
// 		}
// 	}
// }

void PredealMpCount(void)
{
	u16 i;
//	mpNum = 0;
// 	for(i = 1;i < mgDataLenA;i++)
// 	{
// 		//if(mgDataA[3][i] == 0xff)
// 		if((mgDataA[5][i-1] == 0)&&(mgDataA[5][i] == 0xff))
// 		{
// 			if(mpNum < MAX_MP_NUM_ONE_NOTE)
// 			{
// 				mpPos[mpNum++] = i;
// 			}
// 		}
// 	}
}

#define ONE_MP_SAMPLE_NUM 14
u16 GetAqxCodeInMp(u16 pos)
{
// 	u16 i;
// 	u16 start,end;
// 	u16 tmp;
// 	if(mpNum < 1)
// 	{
// 		return 0;
// 	}
// 	for(i = 0;i < mpNum-1;i++)
// 	{
// 		if((pos >= mpPos[i])
// 			&&(pos <= mpPos[i+1]))
// 		{
// 			start = mpPos[i];
// 			end = mpPos[i+1];
// 			tmp = (pos - start)*ONE_MP_SAMPLE_NUM/(end - start);
// 			tmp += i*ONE_MP_SAMPLE_NUM;
// 			return(tmp);
// 		}
// 	}
	return 0;
}

void mr_JudgeRmbNoteType(u8 noteWidth)
{
// 	u16 i,j,k;
// 	u8 k1,k2,k3;
// 	u8 *pdMt;//,*pdLSideMg,*pdRSideMg,*pdLSideMg2,*pdRSideMg2,*pdLMidSideMg,*pdRMidSideMg;
// 	u16 avgAqxCode;
// 	u8 aqxCodeNum,aqxWrongNum2;
// 	u16 aqxCode[MAX_AQX_WAVE_NUM];
// 	u16 aqxWavePosInMp[MAX_AQX_WAVE_NUM];
// 	u16 u16Tmp,u16Tmp2;
// 	
// #ifdef VC_PLUS_PLUS
// 	u16 l,m;
// 	int pTmpData32[MG_DATA_MAX_LEN];
// #endif	 

// #ifdef VC_PLUS_PLUS
// 	for(i = 0;i < 4;i++)
// 	{
// 		for(l = 0;l < mgDataLenA;l++)
// 		{
// 			pTmpData32[l] = mgDataA[i][l];
// 		}
// 		Display_Proj(pTmpData32, mgDataLenA, 0, 100*i, 300,0);
// 	}
// #endif

// 	pdMt = mgDataA[0];
// 	
// 	aqxWaveCnt = 0;
// 	errorCode = 0;
// 	
// 	if(mgDataLenA < 500)
// 	{
// 		errorCode = ERROR_MG_DATALEN;
// 		currentNoteType = RMB_ARTI;
// 		return;
// 	}

// #ifdef VC_PLUS_PLUS
// 		Display_Int(noteWidth,40,0);

// 		Display_Int(afterStopMg,100+40*i++,0);
// 		Display_Int(motorStopMpNum,100+40*i++,0);
// 		Display_Int(stopIrCovered,100+40*i++,0);
// 		Display_Int(stopIrWidth,100+40*i++,0);
// 		Display_Int(mgSlant,100+40*i++,0);
// #endif
// 	//宽度划分基本面额范围
// 	widthNoteType = WID_ARTI;
// 	for(i = 0;i < 3;i++)
// 	{
// 		if((noteWidth <= widthThres[i])&&(noteWidth > widthThres[i+1]))
// 		{
// 			widthNoteType = i;
// 			break;
// 		}
// 	}
// 	if(widthNoteType == WID_ARTI)
// 	{
// 		if(noteWidth > chainNoteThres)
// 		{
// 			errorCode = ERROR_CHAIN_NOTE;
// 		}
// 		else
// 		{
// 			errorCode = ERROR_WIDTH;
// 		}
// 		currentNoteType = RMB_ARTI;
// 		return;
// 	}

//  	GetAqxWave(pdMt,10,mgDataLenA-80,aqxWaveThres,aqxWaveCombineThres);
// #ifdef VC_PLUS_PLUS
//  		Display_Int(aqxMaxWaveNum,0,0);
//  		for(i = 0;i < aqxMaxWaveNum;i++)
// 		{
//  			Draw_BlueCross(aqxMaxWave[i].pos,100 - aqxMaxWave[i].val*3/10,8);
//  		}
// 		Draw_RedLine(0,100- (aqxWaveThres)*3/10,mgDataLenA,100- (aqxWaveThres)*3/10);
// #endif
// 	//编码根据码盘做位置整形
// 	PredealMpCount();
// 	for(i = 0;i < aqxMaxWaveNum;i++)
// 	{
// 		aqxWavePosInMp[i] = GetAqxCodeInMp(aqxMaxWave[i].pos);
// 	}
// 	if(widthNoteType == WID_5)//1元5元宽度
// 	{
// /*		if(aqxMaxWaveNum < 3)//无安全线
// 		{
// 			currentNoteType = RMB_1;
// 			return;
// 		}
// 		else */
// 		if(aqxMaxWaveNum >= aqxCodeNumThres)//5元
// 		{
// 			//检测5元安全线 待做
// 			currentNoteType = RMB_5;
// 			return;
// 		}
// 		else 
// 		{
// 			errorCode = ERROR_AQX_NUM;
// 			currentNoteType = RMB_ARTI;
// 			return;
// 		}
// 	}
// 	else//100宽度 10 20 50宽度
// 	{
// 		//安全线编码过少
// 		if(aqxMaxWaveNum < aqxCodeNumThres)
// 		{
// 			errorCode = ERROR_AQX_NUM;
// 			currentNoteType = RMB_ARTI;
// 			return;		
// 		}
// 	}
// 	
// 	//计算安全线编码
// 	aqxCodeNum = 0;
// 	for(i = 0;i < aqxMaxWaveNum-1;i++)
// 	{
// 		if(aqxCodeNum < MAX_AQX_WAVE_NUM)
// 		{
// 			aqxCode[aqxCodeNum++] = aqxWavePosInMp[i+1] - aqxWavePosInMp[i];
// 		}	
// 	}
// 	aqxWaveCnt = aqxCodeNum;
// #ifdef VC_PLUS_PLUS
//  		for(i = 0;i < aqxCodeNum;i++)
// 		{
// 			Display_Int(aqxCode[i],(aqxMaxWave[i].pos+aqxMaxWave[i+1].pos)/2-10,100- (aqxWaveThres-20)*3/10);
//  		}
// #endif

// 	if(widthNoteType == WID_100)//100元宽度
// 	{
// 		k = 0;
// 		for(i = 0;i < aqxCodeNum;i++)
// 		{
// 			if((aqxCode[i] >= rmb100AqxCodeThres[0])
// 				&&(aqxCode[i] <= rmb100AqxCodeThres[1]))
// 			{
// 				k ++;
// 			}
// 		}
// 		if(k + 4 >= aqxCodeNum)//可以有4个不满足要求
// 		{
// 			//100元05版
// 			k1 = 0;
// 			k2 = 0;
// 			for(i = 0;i < aqxCodeNum;i++)
// 			{
// 				if((aqxCode[i] >= rmb100AqxCodeThres[0])
// 					&&(aqxCode[i] <= rmb100AqxCodeThres[1]))
// 				{
// 					if(i > 0)
// 					{
// 						u16Tmp = 100*aqxCode[i-1];
// 						u16Tmp /= aqxCode[i];
// 						if((u16Tmp >= rmb100ScaleThres[0])
// 							&&(u16Tmp <= rmb100ScaleThres[1]))
// 						{
// 							k2 ++;
// 						}
// 						
// 					}
// 					else
// 					{
// 						u16Tmp = 100*aqxCode[i+1];
// 						u16Tmp /= aqxCode[i];
// 						if((u16Tmp >= rmb100ScaleThres[0])
// 							&&(u16Tmp <= rmb100ScaleThres[1]))
// 						{
// 							k2 ++;
// 						}
// 					}
// 					k1 ++;				
// 				}
// 			}
// 			if((k2 + 3 >= k1)//全部中间有2个可以有3个不满足
// 				&&(k2 >= aqxCodeNum*2/3))//至少有2/3组满足要求
// 			{
// 				currentNoteType = RMB_100_05;
// 			}
// 			else
// 			{
// 				errorCode = ERROR_RMB100_05_MG_ERR;
// 				currentNoteType = RMB_ARTI;
// 			}
// 			return;	
// 		}
// 		else
// 		{
// 			k1 = 0;
// 			for(i = 0;i < aqxCodeNum;i++)
// 			{
// 				if((aqxCode[i] >= 60)
// 					&&(aqxCode[i] <= 70))
// 				{
// 					k1 ++;
// 				}
// 			}
// 			k2 = 0;
// 			for(i = 0;i < aqxCodeNum;i++)
// 			{
// 				if((aqxCode[i] >= 10)
// 					&&(aqxCode[i] <= 18))
// 				{
// 					k2 ++;
// 				}
// 			}
// 			if((k1 >= 5)&&(k2 >= 1))
// 			{
// 				//100元15版
// 				currentNoteType = RMB_100_15;
// 			}
// 			else
// 			{
// 				errorCode = ERROR_RMB100_15_MG_ERR;
// 				currentNoteType = RMB_ARTI;
// 			}
// 		}
// 				
// 	}
// 	else if(widthNoteType == WID_20)//50元宽度
// 	{
// 		//统计50的安全线特征
// 		k = 0;
// 		for(i = 0;i < aqxCodeNum;i++)
// 		{
// 			if((aqxCode[i] >= rmb50AqxCodeThres[0])
// 				&&(aqxCode[i] <= rmb50AqxCodeThres[1]))
// 			{
// 				k ++;
// 			}
// 		}
// 		if(k + 2 >= aqxCodeNum/2)//可以有2个不满足要求
// 		{
// 			k1 = 0;
// 			k2 = 0;
// 			for(i = 0;i < aqxCodeNum;i++)
// 			{
// 				if((aqxCode[i] >= rmb50AqxCodeThres[0])
// 					&&(aqxCode[i] <= rmb50AqxCodeThres[1]))
// 				{
// 					if(i > 0)
// 					{
// 						u16Tmp = 100*aqxCode[i-1];
// 						u16Tmp /= aqxCode[i];
// 						if((u16Tmp >= rmb50ScaleThres[0])
// 							&&(u16Tmp <= rmb50ScaleThres[1]))
// 						{
// 							k2 ++;
// 						}
// 						
// 					}
// 					else
// 					{
// 						u16Tmp = 100*aqxCode[i+1];
// 						u16Tmp /= aqxCode[i];
// 						if((u16Tmp >= rmb50ScaleThres[0])
// 							&&(u16Tmp <= rmb50ScaleThres[1]))
// 						{
// 							k2 ++;
// 						}
// 					}
// 					k1 ++;
// 				}
// 			}

// 			if((k2 + 3 >= k1)//全部中间有2个可以有3个不满足
// 				&&(k2 >= 2))//至少有2组满足要求
// 			{
// 				currentNoteType = RMB_50;
// 			}
// 			else
// 			{
// 				errorCode = ERROR_RMB50_MG_ERR;
// 				currentNoteType = RMB_ARTI;
// 			}
// 			return;	
// 		}
// 		
// 		//10块20块
// 		k = 0;
// 		for(i = 0;i < aqxCodeNum;i++)
// 		{
// 			if((aqxCode[i] >= rmb20_10AqxCodeThres[0])
// 				&&(aqxCode[i] <= rmb20_10AqxCodeThres[1]))
// 			{
// 				k ++;
// 			}
// 		}	
// 		if(k + 3 >= aqxCodeNum/3)
// 		{
// 			k1 = 0;
// 			k2 = 0;
// 			k3 = 0;
// 			for(i = 0;i < aqxCodeNum;i++)
// 			{
// 				if((aqxCode[i] >= rmb20_10AqxCodeThres[0])
// 					&&(aqxCode[i] <= rmb20_10AqxCodeThres[1]))
// 				{
// 					if((i > 0)&&(i < aqxCodeNum-1))
// 					{
// 						u16Tmp = 100*aqxCode[i];
// 						u16Tmp /= aqxCode[i-1];
// 						u16Tmp2 = 100*aqxCode[i];
// 						u16Tmp2 /= aqxCode[i+1];
// 						aqxCodeScale[k1][0] = aqxCode[i];
// 						aqxCodeScale[k1][1] = u16Tmp;
// 						aqxCodeScale[k1][2] = u16Tmp2;
// 						aqxCodeScale[k1][3] = 0;
// 						aqxCodeScale[k1][4] = 0;
// 						if(((u16Tmp >= rmb20ScaleThres[0][0])
// 						&&(u16Tmp <= rmb20ScaleThres[0][1])
// 						&&(u16Tmp2 >= rmb20ScaleThres[1][0])
// 						&&(u16Tmp2 <= rmb20ScaleThres[1][1]))
// 						||((u16Tmp2 >= rmb20ScaleThres[0][0])
// 						&&(u16Tmp2 <= rmb20ScaleThres[0][1])
// 						&&(u16Tmp >= rmb20ScaleThres[1][0])
// 						&&(u16Tmp <= rmb20ScaleThres[1][1])))
// 						{
// 							k2 ++;
// 							aqxCodeScale[k1][3] = 1;
// 						}
// 						if(((u16Tmp >= rmb10ScaleThres[0][0])
// 						&&(u16Tmp <= rmb10ScaleThres[0][1])
// 						&&(u16Tmp2 >= rmb10ScaleThres[1][0])
// 						&&(u16Tmp2 <= rmb10ScaleThres[1][1]))
// 						||((u16Tmp2 >= rmb10ScaleThres[0][0])
// 						&&(u16Tmp2 <= rmb10ScaleThres[0][1])
// 						&&(u16Tmp >= rmb10ScaleThres[1][0])
// 						&&(u16Tmp <= rmb10ScaleThres[1][1])))
// 						{
// 							k3 ++;
// 							aqxCodeScale[k1][4] = 1;
// 						}						
// 					}
// 					else if(i == 0)
// 					{
// 						u16Tmp = 100*aqxCode[i];
// 						u16Tmp /= aqxCode[i+1];
// 						aqxCodeScale[k1][0] = aqxCode[i];
// 						aqxCodeScale[k1][1] = 0xff;
// 						aqxCodeScale[k1][2] = u16Tmp;
// 						aqxCodeScale[k1][3] = 0;
// 						aqxCodeScale[k1][4] = 0;
// 						if(((u16Tmp >= rmb20ScaleThres[0][0])
// 						&&(u16Tmp <= rmb20ScaleThres[0][1]))
// 						||((u16Tmp >= rmb20ScaleThres[1][0])
// 						&&(u16Tmp <= rmb20ScaleThres[1][1])))
// 						{
// 							k2 ++;
// 							aqxCodeScale[k1][3] = 1;
// 						}
// 						if(((u16Tmp >= rmb10ScaleThres[0][0])
// 						&&(u16Tmp <= rmb10ScaleThres[0][1]))
// 						||((u16Tmp >= rmb10ScaleThres[1][0])
// 						&&(u16Tmp <= rmb10ScaleThres[1][1])))
// 						{
// 							k3 ++;
// 							aqxCodeScale[k1][4] = 1;
// 						}
// 					}
// 					else if(i == aqxCodeNum-1)
// 					{
// 						u16Tmp = 100*aqxCode[i];
// 						u16Tmp /= aqxCode[i-1];
// 						aqxCodeScale[k1][0] = aqxCode[i];
// 						aqxCodeScale[k1][1] = u16Tmp;
// 						aqxCodeScale[k1][2] = 0xff;	
// 						aqxCodeScale[k1][3] = 0;
// 						aqxCodeScale[k1][4] = 0;
// 						if(((u16Tmp >= rmb20ScaleThres[0][0])
// 						&&(u16Tmp <= rmb20ScaleThres[0][1]))
// 						||((u16Tmp >= rmb20ScaleThres[1][0])
// 						&&(u16Tmp <= rmb20ScaleThres[1][1])))
// 						{
// 							k2 ++;
// 							aqxCodeScale[k1][3] = 1;
// 						}
// 						if(((u16Tmp >= rmb10ScaleThres[0][0])
// 						&&(u16Tmp <= rmb10ScaleThres[0][1]))
// 						||((u16Tmp >= rmb10ScaleThres[1][0])
// 						&&(u16Tmp <= rmb10ScaleThres[1][1])))
// 						{
// 							k3 ++;
// 							aqxCodeScale[k1][4] = 1;
// 						}
// 					}
// 	
// 					k1 ++;
// 				}
// 			}
// #ifdef VC_PLUS_PLUS
// 	for(i = 0;i < k1;i++)
// 	{
// 		Display_Int(aqxCodeScale[i][0],i*40,100);
// 		Display_Int(aqxCodeScale[i][1],i*40,120);
// 		Display_Int(aqxCodeScale[i][2],i*40,140);
// 		Display_Int(aqxCodeScale[i][3],i*40,160);
// 		Display_Int(aqxCodeScale[i][4],i*40,180);
// 	}
// #endif
// 			
// 			if(k2 > k3)
// 			{
// 				//20元
// 				if((k2 + 3 >= k1)//全部中间有2个可以有2个不满足
// 				&&(k2 >= 2))//至少有2组满足要求
// 				{
// 					currentNoteType = RMB_20;
// 				}
// 				else
// 				{
// 					errorCode = ERROR_RMB20_MG_ERR;
// 					currentNoteType = RMB_ARTI;
// 				}
// 			}
// 			else if(k3 > k2)
// 			{
// 				//10元
// 				if((k3 + 3 >= k1)//全部中间有2个可以有2个不满足
// 				&&(k3 >= 2))//至少有2组满足要求
// 				{
// 					currentNoteType = RMB_10;
// 				}
// 				else
// 				{
// 					errorCode = ERROR_RMB10_MG_ERR;
// 					currentNoteType = RMB_ARTI;
// 				}
// 			}
// 			else
// 			{
// 				errorCode = ERROR_RMB10_20_MG_UNKNOWN;
// 				currentNoteType = RMB_ARTI;
// 			}	
// 			return;
// 		}
// 		else
// 		{
// 			errorCode = ERROR_RMB10_20_MG_ERR;
// 			currentNoteType = RMB_ARTI;
// 			return;	
// 		}
// 			
// 	}

}


/*
#define UV_HEIGHT_THRES 100
#define UV_WIDTH_THRES 20
void uv_JudgeNote(void)
{
	u16 i,j,k;
#ifdef VC_PLUS_PLUS
	u16 l,m;
	int pTmpData32[MG_DATA_MAX_LEN];
#endif
	
#ifdef VC_PLUS_PLUS
	for(i = 0;i < 4;i++)
	{
		for(l = 0;l < uvDataLenA;l++)
		{
			pTmpData32[l] = uvDataA[i][l];
		}
		Display_Proj(pTmpData32, uvDataLenA, mtDataLenA + 10, 100*i, 300,0);
	}
#endif
	uvRlt = 0;
	for(i = 0;i < 4;i++)
	{
		k = 0;
		for(j = 10;j < uvDataLenA/2;j++)
		{
			if(uvDataA[i][j] >= UV_HEIGHT_THRES)
			{
				k ++;
				if(k >= UV_WIDTH_THRES)
				{
					uvRlt |= 1<<(i*2);
					break;
				}
			}
			else
			{
				k = 0;
			}
		}
		k = 0;
		for(j = uvDataLenA/2;j < uvDataLenA - 10;j++)
		{
			if(uvDataA[i][j] >= UV_HEIGHT_THRES)
			{
				k ++;
				if(k >= UV_WIDTH_THRES)
				{
					uvRlt |= 1<<(i*2+1);
					break;
				}
			}
			else
			{
				k = 0;
			}
		}
	}
}
*/
