#ifndef _CONSTRUCTION_HPP
#define _CONSTRUCTION_HPP

#include "system.h"
#include "systick.h"
#include "led.hpp"
#include "exti.hpp"
#include "key.hpp"
#include "time.hpp"

class PeripheralMapping{
public:
    static LedMapping_TypeDef led0;
    static LedMapping_TypeDef led1;
    static KeyMapping_TypeDef key3;
    static ExtiMapping_TypeDef exti0;
};
#endif
