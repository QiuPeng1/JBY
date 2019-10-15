/*******************************************************

*******************************************************/

/*包含私有头文件 */
#include "_fifo.h"

/*公开的子程序*/

/********************************************************
* 函数介绍：清空清分机队列
* 输入参数：数目/类型/顺序/约束
* 输出参数：
* 返回值  ：
********************************************************/
void fifo_Init(void)
{
	u8 i;
	
	for (i=0; i<FIFO_NUM; i++)
	{
		allFifo[i].pd = FIFO_PD[i];
		allFifo[i].size = FIFO_SIZE[i];
		allFifo[i].front = allFifo[i].size -1;
		allFifo[i].rear = allFifo[i].size -1;
		allFifo[i].count = 0;
		allFifo[i].front2 = allFifo[i].size -1;
	}
	uart1infifo_Clear();
	uart1outfifo_Clear();
	uart2outfifo_Clear();
	uart3infifo_Clear();
	uart3outfifo_Clear();
	uart1Pacinfifo_Clear();
}

/********************************************************
入队列
********************************************************/
void fifo_DataIn 
(	
	u8 fifoName,
	u8 inData		//入队列数据
)
{
	u8 * pd;

	if (allFifo[fifoName].count < allFifo[fifoName].size)
	{
		allFifo[fifoName].rear = ((allFifo[fifoName].rear +1) % allFifo[fifoName].size);		
		pd = allFifo[fifoName].pd + allFifo[fifoName].rear; 
		*pd = inData;			
		allFifo[fifoName].count ++;
	}
}

/********************************************************
出队列
********************************************************/
u8 fifo_DataOut
(
	u8 fifoName
)
{
	u8 * pd;

/*	if (fifoName == UART1_IN_FIFO)
	{
		if (needDealUart1InDataNum > 0)
		{
			needDealUart1InDataNum --;
		}
	} */
	if (allFifo[fifoName].count > 0)
	{			
		allFifo[fifoName].front = ((allFifo[fifoName].front +1) % allFifo[fifoName].size);	
/*		if (fifoName == UART1_IN_FIFO)
		{
			USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);	
			allFifo[fifoName].count --;		
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		}
		else if (fifoName == UART3_IN_FIFO)
		{
			USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	
			allFifo[fifoName].count --;		
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		}
		else	  */
		{
			allFifo[fifoName].count --;		
		}
		pd = allFifo[fifoName].pd + allFifo[fifoName].front; 
		return(*pd);
	}
	else
	{
		return(0);
	}
}

/********************************************************
出队列
********************************************************/
u8 fifo_DataOut2
(
	u8 fifoName
)
{
	u8 * pd;

	if (allFifo[fifoName].count > 0)
	{			
		allFifo[fifoName].front2 = ((allFifo[fifoName].front2 +1) % allFifo[fifoName].size);	
		pd = allFifo[fifoName].pd + allFifo[fifoName].front2; 
		return(*pd);
	}
	else
	{
		return(0);
	}
}

/********************************************************
清队列
********************************************************/
void fifo_Clear(u8 fifoName)
{
/*	if (fifoName == UART1_IN_FIFO)
	{
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);	
		allFifo[fifoName].front = allFifo[fifoName].size -1;
		allFifo[fifoName].rear = allFifo[fifoName].size -1;
		allFifo[fifoName].count = 0;
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	}
	else if (fifoName == UART3_IN_FIFO)
	{
		USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	
		allFifo[fifoName].front = allFifo[fifoName].size -1;
		allFifo[fifoName].rear = allFifo[fifoName].size -1;
		allFifo[fifoName].count = 0;
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	}
	else		*/
	{
		allFifo[fifoName].front = allFifo[fifoName].size -1;
		allFifo[fifoName].rear = allFifo[fifoName].size -1;
		allFifo[fifoName].count = 0;
	}
}

/********************************************************
获取队列长度
********************************************************/
u16 fifo_GetCount
(
	u8 fifoName
)
{
	return (allFifo[fifoName].count);
}

/********************************************************
获取队列剩余空间
********************************************************/
u16 fifo_GetSpace
(
	u8 fifoName
)
{
	return (allFifo[fifoName].size - allFifo[fifoName].count);
}

//??1?????
u16 uart1Pacinfifo_GetCount(void)
{
	u16 countR,countF;
	countR = uart1Pacinfifo_rear;
	countF = uart1Pacinfifo_front;
	if (countR >=	countF)
	{
		return(countR - countF);
	}
	else
	{
		return(UARTPAC_IN_FIFO_SIZE + countR - countF);
	}
}

