#ifndef _SET_UP_HPP
#define _SET_UP_HPP

#include "static_manager.hpp"

class SetUp{
private:
	LED led0, led1;
    KEY key3;
    TIM time;
    ExternalInterrupt exti;
protected:
    SetUp();
    void experience1_1_init();
    void experience1_1_run();
};
#endif

