#ifndef __TFT_H
#define __TFT_H


#include "stm32f10x.h"


#define     RED          0XF800   //红色
#define     GREEN        0X07E0   //绿色
#define     BLUE         0X001F   //蓝色
#define     WHITE        0XFFFF   //白色


#define TFT_COLUMN_NUMBER 320
#define TFT_LINE_NUMBER 240
#define TFT_COLUMN_OFFSET 0



#define PIC_NUM 28800           //图片数据大小




#define SPI_SCK_0  GPIO_ResetBits(GPIOB,GPIO_Pin_5)       // 设置sck接口到PB5   清零
#define SPI_SCK_1  GPIO_SetBits(GPIOB,GPIO_Pin_5)       //置位
#define SPI_SDA_0  GPIO_ResetBits(GPIOB,GPIO_Pin_6)       // 设置SDA接口到PB6
#define SPI_SDA_1  GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define SPI_RST_0  GPIO_ResetBits(GPIOB,GPIO_Pin_7)      // 设置RST接口到PB7
#define SPI_RST_1  GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SPI_DC_0   GPIO_ResetBits(GPIOB,GPIO_Pin_8)      // 设置DC接口到PB8
#define SPI_DC_1   GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define SPI_CS_0   GPIO_ResetBits(GPIOB,GPIO_Pin_9)    // 设置/WR 或CS接口到PB9
#define SPI_CS_1   GPIO_SetBits(GPIOB,GPIO_Pin_9)







void TFT_GPIO_Init(void);
void SPI_SendByte(unsigned  char byte);
void TFT_SEND_CMD(unsigned char o_command);
void TFT_SEND_DATA(unsigned  char o_data);
void TFT_clear(void);
void TFT_full(unsigned int color);
void TFT_init(void);
void display_char16_16(unsigned int x, unsigned int y, unsigned long color, unsigned char word_serial_number);
void Picture_Display(const unsigned char *ptr_pic);



#endif  /*  */



