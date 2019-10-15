#ifndef __USART_H__
#define __USART_H__
#include "user_includes.h"
	void Usart_Config(void);
	void SendChar(u8);
	void SendStr(u8*);
	void SendADStr(u16);
	void SendValueStr(u16);//发送数据量的字符串
	void SendIntStr(u32);
#endif
