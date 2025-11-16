#ifndef _CONSTRUCTION_HPP
#define _CONSTRUCTION_HPP

#include "system.h"
#include "systick.h"
#include "exti.hpp"
#include "key.hpp"
#include "led.hpp"
#include "time.hpp" 

class PeripheralMapping{
public:
    static KeyMapping_TypeDef key3;
    static LedMapping_TypeDef led0;
    static LedMapping_TypeDef led1;
    static ExtiMapping_TypeDef exti0;
};
#endif
