/*********************************************************************


**********************************************************************/
/*防止重复引用 */
#ifndef _MAIN_H_
#define _MAIN_H_

/*包含文件 */
#include <string.h>
#include "system.h"
#include "delay.h"
#include "fifo.h"
#include "uart.h"
#include "eeprom.h"
//#include "coin.h"
//#include "tm1620.h"
//#define USE_IWDG
#include "motor.h"
#include "mr.h"
#include "bill.h"
#include "disp.h"

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
//----------------------
//#include "batchOperation.h"
//-----------------------------------------------------------------
//类型定义
//-----------------------------------------------------------------
//管脚定义
// #define PA_AD_GPIO_PORT              GPIOA
// #define PA_AD_GPIO_PIN               (GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
// #define PA_AD_GPIO_MODE              GPIO_Mode_AIN

// #define PB_AD_GPIO_PORT              GPIOB
// #define PB_AD_GPIO_PIN               (GPIO_Pin_1|GPIO_Pin_0)
// #define PB_AD_GPIO_MODE              GPIO_Mode_AIN

// #define PC_AD_GPIO_PORT             GPIOC
// #define PC_AD_GPIO_PIN              (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4)
// #define PC_AD_GPIO_MODE             GPIO_Mode_AIN

// u8 gb_hwfsIsOn = 1;

// #define HWFS_GPIO_PORT           GPIOC
// #define HWFS_GPIO_PIN            GPIO_Pin_3
// #define HWFS_GPIO_MODE           GPIO_Mode_Out_PP
// #define HWFS_ON() (GPIO_SetBits(HWFS_GPIO_PORT, HWFS_GPIO_PIN),gb_hwfsIsOn = 1)
// #define HWFS_OFF() (GPIO_ResetBits(HWFS_GPIO_PORT, HWFS_GPIO_PIN),gb_hwfsIsOn = 0)

#define HW_FS_GPIO_PORT              GPIOB
#define HW_FS_GPIO_PIN               GPIO_Pin_9
#define HW_FS_GPIO_MODE              GPIO_Mode_Out_PP
bit gb_hwVccIsOn;
#define hwfs_On() 			GPIO_SetBits(HW_FS_GPIO_PORT, HW_FS_GPIO_PIN);gb_hwVccIsOn=1
#define hwfs_Off() 			GPIO_ResetBits(HW_FS_GPIO_PORT, HW_FS_GPIO_PIN);gb_hwVccIsOn=0

#define UV_FS_GPIO_PORT              GPIOB
#define UV_FS_GPIO_PIN               GPIO_Pin_4
#define UV_FS_GPIO_MODE              GPIO_Mode_Out_PP
bit gb_uvVccIsOn;
#define uvfs_On() 			GPIO_SetBits(UV_FS_GPIO_PORT, UV_FS_GPIO_PIN);gb_uvVccIsOn=1
#define uvfs_Off() 		GPIO_ResetBits(UV_FS_GPIO_PORT, UV_FS_GPIO_PIN);gb_uvVccIsOn=0
// u8 gb_ledIsOn = 0;
// #define LED_GPIO_PORT          GPIOB
// #define LED_GPIO_PIN            GPIO_Pin_14
// #define LED_GPIO_MODE           GPIO_Mode_Out_PP
// #define LED_ON() GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);gb_ledIsOn = 1
// #define LED_OFF() GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);gb_ledIsOn = 0

#define ENTERANCE_FS_GPIO_PORT              GPIOA
#define ENTERANCE_FS_GPIO_PIN               GPIO_Pin_5
#define ENTERANCE_FS_GPIO_MODE              GPIO_Mode_Out_PP
bit gb_jinChaoFaSheIsOn = 0;	
#define jckfs_Off()  GPIO_SetBits(ENTERANCE_FS_GPIO_PORT, ENTERANCE_FS_GPIO_PIN); gb_jinChaoFaSheIsOn = 0
#define jckfs_On()  GPIO_ResetBits(ENTERANCE_FS_GPIO_PORT, ENTERANCE_FS_GPIO_PIN); gb_jinChaoFaSheIsOn = 1


//#define TEST_FS_GPIO_PORT              GPIOC
//#define TEST_FS_GPIO_PIN               GPIO_Pin_5
//#define TEST_FS_GPIO_MODE              GPIO_Mode_Out_PP
//#define test_On()  GPIO_SetBits(TEST_FS_GPIO_PORT, TEST_FS_GPIO_PIN); 
//#define test_Off()  GPIO_ResetBits(TEST_FS_GPIO_PORT, TEST_FS_GPIO_PIN);

//蜂鸣器
#define BEEP_GPIO_PORT              GPIOA
#define BEEP_GPIO_CLK               RCC_APB2Periph_GPIOA
#define BEEP_GPIO_PIN               GPIO_Pin_6
#define BEEP_GPIO_MODE              GPIO_Mode_Out_PP

#define beep_Off() GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN)
#define beep_On() GPIO_SetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN)

#define	KEY0_GPIO_PORT GPIOC
#define	KEY0_GPIO_PIN GPIO_Pin_6
#define	KEY0_GPIO_MODE GPIO_Mode_IPU
#define readkey0()  (GPIO_ReadInputDataBit(KEY0_GPIO_PORT, KEY0_GPIO_PIN))

#define	KEY1_GPIO_PORT GPIOC
#define	KEY1_GPIO_PIN GPIO_Pin_7
#define	KEY1_GPIO_MODE GPIO_Mode_IPU
#define readkey1()  (GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN))

#define	KEY2_GPIO_PORT GPIOC
#define	KEY2_GPIO_PIN GPIO_Pin_8
#define	KEY2_GPIO_MODE GPIO_Mode_IPU
#define readkey2()  (GPIO_ReadInputDataBit(KEY2_GPIO_PORT, KEY2_GPIO_PIN))


#define USB_EN_GPIO_PORT              GPIOC
#define USB_EN_GPIO_PIN               GPIO_Pin_10
#define USB_EN_GPIO_MODE              GPIO_Mode_Out_PP
#define Usben_Off() GPIO_SetBits(USB_EN_GPIO_PORT, USB_EN_GPIO_PIN)
#define Usben_On() GPIO_ResetBits(USB_EN_GPIO_PORT, USB_EN_GPIO_PIN)

#define USB_FAULT_GPIO_PORT              GPIOB
#define USB_FAULT_GPIO_PIN               GPIO_Pin_15
#define USB_FAULT_GPIO_MODE              GPIO_Mode_IN_FLOATING
#define readUsbFault()  (GPIO_ReadInputDataBit(USB_FAULT_GPIO_PORT, USB_FAULT_GPIO_PIN))

u8 gb_usbState;
//#define	TEST_GPIO_PORT GPIOC
//#define	TEST_GPIO_PIN GPIO_Pin_6
//#define	TEST_GPIO_MODE GPIO_Mode_Out_PP
//u8 gb_testGpioC6On = 0;
//#define test_Off()  GPIO_SetBits(TEST_GPIO_PORT, TEST_GPIO_PIN); gb_testGpioC6On = 0
//#define test_On()  GPIO_ResetBits(TEST_GPIO_PORT, TEST_GPIO_PIN); gb_testGpioC6On = 1

