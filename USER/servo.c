#include "main.h"
//只有一个舵机

void Servo_open(void)
{
	TIM_SetCompare1(TIM3,19500);
}

void Servo_close(void)
{
	TIM_SetCompare1(TIM3, 19250);
																																																																				
}



