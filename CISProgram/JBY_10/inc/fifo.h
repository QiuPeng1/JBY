/*******************************************************

*******************************************************/

/*��ֹ�ظ����� */
#ifndef FIFO_H
#define FIFO_H

#include "system.h"

/*���ⲿ�������ڲ������ֿ�*/
#ifdef _FIFO_H_
    #define FIFO_EXT
#else
    #define FIFO_EXT  extern
#endif

/*ȫ�ֱ���*/
enum
{
	KB_FIFO=0,
	NOTE_WIDTH_FIFO,
	NOTE_LEN_GRADE_FIFO,
	NOTE_LEN_FIFO,
	SLANT_FIFO,
	GAP_FIFO,
	DIRTY_FIFO,
	NOTE_TYPE_FIFO,
	DIRECTION_VERSION_FIFO,//���� �汾
	LOCATION_FIFO,//λ��	
	FIFO_NUM
};

enum
{
	KEY_CUR = 0x20,//32
	KEY_FUN,//33
	KEY_RESTART,//34
	
	LONG_KEY_CUR = KEY_CUR + 0x20,
	LONG_KEY_FUN,
	LONG_KEY_RESTART,

	KEY_noKey = 0xff,
};

#define UART1_IN_FIFO_SIZE 	1000
#define UART1_OUT_FIFO_SIZE 1000
#define KB_FIFO_SIZE 		10
#define UART3_IN_FIFO_SIZE 	1000
#define UART3_OUT_FIFO_SIZE 1000
#define UART2_IN_FIFO_SIZE 	10
#define UART2_OUT_FIFO_SIZE 10

#define NOTE_WIDTH_FIFO_SIZE 10
#define NOTE_LEN_GRADE_FIFO_SIZE 10
#define NOTE_LEN_FIFO_SIZE 10
#define SLANT_FIFO_SIZE 10
#define GAP_FIFO_SIZE 10
#define DIRTY_FIFO_SIZE 10
#define NOTE_TYPE_FIFO_SIZE 10
#define DIRECTION_VERSION_FIFO_SIZE 10
#define OTHER_INFO2_FIFO_SIZE 10

FIFO_EXT u8 uart1infifo_data[UART1_IN_FIFO_SIZE];
#define uart1infifo_count (uart1infifo_GetCount())
FIFO_EXT u16 uart1infifo_front;
FIFO_EXT u16 uart1infifo_rear;
FIFO_EXT void uart1infifo_Clear(void);
FIFO_EXT void uart1infifo_DataIn(u8 d);
FIFO_EXT u8 uart1infifo_DataOut(void);
FIFO_EXT u16 uart1infifo_GetSpace(void);
FIFO_EXT u16 uart1infifo_GetCount(void);

FIFO_EXT u8 uart1outfifo_data[UART1_OUT_FIFO_SIZE];
FIFO_EXT u16 uart1outfifo_count;
FIFO_EXT u16 uart1outfifo_front;
FIFO_EXT u16 uart1outfifo_rear;
FIFO_EXT void uart1outfifo_Clear(void);
FIFO_EXT void uart1outfifo_DataIn(u8 d);
FIFO_EXT u8 uart1outfifo_DataOut(void);
FIFO_EXT u16 uart1outfifo_GetSpace(void);

FIFO_EXT u16 uart2infifo_data[UART2_IN_FIFO_SIZE];
#define uart2infifo_count (uart2infifo_GetCount())
FIFO_EXT u16 uart2infifo_front;
FIFO_EXT u16 uart2infifo_rear;
FIFO_EXT void uart2infifo_Clear(void);
FIFO_EXT void uart2infifo_DataIn(u16 d);
FIFO_EXT u16 uart2infifo_DataOut(void);
FIFO_EXT u16 uart2infifo_GetSpace(void);
FIFO_EXT u16 uart2infifo_GetCount(void);

FIFO_EXT u16 uart2outfifo_data[UART2_OUT_FIFO_SIZE];
FIFO_EXT u16 uart2outfifo_count;
FIFO_EXT u16 uart2outfifo_front;
FIFO_EXT u16 uart2outfifo_rear;
FIFO_EXT void uart2outfifo_Clear(void);
FIFO_EXT void uart2outfifo_DataIn(u16 d);
FIFO_EXT u16 uart2outfifo_DataOut(void);
FIFO_EXT u16 uart2outfifo_GetSpace(void);

FIFO_EXT u8 uart3infifo_data[UART3_IN_FIFO_SIZE];
//FIFO_EXT u16 uart3infifo_count;
#define uart3infifo_count (uart3infifo_GetCount())
FIFO_EXT u16 uart3infifo_front;
FIFO_EXT u16 uart3infifo_rear;
FIFO_EXT void uart3infifo_Clear(void);
FIFO_EXT void uart3infifo_DataIn(u8 d);
FIFO_EXT u8 uart3infifo_DataOut(void);
FIFO_EXT u16 uart3infifo_GetSpace(void);
FIFO_EXT u16 uart3infifo_GetCount(void);

FIFO_EXT u8 uart3outfifo_data[UART3_OUT_FIFO_SIZE];
FIFO_EXT u16 uart3outfifo_count;
FIFO_EXT u16 uart3outfifo_front;
FIFO_EXT u16 uart3outfifo_rear;
FIFO_EXT void uart3outfifo_Clear(void);
FIFO_EXT void uart3outfifo_DataIn(u8 d);
FIFO_EXT u8 uart3outfifo_DataOut(void);
FIFO_EXT u16 uart3outfifo_GetSpace(void);


/*�����Ĺ���/����*/
//FIFO_EXT u16 needDealUart1InDataNum;

/********************************************************
* �������ܣ������ֻ�����
* ���������
* ���������
* ����ֵ  ��
********************************************************/
FIFO_EXT void fifo_Init(void);

/********************************************************
�����
********************************************************/
FIFO_EXT void fifo_DataIn
(	
	u8 fifoName,
	u8 inData		//���������
);

/********************************************************
������
********************************************************/
FIFO_EXT u8 fifo_DataOut(u8 fifoName);

/********************************************************
������
********************************************************/
FIFO_EXT u8 fifo_DataOut2(u8 fifoName);

/********************************************************
������
********************************************************/
FIFO_EXT void fifo_Clear(u8 fifoName);


/********************************************************
��ȡ���г���
********************************************************/
FIFO_EXT u16 fifo_GetCount(u8 fifoName);
/********************************************************
��ȡ����ʣ��ռ�
********************************************************/
FIFO_EXT u16 fifo_GetSpace
(
	u8 fifoName
);

#endif

