/***************************************************************************
* Copyright (c) 2009~2010 南京理工速必得科技股份有限公司
* All rights reserved
* 
* 文件名称：system.h
* 
* 摘    要：本文件为一个系统的cpu类型选择的头文件
* 
* 创 建 者：易鲜红
* 
* 创建日期：2008年02月28日
*
* 修改记录
日期  修改者   		版本     修改内容
-------------- 		-------  ------------------------  

****************************************************************************/

/*防止重复引用 */
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/*包含文件 */
#ifdef __cplusplus
	#include "usertype_vc.h"
#else
	#include "usertype.h"
#endif

#define MR_NUM 6
#define MAX_SAMPLE_NUM 1200
#define DRAW_STATE

#endif