enum
{
	FS_RED,
	FS_GREEN,
	FS_BLUE,
	FS_OFF,
};
u8 g_colorFsRGB = FS_OFF;
#define R_FS_GPIO_PORT              GPIOB
#define R_FS_GPIO_PIN               GPIO_Pin_12
#define R_FS_GPIO_MODE              GPIO_Mode_Out_PP
#define redFs_Off() GPIO_ResetBits(R_FS_GPIO_PORT, R_FS_GPIO_PIN)
#define redFs_On() GPIO_SetBits(R_FS_GPIO_PORT, R_FS_GPIO_PIN);g_colorFsRGB = FS_RED

#define G_FS_GPIO_PORT              GPIOB
#define G_FS_GPIO_PIN               GPIO_Pin_13
#define G_FS_GPIO_MODE              GPIO_Mode_Out_PP
#define greenFs_Off() GPIO_ResetBits(G_FS_GPIO_PORT, G_FS_GPIO_PIN)
#define greenFs_On() GPIO_SetBits(G_FS_GPIO_PORT, G_FS_GPIO_PIN);g_colorFsRGB = FS_GREEN

#define B_FS_GPIO_PORT              GPIOB
#define B_FS_GPIO_PIN               GPIO_Pin_14
#define B_FS_GPIO_MODE              GPIO_Mode_Out_PP
#define blueFs_Off() GPIO_ResetBits(B_FS_GPIO_PORT, B_FS_GPIO_PIN)
#define blueFs_On() GPIO_SetBits(B_FS_GPIO_PORT, B_FS_GPIO_PIN);g_colorFsRGB = FS_BLUE

#define A_GPIO_PORT           GPIOB
#define A_GPIO_PIN            GPIO_Pin_3
#define A_GPIO_MODE           GPIO_Mode_Out_PP
#define A_HIGH() GPIO_SetBits(A_GPIO_PORT, A_GPIO_PIN)
#define A_LOW() GPIO_ResetBits(A_GPIO_PORT, A_GPIO_PIN)

#define B_GPIO_PORT           GPIOD
#define B_GPIO_PIN            GPIO_Pin_2
#define B_GPIO_MODE           GPIO_Mode_Out_PP
#define B_HIGH() GPIO_SetBits(B_GPIO_PORT, B_GPIO_PIN)
#define B_LOW() GPIO_ResetBits(B_GPIO_PORT, B_GPIO_PIN)

#define C_GPIO_PORT           GPIOC
#define C_GPIO_PIN            GPIO_Pin_12
#define C_GPIO_MODE           GPIO_Mode_Out_PP
#define C_HIGH() GPIO_SetBits(C_GPIO_PORT, C_GPIO_PIN)
#define C_LOW() GPIO_ResetBits(C_GPIO_PORT, C_GPIO_PIN)

u8 chanelIndexOf4051 = 0;
u8 g_motorRunState = 0;

u8 g_colorFsStopWork = 0;
u8 gb_needStopMotorTimeout = 0;
u8 gb_mpPeriodRecordCnt = 0;
u8 g_needSaveMpPeriodFlag = 0;
u8 gb_mpPeriodRecord[100];
// #define A1_GPIO_PORT           GPIOB
// #define A1_GPIO_PIN            GPIO_Pin_1
// #define A1_GPIO_MODE           GPIO_Mode_Out_PP
// #define A1_HIGH() GPIO_SetBits(A1_GPIO_PORT, A1_GPIO_PIN)
// #define A1_LOW() GPIO_ResetBits(A1_GPIO_PORT, A1_GPIO_PIN)

// #define PC3_GPIO_PORT           GPIOC
// #define PC3_GPIO_PIN            GPIO_Pin_3
// #define PC3_GPIO_MODE           GPIO_Mode_Out_PP
// #define PC3_High() GPIO_SetBits(PC3_GPIO_PORT, PC3_GPIO_PIN)
// #define PC3_Low() GPIO_ResetBits(PC3_GPIO_PORT, PC3_GPIO_PIN)

/*
位置4	PS4	PC9
位置3	PS3	PC10
位置2	PS2	PC11
位置1	PS1	PC12
位置7	PS7	PE10
位置8	PS8	PE11
*/

//#define PS1_GPIO_PORT       GPIOB
//#define PS1_GPIO_PIN        GPIO_Pin_12
//#define PS1_GPIO_MODE       GPIO_Mode_IN_FLOATING
//#define ps1_HaveNote()  (!GPIO_ReadInputDataBit(PS1_GPIO_PORT, PS1_GPIO_PIN))

//#define PS2_GPIO_PORT       GPIOB
//#define PS2_GPIO_PIN        GPIO_Pin_13
//#define PS2_GPIO_MODE       GPIO_Mode_IN_FLOATING
//#define ps2_HaveNote()  (!GPIO_ReadInputDataBit(PS2_GPIO_PORT, PS2_GPIO_PIN))

// #define PS1_GPIO_PORT       GPIOC
// #define PS1_GPIO_PIN        GPIO_Pin_12
// #define PS1_GPIO_MODE       GPIO_Mode_IN_FLOATING
// #define ps1_HaveNote()  (!GPIO_ReadInputDataBit(PS1_GPIO_PORT, PS1_GPIO_PIN))

// #define PS2_GPIO_PORT       GPIOC
// #define PS2_GPIO_PIN        GPIO_Pin_11
// #define PS2_GPIO_MODE       GPIO_Mode_IN_FLOATING
// #define ps2_HaveNote()  (!GPIO_ReadInputDataBit(PS2_GPIO_PORT, PS2_GPIO_PIN))

// #define PS3_GPIO_PORT       GPIOC
// #define PS3_GPIO_PIN        GPIO_Pin_10
// #define PS3_GPIO_MODE       GPIO_Mode_IN_FLOATING
// #define ps3_HaveNote()  (!GPIO_ReadInputDataBit(PS3_GPIO_PORT, PS3_GPIO_PIN))

// #define PS4_GPIO_PORT       GPIOC
// #define PS4_GPIO_PIN        GPIO_Pin_9
// #define PS4_GPIO_MODE       GPIO_Mode_IN_FLOATING
// #define ps4_HaveNote()  (!GPIO_ReadInputDataBit(PS4_GPIO_PORT, PS4_GPIO_PIN))

// #define PS7_GPIO_PORT       GPIOE
// #define PS7_GPIO_PIN        GPIO_Pin_10
// #define PS7_GPIO_MODE       GPIO_Mode_IN_FLOATING
// #define ps7_HaveNote()  (!GPIO_ReadInputDataBit(PS7_GPIO_PORT, PS7_GPIO_PIN))

// #define PS8_GPIO_PORT       GPIOE
// #define PS8_GPIO_PIN        GPIO_Pin_10
// #define PS8_GPIO_MODE       GPIO_Mode_IN_FLOATING
// #define ps8_HaveNote()  (!GPIO_ReadInputDataBit(PS8_GPIO_PORT, PS8_GPIO_PIN))

