#include "_tm1620.h"
//#include "system.h"


// u8 js_ge;	
// u8 js_shi;		
// u8 js_bai;		
// u8 js_qian;		
// u8 yz_ge;	
// u8 yz_shi;	
// u8 yz_bai;			
// u8 yz_qian;	
// u8 yz_wan;		
// u8 kong;	

void Delay(void)
{
  u16  i;

  for(i = 0; i <10;  i++);
}

u8	JS_TABLE_LED[] = 
{
	0X3F,0x06,0x5B,0x4f,0x66,0x6d,0x7d,0x07,0x7F,0x6f
};
		
u8 TABLE_LED_CODE[] = 
{
	0x77,/*A*/
	0x7c,/*b*/
	0x39,/*C*/
	0x5e,/*d*/
	0x79,/*E*/
	0x71,/*F*/
	0x3d,/*G*/
	0x76,/*H*/
	0x10,/*i*/
	0x0e,/*J*/
	0x7a,/*K*/
	0x38,/*L*/
	0x55,/*M*/
	0x54,/*n*/
	0x5c,/*o*/
	0x73,/*P*/
	0x67,/*q*/
	0x50,/*r*/
	0x64,/*s*/
	0x78,/*t*/
	0x3e,/*U*/
	0x62,/*V*/
	0x6a,/*w*/
	0x36,/*x*/
	0x6e,/*y*/
	0x49,/*z*/
};

u8 SPACE_LED_CODE = 0;
u8 SIGN_LED_CODE = 0x40;
u8 UNKNOWN_LED_CODE = 0x2D;

u8 GetLedCode(u8 d)
{
	if(d >= '0'&&d <= '9')
	{
		return(JS_TABLE_LED[d-'0']);
	}
	else if(d >= 'a'&&d <= 'z')
	{
		return(TABLE_LED_CODE[d-'a']);
	}
	else if(d >= 'A'&&d <= 'Z')
	{
		return(TABLE_LED_CODE[d-'A']);
	}
	else if(d == ' ')
	{
		return(SPACE_LED_CODE);
	}
	else if(d == '-')
	{
		return(SIGN_LED_CODE);
	}
	return(UNKNOWN_LED_CODE);//未找到码
}
// unsigned char TABLE_LED_CODE[] = 
// {
// 	0x77,/*A*/
// 	0x7c,/*b*/
// 	0x39,/*C*/
// 	0x5e,/*d*/
// 	0x79,/*E*/
// 	0x7b,/*e*/
// 	0x71,/*F*/
// 	0x3d,/*G*/
// 	0x76,/*H*/
// 	0x74,/*h*/
// 	0x10,/*i*/
// 	0x0e,/*J*/
// 	0x7a,/*K*/
// 	0x38,/*L*/
// 	0x55,/*M*/
// 	0x54,/*n*/
// 	0x5c,/*o*/
// 	0x73,/*P*/
// 	0x67,/*q*/
// 	0x50,/*r*/
// 	0x64,/*s*/
// 	0x78,/*t*/
// 	0x3e,/*U*/
// 	0x62,/*V*/
// 	0x6a,/*w*/
// 	0x36,/*x*/
// 	0x6e,/*y*/
// 	0x49,/*z*/
// 	0	,	 /*消隐*/ /*10*/
// 	0x40,/*-*/	  /*18*/
// };
//*******************************************************
//内显示——写子程序
//*******************************************************
//BRR拉低
//BSRR拉高
	//	GPIOx->BRR = GPIO_Pin;拉低
//		GPIOx->BSRRL//拉高
void write_up_disp(u8 wr_data)
{
	u8 i;
	u8 CY;

	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();
	
	for(i=0;i<8;i++)				//开始传送8位数据，每循环一次传送一位数据
	{
		GPIO_ResetBits(CLK_GPIO_PORT,CLK_GPIO_PIN);
		Delay();
		CY = wr_data & 0x01;   
		wr_data >>= 1;			//移位数据，低位在前!
		if( CY == 0X01)
		{
			//GPIOD->ODR |= 0X0020;//dio
			GPIO_SetBits(DIO_GPIO_PORT,DIO_GPIO_PIN);
		}
		else
		{
			//GPIOD->ODR &= 0XFFDF;
			GPIO_ResetBits(DIO_GPIO_PORT,DIO_GPIO_PIN);
		}
		Delay();
		GPIO_SetBits(CLK_GPIO_PORT,CLK_GPIO_PIN);
		Delay();
	}
}

