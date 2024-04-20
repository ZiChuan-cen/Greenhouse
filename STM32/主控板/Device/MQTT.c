#include "MQTT.h"
#include "ESP.h"
#include "delay.h"
#include "Zigbee.h"
#include <stdio.h>
#include <string.h>





extern char RECS[250];
extern u16 co2;
extern float temp;
extern long pressure;
extern float illumin;
extern int Tem_air;
extern int Hum_air;
extern float raindata;


/*"{\"clientId\":\"master-control\",
\"signmethod\":\"hmacsha1\",
\"sign\":\"B39894633F9DBB8A5464057BA5E4B88AE40378D8\",
\"productKey\":\"i3umqznXrDS\",\"deviceName\":\"master-control\"}"
*/
const char *WIFI = "FAST_6E18";
const char *WIFIASSWORD = "abcd2345.";
const char *ClintID = "master-control|securemode=3,signmethod=hmacsha1|";
const char *username = "master-control&i3umqznXrDS";
const char *passwd = "B39894633F9DBB8A5464057BA5E4B88AE40378D8";
const char *Url = "i3umqznXrDS.iot-as-mqtt.cn-shanghai.aliyuncs.com";
const char *pubtopic = "/sys/i3umqznXrDS/master-control/thing/event/property/post";           //发布
const char *subtopic = "/sys/i3umqznXrDS/master-control/thing/event/property/post_reply";     //订阅


//func1到func4为云平台上设备标识符
const char *func1 = "CO2Content";              //bool
const char *func2 = "SoilTemperature";         //float
const char *func3 = "Atmosphere";      //int
const char *func4 = "LightLux";              //bool
const char *func5 = "CurrentTemperature";         //float
const char *func6 = "mhumi";      //int
const char *func7 = "SoilMoisture";      //int



char esp_Init(void)
{
    memset(RECS, 0, sizeof(RECS));
    printf("AT+RST\r\n");  //重启
    Delay_ms(2000);

    memset(RECS, 0, sizeof(RECS));
    printf("ATE0\r\n");    //关闭回显
    Delay_ms(1000);
    if (strcmp(RECS, "OK"))
        return 1;

    printf("AT+CWMODE=1\r\n"); //Station模式
    Delay_ms(1000);
    if (strcmp(RECS, "OK"))
        return 2;

    memset(RECS, 0, sizeof(RECS));
    printf("AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI, WIFIASSWORD); //连接热点
    Delay_ms(2000);
    if (strcmp(RECS, "OK"))
        return 3;

    memset(RECS, 0, sizeof(RECS));
    printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n", ClintID, username, passwd); //用户信息配置
    Delay_ms(10);
    if (strcmp(RECS, "OK"))
        return 4;

    memset(RECS, 0, sizeof(RECS));
    printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n", Url); //连接服务器
    Delay_ms(1000);
    if (strcmp(RECS, "OK"))
        return 5;

    printf("AT+MQTTSUB=0,\"%s\",1\r\n", subtopic); //订阅消息
    Delay_ms(500);
    if (strcmp(RECS, "OK"))
        return 5;
    memset(RECS, 0, sizeof(RECS));
    return 0;
}


void esp_PublishData(void)
{
    char topic[100];
    sprintf(topic, "%s/%s", pubtopic, func1); // 拼接发布的主题

    char payload[200];
    sprintf(payload, "{\"%s\":%d,\"%s\":%.2f,\"%s\":%ld,\"%s\":%.2f,\"%s\":%d,\"%s\":%d,\"%s\":%.2f}", 
            func1, co2, func2, temp, func3, pressure, func4, illumin, func5, Tem_air, func6, Hum_air, func7, raindata);

    char cmd[500];
    sprintf(cmd, "AT+MQTTPUB=0,\"%s\",1,0,0,\"%s\"\r\n", topic, payload); // 发布数据
    printf("%s", cmd);
    Delay_ms(500);
}