enum
{
	FB_UP,
	FB_DOWN,
	FB_UNKNOWN
};
u8 fbPosition = FB_UNKNOWN;
u8 fbInUse = 0;
//翻板电磁铁机控制
#define FBDCT_UP_GPIO_PORT              GPIOE
#define FBDCT_UP_GPIO_PIN               GPIO_Pin_8
#define FBDCT_UP_GPIO_MODE              GPIO_Mode_Out_PP

#define FBDCT_DOWN_GPIO_PORT            GPIOE
#define FBDCT_DOWN_GPIO_PIN             GPIO_Pin_7
#define FBDCT_DOWN_GPIO_MODE            GPIO_Mode_Out_PP

//#define fbdct_Run() 	GPIO_SetBits(FBDCT_ENABLE_GPIO_PORT, FBDCT_ENABLE_GPIO_PIN)
#define FBDCT_STOP() 	GPIO_SetBits(FBDCT_UP_GPIO_PORT, FBDCT_UP_GPIO_PIN);GPIO_SetBits(FBDCT_DOWN_GPIO_PORT, FBDCT_DOWN_GPIO_PIN)

// 	#define FBDCT_UP() 		GPIO_SetBits(FBDCT_UP_GPIO_PORT, FBDCT_UP_GPIO_PIN);GPIO_ResetBits(FBDCT_DOWN_GPIO_PORT, FBDCT_DOWN_GPIO_PIN)
// 	#define FBDCT_DOWN() 	GPIO_ResetBits(FBDCT_UP_GPIO_PORT, FBDCT_UP_GPIO_PIN);GPIO_SetBits(FBDCT_DOWN_GPIO_PORT, FBDCT_DOWN_GPIO_PIN)

#define FBDCT_DOWN() 		GPIO_ResetBits(FBDCT_UP_GPIO_PORT, FBDCT_UP_GPIO_PIN);GPIO_SetBits(FBDCT_DOWN_GPIO_PORT, FBDCT_DOWN_GPIO_PIN)
#define FBDCT_UP() 	GPIO_SetBits(FBDCT_UP_GPIO_PORT, FBDCT_UP_GPIO_PIN);GPIO_ResetBits(FBDCT_DOWN_GPIO_PORT, FBDCT_DOWN_GPIO_PIN)



// #define YIYUAN_IR_GPIO_PORT       GPIOC
// #define YIYUAN_IR_GPIO_PIN        GPIO_Pin_1
// #define YIYUAN_IR_GPIO_MODE       GPIO_Mode_IN_FLOATING
// #define yiYuan_HaveCoin()  (!GPIO_ReadInputDataBit(YIYUAN_IR_GPIO_PORT, YIYUAN_IR_GPIO_PIN))

// #define EXIT_IR_GPIO_PORT       GPIOC
// #define EXIT_IR_GPIO_PIN        GPIO_Pin_2
// #define EXIT_IR_GPIO_MODE       GPIO_Mode_IN_FLOATING
// #define exit_HaveCoin()  (!GPIO_ReadInputDataBit(EXIT_IR_GPIO_PORT, EXIT_IR_GPIO_PIN))

// #define	F1_GPIO_PORT       GPIOA
// #define F1_GPIO_PIN        GPIO_Pin_0
// #define F1_GPIO_MODE       GPIO_Mode_IN_FLOATING

// #define	F2_GPIO_PORT       GPIOD
// #define F2_GPIO_PIN        GPIO_Pin_2
// #define F2_GPIO_MODE       GPIO_Mode_IN_FLOATING

// #define RESET_GPIO_PORT           GPIOB
// #define RESET_GPIO_PIN            GPIO_Pin_8
// #define RESET_GPIO_MODE           GPIO_Mode_Out_PP
// #define RESET_High() GPIO_SetBits(RESET_GPIO_PORT, RESET_GPIO_PIN)
// #define RESET_Low() GPIO_ResetBits(RESET_GPIO_PORT, RESET_GPIO_PIN)

#define SPI_SLAVE                    SPI2
#define SPI_SLAVE_CLK                RCC_APB1Periph_SPI2
#define SPI_SLAVE_GPIO               GPIOB
#define SPI_SLAVE_GPIO_CLK           RCC_APB2Periph_GPIOB 
#define SPI_SLAVE_PIN_NSS            GPIO_Pin_12
#define SPI_SLAVE_PIN_SCK            GPIO_Pin_13
#define SPI_SLAVE_PIN_MISO           GPIO_Pin_14
#define SPI_SLAVE_PIN_MOSI           GPIO_Pin_15 
#define SPI_SLAVE_DMA                DMA1
#define SPI_SLAVE_DMA_CLK            RCC_AHBPeriph_DMA1  
#define SPI_SLAVE_Tx_DMA_Channel     DMA1_Channel5
#define SPI_SLAVE_Tx_DMA_FLAG        DMA1_FLAG_TC5
#define SPI_SLAVE_DR_Base            0x4000380C

#define SPI_SLAVE_NSS_GPIO_PORT              GPIOB
#define SPI_SLAVE_NSS_GPIO_PIN               GPIO_Pin_12
#define SPI_SLAVE_NSS_GPIO_MODE              GPIO_Mode_Out_PP//GPIO_Mode_IPU//GPIO_Mode_IPD//GPIO_Mode_IN_FLOATING	
#define Cs_High() GPIO_SetBits(SPI_SLAVE_NSS_GPIO_PORT, SPI_SLAVE_NSS_GPIO_PIN)
#define Cs_Low() GPIO_ResetBits(SPI_SLAVE_NSS_GPIO_PORT, SPI_SLAVE_NSS_GPIO_PIN)

#define SPI_SLAVE_SCK_GPIO_PORT              GPIOB
#define SPI_SLAVE_SCK_GPIO_PIN               GPIO_Pin_13
#define SPI_SLAVE_SCK_GPIO_MODE              GPIO_Mode_Out_PP//GPIO_Mode_IPU//GPIO_Mode_IPD//GPIO_Mode_IN_FLOATING	
#define Clk_High() GPIO_SetBits(SPI_SLAVE_SCK_GPIO_PORT, SPI_SLAVE_SCK_GPIO_PIN)
#define Clk_Low() GPIO_ResetBits(SPI_SLAVE_SCK_GPIO_PORT, SPI_SLAVE_SCK_GPIO_PIN)

#define SPI_SLAVE_MISO_GPIO_PORT              GPIOB
#define SPI_SLAVE_MISO_GPIO_PIN               GPIO_Pin_14
#define SPI_SLAVE_MISO_GPIO_MODE              GPIO_Mode_IPU//GPIO_Mode_IN_FLOATING//GPIO_Mode_IPU//GPIO_Mode_IPD//GPIO_Mode_AF_PP	

#define SPI_SLAVE_MOSI_GPIO_PORT              GPIOB
#define SPI_SLAVE_MOSI_GPIO_PIN               GPIO_Pin_15
#define SPI_SLAVE_MOSI_GPIO_MODE              GPIO_Mode_Out_PP//GPIO_Mode_IPU//GPIO_Mode_IPD//GPIO_Mode_IN_FLOATING
#define Mosi_High() GPIO_SetBits(SPI_SLAVE_MOSI_GPIO_PORT, SPI_SLAVE_MOSI_GPIO_PIN)
#define Mosi_Low() GPIO_ResetBits(SPI_SLAVE_MOSI_GPIO_PORT, SPI_SLAVE_MOSI_GPIO_PIN)