u8 read_Data(void)
{
	u8 i;
	u8 tm1668_date;

	tm1668_date=0;

	dio_input();//数据线为输入口

	GPIO_ResetBits(CLK_GPIO_PORT,CLK_GPIO_PIN);

	for(i=0;i<8;i++)
	{
		GPIO_SetBits(CLK_GPIO_PORT,CLK_GPIO_PIN);

		tm1668_date = tm1668_date>>1;	//先读出的是低位

		if(readDio())
		{
			tm1668_date = tm1668_date|0x80;
		}
		else
		{
			tm1668_date = tm1668_date&0x7f; 
		}
		GPIO_ResetBits(CLK_GPIO_PORT,CLK_GPIO_PIN);
	}

	dio_output();

	return(tm1668_date);
}

//读按键函数

void read_key(void)
{
	//GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	memset(keyData,0,sizeof(keyData));
	write_up_disp(0x42); //读按键命令
	Delay();
	
	keyData[0] = read_Data();
	keyData[1] = read_Data();
	keyData[2] = read_Data();
	keyData[3] = read_Data();
	keyData[4] = read_Data();
		
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}

u8 tm16xx_readKey(void)
{
	u8 i;
	
	read_key();
	
	if(keyData[0] == 1)
	{
		return KEY_A;
	}
	if(keyData[0] == 8)
	{
		return KEY_E;
	}
	if(keyData[1] == 8)
	{
		return KEY_C;
	}
	if(keyData[1] == 1)
	{
		return KEY_D;
	}
	if(keyData[2] == 1)
	{
		return KEY_B;
	}
	if(keyData[2] == 8)
	{
		return KEY_F;
	}
	return(0xff);
}
/******************************************************************
TM1668显示寄存器地址
				SEG1-SEG8		| SEG9 SEG10 XXX SEG12 SEG13 SEG14 XXX XXX
GRID1		0xC0				| 0xC1 			
GRID2		0xC2				| 0xC3
GRID3		0xC4				| 0xC5
GRID4		0xC6				| 0xC7
GRID5		0xC8				| 0xC9
GRID6		0xCA				| 0xCB
GRID7		0xCC				| 0xCD

******************************************************************/

enum
{
	LED1_GRID1 = 0xc2,//JS_BAI 	GR3
	LED1_GRID2 = 0xc4,//JS_SHI 	GR2
	LED1_GRID3 = 0xc0,//JS_GE 	GR1
	LED2_GRID1 = 0xc6,//JE_QIAN	GR4
	LED2_GRID2 = 0xc8,//JE_BAI	GR5
	LED2_GRID3 = 0xca,//JE_SHI	GR6
	LED2_GRID4 = 0xcc,//JE_GE		GR7
// 	D1_GRID = 0xc7,//JE_QIAN  	GR4
// 	D2_GRID = 0xc9,//JE_BAI			GR5
// 	D3_GRID = 0xcb,//JE_SHI			GR6
// 	D4_GRID = 0xcd,//JE_GE			GR7
};

#define ORDER1 0
#define ORDER2 1
#define LED_ORDER ORDER2
#if(LED_ORDER == ORDER1)
enum
{
	LED1 = 0xc0,
	LED2 = 0xc1,
	LED3 = 0xc2,
	LED4 = 0xc3,
	LED5 = 0xc4,
	LED6 = 0xc5,
	LED7 = 0xc6,
	LED8 = 0xc7,
	LED9 = 0xc8,
	LED10 = 0xc9,
};
#else
/*********************************
调整led顺的方法 设置#define LED_ORDER ORDER1 调用函数LED_DISPDATA(9876,54321,0);
显示内容为
	8 6 4 2
9 7 6 3 1
则对应的led为
	 c1 c3 c5 c7
c0 c2 c4 c6 c8
写入ORDER2的枚举中
#define LED_ORDER ORDER1
**********************************/
enum
{
	LED1 = 0xc1,
	LED2 = 0xc3,
	LED3 = 0xc5,
	LED4 = 0xc7,
	LED5 = 0xc0,
	LED6 = 0xc2,
	LED7 = 0xc4,
	LED8 = 0xc6,
	LED9 = 0xc8,
	LED10 = 0xc9,
};
#endif

u8 LED_VAL[] =
{
	LED1,	
	LED2, 
	LED3,
	LED4,
	LED5,
	LED6,
	LED7,
	LED8,
	LED9,
	LED10,
};

void disp_led(u8 add,u8 data)
{
	Delay();
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(add);		//寄存器地址
	write_up_disp(data);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}
