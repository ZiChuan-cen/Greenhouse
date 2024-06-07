#ifndef __ESP_H
#define __ESP_H


#include "stm32f10x.h"



#define USART3_GPIO_CLK             RCC_APB2Periph_GPIOB
#define USART3_CLK                  RCC_APB1Periph_USART3
#define USART3_TX_PORT              GPIOB
#define USART3_TX_Pin               GPIO_Pin_10
#define USART3_RX_PORT              GPIOB
#define USART3_RX_Pin               GPIO_Pin_11






void ESP_GPIO_Init(void);

void Serial_SendByte(uint8_t Byte);
void SendATCommand(const char *format, ...);



#endif  /* __ESP_H */