DMA_InitTypeDef DMA_InitStructure;
#define ADC1_DR_ADDRESS    ((uint32_t)0x4001244C)
volatile u32 adcResult[5];
u8 adData[10];
#define CHANNELS_PER_DMA_GROUP 5

u8 gb_udsikIsOnLine = 0;
u8 gb_udiskPlugIn = 0;
u8 gb_udiskStateChanger = 0;
u8 gb_needSetCurrency = 0;
u32 SetCurrencyFileLen;
uint8_t read_txt_file_buff[2048]; 
u8 gb_udiskCurrencyCnt;

char upgradeFileName[15] = "JBY.bin";

char SetCurrencyFileName[15] = "JBYC.txt";

u32 g_timetest[5];
u8 irValue[REAL_IR_NUM];//测长红外灯
u8 mrValue[2];//磁头通道
u8 colorRGB[4][3];//4个颜色通道 RGB值
u8 UvValue;
u8 enteranceSensorVal;
u8 tdjsValue[2];

u8 IRlengthBuffer[8192];
u8 uvCnt;

u8 lengthFlag = 0;
u8 gb_lengthHaveNote = 0;
u8 gb_lengthCovered = 0;

u8 dubiRecoverCnt = 0;

u16 lastFsOffVal = 0xff;
u16 lastFsOnVal = 0xff;
enum
{
//	ENTERANCE_HAVENOTE_THRES = 100,
	SCAN_ENTERGATE_TIME = 8,//10,			//扫描进钞口的时间间隔
	MIN_HAVEMONEY_PULSENUM_COUNT = 20,//30,//进钞口有纸币的最少脉冲数（在扫描间隔期内）
	ENTERANCE_HAVENOTE_THRES = 60,
	ENTERANCE_HAVENOTE_CHAZHI = 20,//50
	TONGDAO_HAVENOTE_THRES = 200,
	SCAN_MOTOR_TIME = 10,
};
u8 entergatePulseNumCounter = 0;			//入钞口的计数器，如果有纸币，就会一直增加
u8 ps1PulseNumCounter = 0;		    	//PS1的计数器，如果有纸币，就会一直增加
u8 ps2PulseNumCounter = 0;		    	//PS2的计数器，如果有纸币，就会一直增加
u8 scanEntergateTimer = 0; 
u8 gb_haveNoteInEntergate = 0;
u32 PS1Flag = 0;
u8 motor1StopRecord = 0;
u8 motor1SataRecord = 0;
u8 motor1SataRecord2 = 0;
u8 PS1ValueRecord[1500];
u8 PS2ValueRecord[1500];
u16 PS1ValueRecordCnt = 0;
u16 PS2ValueRecordCnt = 0;
u8 mpCntRecode[1000];
u8 msCntRecode[1000];
u8 ententernce[500];
u16 ententernceCnt = 0;
u8 gb_motorNeedEndOneNoteCnt = 0;
u8 gb_needScanEteranceSensor = 1;
u8 fiveMsCnt = 0;
u8 PS2Flag = 0;
u8 PS2FlagCnt = 0;
u8 gb_haveNoteInPS1 = 0;

u8 PS3Flag = 0;
u8 PS3FlagCnt = 0;
u8 gb_haveNoteInPS3 = 0;

enum
{
	ERROR_ENIR = 0x01,
	ERROR_PSIR = 0x02,
	ERROR_MP = 0x04,
	ERROR_RGB1 = 0x08,
	ERROR_RGB2 = 0x10,
	ERROR_RGB3 = 0x20,
	ERROR_RGB4 = 0x40,
	ERROR_IR = 0x80,
};
u8 gb_selfcheckErrorState = 0;
u16 gb_selfcheckErrorStateOverTime = 0;
u8 gb_selfcheckErrorStateClearFlag = 0;

u8 scanMotorTimer = 0; 

u8 gb_haveNoteInPS2 = 0;

u8 gb_startRGBSample = 0;
u8 gb_endRGBSample = 0;
u8 gb_colorSampleStart = 0;
u8 gb_colorSampleEnd = 0;
u8 gb_colorSampleEnable = 0;
// u8 noMoneyOnEntergateCounter = 0;
// bit gb_noMoneyOnEntergateForAWhile = 0;
u32 msecCnt = 0;
	
enum
{
	DEBUG_MODE,//调试串口
	DISPLAY_MODE,
};
u8 gb_uartWorkMode = DEBUG_MODE;//DISPLAY_MODE;

//#define IR_HAVENOTE_THRES 150
// #define ir2_HaveNote() (irValue[2] < irHaveNoteThres)//(psValue[0] < irHaveNoteThres)
// #define ir3_HaveNote() (irValue[5] < irHaveNoteThres)//(psValue[1] < irHaveNoteThres)
// #define ir1_HaveNote() (irValue[1] < irHaveNoteThres)
// #define ir4_HaveNote() (irValue[4] < irHaveNoteThres)

// u8 gb_ps2LeftHaveNote,gb_ps2RightHaveNote;

// volatile s8  currentCountNum;
// volatile u8  lowCountNum;
// volatile u16  noteWidth = 0;
// volatile u8  noteWidthGrade;

// volatile u8  ir2IrNum = 0,ir3IrNum = 0;
// u8  ps2LeftIrNum = 0,ps2RightIrNum = 0;
// volatile u16  countIrNum = 0;
// volatile u8  oneCountIrNum = 0;
// u8 irWidth = 0;
// u8 irGap = 0;
// u8 gb_irCovered = 0;
// u8 irWidthSaved = 0;
// u8 irGapSaved = 0;
// u8 minGapWidthProp = 0xff;
// u8 leftIrCovered = 0;
// u8 rightIrCovered = 0;

u16 irHaveNoteContinuslyCnt = 0;

#define MIN_NOTE_NUM 30
#define WIDTH_JZ_BASE 10

bit gb_inHwAdjusting = 0;
bit gb_inKdAdjusting = 0;

u8 gb_oneNotePass = 0;

u8 irNoteNum = 0;
u8 currentSlant = 0;
u8 gb_leftIsFirst = 0;
s16 slant = 0;
s16 slantAvg = 0;
s16 slantSum = 0;
u16 slantNum = 0;

u8 gb_cntMgComputeTime = 0;
u8 mgComputeMpNum = 0;

// typedef struct
// {
// 	u8 max;
// 	u8 min;
// 	u8 avg;
// 	u8 scope;
// 	u16 sum;
// 	u16 num;
// }IR_T;
// IR_T ir2,ir3;
// IR_T ir2Saved,ir3Saved;

enum
{
	WORKMODE_1 = 0,   
	WORKMODE_2,
	WORKMODE_3,
	WORKMODE_4,
	WORKMODE_5,
};
u8 g_workMode = WORKMODE_1;