/*
void display_led(unsigned char x)
{
	write_up_disp(0x44);	   //固定地址模式
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	
	Delay();
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[0]);		//寄存器地址
	write_up_disp(js_qian);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	
	Delay();
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[1]);	 //寄存器地址
	write_up_disp(js_bai);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();

	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[2]);	  //寄存器地址
	write_up_disp(js_shi);
//	write_up_disp(0xff);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();

	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[3]);	//寄存器地址
	write_up_disp(js_ge);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();

	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[4]);	//寄存器地址
	write_up_disp(yz_wan);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();

	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[5]);	//寄存器地址
	write_up_disp(yz_qian);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();

	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[6]);	//寄存器地址
	write_up_disp(yz_bai);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();

	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[7]);   //寄存器地址
	write_up_disp(yz_shi);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();

	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[8]);   //寄存器地址
	write_up_disp(yz_ge);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();
 	
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED_VAL[9]);  //寄存器地址
	write_up_disp(x);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	Delay();

	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(0x8f);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}
*/

//3位数码管
void tm16xx_Led1Disp(u16 num)
{
	u16 temp;
	u8 temp1;
	u8 bai,shi,ge;
	
	if(gb_led1FlashOn == 1)
	{
		return;
	}
   	//大数码管
	temp = num/100;
	temp1 = (u8)temp;
	bai =JS_TABLE_LED[temp1];
	
	temp = (num%100)/10;
	temp1 = (u8)temp;
	shi =JS_TABLE_LED[temp1];
	
	temp = num%10;
	temp1 = (u8)temp;
	ge =JS_TABLE_LED[temp1];
	
	led1CurDispStr[0] = bai;
	led1CurDispStr[1] = shi;
	led1CurDispStr[2] = ge;
	
	if(num<100) 
	{
		bai = 0;
		if(num<10)
		{
			shi = 0;
		}
	}
	
	write_up_disp(0x44);	   //固定地址模式
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	
	disp_led(LED1_GRID1,bai);
	disp_led(LED1_GRID2,shi);
	disp_led(LED1_GRID3,ge);
	
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED1_LIGHT);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}

void tm16xx_Led1Flash(u8 on)
{
	u8 i;
	u8 ledCode[3];
	if(gb_led1FlashOn == 1)
	{
		if(on == 1)
		{
			for(i = 0;i < 3;i++)
			{
				ledCode[i] = GetLedCode(led1FlashStr[i]);
			}
		}
		else
		{
			memset(ledCode,SPACE_LED_CODE,3);
		}
		write_up_disp(0x44);	   //固定地址模式
		GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
		
		disp_led(LED1_GRID1,ledCode[0]);
		disp_led(LED1_GRID2,ledCode[1]);
		disp_led(LED1_GRID3,ledCode[2]);
		
		GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
		write_up_disp(LED1_LIGHT);
		GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	}
}

void tm16xx_Led2Flash(u8 on)
{
	u8 i;
	u8 ledCode[4];
	if(gb_led2FlashOn == 1)
	{
		if(on == 1)
		{
			for(i = 0;i < 4;i++)
			{
				ledCode[i] = GetLedCode(led2FlashStr[i]);
			}
		}
		else
		{
			memset(ledCode,SPACE_LED_CODE,4);
		}
		
		if(instructLed1 > 0)
		{
			ledCode[0] |= 0x80;
		}
		if(instructLed2 > 0)
		{
			ledCode[1] |= 0x80;
		}
		if(instructLed3 > 0)
		{
			ledCode[2] |= 0x80;
		}
		if(instructLed4 > 0)
		{
			ledCode[3] |= 0x80;
		}	
		
		write_up_disp(0x44);	   //固定地址模式
		GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
		
		disp_led(LED2_GRID1,ledCode[0]);
		disp_led(LED2_GRID2,ledCode[1]);
		disp_led(LED2_GRID3,ledCode[2]);
		disp_led(LED2_GRID4,ledCode[3]);
		
		GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
		write_up_disp(LED2_LIGHT);
		GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
		
	}
}

void tm16xx_Led1DispStr(u8 *str)
{
	u8 i;
	u8 ledCode[3];
	
	if(gb_led1FlashOn == 1)
	{
		return;
	}
	
	for(i = 0;i < 3;i++)
	{
		ledCode[i] = GetLedCode(str[i]);
	}
	memcpy(led1CurDispStr,ledCode,3);
	
	write_up_disp(0x44);	   //固定地址模式
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	
	disp_led(LED1_GRID1,ledCode[0]);
	disp_led(LED1_GRID2,ledCode[1]);
	disp_led(LED1_GRID3,ledCode[2]);
	
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED1_LIGHT);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}

