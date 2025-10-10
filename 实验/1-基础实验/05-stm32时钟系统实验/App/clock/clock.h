#ifndef _CLOCK
#define _CLOCK

#include "stm32f10x.h"
void RCC_HSE_Config(u32 div, u32 pllm);
void delay(u32 ms);
#endif
