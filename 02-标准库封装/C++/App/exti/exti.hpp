#ifndef _EXTI_HPP
#define _EXTI_HPP

#include "system.h"

typedef struct{
    uint32_t RCC_EXTI_MASK;
    uint8_t EXTI_PORT_SOURCE_MASK;
    uint8_t EXTI_PIN_SOURCE_MASK;
    uint8_t LINE;
    NVIC_InitTypeDef NVIC_STRUCTURE;
    EXTI_InitTypeDef EXTI_STRUCTURE;
}ExtiMapping_TypeDef;


class ExternalInterrupt{
public:
    void Init_EXTI(ExtiMapping_TypeDef& exti, uint32_t NVIC_PriorityGroup = NVIC_PriorityGroup_2);
};
#endif
