// 引入头文件
#include "oled.h"
#include "oled_lib.h"




// 定义SSD1315模块的I2C地址，根据您的模块的规格来确定
#define oledAddress 0x78

// 定义SSD1315模块的命令模式和数据模式，通常不需要修改
#define oledCommandMode 0x00
#define oledDateMode 0x40



// SSD1315模块的发送命令函数
void led_cmd (uint8_t cmd)
{
	uint8_t sendbuf[2]={0};
	sendbuf[0]=oledCommandMode; // 使用宏定义来表示命令模式
	sendbuf[1]=cmd;
	HAL_I2C_Master_Transmit(&hi2c1,oledAddress,sendbuf,sizeof(sendbuf),HAL_MAX_DELAY);

}
// SSD1315模块的发送数据函数
void led_data(uint8_t cmd)
{
	uint8_t sendbuf[2]={0};
	sendbuf[0]=oledDateMode;
	sendbuf[1]=cmd;
	HAL_I2C_Master_Transmit(&hi2c1,oledAddress,sendbuf,sizeof(sendbuf),HAL_MAX_DELAY);
}

// SSD1315模块的初始化函数
void led_init(){
	HAL_Delay(1000);
	led_cmd(0xAE); // 关闭显示
	led_cmd(0xD5); // 设置时钟分频因子
	led_cmd(0x80); // 默认值
	led_cmd(0xA8); // 设置多路复用比
	led_cmd(0x3F); // 64
	led_cmd(0xD3); // 设置显示偏移
	led_cmd(0x00); // 偏移量为0
	led_cmd(0x40); // 设置显示起始行为0
	led_cmd(0x8D); // 开启电荷泵
	led_cmd(0x14); // 使能
	led_cmd(0x20); // 设置内存地址模式
	led_cmd(0x02); // 页地址模式
	led_cmd(0xA1); // 设置段重映射
	led_cmd(0xC8); // 设置COM输出扫描方向
	led_cmd(0xDA); // 设置COM硬件引脚配置
	led_cmd(0x12); // 连续模式
	led_cmd(0x81); // 设置对比度
	led_cmd(0xCF); // 207
	led_cmd(0xD9); // 设置预充电周期
	led_cmd(0xF1); // 15 DCLKs和1 DCLK
	led_cmd(0xDB); // 设置VCOMH解除电压
	led_cmd(0x30); // 0.77 x VCC
	led_cmd(0xA4); // 正常方向
	led_cmd(0xA6); // 非反相显示
	led_cmd(0xAF); // 开启显示


}

void clear_olde(){//清屏
	for(uint8_t i=0;i<8;i++){
	led_cmd(0xB0+i);
	led_cmd(0x00);
	led_cmd(0x10);
	uint8_t senbuf[129]={0};
	senbuf[0]=0x40;
	HAL_I2C_Master_Transmit(&hi2c1,oledAddress,senbuf,sizeof(senbuf),HAL_MAX_DELAY);
	}

}

void clear_olde_Page(uint8_t Page){//清页
	led_cmd(0xB0+Page);
	led_cmd(0x00);
	led_cmd(0x10);
	uint8_t senbuf[129]={0};
	senbuf[0]=0x40;
	HAL_I2C_Master_Transmit(&hi2c1,oledAddress,senbuf,sizeof(senbuf),HAL_MAX_DELAY);

}

void transform(uint8_t input, uint8_t* low, uint8_t* high) {  //将列转换为两个数
    // 设置低4位
    *low = (input & 0x0F) & 0x0F;
    // 设置高4位
    *high = ((input >> 4) & 0x0F) | 0x10;
}

void oled_show(uint8_t page,uint8_t row,uint8_t date[], size_t size){  //显示一个数据
   uint8_t low,high;
   row=row+0x00;
   transform(row,&low,&high);
   led_cmd(page+0xB0);
   led_cmd(low);
   led_cmd(high);
   HAL_I2C_Master_Transmit(&hi2c1,oledAddress,date,size,HAL_MAX_DELAY);

}


