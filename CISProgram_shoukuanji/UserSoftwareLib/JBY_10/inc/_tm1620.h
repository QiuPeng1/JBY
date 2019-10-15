/***************************************************************************

****************************************************************************/
/*防止重复引用 */
#ifndef _TM1620_H_
#define _TM1620_H_

/*包含文件 */
#include "system.h"
#include "tm1620.h"
//#include "fifo.h"

//-----------------------------------------------------------------
//管脚及宏函数定义
//-----------------------------------------------------------------
// #define STB_GPIO_PORT        GPIOD
// #define STB_GPIO_PIN         GPIO_Pin_7
// #define STB_GPIO_MODE        GPIO_Mode_Out_PP
// #define STB_GPIO_PORT_CLK 	 RCC_APB2Periph_GPIOD

// #define CLK_GPIO_PORT        GPIOD
// #define CLK_GPIO_PIN         GPIO_Pin_5
// #define CLK_GPIO_MODE        GPIO_Mode_Out_PP
// #define CLK_GPIO_PORT_CLK 	 RCC_APB2Periph_GPIOD

// #define DIO_GPIO_PORT        GPIOD
// #define DIO_GPIO_PIN         GPIO_Pin_8
// #define DIO_GPIO_MODE        GPIO_Mode_Out_PP
// #define DIO_GPIO_PORT_CLK 	 RCC_APB2Periph_GPIOD
// #define readDio()  GPIO_ReadInputDataBit(DIO_GPIO_PORT, DIO_GPIO_PIN)

#define STB_GPIO_PORT        GPIOC
#define STB_GPIO_PIN         GPIO_Pin_12
#define STB_GPIO_MODE        GPIO_Mode_Out_PP
#define STB_GPIO_PORT_CLK 	 RCC_APB2Periph_GPIOC

#define CLK_GPIO_PORT        GPIOC
#define CLK_GPIO_PIN         GPIO_Pin_10
#define CLK_GPIO_MODE        GPIO_Mode_Out_PP
#define CLK_GPIO_PORT_CLK 	 RCC_APB2Periph_GPIOC

#define DIO_GPIO_PORT        GPIOC
#define DIO_GPIO_PIN         GPIO_Pin_11
#define DIO_GPIO_MODE        GPIO_Mode_Out_PP
#define DIO_GPIO_PORT_CLK 	 RCC_APB2Periph_GPIOC
#define readDio()  GPIO_ReadInputDataBit(DIO_GPIO_PORT, DIO_GPIO_PIN)
//---------------------------------------------------------------------
//类型定义
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//常量定义
//---------------------------------------------------------------------
u8 keyData[5];
//---------------------------------------------------------------------
//文件内部模块私有函数
//---------------------------------------------------------------------
void write_up_disp(unsigned char wr_data);
void disp_led(u8 add,u8 data);
void dio_output(void);
void dio_input(void);
u8 read_Data(void);
void read_key(void);
u8 GetLedCode(u8 d);
#endif
