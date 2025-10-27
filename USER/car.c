#include "main.h"

//ʹ��PA0��PA1��PA2��PA3��Ϊ���ֵ�pwm��

//���İ���L298N����:
//L298Nǰ  ��ǰ_PA0��ǰ_PA1  N1 1��2��3��4  PE 0,1,2,3
//L298N��  ���_PA2�Һ�_PA3  N2 1��2��3��4  PE 7,8,9,10

//��ʵ����ǰ���ˣ����ø�
void init_Car_GPIOE(void)
{

GPIO_InitTypeDef  GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 	
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
GPIO_Init(GPIOE, &GPIO_InitStructure); //����PE
//PE0,PE1,PE2,PE3,PE7,PE8,PE9,PE10��Ϊgpio�ڡ�

}

//GPIO����

//ʹ�ú���
void Car_Go(void)
{
//ǰ�����
GPIO_SetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_3);   //����߼�0101
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_2); //ǰ������ǰ������
//������
GPIO_SetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_9);  //����߼�1010
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_10); //�������󣬺�������
TIM_SetCompare1(TIM2,3000);	
TIM_SetCompare2(TIM2,3000);	
TIM_SetCompare3(TIM2,3000);	
TIM_SetCompare4(TIM2,3000);	
}

void Car_Go_Speed_Up1(void)
{
//ǰ�����
GPIO_SetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_3);   //����߼�0101
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_2); //ǰ������ǰ������
//������
GPIO_SetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_9);  //����߼�1010
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_10); //�������󣬺�������
TIM_SetCompare1(TIM2,3000);	
TIM_SetCompare2(TIM2,3000);	
TIM_SetCompare3(TIM2,3000);	
TIM_SetCompare4(TIM2,3000);	
}

//PE0,PE1,PE2,PE3,PE7,PE8,PE9,PE10�ֱ�ӵ�һ��L298N�͵ڶ���L298N��N1,N2,N3,N4,N1,N2,N3,N4

void Car_Stop(void)
{
//ǰ�����
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2);   //����߼�0000
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3); //ȫ��
//������
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10);  //����߼�0000
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9); //ȫ��
TIM_SetCompare1(TIM2,0);	
TIM_SetCompare2(TIM2,0);	
TIM_SetCompare3(TIM2,0);	
TIM_SetCompare4(TIM2,0);	
}

void Car_Back(void)
{
//ǰ�����
GPIO_SetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_2);   //����߼�1010
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_3); //ǰ����ǰ��ǰ����ǰ
//������
GPIO_SetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_10);  //����߼�0101
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_9); //������ǰ��������ǰ

TIM_SetCompare1(TIM2,3000);	//Խ��Խ��
TIM_SetCompare2(TIM2,3000);	
TIM_SetCompare3(TIM2,3000);	
TIM_SetCompare4(TIM2,3000);	
}

void Car_Back_Speed_Up1(void)
{
//ǰ�����
GPIO_SetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_2);   //����߼�1010
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_3); //ǰ����ǰ��ǰ����ǰ
//������
GPIO_SetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_10);  //����߼�0101
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_9); //������ǰ��������ǰ

TIM_SetCompare1(TIM2,5000);	//Խ��Խ��
TIM_SetCompare2(TIM2,5000);	
TIM_SetCompare3(TIM2,5000);	
TIM_SetCompare4(TIM2,5000);	
}

void Car_Left_Move(void)
{
//ǰ�����
GPIO_SetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2);   //����߼�0110
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3); //������ǰ����������
//������
GPIO_SetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10);  //����߼�1001
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9); //ǰ������ǰ����ǰ
TIM_SetCompare1(TIM2,3500);	
TIM_SetCompare2(TIM2,3500);	
TIM_SetCompare3(TIM2,3500);	
TIM_SetCompare4(TIM2,3500);	
}

void Car_Right_Move(void)
{
//ǰ�����
GPIO_SetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3);   //����߼�1001
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2); //ǰ������ǰ����ǰ
//������
GPIO_SetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9);  //����߼�0110
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10); //������ǰ����������
TIM_SetCompare1(TIM2,3500);	
TIM_SetCompare2(TIM2,3500);	
TIM_SetCompare3(TIM2,3500);	
TIM_SetCompare4(TIM2,3500);	
}

void Car_Left(void)
{
//ǰ�����
GPIO_SetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2);   //����߼�0110
GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3); //ǰ����ǰ��ǰ������
//������
GPIO_SetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9);  //����߼�0110
GPIO_ResetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10); //������ǰ����������
TIM_SetCompare1(TIM2,2000);	
TIM_SetCompare2(TIM2,2000);	
TIM_SetCompare3(TIM2,2000);	
TIM_SetCompare4(TIM2,2000);	
}

void Car_Right(void)
{
//ǰ�����
GPIO_SetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_3);   //����߼�1001
GPIO_ResetBits(GPIOE, GPIO_Pin_1|GPIO_Pin_2); //ǰ������ǰ����ǰ
//������
GPIO_SetBits(GPIOE, GPIO_Pin_7|GPIO_Pin_10);  //����߼�1001
GPIO_ResetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9); //�������󣬺�����ǰ
TIM_SetCompare1(TIM2,2000);	
TIM_SetCompare2(TIM2,2000);	
TIM_SetCompare3(TIM2,2000);	
TIM_SetCompare4(TIM2,2000);	
}

