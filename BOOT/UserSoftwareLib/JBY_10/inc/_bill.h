/***************************************************************************
****************************************************************************/
//��ֹ�ظ�����
#ifndef _BILL_H_
#define _BILL_H_

//�����ļ�
#include "system.h"
#include "bill.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//---------------------------------------------------------------------
//�ܽż��꺯������
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//���Ͷ���
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//��������
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//���õ�ȫ�ֱ��������뺯��
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//�ļ��ڲ�ģ��˽�б���
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//�ļ��ڲ�ģ��˽�к���
//---------------------------------------------------------------------
static void getDataGradientInfor(u8 *pSrc, short len, POS_INFOR *posMax, POS_INFOR *posMin);
static void RGBToISH(int r,int g,int b, double *I,double *S,double *H);
//static int MatchDis_Class(const FEA_DATA_TYPE *pTest, const FEA_DATA_TYPE *pTrain, const FVTHEAD *head, int known);
//static int MatchDis_Class1(const FEA_DATA_TYPE *pTest, const FEA_DATA_TYPE *pTrain, const FVTHEAD *head, int known, u8 flag);
static void FilterAverage_1(int *data,I32 l, int *dst);
static void ResizeData(const u8 *pOldData,I32 len,u8 *pNewData, I32 newLen);
static void ResizeCharImgGray(u8 *pOldImg,I32 oldImgW,I32 oldImgH, u8 *pNewImg, I32 newImgW,I32 newImgH);
#endif
