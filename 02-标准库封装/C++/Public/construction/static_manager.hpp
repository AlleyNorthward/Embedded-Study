#ifndef _STATIC_MANAGER_HPP
#define _STATIC_MANAGER_HPP

#include "system.h"
#include "led.hpp"
#include "beep.hpp"
#include "key.hpp"


class StaticBuilder{
public:
    static BEEP* beep[];
    static LED* led[2];
    static KEY* key[4];
};

#endif