void oled_wait(){//至此，已成艺术
	uint8_t zhici_up[]={0x40,0x00,0x02,0x42,0x62,0x52,0x4A,0x46,0x42,0x42,0x42,0x52,0x62,0xC2,0x02,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0xFF,0x20,0x20,0x00,0xFF,0x40,0x20,0x10,0x08,0x00,0x00};
	uint8_t zhici_down[]={0x40,0x40,0x40,0x44,0x44,0x44,0x44,0x44,0x7F,0x44,0x44,0x44,0x44,0x44,0x40,0x40,0x00,0x20,0x60,0x3F,0x20,0x10,0x1F,0x10,0x10,0x00,0x3F,0x40,0x40,0x40,0x40,0x78,0x00};
	uint8_t ycys_up[]={0x40,0x00,0x00,0xE2,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0x08,0x08,0xFF,0x08,0x09,0x0A,0xC8,0x08,0x00,0x04,0x04,0x44,0x44,0x5F,0x44,0x44,0x44,0xC4,0xC4,0x5F,0x04,0x04,0x04,0x04,0x00,0x00,0x10,0x10,0x10,0x10,0xD0,0x30,0xFF,0x30,0xD0,0x12,0x1C,0x10,0x10,0x00,0x00};
	uint8_t ycys_down[]={0x40,0x00,0x00,0x3F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x78,0x00,0x00,0x80,0x60,0x1F,0x00,0x10,0x20,0x1F,0x80,0x40,0x21,0x16,0x18,0x26,0x41,0xF8,0x00,0x00,0x00,0x30,0x48,0x44,0x42,0x41,0x41,0x40,0x40,0x40,0x40,0x40,0x70,0x00,0x00,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0xFF,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x00};
	oled_show(2,47,zhici_up,sizeof(zhici_up));
	oled_show(3,47,zhici_down,sizeof(zhici_down));
	oled_show(4,31,ycys_up,sizeof(ycys_up));
	oled_show(5,31,ycys_down,sizeof(ycys_down));

}


void Oled_Show_MultiWord(uint8_t Page,uint8_t Row,uint8_t *Arr,bool flag, uint16_t data_number){
	uint8_t low,high,i,j,index=0,temp[129]={0};
	temp[0]=0x40;
	if(Page>=8||Row>=128||data_number>256){
		return;
	}
	Page=Page+0XB0;
	Row=Row+0x00;
	transform(Row,&low,&high);
	if(flag){
		for(j=0;j<data_number;j+=16){
            for(i=0;i<8;i++){
    	        temp[index+1]=Arr[i+j];
    	        index++;

            }
		}
        led_cmd(Page);
        led_cmd(low);
	    led_cmd(high);
	    if(Row+(data_number/2)>128){
	        HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,128-Row,HAL_MAX_DELAY);
	    }else{
	    	HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,data_number/2,HAL_MAX_DELAY);
	    }
	    memset(temp,0,sizeof(temp));
	    index=0;
	    temp[0]=0x40;
	    for(j=8;j<data_number;j+=16){
	        for(i=0;i<8;i++){
	        	temp[index+1]=Arr[i+j];
	        	index++;
	        }
	    }
	    led_cmd(Page+1);
	    led_cmd(low);
        led_cmd(high);
        if(Row+(data_number/2)>128){
        	        HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,128-Row,HAL_MAX_DELAY);
        	    }else{
        	    	HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,data_number/2,HAL_MAX_DELAY);
        	    }
	}else{
		for(j=0;j<data_number;j+=32){
			for(i=0;i<16;i++){
			    temp[index+1]=Arr[i+j];
			    index++;
			}
		}
	    led_cmd(Page);
	    led_cmd(low);
		led_cmd(high);
		if(Row+(data_number/2)>128){
			        HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,128-Row,HAL_MAX_DELAY);
			    }else{
			    	HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,data_number/2,HAL_MAX_DELAY);
			    }
		memset(temp,0,sizeof(temp));
		index=0;
		temp[0]=0x40;
		for(j=16;j<data_number;j+=32){
			for(i=0;i<16;i++){
			    temp[index+1]=Arr[i+j];
			    index++;
			}
		}
		led_cmd(Page+1);
		led_cmd(low);
	    led_cmd(high);
	    if(Row+(data_number/2)>128){
	    	        HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,128-Row,HAL_MAX_DELAY);
	    	    }else{
	    	    	HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,data_number/2,HAL_MAX_DELAY);
	    	    }
	}
}


void Oled_Show_Word(uint8_t Page,uint8_t Row,uint8_t *Arr,bool flag){//指定位置显示字或者字母
	uint8_t low,high,i,temp[17]={0};
	temp[0]=0x40;
	if(Page>=8||Row>=128){
		return;
	}
	Page=Page+0XB0;
	Row=Row+0x00;
	transform(Row,&low,&high);
	if(flag){          //如果为字母
        for(i=0;i<8;i++){
    	temp[i+1]=Arr[i];
             }
        led_cmd(Page);
        led_cmd(low);
	    led_cmd(high);
	    HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,sizeof(temp),HAL_MAX_DELAY);
	    for(i=0;i<8;i++){
	      temp[i+1]=Arr[i+8];
	         }
	    led_cmd(Page+1);
	    led_cmd(low);
        led_cmd(high);
        HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,sizeof(temp),HAL_MAX_DELAY);
	}else{             //如果为汉字
	    for(i=0;i<16;i++){
	    	temp[i+1]=Arr[i];
	    }
	    led_cmd(Page);
	    led_cmd(low);
		led_cmd(high);
		HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,sizeof(temp),HAL_MAX_DELAY);
		for(i=0;i<16;i++){
		    temp[i+1]=Arr[i+16];
		    }
		led_cmd(Page+1);
		led_cmd(low);
	    led_cmd(high);
	    HAL_I2C_Master_Transmit(&hi2c1,oledAddress,temp,sizeof(temp),HAL_MAX_DELAY);
	}
}

