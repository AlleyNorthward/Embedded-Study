#ifndef _EXTI_HPP
#define _EXTI_HPP

#include "system.h"

typedef struct{
    uint32_t RCC_EXTI_MASK;
    uint8_t EXTI_PORT_SOURCE_MASK;
    uint8_t EXTI_PIN_SOURCE_MASK;
    uint8_t LINE;
    NVIC_InitTypeDef NVIC_STRUCTURE;// 这两个是死的.灵活一些, 可以优化减小内存占用.
    EXTI_InitTypeDef EXTI_STRUCTURE;
}ExtiMapping_TypeDef;


class ExternalInterrupt{
public:
    void Init_EXTI(ExtiMapping_TypeDef& exti);
};
#endif
