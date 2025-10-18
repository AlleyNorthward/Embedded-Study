#ifndef _CLOCK
#define _CLOCK

#include "stm32f10x.h"
#define DELAY_500MS                             6000000
void RCC_HSE_Config(u32 div, u32 pllm);
void delay(u32 ms);

#endif
