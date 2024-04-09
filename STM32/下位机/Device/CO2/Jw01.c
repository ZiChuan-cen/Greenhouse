#include "bsp_usart.h"
#include "Jw01.h"
#include "Delay.h"

u8 gReceFlag = 0;

void JW01_Init(void)
{
    Usart1_Config();    

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                              //开启接收中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                             //NVIC中断配置
    NVIC_InitTypeDef nitd;
    nitd.NVIC_IRQChannel = USART1_IRQn;
    nitd.NVIC_IRQChannelCmd = ENABLE;
    nitd.NVIC_IRQChannelPreemptionPriority = 2;
    nitd.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&nitd);

    
}

uint8_t CO2_Data[6];                                        //存放接收到的数据包

void USART1_IRQHandler(void)
{
    static uint8_t index = 0;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        CO2_Data[index] = USART_ReceiveData(USART1);
        if (index == 0 && CO2_Data[index] != 0x2C)          //固定数据包的开头
        {
            return;
        }
        else
        {
            if (++index >= 6) index = 0;
        }
        USART_ClearITPendingBit(USART1, USART_FLAG_RXNE);   //清除数据接收标志位
        gReceFlag = 1;
    }
}



//void USART3_IRQHandler(void)
//{
//    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
//    {
//        uint8_t data = USART_ReceiveData(USART3);
//        // 在这里处理接收到的数据
//    }
//}



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

    gReceFlag = 0;      //数据接收位清零
    return CO2;





}


