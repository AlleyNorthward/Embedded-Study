#ifndef _EXTI_H
#define _EXTI_H

#include "system.h"

#define RCC_EXTI_MASK                       RCC_APB2Periph_AFIO

#define EXTI_KEY_UP_SOURCE_PORT_MASK        GPIO_PortSourceGPIOA
#define EXTI_KEY_SOURCE_PORT_MASK           GPIO_PortSourceGPIOE

#define EXTI_KEY_UP_SOURCE_PIN_MASK         GPIO_PinSource0
#define EXTI_KEY0_SOURCE_PIN_MASK           GPIO_PinSource4
#define EXTI_KEY1_SOURCE_PIN_MASK           GPIO_PinSource3
#define EXTI_KEY2_SOURCE_PIN_MASK           GPIO_PinSource2

void EXTI_USING_KEY_Init(void);

#endif
