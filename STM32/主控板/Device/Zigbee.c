#include "Zigbee.h"
#include "bsp_usart.h"
#include "stdio.h"




extern u16 co2;
extern float temp;
extern long pressure;
extern float illumin;
extern int Tem_air;
extern int Hum_air;
extern float raindata;


void Zigbee_Init(void)
{
    Usart2_Config();

}



char rx_buffer[256];  // 接收缓冲区
int rx_index = 0;     // 接收缓冲区的索引
int data_ready = 0;	  // 数据接收完毕

void USART2_IRQHandler(void)
{
    // 检查是否接收到数据
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        // 从接收数据寄存器读取数据
        rx_buffer[rx_index++] = USART_ReceiveData(USART2);

        // 检查是否接收到完整的数据包
        if (rx_index > 0 && rx_buffer[rx_index - 1] == '\n')
        {
            // 解析接收到的数据
            sscanf(rx_buffer, "CO2: %d ppm, Temp: %f C, Pressure: %ld Pa, Illumination: %f lux, Air Temp: %d C, Air Humidity: %d %%, Rain: %f mm",
                   &co2, &temp, &pressure, &illumin, &Tem_air, &Hum_air, &raindata);

            // 重置接收缓冲区的索引
            rx_index = 0;
			data_ready = 1;
        }
    }
}





