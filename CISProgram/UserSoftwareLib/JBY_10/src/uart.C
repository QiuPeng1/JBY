/***************************************************************************

****************************************************************************/

/*包含私有头文件 */
#include "_uart.h"

/*公开的子程序*/
//---------------------------------------------------------------------
//初始化
//---------------------------------------------------------------------
void uart_Init
(
	void
)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//UART1 管脚配置：时钟、模式	
	
	GPIO_InitStructure.GPIO_Pin = UART1_RXD_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = UART1_RXD_GPIO_MODE; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	
	GPIO_Init(UART1_RXD_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = UART1_TXD_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = UART1_TXD_GPIO_MODE; 
	GPIO_Init(UART1_TXD_GPIO_PORT, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART1, &USART_InitStructure);	


	//配置nvic向量表
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	

	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);		//一开始就是要关闭

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);	

	gb_needDealUart1Data = FALSE;
	uart1DelayTimer = 0;
	
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

 	//UART3 管脚配置：时钟、模式	
 	
 	GPIO_InitStructure.GPIO_Pin = UART3_RXD_GPIO_PIN;
 	GPIO_InitStructure.GPIO_Mode = UART3_RXD_GPIO_MODE; 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	
 	GPIO_Init(UART3_RXD_GPIO_PORT, &GPIO_InitStructure);

 	GPIO_InitStructure.GPIO_Pin = UART3_TXD_GPIO_PIN;
 	GPIO_InitStructure.GPIO_Mode = UART3_TXD_GPIO_MODE; 
 	GPIO_Init(UART3_TXD_GPIO_PORT, &GPIO_InitStructure);
 	
 	USART_InitStructure.USART_BaudRate = 115200;
 	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
 	USART_InitStructure.USART_StopBits = USART_StopBits_1;
 	USART_InitStructure.USART_Parity = USART_Parity_No;
 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 	
 	USART_Init(USART3, &USART_InitStructure);	


 	//配置nvic向量表
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
 	
 	/* Enable the USARTy Interrupt */
 	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);	

 	/* Enable USART3 Receive and Transmit interrupts */
 	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
 	USART_ITConfig(USART3, USART_IT_TXE, DISABLE);		//一开始就是要关闭

 	/* Enable USART */
 	USART_Cmd(USART3, ENABLE);	

 	gb_needDealUart3Data = 0;
}

//---------------------------------------------------------------------
//发送数据到USART1
//---------------------------------------------------------------------
void uart_SendDataToUart1(u8 * pData, u16 len)
{
	u8 i;

	while (1)
	{
		if (uart1outfifo_GetSpace() > len+5)
		{
			break;
		}
		else
		{
			i = 0;
		}
	}
	//等待发送数据为0
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);	//首先肯定要关闭中断，防止队列的进出会同时进行
	while (len --)
	{		
		uart1outfifo_DataIn(*pData);
		pData ++;
	}  
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

void uart_SendDataToUart2(u16 * pData, u16 len)
{
	u8 i;

	while (1)
	{
		if (uart2outfifo_GetSpace() > len+5)
		{
			break;
		}
		else
		{
			i = 0;
		}
	}
	//等待发送数据为0
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);	//首先肯定要关闭中断，防止队列的进出会同时进行
	while (len --)
	{		
		uart2outfifo_DataIn(*pData);
		pData ++;
	}  
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}


void uart_SendDataToUart3(u8 * pData, u16 len)
{
	u8 i;

	while (1)
	{
		if (uart3outfifo_GetSpace() > len+5)
		{
			break;
		}
		else
		{
			i = 0;
		}
	}
	//等待发送数据为0
	USART_ITConfig(USART3, USART_IT_TXE, DISABLE);	//首先肯定要关闭中断，防止队列的进出会同时进行
	while (len --)
	{		
		uart3outfifo_DataIn(*pData);
		pData ++;
	}  
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

