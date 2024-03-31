主控板
oled		IIC1	PB6	PB7
Zigbee模块	Usart3	PB10	PB11
esp-01s		Usart1	PA9	PA10
光照
二氧化碳
dht11		PB0
防水ds18b20	PB1
bh1750
sgp30	
BMP180	

采集板
Zigbee模块
光照
二氧化碳
dht11
防水ds18b20
bh1750
sgp30
土壤湿度

我准备做一个项目，分为上位机与下位机，主控芯片采用stm32f103c8t6,上位机与下位机之间的通讯通过Zigbee模块来执行，上位机有四针IIC OLED 屏显示，通过串口来控制Zigbee与ESP-01s；下位机也是通过串口控制Zigbee，同时还有BH1750光照模块，通过IIC控制，二氧化碳检测通过SGP30，有DHT11，DS18B20，土壤湿度检测
