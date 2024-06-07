#ifndef __ZIGBEE_H
#define __ZIGBEE_H


#include "stm32f10x.h"                  // Device header

#define USART2_GPIO_CLK				RCC_APB2Periph_GPIOA
#define USART2_CLK					RCC_APB1Periph_USART2
#define USART2_TX_PORT				GPIOA
#define USART2_TX_Pin				GPIO_Pin_2	
#define USART2_RX_PORT				GPIOA
#define USART2_RX_Pin				GPIO_Pin_3


void Zigbee_Init(void);
void data_dispose(void);









#endif
