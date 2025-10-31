#ifndef _CONSTRUCTION_HPP
#define _CONSTRUCTION_HPP

#include "system.h"
#include "systick.h"
#include "led.hpp"
#include "time.hpp"
#include "usart.hpp"

class PeripheralMapping{
public:
    static LedMapping_TypeDef led0;
	static LedMapping_TypeDef led1;
};
#endif
