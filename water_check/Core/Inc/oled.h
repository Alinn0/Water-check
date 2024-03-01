#ifndef INC_OLED_H_
#define INC_OLED_H_

#include"i2c.h"
#include "stdbool.h"
#include <stdlib.h>
#include "string.h"

void led_cmd(uint8_t cmd);
void led_data(uint8_t cmd);
void led_init();
void clear_olde();
void clear_olde_Page(uint8_t Page);
void transform(uint8_t input, uint8_t *output2, uint8_t *output1);
void Oled_Show_Word(uint8_t Page,uint8_t Row,uint8_t *Arr,bool flag);
void oled_show_zero(uint8_t Page,uint8_t Row);
void oled_show_one(uint8_t Page,uint8_t Row);
void oled_show_two(uint8_t Page,uint8_t Row);
void oled_show_three(uint8_t Page,uint8_t Row);
void oled_show_four(uint8_t Page,uint8_t Row);
void oled_show_five(uint8_t Page,uint8_t Row);
void oled_show_six(uint8_t Page,uint8_t Row);
void oled_show_seven(uint8_t Page,uint8_t Row);
void oled_show_eight(uint8_t Page,uint8_t Row);
void oled_show_nine(uint8_t Page,uint8_t Row);
void oled_show_Spa(uint8_t Page,uint8_t Row);
void oled_show_Dot(uint8_t Page,uint8_t Row);
void oled_show_minus(uint8_t Page,uint8_t Row);
void show_unmber(uint8_t page ,uint8_t row,uint8_t unmber);
void show_min_number(uint8_t page ,uint8_t row,int unmber);
void show_2_number(uint8_t page ,uint8_t row,int unmber);
void show_tem(uint8_t page ,uint8_t row,int unmber);
void show_tur(uint8_t page ,uint8_t row,int unmber);
void oled_wait();
void show_ip_conect();
void show_ip_disconect();
void Oled_Show_MultiWord(uint8_t Page,uint8_t Row,uint8_t *Arr,bool flag,uint16_t data_number);
void show_Weal(uint8_t page ,uint8_t row,int unmber);
void show_Ph(uint8_t page ,uint8_t row,int unmber);
#endif
