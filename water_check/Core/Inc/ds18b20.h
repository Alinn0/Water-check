#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include"tim.h"

#define  DS18B20_DQ_OUT_HIGH       HAL_GPIO_WritePin(DS18B20_GPIO_Port, DS18B20_Pin, GPIO_PIN_SET)
#define  DS18B20_DQ_OUT_LOW        HAL_GPIO_WritePin(DS18B20_GPIO_Port, DS18B20_Pin, GPIO_PIN_RESET)
#define  DS18B20_DQ_IN             HAL_GPIO_ReadPin(DS18B20_GPIO_Port, DS18B20_Pin)

void DS18B20_IO_IN();
void DS18B20_IO_OUT();
void DS18B20_Rst(void);
uint8_t DS18B20_Check(void);
void DS18B20_Write_Byte(uint8_t data);
uint8_t DS18B20_Read_Bit(void);
uint8_t DS18B20_Read_Byte(void);
void DS18B20_Start(void);
uint8_t DS18B20_Init(void);
int DS18B20_Get_Temperature();

#endif


















