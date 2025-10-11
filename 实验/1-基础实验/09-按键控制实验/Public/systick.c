#include "systick.h"

static u8 fac_us = 0;
static u16 fac_ms = 0;

void Init_SysTick(u8 SYSCLK){
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

    fac_us = SYSCLK / 8;
    fac_ms = (u16)fac_us * 1000;
}

void delay_us(u32 nus){

    u32 count;

    SysTick -> LOAD = nus * fac_us;
    SysTick -> VAL = 0x00;
    SysTick -> CTRL |= 1;

    do{
       count = SysTick -> CTRL;
    }while((count & 0x01) && !(count &(1 << 16)));

    SysTick -> CTRL &= ~0x01; //0000 0001
    SysTick -> VAL = 0x00;
}

void delay_ms(u16 nms){

    u32 count;

    SysTick -> LOAD = nms * fac_ms;
    SysTick -> VAL = 0x00;
    SysTick -> CTRL |= 1;

    do{
        count = SysTick -> CTRL;
    
    }while((count & 0x01) && !(count &(1 << 16)));

    SysTick -> CTRL &= ~0x01; //0000 0001
    SysTick -> VAL = 0x00;

}
