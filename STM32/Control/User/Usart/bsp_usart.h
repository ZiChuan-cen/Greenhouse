#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h"                  // Device header

#define USART1_GPIO_CLK				RCC_APB2Periph_GPIOA
#define USART1_CLK					RCC_APB2Periph_USART1
#define USART1_TX_PORT				GPIOA
#define USART1_TX_Pin				GPIO_Pin_9
#define USART1_RX_PORT				GPIOA
#define USART1_RX_Pin				GPIO_Pin_10





void Usart1_Config(void);

#endif /* __BSP_USART_H */