void uart1Pacinfifo_Clear(void)
{
	uart1Pacinfifo_front = UARTPAC_IN_FIFO_SIZE -1;
	uart1Pacinfifo_rear = uart1Pacinfifo_front;
//	uart1infifo_count = 0;
}
void uart1Pacinfifo_DataIn(UART_CMD d)
{
	if (uart1Pacinfifo_count < UARTPAC_IN_FIFO_SIZE)
	{
		uart1Pacinfifo_rear = (uart1Pacinfifo_rear +1) % UARTPAC_IN_FIFO_SIZE;	
		//uart1infifo_count ++;		
		uart1Pacinfifo_data[uart1Pacinfifo_rear] = d;
	}
}

UART_CMD uart1Pacinfifo_DataOut(void)
{
	if (uart1Pacinfifo_rear !=  uart1Pacinfifo_front)
	{
		uart1Pacinfifo_front = (uart1Pacinfifo_front +1) % UARTPAC_IN_FIFO_SIZE;
//		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);		
//		uart1infifo_count --;		
//		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
		return(uart1Pacinfifo_data[uart1Pacinfifo_front]);
	}
	else
	{
		return(uart1Pacinfifo_data[0]);
	}
}

u16 uart1Pacinfifo_GetSpace(void)
{
	return(UARTPAC_IN_FIFO_SIZE - uart1Pacinfifo_count);
}

//串口1入队列
u16 uart1infifo_GetCount(void)
{
	u16 countR,countF;
	countR = uart1infifo_rear;
	countF = uart1infifo_front;
	if (countR >=	countF)
	{
		return(countR - countF);
	}
	else
	{
		return(UART1_IN_FIFO_SIZE + countR - countF);
	}
}

void uart1infifo_Clear(void)
{
	uart1infifo_front = UART1_IN_FIFO_SIZE -1;
	uart1infifo_rear = uart1infifo_front;
//	uart1infifo_count = 0;
}
void uart1infifo_DataIn(u8 d)
{
	if (uart1infifo_count < UART1_IN_FIFO_SIZE)
	{
		uart1infifo_rear = (uart1infifo_rear +1) % UART1_IN_FIFO_SIZE;	
		//uart1infifo_count ++;		
		uart1infifo_data[uart1infifo_rear] = d;
	}
}

u8 uart1infifo_DataOut(void)
{
	if (uart1infifo_rear !=  uart1infifo_front)
	{
		uart1infifo_front = (uart1infifo_front +1) % UART1_IN_FIFO_SIZE;
//		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);		
//		uart1infifo_count --;		
//		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
		return(uart1infifo_data[uart1infifo_front]);
	}
	else
	{
		return(0xff);
	}
}

u16 uart1infifo_GetSpace(void)
{
	return(UART1_IN_FIFO_SIZE - uart1infifo_count);
}

void uart1outfifo_Clear(void)
{
	uart1outfifo_front = UART1_OUT_FIFO_SIZE -1;
	uart1outfifo_rear = uart1outfifo_front;
	uart1outfifo_count = 0;

}
void uart1outfifo_DataIn(u8 d)
{
	if (uart1outfifo_count < UART1_OUT_FIFO_SIZE)
	{
		uart1outfifo_rear = (uart1outfifo_rear +1) % UART1_OUT_FIFO_SIZE;	
		uart1outfifo_count ++;		
		uart1outfifo_data[uart1outfifo_rear] = d;
	}
}
u8 uart1outfifo_DataOut(void)
{
	if (uart1outfifo_count > 0)
	{
		uart1outfifo_front = (uart1outfifo_front +1) % UART1_OUT_FIFO_SIZE;	
		uart1outfifo_count --;		
		return(uart1outfifo_data[uart1outfifo_front]);
	}
	else
	{
		return(0);
	}
}

u16 uart1outfifo_GetSpace(void)
{
	return(UART1_OUT_FIFO_SIZE - uart1outfifo_count);
}

//串口2入队列
u16 uart2infifo_GetCount(void)
{
	u16 countR,countF;
	countR = uart2infifo_rear;
	countF = uart2infifo_front;
	if (countR >=	countF)
	{
		return(countR - countF);
	}
	else
	{
		return(UART2_IN_FIFO_SIZE + countR - countF);
	}
}

