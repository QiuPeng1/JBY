/*
*********************************************************************************************************
*
*	ģ������ : SD���ļ�ϵͳӦ�ú���
*	�ļ����� : fatfs_sd.c
*	��    �� : V1.0������FatFs R0.10b (C)ChaN, 2014��
*	˵    �� : ��װһЩff.c�еĺ���������ʹ��.
*			   ֧��BMPͼ����ʾ
*	�޸ļ�¼ :
*		�汾��	����       	����	˵��
*		V1.0	2014-10-21	JOY		
*
*********************************************************************************************************
*/
#include "fatfs_demo.h"
#include <stdio.h>
#include <string.h>


#include <stdlib.h>	// calloc

#include "usbh_usr.h"

FATFS fs;   /* ��Ҫ���ó�ȫ�ֱ��� */
FIL file;
FRESULT res;

char pathname[_MAX_LFN+1];
/* ���ڲ��Զ�д�ٶ� */
#define TEST_FILE_LEN			(2*1024*1024)	/* ���ڲ��Ե��ļ����� */
#define BUF_SIZE				512				/* ÿ�ζ�дSD����������ݳ��� */
uint8_t g_TestBuf[BUF_SIZE];
extern __IO int32_t g_iRunTime;	/* ȫ������ʱ�䣬��λ1ms�����ڼ���ϵͳ����ʱ�� */

//#define IMAGE_BUFFER_SIZE    660
//uint8_t Image_Buf[IMAGE_BUFFER_SIZE];
//#define RGB24TORGB16(R,G,B) ((uint16_t)((((R)>>3)<<11) | (((G)>>2)<<5)	| ((B)>>3)	))
//#define WIDTHBYTES(bits) (((bits)+31)/32*4)		//����24λ���ɫ ÿһ�е����ؿ�ȱ���ʱ4�ı���  ����0����

//void ShowBmpHeader(BITMAPFILEHEADER* pBmpHead);
//void ShowBmpInfoHeader(BITMAPINFOHEADER* pBmpInforHead);
//static void Show_ImageBMP1(uint8_t _x, uint8_t _y);	// test
//static void Show_ImageBMP(uint8_t _x, uint8_t _y);
//static void Show_ImageGIF(uint8_t _x, uint8_t _y);
//FRESULT FATFS_ShowBMP(uint8_t _x, uint8_t _y, char *_bmppathname);

//extern const uint16_t TextColor, BackColor;	// ����ɫ0xF807Ϊ��ɫ(ԭʼ��0xFF003B)
//extern FONT_T tFont;
extern USB_OTG_CORE_HANDLE		USB_OTG_Core;

/*
*********************************************************************************************************
*	�� �� ��: FATFS_DriveSize
*	����˵��: ��õ�ǰ�����ܴ�С�Ϳ���ռ��С
*	��    ��: uint32_t* total���ܿռ��С����λKiB
*			  uint32_t* free������ռ��С����λKiB
*	�� �� ֵ: FRESULT���ɹ�����FR_OK
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
*	�� �� ��: ViewRootDir
*	����˵��: ɨ��SD��ָ��Ŀ¼�µ��ļ�����ʾͼƬ�ļ���bmp��gif��ʽ��
*	��    �Σ�char *path��ɨ��ָ��·��
*	�� �� ֵ: ��
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
				res = scan_files(fn);       //�����ݹ����
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

// �½��ļ�������ļ��������򸲸�
FRESULT CreateFile(char *filename)
{
	FRESULT result;
	
	// ǰ���Ѿ����غ��ļ�ϵͳ
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
// ɾ���ļ�
// ��֧�ַǿ��ļ���ɾ��������Ϊ��ǰ�ļ��У�����Ϊ�򿪵��ļ�������Ϊ�ƶ��ļ�
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
// д������
// mode = 0, ����ļ����ڣ������д�룻����ļ������ڣ��򴴽��ļ�����д��
// mode = 1, ����ļ����ڣ�����������ݺ�д�룻����ļ������ڣ��򴴽��ļ�����д��
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
			f_lseek(&file,0);	// ָ��ص��ļ���ͷ
			f_truncate(&file);	// �ڵ�ǰָ��λ�ô��ض�
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

// ��ȡ�ļ����ݣ�ͨ���������
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
//		printf("> ��ȡ�ļ���ɣ�\r\n");
		
		f_close(&file);
	}
//	else
//		printf("> ! Failed to read the file(%d).\r\n",result);
	return result;
}



