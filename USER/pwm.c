#include "main.h"

//该文件为pwm控制电机与舵机

//当前方案使用五个电机和一个舵机

void TIM2_PWM_Init(void)  
//目前车辆驱动使用四个电机（轮用）（见car.c）
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//用于配置定时器的基本参数，包括定时器的时钟预分频系数、计数模式、自动重载寄存器的值等。
  TIM_OCInitTypeDef TIM_OCInitStructure; //用于配置定时器的输出比较通道的参数，包括通道的模式、输出极性、预分频系数、比较值等。
	//NVIC_InitTypeDef NVIC_InitStructure;//用于中断配置
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB,ENABLE);
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2); 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2); 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2); 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM2); 
	//使用了PA0，PA1，PA2，PA3。
  
  TIM_TimeBaseStructure.TIM_Period = 7199;
  TIM_TimeBaseStructure.TIM_Prescaler = 71;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;//可以选择使用定时器的最大频率，适用于对定时器精度要求较高，但对溢出频率不敏感的应用场景。
  TIM_TimeBaseInit(TIM2 , &TIM_TimeBaseStructure);
 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC1Init(TIM2 , &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2 , TIM_OCPreload_Enable);
  TIM_OC2Init(TIM2 , &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2 , TIM_OCPreload_Enable);
  TIM_OC3Init(TIM2 , &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2 , TIM_OCPreload_Enable);
	TIM_OC4Init(TIM2 , &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM2 , TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);//使能自动重装载寄存器，arr的预装载
	TIM_Cmd(TIM2 , ENABLE);
	
//	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}
 
void TIM3_PWM_Init(void)  
//用于舵机和丝杠调用。

//该舵机使用PA6作为pwm输出。
//该丝杠电机使用PA7作为pwm输出。
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure; 
	//NVIC_InitTypeDef NVIC_InitStructure;//用于中断配置
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3); 
	//使用了PA6，PA7。
  
  TIM_TimeBaseStructure.TIM_Period = 19999;
  TIM_TimeBaseStructure.TIM_Prescaler = 83;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseInit(TIM3 , &TIM_TimeBaseStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_Pulse = 0;
	
  TIM_OC1Init(TIM3 , &TIM_OCInitStructure);
  TIM_OC2Init(TIM3 , &TIM_OCInitStructure);
  
	TIM_OC1PreloadConfig(TIM3 , TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3 , TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);//使能自动重装载寄存器，arr的预装载
	TIM_Cmd(TIM3 , ENABLE);
	
//	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
}





