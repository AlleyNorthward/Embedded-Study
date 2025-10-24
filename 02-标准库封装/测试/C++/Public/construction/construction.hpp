#ifndef _CONSTRUCTION_HPP
#define _CONSTRUCTION_HPP

#include "system.h"
#include "beep.hpp"
#include "led.hpp"
#include "key.hpp"


class PeripheralMapping{
public:
    // 蜂鸣器
    static BeepMapping_TypeDef beep0;

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
