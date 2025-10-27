#include "construction.hpp"


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

