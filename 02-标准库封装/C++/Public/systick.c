#include "systick.h"
u8 static IsInitSystick = 0;
u8 IS_Init_Systick(void){return IsInitSystick;}
void Set_IsInitSystick(void){IsInitSystick = 1;}

/*
    @author 巷北
    @time 2025.10.14 15:43
        这些东西,现在还不理解,没有太大关系.等后续基础知识掌握后,再来理解也不迟.
*/

static u8 fac_us = 0;
static u16 fac_ms = 0;

void SysTick_Init(u8 SYSCLK){
    IsInitSystick = 1;
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

    fac_us = SYSCLK / 8;
    fac_ms = (u16)fac_us * 1000;
}

void delay_us(u32 nus){
    if (!IsInitSystick){SysTick_Init(SYSTICK_72MHz); Set_IsInitSystick();}

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
    if (!IsInitSystick){SysTick_Init(SYSTICK_72MHz); Set_IsInitSystick();}

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
