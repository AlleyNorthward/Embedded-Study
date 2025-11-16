#include "tftlcd.hpp"
#include "usart.hpp"
#include "systick.h"
#include "font.h"
#include "picture.h"

TFTLCD_::TFTLCD_(){
    this->FRONT_COLOR = BLACK;
    this->BACK_COLOR = WHITE;
}

void TFTLCD_::LCD_WriteCmd(u16 cmd){
    TFTLCD->LCD_CMD = cmd;
}

void TFTLCD_::LCD_WriteData(u16 data){
    TFTLCD->LCD_DATA = data;
}

void TFTLCD_::LCD_WriteCmdData(u16 cmd, u16 data){
    TFTLCD->LCD_CMD = cmd;
    TFTLCD->LCD_DATA = data;
}

u32 TFTLCD_::LCD_RGBColor_Change(u16 color){
    u8 r, g, b = 0; 
    r = (color >> 11) & 0x1f;
    g = (color >> 5) & 0x3f;
    b = color & 0x1f;
    return ((r << 13) | (g << 6) | (b << 1));
}

void TFTLCD_::LCD_WriteData_Color(u16 color){
    TFTLCD->LCD_DATA = color;
}

u16 TFTLCD_::LCD_ReadData(){
    return TFTLCD->LCD_DATA;
}

void TFTLCD_::LCD_Display_Dir(u8 dir){
    tftlcd_data.dir = dir;
    if(dir == 0){
        LCD_WriteCmdData(0x36, 0x00);
        tftlcd_data.height = 800;
        tftlcd_data.width = 480;
    }
    else{
        LCD_WriteCmdData(0x36, 0x68);
        tftlcd_data.height = 480;
        tftlcd_data.width = 800;
    }
}

void TFTLCD_::LCD_Set_Window(u16 sx, u16 sy, u16 width, u16 height){
    LCD_WriteCmd(0x2A);
    LCD_WriteData(sx/256);
    LCD_WriteData(sx%256);
    LCD_WriteData(width/256);
    LCD_WriteData(width%256);

    LCD_WriteCmd(0x2B);
    LCD_WriteData(sy/256);
    LCD_WriteData(sy%256);
    LCD_WriteData(height/256);
    LCD_WriteData(height%256);

    LCD_WriteCmd(0x2c);
}

u16 TFTLCD_::LCD_ReadPoint(u16 x, u16 y){
    u16 r = 0, g = 0, b = 0;
    // u16 r1, r2, r3;
    // u32 value;
    if(x >= tftlcd_data.width || y >= tftlcd_data.height) return 0;
    LCD_Set_Window(x, y, x, y);

    LCD_WriteCmd(0x2e);
    r = LCD_ReadData();
    r = LCD_ReadData();
    b = LCD_ReadData();
    g = LCD_ReadData();
    return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));
}

void TFTLCD_::TFTLCD_GPIO_Init(){
    GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		    
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
  	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		    
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);    	    	 											 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	   
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		    
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	LCD_LED=1;				
}

void TFTLCD_::TFTLCD_FSMC_Init(){
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  FSMC_ReadTimingInitStructure; 
	FSMC_NORSRAMTimingInitTypeDef  FSMC_WriteTimingInitStructure;
	
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	
	
	FSMC_ReadTimingInitStructure.FSMC_AddressSetupTime = 0x01;	 
  	FSMC_ReadTimingInitStructure.FSMC_AddressHoldTime = 0x00;	 
  	FSMC_ReadTimingInitStructure.FSMC_DataSetupTime = 0x0f;		 
  	FSMC_ReadTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_CLKDivision = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_DataLatency = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	  

	FSMC_WriteTimingInitStructure.FSMC_AddressSetupTime = 0x15;	   
  	FSMC_WriteTimingInitStructure.FSMC_AddressHoldTime = 0x15;	 	
  	FSMC_WriteTimingInitStructure.FSMC_DataSetupTime = 0x05;		 	
  	FSMC_WriteTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_CLKDivision = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_DataLatency = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	   

 
  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;   
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;   
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; 
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadTimingInitStructure;
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_WriteTimingInitStructure; 

  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  

 	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  
}

void TFTLCD_::LCD_SSD_BackLightSet(u8 pwm){
    LCD_WriteCmd(0xBE);
    LCD_WriteData(0x05);
    LCD_WriteData(pwm * 2.55);
    LCD_WriteData(0x01);
    LCD_WriteData(0xFF);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
}

void TFTLCD_::LCD_Clear(u16 color){
    u16 i, j;
    LCD_Set_Window(0, 0, tftlcd_data.width - 1, tftlcd_data.height - 1);
    for(i = 0; i < tftlcd_data.width; i++){
        for(j = 0; j < tftlcd_data.height; j++){
            LCD_WriteData_Color(color);
        }
    }
}

