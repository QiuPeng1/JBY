/***************************************************************************


****************************************************************************/

/*����˽��ͷ�ļ� */
#include "_flash.h"

/*�������ӳ���*/
/***************************************************************************
* �������ܣ�
* �����������ʼ��������״̬�Ĵ���
* ���������
* ����ֵ  ��
****************************************************************************/
void eeprom_Init(void)
{
}

/***************************************************************************
* �������ܣ�
* ���������������
* ���������
* ����ֵ  ��
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

/***************************************************************************
* �������ܣ�
* ���������д����
* ���������
* ����ֵ  ��
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
* �������ܣ�
* ���������������
* ���������
* ����ֵ  ��
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
* �������ܣ�
* ���������д����
* ���������
* ����ֵ  ��
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
