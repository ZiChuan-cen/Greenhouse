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

#include "OLED.h"
#include "key.h"
#include "Zigbee.h"



int main(void)
{
	OLED_Init();
	Zigbee_Init();
	Key_Init();
	//OLED_Display_On();
	int Q;


    while (1)
    {
		Q = 1234;
		
		OLED_ShowCHinese(1, 1, "Óë");
		Delay_s(2);
		OLED_Clear();
		Delay_s(2);
		

    }
}

