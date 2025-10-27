#ifndef _STATIC_MANAGER_HPP
#define _STATIC_MANAGER_HPP

#include "system.h"
#include "config.hpp"

class StaticBuilder{
public:
    static BEEP* beep[];
    static LED* led[2];
    static KEY* key[4];

    static WDG_* wdg;
};

#endif
