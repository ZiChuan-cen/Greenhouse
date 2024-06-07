#ifndef __TFT_H
#define __TFT_H


#include "stm32f10x.h"


#define     RED          0XF800   //��ɫ
#define     GREEN        0X07E0   //��ɫ
#define     BLUE         0X001F   //��ɫ
#define     WHITE        0XFFFF   //��ɫ


#define TFT_COLUMN_NUMBER 320
#define TFT_LINE_NUMBER 240
#define TFT_COLUMN_OFFSET 0



#define PIC_NUM 28800           //ͼƬ���ݴ�С




#define SPI_SCK_0  GPIO_ResetBits(GPIOB,GPIO_Pin_5)       // ����sck�ӿڵ�PB5   ����
#define SPI_SCK_1  GPIO_SetBits(GPIOB,GPIO_Pin_5)       //��λ
#define SPI_SDA_0  GPIO_ResetBits(GPIOB,GPIO_Pin_6)       // ����SDA�ӿڵ�PB6
#define SPI_SDA_1  GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define SPI_RST_0  GPIO_ResetBits(GPIOB,GPIO_Pin_7)      // ����RST�ӿڵ�PB7
#define SPI_RST_1  GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SPI_DC_0   GPIO_ResetBits(GPIOB,GPIO_Pin_8)      // ����DC�ӿڵ�PB8
#define SPI_DC_1   GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define SPI_CS_0   GPIO_ResetBits(GPIOB,GPIO_Pin_9)    // ����/WR ��CS�ӿڵ�PB9
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



