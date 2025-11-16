#include "setup.hpp"
#include "picture.h"

SetUp::SetUp():led0(PeripheralMapping::led0){}

void SetUp::testing_picture_init(){
    u16 color = 0;
    usart.Init_USART1(115200);
	USART_Cmd(USART1, ENABLE);
    tftlcd.TFTLCD_Init();
    
    tftlcd.FRONT_COLOR = BLACK;
    tftlcd.LCD_ShowString(10, 10, tftlcd.tftlcd_data.width, tftlcd.tftlcd_data.height, 12, (u8*) "Hello World!");
    tftlcd.LCD_ShowString(10, 30, tftlcd.tftlcd_data.width, tftlcd.tftlcd_data.height, 16, (u8*) "Hello World!");
    tftlcd.LCD_ShowString(10, 50, tftlcd.tftlcd_data.width, tftlcd.tftlcd_data.height, 24, (u8*) "Hello World!");
    tftlcd.LCD_ShowFontHZ(10, 80, (u8*) "∆’÷–ø∆ºº");
    tftlcd.LCD_ShowString(10, 120, tftlcd.tftlcd_data.width, tftlcd.tftlcd_data.height, 24, (u8*) "2417534000@qq.com");

    tftlcd.LCD_Fill(10, 150, 60, 180, GRAY);
    color = tftlcd.LCD_ReadPoint(20, 160);
    tftlcd.LCD_Fill(100, 150, 150, 180, color);
    printf("color = %x\r\n", color);

    tftlcd.LCD_ShowPicture(20, 220, 200, 112, (u8*) gImage_picture);
}

void SetUp::testing_picture_run(){
    led0.Heart_Beat();
}

