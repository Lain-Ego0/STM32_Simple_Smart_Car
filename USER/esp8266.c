//#include "esp8266.h"
//#define BUFFER_SIZE 8

//此文件为旧版的esp8266控制文件，现在新版本已经迁往usart.c

//int wifi_remoto[BUFFER_SIZE];
//int i=0;
///**
// * @brief 串口中断服务程序
//*/
//void UART1_IRQHandler(void)
//{

//    static u8 data_index = 0;
//    static u8 data_buffer[BUFFER_SIZE * sizeof(int)];//定义了静态变量data_index和data_buffer，用于存储接收到的数据。

//    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//接着通过USART_GetITStatus函数判断是否接收到了数据。如果接收到了数据，则通过USART_ReceiveData函数读取接收到的数据。
//    {
//        uint8_t received_data = USART_ReceiveData(USART1);//然后判断data_index是否小于BUFFER_SIZE * sizeof(int)，如果是，则将接收到的数据存储到data_buffer中，并将data_index加一。
//        if (data_index < BUFFER_SIZE * sizeof(int))
//        {
//            data_buffer[data_index] = received_data;
//            data_index++;

//            if (data_index == BUFFER_SIZE * sizeof(int))//接着判断data_index是否等于BUFFER_SIZE * sizeof(int)，如果是，则表示接收完成。将data_buffer中的数据解析成int类型的数组，并将其存储到wifi_remoto数组中。
//            {
//                //接收完成
//                int *states_ptr = (int*)data_buffer;
//                for (i = 0; i < BUFFER_SIZE; i++)
//                {
//                    wifi_remoto[i] = *states_ptr;
//                    states_ptr++;
//                }

//                //重置缓冲区
//                data_index = 0;
//                memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));//最后重置data_index和data_buffer，将data_buffer清零，以便下一次接收数据。
//            }
//        }
//    }
//}
