#include "ESP.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>







void ESP_GPIO_Init(void)
{
    /*********************************** 构造结构体 ***********************************/
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef   USART_InitStructure;
//    NVIC_InitTypeDef    NVIC_InitStructure;


    /*********************************** 配置GPIO ***********************************/
    RCC_APB2PeriphClockCmd(USART3_GPIO_CLK, ENABLE);

    //PB10  USART3_TX
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;    //复用推挽输出
    GPIO_InitStructure.GPIO_Pin   = USART3_TX_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART3_TX_PORT, &GPIO_InitStructure);     //初始化寄存器

    //PB11  USART3_RX
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;  //下拉输入
    GPIO_InitStructure.GPIO_Pin   = USART3_RX_Pin;
    GPIO_Init(USART3_RX_PORT, &GPIO_InitStructure);     //初始化寄存器

    /*********************************** 配置串口 ***********************************/
    RCC_APB1PeriphClockCmd(USART3_CLK, ENABLE);

    USART_InitStructure.USART_BaudRate  =   115200;
    USART_InitStructure.USART_HardwareFlowControl   =   DISABLE;
    USART_InitStructure.USART_Mode  =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity    =   USART_Parity_No;
    USART_InitStructure.USART_StopBits  =   USART_StopBits_1;
    USART_InitStructure.USART_WordLength    =   USART_WordLength_8b;

    USART_Init(USART3, &USART_InitStructure);   //初始化寄存器
    USART_Cmd(USART3, ENABLE);  //使能串口

    /*********************************** 配置NVIC ***********************************/
//    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_Init(&NVIC_InitStructure);

//    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

}

// 使用串口三发送字节
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART3, Byte);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}


void SendATCommand(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[256]; // 假定最大长度为256
    vsprintf(buffer, format, args);

    va_end(args);

    // 发送格式化后的AT指令
    for (int i = 0; buffer[i] != '\0'; ++i)
    {
        Serial_SendByte(buffer[i]);
    }
}








