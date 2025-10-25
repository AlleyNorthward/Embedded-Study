#include "exti.hpp"
#include "static_manager.hpp"
void ExternalInterrupt::Init_EXTI(ExtiMapping_TypeDef& exti, uint32_t NVIC_PriorityGroup){
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
    RCC_APB2PeriphClockCmd(exti.RCC_EXTI_MASK, ENABLE);

    GPIO_EXTILineConfig(exti.EXTI_PORT_SOURCE_MASK, exti.EXTI_PIN_SOURCE_MASK);
    NVIC_Init(&exti.NVIC_STRUCTURE);
    EXTI_Init(&exti.EXTI_STRUCTURE);
}

