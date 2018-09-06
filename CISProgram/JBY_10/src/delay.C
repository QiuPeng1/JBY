
/*包含私有头文件 */
#include "_delay.h"

/*公开的子程序*/

/************************************************************
延时若干毫秒
输入：X代表需要延时的毫秒数
************************************************************/
void delay_Init(void)
{
	SysTick_Config(72000000 / 1000);	//1ms
}

// void delay_DelayMs
// (
// 	U16 x		//延时的毫秒数
// )
// {
// 	TimingDelay = x;
// 	while(TimingDelay != 0);   
// }

#define COMPUTE_TIMES_1MS 10120//72M??1ms?????
void delay_DelayMs
(
	u16 x		//??????
)
{
	u32 n;
	n = x*COMPUTE_TIMES_1MS;
	while(n > 0)
	{
		n --;
	}
}

#define COMPUTE_TIMES_1US 11//72M??1ms?????
void delay_DelayUs
(
	u16 x		//??????
)
{
	u32 n;
	n = x*COMPUTE_TIMES_1US;
	while(n > 0)
	{
		n --;
	}
}

void delay_DelayCpuTime
(
	u16 x		//??????
)
{
	u32 n;
	n = x;
	while(n > 0)
	{
		n --;
	}
}
