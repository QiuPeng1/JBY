/*
*********************************************************************************************************
*
*	模块名称 : 用于FAT驱动diskio.c调用的SDIO底层函数
*	文件名称 : fatfs_sdio_sd.c
*	版    本 : V1.0
*	修改记录 :
*		版本号	日期       	作者	说明
*		V1.0	2014-1-18	JOY		
*
*********************************************************************************************************
*/

#ifndef __FATFS_SDIO_SD_H
#define __FATFS_SDIO_SD_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "diskio.h"		// FATFS底层函数

	 
DSTATUS FATFSdisk_SD_SDIO_Init(void);
DSTATUS FATFSdisk_SD_SDIO_Status(void);
DRESULT FATFSdisk_SD_SDIO_Read(BYTE *buff, DWORD sector, UINT count);
DRESULT FATFSdisk_SD_SDIO_Write(const BYTE *buff, DWORD sector, UINT count); 
DRESULT FATFSdisk_SD_SDIO_Ioctl(BYTE cmd, char *buff);	 
#endif
