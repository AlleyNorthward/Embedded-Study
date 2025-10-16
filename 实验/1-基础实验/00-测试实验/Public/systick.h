#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "system.h"

#define SYSTICK_72MHz       72

void SysTick_Init(u8 SYSCLK);
u8 IS_Init_Systick(void);
void Set_IsInitSystick(void);
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif
