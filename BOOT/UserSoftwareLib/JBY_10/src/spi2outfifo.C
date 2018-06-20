/*******************************************************

*******************************************************/

/*包含私有头文件 */
#include "inc\_spi2outfifo.h"

/*公开的子程序*/
//---------------------------------------------------------------------
//队列清空
//---------------------------------------------------------------------
void spi2outfifo_Clear(void)
{
	spi2outfifoFront = SPI2OUTFIFO_SIZE - 1;
	spi2outfifoRear = SPI2OUTFIFO_SIZE - 1;
	spi2outfifo_count = 0;
//	gb_spiOutOff = 0;
}

//---------------------------------------------------------------------
//数据入队列
//---------------------------------------------------------------------
void spi2outfifo_DataIn
(	
	u8 inData		//入队列数据
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
//出队列：如果队列有数据，就直接返回头部的数据。
//		  如果没有数据，就先等待一段时间，再没有，就返回0xff
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

/*私有的子程序*/


