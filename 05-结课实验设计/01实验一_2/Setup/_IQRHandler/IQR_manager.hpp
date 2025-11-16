#ifndef _IQR_MANAGER_HPP
#define _IQR_MANAGER_HPP

#include "static_manager.hpp"

class IQRManager{
public:
    static void exti0_handler();
    static void tim4_handler();
};

#endif
