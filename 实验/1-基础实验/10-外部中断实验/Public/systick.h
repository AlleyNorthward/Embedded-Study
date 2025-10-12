#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "system.h"

#define SYSTICK_72MHz       72

void Init_SysTick(u8 SYSCLK);
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif
