//#include "esp8266.h"
//#define BUFFER_SIZE 8

//���ļ�Ϊ�ɰ��esp8266�����ļ��������°汾�Ѿ�Ǩ��usart.c

//int wifi_remoto[BUFFER_SIZE];
//int i=0;
///**
// * @brief �����жϷ������
//*/
//void UART1_IRQHandler(void)
//{

//    static u8 data_index = 0;
//    static u8 data_buffer[BUFFER_SIZE * sizeof(int)];//�����˾�̬����data_index��data_buffer�����ڴ洢���յ������ݡ�

//    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//����ͨ��USART_GetITStatus�����ж��Ƿ���յ������ݡ�������յ������ݣ���ͨ��USART_ReceiveData������ȡ���յ������ݡ�
//    {
//        uint8_t received_data = USART_ReceiveData(USART1);//Ȼ���ж�data_index�Ƿ�С��BUFFER_SIZE * sizeof(int)������ǣ��򽫽��յ������ݴ洢��data_buffer�У�����data_index��һ��
//        if (data_index < BUFFER_SIZE * sizeof(int))
//        {
//            data_buffer[data_index] = received_data;
//            data_index++;

//            if (data_index == BUFFER_SIZE * sizeof(int))//�����ж�data_index�Ƿ����BUFFER_SIZE * sizeof(int)������ǣ����ʾ������ɡ���data_buffer�е����ݽ�����int���͵����飬������洢��wifi_remoto�����С�
//            {
//                //�������
//                int *states_ptr = (int*)data_buffer;
//                for (i = 0; i < BUFFER_SIZE; i++)
//                {
//                    wifi_remoto[i] = *states_ptr;
//                    states_ptr++;
//                }

//                //���û�����
//                data_index = 0;
//                memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));//�������data_index��data_buffer����data_buffer���㣬�Ա���һ�ν������ݡ�
//            }
//        }
//    }
//}
