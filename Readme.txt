
供电：锂电池
显示：oled		IIC1	PB6	PB7
通讯：Zigbee模块		Usart3	PB10	PB11
			串口2
联网：esp-01s		Usart1	PA9	PA10
光敏：bh1750		IIC
CO2：sgp30		串口
温湿度：dht11		PB0
土壤温度：防水ds18b20	PB1
大气压：BMP180		
土壤湿度：
控制：矩阵键盘





主控板
显示、联网、通讯

采集板
通讯、光敏、气体、温湿度、土壤温湿度、大气压、

Zigbee模块：使用USART2，将PA2（USART2_TX）和PA3（USART2_RX）

BH1750光照模块：使用I2C1，将PB6（I2C1_SCL）和PB7（I2C1_SDA）

二氧化碳检测模块（Jw01）：使用USART3，将PB10（USART3_TX）和PB11（USART3_RX）
USART3的部分替代引脚PB8（USART3_TX）和PB9（USART3_RX）。

DHT11模块：使用单线接口，选择GPIO引脚PA11

DS18B20模块：使用单线接口，选择GPIO引脚PB1。

土壤湿度检测模块：如果它使用模拟接口，使用ADC，将PA5

BMP180大气压检测模块：使用I2C2，将PB10（I2C2_SCL）和PB11（I2C2_SDA）






基于STM32的智能大棚检测与控制系统设计与实现
分为主控板与下位机，控制器采用stm32f103c8t6
下位机集成了Zigbee模块（使用USART2）、BH1750光照模块（使用I2C1）、二氧化碳检测模块（Jw01）（使用USART1）、DHT11模块（PA11）、DS18B20（PB12）、土壤湿度检测模块（使用ADC， PA5）、BMP180大气压检测模块（I2C2）；
主控板有0.96寸OLED（IIC1，PB13    PB15）Zigbee（Usart2）、ESP - 01S（Usart3  PB10    PB11）
主控板与下位机之间通过Zigbee模块进行组网并传输数据，主控板通过ESP-01s、mqtt与阿里云云平台连接并上传数据，同时可以设置报警阈值。数据流转可以将上传至阿里云的数据在小程序上显示并控制。

