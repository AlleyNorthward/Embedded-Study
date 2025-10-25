#include "exti.hpp"
void ExternalInterrupt::Init_EXTI(ExtiMapping_TypeDef& exti){
    RCC_APB2PeriphClockCmd(exti.RCC_EXTI_MASK, ENABLE);

    GPIO_EXTILineConfig(exti.EXTI_PORT_SOURCE_MASK, exti.EXTI_PIN_SOURCE_MASK);
    NVIC_Init(&exti.NVIC_STRUCTURE);
    EXTI_Init(&exti.EXTI_STRUCTURE);
}