enum
{
	WORK_ADD,
	WORK_NOADD,
};
u8 g_needAddValue = WORK_NOADD;
//u8 g_beepOn = 0;//1打开0关闭
u8 g_funDispChanger = 0;
	
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
#define HUAEN_BLUE 0x3a55
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


#define KEMI_BLUE 0x5d56 
#define KEMI_GRAY  0xB5B6
#define KEMI_PURPLE 0x4008//0x7AB0

#define TOP_BAR_PEN_COLOR BLACK
#define TOP_BAR_COLOR CYAN
#define MID_BAR_COLOR WHITE
#define BOTTOM_BAR_COLOR CYAN
#define BOTTOM_BAR_PEN_COLOR BLACK
#define BAR_LINE_COLOR KEMI_PURPLE

#define TOP_BAR_ICON_BACK_COLOR CYAN
#define TOP_BAR_ICON_PEN_COLOR BLACK
#define TOP_BAR_ICON_DISABLE_BACK_COLOR GRAY
#define TOP_BAR_ICON_DISABLE_PEN_COLOR KEMI_GRAY

#define MP_GPIO_PORT           GPIOB
#define MP_GPIO_PIN            GPIO_Pin_8
#define MP_GPIO_MODE           GPIO_Mode_IN_FLOATING
#define MP_GPIO_EXTI_PORT_SOURCE 	GPIO_PortSourceGPIOB
#define MP_GPIO_EXTI_PIN_SOURCE	GPIO_PinSource8
#define MP_EXTI_LINE				EXTI_Line8
#define MP_EXTI_TRIGGER			EXTI_Trigger_Falling
#define MP_EXTI_IRQ				EXTI9_5_IRQn

#define ReadMp() (GPIO_ReadInputDataBit(MP_GPIO_PORT, MP_GPIO_PIN))
#define MAX_RGB_VALUE 250
#define MAX_UV_VALUE 200
u16 mpCnt = 0;
u16 lengthMpCnt = 0;
u16 mpStartCnt = 0;
u16 mpEndCnt = 0;

u8 openCurrency[NOTE_NUM];
u8 openCurrencyNum = 0;

u32 time1;
u32 time2;
u32 timeCnt = 0;

u32 sampleStartNum = 0;
u32 dmaEndNum = 0;

u16 needSampleIdleNum = 0;

u8 gb_sampleIdleOver = 0;		

u8 gb_enableSample = 0;
//u8 gb_enableSampleFlag = 0; 

// enum
// {
// 	NOT_AFTER_STOP,
// 	AFTER_STOP,
// 	AFTER_STOP_CROSS_MR,
// };
// u8 gb_afterStop = NOT_AFTER_STOP;


u8 gb_needStopCsddj = 0;

u8 g_yuZhiNum = 0;

// u8 gb_mgIsOn = 1;
// u8 gb_uvIsOn = 1;
// u8 gb_addIsOn = 0;
// u8 gb_autoIsOn = 1;

u8 const BATCH_NUM[] = 
{
	0,
	100,
	50,
	10,
	5,
};
u8 g_btachNumIndex = 0;
u8 gb_batchIsOn = 0;
u8 gb_inDispBatch = 0;

u8 gb_work = 0;

u8 gb_oneSec = 0;
u8 gb_oneSecAutoRefresh = 0;

u8 gb_keyFuWeiDown = 0;
u8 gb_runInManual = 0;

#define HWFS_OFF_DELAY 2000  //10s
u16 g_turnOffHwfsDelayTimer = 0;
u8 gb_needTurnOffLed = 0;

#define HAVE_NOMONEY_TIMEOUT 400
#define HAVE_NO_NOTE_MAX_COUNTER_START 1500
u16 g_haveNoNoteCounter = 0;

u8 gb_inSelfcheck = 0;
u8 selfcheckResult;

enum
{
	LONG_BEEP_LENGTH = 20,//长声，160ms
	SHORT_BEEP_LENGTH = 8,	//短声，40ms
	INTERVAL_BEEP_LENGTH = 12	//间隔，40ms
};

u8  beepTimes;	//蜂鸣器该响的次数
u8  beepType;
u8  timerForBeep;

//#define F1_FREQ_HAVE_COIN_DIFF 30
//u16 f1BaseFreq = 200;
//#define F2_FREQ_HAVE_COIN_DIFF 80
//u16 f2BaseFreq = 100;


// // u8 errorCode = 0;
// u8 gb_needReject = 0;


//u8 curNoteType = 0;

#define CCHWMAXVALUE       120//140薄铜板纸的标准值
#define CCHWMINVALUE       50//50厚铜版纸的标准值 
float kAdjust[REAL_IR_NUM];//40g白纸到80克白纸的之间的曲线
float bAdjust[REAL_IR_NUM];

u8 outputDeatalDataCnt = 0;
u8 gb_autoOutputDetailData = 0;
u8 gb_lengthInOriginData = 0;
u8 gb_colorInOriginData = 0;
//u8 gb_autoOutputDetailData2 = 0;
// u8 testSystick = 0;
// u32 systickTestCnt = 0;
// u8 testTim4 = 0;
// u32 tim4TestCnt = 0;

// u8 gb_needCheckKey = 0;
// #define CHECK_KEY_TIME 15
// u8 checkKeyCnt = CHECK_KEY_TIME;
// u8  currentLcdKey = KEY_noKey;
// u8  lastLcdKey = KEY_noKey;

// u8 lengthData[LENGTH_IR_CHANNEL_NUM][IR_DATA_MAX_LEN]; 
u32 g_lengthSampleIndex;
// u8 gb_needSampleIr = 0;
u16 g_lengthIrMpNum;

u8 gb_debugErrFlag = 0;
u8 gb_FristInPS2 = 0;
u8 gb_FristOutPS2 = 0;
// u8 mgData[2][MG_DATA_MAX_LEN]; 
u8 gb_uvNeedStartSampleflag = 0;
u8 gb_uvNeedStartSampleCnt = 0;
u8 gb_uvNeedEndSampleCnt = 0;
u8 gb_needStopMotorCnt = 0;
u8 gb_needBackMotorCnt = 0;
u8 gb_lengthIrNeedStartSampleflag = 0;
u8 gb_lengthIrNeedStartSampleCnt = 0;
u8 gb_lengthIrNeedEndSampleCnt = 0;
u16 g_uvSampleIndex;
u16 g_mgSampleIndex;
u8 gb_needSampleMr = 0;
u8 gb_needOutPutErrData = 0;

#define LAST_MG_DATA_MAX 50
u8 lastMgData[2][LAST_MG_DATA_MAX];
u8 lastMgDataIndex = 0;

 
#define TEMP_MG_DATA_MAX_LEN 2000 
u8 tempMgData[2][TEMP_MG_DATA_MAX_LEN]; 
u16 tempMgDataLen = 0;

// u8 colorData[12][COLOR_DATA_MAX_LEN]; 
u16 g_colorSampleIndex = 0;
u16 csmpNumInCurrentCycle=0;

