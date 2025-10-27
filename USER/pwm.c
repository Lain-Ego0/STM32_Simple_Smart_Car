#include "main.h"

//���ļ�Ϊpwm���Ƶ������

//��ǰ����ʹ����������һ�����

void TIM2_PWM_Init(void)  
//Ŀǰ��������ʹ���ĸ���������ã�����car.c��
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//�������ö�ʱ���Ļ���������������ʱ����ʱ��Ԥ��Ƶϵ��������ģʽ���Զ����ؼĴ�����ֵ�ȡ�
  TIM_OCInitTypeDef TIM_OCInitStructure; //�������ö�ʱ��������Ƚ�ͨ���Ĳ���������ͨ����ģʽ��������ԡ�Ԥ��Ƶϵ�����Ƚ�ֵ�ȡ�
	//NVIC_InitTypeDef NVIC_InitStructure;//�����ж�����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB,ENABLE);
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2); 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2); 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2); 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM2); 
	//ʹ����PA0��PA1��PA2��PA3��
  
  TIM_TimeBaseStructure.TIM_Period = 7199;
  TIM_TimeBaseStructure.TIM_Prescaler = 71;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;//����ѡ��ʹ�ö�ʱ�������Ƶ�ʣ������ڶԶ�ʱ������Ҫ��ϸߣ��������Ƶ�ʲ����е�Ӧ�ó�����
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
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);//ʹ���Զ���װ�ؼĴ�����arr��Ԥװ��
	TIM_Cmd(TIM2 , ENABLE);
	
//	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}
 
void TIM3_PWM_Init(void)  
//���ڶ����˿�ܵ��á�

//�ö��ʹ��PA6��Ϊpwm�����
//��˿�ܵ��ʹ��PA7��Ϊpwm�����
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure; 
	//NVIC_InitTypeDef NVIC_InitStructure;//�����ж�����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3); 
	//ʹ����PA6��PA7��
  
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
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);//ʹ���Զ���װ�ؼĴ�����arr��Ԥװ��
	TIM_Cmd(TIM3 , ENABLE);
	
//	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
}