void TFTLCD_::TFTLCD_Init(){
    // u16 i;
    TFTLCD_GPIO_Init();
    TFTLCD_FSMC_Init();
    delay_ms(50);

    LCD_WriteCmd(0xd3);
    tftlcd_data.id = TFTLCD->LCD_DATA;
    tftlcd_data.id = TFTLCD->LCD_DATA;
    tftlcd_data.id = TFTLCD->LCD_DATA;
    tftlcd_data.id <<= 8;
    tftlcd_data.id |= TFTLCD->LCD_DATA;

    printf(" LCD ID:%x\r\n",tftlcd_data.id); //打印LCD ID

    LCD_WriteCmd(0xFF);
	LCD_WriteData(0xFF);
	LCD_WriteData(0x98);
	LCD_WriteData(0x06);

	LCD_WriteCmd(0xBA);
	LCD_WriteData(0x60);

	LCD_WriteCmd(0xBC);
	LCD_WriteData(0x03);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x03);
	LCD_WriteData(0x63);
	LCD_WriteData(0x01);
	LCD_WriteData(0x01);
	LCD_WriteData(0x1B);
	LCD_WriteData(0x12);
	LCD_WriteData(0x6F);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x01);
	LCD_WriteData(0x03);
	LCD_WriteData(0x02);
	LCD_WriteData(0xFF);
	LCD_WriteData(0xF2);
	LCD_WriteData(0x01);
	LCD_WriteData(0x00);
	LCD_WriteData(0xC0);

	LCD_WriteCmd(0xBD);
	LCD_WriteData(0x02);
	LCD_WriteData(0x13);
	LCD_WriteData(0x45);
	LCD_WriteData(0x67);
	LCD_WriteData(0x45);
	LCD_WriteData(0x67);
	LCD_WriteData(0x01);
	LCD_WriteData(0x23);

	LCD_WriteCmd(0xBE);
	LCD_WriteData(0x01);
	LCD_WriteData(0x22);
	LCD_WriteData(0x22);
	LCD_WriteData(0xDC);
	LCD_WriteData(0xBA);
	LCD_WriteData(0x67);
	LCD_WriteData(0x22);
	LCD_WriteData(0x22);
	LCD_WriteData(0x22);

	LCD_WriteCmd(0xC7);
	LCD_WriteData(0x66);

	LCD_WriteCmd(0xED);
	LCD_WriteData(0x7F);
	LCD_WriteData(0x0F);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0xC0);
	LCD_WriteData(0x03);
	LCD_WriteData(0x0B);
	LCD_WriteData(0x00);
	
	LCD_WriteCmd(0XF5);
	LCD_WriteData(0x20);
	LCD_WriteData(0x43);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0xEE);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x1B);
	LCD_WriteData(0x5F);
	LCD_WriteData(0x40);
	LCD_WriteData(0x28);
	LCD_WriteData(0x38);
	LCD_WriteData(0x02);
	LCD_WriteData(0x2B);
	LCD_WriteData(0x50);
	LCD_WriteData(0x00);
	LCD_WriteData(0x80);

	LCD_WriteCmd(0xFC);
	LCD_WriteData(0x08);

	LCD_WriteCmd(0xDF);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x20);

	LCD_WriteCmd(0xF3);
	LCD_WriteData(0x74);

	LCD_WriteCmd(0xB4);
	LCD_WriteData(0x02);
	LCD_WriteData(0x02);
	LCD_WriteData(0x02);

	LCD_WriteCmd(0xF7);
	LCD_WriteData(0x82);
	
	LCD_WriteCmd(0xB1);
	LCD_WriteData(0x00);
	LCD_WriteData(0x13);
	LCD_WriteData(0x13);

	LCD_WriteCmd(0xF2);
	LCD_WriteData(0x41);
	LCD_WriteData(0x04);
	LCD_WriteData(0x41);
	LCD_WriteData(0x28);

	LCD_WriteCmd(0xC1);
	LCD_WriteData(0x17);
	LCD_WriteData(0x78);
	LCD_WriteData(0x7B);
	LCD_WriteData(0x20);

	LCD_WriteCmd(0xE0);
	LCD_WriteData(0x00);
	LCD_WriteData(0x02);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x0F);
	LCD_WriteData(0x11);
	LCD_WriteData(0x1C);
	LCD_WriteData(0xC8);
	LCD_WriteData(0x07);
	LCD_WriteData(0x03);
	LCD_WriteData(0x08);
	LCD_WriteData(0x03);
	LCD_WriteData(0x0D);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x31);
	LCD_WriteData(0x2C);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0xE1);
	LCD_WriteData(0x00);
	LCD_WriteData(0x02);
	LCD_WriteData(0x08);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x12);
	LCD_WriteData(0x17);
	LCD_WriteData(0x7C);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x03);
	LCD_WriteData(0x09);
	LCD_WriteData(0x06);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x2E);
	LCD_WriteData(0x2A);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0x35);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0x36); 
	LCD_WriteData(0xC0);

	LCD_WriteCmd(0x3A); 
	LCD_WriteData(0x55);

	LCD_WriteCmd(0x11);
	delay_ms(120);

	LCD_WriteCmd(0x29);

    LCD_Display_Dir(TFTLCD_DIR);
    LCD_Clear(WHITE);
}

