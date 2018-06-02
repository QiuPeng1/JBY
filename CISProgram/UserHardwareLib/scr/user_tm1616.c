#include "user_tm1616.h"
/**************************************/
_LEDW1629 	 			g_LEDW1629;
_LEDW91629 	 			g_LEDW91629;
/**************************************/
static const u8 LED_7[SEG_NUM]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,/*num*/
					0x77,0x7c,0x39,0x5e,0x79,0x71,/*ABCDEF*/
					0x76,/*H*/0x0e/*J*/,0x38,/*L*/0x37,/*N*/
					0x73,/*P*/0x44,/*R*/0x78,/*T*/0x3e/*U*/,
					0x6e/*Y*/,0x40/* - */,0x3f/* O */,0x00/*blank*/,0xff/*Fill*/}; 

const u8 LED_JS[SEG_NUM]={0xfc,0x84,0xba,0xae,0xC6,0x6E,0x7E,0xA4,0xfe,0xEE/*num*/,0x00
						};
const u8 LED_TOL[SEG_NUM]={0x3f,0x24,0x5d,0x75,0x66,0x73,0x7b,0x25,0x7f,0x77/*num*/,0x00
						};
//==========================delay=================================
void TM1616_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if((g_Sensitivity.DispSel!=DISP_SEL_OFF)&&(g_Sensitivity.DispSel!=DISP_STATIC)&&
        (g_Sensitivity.DispSel!=DISP_SEL_COM)&&(g_Sensitivity.DispSel!=DISP_SEL_COM_STOP))
	{
		//外显示接口
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;		
		//---------------------------------------------------------
		GPIO_InitStruct.GPIO_Pin = TM1616_STB_PIN;
		GPIO_Init(TM1616_STB_PORT, &GPIO_InitStruct);
		//---------------------------------------------------------
		GPIO_InitStruct.GPIO_Pin = TM1616_CLK_PIN;
		GPIO_Init(TM1616_CLK_PORT, &GPIO_InitStruct);
		//---------------------------------------------------------
		GPIO_InitStruct.GPIO_Pin = TM1616_DIO_PIN;
		GPIO_Init(TM1616_DIO_PORT, &GPIO_InitStruct);
	}
 	else
	{
		Usart_Config();//配置USART
	}
}
//---------------------------------------------------
void write1616(u8 wr_data)
{
	u8 i;
	BitAction BitData;
	TM1616_STB = 0;
    DelayUS(2);         
	for(i=0;i<8;i++)//开始传送8位数据，每循环一次传送一位数据   
	{   
		TM1616_CLK = 0;
		DelayUS(2);
		BitData = (BitAction)(wr_data&0x01);
		if(BitData==1)
		{
			TM1616_DIO = 1;
		}
		else
		{
			TM1616_DIO = 0;
		}
		wr_data >>= 1;//移位数据，低位在前!   
		DelayUS(2);
		TM1616_CLK = 1;
		DelayUS(2);
	}    
}
void SendDataTM1629(u8* pBuffer)  //外显示合计驱动
{
	u8 i;
	TM1616_STB = 1;TM1616_CLK = 1;TM1616_DIO = 1;    
	write1616(0x03);//显示模式设置，设置为6个GRID，8个SEG    
	TM1616_STB = 1;
	write1616(0x40);//写数据到显示寄存器，采用地址自动加一    
	TM1616_STB = 1;
	write1616(0xc0);//显示寄存器的00H单元开始   
	for(i=0;i<16;i++)   
	{       
		write1616(*pBuffer++);//给显示寄存器送数据， 
	}  
	TM1616_STB = 1;  
	write1616(0x8d);//显示控制参数，点亮数码屏幕，亮度可以通过改变低三位调节   	
	TM1616_STB = 1;
} 
//------------------------------3位侧显示---------------------------------------
void Disp_3NumW(u8* p)
{
	TM1616_STB = 1;TM1616_CLK = 1;TM1616_DIO = 1;  
	write1616(0x00);//显示模式设置，设置为6个GRID，8个SEG    
	TM1616_STB = 1;
	write1616(0x40);//写数据到显示寄存器，采用地址自动加一    
	TM1616_STB = 1;
	write1616(0xc0);//显示寄存器的00H单元开始   
	write1616(LED_7[p[0]]);
	write1616(LED_7[p[0]]);
	write1616(LED_7[p[2]]);
	write1616(LED_7[p[2]]);
	write1616(LED_7[p[4]]);
	write1616(LED_7[p[4]]);
	TM1616_STB = 1; 
	write1616(0x8d);//显示控制参数，点亮数码屏幕，亮度可以通过改变低三位调节   	
	TM1616_STB = 1;	
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Disp_TotalW(void)
{
	u8 show_array[8]={0}; 
	u32 temp = 0;
	show_array[0] = g_SysType.jishu%1000/100;
	show_array[1] = g_SysType.jishu%100/10;
	show_array[2] = g_SysType.jishu%10; 
	if(show_array[0] == 0)
	{
		show_array[0] = 10;
		if(show_array[1]==0)
		{
			show_array[1] = 10;	
		}
	}
	g_LEDW1629.LEDW_JSA = LED_JS[show_array[0]];
	g_LEDW1629.LEDW_JSB = LED_JS[show_array[1]];
	g_LEDW1629.LEDW_JSC = LED_JS[show_array[2]]; 
	/*****************去除前导0******************************/
	if(g_LCD.TOTAL) temp = g_SysType.total;
	else temp = g_SysType.yuzhi;
	show_array[0] = temp%1000000/100000;
	show_array[1] =	temp%100000/10000;
	show_array[2] =	temp%10000/1000;
	show_array[3] =	temp%1000/100;
	show_array[4] =	temp%100/10;
	show_array[5] =	temp%10;
	if(show_array[0]==0)
	{
		show_array[0] = 10;
		if(show_array[1]==0)
		{
			show_array[1] = 10;
			if(show_array[2]==0)
			{
				show_array[2] = 10;
				if(show_array[3]==0)
				{
					show_array[3] = 10;
					if(show_array[4]==0)
					{
						show_array[4] = 10;
					}
				}
			}
		}
	}
	g_LEDW1629.LEDW_TOLA = LED_TOL[show_array[0]];
	g_LEDW1629.LEDW_TOLB = LED_TOL[show_array[1]];
	g_LEDW1629.LEDW_TOLC = LED_TOL[show_array[2]];
	g_LEDW1629.LEDW_TOLD = LED_TOL[show_array[3]];
	g_LEDW1629.LEDW_TOLE = LED_TOL[show_array[4]];
	g_LEDW1629.LEDW_TOLF = LED_TOL[show_array[5]];
	SendDataTM1629((u8*)(&g_LEDW1629));
}
//-----------------新9位显示屏----------------------------------------------------
void Disp_TotalW9(void)
{
	u8 show_array[8]={0}; 
	u32 temp = 0;
    show_array[0] = g_SysType.jishu/1000;
	show_array[1] = g_SysType.jishu%1000/100;
	show_array[2] = g_SysType.jishu%100/10;
	show_array[3] = g_SysType.jishu%10; 
	if(show_array[0] == 0)
	{
		show_array[0] = _BLACK_;
		if(show_array[1]==0)
		{
			show_array[1] = _BLACK_;	
            if(show_array[2]==0)
            {
                show_array[2] = _BLACK_;	
            }
		}
	}
	g_LEDW91629.LEDW9_JSA = LED_7[show_array[0]];
	g_LEDW91629.LEDW9_JSB = LED_7[show_array[1]];
	g_LEDW91629.LEDW9_JSC = LED_7[show_array[2]]; 
    g_LEDW91629.LEDW9_JSD = LED_7[show_array[3]]; 
	/*****************去除前导0******************************/
	if(g_LCD.TOTAL) temp = g_SysType.total;
	else temp = g_SysType.yuzhi;
	show_array[0] =	temp%100000/10000;
	show_array[1] =	temp%10000/1000;
	show_array[2] =	temp%1000/100;
	show_array[3] =	temp%100/10;
	show_array[4] =	temp%10;
	if(show_array[0]==0)
	{
		show_array[0] = _BLACK_;
		if(show_array[1]==0)
		{
			show_array[1] = _BLACK_;
			if(show_array[2]==0)
			{
				show_array[2] = _BLACK_;
				if(show_array[3]==0)
				{
					show_array[3] = _BLACK_;
				}
			}
		}
	}
	g_LEDW91629.LEDW9_TOLA = LED_7[show_array[0]];
	g_LEDW91629.LEDW9_TOLB = LED_7[show_array[1]];
	g_LEDW91629.LEDW9_TOLC = LED_7[show_array[2]];
	g_LEDW91629.LEDW9_TOLD = LED_7[show_array[3]];
	g_LEDW91629.LEDW9_TOLE = LED_7[show_array[4]];
    
    g_LEDW91629.LEDW9_BJ = LED_7[_BLACK_];;
	SendDataTM1629((u8*)(&g_LEDW91629));
}
//---------------------------------------------------------------------
void Disp_Static(void)
{
    SendChar('P');SendChar(g_SysType.jishu%1000/100+0x30);
    SendChar(g_SysType.jishu%100/10+0x30);SendChar(g_SysType.jishu%10+0x30);SendChar('D');
}
//------------------------------------------
void Fill_Static(void)
{
    SendChar('P');SendChar('8');SendChar('8');SendChar('8');SendChar('D');
}
//---------------------------------------------------------
void Fill_3NumW(void)
{
	u8 h;
	TM1616_STB = 1;TM1616_CLK = 1;TM1616_DIO = 1;  
	write1616(0x00);//显示模式设置，设置为6个GRID，8个SEG    
	TM1616_STB = 1;
	write1616(0x40);//写数据到显示寄存器，采用地址自动加一    
	TM1616_STB = 1;
	write1616(0xc0);//显示寄存器的00H单元开始   
	for(h=0;h<8;h++)   
	{       
		write1616(0XFF);//给显示寄存器送数据， 
	}  
	TM1616_STB = 1;
	write1616(0x8b);//显示控制参数，点亮数码屏幕，亮度可以通过改变低三位调节   	
	TM1616_STB = 1;
}
void Fill_TotalW(void)
{
	u8 h;
	TM1616_STB = 1;TM1616_CLK = 1;TM1616_DIO = 1;   
	write1616(0x03);//显示模式设置，设置为6个GRID，8个SEG    
	TM1616_STB = 1;
	write1616(0x40);//写数据到显示寄存器，采用地址自动加一    
	TM1616_STB = 1; 
	write1616(0xc0);//显示寄存器的00H单元开始   
	for(h=0;h<16;h++)   
	{       
		write1616(0XFF);//给显示寄存器送数据， 
	}  
	TM1616_STB = 1; 
	write1616(0x8a);//显示控制参数，点亮数码屏幕，亮度可以通过改变低三位调节   	
	TM1616_STB = 1;
}

