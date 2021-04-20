/***************************************************************************
 

****************************************************************************/

/*防止重复引用 */
#ifndef EEPROM_H
#define EEPROM_H

#include "system.h"

/*将外部包含和内部包含分开*/
#ifdef _EEPROM_H_
    #define EEPROM_EXT_PARA
	#define EEPROM_EXT_FUNC
#else
	#ifdef __cplusplus
		#define EEPROM_EXT_PARA  EXTERN_C
		#define EEPROM_EXT_FUNC  extern
	#else
		#define EEPROM_EXT_PARA  extern
		#define EEPROM_EXT_FUNC  extern		
	#endif
#endif

#define DATA_FLAG  0x87061469

typedef struct 
{
	u32 csmpNumIn50ms[4]; //传输大电机在50ms内的目标码盘数
	u32 csddjInitVal[4][2];	//传输大电机的频率
	u8 irIdleStandard[(REAL_IR_NUM/4+1)*4];
	u16 irBz40gStandard[(REAL_IR_NUM/2+1)*2];	//薄纸标准值 *100
 	u16 irBz80gStandard[(REAL_IR_NUM/2+1)*2];  //厚纸标准值 *100
	u8 widthAdjust;
	u8 colorAdjust[12];
	u8 adjustReserve[3];
}ADJUST_T;

// MR_EXT_PARA u8 widthThres[4];//widthThres[0] >= 100 > widthThres[1] >= 50、20、10 > widthThres[2] >= 5、1 > widthThres[3]
// MR_EXT_PARA u8 doubleNoteThres;
// MR_EXT_PARA u8 chainNoteThres;
// MR_EXT_PARA u8 aqxCodeNumThres;
// MR_EXT_PARA u8 aqxWaveThres;
// MR_EXT_PARA u8 aqxWaveCombineThres;
// MR_EXT_PARA u8 irHaveNoteThres;

enum
{
	INDEX_OPEN_CURRENCY_SWITCH1,
	INDEX_OPEN_CURRENCY_SWITCH2,
	INDEX_OPEN_CURRENCY_SWITCH3,
	INDEX_OPEN_CURRENCY_SWITCH4,
	INDEX_OPEN_CURRENCY_SWITCH5,
	INDEX_OPEN_CURRENCY_SWITCH6,
	INDEX_OPEN_CURRENCY_SWITCH7,
	INDEX_OPEN_CURRENCY_SWITCH8,
	INDEX_OPEN_CURRENCY_SWITCH9,
	INDEX_OPEN_CURRENCY_SWITCH10,
	DEFAULT_CURRENCY,
};
typedef struct 
{
	u8 d[48];	
}MACHINE_WORK_PARA_T;

enum
{
	INDEX_DOWN_STACKER_CAPACITY = 0,
	INDEX_SPEED,//1
	INDEX_BEEP_ON,//2
	INDEX_BATCH,//3
	INDEX_SELFCHECK,//4
	INDEX_MONEY_TYPE,//5
	INDEX_4thRMB_SUPPORT,//6
	INDEX_YU_ZHI_STOP_CLEAR_RESULT,//7
	INDEX_PRINT_MODE,//8
	INDEX_ADD_IS_ON,//9
	INDEX_MANUAL_IS_ON,//10
	INDEX_RMB_MG_GRADE,//11
	INDEX_RMB_UV_GRADE,//12
	INDEX_RMB_DOUBLE_NOTE_THRES,//13
	INDEX_RMB_CHAIN_NOTE_THRES,//14
	INDEX_WORKMODE,//15
	INDEX_USER_WORK_PARA_MAX,
};

typedef struct 
{
	u8 d[48];	
}USER_WORK_PARA_T;

typedef struct 
{
	u8 d[16];	
}JUDGE_PARA_T;

typedef struct
{
	ADJUST_T adjustPara;
	MACHINE_WORK_PARA_T machineWorkPara;
	USER_WORK_PARA_T userWorkPara;
	JUDGE_PARA_T judgePara;
	u8 beepSwitch;
	u8 noteLeaveRoads;
	u8 identificationWays;
	u8 uvGrade;
	u8 uvWhiteValue;
	u8 reserve[60];
	u32 flag;
}DATANEEDSAVED_T;

EEPROM_EXT_PARA DATANEEDSAVED_T savedPara;
EEPROM_EXT_PARA STATE_T systemState;

/*公开的过程/函数*/

/***************************************************************************
* 函数介绍：
* 输入参数：初始化，更新状态寄存器
* 输出参数：
* 返回值  ：
****************************************************************************/
EEPROM_EXT_FUNC void eeprom_Init(void);

/***************************************************************************
* 函数介绍：
* 输入参数：读数据
* 输出参数：
* 返回值  ：
****************************************************************************/
EEPROM_EXT_FUNC void eeprom_ReadData(void);

/***************************************************************************
* 函数介绍：
* 输入参数：写数据
* 输出参数：
* 返回值  ：
****************************************************************************/
EEPROM_EXT_FUNC void eeprom_SaveData(void);
EEPROM_EXT_FUNC u32 flash_ReadUpdateFlag(void);
EEPROM_EXT_FUNC void flash_SaveUpdateFlag(u32 flag);

#endif
