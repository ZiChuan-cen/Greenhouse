#include "Zigbee.h"
#include "bsp_usart.h"


extern u16 co2;            //����co2Ũ��   ppm
extern float temp;         //�����¶�
extern long pressure;      //����ѹ
extern float illumin;      //������

//extern DHT11Data_TypeDef dht11_data = {0};             //�����ʪ�ȴ��������ص�ֵ
extern int Tem_air;
extern int Hum_air;
extern float raindata;


void Zigbee_Init(void)
{
    Usart2_Config();

}



void USART2_SendData(uint8_t data)
{
    // �ȴ��������ݼĴ���Ϊ��
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

    // �����ݷ��͵��������ݼĴ���
    USART_SendData(USART2, data);
}

void USART2_SendString(char* str)
{
    // �����ַ�����ֱ���������ַ�
    while(*str)
    {
        USART2_SendData(*str++);
    }
}



void SendSensorData(void)
{
    char buffer[200];

    // ��ʽ������������Ϊ�ַ���
    sprintf(buffer, "CO2: %d, Temp: %.2f, Pressure: %ld, Illumination: %.2f, Air Temp: %d, Air Humidity: %d, Rain: %.2f\r\n",
            co2, temp, pressure, illumin, Tem_air, Hum_air, raindata);

    // ͨ�����ڷ����ַ���
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






