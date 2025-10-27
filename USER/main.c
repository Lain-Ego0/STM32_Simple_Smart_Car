//基于正点原子工程文件改造。
//主函数改编自正点原子“PWM输出实验”，驱动四个电机输出PWM信号即电机转速可变
#include "main.h"
//延时函数

 int main(void)
{
	  TIM2_PWM_Init();
	  TIM3_PWM_Init();
	  Servo_close();
	  uart1_init(115200);
    init_Car_GPIOE();
	  init_Screw_GPIOC();
    delay_init(72);//常规的配置
		while(1)
			{				
//以下为小车四轮运动控制程序					
		 if(wifi_remoto[1]>3&&wifi_remoto[1]<=5)
			{
        Car_Go();//前进
	    }
	  if(wifi_remoto[1]>5&&wifi_remoto[1]<=7)
			{
        Car_Go_Speed_Up1();//一档加速前进
	    }
	  if(wifi_remoto[1]==0&&wifi_remoto[0]==0&&wifi_remoto[2]==0&&wifi_remoto[3]==0)
			{
        Car_Stop();//停车
	    }
	  if(wifi_remoto[1]>=-9&&wifi_remoto[1]<-7)
			{
        Car_Back();//后退
	    }
	  if(wifi_remoto[1]>=-11&&wifi_remoto[1]<-9)
			{
        Car_Back_Speed_Up1();//一档加速后退
	    }
	  if(wifi_remoto[0]<-3)
			{
        Car_Left_Move();//左移
	    }
	  if(wifi_remoto[0]>7)
			{
        Car_Right_Move();//右移
	    }				
		if(wifi_remoto[2]<=-3)
			{
        Car_Left();//左转
	    }
	  if(wifi_remoto[2]>=7)
			{
        Car_Right();//右转
	    }
			
//以下为舵机控制模版文件
		 if(wifi_remoto[8]==10&&wifi_remoto[9]==-20)
			{
        Servo_open();//槽打开
	    }
	  if(wifi_remoto[8]==10&&wifi_remoto[9]==-10)
			{
        Servo_close();//槽关闭
	    }
//以下为丝杆控制模版
	  if(wifi_remoto[3]>3&&wifi_remoto[3]<=7)
			{
        Screw_up();//丝杠上升
	    }
	  if(wifi_remoto[3]>=-11&&wifi_remoto[3]<-7)
			{
       Screw_down();//丝杠下降
	    } 
		if(wifi_remoto[3]==0&&wifi_remoto[2]==0)
			{
       Screw_stop();//丝杠停止
	    } 
//		测试用函数（servo.c是否正常）	
//Servo_open();
//delay_us(3000000); // 延时3秒
//Servo_close();
//delay_us(3000000); // 延时3秒


//		测试用函数（car.c是否正常）

			}
}