void oled_show_zero(uint8_t Page,uint8_t Row){//显示0
	uint8_t unmber_zero[]={0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00/*"0",0*/};
	Oled_Show_Word(Page,Row,unmber_zero,1);
}

void oled_show_one(uint8_t Page,uint8_t Row){//显示1
	uint8_t unmber_one[]={0x00,0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00/*"1",0*/
};
	Oled_Show_Word(Page,Row,unmber_one,1);
}

void oled_show_two(uint8_t Page,uint8_t Row){//显示2
	uint8_t unmber_two[]={0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00/*"2",0*/};
	Oled_Show_Word(Page,Row,unmber_two,1);
}

void oled_show_three(uint8_t Page,uint8_t Row){//显示3
	uint8_t unmber_three[]={0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00/*"3",0*/};
	Oled_Show_Word(Page,Row,unmber_three,1);
}

void oled_show_four(uint8_t Page,uint8_t Row){//显示4
	uint8_t unmber_four[]={0x00,0x00,0x80,0x40,0x30,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x24/*"4",0*/};
	Oled_Show_Word(Page,Row,unmber_four,1);
}

void oled_show_five(uint8_t Page,uint8_t Row){//显示5
	uint8_t unmber_five[]={0x00,0xF8,0x88,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x20,0x20,0x20,0x11,0x0E,0x00/*"5",0*/};
	Oled_Show_Word(Page,Row,unmber_five,1);
}

void oled_show_six(uint8_t Page,uint8_t Row){//显示6
	uint8_t unmber_six[]={0x00,0xE0,0x10,0x88,0x88,0x90,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x20,0x1F,0x00/*"6",0*/};
	Oled_Show_Word(Page,Row,unmber_six,1);
}

void oled_show_seven(uint8_t Page,uint8_t Row){//显示7
	uint8_t unmber_seven[]={0x00,0x18,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00/*"7",0*/};
	Oled_Show_Word(Page,Row,unmber_seven,1);
}

void oled_show_eight(uint8_t Page,uint8_t Row){//显示8
	uint8_t unmber_eight[]={0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00/*"8",0*/};
	Oled_Show_Word(Page,Row,unmber_eight,1);
}

void oled_show_nine(uint8_t Page,uint8_t Row){//显示9
	uint8_t unmber_nine[]={0x00,0xF0,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x01,0x12,0x22,0x22,0x11,0x0F,0x00/*"9",0*/};
	Oled_Show_Word(Page,Row,unmber_nine,1);
}

void oled_show_Dot(uint8_t Page,uint8_t Row){//显示小数点
	uint8_t Dot[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00/*".",0*/};
	Oled_Show_Word(Page,Row,Dot,1);
}

void oled_show_minus(uint8_t Page,uint8_t Row){//显示负号
	uint8_t minus[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00/*"-",0*/};
	Oled_Show_Word(Page,Row,minus,1);
}

void oled_show_Spa(uint8_t Page,uint8_t Row){//显示空格
	uint8_t Spa[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00/*" ",0*/};
	Oled_Show_Word(Page,Row,Spa,1);
}

void oled_show_Col(uint8_t Page,uint8_t Row){//显示冒号
	uint8_t Col[]={0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,/*":",0*/};
	Oled_Show_Word(Page,Row,Col,1);
}


void show_unmber(uint8_t page ,uint8_t row,uint8_t unmber){//显示任意一个数字
    if(unmber>=10) return;
	if(unmber==0)oled_show_zero(page,row);
	if(unmber==1)oled_show_one(page,row);
	if(unmber==2)oled_show_two(page,row);
	if(unmber==3)oled_show_three(page,row);
	if(unmber==4)oled_show_four(page,row);
	if(unmber==5)oled_show_five(page,row);
	if(unmber==6)oled_show_six(page,row);
	if(unmber==7)oled_show_seven(page,row);
	if(unmber==8)oled_show_eight(page,row);
	if(unmber==9)oled_show_nine(page,row);
}

void show_3unmber(uint8_t page ,uint8_t row,int unmber){//显示任意一个数字
    int 百位,十位,个位;
    百位=unmber/100;
    十位=unmber/10%10;
    个位=unmber%10;
    show_unmber(page,row,百位);
    show_unmber(page,row+8,十位);
    show_unmber(page,row+16,个位);
}



