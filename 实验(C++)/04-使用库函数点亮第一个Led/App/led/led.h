#ifndef _led_H
#define _led_H

#include "stm32f10x.h"

#define LED1_PORT_RCC		RCC_APB2Periph_GPIOB
#define LED1_PIN			GPIO_Pin_5
#define LED1_PORT			GPIOB

#define LED2_PORT_RCC		RCC_APB2Periph_GPIOE
#define LED2_PIN			GPIO_Pin_5
#define LED2_PORT			GPIOE
void LED_INIT(void);


#endif
