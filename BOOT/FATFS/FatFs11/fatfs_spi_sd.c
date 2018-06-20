/*
*********************************************************************************************************
*
*	ģ������ : ����FAT����diskio.c���õ�SPI_SD�ײ㺯��
*	�ļ����� : fatfs_spi_sd.c
*	��    �� : V1.0
*	�޸ļ�¼ :
*		�汾��	����       	����	˵��
*		V1.0	2015-7-5	JOY		
*
*********************************************************************************************************
*/


/* Includes ------------------------------------------------------------------*/
#include "diskio.h"		// FATFS�ײ㺯��
#include "spi_sd.h"		// SD_SPI�ײ㺯��

// ����ײ�״̬ȫ�ֱ�����DSTATUS��������
static volatile DSTATUS FATFS_SD_SPI_Status = STA_NOINIT;	/* Physical drive status */

/*
*********************************************************************************************************
*	�� �� ��: FATFSdisk_SD_SDIO_Init
*	����˵��: ����SDIO�ײ��ʼ�����������س�ʼ��״̬
*	��    �Σ���
*	�� �� ֵ: DSTATUS���ɹ�����0��ʧ�ܷ���STA_NOINIT
*********************************************************************************************************
*/
DSTATUS FATFSdisk_SD_SDIO_Init(void)
{
	if(SD_Init() == SD_OK)	// ִ��SDIO��ʼ��
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
*	�� �� ��: FATFSdisk_SD_SDIO_Status
*	����˵��: ����SDIO�ײ��ʼ�����������ؿ�״̬���Ƿ�д������
*	��    �Σ���
*	�� �� ֵ: DSTATUS��д��������STA_PROTECT
*********************************************************************************************************
*/
DSTATUS FATFSdisk_SD_SDIO_Status(void) 
{
	// ԭ��Ӧ���Ǽ���Ƿ�д��������������ûʹ��д������鹦�ܣ�ֻ��鿨�Ƿ�����Ӧ
//	if(SD_GetStatus() != SD_TRANSFER_ERROR)	// ������Ӧ
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
*	�� �� ��: FATFSdisk_SD_SDIO_Read
*	����˵��: ����SDIO�ײ��ʼ�����������ؿ�����״̬ 
*	��    �Σ�BYTE *buff��ָ���ȡ�������ݵĻ�����ָ�롣
*			  DWORD sector������������ʼ��ַ��������ַ��
*			  UINT count��Ҫ��ȡ��block��������Χ��1~255����
*	�� �� ֵ: DRESULT�����ش��̲���������ɹ�����RES_OK
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
		// ʵ�ʵ�ַ=������ַ*512
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
*	�� �� ��: FATFSdisk_SD_SDIO_Write
*	����˵��: ����SDIO�ײ��ʼ�����������ؿ�����״̬
*	��    �Σ�const BYTE *buff��ָ�������ݻ�������ָ�롣
*			  DWORD sector��д��������ʼ��ַ��������ַ��
*			  UINT count��Ҫд���block��������Χ��1~255����
*	�� �� ֵ: DRESULT�����ش��̲���������ɹ�����RES_OK
*********************************************************************************************************
*/
DRESULT FATFSdisk_SD_SDIO_Write(const BYTE *buff, DWORD sector, UINT count) 
{
	SD_Error status = SD_OK;

	if ((FATFS_SD_SPI_Status & STA_PROTECT))	// д���� 
	{
		return RES_WRPRT;
	}
	
	if(count==1)
	{
		status = SD_WriteBlock((BYTE *)buff, sector << 9, 512);
	}
	else
	{
		// ʵ�ʵ�ַ=������ַ*512
		// ����DMAֻ֧��4�ֽ�ָ�룬�����������������ת�������Ч��
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
*	�� �� ��: FATFSdisk_SD_SDIO_Ioctl
*	����˵��: ����SDIO�ײ��ʼ�����������ؿ�����״̬
*	��    �Σ�BYTE cmd�������롣
*			  char *buff������/���Ϳ������ݻ�����ָ�롣
*	�� �� ֵ: DRESULT�����ش��̲���������ɹ�����RES_OK
*********************************************************************************************************
*/
DRESULT FATFSdisk_SD_SDIO_Ioctl(BYTE cmd, char *buff) 
{
// д���������룬ȡֵ�μ�diskio.h /* Command code for disk_ioctrl fucntion */
// ��CTRL_SYNC, GET_SECTOR_SIZE, GET_SECTOR_COUNT, GET_BLOCK_SIZE	
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


