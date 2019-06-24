/***************************************************************************

****************************************************************************/
/*��ֹ�ظ����� */
#ifndef _UART_H_
#define _UART_H_

/*�����ļ� */
#include "system.h"
#include "uart.h"
#include "fifo.h"

//-----------------------------------------------------------------
//�ܽż��꺯������
//-----------------------------------------------------------------
#define UART1_TXD_GPIO_PORT              GPIOA
#define UART1_TXD_GPIO_CLK               RCC_APB2Periph_GPIOA
#define UART1_TXD_GPIO_PIN               GPIO_Pin_9
#define UART1_TXD_GPIO_MODE              GPIO_Mode_AF_PP

#define UART1_RXD_GPIO_PORT              GPIOA
#define UART1_RXD_GPIO_CLK               RCC_APB2Periph_GPIOA
#define UART1_RXD_GPIO_PIN               GPIO_Pin_10
#define UART1_RXD_GPIO_MODE              GPIO_Mode_IN_FLOATING

#define UART3_TXD_GPIO_PORT              GPIOB
#define UART3_TXD_GPIO_CLK               RCC_APB2Periph_GPIOB
#define UART3_TXD_GPIO_PIN               GPIO_Pin_10
#define UART3_TXD_GPIO_MODE              GPIO_Mode_AF_PP

#define UART3_RXD_GPIO_PORT              GPIOB
#define UART3_RXD_GPIO_CLK               RCC_APB2Periph_GPIOB
#define UART3_RXD_GPIO_PIN               GPIO_Pin_11
#define UART3_RXD_GPIO_MODE              GPIO_Mode_IPU
//---------------------------------------------------------------------
//���Ͷ���
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//��������
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//�ļ��ڲ�ģ��˽�к���
//---------------------------------------------------------------------

#endif
