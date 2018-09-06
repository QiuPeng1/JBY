/*******************************************************

*******************************************************/

/*��ֹ�ظ����� */
#ifndef _FIFO_H_
#define _FIFO_H_

/*�����ļ� */
#include "system.h"
#include "fifo.h"


/*�������� */

/*�꺯������ */

/*���Ͷ��� */
typedef struct
{
	u8 * pd;
	u16 size;
	u16 front;
	u16 rear;
	u16 count;
	u16 front2;
}FIFO_T;

/*ȫ�ֱ��������뺯�� */

/*�ļ��ڲ�ģ�����������*/
//��ش���

volatile u8 DATA2[KB_FIFO_SIZE];
volatile u8 DATA7[NOTE_WIDTH_FIFO_SIZE];
volatile u8 DATA8[NOTE_LEN_GRADE_FIFO_SIZE];
volatile u8 DATA9[NOTE_LEN_FIFO_SIZE];
volatile u8 DATA10[SLANT_FIFO_SIZE];
volatile u8 DATA11[GAP_FIFO_SIZE];
volatile u8 DATA12[DIRTY_FIFO_SIZE];
volatile u8 DATA13[NOTE_TYPE_FIFO_SIZE];
volatile u8 DATA14[DIRECTION_VERSION_FIFO_SIZE];
volatile u8 DATA15[OTHER_INFO2_FIFO_SIZE];


static u16 const FIFO_SIZE[] = 
{
	KB_FIFO_SIZE,
	NOTE_WIDTH_FIFO_SIZE,
	NOTE_LEN_GRADE_FIFO_SIZE,
	NOTE_LEN_FIFO_SIZE,
	SLANT_FIFO_SIZE,
	GAP_FIFO_SIZE,
	DIRTY_FIFO_SIZE,
	NOTE_TYPE_FIFO_SIZE,
	DIRECTION_VERSION_FIFO_SIZE,
	OTHER_INFO2_FIFO_SIZE
};

static u8 * const FIFO_PD[] = 
{
	//DATA0, DATA1, DATA2, DATA3, DATA4,DATA5,DATA6,DATA7,DATA8,DATA9,DATA10,DATA11, DATA12
	DATA2, DATA7,DATA8,DATA9,DATA10,DATA11, DATA12 ,DATA13,DATA14,DATA15,
};

volatile FIFO_T allFifo[FIFO_NUM];

#endif
