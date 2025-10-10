#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

#define RCC_LED0                RCC_APB2Periph_GPIOB
#define LED0_PORT               GPIOB
#define LED0_PIN                GPIO_Pin_5

#define RCC_LED1                RCC_APB2Periph_GPIOE
#define LED1_PORT               GPIOE
#define LED1_PIN                GPIO_Pin_5

void Init_led(void);
#endif
