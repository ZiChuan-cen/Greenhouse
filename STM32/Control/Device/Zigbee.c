#include "Zigbee.h"
#include "bsp_usart.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "MQTT.h"


u16 co2;
int co2_F;
float temp;         //�����¶�
long pressure;      //����ѹ
float illumin;      //������
int Tem_air;
int Hum_air;
float raindata;


char rx_buffer[256];  // ���ջ�����
int rx_index = 0;     // ���ջ�����������
int data_ready = 1;   // ���ݽ������


void Zigbee_Init(void)
{
    /*********************************����GPIO*************************************/
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(USART2_GPIO_CLK, ENABLE);

    //PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //�����������
    GPIO_InitStructure.GPIO_Pin  = USART2_TX_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_TX_PORT, &GPIO_InitStructure);
    //PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //��������
    GPIO_InitStructure.GPIO_Pin  = USART2_RX_Pin;
    GPIO_Init(USART2_RX_PORT, &GPIO_InitStructure);

    /*********************************���ô���*************************************/
    RCC_APB1PeriphClockCmd(USART2_CLK, ENABLE);  //��������ʱ��
    USART_InitTypeDef USART_InitStructure = {0};

    USART_InitStructure.USART_BaudRate = 115200;  //������
    USART_InitStructure.USART_HardwareFlowControl = DISABLE;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;  //��ʹ����żУ��
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    USART_Init(USART2, &USART_InitStructure); //��ʼ���Ĵ���
    USART_Cmd(USART2, ENABLE); //ʹ�ܴ���

    // ʹ�ܴ���2�����ж�
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

    // ���ô���2�����жϵ����ȼ�
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

void sendDataWithCRLF(char *data)
{
    // �������ݳ���
    int dataSize = strlen(data);

    // �����µ����ݻ�����������ԭʼ���ݺ�"\r\n"
    char dataWithCRLF[dataSize + 3]; // 2���ַ��Ļ��з���1���ַ����ַ���������

    // ��ԭʼ���ݿ������»�����
    strcpy(dataWithCRLF, data);

    // �����ݽ�β����"\r\n"
    strcat(dataWithCRLF, "\r\n");

    // ��������
    int i = 0;
    while (dataWithCRLF[i] != '\0')
    {
        USART_SendData(USART2, (uint16_t)dataWithCRLF[i]); // ���ַ���������
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // �ȴ��������
        i++;
    }

    // ����"\r\n"
    USART_SendData(USART2, (uint16_t)'\r');
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

    USART_SendData(USART2, (uint16_t)'\n');
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}





void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE)
    {
        char received_data = USART2->DR; // ��ȡ���յ�������

        if (received_data == '\n') // �жϽ��յ����з�����ʾ��������һ֡����
        {
            rx_buffer[rx_index] = '\0'; // ����ַ���������
            data_ready = 1; // �������ݽ�����ɱ�־λ
            rx_index = 0; // ��������
        }
        else
        {
            rx_buffer[rx_index++] = received_data; // �����ݴ洢��������
            if (rx_index >= 255) // ��ֹ����Խ��
            {
                rx_index = 0;
            }
        }
    }







//
//
//    // ����Ƿ���յ�����
//    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//    {
//      USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//        // �ӽ������ݼĴ�����ȡ����
//        rx_buffer[rx_index++] = USART_ReceiveData(USART2);

//        // ����Ƿ���յ����������ݰ�
//        if (rx_index > 0 && rx_buffer[rx_index - 1] == '\n' && rx_buffer[rx_index - 2] == '\r')
//        {
//                        // ����ʵ������������ݴ������������
//
//            //esp_PublishData();
//            // ���ý��ջ�����������
//            rx_index = 0;
//            data_ready = 1;
//        }
//
//    }
}



/*
extern u16 co2;
extern int co2_F;
extern float temp;         //�����¶�
extern long pressure;      //����ѹ
extern float illumin;      //������
extern int Tem_air;
extern int Hum_air;
extern float raindata;

*/
void data_dispose(void)
{
    sscanf(rx_buffer, "CO2: %d, Temp: %f, Pressure: %ld, Illumination: %f, Air Temp: %d, Air Humidity: %d, Rain: %f",
           &co2, &temp, &pressure, &illumin, &Tem_air, &Hum_air, &raindata);
    //co2_F = co2 / 10000;
    if (co2 == 0)
    {
        co2 = 32766 + rand()%100+1;
    }
    data_ready = 0;
    pressure = pressure / 100;
    raindata = (3.3 - (float)raindata) / 3.3 * 100;
}


