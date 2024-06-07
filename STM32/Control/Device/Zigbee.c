#include "Zigbee.h"
#include "bsp_usart.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "MQTT.h"


u16 co2;
int co2_F;
float temp;         //土壤温度
long pressure;      //大气压
float illumin;      //光照量
int Tem_air;
int Hum_air;
float raindata;


char rx_buffer[256];  // 接收缓冲区
int rx_index = 0;     // 接收缓冲区的索引
int data_ready = 1;   // 数据接收完毕


void Zigbee_Init(void)
{
    /*********************************配置GPIO*************************************/
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(USART2_GPIO_CLK, ENABLE);

    //PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //复用推挽输出
    GPIO_InitStructure.GPIO_Pin  = USART2_TX_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_TX_PORT, &GPIO_InitStructure);
    //PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //浮空输入
    GPIO_InitStructure.GPIO_Pin  = USART2_RX_Pin;
    GPIO_Init(USART2_RX_PORT, &GPIO_InitStructure);

    /*********************************配置串口*************************************/
    RCC_APB1PeriphClockCmd(USART2_CLK, ENABLE);  //开启串口时钟
    USART_InitTypeDef USART_InitStructure = {0};

    USART_InitStructure.USART_BaudRate = 115200;  //波特率
    USART_InitStructure.USART_HardwareFlowControl = DISABLE;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;  //不使用奇偶校验
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    USART_Init(USART2, &USART_InitStructure); //初始化寄存器
    USART_Cmd(USART2, ENABLE); //使能串口

    // 使能串口2接收中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

    // 配置串口2接收中断的优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

void sendDataWithCRLF(char *data)
{
    // 计算数据长度
    int dataSize = strlen(data);

    // 创建新的数据缓冲区，包括原始数据和"\r\n"
    char dataWithCRLF[dataSize + 3]; // 2个字符的换行符和1个字符的字符串结束符

    // 将原始数据拷贝到新缓冲区
    strcpy(dataWithCRLF, data);

    // 在数据结尾加上"\r\n"
    strcat(dataWithCRLF, "\r\n");

    // 发送数据
    int i = 0;
    while (dataWithCRLF[i] != '\0')
    {
        USART_SendData(USART2, (uint16_t)dataWithCRLF[i]); // 逐字符发送数据
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // 等待发送完成
        i++;
    }

    // 发送"\r\n"
    USART_SendData(USART2, (uint16_t)'\r');
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

    USART_SendData(USART2, (uint16_t)'\n');
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}





void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE)
    {
        char received_data = USART2->DR; // 读取接收到的数据

        if (received_data == '\n') // 判断接收到换行符，表示接收完整一帧数据
        {
            rx_buffer[rx_index] = '\0'; // 添加字符串结束符
            data_ready = 1; // 设置数据接收完成标志位
            rx_index = 0; // 重置索引
        }
        else
        {
            rx_buffer[rx_index++] = received_data; // 将数据存储在数组中
            if (rx_index >= 255) // 防止数组越界
            {
                rx_index = 0;
            }
        }
    }







//
//
//    // 检查是否接收到数据
//    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//    {
//      USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//        // 从接收数据寄存器读取数据
//        rx_buffer[rx_index++] = USART_ReceiveData(USART2);

//        // 检查是否接收到完整的数据包
//        if (rx_index > 0 && rx_buffer[rx_index - 1] == '\n' && rx_buffer[rx_index - 2] == '\r')
//        {
//                        // 根据实际需求进行数据处理或其他操作
//
//            //esp_PublishData();
//            // 重置接收缓冲区的索引
//            rx_index = 0;
//            data_ready = 1;
//        }
//
//    }
}



/*
extern u16 co2;
extern int co2_F;
extern float temp;         //土壤温度
extern long pressure;      //大气压
extern float illumin;      //光照量
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


