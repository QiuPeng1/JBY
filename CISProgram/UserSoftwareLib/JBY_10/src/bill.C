/*包含私有头文件 */
#include "_bill.h"
#include <math.h>

/***********************************************/
#ifdef  BILL_INDEX_USD
	#include "LW_USD_ValueFvt.h"
	#include "LW_USD_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_EUR
	#include "LW_EUR_ValueFvt.h"
	#include "LW_EUR_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_RUB
	#include "LW_RUB_ValueFvt.h"
	#include "LW_RUB_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_TRY
	#include "LW_TRY_ValueFvt.h"
	#include "LW_TRY_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_IQD
	#include "LW_IQD_ValueFvt.h"
	#include "LW_IQD_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_SAR
	#include "LW_SAR_ValueFvt.h"
	#include "LW_SAR_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_AED
	#include "LW_AED_ValueFvt.h"
	#include "LW_AED_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_GBP
#include "LW_GBP_ValueFvt.h"
#include "LW_GBP_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_ARS
#include "LW_ARS_ValueFvt.h"
#include "LW_ARS_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_THB
#include "LW_THB_ValueFvt.h"
#include "LW_THB_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_TWD
#include "LW_TWD_ValueFvt.h"
#include "LW_TWD_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_CNY
#include "LW_CNY_ValueFvt.h"
#include "LW_CNY_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_BYR
#include "LW_BYR_ValueFvt.h"
#include "LW_BYR_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_KZT
#include "LW_KZT_ValueFvt.h"
#include "LW_KZT_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_UZS
#include "LW_UZS_ValueFvt.h"
#include "LW_UZS_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_MAD
#include "LW_MAD_ValueFvt.h"
#include "LW_MAD_ColorFvt.h"
#endif
/***********************************************/
#ifdef  BILL_INDEX_UAH
#include "LW_UAH_ValueFvt.h"
#include "LW_UAH_ColorFvt.h"
#endif
/***********************************************/

//#define DRAW_STATE
//#define DRAW_STATE2


#ifdef DRAW_STATE1
u8 pImg0[50*3*100];
u8 pImg1[50*3*100];
u8 pImg2[50*3*100];
u8 pImg3[50*3*100];	
#endif
/*公开的子程序*/
//---------------------------------------------------------------------
//函数介绍： 
//---------------------------------------------------------------------

