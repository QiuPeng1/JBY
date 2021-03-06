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

static void ResizeData(const u16 *pOldData,I32 len,u16 *pNewData, I32 newLen);
static void ResizeCharImgGray(u8 *pOldImg,I32 oldImgW,I32 oldImgH, u8 *pNewImg, I32 newImgW,I32 newImgH);
static void FilterAverage_2(I32 *data,I32 l);
#endif
