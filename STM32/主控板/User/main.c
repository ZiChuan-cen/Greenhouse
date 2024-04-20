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

#include "OLED.h"
#include "key.h"
#include "Zigbee.h"
#include "MQTT.h"



u16 co2;
float temp;
long pressure;
float illumin;
int Tem_air = 0;
int Hum_air = 0;
float raindata;

extern int data_ready;	  // 数据接收完毕



int main(void)
{
	OLED_Init();
	Zigbee_Init();
	Key_Init();


    while (1)
    {
		if(data_ready == 1)
		{
			esp_PublishData();
			
			
		}
		

    }
}

