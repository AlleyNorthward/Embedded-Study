#ifndef _TFTLCD_HPP
#define _TFTLCD_HPP

#include "system.h"

#define TFTLCD_DIR                      0
#define LCD_LED                         PBout(0)

typedef struct{
    u16 LCD_CMD;
    u16 LCD_DATA; 
}TFTLCD_TypeDef;

#define TFTLCD_BASE                     ((u32)(0x6C000000 | 0x000007FE))
#define TFTLCD                          ((TFTLCD_TypeDef *) TFTLCD_BASE)

typedef struct{
    u16 width;
    u16 height;
    u16 id;
    u8 dir;
}_tftlcd_data;

#define WHITE         	                0xFFFF
#define BLACK         	                0x0000	  
#define BLUE         	                0x001F
#define BRED                            0XF81F
#define GRED 			                0XFFE0
#define GBLUE			                0X07FF
#define RED           	                0xf800
#define MAGENTA       	                0xf81f
#define GREEN         	                0x07e0
#define CYAN          	                0x7FFF
#define YELLOW        	                0xFFE0
#define BROWN 			                0xbc40 //棕色
#define BRRED 			                0xfc07 //棕红色
#define GRAY 			                0X8430 //灰色
#define DARKBLUE      	                0X01CF	//深蓝色
#define LIGHTBLUE      	                0X7D7C	//浅蓝色  
#define GRAYBLUE       	                0X5458 //灰蓝色
#define LIGHTGREEN     	                0X841F //浅绿色
#define LIGHTGRAY                       0XEF5B //浅灰色(PANNEL)
#define LGRAY 			                0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE                       0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE                          0X2B12 //浅棕蓝色(选择条目的反色)

class TFTLCD_{
protected:
    u32 LCD_RGBColor_Change(u16 color);
    u16 LCD_ReadData();
    void TFTLCD_GPIO_Init();
    void TFTLCD_FSMC_Init();
    void LCD_SSD_BackLightSet(u8 pwm);
    u32 LCD_Pow(u8 m, u8 n);
public:
    u16 FRONT_COLOR;
    u16 BACK_COLOR;
    _tftlcd_data tftlcd_data;

    TFTLCD_();

    void LCD_WriteCmd(u16 cmd);
    void LCD_WriteData(u16 data);
    void LCD_WriteCmdData(u16 cmd, u16 data);
    void LCD_WriteData_Color(u16 color);

    void TFTLCD_Init();
    void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);//设置窗口
    void LCD_Display_Dir(u8 dir);//设置屏幕显示方向
    void LCD_Clear(u16 color);//清屏
    void LCD_Fill(u16 xState,u16 yState,u16 xEnd,u16 yEnd,u16 color);//填充单色
    void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);//在指定区域内填充指定颜色块
    void LCD_DrawPoint(u16 x,u16 y);//画点
    void LCD_DrawFRONT_COLOR(u16 x,u16 y,u16 color);//指定颜色画点
    u16 LCD_ReadPoint(u16 x,u16 y);//读点
    void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);//画线
    void LCD_DrawLine_Color(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);//指定颜色画线
    void LCD_DrowSign(uint16_t x, uint16_t y, uint16_t color);//画十字标记
    void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);//画矩形
    void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);//画圆
    void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);//显示一个字符
    void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);//显示一个数字
    void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);//显示数字
    void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);//显示字符串
    void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn);//显示汉字					   						   																			
    void LCD_ShowPicture(u16 x, u16 y, u16 width, u16 height,u8 *pic);//显示图片
};

#endif
