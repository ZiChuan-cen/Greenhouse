#include "Zigbee.h"
#include "bsp_usart.h"


extern u16 co2;            //空气co2浓度   ppm
extern float temp;         //土壤温度
extern long pressure;      //大气压
extern float illumin;      //光照量

//extern DHT11Data_TypeDef dht11_data = {0};             //存放温湿度传感器返回的值
extern int Tem_air;
extern int Hum_air;
extern float raindata;


void Zigbee_Init(void)
{
    Usart2_Config();

}



void USART2_SendData(uint8_t data)
{
    // 等待发送数据寄存器为空
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

    // 将数据发送到发送数据寄存器
    USART_SendData(USART2, data);
}

void USART2_SendString(char* str)
{
    // 遍历字符串，直到遇到空字符
    while(*str)
    {
        USART2_SendData(*str++);
    }
}



void SendSensorData(void)
{
    char buffer[200];

    // 格式化传感器数据为字符串
    sprintf(buffer, "CO2: %d, Temp: %.2f, Pressure: %ld, Illumination: %.2f, Air Temp: %d, Air Humidity: %d, Rain: %.2f\r\n",
            co2, temp, pressure, illumin, Tem_air, Hum_air, raindata);

    // 通过串口发送字符串
    USART2_SendString(buffer);
}






uint16_t    Zigbee_RX_buff[256];

void USART2_IRQHandler(void)
{
    static uint8_t index = 0;
    if (USART_GetFlagStatus(USART2, USART_IT_RXNE) != RESET)
    {
        Zigbee_RX_buff[index] = USART_ReceiveData(USART2);


        USART_ClearITPendingBit(USART2, USART_IT_RXNE);

        index++;
        if (index >= sizeof(Zigbee_RX_buff) / sizeof(Zigbee_RX_buff[0]))
        {
            index = 0;
        }
    }


}






