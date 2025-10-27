#include "main.h"
//使用PA9，PA10

//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
//以上为printf支持函数

 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	
#endif
//初始化IO 串口1 
//bound:波特率
void uart1_init(u32 bound)
{
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;//gpio，串口，中断常规配置
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置（GPIO）
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

  //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_Cmd(USART1, ENABLE);  //使能串口1 
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif
	
}

//新版本

//#define BUFFER_SIZE 10// 定义了一个宏BUFFER_SIZE，表示缓冲区大小为10
int wifi_remoto[BUFFER_SIZE];// 声明了一个全局变量wifi_remoto，它是一个长度为BUFFER_SIZE的整型数组。(8<10?)
int i=0;// 声明了一个全局变量i，用于循环中的计数。
const uint8_t PACKET_START = 0xAB; // 定义了一个常量,表示数据包起始标志符

/**
 * @brief 串口1中断服务程序
 */
void USART1_IRQHandler(void)// 定义一个名为USART1_IRQHandler的中断服务程序，该函数没有参数，也没有返回值。
{
    static uint8_t state = 0; // 定义了一个静态变量state。静态变量在函数调用结束后不会被销毁，可以保持其值。state用于记录状态机的状态。
    static uint8_t data_index = 0;// 定义了一个静态变量data_index，并初始化为0。data_index用于记录当前接收到数据的位置。
    static uint8_t data_buffer[BUFFER_SIZE * sizeof(int)];// 定义了一个静态数组data_buffer，长度为BUFFER_SIZE * sizeof(int)。data_buffer用于临时存储接收到的数据。

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)// 判断USART1的接收中断是否发生。
    {
        uint8_t received_data = USART_ReceiveData(USART1);// 如果接收中断发生，那么调用USART_ReceiveData函数获取接收到的数据，并赋值给received_data。

        switch (state)// 对状态变量state进行判断，根据state的值来执行不同的操作。
        {
            case 0: // 等待数据包起始标志符
                if (received_data == PACKET_START)// 判断接收到的数据是否为数据包的起始标志符。
                {
                    state = 1;// 如果接收到的数据为数据包的起始标志符，那么将state设置为1，表示开始接收数据。
                    data_index = 0;// 并将data_index重置为0，表示从数据包的开始位置接收数据。
                }
                break;
								
						//上一步确认起始标志符后进入下一步。（state = 1实现）	

            case 1: // 接收数据
                if (data_index < BUFFER_SIZE * sizeof(int))// 小于表示数据包还没有接收完毕。
                {
                    data_buffer[data_index] = received_data;// 将接收到的数据存入data_buffer中的对应位置。
                    data_index++;// 并将data_index加1，表示已经接收到了一个数据。
                }
								
            //通过data_index加1和不断接收，直到两者大小相等。
								
                if (data_index == BUFFER_SIZE * sizeof(int))// 等于表示数据包已经接收完毕。
                {
                    // 接收完成
                    int *states_ptr = (int*)data_buffer;// 定义一个指向data_buffer的指针states_ptr。
                    for ( i = 0; i < BUFFER_SIZE; i++)// 用一个循环，将data_buffer中的数据复制到wifi_remoto中。
                    {
                        wifi_remoto[i] = *states_ptr;// 将states_ptr指向的数据赋值给wifi_remoto的对应位置。
                        states_ptr++;// 然后将states_ptr向后移动一个位置，指向下一个数据。
                    }

                    // 重置状态机和缓冲区
                    state = 0;// 表示等待接收下一个数据包的起始标志符。
                    data_index = 0;// 表示从下一个数据包的开始位置接收数据。
                    memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));// 使用memset函数，将data_buffer的所有数据清零。
                }
                break;

            default:// 当state的值不是0也不是1时，执行default的代码。（视为接收完成，开启下一个数据包的接受
                state = 0;// 将state重置为0，表示等待接收下一个数据包的起始标志符。
                data_index = 0;// 并将data_index重置为0，表示从下一个数据包的开始位置接收数据。
                memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));// 使用memset函数，将data_buffer的所有数据清零。
                break;
        }
    }

    if (USART_GetITStatus(USART1, USART_IT_ORE) != RESET ||
        USART_GetITStatus(USART1, USART_IT_FE) != RESET ||
        USART_GetITStatus(USART1, USART_IT_NE) != RESET ||
        USART_GetITStatus(USART1, USART_IT_PE) != RESET)// 当USART1的接收溢出中断、帧错误中断、噪声中断或奇偶校验错误中断发生时，执行以下代码。
    {
        // 数据接收错误，重置状态机和缓冲区
        state = 0;// 表示等待接收下一个数据包的起始标志符。
        data_index = 0;// 表示从下一个数据包的开始位置接收数据。
        memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));// 使用memset函数，将data_buffer的所有数据清零。
        USART_ClearITPendingBit(USART1, USART_IT_ORE | USART_IT_FE | USART_IT_NE | USART_IT_PE);// 调用USART_ClearITPendingBit函数，清除USART1的接收溢出中断、帧错误中断、噪声中断和奇偶校验错误中断的标志位。
    }
		

}
	   //以下为运动控制程序(备份)
//		
//		 if(wifi_remoto[1]>=0&&wifi_remoto[1]<=2)
//			{
//        Car_Go();//前进
//	    }
//	  if(wifi_remoto[1]>2&&wifi_remoto[1]<=4)
//			{
//        Car_Go_Speed_Up1();//一档加速前进
//	    }
//	  if(wifi_remoto[1]>4&&wifi_remoto[1]<=7)
//			{
//        Car_Go_Speed_Up2();//二挡加速前进
//	    }
//	  if(wifi_remoto[4]==1)
//			{
//        Car_Stop();//停车
//	    }
//	  if(wifi_remoto[1]>=-4&&wifi_remoto[1]<=0)
//			{
//        Car_Back();//后退
//	    }
//	  if(wifi_remoto[1]>=-8&&wifi_remoto[1]<-4)
//			{
//        Car_Back_Speed_Up1();//一档加速后退
//	    }
//	  if(wifi_remoto[1]>=-11&&wifi_remoto[1]<-8)
//			{
//        Car_Back_Speed_Up2();//二挡加速后退
//	    }
//	  if(wifi_remoto[2]==1)
//			{
//        Car_Left();//左转
//	    }
//	  if(wifi_remoto[3]==1)
//			{
//        Car_Right();//右转
//	    }

