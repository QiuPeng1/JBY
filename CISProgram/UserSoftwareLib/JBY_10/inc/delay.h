/*******************************************************

*******************************************************/

/*防止重复引用 */
#ifndef DELAY_H
#define DELAY_H

#include "stm32f10x.h"

/*将外部包含和内部包含分开*/
#ifdef _DELAY_H_
    #define DELAY_EXT
#else
    #define DELAY_EXT  extern
#endif

/*公开的过程/函数*/
/************************************************************
延时模块初始化
************************************************************/
DELAY_EXT void delay_Init
(
	void
);

/************************************************************
延时若干毫秒
************************************************************/
DELAY_EXT void delay_DelayMs
(
	u16 x		//延时的毫秒数
);

DELAY_EXT void delay_DelayUs
(
	u16 x		//??????
);

DELAY_EXT void delay_DelayCpuTime
(
	u16 x		//??????
);

#endif
