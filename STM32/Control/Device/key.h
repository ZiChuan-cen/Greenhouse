#ifndef __KEY_H
#define __KEY_H
#include "sys.h"


#include "stm32f10x.h"




//�����а���������
#define key_row0_Pin GPIO_Pin_4//��1
#define key_row1_Pin GPIO_Pin_5//��2
#define key_row2_Pin GPIO_Pin_6//��3
#define key_row3_Pin GPIO_Pin_7//��4

#define Row0 GPIO_ReadInputDataBit(GPIOB, key_row0_Pin) // ��ȡ��1��
#define Row1 GPIO_ReadInputDataBit(GPIOB, key_row1_Pin) // ��ȡ��2��
#define Row2 GPIO_ReadInputDataBit(GPIOB, key_row2_Pin) // ��ȡ��3��
#define Row3 GPIO_ReadInputDataBit(GPIOB, key_row3_Pin) // ��ȡ��4��

//�����еĵ͵�ƽ���
#define KEY_CLO3_OUT_LOW  GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define KEY_CLO2_OUT_LOW  GPIO_ResetBits(GPIOA,GPIO_Pin_15)
#define KEY_CLO1_OUT_LOW  GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#define KEY_CLO0_OUT_LOW  GPIO_ResetBits(GPIOA,GPIO_Pin_11)

//�����еĸߵ�ƽ���
#define KEY_CLO3_OUT_HIGH  GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define KEY_CLO2_OUT_HIGH  GPIO_SetBits(GPIOA,GPIO_Pin_15)
#define KEY_CLO1_OUT_HIGH  GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define KEY_CLO0_OUT_HIGH  GPIO_SetBits(GPIOA,GPIO_Pin_11)


void Key_Init(void);
char key_row_scan(void);
char key_Scan(void);





#endif

