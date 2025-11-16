#ifndef _SET_UP_HPP
#define _SET_UP_HPP

#include "static_manager.hpp"

class SetUp{
private:
    ADC_ adc;
    LED led0;
    TIM time;
protected:
    SetUp();
    void adc_init();
    void adc_run();
public:
    static float delay_times;
    static u16 count_;
};
#endif