void TFTLCD_::LCD_Fill(u16 xState,u16 yState,u16 xEnd,u16 yEnd,u16 color){
    u16 temp;
    if((xState > xEnd) || (yState > yEnd)){
        return ;
    }
    LCD_Set_Window(xState, yState, xEnd, yEnd);
    xState = xEnd - xState + 1;
    yState = yEnd - yState + 1;

    while(xState--){
        temp = yState;
        while(temp--){
            LCD_WriteData_Color(color);
        }
    }
}
void TFTLCD_::LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color){
    u16 height, width;
    u16 i, j;
    width = ex - sx + 1;
    height = ey - sy + 1;

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            LCD_Set_Window(sx + j, sy + i, ex, ey);
            LCD_WriteData_Color(color[i * width + j]);
        }
    }
}

void TFTLCD_::LCD_DrawPoint(u16 x, u16 y){
    LCD_Set_Window(x, y, x, y);
    LCD_WriteData_Color(FRONT_COLOR);
}

void TFTLCD_::LCD_DrawFRONT_COLOR(u16 x, u16 y, u16 color){
    LCD_Set_Window(x, y, x, y);
    LCD_WriteData_Color(color);
}

void TFTLCD_::LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2){
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if(delta_x > 0) incx = 1;
    else if(delta_x ==0) incx = 0;
    else {incx = -1; delta_x = -delta_x;}

    if(delta_y > 0)incy = 1;
    else if(delta_y == 0) incy = 0;
    else{incy = -1; delta_y = -delta_y;}

    if(delta_x > delta_y) distance = delta_x;
    else distance = delta_y;

    for(t = 0; t <= distance + 1; t++){
        LCD_DrawPoint(uRow, uCol);
        xerr += delta_x;
        yerr += delta_y;

        if(xerr > distance){
            xerr -= distance;
            uRow += incx;
        }
        if(yerr > distance){
            yerr -= distance;
            uCol += incy;
        }
    }
}

void TFTLCD_::LCD_DrawLine_Color(u16 x1, u16 y1, u16 x2, u16 y2, u16 color){
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    
    if(delta_x > 0)incx = 1;
    else if(delta_x == 0) incx = 0;
    else{incx = -1; delta_x = -delta_x;}

    if(delta_y > 0)incy = 1;
    else if(delta_y == 0)incy = 0;
    else{incy = -1; delta_y = -delta_y;}
    
    if(delta_x > delta_y)distance = delta_x;
    else distance = delta_y;

    for(t = 0; t <= distance + 1; t++){
        LCD_DrawFRONT_COLOR(uRow, uCol, color);
        xerr += delta_x;
        yerr += delta_y;
        if(xerr > distance){
            xerr -= distance;
            uRow = incx;
        }
        if(yerr > distance){
            yerr -= distance;
            uCol += incy;
        }
    }
}

void TFTLCD_::LCD_DrowSign(uint16_t x, uint16_t y, uint16_t color){
    u8 i;
    LCD_Set_Window(x - 1, y - 1, x + 1, y + 1);
    for(i = 0; i < 9; i++) LCD_WriteData_Color(color);

    LCD_Set_Window(x - 4, y, y + 4, y);
    for (i = 0; i < 9; i++) LCD_WriteData_Color(color);

    LCD_Set_Window(x, y - 4, x, y + 4);
    for(i = 0; i < 9; i++) LCD_WriteData_Color(color);
}

void TFTLCD_::LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2){
    LCD_DrawLine(x1, y1, x2, y1);
    LCD_DrawLine(x1, y1, x1, y2);
    LCD_DrawLine(x1, y2, x2, y2);
    LCD_DrawLine(x2, y1, x2, y2);
}

