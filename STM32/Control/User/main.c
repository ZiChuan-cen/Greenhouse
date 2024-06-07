/**
  ******************************************************************************
  * @file    main.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-13
  * @brief   主函数
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"

#include "MQTT.h"
#include "ESP.h"
#include "Zigbee.h"
#include "TFT.h"
#include "key.h"
#include "IO.h"
#include "bsp_usart.h"



/******************************** 全局变量 ********************************/


extern u16 co2;
extern int co2_F;
extern float temp;         //土壤温度
extern long pressure;      //大气压
extern float illumin;      //光照量
extern int Tem_air;
extern int Hum_air;
extern float raindata;

extern int Fan_Flag;
extern int Motor_Flag;

extern int data_ready;   // 数据接收完毕
char flag_wifi;

extern char rx_buffer;

int Air_tem_H = 30;
int raindata_H = 25;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //TFT_GPIO_Init();
	//TFT_init();
    ESP_GPIO_Init();
    IO_Init();
    //Usart1_Config();
    Zigbee_Init();

    uint8_t Judge = 0;
    do
    {
        Judge = esp_Init();
        //OLED_ShowString(1,1,"error code:    ");
        //OLED_ShowNum(2,1,Judge,1);
    }
    while (Judge); //连接阿里云直到成功
	
	
    while (1)
    {
        while (data_ready != 0)
        {
            data_dispose();
			if(Tem_air > Air_tem_H)
			{
				Fan_ON();Bee_ON();Fan_Flag = 1;				
			}else{Fan_OFF();Bee_OFF();Fan_Flag = 0;}
			
			if(raindata < raindata_H)
			{
				Motor_ON();Bee_ON();Motor_Flag = 1;				
			}else{Motor_OFF();Bee_OFF();Motor_Flag = 0;}
			
            //    printf("CO2: %d\n", co2_F);
            //    printf("Temperature: %.2f\n", temp);
            //    printf("Pressure: %ld\n", pressure);
            //    printf("Illumination: %.2f\n", illumin);
            //    printf("Temperature of Air: %d\n", Tem_air);
            //    printf("Humidity of Air: %d\n", Hum_air);
            //    printf("Rain Data: %.2f\n", raindata);

            esp_PublishData();
//            data_ready = 0;


        }

    }

}





