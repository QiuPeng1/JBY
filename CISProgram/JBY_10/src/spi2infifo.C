/*******************************************************

*******************************************************/

/*包含私有头文件 */
#include "inc\_spi2infifo.h"

/*公开的子程序*/
//---------------------------------------------------------------------
//队列清空
//---------------------------------------------------------------------
void spi2infifo_Clear(void)
{
	spi2infifoFront = SPI2INFIFO_SIZE - 1;
	spi2infifoRear = SPI2INFIFO_SIZE - 1;
	spi2infifo_count = 0;
	gb_spiInOff = 0;
}

//---------------------------------------------------------------------
//数据入队列
//---------------------------------------------------------------------
void spi2infifo_DataIn
(	
	u8 inData		//入队列数据
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
//出队列：如果队列有数据，就直接返回头部的数据。
//		  如果没有数据，就先等待一段时间，再没有，就返回0xff
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

/*私有的子程序*/


