#include "main.h"
//ʹ��PA9��PA10

//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
//����Ϊprintf֧�ֺ���

 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	
#endif
//��ʼ��IO ����1 
//bound:������
void uart1_init(u32 bound)
{
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;//gpio�����ڣ��жϳ�������
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿����ã�GPIO��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

  //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}

//�°汾

//#define BUFFER_SIZE 10// ������һ����BUFFER_SIZE����ʾ��������СΪ10
int wifi_remoto[BUFFER_SIZE];// ������һ��ȫ�ֱ���wifi_remoto������һ������ΪBUFFER_SIZE���������顣(8<10?)
int i=0;// ������һ��ȫ�ֱ���i������ѭ���еļ�����
const uint8_t PACKET_START = 0xAB; // ������һ������,��ʾ���ݰ���ʼ��־��

/**
 * @brief ����1�жϷ������
 */
void USART1_IRQHandler(void)// ����һ����ΪUSART1_IRQHandler���жϷ�����򣬸ú���û�в�����Ҳû�з���ֵ��
{
    static uint8_t state = 0; // ������һ����̬����state����̬�����ں������ý����󲻻ᱻ���٣����Ա�����ֵ��state���ڼ�¼״̬����״̬��
    static uint8_t data_index = 0;// ������һ����̬����data_index������ʼ��Ϊ0��data_index���ڼ�¼��ǰ���յ����ݵ�λ�á�
    static uint8_t data_buffer[BUFFER_SIZE * sizeof(int)];// ������һ����̬����data_buffer������ΪBUFFER_SIZE * sizeof(int)��data_buffer������ʱ�洢���յ������ݡ�

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)// �ж�USART1�Ľ����ж��Ƿ�����
    {
        uint8_t received_data = USART_ReceiveData(USART1);// ��������жϷ�������ô����USART_ReceiveData������ȡ���յ������ݣ�����ֵ��received_data��

        switch (state)// ��״̬����state�����жϣ�����state��ֵ��ִ�в�ͬ�Ĳ�����
        {
            case 0: // �ȴ����ݰ���ʼ��־��
                if (received_data == PACKET_START)// �жϽ��յ��������Ƿ�Ϊ���ݰ�����ʼ��־����
                {
                    state = 1;// ������յ�������Ϊ���ݰ�����ʼ��־������ô��state����Ϊ1����ʾ��ʼ�������ݡ�
                    data_index = 0;// ����data_index����Ϊ0����ʾ�����ݰ��Ŀ�ʼλ�ý������ݡ�
                }
                break;
								
						//��һ��ȷ����ʼ��־���������һ������state = 1ʵ�֣�	

            case 1: // ��������
                if (data_index < BUFFER_SIZE * sizeof(int))// С�ڱ�ʾ���ݰ���û�н�����ϡ�
                {
                    data_buffer[data_index] = received_data;// �����յ������ݴ���data_buffer�еĶ�Ӧλ�á�
                    data_index++;// ����data_index��1����ʾ�Ѿ����յ���һ�����ݡ�
                }
								
            //ͨ��data_index��1�Ͳ��Ͻ��գ�ֱ�����ߴ�С��ȡ�
								
                if (data_index == BUFFER_SIZE * sizeof(int))// ���ڱ�ʾ���ݰ��Ѿ�������ϡ�
                {
                    // �������
                    int *states_ptr = (int*)data_buffer;// ����һ��ָ��data_buffer��ָ��states_ptr��
                    for ( i = 0; i < BUFFER_SIZE; i++)// ��һ��ѭ������data_buffer�е����ݸ��Ƶ�wifi_remoto�С�
                    {
                        wifi_remoto[i] = *states_ptr;// ��states_ptrָ������ݸ�ֵ��wifi_remoto�Ķ�Ӧλ�á�
                        states_ptr++;// Ȼ��states_ptr����ƶ�һ��λ�ã�ָ����һ�����ݡ�
                    }

                    // ����״̬���ͻ�����
                    state = 0;// ��ʾ�ȴ�������һ�����ݰ�����ʼ��־����
                    data_index = 0;// ��ʾ����һ�����ݰ��Ŀ�ʼλ�ý������ݡ�
                    memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));// ʹ��memset��������data_buffer�������������㡣
                }
                break;

            default:// ��state��ֵ����0Ҳ����1ʱ��ִ��default�Ĵ��롣����Ϊ������ɣ�������һ�����ݰ��Ľ���
                state = 0;// ��state����Ϊ0����ʾ�ȴ�������һ�����ݰ�����ʼ��־����
                data_index = 0;// ����data_index����Ϊ0����ʾ����һ�����ݰ��Ŀ�ʼλ�ý������ݡ�
                memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));// ʹ��memset��������data_buffer�������������㡣
                break;
        }
    }

    if (USART_GetITStatus(USART1, USART_IT_ORE) != RESET ||
        USART_GetITStatus(USART1, USART_IT_FE) != RESET ||
        USART_GetITStatus(USART1, USART_IT_NE) != RESET ||
        USART_GetITStatus(USART1, USART_IT_PE) != RESET)// ��USART1�Ľ�������жϡ�֡�����жϡ������жϻ���żУ������жϷ���ʱ��ִ�����´��롣
    {
        // ���ݽ��մ�������״̬���ͻ�����
        state = 0;// ��ʾ�ȴ�������һ�����ݰ�����ʼ��־����
        data_index = 0;// ��ʾ����һ�����ݰ��Ŀ�ʼλ�ý������ݡ�
        memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));// ʹ��memset��������data_buffer�������������㡣
        USART_ClearITPendingBit(USART1, USART_IT_ORE | USART_IT_FE | USART_IT_NE | USART_IT_PE);// ����USART_ClearITPendingBit���������USART1�Ľ�������жϡ�֡�����жϡ������жϺ���żУ������жϵı�־λ��
    }
		

}
	   //����Ϊ�˶����Ƴ���(����)
//		
//		 if(wifi_remoto[1]>=0&&wifi_remoto[1]<=2)
//			{
//        Car_Go();//ǰ��
//	    }
//	  if(wifi_remoto[1]>2&&wifi_remoto[1]<=4)
//			{
//        Car_Go_Speed_Up1();//һ������ǰ��
//	    }
//	  if(wifi_remoto[1]>4&&wifi_remoto[1]<=7)
//			{
//        Car_Go_Speed_Up2();//��������ǰ��
//	    }
//	  if(wifi_remoto[4]==1)
//			{
//        Car_Stop();//ͣ��
//	    }
//	  if(wifi_remoto[1]>=-4&&wifi_remoto[1]<=0)
//			{
//        Car_Back();//����
//	    }
//	  if(wifi_remoto[1]>=-8&&wifi_remoto[1]<-4)
//			{
//        Car_Back_Speed_Up1();//һ�����ٺ���
//	    }
//	  if(wifi_remoto[1]>=-11&&wifi_remoto[1]<-8)
//			{
//        Car_Back_Speed_Up2();//�������ٺ���
//	    }
//	  if(wifi_remoto[2]==1)
//			{
//        Car_Left();//��ת
//	    }
//	  if(wifi_remoto[3]==1)
//			{
//        Car_Right();//��ת
//	    }

