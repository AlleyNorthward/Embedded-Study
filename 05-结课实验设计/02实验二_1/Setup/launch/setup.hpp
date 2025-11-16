#ifndef _SET_UP_HPP
#define _SET_UP_HPP

#include "static_manager.hpp"

extern volatile bool led_on;
extern volatile uint16_t seconds;

class SetUp{
private:
	LED led0;
    USART usart;
    TIM time;
protected:
    SetUp();
    void Heart_Beat();
    void usart_init();
    void usart_infos();
};
#endif

