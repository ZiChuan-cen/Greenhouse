#include "Zigbee.h"
#include "bsp_usart.h"



void Zigbee_Init(void)
{
    Usart2_Config();

}


uint16_t    Zigbee_RX_buff[256];

void USART2_IRQHandler(void)
{
    static uint8_t index = 0;
    if (USART_GetFlagStatus(USART2, USART_IT_RXNE) != RESET)
    {
        Zigbee_RX_buff[index] = USART_ReceiveData(USART2);


        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }


}






