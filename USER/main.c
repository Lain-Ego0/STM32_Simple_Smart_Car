//��������ԭ�ӹ����ļ����졣
//�������ı�������ԭ�ӡ�PWM���ʵ�顱�������ĸ�������PWM�źż����ת�ٿɱ�
#include "main.h"
//��ʱ����

 int main(void)
{
	  TIM2_PWM_Init();
	  TIM3_PWM_Init();
	  Servo_close();
	  uart1_init(115200);
    init_Car_GPIOE();
	  init_Screw_GPIOC();
    delay_init(72);//���������
		while(1)
			{				
//����ΪС�������˶����Ƴ���					
		 if(wifi_remoto[1]>3&&wifi_remoto[1]<=5)
			{
        Car_Go();//ǰ��
	    }
	  if(wifi_remoto[1]>5&&wifi_remoto[1]<=7)
			{
        Car_Go_Speed_Up1();//һ������ǰ��
	    }
	  if(wifi_remoto[1]==0&&wifi_remoto[0]==0&&wifi_remoto[2]==0&&wifi_remoto[3]==0)
			{
        Car_Stop();//ͣ��
	    }
	  if(wifi_remoto[1]>=-9&&wifi_remoto[1]<-7)
			{
        Car_Back();//����
	    }
	  if(wifi_remoto[1]>=-11&&wifi_remoto[1]<-9)
			{
        Car_Back_Speed_Up1();//һ�����ٺ���
	    }
	  if(wifi_remoto[0]<-3)
			{
        Car_Left_Move();//����
	    }
	  if(wifi_remoto[0]>7)
			{
        Car_Right_Move();//����
	    }				
		if(wifi_remoto[2]<=-3)
			{
        Car_Left();//��ת
	    }
	  if(wifi_remoto[2]>=7)
			{
        Car_Right();//��ת
	    }
			
//����Ϊ�������ģ���ļ�
		 if(wifi_remoto[8]==10&&wifi_remoto[9]==-20)
			{
        Servo_open();//�۴�
	    }
	  if(wifi_remoto[8]==10&&wifi_remoto[9]==-10)
			{
        Servo_close();//�۹ر�
	    }
//����Ϊ˿�˿���ģ��
	  if(wifi_remoto[3]>3&&wifi_remoto[3]<=7)
			{
        Screw_up();//˿������
	    }
	  if(wifi_remoto[3]>=-11&&wifi_remoto[3]<-7)
			{
       Screw_down();//˿���½�
	    } 
		if(wifi_remoto[3]==0&&wifi_remoto[2]==0)
			{
       Screw_stop();//˿��ֹͣ
	    } 
//		�����ú�����servo.c�Ƿ�������	
//Servo_open();
//delay_us(3000000); // ��ʱ3��
//Servo_close();
//delay_us(3000000); // ��ʱ3��


//		�����ú�����car.c�Ƿ�������

			}
}