u8 billRGB_Judge(int noteType)
{
	s16 i, j, m;
	int r, g, b, t0, t1;
	int min_i;

	double fvt, tt, max_t;
	short *pFvt;
	short *pf1;
	u8 *pNoteClass;
	u8 Class;
	int fvtInt;
	m = 2;
	if (colorDataLen < 50 || colorDataLen > 180)
	{
		colorJudgeValue = 0xff;
		colorJudgeFlag = 0xff;
		return 0;
	}

	//memset(colorFvtTotal, 0, sizeof(short)*COLOR_DATA_RESIZE*2*4);
	memset(colorFvtTotal, 0, sizeof(short)*COLOR_DATA_RESIZE*COLOR_FIV_DIM*COLOR_DATA_NUM);

	for (i = 0; i < 12; i++)
	{
		ResizeData(colorData[i]+20, colorDataLen-24, colorData_tmp[i], COLOR_DATA_RESIZE);
	}

	for (i = 0; i < COLOR_DATA_NUM; i++)
	{
		for (j = 0; j < COLOR_DATA_RESIZE; j++)
		{
			r = colorData_tmp[i*3+0][j];
			g = colorData_tmp[i*3+1][j];
			b = colorData_tmp[i*3+2][j];
			
			//t = r*500/(g+1);
			colorFvtTotal[i*COLOR_DATA_RESIZE*COLOR_FIV_DIM+COLOR_FIV_DIM*j+0] = r/m;
			//t = b*500/(g+1);
			colorFvtTotal[i*COLOR_DATA_RESIZE*COLOR_FIV_DIM+COLOR_FIV_DIM*j+1] = g/m;
			colorFvtTotal[i*COLOR_DATA_RESIZE*COLOR_FIV_DIM+COLOR_FIV_DIM*j+2] = b/m;
		}
	}
#ifdef DRAW_STATE1
	
	for (i = 0; i < 50; i++)
	{
		for (j = 0; j < COLOR_DATA_RESIZE; j++)
		{
			pImg0[3*(i*COLOR_DATA_RESIZE+j)+2] = min(255,colorData_tmp[0][j]/m);
			pImg0[3*(i*COLOR_DATA_RESIZE+j)+1] = min(255,colorData_tmp[1][j]/m);
			pImg0[3*(i*COLOR_DATA_RESIZE+j)+0] = min(255,colorData_tmp[2][j]/m);
			
			pImg1[3*(i*COLOR_DATA_RESIZE+j)+2] = min(255,colorData_tmp[3][j]/m);
			pImg1[3*(i*COLOR_DATA_RESIZE+j)+1] = min(255,colorData_tmp[4][j]/m);
			pImg1[3*(i*COLOR_DATA_RESIZE+j)+0] = min(255,colorData_tmp[5][j]/m);
			
			pImg2[3*(i*COLOR_DATA_RESIZE+j)+2] = min(255,colorData_tmp[6][j]/m);
			pImg2[3*(i*COLOR_DATA_RESIZE+j)+1] = min(255,colorData_tmp[7][j]/m);
			pImg2[3*(i*COLOR_DATA_RESIZE+j)+0] = min(255,colorData_tmp[8][j]/m);
			
			pImg3[3*(i*COLOR_DATA_RESIZE+j)+2] = min(255,colorData_tmp[9][j]/m);
			pImg3[3*(i*COLOR_DATA_RESIZE+j)+1] = min(255,colorData_tmp[10][j]/m);
			pImg3[3*(i*COLOR_DATA_RESIZE+j)+0] = min(255,colorData_tmp[11][j]/m);

		}
	}
#endif
//	return;
	pf1 = colorFvtTotal;

#ifdef  BILL_INDEX_USD
	if (noteType == INDEX_USD)
	{
		pNoteClass = g_USD_Color_noteClass;
		pFvt = (short *)USD_colorFvt_Int;
		Class = USD_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_EUR
	if (noteType == INDEX_EUR)
	{
		pNoteClass = g_EUR_Color_noteClass;
		pFvt = (short *)EUR_colorFvt_Int;
		Class = EUR_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_RUB
	if (noteType == INDEX_RUB)
	{
		pNoteClass = g_RUB_Color_noteClass;
		pFvt = (short *)RUB_colorFvt_Int;
		Class = RUB_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_TRY
	if (noteType == INDEX_TRY)
	{
		pNoteClass = g_TRY_Color_noteClass;
		pFvt = (short *)TRY_colorFvt_Int;
		Class = TRY_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_IQD
	if (noteType == INDEX_IQD)
	{
		pNoteClass = g_IQD_Color_noteClass;
		pFvt = (short *)IQD_colorFvt_Int;
		Class = IQD_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_SAR
	if (noteType == INDEX_SAR)
	{
		pNoteClass = g_SAR_Color_noteClass;
		pFvt = (short *)SAR_colorFvt_Int;
		Class = SAR_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_AED
	if (noteType == INDEX_AED)
	{
		pNoteClass = g_AED_Color_noteClass;
		pFvt = (short *)AED_colorFvt_Int;
		Class = AED_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_GBP
	if (noteType == INDEX_GBP)
	{
		pNoteClass = g_GBP_Color_noteClass;
		pFvt = (short *)GBP_colorFvt_Int;
		Class = GBP_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_ARS
	if (noteType == INDEX_ARS)
	{
		pNoteClass = g_ARS_Color_noteClass;
		pFvt = (short *)ARS_colorFvt_Int;
		Class = ARS_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_THB
	if (noteType == INDEX_THB)
	{
		pNoteClass = g_THB_Color_noteClass;
		pFvt = (short *)THB_colorFvt_Int;
		Class = THB_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_TWD
	if (noteType == INDEX_TWD)
	{
		pNoteClass = g_TWD_Color_noteClass;
		pFvt = (short *)TWD_colorFvt_Int;
		Class = TWD_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_CNY
	if (noteType == INDEX_CNY)
	{
		pNoteClass = g_CNY_Color_noteClass;
		pFvt = (short *)CNY_colorFvt_Int;
		Class = CNY_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_UZS
	if (noteType == INDEX_UZS)
	{
		pNoteClass = g_UZS_Color_noteClass;
		pFvt = (short *)UZS_colorFvt_Int;
		Class = UZS_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_BYR
	if (noteType == INDEX_BYR)
	{
		pNoteClass = g_BYR_Color_noteClass;
		pFvt = (short *)BYR_colorFvt_Int;
		Class = BYR_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_KZT
	if (noteType == INDEX_KZT)
	{
		pNoteClass = g_KZT_Color_noteClass;
		pFvt = (short *)KZT_colorFvt_Int;
		Class = KZT_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_MAD
	if (noteType == INDEX_MAD)
	{
		pNoteClass = g_MAD_Color_noteClass;
		pFvt = (short *)MAD_colorFvt_Int;
		Class = MAD_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_UAH
	if (noteType == INDEX_UAH)
	{
		pNoteClass = g_UAH_Color_noteClass;
		pFvt = (short *)UAH_colorFvt_Int;
		Class = UAH_COLOR_NOTE_CLASS;
	}
#endif
	max_t = 0.0;
	for (i = 0; i < Class; i++)
	{
		fvtInt = 0;
		for (j = 0; j < COLOR_DATA_RESIZE*COLOR_FIV_DIM*COLOR_DATA_NUM; j++)
		{
			fvtInt += (pf1[j]*pFvt[j*Class+i]);
		}
		fvt = ((double)(fvtInt))/50000;
		fvt += ((double)(pFvt[j*Class+i]*200))/50000;
		
		tt = exp(-fvt);	
		fvt = 1/(1+tt);
		
		if (max_t < fvt)
		{
			max_t = fvt;
			min_i = pNoteClass[i];
		}
	}

	if (max_t < 0.005)
	{
	//	min_i = 50;
	}
	colorJudgeValue = min_i;
	colorJudgeFlag = 0;//min_i%4;

#ifdef DRAW_STATE2
	for (i = 0; i < 12; i++)
	{
		Display_Proj1(colorData_tmp[i],COLOR_DATA_RESIZE,600,0+i*60,0,0);
	}
#endif
	return 0;
}

//最小二乘法直线拟合
I32 LwCalculateLineKD(short *x,short *y,I32 n,float *k,float *d)
{
	//拟合直线方程(Y=kX+b)
	float mX,mY,mXX,mXY;
	I32 i, Max, t, count;
	
	if(n < 2)
	{
		return 0;
	}
	
	Max = 0;
	t = 0;
	for (i = 0; i < n; i++)
	{
		if (Max < y[i])
		{
			Max = y[i];
			t = i;
		}
	}
	mX = mY = mXX = mXY = 0;
	count = 0;
	for(i = 0; i < n; i++)
	{
		
		count++;
		mX += x[i];
		mY += y[i];
		mXX += x[i]*x[i];
		mXY += x[i]*y[i];
	}
	
	if(mX*mX-mXX*count == 0)
	{
		return 0;
	}
	
	*k = (mY*mX-mXY*count)/(mX*mX-mXX*count);
	*d = (mY-mX*(*k))/count;
	
	return 1;
}

short pointX[IR_DATA_MAX_LEN], pointY[IR_DATA_MAX_LEN];
u8 billIrad_Judge(u8 *lengthData_Tmp, int noteType)
{
	int i, j, k, sum, count, count1, t1;
	short sx, ex, sw, sh, sy, ey, t, wirePos;
	int Min, MinPos, Max0, Max1, Max, MaxPos, whitePaperVal,iradAve;
	static POS_INFOR posMin[21];
	u8 *pImg;
	double fvt, tt, max_t;
	short *pFvt;
	u8 *pNoteClass, *pf1;
	u8 Class, min_i;
	int fvtInt, line_n1;
	int w, h, ret;
	float kk, d;
	pImg = (u8 *)lengthData;
	billIradMask = 0;

	if (lengthDataLen < 190||lengthDataLen > 500)
	{
		billIradMask = 1;
		return 0;
	}

#ifdef DRAW_STATE
	Draw_Gray_Image(pImg, IR_DATA_MAX_LEN, 21, 200, 100, 1);
	Draw_Line(200+ex,100,200+ex,230);
	Draw_Line(200+sx,100,200+sx,230);
	Draw_Line(200+sx, 100+sy, 200+ex, 100+sy);
#endif
	line_n1 = 0;
	w = lengthDataLen;
	h = 21;
	for(j=50;j<w-50;j+=8)
	{
		for(i=1;i<h/2;i++)
		{
			if(pImg[i*IR_DATA_MAX_LEN+j]< 200)
			{
				if(line_n1>100)
				{
					break;
				}
				pointY[line_n1]=(i+1)*32;
				pointX[line_n1]=j;
			
				line_n1++;
#ifdef DRAW_STATE
				Draw_Cross(200+j+1,100+i,2);
#endif
				break;
			}
			
		}
	}
	
	LwCalculateLineKD(pointX,pointY,line_n1,&kk,&d);
	ret = (int)(abs(atan(kk)*180/PI));
	memset(projH, 0, sizeof(int)*IR_DATA_MAX_LEN);
	
	for (i = 5; i < 21-5; i++)
	{
		for (j = 0; j < lengthDataLen; j++)
		{
			projH[j] += pImg[i*IR_DATA_MAX_LEN+j];
		}
	}

	for (i = 0; i < lengthDataLen-1; i++)
	{
		projH[i] = projH[i+1]-projH[i];
	}
	projH[i] = 0;
	sx = 8;
	Max = 99999999;
	for (i = 80; i > 0; i--)
	{
		if (Max > projH[i])
		{
			count = 0;
			for (j = 0; j < 21; j++)
			{
				if (lengthData[j][max(i-2, 0)] > 246)
				{
					count ++;
				}
			}
			if (count > 16)
			{
				Max = projH[i];
				sx = i;
				break;
			}
			
		}
	}
	Max = 0;
	ex = lengthDataLen-8;
	for (i = lengthDataLen-60; i < lengthDataLen-3; i++)
	{
		if (Max < projH[i])
		{
			count = 0;
			for (j = 0; j < 21; j++)
			{
				if (lengthData[j][min(i+2, lengthDataLen-1)] > 246)
				{
					count ++;
				}
			}
			if (count > 16)
			{
				Max = projH[i];
				ex = i;
				break;
			}
		}
	}
	sy = 0;
	ey = 21;
	
	for (i = 0; i < 21; i++)
	{
		count = 0;
		count1 = 0;
		for (j = 8; j < lengthDataLen-8; j++)
		{
			if(lengthData[i][j+0] > 240)
			{
				count++;
			}
		}
		for (j = 8; j < lengthDataLen-8; j++)
		{
			if(lengthData[i+1][j+0] > 240)
			{
				count1++;
			}
		}
		if (count < (lengthDataLen/3+18) && count1 < (lengthDataLen/3+18))
		{
			sy = i+1;
			break;
		}
	}

	for (i = 20; i > 0; i--)
	{
		count = 0;
		count1 = 0;
		for (j = 8; j < lengthDataLen-8; j++)
		{
			if(lengthData[i][j+0] > 240)
			{
				count++;
			}
		}
		for (j = 8; j < lengthDataLen-8; j++)
		{
			if(lengthData[i-1][j+0] > 240)
			{
				count1++;
			}
		}
		if (count < lengthDataLen/3 && count1 < lengthDataLen/3)
		{
			ey = i-1;
			break;
		}
	}
	billSyPos = sy;
#ifdef DRAW_STATE
	//Draw_Gray_Image(pImg, IR_DATA_MAX_LEN, 21, 200, 100, 1);
	Draw_Line(200+ex,100,200+ex,230);
	Draw_Line(200+sx,100,200+sx,230);
	Draw_Line(200+sx, 100+sy, 200+ex, 100+sy);
	Display_Int(ret, 200, 80);
#endif
//	ex = lengthDataLen-8;
//	for (i = lengthDataLen-8; i > lengthDataLen-)
//	{
//	}
//	ey = 21;
//	sy = 0;
	sh = ey-sy;
	k = 0;
	for (i = sy; i < ey; i++)
	{
		count = 0;
		for (j = 8; j < lengthDataLen-16; j++)
		{
			if (lengthData[i][j+0] < 30)
			{
				count++;
			}
		}
		if (count > lengthDataLen/5)
		{
		//	sh -= 1;
		//	continue;
		}
		for (j = sx; j < ex; j+=4)
		{
			sum = (lengthData[i][j+0]+lengthData[i][j+1]+lengthData[i][j+2]+lengthData[i][j+3])/4;
			lengthData_Tmp[k++] = sum;
		}
	}
	if (sh == 0)
	{
		billIradMask = 1;
		return 0;
	}
	isQingXie = 0;
	if (ret > 12)// && noteType == INDEX_USD)
	{
		isQingXie = 1;
	}
	sw = k/sh;
	iradImgW = sw;
	iradImgH = sh;
	memset(lengthData_Tmp2, 0, IRAD_FVT_DIM);
	ResizeCharImgGray(lengthData_Tmp,sw,sh, lengthData_Tmp2, IRAD_DATA_RESIZE_W,IRAD_DATA_RESIZE_H);
	//sh = 20;

#ifdef DRAW_STATE
	//Display_Int(count, 200, 100);
	Draw_Gray_Image(lengthData_Tmp2, IRAD_DATA_RESIZE_W,IRAD_DATA_RESIZE_H, 200, 50, 1);
	//Draw_Line(200+ex,100,200+ex,230);
	//Draw_Line(200+sx,100,200+sx,230);
	//Draw_Line(200+sx, 100+sy, 200+ex, 100+sy);
#endif
	
	count = 0;
	for (i = 0; i < IRAD_DATA_RESIZE_H; i++)
	{
		for (j = 0; j < IRAD_DATA_RESIZE_W; j++)
		{
			if (lengthData_Tmp2[i*IRAD_DATA_RESIZE_W+j]< 20)
			{
				count++;
#ifdef DRAW_STATE
				//Display_Int(count, 200, 100);
				Draw_Gray_Image(lengthData_Tmp2, IRAD_DATA_RESIZE_W,IRAD_DATA_RESIZE_H, 200, 150, 1);
				Draw_Cross(200+j, 50+i,2);
#endif
			}
		}
	}
#ifdef DRAW_STATE
	Display_Int(count, 240, 100);
	//Draw_Gray_Image(pImg, IR_DATA_MAX_LEN, 21, 200, 100, 1);
	//Draw_Line(200+ex,100,200+ex,230);
	//Draw_Line(200+sx,100,200+sx,230);
	//Draw_Line(200+sx, 100+sy, 200+ex, 100+sy);
#endif
	
	if (count > IRAD_DATA_RESIZE_W*IRAD_DATA_RESIZE_H/2 )
	{
		billIradMask = 1;
	}
//	return;
	pf1 = lengthData_Tmp2;
#ifdef  BILL_INDEX_USD
	if (noteType == INDEX_USD)
	{
		pNoteClass = g_USD_noteClass;
		pFvt = (short *)USD_iradFvt_Int;
		Class = USD_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_EUR
	if (noteType == INDEX_EUR)
	{
		pNoteClass = g_EUR_noteClass;
		pFvt = (short *)EUR_iradFvt_Int;
		Class = EUR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_RUB
	if (noteType == INDEX_RUB)
	{
		pNoteClass = g_RUB_noteClass;
		pFvt = (short *)RUB_iradFvt_Int;
		Class = RUB_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_TRY
	if (noteType == INDEX_TRY)
	{
		pNoteClass = g_TRY_noteClass;
		pFvt = (short *)TRY_iradFvt_Int;
		Class = TRY_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_IQD
	if (noteType == INDEX_IQD)
	{
		pNoteClass = g_IQD_noteClass;
		pFvt = (short *)IQD_iradFvt_Int;
		Class = IQD_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_SAR
	if (noteType == INDEX_SAR)
	{
		pNoteClass = g_SAR_noteClass;
		pFvt = (short *)SAR_iradFvt_Int;
		Class = SAR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_AED
	if (noteType == INDEX_AED)
	{
		pNoteClass = g_AED_noteClass;
		pFvt = (short *)AED_iradFvt_Int;
		Class = AED_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_GBP
	if (noteType == INDEX_GBP)
	{
		pNoteClass = g_GBP_noteClass;
		pFvt = (short *)GBP_iradFvt_Int;
		Class = GBP_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_ARS
	if (noteType == INDEX_ARS)
	{
		pNoteClass = g_ARS_noteClass;
		pFvt = (short *)ARS_iradFvt_Int;
		Class = ARS_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_THB
	if (noteType == INDEX_THB)
	{
		pNoteClass = g_THB_noteClass;
		pFvt = (short *)THB_iradFvt_Int;
		Class = THB_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_TWD
	if (noteType == INDEX_TWD)
	{
		pNoteClass = g_TWD_noteClass;
		pFvt = (short *)TWD_iradFvt_Int;
		Class = TWD_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_CNY
	if (noteType == INDEX_CNY)
	{
		pNoteClass = g_CNY_noteClass;
		pFvt = (short *)CNY_iradFvt_Int;
		Class = CNY_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_BYR
	if (noteType == INDEX_BYR)
	{
		pNoteClass = g_BYR_noteClass;
		pFvt = (short *)BYR_iradFvt_Int;
		Class = BYR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_KZT
	if (noteType == INDEX_KZT)
	{
		pNoteClass = g_KZT_noteClass;
		pFvt = (short *)KZT_iradFvt_Int;
		Class = KZT_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_UZS
	if (noteType == INDEX_UZS)
	{
		pNoteClass = g_UZS_noteClass;
		pFvt = (short *)UZS_iradFvt_Int;
		Class = UZS_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_MAD
	if (noteType == INDEX_MAD)
	{
		pNoteClass = g_MAD_noteClass;
		pFvt = (short *)MAD_iradFvt_Int;
		Class = MAD_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_UAH
	if (noteType == INDEX_UAH)
	{
		pNoteClass = g_UAH_noteClass;
		pFvt = (short *)UAH_iradFvt_Int;
		Class = UAH_NOTE_CLASS;
	}
#endif
	max_t = 0.0;
	for (i = 0; i < Class; i++)
	{
		fvtInt = 0;
		for (j = 0; j < IRAD_FVT_DIM; j++)
		{
			fvtInt += (pf1[j]*pFvt[j*Class+i]);
		}
		fvt = ((double)(fvtInt))/50000;
		fvt += ((double)(pFvt[j*Class+i]*200))/50000;

		tt = exp(-fvt);	
		fvt = 1/(1+tt);
		
		if (max_t < fvt)
		{
			max_t = fvt;
			min_i = pNoteClass[i];
		}
	}
	g_IradRes = min_i;
	billValue = g_IradRes;
	billFlag = 0;//g_IradRes%4;
	if (max_t < 0.005)
	{
		g_IradRes = 0xff;
		billValue = 0xff;
		billFlag = 0;//g_IradRes%4;
	}


	if (noteType == INDEX_CNY)
	{
		memset(projH, 0, sizeof(int)*IR_DATA_MAX_LEN);
		for (i = sy; i < ey; i++)
		{
			for (j = 0; j < lengthDataLen; j++)
			{
				projH[j] += pImg[i*IR_DATA_MAX_LEN+j];
			}
		}
#ifdef DRAW_STATE
		Display_Proj(projH, lengthDataLen, 1200, 14+200, 0, 0);
#endif
		Min = 99999;
		MinPos = lengthDataLen/2;
		for (i = sx+82; i < ex-80; i++)
		{
			if (Min > projH[i])
			{
				Min = projH[i];
				MinPos = i;
			}
		}
		
		t = MinPos;
		wirePos = t;
		for (i = 0; i < lengthDataLen-1; i++)
		{
			projH1[i] = projH[i+1]-projH[i];
		}
		projH1[i] = 0;
#ifdef DRAW_STATE
		Display_Proj(projH1, lengthDataLen, 1200, 100+14+200, 0, 0);
#endif
		Min = 99999;
		Max = 0;
		
		for (i = t-15; i < t+15; i++)
		{
			if (Min > projH1[i])
			{
				Min = projH1[i];
				MinPos = i;
			}
			
			if (Max < projH1[i])
			{
				Max = projH1[i];
				MaxPos = i;
			}
		}
#ifdef DRAW_STATE
		Draw_Line(MinPos+1200, 0+200, MinPos+1200, 200+200);
		Draw_Line(MaxPos+1200, 0+200, MaxPos+1200, 200+200);
		Display_Int(Max-Min, 0+1200-40, 0+200);
		Display_Int(abs(MaxPos-MinPos), 0+1200-40, 20+200);
#endif
		
		if (((Max-Min) < 100 || abs(MaxPos-MinPos) > 23) & (billValue != 15))
		{
			billIradMask = 1;
		}
#ifdef DRAW_STATE
		for (i = 0; i < 21; i++)
		{
			Display_Proj1(lengthData[i],lengthDataLen,0,0+i*60,0,0);
		}
		Display_Int(lengthDataLen, 0, 60);
#endif
		if (wirePos < 20)
		{
			wirePos = 20;
		}
		if (wirePos+20 > lengthDataLen)
		{
			wirePos = lengthDataLen-20;
		}
		
	
		if (billValue == 0 || billValue == 4 || billValue == 7 || billValue == 10 || billValue < 6)
		{
			count1 = 0;
			if (billValue == 0 || billValue == 4 || billValue == 7 || billValue == 10)
			{
				if (wirePos<(ex-sx)/2)
				{
					for (i = sy, k = 0; i < ey; i++, k++)
					{
						sum = 0;
						count = 0;
						Min = 255;
						count1 ++;
						for (j = ex-80; j < ex; j++)
						{
							sum += lengthData[i][j];
							count++;
							if (Min > lengthData[i][j])
							{
								Min = lengthData[i][j];
								MinPos = j;
							}
						}
						posMin[k].index = i;
						posMin[k].pos = MinPos;
						posMin[k].val = Min;
						sum /= count;
						posMin[k].ave = sum;
						iradAve += sum;
						
	#ifdef DRAW_STATE
						
						Display_Int(sum, 0, i*60);
						Display_Int(Min, 0, i*60+20);
						Draw_Line(MinPos, i*60, MinPos, (i+1)*60);
						Draw_BlueLine(MinPos-5, i*60, MinPos-5, (i+1)*60);
						Draw_BlueLine(MinPos+5, i*60, MinPos+5, (i+1)*60);
	#endif
					}
				}
				else
				{
					for (i = sy, k = 0; i < ey; i++, k++)
					{
						sum = 0;
						count = 0;
						Min = 255;
						count1 ++;
						for (j = sx; j < sx+80; j++)
							//for (j = 60; j < dataIradLen-60; j++)
						{
							sum += lengthData[i][j];
							count++;
							if (Min > lengthData[i][j])
							{
								Min = lengthData[i][j];
								MinPos = j;
							}
						}
						posMin[k].index = i;
						posMin[k].pos = MinPos;
						posMin[k].val = Min;
						sum /= count;
						posMin[k].ave = sum;
						iradAve += sum;
						
	#ifdef DRAW_STATE
						
						Display_Int(sum, 0, i*60);
						Display_Int(Min, 0, i*60+20);
						Draw_Line(MinPos, i*60, MinPos, (i+1)*60);
						Draw_BlueLine(MinPos-5, i*60, MinPos-5, (i+1)*60);
						Draw_BlueLine(MinPos+5, i*60, MinPos+5, (i+1)*60);
	#endif
					}
				}
			}
			else
			{
				for (i = sy, k = 0; i < ey; i++, k++)
				{
					sum = 0;
					count = 0;
					Min = 255;
					count1 ++;
					for (j = wirePos-20; j < wirePos+20; j++)
						//for (j = 60; j < dataIradLen-60; j++)
					{
						sum += lengthData[i][j];
						count++;
						if (Min > lengthData[i][j])
						{
							Min = lengthData[i][j];
							MinPos = j;
						}
					}
					posMin[k].index = i;
					posMin[k].pos = MinPos;
					posMin[k].val = Min;
					sum /= count;
					posMin[k].ave = sum;
					iradAve += sum;
					
		#ifdef DRAW_STATE
					
					Display_Int(sum, 0, i*60);
					Display_Int(Min, 0, i*60+20);
					Draw_Line(MinPos, i*60, MinPos, (i+1)*60);
					Draw_BlueLine(MinPos-5, i*60, MinPos-5, (i+1)*60);
					Draw_BlueLine(MinPos+5, i*60, MinPos+5, (i+1)*60);
		#endif
				}
			}
			
			t = 0;
			sum = 0;
			for (i = 1; i < count1; i++)
			{
				if (abs(posMin[i].pos-posMin[count1/2].pos) < 16)
				{
					t++;
					//posMin[i].mask = 1;
				}
				sum += (posMin[i].pos-posMin[count1/2].pos);
			}
			if (count1 > 1)
			{
				iradAve = sum/(count1-1);
				sum = 0;
				for (i = 1; i < count1; i++)
				{
		
					sum += (posMin[i].pos-posMin[count1/2].pos-iradAve)*(posMin[i].pos-posMin[count1/2].pos-iradAve);
				}
				sum = sqrt(sum)*1000/(count1-1);
			}
			else
			{
				billIradMask = 1;
			}

			t1 = 1200;
			if (billValue == 0 || billValue == 4 || billValue == 7 || billValue == 10)
			{
				t1 = 1600;
			}
			if (t < 10 || sum > t1)
			{
				billIradMask = 1;
			}
	#ifdef DRAW_STATE
			
			Display_Int(t, 200, 0);
			Display_Int(sum, 200, 20);

	#endif
		}
	}
	return 0;
}




u8 billMG_Judge(int noteType)
{
	int i, Max0, Min0, Max1, Min1,sum;
	mgFvtFlag = 0;
	if (mgDataLen < 80 || mgDataLen > 850)
	{
		mgFvtFlag = 1;
		return 0;
	}

	Max0 = 0;
	Min0 = 255*10;
	
	Max1 = 0;
	Min1 = 255*10;

	sum = 0;
	for (i = 16; i < mgDataLen -16; i++)
	{
		if (Max0 < mgData[0][i])
		{
			Max0 = mgData[0][i];
		}
		if (Min0 > mgData[0][i])
		{
			Min0 = mgData[0][i];
		}

		if (Max1 < mgData[1][i])
		{
			Max1 = mgData[1][i];
		}
		if (Min1 > mgData[1][i])
		{
			Min1 = mgData[1][i];
		}
		if (mgData[0][i] > 220 || mgData[1][i] > 220)
		{
			sum ++;
		}
	}
#ifdef DRAW_STATE2
	Display_Proj_BYTE(mgData[0], mgDataLen, 0, 0, 1, 0);

	Display_Proj_BYTE(mgData[1], mgDataLen, 0, 255, 1, 0);
	Display_Int(Max0-Min0, 10, 10);
	Display_Int(sum, 40, 10);
	Display_Int(Max1-Min1, 10, 256);
#endif	

	
	if (noteType == INDEX_EUR)
	{
		if (Max0-Min0 < 120 && Max1-Min1 < 120)
		{
			mgFvtFlag = 1;
		}
	}
	else if (noteType == INDEX_TRY)
	{
		if (Max0-Min0 < 200 && Max1-Min1 < 200)
		{
			mgFvtFlag = 1;
		}
		if (sum < 1)
		{
			mgFvtFlag = 1;
		}
	}
	else if (noteType == INDEX_USD)
	{
		if (Max0-Min0 < 130 && Max1-Min1 < 130)
		{
			mgFvtFlag = 1;
		}
	}
	else if (noteType == INDEX_RUB)
	{
		if (billValue < 10)
		{
			if (Max0-Min0 < 70 && Max1-Min1 < 70)
			{
				//mgFvtFlag = 1;
			}
		}
	}
	return 0;
}

u8 billUV_Judge(int noteType, int uvThre)
{
	int i, Max0, Min0, Max1, Min1, pos0, pos1, t, count;
	billUVFvt = 0;
	if (uvDataLen < 80)// || uvDataLen > 450)
	{
		//billUVFvt = 1;
		return 0;
	}


	if ( uvDataLen > 450)
	{
		uvDataLen = 450;
		//return 0;
	}

	for(i = 0; i < uvDataLen; i++)
	{
		projH1[i] = uvData[i];
	}

	FilterAverage_2(projH1,uvDataLen);

	for (i = 0; i < uvDataLen; i++)
	{
		projH[i] = projH1[i+1]-projH1[i];
	}
	

	Max0 = 0;
	Min0 = 255*10;
	
	Max1 = 0;
	Min1 = 255*10;
	pos0 = pos1 = 1;
	for (i = 16; i < uvDataLen/3; i++)
	{
		if (Max0 < projH[i])
		{
			Max0 = projH[i];
			pos0 = i;
		}

	
	}

	for (i = uvDataLen*2/3; i < uvDataLen -16; i++)
	{
		if (Max1 < projH[i])
		{
			Max1 = projH[i];
			pos1 = i;
		}
		
	}

	count = 1;
	t = 0;
	for (i = pos0; i < pos1; i++)
	{
		t += projH1[i];
		count++;
	}
	t /= count;

	billUVFvt = 0;
	if (noteType == INDEX_RUB)
	{
		if (t > uvThre)
		{
			billUVFvt = 1;
		}
	}
	else
	{
		if (t > uvThre)
		{
			billUVFvt = 1;
		}
	}
	if (noteType == INDEX_CNY)
	{
		billUVFvt = 0;
	}
	/*
	else if (noteType == INDEX_TRY)
	{
		if (t > 100)
		{
			billUVFvt = 1;
		}
	}
	else if(noteType == INDEX_USD)
	{
		if (t > 100)
		{
			billUVFvt = 1;
		}
	}*/
	
#ifdef DRAW_STATE2
	Display_Proj(projH1,uvDataLen,400, 0, 0, 0);
	Display_Proj(projH,uvDataLen,400, 100, 0, 0);
	Display_Proj_BYTE(uvData, uvDataLen, 0, 0, 1, 0);
	Draw_Line(pos0, 0, pos0, 255);
	Draw_Line(pos1, 0, pos1, 255);
	Display_Int(t, 10, 10);
	Display_Int(Max1-Min1, 10, 256);
#endif
	return 0;
}

void FilterAverage_2(I32 *data,I32 l)
{
	register I32 i;
	
	for (i = 2; i < l-2; i++)
	{
		data[i] = (data[i-2]+data[i-1]+data[i]+data[i+1]+data[i+2])/5;
	}
}

void ResizeData(const u16 *pOldData,I32 len,u16 *pNewData, I32 newLen)
{
	I32 i,tx,xx,dxi;
	I32 t;


	for (i = 0; i < newLen; i++)
	{
		tx = i*1024*(len)/(newLen);
		xx = tx>>10;
		dxi=tx-xx*1024;
		t = ((((I32)pOldData[xx+1]-(I32)pOldData[xx])*dxi)>>10)+(((I32)pOldData[xx]-(I32)pOldData[xx+1])*dxi>>20)+(I32)pOldData[xx];
		if (t > 255)
		{
		//	t = 255;
		}
		if (t <= 0)
		{
			t = 0;
		}
		pNewData[i] = t;
	}
	
}

void ResizeCharImgGray(u8 *pOldImg,int oldImgW,int oldImgH, u8 *pNewImg, int newImgW,int newImgH)
{
	I32 i,j,tx,ty,xx,yy,dxi,dyi;
	I32 t;
	u8 *Img = pOldImg;
	I32 X;
	
	X = oldImgW;
	for(i = 0; i < newImgH; i++)
	{
		for(j = 0;j < newImgW; j++)
		{
			ty = i*1024*(oldImgH-1)/(newImgH-1); 
			tx = j*1024*(oldImgW-1)/(newImgW-1);
			xx = tx>>10;
			yy = ty>>10;
			dxi=tx-xx*1024;
			dyi=ty-yy*1024;
			
			t = ((((I32)Img[((yy+1)*X)+xx]-(I32)Img[(yy*X)+xx])*dyi +((I32)Img[(yy*X)+xx+1]-(I32)Img[(yy*X)+xx])*dxi)>>10)+\
				(((I32)Img[((yy+1)*X)+xx+1]+(I32)Img[(yy*X)+xx]-(I32)Img[(yy*X)+xx+1]-(I32)Img[((yy+1)*X)+xx])*dxi*dyi>>20)+\
				(I32)Img[(yy*X)+xx];
			if (t >= 255)
			{
				t = 255;
			}

			if (t <= 0)
			{
				t = 0;
			}
			pNewImg[i*newImgW+j] = t;
		}
	}
	
}
