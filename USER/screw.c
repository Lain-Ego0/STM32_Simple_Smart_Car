#include "main.h"
//以下代码失效，gpio调用更改




void init_Screw_GPIOC(void)
{

GPIO_InitTypeDef  GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 	
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
GPIO_Init(GPIOC, &GPIO_InitStructure); //配置PE
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);   
	GPIO_ResetBits(GPIOC, GPIO_Pin_1); 
}

void Screw_up(void)//丝杠上升
{
	GPIO_SetBits(GPIOC, GPIO_Pin_0);   
	GPIO_ResetBits(GPIOC, GPIO_Pin_1); 
//	TIM_SetCompare2(TIM3,5000);	//越大越快
}

void Screw_down(void)//丝杠下降
{
	GPIO_SetBits(GPIOC, GPIO_Pin_1);    
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);
//	TIM_SetCompare2(TIM3,5000);	//越大越快
}

void Screw_stop(void)//丝杠下降
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_1);    
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);
	TIM_SetCompare2(TIM3,0);	//越大越快
}


