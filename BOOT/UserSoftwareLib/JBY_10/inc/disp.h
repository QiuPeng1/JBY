/*******************************************************

*******************************************************/

/*防止重复引用 */
#ifndef DISP_H
#define DISP_H

#include "stm32f10x.h"
//#include "ili9488.h"

/*将外部包含和内部包含分开*/
#ifdef _DISP_H_
    #define DISP_EXT
#else
    #define DISP_EXT  extern
#endif


enum
{
	IMG_UDISK,
	IMG_NET,
	IMG_NET_OFF,
	IMG_UDISK_OFF,
	IMG_MENU,
	IMG_PRINT,
	IMG_PRINT_OFFLINE,
	IMG_NET_TRANS,
	IMG_UDISK_TRANS,
};

DISP_EXT u8 currentProgress;
DISP_EXT u16 progressX,progressY,progressW,progressH;
DISP_EXT u16 progressBackColor,progressFrontColor;
/*公开的过程/函数*/

DISP_EXT void disp_clearScreen(u16 cl);
DISP_EXT void disp_setFont(u8 f);
DISP_EXT void disp_setPenColor(u16 cl);
DISP_EXT void disp_setBackColor(u16 cl);
DISP_EXT void disp_string(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font8String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font16String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font24String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font32String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font48String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_drawCross(u16 x,u16 y,u16 color);
DISP_EXT void disp_drawRectangle(u16 x,u16 y,u16 w,u16 h,u16 color);
DISP_EXT void disp_progressRect(void);
DISP_EXT void disp_progress(u8 progress);
DISP_EXT void disp_drawRectangleFrame(u16 x,u16 y,u16 w,u16 h,u16 color);
DISP_EXT void disp_SetLine(u16 startY, u16 startX, u16 height, u16 width,u16 cl);
DISP_EXT void disp_DrawCircle(u16 x0,u16 y0,u8 r,u16 Color);
DISP_EXT void disp_DrawFullCircle(u16 x0,u16 y0,u8 r,u16 Color);
DISP_EXT void disp_DrawRoundRect(u16 x,u16 y,u16 w,u16 h,u16 frontColor,u16 backColor);
DISP_EXT void disp_DrawChart(u16 x,u16 y,u16 w,u16 h,u8 rowNum,u8 colNum,u16 backColor);
#endif
