#include "config.hpp"

LedMapping_TypeDef PeripheralMapping::led0 = {
    RCC_APB2Periph_GPIOB,
    GPIOB,
    GPIO_Pin_5,
    &PBout(5),
    0
};

LedMapping_TypeDef PeripheralMapping::led1 = {
    RCC_APB2Periph_GPIOE,
    GPIOE,
    GPIO_Pin_5,
    &PEout(5),
    1
};

KeyMapping_TypeDef PeripheralMapping::key3 = {
    RCC_APB2Periph_GPIOA,
    GPIOA,
    GPIO_Pin_0,
    &PAin(0),
    HIGH_LEVEL,
    3
};

ExtiMapping_TypeDef PeripheralMapping::exti0 = {
    RCC_APB2Periph_AFIO,
    GPIO_PortSourceGPIOA,
    GPIO_PinSource0,
    0,
    {
        EXTI0_IRQn,
        2,
        3,
        ENABLE
    },
    {
        EXTI_Line0,
        EXTI_Mode_Interrupt,
        EXTI_Trigger_Rising,
        ENABLE
    }
};

