#include "user_udisc.h" 


//---------------------------------------------------------------------
void USB_Config(void)
{
//---------------------------------------------------------	
	RCC_OTGFSCLKConfig(RCC_OTGFSCLKSource_PLLVCO_Div3);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_OTG_FS, ENABLE);
	USBH_Init(&USB_OTG_Core, 
	USB_OTG_FS_CORE_ID,
	&USB_Host,
	&USBH_MSC_cb, 		// 
	&USR_MSC_cb);
//---------------------------------------------------------	
}
void USB_CheckReady(void)
{
	u8 r;
//----------------------------ʵʱ����Ƿ���U�̹��سɹ�--------------------------------------------
	if((USBH_USR_ApplicationState==USH_USR_FS_INIT) || (HCD_IsDeviceConnected(&USB_OTG_Core)==0))//���û����
	{
		//g_SysType.FlagUDiscOnline = 0;//U��δ����
		gb_udsikIsOnLine = 0;
		/* Host Task handler */
		USBH_Process(&USB_OTG_Core , &USB_Host);  //�ͼ��U�̽ӿڵ�״̬������浽CORE �ṹ���С�
	}
	else
	{
		if(USBH_USR_ApplicationState==USH_USR_FS_READY)
		{
			r = SaveFileToUdisk("Test Udisk",10,"JBY.txt");
			if((r == 0)&&(gb_udsikIsOnLine == 0))
			{
				gb_udsikIsOnLine = 1;
				gb_udiskPlugIn = 1;
			}
//			if(g_SysType.FlagUDiscOnline==0)
//			{
//				VoiceSeg(_VOICE_BEEP_);
//				g_SysType.FlagUDiscOnline = 1;//U���Ѳ���
//			}
		}
	}
}
//-------------------------�����ļ�-----------------------------------------------
u8 CreateFileToUdisk(char *fileName) 
{
	u8 result;
	result = f_open(&file, fileName, FA_CREATE_ALWAYS);
	if( result== FR_OK)
	{
		f_close(&file);		
	}
	return result;
}
//--------------------------�����ļ�----------------------------------------------
u8 SaveFileToUdisk(u8 *d,u16 len,char *fileName)
{
	u8 result;
	u32 bw;
	result = f_open(&file, fileName, FA_WRITE | FA_OPEN_ALWAYS);
	if(result == FR_OK)
	{		
		f_lseek(&file,file.fsize);
		f_write(&file,d,len,(u32*)&bw);
		//f_sync(&file);
		f_close(&file);
	}
	return result;  
}
//----------------------------��ȡ�ļ���С-------------------------------------------
u8 ReadUdiskFileSize(char *fileName,u32 * len)
{
	u8 result;
//	u32 bw;
	result = f_open(&file, fileName,  FA_OPEN_ALWAYS);
	if(result == FR_OK)
	{		
		*len = file.fsize;

		f_close(&file);
	}
	return result;
}
//---------------------------��ȡ�ļ�--------------------------------------------
u8 ReadUdiskFile(char *fileName,u8 *data,u32 offset,u32 len)
{
	u8 result;
	u32 bw;
	result = f_open(&file, fileName, FA_READ | FA_OPEN_ALWAYS);
	if(result == FR_OK)
	{		
		f_lseek(&file,offset);
		f_read(&file, data, len, (u32 *)&bw);
		f_close(&file);
	}
	return result;
}
//-----------------------------------------------------------------------
//------------------USB�ж�-----------------
void OTG_FS_IRQHandler(void)
{
	USBH_OTG_ISR_Handler(&USB_OTG_Core);
}

