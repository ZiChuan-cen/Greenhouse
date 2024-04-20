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



char rx_buffer[256];  // ���ջ�����
int rx_index = 0;     // ���ջ�����������
int data_ready = 0;	  // ���ݽ������

void USART2_IRQHandler(void)
{
    // ����Ƿ���յ�����
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        // �ӽ������ݼĴ�����ȡ����
        rx_buffer[rx_index++] = USART_ReceiveData(USART2);

        // ����Ƿ���յ����������ݰ�
        if (rx_index > 0 && rx_buffer[rx_index - 1] == '\n')
        {
            // �������յ�������
            sscanf(rx_buffer, "CO2: %d ppm, Temp: %f C, Pressure: %ld Pa, Illumination: %f lux, Air Temp: %d C, Air Humidity: %d %%, Rain: %f mm",
                   &co2, &temp, &pressure, &illumin, &Tem_air, &Hum_air, &raindata);

            // ���ý��ջ�����������
            rx_index = 0;
			data_ready = 1;
        }
    }
}





