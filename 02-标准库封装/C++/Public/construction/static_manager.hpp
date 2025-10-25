#ifndef _STATIC_MANAGER_HPP
#define _STATIC_MANAGER_HPP

#include "system.h"
#include "construction.hpp"

class StaticBuilder{
public:
    static BEEP* beep[];
    static LED* led[2];
    static KEY* key[4];
};

#endif