void tm16xx_Led2DispStr(u8 *str)
{
	u8 i;
	u8 ledCode[4];
	
	if(gb_led2FlashOn == 1)
	{
		return;
	}
	
	for(i = 0;i < 4;i++)
	{
		ledCode[i] = GetLedCode(str[i]);
	}
	memcpy(led2CurDispStr,ledCode,4);
	
	if(instructLed1 > 0)
	{
		ledCode[0] |= 0x80;
	}
	if(instructLed2 > 0)
	{
		ledCode[1] |= 0x80;
	}
	if(instructLed3 > 0)
	{
		ledCode[2] |= 0x80;
	}
	if(instructLed4 > 0)
	{
		ledCode[3] |= 0x80;
	}	
	
	write_up_disp(0x44);	   //固定地址模式
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	
	disp_led(LED2_GRID1,ledCode[0]);
	disp_led(LED2_GRID2,ledCode[1]);
	disp_led(LED2_GRID3,ledCode[2]);
	disp_led(LED2_GRID4,ledCode[3]);
	
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED2_LIGHT);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}

void tm16xx_Led1DispLastStr(void)
{
	write_up_disp(0x44);	   //固定地址模式
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	
	disp_led(LED1_GRID1,led1CurDispStr[0]);
	disp_led(LED1_GRID2,led1CurDispStr[1]);
	disp_led(LED1_GRID3,led1CurDispStr[2]);
	
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED1_LIGHT);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}
void tm16xx_Led2DispLastStr(void)
{
		u8 i;
	u8 ledCode[4];
	
	if(gb_led2FlashOn == 1)
	{
		return;
	}
	
	memcpy(ledCode,led2CurDispStr,4);
	
	if(instructLed1 > 0)
	{
		ledCode[0] |= 0x80;
	}
	if(instructLed2 > 0)
	{
		ledCode[1] |= 0x80;
	}
	if(instructLed3 > 0)
	{
		ledCode[2] |= 0x80;
	}
	if(instructLed4 > 0)
	{
		ledCode[3] |= 0x80;
	}	
	
	write_up_disp(0x44);	   //固定地址模式
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	
	disp_led(LED2_GRID1,ledCode[0]);
	disp_led(LED2_GRID2,ledCode[1]);
	disp_led(LED2_GRID3,ledCode[2]);
	disp_led(LED2_GRID4,ledCode[3]);
	
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED2_LIGHT);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}

void tm16xx_SetInsturctLed(u8 d1,u8 d2,u8 d3,u8 d4)
{
	instructLed1 = d1;
	instructLed2 = d2;
	instructLed3 = d3;
	instructLed4 = d4;
}

