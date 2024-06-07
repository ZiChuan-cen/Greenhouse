#include "key.h"




void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);
    //列
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //行
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


}








char key_row[4] = {0};
char key_row_scan(void)
{
    if (Row0 == 0) return 1;
    else if (Row1 == 0) return 2;
    else if (Row2 == 0) return 3;
    else if (Row3 == 0) return 4;
    else                 return 0;
}


char key_Scan(void)
{
    char key_num = 0;     //1-16对应的按键数
    char key_row_num = 0;      //行扫描结果记录
    GPIO_SetBits(GPIOB, GPIO_Pin_3);
    GPIO_SetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15);
    //第一行
    KEY_CLO0_OUT_LOW;
    if ((key_row_num = key_row_scan()) != 0)
    {
        while (key_row_scan() != 0); //消抖
        key_num = 0 + key_row_num;
    }
    KEY_CLO0_OUT_HIGH;

    //第二行
    KEY_CLO1_OUT_LOW;
    if ((key_row_num = key_row_scan()) != 0)
    {
        while (key_row_scan() != 0);
        key_num = 4 + key_row_num;
    }
    KEY_CLO1_OUT_HIGH;
    //第三行
    KEY_CLO2_OUT_LOW;
    if ((key_row_num = key_row_scan()) != 0)
    {
        while (key_row_scan() != 0);
        key_num = 8 + key_row_num;
    }
    KEY_CLO2_OUT_HIGH;
    //第四行
    KEY_CLO3_OUT_LOW;
    if ((key_row_num = key_row_scan()) != 0)
    {
        while (key_row_scan() != 0);
        key_num = 12 + key_row_num;
    }
    KEY_CLO3_OUT_HIGH;

    return key_num;
}


