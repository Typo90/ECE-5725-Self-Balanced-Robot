#include"oled.h"
#include "ssd1331.h"

void oled_init()
{
	bcm2835_gpio_fsel(DC , BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RST, BCM2835_GPIO_FSEL_OUTP);
	
	SSD1331_begin();
	
}
void oled_clear()
{
	SSD1331_clear();
}

void oled_display()
{
	char str[12];
	SSD1331_clear();
		//=============第一行显示小车模式=======================//	
	if(Way_Angle==1)	
		SSD1331_string(0,0,"DMP",12,1,RED);
		
	else if(Way_Angle==2)	
		SSD1331_string(0,0,"Kalman",12,1,RED);
	else if(Way_Angle==3)	
		SSD1331_string(0,0,"Hubu",12,1,RED);
			   
	if(Bi_zhang==1)	
	   SSD1331_string(60,0,"Bizhang",12,1,BLUE);
	else             
		SSD1331_string(60,0,"Putong",12,1,BLUE);
	
//=============第二行显示温度和距离===============//	
	sprintf(str,"%.1f`C",(float)Temperature/10);
	SSD1331_string(0,12,str,12,1,RED);
	sprintf(str,"%5.1fcm",Distance);
	SSD1331_string(54,12,str,12,1,RED);
//=============第三行显示编码器=======================//	
	sprintf(str,"|L|=%d",Encoder_Left);
	SSD1331_string(0,24,str,12,1,YELLOW);
	sprintf(str,"%3d=|R|",Encoder_Right);
	SSD1331_string(54,24,str,12,1,YELLOW);
//=============第四行显示    =======================//		
	sprintf(str,"reserve");
	SSD1331_string(0,36,str,12,1,GREEN);
//=============第五行显示角度=======================//
	sprintf(str,"ROLL %.1f",Angle_Balance);
	SSD1331_string(0,48,str,12,1,PURPLE);
//=============刷新=======================//
	SSD1331_display();
	
}

