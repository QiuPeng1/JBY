/*******************************************************

*******************************************************/

/*防止重复引用 */
#ifndef SPI2OUTFIFO_H
#define SPI2OUTFIFO_H

#include "system.h"

/*将外部包含和内部包含分开*/
#ifdef _SPI2OUTFIFO_H_
    #define SPI2OUTFIFO_EXT
#else
    #define SPI2OUTFIFO_EXT  extern
#endif

//---------------------------------------------------------------------
//全局常量定义
//---------------------------------------------------------------------
#define SPI2OUTFIFO_SIZE 200

//---------------------------------------------------------------------
//全局类型定义
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//全局变量，可以被外部程序直接访问
//---------------------------------------------------------------------
SPI2OUTFIFO_EXT volatile u8 spi2outfifo_count;
SPI2OUTFIFO_EXT volatile u8 gb_spiOutOff;


/*公开的过程/函数*/
//---------------------------------------------------------------------
//队列清空
//---------------------------------------------------------------------
SPI2OUTFIFO_EXT void spi2outfifo_Clear(void);

//---------------------------------------------------------------------
//数据入队列
//---------------------------------------------------------------------
SPI2OUTFIFO_EXT void spi2outfifo_DataIn
(	
	u8 inData		//入队列数据
);

//---------------------------------------------------------------------
//出队列：如果队列有数据，就直接返回头部的数据。
//		  如果没有数据，就先等待一段时间，再没有，就返回0xff
//---------------------------------------------------------------------
SPI2OUTFIFO_EXT u8 spi2outfifo_DataOut(void);


#endif
