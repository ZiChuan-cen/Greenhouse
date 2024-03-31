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
//#include "delay.h"


static void BSP_Init(void);

int main(void)
{
    BSP_Init();


    while (1)
    {

    }
}


static void BSP_Init(void)
{
    BMP_Init();

    BH1750_Init();

    Soil_Hum_Init();


}

