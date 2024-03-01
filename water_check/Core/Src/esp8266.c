#include "esp8266.h"


void ESP8266_CMD(char *CMD){ //发送命令
	uint8_t AT[100]={0}; // 发送的AT指令
	sprintf((char *)AT, "%s\r\n", CMD); // 构造AT指令，使用输入参数
	HAL_UART_Transmit(&huart2, AT, sizeof(AT), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1, AT, sizeof(AT), HAL_MAX_DELAY);
	HAL_Delay(500);

}




bool Connect_WiFi(char *WiFi名称, char *密码){

	  uint8_t cmd[50]={0}; // 发送的AT指令
	  uint8_t res[50]={0};
	  // 连接到指定的WiFi热点
	  sprintf((char *)cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", WiFi名称, 密码); // 构造AT指令，使用输入参数
	  HAL_UART_Transmit(&huart2, cmd, 50, HAL_MAX_DELAY); // 发送AT指令
	  HAL_UART_Transmit(&huart1, cmd, 50, HAL_MAX_DELAY); //打印调试
	  HAL_Delay(100); // 延时等待响应
	  HAL_UART_Receive(&huart2, res, 50, 5000);
	  if (strstr((char*)res, "WIFI CONNECTED")){
		  show_ip_conect();
		  HAL_UART_Transmit(&huart1, res, 50, HAL_MAX_DELAY);
		  return 1;
	  }else{
		  show_ip_disconect();
		  HAL_UART_Transmit(&huart1, res, 50, HAL_MAX_DELAY);
		  return 0;
	  }


}

bool WIFI_Init(){
	bool WiFi_flag=0;
	uint8_t ok[]="uart_ok\r\n";
	ESP8266_CMD("AT+RST");
	ESP8266_CMD("ATE0");
	WiFi_flag=Connect_WiFi("lin", "12345678");
	HAL_UART_Transmit(&huart1, ok, sizeof(ok), HAL_MAX_DELAY);
	ESP8266_CMD("AT+MQTTUSERCFG=0,1,\"test\",\"username\",\"password\",0,0,\"\"");
	ESP8266_CMD("AT+MQTTCONN=0,\"47.99.153.6\",1883,0");
	ESP8266_CMD("AT+MQTTSUB=0,\"attain\",1");
	return WiFi_flag;
}


void Send_Data(int tem,int tur,float Ph,int Weal){
	 uint8_t cmd[100]={0};
	 sprintf((char *)cmd, "AT+MQTTPUB=0,\"temp2\",\"Tur:%d--Tem:%d--Ele:%d--Ph:%d--Wael:%d\",1,0\r\n",tur,tem,(int)(Ph*10),(int)(Ph*10),Weal);
	 HAL_UART_Transmit(&huart2, cmd, 100, 100); // 发送AT指令
	 HAL_UART_Transmit(&huart1, cmd, 100, 100); // 发送AT指令
}





