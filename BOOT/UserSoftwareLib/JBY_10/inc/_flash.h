/***************************************************************************


****************************************************************************/
//防止重复引用
#ifndef _EEPROM_H_
#define _EEPROM_H_

//包含文件
#include "system.h"
#include "eeprom.h"
//#include "thickness.h"

//---------------------------------------------------------------------
//管脚及宏函数定义
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//类型定义
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//常量定义
//---------------------------------------------------------------------
#define FLASH_START_ADDR ((u32)0x0805fe00)//((u32)0x080ffe00)
#define FLASH_PAGE_SIZE  ((u16)0x200)

#define UPDATA_FLAG_ADDR ((u32)0x0800f800)//APP 0x10000


#define MAX_FLASH_WRITE_TIMES 5

//---------------------------------------------------------------------
//引用的全局变量及输入函数
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//文件内部模块私有变量
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//文件内部模块私有函数
//---------------------------------------------------------------------


#endif
