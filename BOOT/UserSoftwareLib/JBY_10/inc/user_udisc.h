#ifndef __USER_UDISC_H__
#define __USER_UDISC_H__

#include "system.h"
#include "usb_conf.h"
#include "usb_core.h"
#include "usbh_conf.h"
#include "usbh_core.h"
#include "usbh_msc_core.h"
#include "usbh_msc_usr.h"
#include "usb_hcd_int.h"
#include "fatfs_demo.h"
//-----------------------
#include "user_udisc.h" 

extern u8 gb_udsikIsOnLine;
extern u8 gb_udiskPlugIn;
//---------------------------------------
//----------------------------------------------
void USB_Config(void);
void USB_CheckReady(void);
//----------------------------------------------
u8 CreateFileToUdisk(char*);
u8 SaveFileToUdisk(u8*,u16,char*);
//----------------------------------------------
u8 ReadUdiskFileSize(char*,u32*);
//-----------------------------------------------------------------------
u8 ReadUdiskFile(char*,u8*,u32,u32);
//-----------------------------------------------------------------------
#endif


