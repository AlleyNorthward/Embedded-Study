#ifndef _CONSTRUCTION_HPP
#define _CONSTRUCTION_HPP

#include "system.h"
#include "systick.h"
#include "led.hpp"
#include "time.hpp"
#include "adc.hpp"

class PeripheralMapping{
public:
    static LedMapping_TypeDef led0;
    static LedMapping_TypeDef led1;
};
#endif
