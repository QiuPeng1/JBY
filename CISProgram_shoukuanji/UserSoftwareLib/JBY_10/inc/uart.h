/***************************************************************************


****************************************************************************/

/*防止重复引用 */
#ifndef UART_H
#define UART_H

#include "system.h"

/*将外部包含和内部包含分开*/
#ifdef _UART_H_
    #define UART_EXT
#else
    #define UART_EXT  extern
#endif

//---------------------------------------------------------------------
//全局常量定义
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//全局类型定义
//---------------------------------------------------------------------
#define UART1_DATA_DELAY 5

//---------------------------------------------------------------------
//全局变量，可以被外部程序直接访问
//---------------------------------------------------------------------
UART_EXT  bit gb_needDealUart1Data;
UART_EXT  u8 uart1DelayTimer;
UART_EXT  bit gb_needDealUart3Data;
UART_EXT  u8 uart3DelayTimer;
		

UART_EXT u8 gb_uart1Mode;
/*公开的过程/函数*/
//---------------------------------------------------------------------
//初始化
//---------------------------------------------------------------------
UART_EXT void uart1_Init
(
	void
);
UART_EXT void uart3_Init(void);
//---------------------------------------------------------------------
//发送数据
//---------------------------------------------------------------------
UART_EXT void uart_SendDataToUart1(u8 * pData,u16 len);
#endif
