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
	int *pFvt;
	int *pf1;
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
	memset(colorFvtTotal, 0, sizeof(int)*COLOR_DATA_RESIZE*COLOR_FIV_DIM*COLOR_DATA_NUM);

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
		pFvt = (int *)USD_colorFvt_Int;
		Class = USD_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_EUR
	if (noteType == INDEX_EUR)
	{
		pNoteClass = g_EUR_Color_noteClass;
		pFvt = (int *)EUR_colorFvt_Int;
		Class = EUR_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_RUB
	if (noteType == INDEX_RUB)
	{
		pNoteClass = g_RUB_Color_noteClass;
		pFvt = (int *)RUB_colorFvt_Int;
		Class = RUB_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_TRY
	if (noteType == INDEX_TRY)
	{
		pNoteClass = g_TRY_Color_noteClass;
		pFvt = (int *)TRY_colorFvt_Int;
		Class = TRY_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_IQD
	if (noteType == INDEX_IQD)
	{
		pNoteClass = g_IQD_noteClass;
		pFvt = (int *)IQD_colorFvt_Int;
		Class = IQD_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_SAR
	if (noteType == INDEX_SAR)
	{
		pNoteClass = g_SAR_noteClass;
		pFvt = (int *)SAR_colorFvt_Int;
		Class = SAR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_AED
	if (noteType == INDEX_AED)
	{
		pNoteClass = g_AED_noteClass;
		pFvt = (int *)AED_colorFvt_Int;
		Class = AED_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_GBP
	if (noteType == INDEX_GBP)
	{
		pNoteClass = g_GBP_Color_noteClass;
		pFvt = (int *)GBP_colorFvt_Int;
		Class = GBP_COLOR_NOTE_CLASS;
	}
#endif
#ifdef  BILL_INDEX_ARS
	if (noteType == INDEX_ARS)
	{
		pNoteClass = g_ARS_noteClass;
		pFvt = (int *)ARS_colorFvt_Int;
		Class = ARS_NOTE_CLASS;
	}
#endif
	max_t = 0.0;
	for (i = 0; i < Class; i++)
	{
		fvtInt = 0;
		for (j = 0; j < COLOR_DATA_RESIZE*COLOR_FIV_DIM*COLOR_DATA_NUM; j++)
		{
			t0 = (int)pf1[j];
			t1 = (int)pFvt[j*Class+i];
			fvtInt += t0*t1;
		}
		fvt = ((double)(fvtInt))/100000;
		fvt += ((double)(pFvt[j*Class+i]*200))/100000;
		
		tt = exp(-fvt);	
		fvt = 1/(1+tt);
		
		if (max_t < fvt)
		{
			max_t = fvt;
			min_i = pNoteClass[i];
		}
	}

	colorJudgeValue = min_i;
	colorJudgeFlag = 0;//min_i%4;

#ifdef DRAW_STATE
	for (i = 0; i < 12; i++)
	{
		Display_Proj1(colorData_tmp[i],COLOR_DATA_RESIZE,600,0+i*60,0,0);
	}
#endif
	return 0;
}

//最小二乘法直线拟合
I32 LwCalculateLineKD(I32 *x,I32 *y,I32 n,float *k,float *d)
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
		if (i == t)
		{
			continue;
		}
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


u8 billIrad_Judge(u8 *lengthData_Tmp, int noteType)
{
	int i, j, k, sum, count, count1;
	short sx, ex, sw, sh, sy, ey;


	u8 *pImg;
	double fvt, tt, max_t;
	short *pFvt;
	u8 *pNoteClass, *pf1;
	u8 Class, min_i;
	int fvtInt, Max;

	pImg = (u8 *)lengthData;
	billIradMask = 0;

	if (lengthDataLen < 100||lengthDataLen > 500)
	{
		billIradMask = 1;
		return 0;
	}


#ifdef DRAW_STATE
	Draw_Gray_Image(pImg, IR_DATA_MAX_LEN, 21, 100, 20, 1);
#endif

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
	for (i = 0; i < 80; i++)
	{
		if (Max > projH[i])
		{
			count = 0;
			for (j = 0; j < 21; j++)
			{
				if (lengthData[j][max(i-2, 0)] > 240)
				{
					count ++;
				}
			}
			if (count > 8)
			{
				Max = projH[i];
				sx = i;
			}
			
		}
	}
	Max = 0;
	ex = lengthDataLen-8;
	for (i = lengthDataLen-3; i > lengthDataLen-80; i--)
	{
		if (Max < projH[i])
		{
			count = 0;
			for (j = 0; j < 21; j++)
			{
				if (lengthData[j][min(i+2, lengthDataLen-1)] > 240)
				{
					count ++;
				}
			}
			if (count > 8)
			{
				Max = projH[i];
				ex = i;
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
		if (count < lengthDataLen/3 && count1 < lengthDataLen/3)
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
			if (lengthData[i][j+0] == 0)
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
	sw = k/sh;
	iradImgW = sw;
	iradImgH = sh;
	memset(lengthData_Tmp2, 0, IRAD_FVT_DIM);
	ResizeCharImgGray(lengthData_Tmp,sw,sh, lengthData_Tmp2, IRAD_DATA_RESIZE_W,IRAD_DATA_RESIZE_H);
	//sh = 20;


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
	max_t = 0.0;
	for (i = 0; i < Class; i++)
	{
		fvtInt = 0;
		for (j = 0; j < IRAD_FVT_DIM; j++)
		{
			fvtInt += (pf1[j]*pFvt[j*Class+i]);
		}
		fvt = ((double)(fvtInt))/100000;
		fvt += ((double)(pFvt[j*Class+i]*200))/100000;

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

	return 0;
}




u8 billMG_Judge(int noteType)
{
	int i, Max0, Min0, Max1, Min1;
	if (mgDataLen < 80 || mgDataLen > 850)
	{
		mgFvtFlag = 1;
		return 0;
	}

	Max0 = 0;
	Min0 = 255*10;

	Max1 = 0;
	Min1 = 255*10;

	for (i = 4; i < mgDataLen -4; i++)
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
	}
#ifdef DRAW_STATE2
	Display_Proj_BYTE(mgData[0], mgDataLen, 0, 0, 1, 0);

	Display_Proj_BYTE(mgData[1], mgDataLen, 0, 255, 1, 0);
	Display_Int(Max0-Min0, 10, 10);
	Display_Int(Max1-Min1, 10, 256);
#endif	

	mgFvtFlag = 0;
	if (noteType == INDEX_EUR || noteType == INDEX_TRY)
	{
		if (Max0-Min0 < 120 && Max1-Min1 < 120)
		{
			mgFvtFlag = 1;
		}
	}
	else if (noteType == INDEX_USD)
	{
		if (Max0-Min0 < 70 && Max1-Min1 < 70)
		{
		//	mgFvtFlag = 1;
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