//4位数码管
void tm16xx_Led2Disp(u16 num)
{
	u16 temp;
	u8 temp1;
	u8 qian,bai,shi,ge;
	
	if(gb_led2FlashOn == 1)
	{
		return;
	}

	temp = num/1000;
	temp1 = (unsigned char)temp;
	qian =JS_TABLE_LED[temp1];
	
	temp = (num%1000)/100;
	temp1 = (unsigned char)temp;
	bai =JS_TABLE_LED[temp1];
	
	temp = (num%100)/10;
	temp1 = (unsigned char)temp;
	shi =JS_TABLE_LED[temp1];
	
	temp = num%10;
	temp1 = (unsigned char)temp;
	ge =JS_TABLE_LED[temp1];
	
	if(num<1000)
	{
		qian = 0;
		if(num<100) 
		{
			bai = 0;
			if(num<10)
			{
				shi = 0;
			}
		}
	}
	
	led2CurDispStr[0] = qian;
	led2CurDispStr[1] = bai;
	led2CurDispStr[2] = shi;
	led2CurDispStr[3] = ge;
	
	if(instructLed1 > 0)
	{
		qian |= 0x80;
	}
	if(instructLed2 > 0)
	{
		bai |= 0x80;
	}
	if(instructLed3 > 0)
	{
		shi |= 0x80;
	}
	if(instructLed4 > 0)
	{
		ge |= 0x80;
	}	
	write_up_disp(0x44);	   //固定地址模式
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	
	disp_led(LED2_GRID1,qian);
	disp_led(LED2_GRID2,bai);
	disp_led(LED2_GRID3,shi);
	disp_led(LED2_GRID4,ge);
	
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED2_LIGHT);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}
/*
//js_num 张数 4位
//yz_NUM 金额 5位
void LED_DISPDATA(unsigned int js_num,unsigned int yz_num,unsigned char X)
{
	unsigned int temp;
	unsigned char temp1;
   	//大数码管
	temp = js_num/1000;
	temp1 = (unsigned char)temp;
	js_qian =JS_TABLE_LED[temp1];
	
	temp = (js_num%1000)/100;
	temp1 = (unsigned char)temp;
	js_bai =JS_TABLE_LED[temp1];
	
	temp = (js_num%100)/10;
	temp1 = (unsigned char)temp;
	js_shi =JS_TABLE_LED[temp1];
	
	temp = js_num%10;
	temp1 = (unsigned char)temp;
	js_ge =JS_TABLE_LED[temp1];
	
	
//	// 小数码管
	temp = yz_num/10000;
	temp1 = (unsigned char)temp;
	yz_wan =YZ_TABLE_LED[temp1];	
	
	temp = (yz_num%10000)/1000;
	temp1 = (unsigned char)temp;
	yz_qian =YZ_TABLE_LED[temp1];		
	
	temp = (yz_num%1000)/100;
	temp1 = (unsigned char)temp;
	yz_bai =YZ_TABLE_LED[temp1];
	
	temp = (yz_num%100)/10;
	temp1 = (unsigned char)temp;
	yz_shi =YZ_TABLE_LED[temp1];
	
	temp = yz_num%10;
	temp1 = (unsigned char)temp;
	yz_ge =YZ_TABLE_LED[temp1];


	if(js_num<1000)
	{
		js_qian = 0;
		if(js_num<100) {
			js_bai = 0;
			if(js_num<10)
				js_shi = 0;
		}
	}

	if(yz_num<10000)
	{
		yz_wan = 0;
		if(yz_num<1000)
		{
		  yz_qian = 0;
		  if(yz_num<100)
		  {
			yz_bai = 0;
			if(yz_num<10)
			   yz_shi = 0;
		  }
		}
	}
	X %= 10;
	display_led(JS_TABLE_LED[X]);	  //1金额 2 红外 4 智能 8 疑币 16累加 32 混点 64 计数 128 预置
}
*/
void tm16xx_DisableDP(void)//不使用小数点
{
	write_up_disp(0x44);	   //固定地址模式
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	disp_led(0xc1,0);//去除小数点显示
	disp_led(0xc3,0);
	disp_led(0xc5,0);
	disp_led(0xc7,0);
	disp_led(0xc9,0);
	disp_led(0xcb,0);
	disp_led(0xcd,0);	
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED1_LIGHT);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}

void tm16xx_EnableDP(u8 d)//使用小数点
{
	u8 c[7];
	memset(c,0,7);
	if(d < 7)
	{
		c[d] = 0xff;
	}
	write_up_disp(0x44);	   //固定地址模式
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	disp_led(0xc3,c[0]);
	disp_led(0xc5,c[1]);
	disp_led(0xc1,c[2]);
	disp_led(0xc7,c[3]);
	disp_led(0xc9,c[4]);
	disp_led(0xcb,c[5]);
	disp_led(0xcd,c[6]);	
	GPIO_ResetBits(STB_GPIO_PORT,STB_GPIO_PIN);
	write_up_disp(LED1_LIGHT);
	GPIO_SetBits(STB_GPIO_PORT,STB_GPIO_PIN);
}

void tm16xx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(STB_GPIO_PORT_CLK |CLK_GPIO_PORT_CLK |DIO_GPIO_PORT_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	
	GPIO_InitStructure.GPIO_Pin = STB_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = STB_GPIO_MODE; 
	GPIO_Init(STB_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DIO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = DIO_GPIO_MODE; 
	GPIO_Init(DIO_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CLK_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = CLK_GPIO_MODE; 
	GPIO_Init(CLK_GPIO_PORT, &GPIO_InitStructure);
	
	gb_led1FlashOn = 0;
	gb_led2FlashOn = 0;
}

void dio_output(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	

	GPIO_InitStructure.GPIO_Pin = DIO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = DIO_GPIO_MODE; 
	GPIO_Init(DIO_GPIO_PORT, &GPIO_InitStructure);
	
}

void dio_input(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	

	GPIO_InitStructure.GPIO_Pin = DIO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(DIO_GPIO_PORT, &GPIO_InitStructure);
}
