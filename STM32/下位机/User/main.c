/**
  ******************************************************************************
  * @file    main.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-13
  * @brief   Ö÷º¯Êý
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"

#include "BMP180.h"
#include "BH1750.h"
#include "dht11.h"
#include "soil_hum.h"
#include "Jw01.h"
#include "bsp_usart.h"


u16 co2;


static void BSP_Init(void);

int main(void)
{
    //BSP_Init();

    Usart1_Config();


    while (1)
    {
        JW01_Init();
        co2 = CO2_Get();
        //printf("11111\r\n");

        Delay_s(1);
        printf("%d\r\n", co2);
    }
}


static void BSP_Init(void)
{
    BMP_Init();

    BH1750_Init();

    Soil_Hum_Init();

    //JW01_Init();

    //Usart1_Config();


}

