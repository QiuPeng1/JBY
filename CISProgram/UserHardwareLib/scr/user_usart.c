#include "user_includes.h"
#include "stdio.h"
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
//-------------------------------------------------------
void Usart_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStruct);	//根据指定的参数初始化VIC寄存器
	
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断

	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStruct);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART1, ENABLE);
	
	SendChar(0xff);
}
void SendChar(u8 GetData)
{
	USART_SendData(USART1, GetData);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);	
}	
void SendStr(u8* str)
{
	while(*str != '\0')
	{
		SendChar(*str++);		
	}
}
void SendADStr(u16 value)
{
	SendChar(value/100+0x30);
	SendChar(value%100/10+0x30);
	SendChar(value%10+0x30);
	SendChar(' ');
}
void SendIntStr(u32 value)
{
	u8 NumArr[6];
	NumArr[5] = value/100000;
	NumArr[4] = value%100000/10000;
	NumArr[3] = value%10000/1000;
	NumArr[2] = value%1000/100;										
	NumArr[1] = value%100/10;
	NumArr[0] = value%10;
	SendChar(NumArr[5]+0x30);
	SendChar(NumArr[4]+0x30);
	SendChar(NumArr[3]+0x30);
	SendChar(NumArr[2]+0x30);
	SendChar(NumArr[1]+0x30);
	SendChar(NumArr[0]+0x30);
	SendChar('K');
}
void SendValueStr(u16 result)
{
	u32 value;
	value = result*330/4096;
	SendChar(value/100+0x30);
	SendChar(value%100/10+0x30);
	SendChar(value%10+0x30);
}

//-------------------------------------------------------------------------------------
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		USART_ReceiveData(USART1);//读取接收到的数据
     } 
} 

