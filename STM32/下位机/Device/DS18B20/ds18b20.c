#include "ds18b20.h"


/*************************************
    作用：延时
    时序问题调节这里，STM32F103C8T6
    64MHZ是 5 ，如果不稳定再调节
*************************************/
void delay_18B20_us(uint32_t z)
{
    z = z * 6;
    while (z--);
}

/*************************************
    作用：配置io口为输入模式

*************************************/
void DS18B20_DQ_IN()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStruct.GPIO_Pin = DS18B20_Dout_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DS18B20_Dout_PORT, &GPIO_InitStruct);
}
/*************************************
    作用：配置io口为输出模式

*************************************/

void DS18B20_IO_OUT()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStruct.GPIO_Pin = DS18B20_Dout_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DS18B20_Dout_PORT, &GPIO_InitStruct);
}


/*************************************
    作用：复位DS18B20

*************************************/

void DS18B20_Rst(void)
{
    DS18B20_IO_OUT();                       //SET PG11 OUTPUT
    DS18B20_OUT_L;                              //拉低DQ
    delay_18B20_us(750);                //拉低750us
    DS18B20_OUT_H;                              //DQ=1
    delay_18B20_us(15);                 //15US
}

//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
unsigned char DS18B20_Check(void)
{
    unsigned char retry = 0;
    DS18B20_DQ_IN();                        //SET PG11 INPUT
    while (DS18B20_Data_IN && retry < 200)
    {
        retry++;
        delay_18B20_us(1);
    };
    if (retry >= 200)return 1;
    else retry = 0;
    while (!DS18B20_Data_IN && retry < 240)
    {
        retry++;
        delay_18B20_us(1);
    };
    if (retry >= 240)return 1;
    return 0;
}
//从DS18B20读取一个位
//返回值：1/0
unsigned char DS18B20_Read_Bit(void)
{
    unsigned char data;
    DS18B20_IO_OUT();           //SET PG11 OUTPUT
    DS18B20_OUT_L;
    delay_18B20_us(2);
    DS18B20_OUT_H;
    DS18B20_DQ_IN();            //SET PG11 INPUT
    delay_18B20_us(12);
    if (DS18B20_Data_IN)data = 1;
    else data = 0;
    delay_18B20_us(50);
    return data;
}
//从DS18B20读取一个字节
//返回值：读到的数据
unsigned char DS18B20_Read_Byte(void)
{
    unsigned char i, j, dat;
    dat = 0;
    for (i = 1; i <= 8; i++)
    {
        j = DS18B20_Read_Bit();
        dat = (j << 7) | (dat >> 1);
    }
    return dat;
}

//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(unsigned char dat)
{
    unsigned char j;
    unsigned char testb;
    DS18B20_IO_OUT();               //SET PG11 OUTPUT;
    for (j = 1; j <= 8; j++)
    {
        testb = dat & 0x01;
        dat = dat >> 1;
        if (testb)
        {
            DS18B20_OUT_L;      // Write 1
            delay_18B20_us(2);
            DS18B20_OUT_H;
            delay_18B20_us(60);
        }
        else
        {
            DS18B20_OUT_L;  // Write 0
            delay_18B20_us(60);
            DS18B20_OUT_H;
            delay_18B20_us(2);
        }
    }
}
//开始温度转换
void DS18B20_Start(void)
{
    DS18B20_Rst();
    DS18B20_Check();
    DS18B20_Write_Byte(0xcc);   // skip rom
    DS18B20_Write_Byte(0x44);   // convert
}

//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250）
short DS18B20_Get_Temp(void)
{
    unsigned char temp;
    unsigned char TL, TH;
    int tem;
    DS18B20_Start();            // ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();
    DS18B20_Write_Byte(0xcc);   // skip rom
    DS18B20_Write_Byte(0xbe);   // convert

    TL = DS18B20_Read_Byte();   // LSB
    TH = DS18B20_Read_Byte();   // MSB
    if (TH > 7)
    {
        TH = ~TH;
        TL = ~TL;
        temp = 0;               //温度为负
    }
    else temp = 1;              //温度为正
    tem = TH;                   //获得高八位
    tem <<= 8;
    tem += TL;                  //获得底八位
    tem = (float)tem * 0.625;   //转换
    if (temp)
    {
        return tem;             //返回温度值
    }
    else return -tem;
}

//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在
unsigned char DS18B20_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                //使能PORTG口时钟
    GPIO_InitStruct.GPIO_Pin = DS18B20_Dout_PIN;                //PORTG.11 推挽输出
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DS18B20_Dout_PORT, &GPIO_InitStruct);

    GPIO_SetBits(DS18B20_Dout_PORT, DS18B20_Dout_PIN);   //输出1

    DS18B20_Rst();

    while (DS18B20_Get_Temp() == 850 || DS18B20_Get_Temp() == 0) ;  //防止上电读出85°
    return DS18B20_Check();
    return (0);
}

