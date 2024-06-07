#include "MQTT.h"
#include "ESP.h"
#include "delay.h"
#include "stdio.h"

char RECS[250];
unsigned char i;
extern int data_ready;

extern int co2_F;
extern u16 co2;
extern float temp;
extern long pressure;
extern float illumin;
extern int Tem_air;
extern int Hum_air;
extern float raindata;

int Fan_Flag = 0;
int Motor_Flag = 0;

/*
i3umqznXrDS.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883
master-control|securemode=3,signmethod=hmacsha1|
master-control&i3umqznXrDS
B39894633F9DBB8A5464057BA5E4B88AE40378D8
*/


const char *WIFI = "ZICHUAN";
const char *WIFIASSWORD = "123456789";
const char *ClintID = "master-control|securemode=3\\,signmethod=hmacsha1|";
const char *username = "master-control&i3umqznXrDS";
const char *passwd = "B39894633F9DBB8A5464057BA5E4B88AE40378D8";
const char *Url = "i3umqznXrDS.iot-as-mqtt.cn-shanghai.aliyuncs.com";
const char *pubtopic = "/sys/i3umqznXrDS/master-control/thing/event/property/post";           //����
const char *subtopic = "/sys/i3umqznXrDS/master-control/thing/service/property/set";     //����
const char *CN_1 = "cn.ntp.org.cn";
const char *CN_2 = "ntp.sjtu.edu.cn";

/*
{"FanSwitch":1,
"CO2Content":255,
"LightLux":500,
"WaterOutletSwitch":1,
"Atmosphere":1000,
"SoilTemperature":50,
"CurrentTemperature":28,
"mhumi":20,
"SoilMoisture":3.3},"version":"1.0.0"} */
//func1��func7Ϊ��ƽ̨���豸��ʶ��
const char *func1 = "CO2Content";               //������̼  bool
const char *func2 = "SoilTemperature";          //�����¶�  float
const char *func3 = "Atmosphere";               //����ѹ    int
const char *func4 = "LightLux";                 //����      bool
const char *func5 = "CurrentTemperature";       //��ǰ�¶�  float
const char *func6 = "mhumi";                    //����ʪ��  int
const char *func7 = "SoilMoisture";             //����ʪ��  int
const char *func8 = "WaterOutletSwitch";
const char *func9 = "FanSwitch";

/*
func1, co2,
func2, temp,
func3, pressure,
func4, illumin,
func5, Tem_air,
func6, Hum_air,
func7, raindata
*/


char esp_Init(void)
{

    SendATCommand("AT+RSTORE\r\n");  //����
    Delay_ms(1000);

//    SendATCommand("ATE0\r\n");  //�رջ���
//    Delay_ms(2000);

    SendATCommand("AT+CWMODE=1\r\n");
    Delay_ms(2000);

    SendATCommand("AT+CIPSNTPCFG=1,8,\"%s\",\"%s\"\r\n", CN_1, CN_2); //
    Delay_ms(2000);

    SendATCommand("AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI, WIFIASSWORD); //�����ȵ�
    Delay_ms(6000);

    SendATCommand("AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"\r\n", username, passwd); //����MQTT����
    Delay_ms(3000);

    SendATCommand("AT+MQTTCLIENTID=0,\"%s\"\r\n", ClintID);
    Delay_ms(3000);

    SendATCommand("AT+MQTTCONN=0,\"%s\",1883,1\r\n", Url); //���ӷ�����
    Delay_ms(3000);


    SendATCommand("AT+MQTTSUB=0,\"%s\",1\r\n", subtopic); //������Ϣ
    Delay_ms(1000);

    return 0;
}
/*
                                                func1, co2,
                                                func2, temp,
                                                func3, pressure,
                                                func4, illumin,
                                                func5, Tem_air,
                                                func6, Hum_air,
                                                func7, raindata
*/
void esp_PublishData(void)
{
    SendATCommand("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%ld\\\,\\\"%s\\\":%.2f}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0\r\n", pubtopic, func1, co2, func2, temp);
    Delay_ms(800);
//    SendATCommand("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%.2f}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0\r\n", pubtopic, func2, temp);
//    Delay_ms(800);
    SendATCommand("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%d\\\,\\\"%s\\\":%d}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0\r\n", pubtopic, func3, pressure, func4, (int)illumin);
    Delay_ms(800);
//    SendATCommand("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%d}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0\r\n", pubtopic, func4, (int)illumin);
//    Delay_ms(800);
    SendATCommand("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%d\\\,\\\"%s\\\":%d}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0\r\n", pubtopic, func5, Tem_air, func6, Hum_air);
    Delay_ms(800);
//    SendATCommand("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%d}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0\r\n", pubtopic, func6, Hum_air);
//    Delay_ms(800);
    SendATCommand("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%f\\\,\\\"%s\\\":%d}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0\r\n", pubtopic, func7, raindata, func8, Motor_Flag);
    Delay_ms(800);
//	SendATCommand("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%d}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0\r\n", pubtopic, func8, Motor_Flag);
//    Delay_ms(800);
	SendATCommand("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%d}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0\r\n", pubtopic, func9, Fan_Flag);
    Delay_ms(800);


//    char topic[512];
//    sprintf(topic, "%s", pubtopic); // ƴ�ӷ���������

//    char payload[200];
//    sprintf(payload,"{\
//  \"params\":{\
//  \"CO2Content\": %d,\
//  \"SoilTemperature\": %.2f,\
//  \"Atmosphere\": %ld,\
//  \"LightLux\": %.2f,\
//  \"CurrentTemperature\": %d,\
//  \"mhumi\": %d, \
//  \"SoilTemperature\": %.2f}}",
//     co2_F, temp, pressure, illumin, Tem_air, Hum_air, raindata);

//    char cmd[500];
//    sprintf(cmd, "AT+MQTTPUB=0,\"%s\",\"%s\",1,0\r\n", topic, payload); // ����JSON��ʽ������
//    SendATCommand("%s", cmd);
//  Delay_ms(2000);
}

void USART3_IRQHandler()//�����жϲ����������ݴ����RECS������
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE))
    {
        RECS[i++] = USART_ReceiveData(USART3);
        if ((RECS[i - 2] == '\r') | (RECS[i - 1] == '\n'))
        {
            RECS[i - 2] = '\0';
            i = 0;
            //CommandAnalyse();
        }
    }
}









