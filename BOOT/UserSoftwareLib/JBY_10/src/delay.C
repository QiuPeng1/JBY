
/*����˽��ͷ�ļ� */
#include "_delay.h"

/*�������ӳ���*/

/************************************************************
��ʱ���ɺ���
���룺X������Ҫ��ʱ�ĺ�����
************************************************************/
void delay_Init(void)
{
	SysTick_Config(72000000 / 1000);	//1ms
}

// void delay_DelayMs
// (
// 	U16 x		//��ʱ�ĺ�����
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