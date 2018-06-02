/*
*********************************************************************************************************
*
*	ģ������ : ����FAT����diskio.c���õ�SDIO�ײ㺯��
*	�ļ����� : fatfs_sdio_sd.c
*	��    �� : V1.0
*	�޸ļ�¼ :
*		�汾��	����       	����	˵��
*		V1.0	2014-1-18	JOY		
*
*********************************************************************************************************
*/

#ifndef __FATFS_SDIO_SD_H
#define __FATFS_SDIO_SD_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "diskio.h"		// FATFS�ײ㺯��

	 
DSTATUS FATFSdisk_SD_SDIO_Init(void);
DSTATUS FATFSdisk_SD_SDIO_Status(void);
DRESULT FATFSdisk_SD_SDIO_Read(BYTE *buff, DWORD sector, UINT count);
DRESULT FATFSdisk_SD_SDIO_Write(const BYTE *buff, DWORD sector, UINT count); 
DRESULT FATFSdisk_SD_SDIO_Ioctl(BYTE cmd, char *buff);	 
#endif
