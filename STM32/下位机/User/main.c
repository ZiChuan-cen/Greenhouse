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

#include "BMP180.h"
#include "ds18b20.h"
#include "BH1750.h"
#include "dht11.h"
#include "soil_hum.h"
#include "Jw01.h"
#include "bsp_usart.h"
#include "Zigbee.h"

//********************************* 全局变量 *********************************//
u16 co2;            //空气co2浓度   ppm
float temp;         //土壤温度
long pressure;      //大气压
float illumin;      //光照量

DHT11Data_TypeDef dht11_data = {0};             //存放温湿度传感器返回的值
int Tem_air = 0;
int Hum_air = 0;
float raindata;


static void BSP_Init(void);

int main(void)
{
    BSP_Init();

    DS18B20_Start();




    while (1)
    {

        BMP_ReadCalibrationData();
        Dht11_ReadData(&dht11_data);
        DHT11_Check();




        co2 = CO2_Get();
        temp = DS18B20_Get_Temp();
        pressure = bmp180.p;
        illumin = BH1750_Read_Value();
        Tem_air = dht11_data.Tem;
        Hum_air = dht11_data.Hum;
        raindata = (float)(Get_Adc_Average(5, 20)) * (3.3 / 4096);
		
		SendSensorData();



    }
}


static void BSP_Init(void)
{
    BMP_Init();

    BH1750_Init();

    Soil_Hum_Init();

    JW01_Init();

    Usart1_Config();

    Zigbee_Init();

    DS18B20_Init();


}

