#ifndef _IQR_MANAGER_HPP
#define _IQR_MANAGER_HPP

#include "static_manager.hpp"

class IQRManager{
public:
    static void exti0_handler();
    // static void exti1_handler();
    static void exti2_handler();
    static void exti3_handler();
    static void exti4_handler();
    static void tim4_handler();
    static void usart1_handler();
    static void usart1_dma_handler();
    static void wwdg_handler();
    static void tim5_handler();
};

#endif