void uart2infifo_Clear(void)
{
	uart2infifo_front = UART2_IN_FIFO_SIZE -1;
	uart2infifo_rear = uart2infifo_front;
//	uart2infifo_count = 0;
}
void uart2infifo_DataIn(u16 d)
{
	if (uart2infifo_count < UART2_IN_FIFO_SIZE)
	{
		uart2infifo_rear = (uart2infifo_rear +1) % UART2_IN_FIFO_SIZE;	
		//uart2infifo_count ++;		
		uart2infifo_data[uart2infifo_rear] = d;
	}
}

u16 uart2infifo_DataOut(void)
{
	if (uart2infifo_rear !=  uart2infifo_front)
	{
		uart2infifo_front = (uart2infifo_front +1) % UART2_IN_FIFO_SIZE;
//		USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);		
//		uart2infifo_count --;		
//		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
		return(uart2infifo_data[uart2infifo_front]);
	}
	else
	{
		return(0xffff);
	}
}

u16 uart2infifo_GetSpace(void)
{
	return(UART2_IN_FIFO_SIZE - uart2infifo_count);
}

void uart2outfifo_Clear(void)
{
	uart2outfifo_front = UART2_OUT_FIFO_SIZE -1;
	uart2outfifo_rear = uart2outfifo_front;
	uart2outfifo_count = 0;

}
void uart2outfifo_DataIn(u16 d)
{
	if (uart2outfifo_count < UART2_OUT_FIFO_SIZE)
	{
		uart2outfifo_rear = (uart2outfifo_rear +1) % UART2_OUT_FIFO_SIZE;	
		uart2outfifo_count ++;		
		uart2outfifo_data[uart2outfifo_rear] = d;
	}
}

u16 uart2outfifo_DataOut(void)
{
	if (uart2outfifo_count > 0)
	{
		uart2outfifo_front = (uart2outfifo_front +1) % UART2_OUT_FIFO_SIZE;	
		uart2outfifo_count --;		
		return(uart2outfifo_data[uart2outfifo_front]);
	}
	else
	{
		return(0);
	}
}

u16 uart2outfifo_GetSpace(void)
{
	return(UART2_OUT_FIFO_SIZE - uart2outfifo_count);
}

//串口3入队列
u16 uart3infifo_GetCount(void)
{
	u16 countR,countF;
	countR = uart3infifo_rear;
	countF = uart3infifo_front;
	if (countR >=	countF)
	{
		return(countR - countF);
	}
	else
	{
		return(UART3_IN_FIFO_SIZE + countR - countF);
	}
}

void uart3infifo_Clear(void)
{
	uart3infifo_front = UART3_IN_FIFO_SIZE -1;
	uart3infifo_rear = uart3infifo_front;
//	uart3infifo_count = 0;
}
void uart3infifo_DataIn(u8 d)
{
//	if (uart3infifo_count < UART3_IN_FIFO_SIZE)
	{
		uart3infifo_rear = (uart3infifo_rear +1) % UART3_IN_FIFO_SIZE;	
		//uart3infifo_count ++;		
		uart3infifo_data[uart3infifo_rear] = d;
	}
}

u8 uart3infifo_DataOut(void)
{
	if (uart3infifo_rear !=  uart3infifo_front)
	{
		uart3infifo_front = (uart3infifo_front +1) % UART3_IN_FIFO_SIZE;
//		USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);		
//		uart3infifo_count --;		
//		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	
		return(uart3infifo_data[uart3infifo_front]);
	}
	else
	{
		return(0xff);
	}
}

u16 uart3infifo_GetSpace(void)
{
	return(UART3_IN_FIFO_SIZE - uart3infifo_count);
}


void uart3outfifo_Clear(void)
{
	uart3outfifo_front = UART3_OUT_FIFO_SIZE -1;
	uart3outfifo_rear = uart3outfifo_front;
	uart3outfifo_count = 0;	 
}
void uart3outfifo_DataIn(u8 d)
{
	if (uart3outfifo_count < UART3_OUT_FIFO_SIZE)
	{
		uart3outfifo_rear = (uart3outfifo_rear +1) % UART3_OUT_FIFO_SIZE;	
		uart3outfifo_count ++;		
		uart3outfifo_data[uart3outfifo_rear] = d;
	}
}
u8 uart3outfifo_DataOut(void)
{
	if (uart3outfifo_count > 0)
	{
		uart3outfifo_front = (uart3outfifo_front +1) % UART3_OUT_FIFO_SIZE;	
		uart3outfifo_count --;		
		return(uart3outfifo_data[uart3outfifo_front]);
	}
	else
	{
		return(0);
	}
}
u16 uart3outfifo_GetSpace(void)
{
	return(UART3_OUT_FIFO_SIZE - uart3outfifo_count);
}


/*私有的子程序*/


