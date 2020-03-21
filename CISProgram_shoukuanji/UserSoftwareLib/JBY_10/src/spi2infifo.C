/*******************************************************

*******************************************************/

/*����˽��ͷ�ļ� */
#include "inc\_spi2infifo.h"

/*�������ӳ���*/
//---------------------------------------------------------------------
//�������
//---------------------------------------------------------------------
void spi2infifo_Clear(void)
{
	spi2infifoFront = SPI2INFIFO_SIZE - 1;
	spi2infifoRear = SPI2INFIFO_SIZE - 1;
	spi2infifo_count = 0;
	gb_spiInOff = 0;
}

//---------------------------------------------------------------------
//���������
//---------------------------------------------------------------------
void spi2infifo_DataIn
(	
	u8 inData		//���������
)
{
	if (spi2infifo_count < SPI2INFIFO_SIZE-1)
	{
		spi2infifoRear = ((spi2infifoRear+1) % SPI2INFIFO_SIZE);
		spi2infifoData[spi2infifoRear] = inData;
		spi2infifo_count ++;
	}
}

//---------------------------------------------------------------------
//�����У�������������ݣ���ֱ�ӷ���ͷ�������ݡ�
//		  ���û�����ݣ����ȵȴ�һ��ʱ�䣬��û�У��ͷ���0xff
//---------------------------------------------------------------------
u8 spi2infifo_DataOut(void)
{
	if (spi2infifo_count > 0)
	{
		spi2infifoFront = ((spi2infifoFront + 1) % SPI2INFIFO_SIZE);
		gb_spiInOff = 1;
		spi2infifo_count --;
		gb_spiInOff = 0;
		return(spi2infifoData[spi2infifoFront]);	    
	}
	else
	{
		return(0xff);
	}
}

/*˽�е��ӳ���*/

