#include "IO.h"


void IO_Init(void)
{
    /*********************************≈‰÷√∑Á…»GPIO*************************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    //PA5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //∏¥”√Õ∆ÕÏ ‰≥ˆ
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);//≥ı ºªØºƒ¥Ê∆˜


    /*********************************≈‰÷√∑‰√˘∆˜GPIO*************************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}


void Fan_ON(void)       //PA5÷√1
{
    GPIO_SetBits(GPIOA, GPIO_Pin_9);
}


void Fan_OFF(void)      //PA5÷√0
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_9);
}

void Motor_ON(void)       //PA5÷√1
{
    GPIO_SetBits(GPIOA, GPIO_Pin_10);
}


void Motor_OFF(void)      //PA5÷√0
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_10);
}

void Bee_ON(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);

}
void Bee_OFF(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);

}




