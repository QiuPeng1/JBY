
/*包含私有头文件 */
#include "_disp.h"

/*公开的子程序*/
u8 GetBitNum(u32 n)
{
	u8 a,i;
	u32 d;
	d = n;
	a = 1;
	for(i = 0;i< 10;i++)
	{
		if(d/10 > 0)
		{
			d/=10;
			a ++;
		}
		else
		{
			break;
		}
	}
	return a;
}

void disp_Init(void)
{
	//SysTick_Config(SystemFrequency / 1000);	//1ms
}


void disp_clearScreen(u16 cl)
{
	u16 len;
	sprintf(TFTStr,"void LCD_Clear(%d)\r\n",cl);
	len = strlen(TFTStr);	
	uart_SendDataToUart1(TFTStr,len);
}

void disp_setFont(u8 f)
{
	CurrentFont = f;
}

void disp_setPenColor(u16 cl)
{
	CurrentPenColor = cl;
}

void disp_setBackColor(u16 cl)
{
	CurrentBackColor = cl;
}

void disp_string(u8 *str,u16 xAxis,u16 yAxis)
{
	u16 len;
	len = strlen(str);
	
	if(len > sizeof(TFTTmpStr) - 3)
	{
		return;
	}
	TFTTmpStr[0] = '"';
	memcpy(TFTTmpStr+1,str,len);
	TFTTmpStr[len+1] = '"';
	TFTTmpStr[len+2] = '\0';
	
	sprintf(TFTStr,"void LCDLS_Str(%d,%d,%d,%d,%d,%s)\r\n",xAxis,yAxis,CurrentBackColor,CurrentPenColor,CurrentFont,(u8 *)TFTTmpStr);
	//sprintf(TFTStr,"void LCDLS_Str(%d,%d,%d,%d,%d,\"WELCOME\")\r\n",x,y,bkColor,penColor,fontSize);
	len = strlen(TFTStr);	
	uart_SendDataToUart1(TFTStr,len);
}

void disp_num(u32 num,u16 xAxis,u16 yAxis)
{
	u16 len,bitLen;
	bitLen = GetBitNum(num);
	sprintf(TFTStr,"void LCDLS_Num(%d,%d,%d,%d,%d,%d,%d)\r\n",xAxis,yAxis,CurrentBackColor,CurrentPenColor,num,bitLen,CurrentFont);
	len = strlen(TFTStr);	
	uart_SendDataToUart1(TFTStr,len);
}

void disp_DrawChart(u16 x,u16 y,u16 w,u16 h,u8 rowNum,u8 colNum,u16 backColor)
{
	u16 len;
	sprintf(TFTStr,"void LCDLS_Frame(%d,%d,%d,%d,%d,%d,%d)\r\n",x,y,x+w-1,y+h-1,rowNum,colNum,backColor);
	len = strlen(TFTStr);	
	uart_SendDataToUart1(TFTStr,len);	
}
void disp_paraString(u8 *str,u16 xAxis,u16 yAxis)
{
	//LCD_PutString(xAxis,yAxis,str,CurrentFont,green, CurrentBackColor);
}

void disp_font8String(u8 *str,u16 xAxis,u16 yAxis)
{
	//LCD_PutString(xAxis,yAxis,str,FONT_8,CurrentPenColor, CurrentBackColor);
}

void disp_font16String(u8 *str,u16 xAxis,u16 yAxis)
{
	//LCD_PutString(xAxis,yAxis,str,FONT_16,CurrentPenColor, CurrentBackColor);
}

void disp_font24String(u8 *str,u16 xAxis,u16 yAxis)
{
	//LCD_PutString(xAxis,yAxis,str,FONT_24,CurrentPenColor, CurrentBackColor);
}

void disp_font32String(u8 *str,u16 xAxis,u16 yAxis)
{
	//LCD_PutString(xAxis,yAxis,str,FONT_32,CurrentPenColor, CurrentBackColor);
}

void disp_font48String(u8 *str,u16 xAxis,u16 yAxis)
{
	//LCD_PutString(xAxis,yAxis,str,FONT_48,CurrentPenColor, CurrentBackColor);
}

void disp_drawCross(u16 x,u16 y,u16 color)
{
//	LCD_Draw_LineH(x-12,y,25,color);	//横线
//	LCD_Draw_LineV(x,y-12,25,color);	//竖线
//	LCD_Point(x+1,y+1,color);
//	LCD_Point(x-1,y+1,color);
//	LCD_Point(x+1,y-1,color);
//	LCD_Point(x-1,y-1,color);

//	Draw_Circle(x,y,6,color);//画中心圈
}

//填充矩形
void disp_drawRectangle(u16 x,u16 y,u16 w,u16 h,u16 color)
{
	u16 len;
	sprintf(TFTStr,"void LCD_Fill(%d,%d,%d,%d,%d)\r\n",x,y,x+w-1,y+h-1,color);
	len = strlen(TFTStr);	
	uart_SendDataToUart1(TFTStr,len);
}

void disp_SetLine(u16 startY, u16 startX, u16 height, u16 width,u16 color)
{
	//LCD_Fill_Color(startX,startY,startX+width,startY+height,color);
}

void disp_drawRectangleFrame(u16 x,u16 y,u16 w,u16 h,u16 color)
{
	//LCD_DrawRectangle(x,y,w,h,color);
}

void disp_progressRect(void)
{
	//LCD_Fill_Color(progressX,progressY,progressX+progressW,progressY+progressH,progressBackColor);
}

u8 lastProgress = 0;
void disp_progress(u8 currentProgress)
{
//	u16 x,y,x2,w,h;
//	if(currentProgress > lastProgress)
//	{
//		x = progressX + 2+(u16)lastProgress*(progressW-4)/100;
//		x2 = progressX + 2+(u16)currentProgress*(progressW-4)/100;
//		y = progressY + 2;
//		w = x2 - x;
//		h = progressH - 4;
//		//disp_SetLine(progressY+2,x,progressH-4,w);
//		LCD_Fill_Color(x,y,x+w,y+h,progressFrontColor);
//	}
//	lastProgress = currentProgress;	
}

void disp_DrawCircle(u16 x0,u16 y0,u8 r,u16 Color)
{
	//Draw_Circle(x0,y0,r,Color);
}

void disp_DrawFullCircle(u16 x0,u16 y0,u8 r,u16 Color)
{
	//Draw_FullCircle(x0,y0,r,Color);
}

void disp_DrawRoundRect(u16 x,u16 y,u16 w,u16 h,u16 frontColor,u16 backColor)
{
	//DrawRoundRect(x,y,w,h,frontColor,backColor);
}

void disp_DrawPic(u16 x,u16 y,u32 bmp_address)
{
	u16 len;
	sprintf(TFTStr,"void LCDLS_FlashBMP(%d,%d,%d)\r\n",x,y,bmp_address);
	len = strlen(TFTStr);	
	uart_SendDataToUart1(TFTStr,len);
	//LCD_DrawPic(x, y, index,hyaline,hyalineColor);
}

void disp_lcdBLC(u8 light)
{
	u16 len;
	sprintf(TFTStr,"void LCDLS_BLC(%d)\r\n",light);
	len = strlen(TFTStr);	
	uart_SendDataToUart1(TFTStr,len);
	//LCD_DrawPic(x, y, index,hyaline,hyalineColor);
}
