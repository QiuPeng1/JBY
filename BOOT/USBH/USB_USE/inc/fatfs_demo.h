/*
*********************************************************************************************************
*
*	ģ������ : SD���ļ�ϵͳӦ�ú���
*	�ļ����� : fatfs_sd.c
*	��    �� : V1.0������FatFs R0.10b (C)ChaN, 2014��
*	˵    �� : ��װһЩff.c�еĺ���������ʹ��
*	�޸ļ�¼ :
*		�汾��	����       	����	˵��
*		V1.0	2014-10-21	JOY		
*
*********************************************************************************************************
*/
#ifndef __FATFS_DEMO_H
#define __FATFS_DEMO_H

#include "stm32f10x.h"
#include "ff.h"

// λͼ�ļ�ͷ����Ϣ�ṹ����
typedef struct tagBITMAPFILEHEADER	// λͼ�ļ�ͷ����14�ֽ�
{
//	WORD bfType;		/* should be two characters, 'BM"   ע�͵�������ṹ�峤�Ȳ��ԣ����ļ�ʱ��λ 2�ֽ�*/
	DWORD bfSize;		/* Size of file in bytes �ļ���С	4�ֽ�*/
	WORD bfReserved1;	/* 0 ����							2�ֽ�*/
	WORD bfReserved2;	/* 0 ����							2�ֽ�*/
	DWORD bfOffBits;	/* Offset to the start of the image data λͼ������ʼ�ֽ��� 4�ֽ�*/
} BITMAPFILEHEADER;	

typedef struct tagBITMAPINFOHEADER	// λͼ��ϢͷDIB����40�ֽ�
{ /* bmih */
	DWORD biSize;		/* Specifies the number of bytes required by the structure. ��Ϣͷ�ֽ���40	4�ֽ�*/
	LONG biWidth;		/* Specifies the width of the bitmap, in pixels. ͼ�����ؿ��	4�ֽ��з���*/
	LONG biHeight;		/* Specifies the height of the bitmap, in pixels. ͼ�����ظ߶�	4�ֽ��з���*/
		/* If biHeight is positive, the bitmap is a bottom-up DIB and its origin is the lower left corner. 
		If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper left corner. */
		// ���ͼ��߶�Ϊ������λͼ���ݴ��µ��ϣ�ԭ�������½ǣ��߶�Ϊ������λͼ���ݴ��ϵ��£�ԭ�������Ͻ�
	WORD biPlanes;		/* Specifies the number of planes for the target device. 
						This value must be set to 1. ɫ��ƽ�������̶�Ϊ1	2�ֽ�*/
	WORD biBitCount;	/* Specifies the number of bits per pixel. This value must be 1, 4, 8, 16, 24, or 32. */
						// ÿ��������ռλ������ͼ����ȣ�ֻΪ1,4,8,16,24��32	2�ֽ�
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
                              32-bits-per-pixel bitmaps. ѹ����ʽ��0��ʾ��ѹ��	4�ֽ�*/
	DWORD biSizeImage;	/*Size of the image, in bytes. Can be 0 if the
						bitmap is in the BI_RGB format.  λͼ�����ֽ���		4�ֽ�*/

	LONG biXPelsPerMeter;	/*Specifies the horizontal resolution, in pixels
                               per meter, of the target device for the bitmap.
                               Use this value to select a bitmap from a resource
                               group that best matches the characteristics of
                               the current device. ͼ��ˮƽ�ֱ���	4�ֽ��з�����*/

	LONG biYPelsPerMeter;	/*Specifies the vertical resolution, in pixels per
							meter, of the target device. ͼ��ֱ�ֱ���	4�ֽ��з�����*/
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
                              size of the color table. ��ɫ����ɫ����Ϊ0��ʾ��ɫ��ΪĬ�ϵ�2^��ɫ���	4�ֽ�*/

	DWORD biClrImportant;	/*Specifies the number of color indexes that are
							considered important for displaying the bitmap.
							If this value is zero, all colors are important.*/
							// ��Ҫ��ɫ����Ϊ0��ʾ������ɫ����Ҫ��ͨ����ʹ�ñ��	4�ֽ�
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD			// λͼ��ɫ��biBitCount=24ʱ��û����ɫ����
{ /* rgbq */
    BYTE    rgbBlue;		// 0~255
    BYTE    rgbGreen;		// 0~255
    BYTE    rgbRed;			// 0~255
    BYTE    rgbReserved;	// ����������Ϊ0
} RGBQUAD;

// λͼ�ļ�ͷ+��Ϣͷ ��54�ֽ�
typedef struct tagBITMAPINFO
{ /* bmi */
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;
} BITMAPINFO; 
//***ʵ��ʹ��ʱ�����BITMAPFILEHEADER���Ͱ���bfTypeʱ��bmiHeader��ַ-bmfHeader��ַ=16��������14!!
//***ʵ��ʹ��ʱ�����BITMAPFILEHEADER���Ͳ�����bfTypeʱ��bmiHeader��ַ-bmfHeader��ַ=12����ʵ��ͷ�ļ�14-2һ��!!	

// FatFs�ļ�ϵͳ��ȫ�ֱ���������������ϲ��ļ�����
extern FATFS fs;
extern FIL file;
extern FRESULT res;


FRESULT FATFS_DriveSize(uint32_t* total, uint32_t* free);
FRESULT scan_files(char *path);/* Start node to be scanned (also used as work area) */

FRESULT CreateFile(char *filename);	// �½��ļ�������ļ��������򸲸�
FRESULT DeleteFile(char *filename);	// ɾ���ļ�
// ��֧�ַǿ��ļ���ɾ��������Ϊ��ǰ�ļ��У�����Ϊ�򿪵��ļ�������Ϊ�ƶ��ļ�
// д������
// mode = 0, ����ļ����ڣ������д�룻����ļ������ڣ��򴴽��ļ�����д��
// mode = 1, ����ļ����ڣ�����������ݺ�д�룻����ļ������ڣ��򴴽��ļ�����д��
FRESULT WriteFile(char *filename, const void *buff, char mode);
// ��ȡ�ļ����ݣ�ͨ���������
FRESULT ReadFile2(char *filename);
#endif