u8 csmpNumCnt = 0;
u16 csmpNumRecord[100];
enum
{
	JAM_OK = 0,
	JAM_CSDDJ,
	JAM_PS2_IR,
	JAM_ENTERANCE_TO_LENGTH,
	JAM_LENGTH_TO_ENTERANCE,
};
u8 gb_isJammed = JAM_OK;
u8 gb_dispJamInfo = 0;
#define IR_COVER_JAM_NUM 200
enum
{
	CSDDJ_JAM_CHECK = 0x01,
	IR_COVER_TIME_JAM_CHECK = 0x02,
	IR_ENTER_TO_PS1_CHECK = 0x04
};


#define MAX_JAM_TIME 10
#define JAM_COUNT_VAL 15

u16 csddjJamTimes = 0;

// u8 const CHUANGSHU_MOTOR_PWM_PARA[] = {200,210,220,230};
u8 const CHUANGSHU_MOTOR_PWM_PARA[] = {128,128,128,128};
u8 const CSMP_NUM_IN_50MS[] = {95,115,140,255};

// bit gb_uartOutSpiCmd = 0;
// bit gb_uartOutSpiCmdIn = 0;
// bit gb_uartOutSpiOutData = 0;
// bit gb_uartOutSpiOutDataIn = 0;
u8 const VAL_FEN_GE[] = {0xFF,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xFF,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xFF,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

	
//串口输出的调试指令
enum
{
	CMD_SENSOR_VIEW = 0x30,
	CMD_SLANT_OUTPUT,//31
	CMD_NOTE_GAP_OUTPUT,//32
	CMD_STOP_POSITION_OUTPUT//33
};
enum
{
	TEST_MODE_OFF,
	SLANT_TEST,
	NOTEGAP_TEST,
	MOTOR_STOP_TEST,
	TEST_MODE_MAX,
};
u8 g_machineTestMode = TEST_MODE_OFF;

enum
{
	IR_WAY = 0x01,
	UV_WAY = 0x02,
	MG_WAY = 0x04,
	RGB_WAY = 0x08,
	ALL_WAYS = 0x0F,
	RGB_IR_WAYS = 0x09,
	RGB_IR_UV_WAYS = 0x0B,
	RGB_IR_MG_WAYS = 0x0D,
	
};
//u8 gb_identificationWays = ALL_WAYS;
u8 gb_billValue;
u16 gb_modifiIdentificationWaysDealy = 0;
u8 gb_modifiIdentificationWaysFlag = 0;
#define MAX_SAMPLE_NUM_ONE_MP 20
u8 maxSampleNumOneMp = 0;

u8 selectedItemIndex = 0;
u8 lastSelectedItemIndex = 0;
u8 gb_paraChanged = 0;

u8 gb_motorState1 = 0;
u8 gb_motorState2 = 0;

#define MAX_DISP_STRING_BUF 100
u8 dispStr[MAX_DISP_STRING_BUF];
u8 gb_incalibrationByKey = 0;
u8 gb_irCalibrationDisp = 0;

enum
{
	STATE_FORWARD_COVER_ENTERANCE = 0x01,
	STATE_FORWARD_COVER_PS1 = 0x02,
	STATE_COMPUTE = 0x04,
	STATE_FORWARD_NOTE_LEAVE = 0x08,
	STATE_BACKWARD_COVER_PS1 = 0x10,
	STATE_BACKWARD_COVER_ENTERANCE = 0x20,
	STATE_BACKWARD_NOTE_LEAVE = 0x40,
};
u16 noteState = 0;

#define MP_FROM_PS1_TO_PS2 500//200//150 //55mm 91mp
u16 g_maxMpFromPs1ToPs2 = 0;

#define MP_FROM_ENTERANCE_TO_Ps1 500//200//150 //55mm 91mp
u16 g_maxMpFromEnteranceToPs1 = 0;
#define MP_FROM_PS1_TO_ENTERANCE 5//200//150 //55mm 91mp
u8 g_maxMpFromPs1ToEnterance = 0;

#define MP_FROM_PS2_TO_LEAVE 150//120 //50mm 82MP
u8 g_maxMpFromPs2ToLeave = 0;

#define MP_FROM_COMPUTE_TO_PS1 500 
u16 g_maxMpFromComputeToPS1 = 0;

#define MP_FROM_MG_TO_LENGTH 50 //15mm 91mp

//u8 gb_noteBackLeave = 1;//0向前转1向后转

u8 gb_needStopMotor = 0;

u8 gb_billEnable = 0;
enum
{
	BILL_READY = 0,
	BILL_READ = 1,
	BILL_ESCROW = 2,
	BILL_CREDIT = 3,
	BILL_STACKED = 4,
	BILL_REJECT = 5,
	BILL_FRAUD = 6,
	BILL_JAMMED = 7,
	BILL_BOX_FULL = 8,
	BILL_BOX_REMOVED = 9,
	BILL_BOX_REPLACED = 10,
	BILL_SOFTWARERROR = 11,
};
u8 gb_billState = BILL_READY;
u8 gb_CurrentValue = 0;
u8 gb_CurrentHaveBill = 0;
/**********************************串口***********************************/
/*************************************************************************/
enum
{
	UART_TRANSCTL = 0x10,
	UART_FREAM_START = 0x07,
	UART_FREAM_END = 0x08,
	UART_FREAM_REQUEST = 0x05,
};
enum
{
	CMD_INIT = 0x49,
	CMD_BILL_ENABLE = 0x50,
	CMD_BILL_DISABLE = 0x51,
	CMD_READ_STATUS = 0x53,
	CMD_READ_VERSION = 0x54,
	CMD_CLEAR_TD = 0x55,
	CMD_SAME_ID = 0x15,
	CMD_HANDSHAKE = 0x06,
};

u8 gb_lastCmdId[3];
u8 gb_lastCmd;
u8 gb_RequestContent;

u8 gb_bkPacage[250];
u8 gb_bkPacageLen;


enum
{
	UART_IDEL,
	UART_START,
	UART_PAC_LEN,
	UART_PAC_CMD,
	UART_PAC_DATA,
	UART_PAC_ID,
	UART_PAC_CTRL,
	UART_PAC_END,
	UART_PAC_CRC,
};
u8 gb_uartPacDealStep = UART_IDEL;
#define uartPacDealMaxTime 100
u8 gb_uartPacDealOverTime = 0;

enum
{
	UART_PAC_ERR_OVERTIME = 0x0100,
	UART_PAC_ERR_CTRL1 = 0x0200,
	UART_PAC_ERR_START = 0x0400,
	UART_PAC_ERR_CTRL2 = 0x0800,
	UART_PAC_ERR_END = 0x1000,
	UART_PAC_ERR_CRC = 0x2000,
};

u16 gb_uartPacErrInfo = 0;
u8 gb_nextOutTimeCnt = 0;

u8 gb_status[4];
enum
{
	CMD_EXECUTION_SUCESS = 's',
	CMD_EXECUTION_ERR = 'e',
	CMD_EXECUTION_WARNING = 'w',
};
u8 gb_cmdExecutionResult = CMD_EXECUTION_SUCESS;
u16 gb_cmdExecutionErrCode = 0;
/*************************************************************************/
/*************************************************************************/

//老化 5转5秒 停5秒 一个轮回10秒 1分钟6次 1小时360次
#define LAOHUA_SINGLE_RUN_TIME 3
#define LAOHUA_SINGLE_STOP_TIME 1
u8 laoHuaSingleTime = LAOHUA_SINGLE_RUN_TIME;
#define ONE_MIN_LAOHUA (60/(LAOHUA_SINGLE_RUN_TIME+LAOHUA_SINGLE_STOP_TIME))
#define MAX_LAO_HUA_TIME 300
u16 laoHuaTime = MAX_LAO_HUA_TIME;//分钟形式
u8 gb_inLaoHua = 0;
u8 oneMinLaoHuaTime = ONE_MIN_LAOHUA;

enum
{
	ENTER_LONG_KEY_TIME = 100,
	SHORT_KEY_TIME = 2,
	LONG_KEY_INTERVAL_TIME = 0
};
u8  shortLcdKeyTimer = 0;
u16  enterLongLcdKeyTimer;	//进入长按键定时器
u8  longLcdKeyIntervalTimer;//长按键间隔定时器
u8  shortLcdKey,longLcdKey;
u8 gb_longLcdKey;
u8 const LONG_LCD_KEY_ADDVAL = 0x20;

u8 gb_needCheckKey = 0;
u8 gb_needCheckTpClick = 0;
#define CHECK_KEY_TIME 20
u8 checkKeyCnt = CHECK_KEY_TIME;
u8  currentLcdKey = KEY_noKey;
u8  lastLcdKey = KEY_noKey;
u8 keyFlag = 0;
u16 g_errFlag = 0;
u8 gb_haveErrUdiskInforDisp = 0;
enum
{
	ERR_VALUE = 0x0001,
	ERR_IR = 0x0002,
	ERR_COLOR = 0x0004,
	ERR_MG = 0x0008,
	ERR_ALL= 0x0010,
	ERR_UV = 0x0020,
};
u16 gb_errflagOverTime = 0;
u8 gb_errflagClearDisp = 0;
enum
{
	INDEX_CHINESE,
	INDEX_ENGLISH,
};
enum
{
	NOTE_IDEL,
	NOTE_FORWARD,
	NOTE_BACKWARD,
};
u8 gb_noteState = NOTE_IDEL;
u8 CurrencyStr[4];
u8 * const CURRENCY_INFO_STR[] = 
{
	"RMB",
	"USD",
	"EUR",
	"JPY",
	"GBP",
	"HKD",	//港币
	"AUD",
	"CAD",

	"SGD",	//8新加坡
	"KRW",	//9韩国
	"TWD",	//10台湾
	"RUB",	//11卢布
	"GHC",	//12加纳塞第
	"UAH",	//13乌克兰
	"NGN",	//14尼日利亚
	"ALL",	//15阿尔巴尼亚

	"MKD",	//16马其顿第纳尔
	"MOP",  //17中国澳门
	"CHF",	//18瑞士法郎
	"SEK",	//19瑞典克郎
	"KZT",  //20哈萨克斯坦
	"TRY",  //21土耳其
	"INR",	//22印度
	"VND",	//23越南,

	"MYR",	//24马来西亚
	"BRL",	//25巴西
	"TJS",	//26
	"CNY",	//27
	"BGN",  //28保加利亚
	"MAD",  //29摩洛哥
	"LYD", //30利比亚
	"LAK",	//31
	
	"ZAR",	//32南非
	"KES",	//33
	"ARS",	//34阿根廷
	"THB",	//35泰铢
	"EGP",	//36埃及镑
	"LKR",	//37斯里兰卡
	"IDR",	//38印尼
	"ILS",	//39以色列
	
	"AFN", 	//40阿富汗
	"JOD", 	//41约旦
	"IQD", 	//42伊拉克
	"LBP", 	//43黎巴嫩
	"SAR", 	//43沙特
	"AED", 	//43阿联酋
};
	
#define g_languageIndex INDEX_ENGLISH//savedPara.userWorkPara.d[INDEX_LANGUAGE]
u8 g_currency;//INDEX_RUB; //savedPara.userWorkPara.d[INDEX_MONEY_TYPE]
u16 gb_ChangeCurrencyDelay = 0;
u8 gb_ChangeCurrencyFlag = 0;
u8 gb_testbuf[20];
enum
{
	NORMAL_DIAN_CHAO = 0,
	NORMAL_CHA_KAN_CAN_SHU,
	NORMAL_HOU_DU_XIAO_ZHENG,
	NORMAL_CI_TOU_XIAO_ZHENG,
	NORMAL_XIN_JIU_XUE_XI,
	NORMAL_WIDTH_IR_ADJUST,
	NORMAL_SUB_STATE_NUM
};
u8 g_subStateOfNormal = NORMAL_DIAN_CHAO;

u8 gb_lcdBacklightOn = 1;
#define TURN_OFF_LCD_BACKLIGHT_TIME 60
u16 lcdBackLightOffCnt = TURN_OFF_LCD_BACKLIGHT_TIME;
u8 gb_uvTher[]={20,25,30,35,40,45,50,55,60,65,70};
//u8 gb_notebackInEnteranceFlag = 0;
#ifdef DEBUG_MODE
u8 testflag[40];
u8 testflag2[40];
u8 testflag2Cnt;
#endif
u8 uart3toPCdebug[40];
u16 gb_needOutPutLength;
u32 noteNum = 0;
u32 noteSum = 0;
u16 noteDenoValue = 0;
u16 denoNoteNum[10];
u8 const RMB_NOTE_VALUE[] = {100,50,20,10,5,1,0,0,0};
u8 const USD_NOTE_VALUE[] = {100,50,20,10,5,2,1,0,0,0};
u16 const EUR_NOTE_VALUE[] = {500,200,100,50,20,10,5,0,0,0};
u16 const RUB_NOTE_VALUE[] = {5000,2000,1000,500,200,100,50,10,0,0};
u16 const TRY_NOTE_VALUE[] = {200,100,50,20,10,5,0,0,0,0};
u16 const IQD_NOTE_VALUE[] = {50000,25000,10000,5000,1000,250,50,0,0,0};
u16 const SAR_NOTE_VALUE[] = {500,100,50,20,10,5,1,0,0,0};
u16 const AED_NOTE_VALUE[] = {1000,500,200,100,50,20,10,5,0,0};
u16 const GBP_NOTE_VALUE[] = {50,20,10,5,0,0,0,0,0};
u16 const ARS_NOTE_VALUE[] = {1000,500,200,100,50,20,10,5,2,0};
u16 const THB_NOTE_VALUE[] = {1000,500,100,50,20,0,0,0,0,0};
u16 const TWD_NOTE_VALUE[] = {2000,1000,500,200,100,0,0,0,0,0};
u16 const CNY_NOTE_VALUE[] = {100,50,20,10,5,1,0,0,0,0};
u32 JbmpAddress[]={BMP_AJ0,BMP_AJ1,BMP_AJ2,BMP_AJ3,BMP_AJ4,BMP_AJ5,BMP_AJ6,BMP_AJ7,BMP_AJ8,BMP_AJ9,BMP_AJB};
u32 YbmpAddress[]={BMP_AY0,BMP_AY1,BMP_AY2,BMP_AY3,BMP_AY4,BMP_AY5,BMP_AY6,BMP_AY7,BMP_AY8,BMP_AY9,BMP_AYB};
u32 SbmpAddress[]={BMP_AS0,BMP_AS1,BMP_AS2,BMP_AS3,BMP_AS4,BMP_AS5,BMP_AS6,BMP_AS7,BMP_AS8,BMP_AS9,BMP_ASB};
u16 SBmpDispXY[]={	
					BMP_S1C_X,BMP_S1C_Y,
					BMP_S2C_X,BMP_S2C_Y,
					BMP_S3C_X,BMP_S3C_Y,
					BMP_S4C_X,BMP_S4C_Y,
					BMP_S5C_X,BMP_S5C_Y,
					BMP_S6C_X,BMP_S6C_Y,
					BMP_S7C_X,BMP_S7C_Y,
					BMP_S8C_X,BMP_S8C_Y,
					BMP_S9C_X,BMP_S9C_Y,
					BMP_S10C_X,BMP_S10C_Y,
					
					
					};
void InitGpioInMain(void);
void MainInit(void);
void OutputCurrentCoinData(void);

//-----------------------------------------------------------------------
//中断相关
//-----------------------------------------------------------------------
//变量
u16 TimingDelay = 0;

//函数申明
void SetSampleRatio(void);
void InitParaData(void);
void set4051Chanel(u8 index);
void RunProgramme(unsigned int Address);
void SelfCheck(void);
void SPI_init(void);
void adc_init(void);
void tim_init(void);
void InitDMA(void);
void DealEddyDataCollect(void);
void ADOneTime2(void);
void ADOneTime(void);
void ScanKeyDown(void);
void SetSystemState(u8 d);
void ToggleJinChaoFaShe(void);
void DealScanEnteracneSensor(void);
void DispAutoRefreshMenu(void);
void DispSensorViewMenu(void);
void DealKeyDownOnSensorView(u8 key);
void DispMainMenu(void);
void SampleOneRow(void);
void DealNotePass(void);
void InitNoteNum(void);
void DispNoteNumValSum(void);
void DealKeyDownOnBatchStop(u8 key);
void LongBeep(u8 times);
void InitMotorSpeedData(void);
void InitMotorMuBiaoSpeed(void);
void InitAllPara(void);
void InitAdjustPara(void);
void InitMachineWorkPara(void);
void InitUserWorkPara(void);
void adjustMotorSpeed(void);
void SystemSelfcheck(void);
u16 Sqrt(u8 x);
u16 ComputeWidth(u16 m, u8 s);
void BatchMotorStop(void);
void JudgeMotorStop(void);
void DealPS1INT(void);
void DealPS2INT(void);
void DealPS3INT(void);


void SetSmpleRatioTimer(u8 spd);
void OutputMgColorDetailData(void);
void OutputLengthDetailData(void);
void OutputALLDetailData(void);
void OutputALLDetailData2(void);
void DispJudgeGradeMenu(void);
void DealKeyDownOnJudgeGradeMenu(u8 key);
void DispUserParaMenu(void);
void DealKeyDownOnUserParaMenu(u8 key);
void DispNotepassInfoMenu(void);
void DealKeyDownOnNotepassInfoMenu(u8 key);
void DispVersionMenu(void);
void DealKeyDownOnVersionMenu(u8 key);
void DispMotorMenu(void);
void DispMotorParaMenu(void);
void MotorParaInc(void);
void MotorParaDec(void);
void DealKeyDownOnMotorMenu(u8 key);
void DispTestMenu(void);
void DealKeyDownOnTestMenu(u8 key);
void DispParaViewMenu(void);
void DealKeyDownOnParaViewMenu(u8 key);
void DispLaoHuaMenu(void);
void DealKeyDownOnLaoHuaMenu(u8 key);
void DealKeyDown(void);
void DealKeyDownOnNormal(u8 key);
void DealKeyDownOnJudgeStop(u8 key);
void DealKeyDownOnDubiStop(u8 key);
void DealKeyDownOnMenu11(u8 key);

void DispIRCalibration(void);
void DispUVCalibration(void);
void DispColorCalibration(void);
			
void OutputSensorView(void);
void OutputNoteSlant(void);
void OutputNoteGap(void);
void OutputMotorStopInfo(void);
void OutputIrDetailData(void);

void ClearNoteNum(void);
void IncNoteNum(void);

void UpdateDataFromSavedData(void);
void U8ToStrNoSpace(u8 d, u8 * str);
void U16ToTimeStr(u16 d, u8 * str, u8 len);
void U32ToStr(u32 d, u8 * str, u8 len);
void U16ToStr(u16 d, u8 * str, u8 len);
void U8ToStr(u8 d, u8 * str);

void ParaInc(void);
void ParaDec(void);
void DispParaMenu(void);
void DispLaoHuaTime(void);
void InitCountIr(void);
void dispSelfcheckError(u8 code);
void DealPackageFromUart3(void);
void DispString(u8 *str,u8 enter);
void DealInMp(void);
void U16ToStr04(u16 d1, u8 *pStr);
void U16ToTimeStr(u16 d, u8 * str, u8 len);
void U8ToHexstr(u8 d, u8 * str);

void DealLengthIrINT(void);
void DealMgSampleINT(void);
void DealColorSampleINT(void);
void DealUVSampleINT(void);

u8 isLengthIrHaveNote(void);

void computeAdjustData(void);
u8 GetAdjustedData(u8 vaule,u8 index);

void DispCurrency(void);
u8 GetCertainStrFromLongStr(u8 *pStr,u8 index,u8 *pCertainStr);
void DealKeyDownOnNormal(u8 key);

void DispNoteNum(void);//显示张数
void DispNoteSum(void);//显示金额
void DispNoteDenoValue(void);//显示币值
void DispDetailNoteNum(void);//显示明细
void DispJamInfo(void);
void DispFunInfo(void);
void SettingParaInc(void);
void DispMenu1(void);
void DispSetting(void);
void DispSettingSelected(void);
void DealKeyDownOnMenu1(u8 key);
void DealKeyDownOnCalibration(u8 key);
void DispUdiskInfo(void);

void ClearAllNoteNum(void);
void ClearPSIrFlag(void);
void ClearJamFlag(void);
void initEteranceSensor(void);
void modifiIdentificationWays(void);
void DispIdentificationWays(void);
void updataCurrencySwitch(void);
void GetOpenCurrency(void);
void ChangeCurrency(void);
void DispCurrency(void);
void DispEngMode(void);
void DealKeyDownOnEngMode(u8 key);
void DispEngModeSettingSelected(void);
void DispEngModeSetting(void);
void DispEngModeValue(void);
void EngModeParaInc(void);

unsigned int crcVal(unsigned char *pcMess,unsigned int wLen);
void UserCopyPac(UART_CMD UserPac);
void DealBKPackage(void);
void sendInfoToHost(u8 cmd);
void DispTransef(void);
// void InitIrData(void);
// void DealIr2Data(u8 d);
// void DealIr3Data(u8 d);

//#include "menu.c"
#include "uartOutput.c"

#endif
