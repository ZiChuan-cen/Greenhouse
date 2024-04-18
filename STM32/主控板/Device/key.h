#ifndef __KEY_H
#define __KEY_H
#include "sys.h"


#include "stm32f10x.h"




//定义列按键的引脚
#define key_row0_Pin GPIO_Pin_4//列1
#define key_row1_Pin GPIO_Pin_5//列2
#define key_row2_Pin GPIO_Pin_6//列3
#define key_row3_Pin GPIO_Pin_7//列4

#define Row0 GPIO_ReadInputDataBit(GPIOB, key_row0_Pin) // 读取第1列
#define Row1 GPIO_ReadInputDataBit(GPIOB, key_row1_Pin) // 读取第2列
#define Row2 GPIO_ReadInputDataBit(GPIOB, key_row2_Pin) // 读取第3列
#define Row3 GPIO_ReadInputDataBit(GPIOB, key_row3_Pin) // 读取第4列

//定义行的低电平输出
#define KEY_CLO3_OUT_LOW  GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define KEY_CLO2_OUT_LOW  GPIO_ResetBits(GPIOA,GPIO_Pin_15)
#define KEY_CLO1_OUT_LOW  GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#define KEY_CLO0_OUT_LOW  GPIO_ResetBits(GPIOA,GPIO_Pin_11)

//定义行的高电平输出
#define KEY_CLO3_OUT_HIGH  GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define KEY_CLO2_OUT_HIGH  GPIO_SetBits(GPIOA,GPIO_Pin_15)
#define KEY_CLO1_OUT_HIGH  GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define KEY_CLO0_OUT_HIGH  GPIO_SetBits(GPIOA,GPIO_Pin_11)


void Key_Init(void);
char key_row_scan(void);
char key_Scan(void);





#endif

