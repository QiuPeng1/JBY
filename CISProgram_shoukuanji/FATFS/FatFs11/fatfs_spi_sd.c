/*
*********************************************************************************************************
*
*	模块名称 : 用于FAT驱动diskio.c调用的SPI_SD底层函数
*	文件名称 : fatfs_spi_sd.c
*	版    本 : V1.0
*	修改记录 :
*		版本号	日期       	作者	说明
*		V1.0	2015-7-5	JOY		
*
*********************************************************************************************************
*/


/* Includes ------------------------------------------------------------------*/
#include "diskio.h"		// FATFS底层函数
#include "spi_sd.h"		// SD_SPI底层函数

// 定义底层状态全局变量，DSTATUS数据类型
static volatile DSTATUS FATFS_SD_SPI_Status = STA_NOINIT;	/* Physical drive status */

/*
*********************************************************************************************************
*	函 数 名: FATFSdisk_SD_SDIO_Init
*	功能说明: 调用SDIO底层初始化函数，返回初始化状态
*	形    参：无
*	返 回 值: DSTATUS：成功返回0，失败返回STA_NOINIT
*********************************************************************************************************
*/
DSTATUS FATFSdisk_SD_SDIO_Init(void)
{
	if(SD_Init() == SD_OK)	// 执行SDIO初始化
	{
		FATFS_SD_SPI_Status &= ~STA_NOINIT;	/* Clear STA_NOINIT flag */
	}
	else
	{
		FATFS_SD_SPI_Status |= STA_NOINIT;
	}
	
	return FATFS_SD_SPI_Status;
}

/*
*********************************************************************************************************
*	函 数 名: FATFSdisk_SD_SDIO_Status
*	功能说明: 调用SDIO底层初始化函数，返回卡状态（是否写保护）
*	形    参：无
*	返 回 值: DSTATUS：写保护返回STA_PROTECT
*********************************************************************************************************
*/
DSTATUS FATFSdisk_SD_SDIO_Status(void) 
{
	// 原本应该是检查是否写保护函数，这里没使用写保护检查功能，只检查卡是否有响应
//	if(SD_GetStatus() != SD_TRANSFER_ERROR)	// 卡有响应
//	{
//		FATFS_SD_SPI_Status &= ~STA_PROTECT;
//	}
//	else
//	{
//		FATFS_SD_SPI_Status |= STA_PROTECT;
//	}
//	
//	return FATFS_SD_SPI_Status;
	return 0;
}

/*
*********************************************************************************************************
*	函 数 名: FATFSdisk_SD_SDIO_Read
*	功能说明: 调用SDIO底层初始化函数，返回卡操作状态 
*	形    参：BYTE *buff：指向读取接收数据的缓存器指针。
*			  DWORD sector：读操作的起始地址，扇区地址。
*			  UINT count：要读取的block数量，范围（1~255）。
*	返 回 值: DRESULT：返回磁盘操作结果，成功返回RES_OK
*********************************************************************************************************
*/
DRESULT FATFSdisk_SD_SDIO_Read(BYTE *buff, DWORD sector, UINT count) 
{
	SD_Error status = SD_OK;

	if ((FATFS_SD_SPI_Status & STA_NOINIT)) 
	{
		return RES_NOTRDY;
	}

	if(count==1)
	{
		status = SD_ReadBlock(buff, sector << 9, 512);
	}
	else
	{
		// 实际地址=扇区地址*512
		status = SD_ReadMultiBlocks(buff, sector << 9, 512, count);
	}
	if(status != SD_OK)
	{
		return RES_ERROR;
	}

	/* Check if the Transfer is finished */
	status =  SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);

	if (status != SD_OK) 
	{
		return RES_ERROR;
	}
	return RES_OK;
}

/*
*********************************************************************************************************
*	函 数 名: FATFSdisk_SD_SDIO_Write
*	功能说明: 调用SDIO底层初始化函数，返回卡操作状态
*	形    参：const BYTE *buff：指向发送数据缓存器的指针。
*			  DWORD sector：写操作的起始地址，扇区地址。
*			  UINT count：要写入的block数量，范围（1~255）。
*	返 回 值: DRESULT：返回磁盘操作结果，成功返回RES_OK
*********************************************************************************************************
*/
DRESULT FATFSdisk_SD_SDIO_Write(const BYTE *buff, DWORD sector, UINT count) 
{
	SD_Error status = SD_OK;

	if ((FATFS_SD_SPI_Status & STA_PROTECT))	// 写保护 
	{
		return RES_WRPRT;
	}
	
	if(count==1)
	{
		status = SD_WriteBlock((BYTE *)buff, sector << 9, 512);
	}
	else
	{
		// 实际地址=扇区地址*512
		// 由于DMA只支持4字节指针，所以在这里进行类型转换，提高效率
		SD_WriteMultiBlocks((BYTE *)buff, sector << 9, 512, count);
	}
	if(status != SD_OK)
	{
		return RES_ERROR;
	}

	/* Check if the Transfer is finished */
	status = SD_WaitWriteOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);     

	if (status != SD_OK) 
	{
		return RES_ERROR;
	}
	return RES_OK;
}

/*
*********************************************************************************************************
*	函 数 名: FATFSdisk_SD_SDIO_Ioctl
*	功能说明: 调用SDIO底层初始化函数，返回卡操作状态
*	形    参：BYTE cmd：控制码。
*			  char *buff：接收/发送控制数据缓冲器指针。
*	返 回 值: DRESULT：返回磁盘操作结果，成功返回RES_OK
*********************************************************************************************************
*/
DRESULT FATFSdisk_SD_SDIO_Ioctl(BYTE cmd, char *buff) 
{
// 写控制命令码，取值参见diskio.h /* Command code for disk_ioctrl fucntion */
// 如CTRL_SYNC, GET_SECTOR_SIZE, GET_SECTOR_COUNT, GET_BLOCK_SIZE	
	switch (cmd) 
	{
		case GET_SECTOR_SIZE :     // Get R/W sector size (WORD) 
			*(WORD * )buff = 512;
		break;
		case GET_BLOCK_SIZE :      // Get erase block size in unit of sector (DWORD)
			*(DWORD * )buff = 32;
		break;
		case CTRL_SYNC :
		break;
	}

	return RES_OK;
}


