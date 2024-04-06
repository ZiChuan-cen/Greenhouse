#ifndef __DS18B20_H
#define __DS18B20_H
#include "sys.h"

#define DS18B20_Dout_PORT                           GPIOB
#define DS18B20_Dout_PIN                            GPIO_Pin_12

#define DS18B20_OUT_L			GPIO_ResetBits(DS18B20_Dout_PORT,DS18B20_Dout_PIN)
#define DS18B20_OUT_H           GPIO_SetBits(DS18B20_Dout_PORT,DS18B20_Dout_PIN)
#define DS18B20_Data_IN         GPIO_ReadInputDataBit(DS18B20_Dout_PORT,DS18B20_Dout_PIN)


unsigned char DS18B20_Init(void);//��ʼ��DS18B20
short DS18B20_Get_Temp(void);//��ȡ�¶�
void DS18B20_Start(void);//��ʼ�¶�ת��
void DS18B20_Write_Byte(unsigned char dat);//д��һ���ֽ�
unsigned char DS18B20_Read_Byte(void);//����һ���ֽ�
unsigned char DS18B20_Read_Bit(void);//����һ��λ
unsigned char DS18B20_Check(void);//����Ƿ����DS18B20
void DS18B20_Rst(void);//��λDS18B20  

#endif
