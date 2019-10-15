/*
*********************************************************************************************************
*
*	模块名称 : SD卡文件系统应用函数
*	文件名称 : fatfs_sd.c
*	版    本 : V1.0（基于FatFs R0.10b (C)ChaN, 2014）
*	说    明 : 封装一些ff.c中的函数，便于使用.
*			   支持BMP图像显示
*	修改记录 :
*		版本号	日期       	作者	说明
*		V1.0	2014-10-21	JOY		
*
*********************************************************************************************************
*/
#include "fatfs_demo.h"
#include <stdio.h>
#include <string.h>


#include <stdlib.h>	// calloc

#include "usbh_usr.h"

FATFS fs;   /* 需要设置成全局变量 */
FIL file;
FRESULT res;

char pathname[_MAX_LFN+1];
/* 用于测试读写速度 */
#define TEST_FILE_LEN			(2*1024*1024)	/* 用于测试的文件长度 */
#define BUF_SIZE				512				/* 每次读写SD卡的最大数据长度 */
uint8_t g_TestBuf[BUF_SIZE];
extern __IO int32_t g_iRunTime;	/* 全局运行时间，单位1ms，用于计算系统运行时间 */

//#define IMAGE_BUFFER_SIZE    660
//uint8_t Image_Buf[IMAGE_BUFFER_SIZE];
//#define RGB24TORGB16(R,G,B) ((uint16_t)((((R)>>3)<<11) | (((G)>>2)<<5)	| ((B)>>3)	))
//#define WIDTHBYTES(bits) (((bits)+31)/32*4)		//对于24位真彩色 每一行的像素宽度必须时4的倍数  否则补0补齐

//void ShowBmpHeader(BITMAPFILEHEADER* pBmpHead);
//void ShowBmpInfoHeader(BITMAPINFOHEADER* pBmpInforHead);
//static void Show_ImageBMP1(uint8_t _x, uint8_t _y);	// test
//static void Show_ImageBMP(uint8_t _x, uint8_t _y);
//static void Show_ImageGIF(uint8_t _x, uint8_t _y);
//FRESULT FATFS_ShowBMP(uint8_t _x, uint8_t _y, char *_bmppathname);

//extern const uint16_t TextColor, BackColor;	// 背景色0xF807为红色(原始：0xFF003B)
//extern FONT_T tFont;
extern USB_OTG_CORE_HANDLE		USB_OTG_Core;

/*
*********************************************************************************************************
*	函 数 名: FATFS_DriveSize
*	功能说明: 获得当前磁盘总大小和空余空间大小
*	形    参: uint32_t* total：总空间大小，单位KiB
*			  uint32_t* free：空余空间大小，单位KiB
*	返 回 值: FRESULT：成功返回FR_OK
*********************************************************************************************************
*/
FRESULT FATFS_DriveSize(uint32_t* total, uint32_t* free) 
{ 
	FATFS *fs;
    DWORD fre_clust; 

    /* Get volume information and free clusters of drive */ 
    res = f_getfree("0:", &fre_clust, &fs); 
    if (res != FR_OK) 
	{ 
		return res; 
	} 

    /* Get total sectors and free sectors */ 
    *total = (fs->n_fatent - 2) * fs->csize / 2; 
    *free = fre_clust * fs->csize / 2; 
	 
	/* Return OK */ 
	return FR_OK; 
} 


/*
*********************************************************************************************************
*	函 数 名: ViewRootDir
*	功能说明: 扫描SD卡指定目录下的文件，显示图片文件（bmp和gif格式）
*	形    参：char *path：扫描指定路径
*	返 回 值: 无
*********************************************************************************************************
*/
uint16_t FileCount=0;	
FRESULT scan_files (
    char *path        /* Start node to be scanned (also used as work area) */
)
{
    FILINFO fno;
    DIR dir;
//    BYTE i;
    char *fn;   /* This function is assuming non-Unicode cfg. */
	
#if _USE_LFN
    static char lfn[_MAX_LFN + 1];   /* Buffer to store the LFN */
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif

    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) 
	{
//        i = strlen(path);
//		printf("Name\t\tSize\r\n");
        while(HCD_IsDeviceConnected(&USB_OTG_Core))
		{
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) 
			{
				break;  /* Break on error or end of dir */
			}
            if (fno.fname[0] == '.') 
			{
				continue;             /* Ignore dot entry */
			}
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
			strcpy(pathname, fn);
            if ((fno.fattrib & AM_MASK) == AM_DIR) /* It is a directory */
			{      
				sprintf(fn, "%s/%s", path,pathname);
//				printf("%s/",fn);
				res = scan_files(fn);       //函数递归调用
                if (res != FR_OK) break;

            } 
			else /* It is a file. */
			{             
				FileCount++;

            }

        }	
    }
	if(FileCount) res = FR_OK;	
    return res;
}

// 新建文件，如果文件重名，则覆盖
FRESULT CreateFile(char *filename)
{
	FRESULT result;
	
	// 前提已经挂载好文件系统
	result = f_open(&file,filename, FA_CREATE_ALWAYS);
	if( result== FR_OK)
	{
//		printf("> %s is created.\r\n", filename);
		f_close(&file);		
	}
//	else
//		printf("> ! Failed to create the file \"%s\"(%d).\r\n", filename,result);
	return result;
}
// 删除文件
// 不支持非空文件夹删除，不能为当前文件夹，不能为打开的文件，不能为制度文件
FRESULT DeleteFile(char *filename)
{
	FRESULT result;
	result = f_unlink(filename);
//	if(result == FR_OK)
//	{
//		printf("> %s is deleted.\r\n", filename);
//	}
//	else
//		printf("> ! Failed to delete the file \"%s\"(%d).\r\n",filename,result);
	return result;
}
// 写入数据
// mode = 0, 如果文件存在，则继续写入；如果文件不存在，则创建文件，并写入
// mode = 1, 如果文件存在，则清除旧内容后，写入；如果文件不存在，则创建文件，并写入
FRESULT WriteFile(char *filename, const void *buff, char mode)
{
	FRESULT result;
	result = f_open(&file, filename, FA_WRITE | FA_OPEN_ALWAYS);
	if(result == FR_OK)
	{		
		if(mode == 0)
		{
			f_lseek(&file, f_size(&file));
			f_puts(buff, &file);
		}
		else
		{
			f_lseek(&file,0);	// 指针回到文件开头
			f_truncate(&file);	// 在当前指针位置处截断
			f_puts(buff, &file);
			f_sync(&file);	
		}
//		printf("> %s is written.\r\n", filename);
		f_close(&file);
	}
//	else
//		printf("> ! Failed to write the file \"%s\"(%d).\r\n",filename,result);
	return result;
}

// 读取文件数据，通过串口输出
FRESULT ReadFile2(char *filename)
{
	FRESULT result;
	char buffer[512];
	uint16_t i;
	
	result = f_open(&file, filename, FA_READ | FA_OPEN_EXISTING);
	if(result == FR_OK)
	{
//		printf("> Open the file %s\r\n", filename);
		for(i=0;f_eof(&file)==0; i++)
		{
			if(f_gets(buffer, sizeof(buffer), &file))
			{
//				printf("%s\r\n", buffer);							
			}
		}					
//		printf("> 读取文件完成！\r\n");
		
		f_close(&file);
	}
//	else
//		printf("> ! Failed to read the file(%d).\r\n",result);
	return result;
}



