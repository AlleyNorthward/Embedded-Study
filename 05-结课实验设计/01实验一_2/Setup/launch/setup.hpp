#ifndef _SET_UP_HPP
#define _SET_UP_HPP

#include "static_manager.hpp"

extern volatile bool led_on;
extern volatile uint16_t seconds;

class SetUp{
private:
	LED led0, led1;
    KEY key3;
    TIM time;
    ExternalInterrupt exti;
protected:
    SetUp();
    void experience1_2_init();
    void experience1_2_run();
public:
    static void key_exti_func();
};

#endif

