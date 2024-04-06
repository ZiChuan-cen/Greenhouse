#include "Jw01.h"
#include "Delay.h"

u8 gReceFlag = 0;

void JW01_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ������ʱ��

    GPIO_InitTypeDef GPIO_Init_Struct;
    GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_AF_PP;                    //TXDΪ�����������
    GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_10;                          //10��ΪTXD
    GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_50MHz;                  //�������
    GPIO_Init(GPIOB, &GPIO_Init_Struct);

    GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //RXDΪ��������
    GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_11;                         //11��ΪRXD
    GPIO_Init(GPIOB, &GPIO_Init_Struct);

    USART_InitTypeDef Usart_Init_Struct;
    Usart_Init_Struct.USART_BaudRate = 9600;                                    //������
    Usart_Init_Struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
    Usart_Init_Struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;               //�շ�ģʽ
    Usart_Init_Struct.USART_Parity = USART_Parity_No;                           //��У��
    Usart_Init_Struct.USART_StopBits = USART_StopBits_1;                        //ֹͣλ1λ
    Usart_Init_Struct.USART_WordLength = USART_WordLength_8b;                   //����λ8λ
    USART_Init(USART3, &Usart_Init_Struct);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                              //���������ж�

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                             //NVIC�ж�����
    NVIC_InitTypeDef nitd;
    nitd.NVIC_IRQChannel = USART3_IRQn;
    nitd.NVIC_IRQChannelCmd = ENABLE;
    nitd.NVIC_IRQChannelPreemptionPriority = 2;
    nitd.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&nitd);

    USART_Cmd(USART3, ENABLE);
}

uint8_t CO2_Data[6];                                        //��Ž��յ������ݰ�

void USART3_IRQHandler(void)
{
    static uint8_t index = 0;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        CO2_Data[index] = USART_ReceiveData(USART3);
        if (index == 0 && CO2_Data[index] != 0x2C)          //�̶����ݰ��Ŀ�ͷ
        {
            return;
        }
        else
        {
            if (++index >= 6) index = 0;
        }
        USART_ClearITPendingBit(USART3, USART_FLAG_RXNE);   //������ݽ��ձ�־λ
        gReceFlag = 1;
    }
}


uint16_t CO2_Get(void)
{
    u16 CO2;
    if (gReceFlag == 1)
    {
        if (CO2_Data[5] == (uint8_t)(CO2_Data[0] + CO2_Data[1] + CO2_Data[2] + CO2_Data[3] + CO2_Data[4]))
        {
            CO2 = (float)(CO2_Data[1] * 256 + CO2_Data[2]);
        }
//      else
//          printf("DATA Error");
    }

    gReceFlag = 0;      //���ݽ���λ����
    return CO2;





}


