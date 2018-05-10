/***************************************************************************
****************************************************************************/
//防止重复引用
#ifndef _BILL_H_
#define _BILL_H_

//包含文件
#include "system.h"
#include "bill.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//---------------------------------------------------------------------
//管脚及宏函数定义
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//类型定义
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//常量定义
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//引用的全局变量及输入函数
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//文件内部模块私有变量
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//文件内部模块私有函数
//---------------------------------------------------------------------
static void getDataGradientInfor(u8 *pSrc, short len, POS_INFOR *posMax, POS_INFOR *posMin);
static void RGBToISH(int r,int g,int b, double *I,double *S,double *H);
//static int MatchDis_Class(const FEA_DATA_TYPE *pTest, const FEA_DATA_TYPE *pTrain, const FVTHEAD *head, int known);
//static int MatchDis_Class1(const FEA_DATA_TYPE *pTest, const FEA_DATA_TYPE *pTrain, const FVTHEAD *head, int known, u8 flag);
static void FilterAverage_1(int *data,I32 l, int *dst);
static void ResizeData(const u8 *pOldData,I32 len,u8 *pNewData, I32 newLen);
static void ResizeCharImgGray(u8 *pOldImg,I32 oldImgW,I32 oldImgH, u8 *pNewImg, I32 newImgW,I32 newImgH);
#endif
