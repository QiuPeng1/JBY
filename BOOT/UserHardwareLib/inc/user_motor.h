#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "user_includes.h"

#define RUN1_ON 	PER_RUN1 = 0;PER_STOP = 1
#define RUN1_OFF 	PER_RUN1 = 1;PER_STOP = 1

#define BREAK_ON 	PER_RUN1 = 1;PER_STOP = 0
#define BREAK_OFF 	PER_RUN1 = 1;PER_STOP = 1

#define RUN2_ON 	PER_RUN2 = 1
#define RUN2_OFF 	PER_RUN2 = 0

void Motor_Config(void);
/*����������С�������*/
void  Motor_On(void);

/*���е���ƶ���ɲ������*/
void  Motor_Stop(void);
/*���е�����Զ�ͣ��*/
void  Motor_AutoStop(void);
void Motor_Break(void);//ɲ��
#endif