void TFTLCD_::LCD_Draw_Circle(u16 x0, u16 y0, u8 r){
    int a = 0, b = r;
    int di = 3 - (r << 1);
    while(a <= b){
        LCD_DrawPoint(x0 + a, y0 - b);
        LCD_DrawPoint(x0 + b, y0 - a);
        LCD_DrawPoint(x0 + b, y0 + a);
        LCD_DrawPoint(x0 + a, y0 + b);
        LCD_DrawPoint(x0 - a, y0 + b);
        LCD_DrawPoint(x0 - b, y0 + a);
        LCD_DrawPoint(x0 - a, y0 - b);
        LCD_DrawPoint(x0 - b, y0 - a);
        a++;
        if(di < 0) di += 4 * a + 6;
        else{
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

void TFTLCD_::LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u8 mode){
    u8 temp, t1, t;
    u16 y0 = y;
    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);
    num = num - ' ';
    for(t = 0; t < csize; t++){
        if(size == 12) temp = ascii_1206[num][t];
        else if (size == 16) temp = ascii_1608[num][t];
        else if (size == 24) temp = ascii_2412[num][t];
        else return;
        for (t1 = 0; t1 < 8; t1++){
            if(temp & 0x80) LCD_DrawFRONT_COLOR(x, y, FRONT_COLOR);
            else if (mode == 0) LCD_DrawFRONT_COLOR(x, y, BACK_COLOR);
            temp <<= 1;
            y++;
            if(y >= tftlcd_data.height) return;
            if((y - y0) == size){
                y = y0;
                x++;
                if(x >= tftlcd_data.width) return;
                break;
            }
        }
    }
}

u32 TFTLCD_::LCD_Pow(u8 m, u8 n){
    u32 result = 1;
    while(n--) result *= m;
    return result;
}

void TFTLCD_::LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size){
    u8 t, temp;
    u8 enshow = 0;
    for(t = 0; t < len; t++){
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;
        if(enshow == 0 && t < (len - 1)){
            if(temp == 0){
                LCD_ShowChar(x + (size / 2) * t, y, ' ', size, 0);
                continue;
            }
            else enshow = 1;
        }
        LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, 0);
    }
}

void TFTLCD_::LCD_ShowxNum(u16 x, u16 y, u32 num, u8 len, u8 size, u8 mode){
    u8 t, temp;
    u8 enshow = 0;
    for(t = 0; t < len; t++){
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;
        if(enshow == 0 && t < (len - 1)){
            if(temp == 0){
                if(mode & 0x80)LCD_ShowChar(x + (size / 2) * t, y, '0', size, mode & 0x01);
                else LCD_ShowChar(x + (size / 2) * t, y, ' ', size, mode & 0x01);
                continue;
            }
            else enshow = 1;
        }
        LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, mode & 0x01);
    }
}
void TFTLCD_::LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, u8* p){
    u8 x0 = x;
    width += x;
    height += y;
    while((*p <= '~') && (*p >= ' ')){
        if(x >= width){x = x0; y += size;}
        if(y >= height) break;
        LCD_ShowChar(x, y, *p, size, 0);
        x += size / 2;
        p++;
    }
}

void TFTLCD_::LCD_ShowFontHZ(u16 x, u16 y, u8 *cn){
    u8 i, j, wordNum;
    u16 color;
    u16 x0 = x;
    u16 y0 = y;

    while(*cn != '\0'){
        for (wordNum = 0; wordNum < 20; wordNum++){
            if((CnChar32x29[wordNum].Index[0] == *cn) && (CnChar32x29[wordNum].Index[1] == *(cn + 1))){
                for(i = 0; i < 116; i++){
                    color = CnChar32x29[wordNum].Msk[i];
                    for(j = 0; j < 8; j++){
                        if((color & 0x80) == 0x80) LCD_DrawFRONT_COLOR(x, y, FRONT_COLOR);
                        else LCD_DrawFRONT_COLOR(x, y, BACK_COLOR);
                        color <<= 1;
                        x++;
                        
                        if((x - x0) == 32){
                            x = x0;
                            y++;
                            if((y - y0) == 29) y = y0;
                        }
                    }
                }
            }
        }
        cn += 2;
        x += 32;
        x0 = x;
    }
}

void TFTLCD_::LCD_ShowPicture(u16 x, u16 y, u16 width, u16 height, u8* pic){
    u16 i, j;
    u16 temp = 0;
    long tmp = 0;//, num = 0;
    LCD_Set_Window(x, y, x + width - 1, y + height - 1);
    // num = width * height * 2;
    
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            temp = pic[tmp + 1];
            temp = temp << 8;
            temp = temp | pic[tmp];
            LCD_DrawFRONT_COLOR(x + j, y + i, temp);
            tmp += 2;
        }
    }
}
