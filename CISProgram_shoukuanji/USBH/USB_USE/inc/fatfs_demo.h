/*
*********************************************************************************************************
*
*	模块名称 : SD卡文件系统应用函数
*	文件名称 : fatfs_sd.c
*	版    本 : V1.0（基于FatFs R0.10b (C)ChaN, 2014）
*	说    明 : 封装一些ff.c中的函数，便于使用
*	修改记录 :
*		版本号	日期       	作者	说明
*		V1.0	2014-10-21	JOY		
*
*********************************************************************************************************
*/
#ifndef __FATFS_DEMO_H
#define __FATFS_DEMO_H

#include "stm32f10x.h"
#include "ff.h"

// 位图文件头和信息结构定义
typedef struct tagBITMAPFILEHEADER	// 位图文件头，共14字节
{
//	WORD bfType;		/* should be two characters, 'BM"   注释掉，否则结构体长度不对，读文件时错位 2字节*/
	DWORD bfSize;		/* Size of file in bytes 文件大小	4字节*/
	WORD bfReserved1;	/* 0 保留							2字节*/
	WORD bfReserved2;	/* 0 保留							2字节*/
	DWORD bfOffBits;	/* Offset to the start of the image data 位图数据起始字节数 4字节*/
} BITMAPFILEHEADER;	

typedef struct tagBITMAPINFOHEADER	// 位图信息头DIB，共40字节
{ /* bmih */
	DWORD biSize;		/* Specifies the number of bytes required by the structure. 信息头字节数40	4字节*/
	LONG biWidth;		/* Specifies the width of the bitmap, in pixels. 图像像素宽度	4字节有符号*/
	LONG biHeight;		/* Specifies the height of the bitmap, in pixels. 图像像素高度	4字节有符号*/
		/* If biHeight is positive, the bitmap is a bottom-up DIB and its origin is the lower left corner. 
		If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper left corner. */
		// 如果图像高度为正，则位图数据从下到上，原点在左下角；高度为负，则位图数据从上到下，原点在右上角
	WORD biPlanes;		/* Specifies the number of planes for the target device. 
						This value must be set to 1. 色彩平面数，固定为1	2字节*/
	WORD biBitCount;	/* Specifies the number of bits per pixel. This value must be 1, 4, 8, 16, 24, or 32. */
						// 每个像素所占位数，即图像深度，只为1,4,8,16,24或32	2字节
	DWORD biCompression;/* Specifies the type of compression for a
   									compressed bottom-up bitmap (top-down DIBs
                              cannot be compressed). It can be one of the
                               following values:
   						         Value	Description
										BI_RGB		An uncompressed format.
										BI_RLE8	A run-length encoded (RLE) format for
                              bitmaps with 8 bits per pixel. The compression
                              format is a two-byte format consisting of a count
                              byte followed by a byte containing a color index.

                              BI_RLE4	An RLE format for bitmaps with 4 bits per
                              pixel. The compression format is a two-byte format
                              consisting of a count byte followed by two word-
                              length color indices.

										BI_BITFIELDS	Specifies that the bitmap is not
                              compressed and that the color table consists of
                              three doubleword color masks that specify the red,
                              green, and blue components, respectively, of each
                              pixel. This is valid when used with 16- and
                              32-bits-per-pixel bitmaps. 压缩方式，0表示不压缩	4字节*/
	DWORD biSizeImage;	/*Size of the image, in bytes. Can be 0 if the
						bitmap is in the BI_RGB format.  位图数据字节数		4字节*/

	LONG biXPelsPerMeter;	/*Specifies the horizontal resolution, in pixels
                               per meter, of the target device for the bitmap.
                               Use this value to select a bitmap from a resource
                               group that best matches the characteristics of
                               the current device. 图像水平分辨率	4字节有符号数*/

	LONG biYPelsPerMeter;	/*Specifies the vertical resolution, in pixels per
							meter, of the target device. 图像垂直分辨率	4字节有符号数*/
	DWORD biClrUsed;		/*Specifies the number of color indexes in the color
							table actually used by the bitmap. If this value
                              is 0, the bitmap uses the maximum number of colors
                              corresponding to the value of the biBitCount member.
										For 16-bit applications, if biClrUsed is nonzero,
                              it specifies the actual number of colors that the
                              graphics engine or device driver will access if
                              the biBitCount member is less than 24.
                              If biBitCount is set to 24, biClrUsed specifies
                              the size of the reference color table used to
                              optimize performance of color palettes.
										For 32-bit applications, if biClrUsed is nonzero
                              and the biBitCount member is less than 16, the
                              biClrUsed member specifies the actual number of
                              colors the graphics engine or device driver accesses.
                              If biBitCount is 16 or greater, then biClrUsed
                              member specifies the size of the color table used
                              to optimize performance of Windows color palettes.
                              For biBitCount equal to 16 or 32 the optimal
                              color palette starts immediately following
                              the 3 DWORD masks.

										If the bitmap is a packed bitmap (that is, a
                              bitmap in which the bitmap array immediately
                              follows the BITMAPINFO header and which is
                              referenced by a single pointer), the biClrUsed
                              member must be set to zero or to the actual
                              size of the color table. 调色板颜色数，为0表示颜色数为默认的2^颜色深度	4字节*/

	DWORD biClrImportant;	/*Specifies the number of color indexes that are
							considered important for displaying the bitmap.
							If this value is zero, all colors are important.*/
							// 重要颜色数，为0表示所有颜色都重要，通常不使用本项。	4字节
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD			// 位图颜色表，biBitCount=24时，没有颜色表项
{ /* rgbq */
    BYTE    rgbBlue;		// 0~255
    BYTE    rgbGreen;		// 0~255
    BYTE    rgbRed;			// 0~255
    BYTE    rgbReserved;	// 保留，必须为0
} RGBQUAD;

// 位图文件头+信息头 共54字节
typedef struct tagBITMAPINFO
{ /* bmi */
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;
} BITMAPINFO; 
//***实际使用时，如果BITMAPFILEHEADER类型包括bfType时，bmiHeader地址-bmfHeader地址=16，而不是14!!
//***实际使用时，如果BITMAPFILEHEADER类型不包括bfType时，bmiHeader地址-bmfHeader地址=12，与实际头文件14-2一致!!	

// FatFs文件系统用全局变量，声明后便于上层文件调用
extern FATFS fs;
extern FIL file;
extern FRESULT res;


FRESULT FATFS_DriveSize(uint32_t* total, uint32_t* free);
FRESULT scan_files(char *path);/* Start node to be scanned (also used as work area) */

FRESULT CreateFile(char *filename);	// 新建文件，如果文件重名，则覆盖
FRESULT DeleteFile(char *filename);	// 删除文件
// 不支持非空文件夹删除，不能为当前文件夹，不能为打开的文件，不能为制度文件
// 写入数据
// mode = 0, 如果文件存在，则继续写入；如果文件不存在，则创建文件，并写入
// mode = 1, 如果文件存在，则清除旧内容后，写入；如果文件不存在，则创建文件，并写入
FRESULT WriteFile(char *filename, const void *buff, char mode);
// 读取文件数据，通过串口输出
FRESULT ReadFile2(char *filename);
#endif
