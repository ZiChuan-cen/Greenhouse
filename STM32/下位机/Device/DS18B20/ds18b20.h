#ifndef __DS18B20_H
#define __DS18B20_H
#include "sys.h"

#define DS18B20_Dout_PORT                           GPIOB
#define DS18B20_Dout_PIN                            GPIO_Pin_12

#define DS18B20_OUT_L			GPIO_ResetBits(DS18B20_Dout_PORT,DS18B20_Dout_PIN)
#define DS18B20_OUT_H           GPIO_SetBits(DS18B20_Dout_PORT,DS18B20_Dout_PIN)
#define DS18B20_Data_IN         GPIO_ReadInputDataBit(DS18B20_Dout_PORT,DS18B20_Dout_PIN)


unsigned char DS18B20_Init(void);//初始化DS18B20
short DS18B20_Get_Temp(void);//获取温度
void DS18B20_Start(void);//开始温度转换
void DS18B20_Write_Byte(unsigned char dat);//写入一个字节
unsigned char DS18B20_Read_Byte(void);//读出一个字节
unsigned char DS18B20_Read_Bit(void);//读出一个位
unsigned char DS18B20_Check(void);//检测是否存在DS18B20
void DS18B20_Rst(void);//复位DS18B20  

#endif
