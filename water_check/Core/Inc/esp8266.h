/*
 * esp8266.h
 *
 *  Created on: Dec 12, 2023
 *      Author: Alin
 */

#ifndef INC_ESP8266_H_
#define INC_ESP8266_H_

#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "oled.h"
#include "stdbool.h"
bool Connect_WiFi(char *WiFi名称, char *密码);
void ESP8266_CMD(char *CMD);
bool WIFI_Init();
void Send_Data(int tem,int tur,float Ph,int Weal);
void ReConnectWiFi(char *WiFi名称, char *密码);
#endif /* INC_ESP8266_H_ */
