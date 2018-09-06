/*包含私有头文件 */
#include "_bill.h"
#include <math.h>
#include "LW_USD_ValueFvt.h"
#include "LW_USD_ColorFvt.h"
#include "LW_EUR_ValueFvt.h"
#include "LW_EUR_ColorFvt.h"

#include "LW_RUB_ValueFvt.h"
#include "LW_RUB_ColorFvt.h"

#include "LW_TRY_ValueFvt.h"
#include "LW_TRY_ColorFvt.h"
//#define DRAW_STATE
//#define DRAW_STATE1

#ifdef DRAW_STATE1
u8 pImg0[500*3*500], pImg1[500*3*500];
u8 pImg2[500*3*500], pImg3[500*3*500];	
#endif
/*公开的子程序*/
//---------------------------------------------------------------------
//函数介绍： 
//---------------------------------------------------------------------

u8 billRGB_Judge(int noteType)
{
	s16 i, j;
	int r, g, b, t, t0, t1;
	int min_i;

	double fvt, tt, max_t;
	short *pFvt;
	short *pf1;
	u8 *pNoteClass;
	u8 Class;
	int fvtInt;

	if (colorDataLen < 50 || colorDataLen > 180)
	{
		colorJudgeValue = 0xff;
		colorJudgeFlag = 0xff;
		return 0;
	}

	memset(colorFvtTotal, 0, sizeof(short)*COLOR_DATA_RESIZE*2*4);
	
	for (i = 0; i < 12; i++)
	{
		ResizeData(colorData[i]+12, colorDataLen-12, colorData_tmp[i], COLOR_DATA_RESIZE);
	}
#ifdef DRAW_STATE1
	for (i = 0; i < 50; i++)
	{
		for (j = 0; j < COLOR_DATA_RESIZE; j++)
		{
			pImg0[3*(i*COLOR_DATA_RESIZE+j)+2] = colorData_tmp[0][j];
			pImg0[3*(i*COLOR_DATA_RESIZE+j)+1] = colorData_tmp[1][j];
			pImg0[3*(i*COLOR_DATA_RESIZE+j)+0] = colorData_tmp[2][j];
			
			pImg1[3*(i*COLOR_DATA_RESIZE+j)+2] = colorData_tmp[3][j];
			pImg1[3*(i*COLOR_DATA_RESIZE+j)+1] = colorData_tmp[4][j];
			pImg1[3*(i*COLOR_DATA_RESIZE+j)+0] = colorData_tmp[5][j];
			
			pImg2[3*(i*COLOR_DATA_RESIZE+j)+2] = colorData_tmp[6][j];
			pImg2[3*(i*COLOR_DATA_RESIZE+j)+1] = colorData_tmp[7][j];
			pImg2[3*(i*COLOR_DATA_RESIZE+j)+0] = colorData_tmp[8][j];
			
			pImg3[3*(i*COLOR_DATA_RESIZE+j)+2] = colorData_tmp[9][j];
			pImg3[3*(i*COLOR_DATA_RESIZE+j)+1] = colorData_tmp[10][j];
			pImg3[3*(i*COLOR_DATA_RESIZE+j)+0] = colorData_tmp[11][j];
		}
	}

	Draw_TrueColor_Image(pImg0,COLOR_DATA_RESIZE,50,900,120);
	Draw_TrueColor_Image(pImg1,COLOR_DATA_RESIZE,50,900,180);

	
	Draw_TrueColor_Image(pImg2,COLOR_DATA_RESIZE,50,900+colorDataLen,120);
	Draw_TrueColor_Image(pImg3,COLOR_DATA_RESIZE,50,900+colorDataLen,180);

#endif

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < COLOR_DATA_RESIZE; j++)
		{
			r = colorData_tmp[i*3+0][j];
			g = colorData_tmp[i*3+1][j];
			b = colorData_tmp[i*3+2][j];

			t = r*500/(g+1);
			colorFvtTotal[i*COLOR_DATA_RESIZE*2+2*j+0] = t;
			t = b*500/(g+1);
			colorFvtTotal[i*COLOR_DATA_RESIZE*2+2*j+1] = t;
		}
	}
	pf1 = colorFvtTotal;
	pNoteClass = g_USD_noteClass;
	pFvt = (short *)USD_colorFvt_Int;
	Class = USD_NOTE_CLASS;

	if (noteType == INDEX_USD)
	{
		pNoteClass = g_USD_noteClass;
		pFvt = (short *)USD_colorFvt_Int;
		Class = USD_NOTE_CLASS;
	}
	else if (noteType == INDEX_EUR)
	{
		pNoteClass = g_EUR_noteClass;
		pFvt = (short *)EUR_colorFvt_Int;
		Class = EUR_NOTE_CLASS;
	}
	else if (noteType == INDEX_RUB)
	{
		pNoteClass = g_RUB_noteClass;
		pFvt = (short *)RUB_colorFvt_Int;
		Class = RUB_NOTE_CLASS;
	}
	else if (noteType == INDEX_TRY)
	{
		pNoteClass = g_TRY_noteClass;
		pFvt = (short *)TRY_colorFvt_Int;
		Class = TRY_NOTE_CLASS;
	}
	max_t = 0.0;
	for (i = 0; i < Class; i++)
	{
		fvtInt = 0;
		for (j = 0; j < COLOR_DATA_RESIZE*2*4; j++)
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

	colorJudgeValue = min_i/4;
	colorJudgeFlag = min_i%4;

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
	int Min, MinPos, Max0, Max1, Max, MaxPos, whitePaperVal;
	int i, j, k, m, count, t, t0, t1, t2, x[10], y[10];
	int sum, iradAve, boDong, angle, wirePos, arv0, arv1;
	short sxLeft, exLeft, sxRight, exRight, count1;
	short sx, ex, sw, sh, iradVal, sy, ey;

	float threK, d;
	u8 *pImg;
	double fvt, tt, max_t;
	short *pFvt;
	u8 *pNoteClass, *pf1;
	u8 Class, min_i;
	int fvtInt;

	pImg = (u8 *)lengthData;
	billIradMask = 0;

	if (lengthDataLen < 100 || billValue == 0x0ff)
	{
		billIradMask = 1;
		return 0;
	}


#ifdef DRAW_STATE1
	Draw_Gray_Image(pImg, IR_DATA_MAX_LEN, 21, 1200, 200, 1);
#endif

	sy = 0;
	ey = 21;
	
	for (i = 0; i < 21; i++)
	{
		count = 0;
		for (j = 8; j < lengthDataLen-8; j++)
		{
			if(lengthData[i][j+0] > 240)
			{
				count++;
			}
		}
		if (count < lengthDataLen/3)
		{
			sy = i+1;
			break;
		}
	}

	for (i = 20; i > 0; i--)
	{
		count = 0;
		for (j = 8; j < lengthDataLen-8; j++)
		{
			if(lengthData[i][j+0] > 240)
			{
				count++;
			}
		}
		if (count < lengthDataLen/3)
		{
			ey = i-1;
			break;
		}
	}
//	ey = 21;
//	sy = 0;
	sh = ey-sy;
	k = 0;
	for (i = sy; i < ey; i++)
	{
		for (j = 8; j < lengthDataLen-8; j+=4)
		{
			sum = (lengthData[i][j+0]+lengthData[i][j+1]+lengthData[i][j+2]+lengthData[i][j+3])/4;
			lengthData_Tmp[k++] = sum;
		}
	}
	sw = k/sh;
	
	memset(lengthData_Tmp2, 0, IRAD_FVT_DIM);
	ResizeCharImgGray(lengthData_Tmp,sw,sh, lengthData_Tmp2, IRAD_DATA_RESIZE_W,IRAD_DATA_RESIZE_H);
	//sh = 20;
#ifdef DRAW_STATE1
	Draw_Gray_Image(lengthData_Tmp, sw, sh, 800, 300, 1);
	Draw_Gray_Image(lengthData_Tmp2, IRAD_DATA_RESIZE_W, IRAD_DATA_RESIZE_H, 800, 320, 1);
#endif

//	return;
	pf1 = lengthData_Tmp2;
	pNoteClass = g_USD_noteClass;
	pFvt = (short *)USD_iradFvt_Int;
	Class = USD_NOTE_CLASS;

	if (noteType == INDEX_USD)
	{
		pNoteClass = g_USD_noteClass;
		pFvt = (short *)USD_iradFvt_Int;
		Class = USD_NOTE_CLASS;
	}
	else if (noteType == INDEX_EUR)
	{
		pNoteClass = g_EUR_noteClass;
		pFvt = (short *)EUR_iradFvt_Int;
		Class = EUR_NOTE_CLASS;
	}
	else if (noteType == INDEX_RUB)
	{
		pNoteClass = g_RUB_noteClass;
		pFvt = (short *)RUB_iradFvt_Int;
		Class = RUB_NOTE_CLASS;
	}
	else if (noteType == INDEX_TRY)
	{
		pNoteClass = g_TRY_noteClass;
		pFvt = (short *)TRY_iradFvt_Int;
		Class = TRY_NOTE_CLASS;
	}
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
	billValue = g_IradRes/4;
	billFlag = g_IradRes%4;

	return 0;
}




u8 billMG_Judge(int noteType)
{
	int i, Max0, Min0, Max1, Min1;
	if (mgDataLen < 80)
	{
		colorJudgeValue = 0xff;
		colorJudgeFlag = 0xff;
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
#ifdef DRAW_STATE1
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
			mgFvtFlag = 1;
		}
	}
//	FilterGaussian_1D_Int(mgData[0], mgDataLen, 1);
	//	FilterAverage_1(mgData[0], mgDataLen, mgData_tmp);
//	Display_Proj_BYTE(mgData[0], mgDataLen, 0, 255*2, 1, 0);
	
	
	//	FilterAverage_1(mgData[1], mgDataLen, mgData_tmp);
//	FilterGaussian_1D_Int(mgData[1], mgDataLen, 1);
//	Display_Proj_BYTE(mgData[1], mgDataLen, 0, 255*3, 1, 0);
}



void ResizeData(const u8 *pOldData,I32 len,u8 *pNewData, I32 newLen)
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
			t = 255;
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
