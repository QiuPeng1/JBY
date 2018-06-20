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
/*大电机启动，小电机启动*/
void  Motor_On(void);

/*所有电机制动，刹车启动*/
void  Motor_Stop(void);
/*所有电机，自动停机*/
void  Motor_AutoStop(void);
void Motor_Break(void);//刹车
#endif
