#include "config.hpp"

LedMapping_TypeDef PeripheralMapping::led0 = {
    RCC_APB2Periph_GPIOB,
    GPIOB,
    GPIO_Pin_5,
    &PBout(5),
    0
};
