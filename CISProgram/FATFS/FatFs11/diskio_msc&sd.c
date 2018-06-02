/*
*********************************************************************************************************
*
*	ģ������ : ����FAT�ײ�����������USB��SDIO�ĵײ�����
*	�ļ����� : diskio_msc&sd.c
*	��    �� : V1.0
*	�޸ļ�¼ :
*		�汾��	����       	����	˵��
*		V1.0	2015-7-5	JOY		
*
*********************************************************************************************************
*/
#include "diskio.h"
#include "usb_conf.h"
#include "usbh_msc_core.h"
//#include "fatfs_sdio_sd.h"
//#include "spi_sd.h"

/* ����������������� Definitions of physical drive number for each drive */
#define USB		0	// ��ű���Ϊ0
#define SD		1

/*--------------------------------------------------------------------------

Module Private Functions and Variables

---------------------------------------------------------------------------*/
static volatile DSTATUS Stat = STA_NOINIT;	/* Disk status */

// USB��
extern USB_OTG_CORE_HANDLE		USB_OTG_Core;
extern USBH_HOST				USB_Host;

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
                         BYTE drv		/* Physical drive number (0) */
                           )
{
	switch(drv)
	{
		case USB:		// USB HOST U��
		{
			if(HCD_IsDeviceConnected(&USB_OTG_Core))
			{  
				Stat &= ~STA_NOINIT;
			}
		}
		break;
			
		case SD:		// SD��
		/*{	
//			Stat = FATFSdisk_SD_SDIO_Init();
			if(SD_Init() == SD_RESPONSE_NO_ERROR)	// ִ��SD��ʼ��
			{
				Stat &= ~STA_NOINIT;	// Clear STA_NOINIT flag 
			}
			else
			{
				Stat |= STA_NOINIT;
			}	
		}*/		
		break;
	}
	return Stat;
  
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
                     BYTE drv		/* Physical drive number (0) */
                       )
{
	switch(drv)
	{
		case USB:		// USB HOST U��
			Stat = 0;
			break;
		
		case SD:		// SD��
			Stat = 0;
			break;
	}
	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
                   BYTE drv,			/* Physical drive number (0) */
                   BYTE *buff,			/* Pointer to the data buffer to store read data */
                   DWORD sector,		/* Start sector number (LBA) */
                   UINT count			/* Sector count (1..255) */
                     )
{
	DRESULT res = RES_PARERR;
	
	switch(drv)
	{
		case USB:		// USB HOST U��		
		{
			BYTE status = USBH_MSC_OK;
			if (drv || !count) return RES_PARERR;
			if (Stat & STA_NOINIT) return RES_NOTRDY;

			if(HCD_IsDeviceConnected(&USB_OTG_Core))
			{  
				do
				{
					status = USBH_MSC_Read10(&USB_OTG_Core, buff,sector,512 * count);
					USBH_MSC_HandleBOTXfer(&USB_OTG_Core ,&USB_Host);

					if(!HCD_IsDeviceConnected(&USB_OTG_Core))
					{ 
						res =  RES_ERROR;
						break;
					}      
				}
				while(status == USBH_MSC_BUSY );
			}

			if(status == USBH_MSC_OK)
				res =  RES_OK;
			else
				res = RES_ERROR;
		}
		break;
			
		case SD:		// SD��
		/*{
//			res = FATFSdisk_SD_SDIO_Read(buff, sector, count);
			SD_Error status = SD_RESPONSE_NO_ERROR;

			if(count==1)
			{
				status = SD_ReadBlock(buff, sector << 9, SD_BLOCK_SIZE);
			}
			else
			{
				// ʵ�ʵ�ַ=������ַ*512
				status = SD_ReadMultiBlocks(buff, sector << 9, SD_BLOCK_SIZE, count);
			}
			
			if(status != SD_RESPONSE_NO_ERROR)
				res = RES_ERROR;
			else
				res = RES_OK;
		}*/
		break;
	}
	return res;
  
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
DRESULT disk_write (
                    BYTE drv,			/* Physical drive number (0) */
                    const BYTE *buff,	/* Pointer to the data to be written */
                    DWORD sector,		/* Start sector number (LBA) */
                    UINT count			/* Sector count (1..255) */
                      )
{
	DRESULT res = RES_PARERR;
	BYTE status = USBH_MSC_OK;
	
	switch(drv)
	{
		case USB:		// USB HOST U��	
		{			
			if (drv || !count) return RES_PARERR;
			if (Stat & STA_NOINIT) return RES_NOTRDY;
			if (Stat & STA_PROTECT) return RES_WRPRT;

			if(HCD_IsDeviceConnected(&USB_OTG_Core))
			{  
				do
				{
					status = USBH_MSC_Write10(&USB_OTG_Core,(BYTE*)buff,sector,512 * count);
					USBH_MSC_HandleBOTXfer(&USB_OTG_Core, &USB_Host);

					if(!HCD_IsDeviceConnected(&USB_OTG_Core))
					{ 
						res = RES_ERROR;
						break;
					}
				}
				while(status == USBH_MSC_BUSY );
			}

			if(status == USBH_MSC_OK)
				res = RES_OK;
			else
				res = RES_ERROR;
		}
		break;
		
		case SD:		// SD��
		/*{
//			res = FATFSdisk_SD_SDIO_Write((BYTE *)buff, sector, count); 
			SD_Error status = SD_RESPONSE_NO_ERROR;
			
			if(SD_Detect() == SD_NOT_PRESENT)
				return RES_NOTRDY;
			if(count==1)
			{
				status = SD_WriteBlock((BYTE *)buff, sector << 9, SD_BLOCK_SIZE);
			}
			else
			{
				// ʵ�ʵ�ַ=������ַ*512
				SD_WriteMultiBlocks((BYTE *)buff, sector << 9, SD_BLOCK_SIZE, count);
			}
			
			if(status != SD_RESPONSE_NO_ERROR)
				res = RES_ERROR;
				
			// Check if the Transfer is finished 
			while(SD_GetStatus() != SD_CARD_TRANSFER);     
			res = RES_OK;
		}*/
		break;
	}
	return res;
}
#endif /* _READONLY == 0 */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL != 0
DRESULT disk_ioctl (
                    BYTE drv,		/* Physical drive number (0) */
                    BYTE ctrl,		/* Control code */
                    void *buff		/* Buffer to send/receive control data */
                      )
{
	DRESULT res = RES_OK;

	switch(drv)
	{
		case USB:		// USB HOST U��	
		{			
			if (drv) return RES_PARERR;

			res = RES_ERROR;

			if (Stat & STA_NOINIT) return RES_NOTRDY;

			switch (ctrl) 
			{
				case CTRL_SYNC :		/* Make sure that no pending write process */
					res = RES_OK;
					break;

				case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
					*(DWORD*)buff = (DWORD) USBH_MSC_Param.MSCapacity;
					res = RES_OK;
					break;

				case GET_SECTOR_SIZE :	/* Get R/W sector size (WORD) */
					*(WORD*)buff = 512;
					res = RES_OK;
					break;

				case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
					*(DWORD*)buff = 512;
					break;

				default:
					res = RES_PARERR;
					break;
			}
		}
		break;
		
		case SD:		// SD��
		/*{
//			res = FATFSdisk_SD_SDIO_Ioctl(ctrl, buff);	
			if (Stat & STA_NOINIT) return RES_NOTRDY;
			if(SD_Detect() == SD_NOT_PRESENT)
				return RES_NOTRDY;
		}*/
		break;
			
	}
  
  return res;
}
#endif /* _USE_IOCTL != 0 */

/*-----------------------------------------------------------------------*/
/* Get time for fatfs for files                                          */
/*-----------------------------------------------------------------------*/
__weak DWORD get_fattime(void) {
	/* Returns current time packed into a DWORD variable */
	return	  ((DWORD)(2015 - 1980) << 25)	/* Year 2015 */
			| ((DWORD)7 << 21)				/* Month 7 */
			| ((DWORD)3 << 16)				/* Mday 3 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				/* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */
}

