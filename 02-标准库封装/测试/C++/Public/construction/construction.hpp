#ifndef _CONSTRUCTION_HPP
#define _CONSTRUCTION_HPP

#include "system.h"
#include "systick.h"
#include "led.hpp"
#include "key.hpp"
#include "static_manager.hpp"


class PeripheralMapping{
public:

    // led灯
    static LedMapping_TypeDef led0;
    static LedMapping_TypeDef led1;

    // 按键key
    static KeyMapping_TypeDef key0;
    static KeyMapping_TypeDef key1;
    static KeyMapping_TypeDef key2;
    static KeyMapping_TypeDef key3;

};
#endif
