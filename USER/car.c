#include "main.h"

//使用PA0，PA1，PA2，PA3作为四轮的pwm口

//核心板与L298N连线:
//L298N前  左前_PA0右前_PA1  N1 1，2，3，4  PE 0,1,2,3
//L298N后  左后_PA2右后_PA3  N2 1，2，3，4  PE 7,8,9,10

//其实换成前后了，懒得改
void init_Car_GPIOE(void)
{

GPIO_InitTypeDef  GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 	
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
GPIO_Init(GPIOE, &GPIO_InitStructure); //配置PE
//PE0,PE1,PE2,PE3,PE7,PE8,PE9,PE10作为gpio口。

}

//GPIO控制

//使用函数
void Car_Go(void)
{
//前侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_3);   //输出逻辑0101
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_2); //前左往后，前右往后
//后侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_9);  //输出逻辑1010
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_10); //后左往后，后右往后
TIM_SetCompare1(TIM2,3000);	
TIM_SetCompare2(TIM2,3000);	
TIM_SetCompare3(TIM2,3000);	
TIM_SetCompare4(TIM2,3000);	
}

void Car_Go_Speed_Up1(void)
{
//前侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_3);   //输出逻辑0101
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_2); //前左往后，前右往后
//后侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_9);  //输出逻辑1010
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_10); //后左往后，后右往后
TIM_SetCompare1(TIM2,3000);	
TIM_SetCompare2(TIM2,3000);	
TIM_SetCompare3(TIM2,3000);	
TIM_SetCompare4(TIM2,3000);	
}

//PE0,PE1,PE2,PE3,PE7,PE8,PE9,PE10分别接第一个L298N和第二个L298N的N1,N2,N3,N4,N1,N2,N3,N4

void Car_Stop(void)
{
//前侧马达
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2);   //输出逻辑0000
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3); //全寄
//后侧马达
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10);  //输出逻辑0000
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9); //全寄
TIM_SetCompare1(TIM2,0);	
TIM_SetCompare2(TIM2,0);	
TIM_SetCompare3(TIM2,0);	
TIM_SetCompare4(TIM2,0);	
}

void Car_Back(void)
{
//前侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_2);   //输出逻辑1010
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_3); //前左往前，前右往前
//后侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_10);  //输出逻辑0101
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_9); //后左往前，后右往前

TIM_SetCompare1(TIM2,3000);	//越大越快
TIM_SetCompare2(TIM2,3000);	
TIM_SetCompare3(TIM2,3000);	
TIM_SetCompare4(TIM2,3000);	
}

void Car_Back_Speed_Up1(void)
{
//前侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_2);   //输出逻辑1010
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_3); //前左往前，前右往前
//后侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_10);  //输出逻辑0101
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_9); //后左往前，后右往前

TIM_SetCompare1(TIM2,5000);	//越大越快
TIM_SetCompare2(TIM2,5000);	
TIM_SetCompare3(TIM2,5000);	
TIM_SetCompare4(TIM2,5000);	
}

void Car_Left_Move(void)
{
//前侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2);   //输出逻辑0110
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3); //后左往前，后右往后
//后侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10);  //输出逻辑1001
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9); //前左往后，前右往前
TIM_SetCompare1(TIM2,3500);	
TIM_SetCompare2(TIM2,3500);	
TIM_SetCompare3(TIM2,3500);	
TIM_SetCompare4(TIM2,3500);	
}

void Car_Right_Move(void)
{
//前侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3);   //输出逻辑1001
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2); //前左往后，前右往前
//后侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9);  //输出逻辑0110
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10); //后左往前，后右往后
TIM_SetCompare1(TIM2,3500);	
TIM_SetCompare2(TIM2,3500);	
TIM_SetCompare3(TIM2,3500);	
TIM_SetCompare4(TIM2,3500);	
}

void Car_Left(void)
{
//前侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2);   //输出逻辑0110
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3); //前左往前，前右往后
//后侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9);  //输出逻辑0110
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10); //后左往前，后右往后
TIM_SetCompare1(TIM2,2000);	
TIM_SetCompare2(TIM2,2000);	
TIM_SetCompare3(TIM2,2000);	
TIM_SetCompare4(TIM2,2000);	
}

void Car_Right(void)
{
//前侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3);   //输出逻辑1001
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2); //前左往后，前右往前
//后侧马达
GPIO_SetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10);  //输出逻辑1001
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9); //后左往后，后右往前
TIM_SetCompare1(TIM2,2000);	
TIM_SetCompare2(TIM2,2000);	
TIM_SetCompare3(TIM2,2000);	
TIM_SetCompare4(TIM2,2000);	
}

