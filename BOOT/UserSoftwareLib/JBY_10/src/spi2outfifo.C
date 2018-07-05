/*******************************************************

*******************************************************/

/*����˽��ͷ�ļ� */
#include "inc\_spi2outfifo.h"

/*�������ӳ���*/
//---------------------------------------------------------------------
//�������
//---------------------------------------------------------------------
void spi2outfifo_Clear(void)
{
	spi2outfifoFront = SPI2OUTFIFO_SIZE - 1;
	spi2outfifoRear = SPI2OUTFIFO_SIZE - 1;
	spi2outfifo_count = 0;
//	gb_spiOutOff = 0;
}

//---------------------------------------------------------------------
//���������
//---------------------------------------------------------------------
void spi2outfifo_DataIn
(	
	u8 inData		//���������
)
{
	if (spi2outfifo_count <  SPI2OUTFIFO_SIZE-1)
	{
		spi2outfifoRear = ((spi2outfifoRear+1) % SPI2OUTFIFO_SIZE);
		spi2outfifoData[spi2outfifoRear] = inData;
//		gb_spiOutOff = 1;
		spi2outfifo_count ++;
//		gb_spiOutOff = 0;
	}
}

//---------------------------------------------------------------------
//�����У�������������ݣ���ֱ�ӷ���ͷ�������ݡ�
//		  ���û�����ݣ����ȵȴ�һ��ʱ�䣬��û�У��ͷ���0xff
//---------------------------------------------------------------------
u8 spi2outfifo_DataOut(void)
{
	if (spi2outfifo_count > 0)
	{
		spi2outfifoFront = ((spi2outfifoFront + 1) % SPI2OUTFIFO_SIZE);
		spi2outfifo_count --;
		return(spi2outfifoData[spi2outfifoFront]);	    
	}
	else
	{
		return(0xff);
	}
}

/*˽�е��ӳ���*/

