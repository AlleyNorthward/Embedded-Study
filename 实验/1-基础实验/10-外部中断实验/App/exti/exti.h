#ifndef _EXTI_H
#define _EXTI_H

#include "system.h"

#define RCC_EXIT                    RCC_APB2Periph_AFIO

#define EXIT_KEY_UP_PORT            GPIO_PortSourceGPIOA
#define EXIT_KEY_PORT               GPIO_PortSourceGPIOE

#define EXIT_KEY_UP_Pin             GPIO_PinSource0
#define EXIT_KEY0_Pin               GPIO_PinSource2
#define EXIT_KEY1_Pin               GPIO_PinSource3
#define EXIT_KEY2_Pin               GPIO_PinSource4

void Init_EXTI(void);

#endif

