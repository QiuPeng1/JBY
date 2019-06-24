/***************************************************************************


****************************************************************************/

/*包含私有头文件 */
#include "_flash.h"

/*公开的子程序*/
/***************************************************************************
* 函数介绍：
* 输入参数：初始化，更新状态寄存器
* 输出参数：
* 返回值  ：
****************************************************************************/
void eeprom_Init(void)
{
}

/***************************************************************************
* 函数介绍：
* 输入参数：读数据
* 输出参数：
* 返回值  ：
****************************************************************************/
void eeprom_ReadData(void)
{
	u32 address;
	u32 *pd;
	u16 i;

	address = FLASH_START_ADDR;	 
	pd = (u32 *)(&savedPara);
	for(i=0; i<sizeof(savedPara)/4; i++)
	{
		//FLASH_ProgramWord(address, *pd);
		*pd = *((u32 *) address);
		address += 4;
		pd ++;
	}
}

void flash_ReadData(u32 addr,u32 *data,u16 len)
{
	u32 address;
//	u32 *pd;
	u16 i;

	address = addr;	 
//	pd = data;
	for(i=0; i<len/4; i++)
	{
		*data = *((u32 *) address);
		address += 4;
		data ++;
	}
}

//一页按2K写
void flash_WriteData(u32 addr,u32 *data,u16 len)
{
	u16 i;
	u8 writeTimes;
	u32 address;
	u8 isRight;
	u32 * pd;
	
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

	writeTimes = MAX_FLASH_WRITE_TIMES;

	while(writeTimes--)
	{
		FLASH_ErasePage(addr);	//擦掉一个page
		
		pd = data;
		address = addr;
		for(i=0; i<len/4; i++)
		{
			FLASH_ProgramWord(address, *pd);
			address += 4;
			pd ++;
		}

		isRight = 1;
		address = addr;
		pd = data;	
		for(i=0; i<len/4; i++)
		{
			if((*(__IO u32*) address) != *pd)
			{
				isRight = 0;
			}
			address += 4;
			pd ++;
		}
		if (isRight)
		{
			break;
		}
	}
}

/***************************************************************************
* 函数介绍：
* 输入参数：写数据
* 输出参数：
* 返回值  ：
****************************************************************************/
void eeprom_SaveData(void)
{
	u16 i;
	u8 writeTimes;
	u32 address;
	u8 isRight;
	u32 * pd;

#ifndef VC_PLUS_PLUS
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
#endif
	writeTimes = MAX_FLASH_WRITE_TIMES;

	while(writeTimes--)
	{
#ifndef VC_PLUS_PLUS
		FLASH_ErasePage(FLASH_START_ADDR);
#endif
		address = FLASH_START_ADDR;	 
		pd = (u32 *)(&savedPara);
		for(i=0; i<sizeof(savedPara)/4; i++)
		{
#ifndef VC_PLUS_PLUS
			FLASH_ProgramWord(address, *pd);
#endif
			address += 4;
			pd ++;
		}

		isRight = 1;
		address = FLASH_START_ADDR;	 
		pd = (u32 *)(&savedPara);	
		for(i=0; i<sizeof(savedPara)/4; i++)
		{
#ifndef VC_PLUS_PLUS
			if((*(__IO u32*) address) != *pd)
			{
				isRight = 0;
			}
#endif
			address += 4;
			pd ++;
		}
		if (isRight)
		{
			break;
		}
	}
}

/***************************************************************************
* 函数介绍：
* 输入参数：读数据
* 输出参数：
* 返回值  ：
****************************************************************************/
u32 flash_ReadAPPdate(u32 appdateAddr)
{
	u32 address;
	u32 *pd;
	u16 i;
	u32 appdate;

	address = appdateAddr;	 
	pd = (u32 *)(&appdate);
	//FLASH_ProgramWord(address, *pd);
	*pd = *((u32 *) address);
	
	return appdate;
}
/***************************************************************************
* 函数介绍：
* 输入参数：读数据
* 输出参数：
* 返回值  ：
****************************************************************************/
u32 flash_ReadUpdateFlag(void)
{
	u32 address;
	u32 *pd;
//	u16 i;
	u32 updateFlag;

	address = UPDATA_FLAG_ADDR;	 
	pd = (u32 *)(&updateFlag);
	//FLASH_ProgramWord(address, *pd);
	*pd = *((u32 *) address);
	
	return updateFlag;
}

/***************************************************************************
* 函数介绍：
* 输入参数：写数据
* 输出参数：
* 返回值  ：
****************************************************************************/
void flash_SaveUpdateFlag(u32 flag)
{
//	u16 i;
	u8 writeTimes;
	u32 address;
	u8 isRight;
	u32 * pd;

#ifndef VC_PLUS_PLUS
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
#endif
	writeTimes = MAX_FLASH_WRITE_TIMES;

	while(writeTimes--)
	{
#ifndef VC_PLUS_PLUS
		FLASH_ErasePage(UPDATA_FLAG_ADDR);
#endif
		address = UPDATA_FLAG_ADDR;	 
		pd = (u32 *)(&flag);
#ifndef VC_PLUS_PLUS
		FLASH_ProgramWord(address, *pd);
#endif

		isRight = 1;
		address = UPDATA_FLAG_ADDR;	 
		pd = (u32 *)(&flag);	

#ifndef VC_PLUS_PLUS
			if((*(__IO u32*) address) != *pd)
			{
				isRight = 0;
			}
#endif
		if (isRight)
		{
			break;
		}
	}
}