void show_min_number(uint8_t page ,uint8_t row,int unmber){
	  unmber=abs(unmber);
	  int 个位,十位,小数位;
	  小数位=unmber%10;
	  个位=unmber/10%10;
	  十位=unmber/100;
	  if(十位){
		  show_unmber(page,row,十位);
		  show_unmber(page,row+8,个位);
		  oled_show_Dot(page,row+16);
		  show_unmber(page,row+24,小数位);
	  	  }else{
	  		show_unmber(page,row,个位);
	  		oled_show_Dot(page,row+8);
	  		show_unmber(page,row+16,小数位);
	  		oled_show_Spa(page,row+24);
	  	  }
}

void show_2_number(uint8_t page ,uint8_t row,int unmber){
	  int 个位,十位;
	  if(unmber>99)return;
	  个位=unmber%10;
	  十位=unmber/10;
	  if(十位){
	     show_unmber(page,row,十位);
	     show_unmber(page,row+8,个位);
	  }else{
		  show_unmber(page,row,个位);
		  oled_show_Spa(page,row+8);
	  }

}

void show_tem(uint8_t page ,uint8_t row,int unmber){
      uint8_t tem[]={0x10,0x60,0x02,0x8C,0x00,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,0x04,0x04,0x7E,0x01,0x40,0x7E,0x42,0x42,0x7E,0x42,0x7E,0x42,0x42,0x7E,0x40,0x00/*"温",0*/};
      uint8_t tem_sym[]={0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00/*"℃",0*/};
      Oled_Show_Word(page,row,tem,0);
      oled_show_Col(page,row+16);
      if(unmber>0){
          show_min_number(page,row+24,unmber);
          Oled_Show_Word(page,row+56,tem_sym,0);
          oled_show_Spa(page,row+72);
      }else if(unmber<0){
          oled_show_minus(page,row+24);
          show_min_number(page,row+32,unmber);
          Oled_Show_Word(page,row+64,tem_sym,0);
      }else{
    	  show_min_number(page,row+32,0);
    	  Oled_Show_Word(page,row+56,tem_sym,0);
    	  oled_show_Spa(page,row+72);
      }


}

void show_tur(uint8_t page ,uint8_t row,int unmber){
      uint8_t tur[]={0x10,0x60,0x02,0x8C,0x00,0xF8,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0xF8,0x00,0x00,0x04,0x04,0x7E,0x01,0x20,0x63,0x21,0x21,0x21,0x3F,0x21,0x21,0x29,0x33,0x60,0x00/*"浊",0*/};
      uint8_t tur_sym[]={0xF0,0x08,0xF0,0x80,0x60,0x18,0x00,0x00,0x00,0x31,0x0C,0x03,0x1E,0x21,0x1E,0x00,/*"%",0*/};
      Oled_Show_Word(page,row,tur,0);
      oled_show_Col(page,row+16);
      show_2_number(page,row+24,unmber);
      Oled_Show_Word(page,row+40,tur_sym,1);
}

void show_ip_conect(){
	clear_olde_Page(6);
	clear_olde_Page(7);
	oled_show(6,0,IP_up,sizeof(IP_up));
	oled_show(7,0,IP_down,sizeof(IP_down));
}

void show_ip_disconect(){
	oled_show(6,0,WIFI_up,sizeof(WIFI_up));
	oled_show(7,0,WIFI_down,sizeof(WIFI_down));
}

void show_Weal(uint8_t page ,uint8_t row,int unmber){
	uint8_t Weal[]={0x10,0x60,0x02,0x8C,0x00,0x0E,0x22,0x12,0x0A,0xC2,0x0A,0x12,0x22,0x0E,0x00,0x00,0x04,0x04,0x7E,0x01,0x20,0x21,0x11,0x09,0x05,0xFF,0x05,0x09,0x11,0x21,0x20,0x00/*"深",0*/};
	uint8_t Weal_sym[]={0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,/*"m",0*/0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F/*"m",1*/
};
	Oled_Show_Word(page,row,Weal,0);
	oled_show_Col(page,row+16);
	show_3unmber(page,row+24,unmber);
	Oled_Show_MultiWord(page,row+48,Weal_sym,1,sizeof(Weal_sym)/sizeof(Weal_sym[0]));

}

void show_Ph(uint8_t page ,uint8_t row,int unmber){
	uint8_t ph[]={0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,/*"P",0*/0x10,0xF0,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20/*"h",1*/};
	Oled_Show_MultiWord(page,row,ph,1,sizeof(ph)/sizeof(ph[0]));
      oled_show_Col(page,row+16);
      show_min_number(page,row+24,unmber);
}










