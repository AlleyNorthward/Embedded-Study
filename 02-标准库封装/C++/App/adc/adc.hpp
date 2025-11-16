#ifndef _ABC_HPP
#define _ABC_HPP

#include "system.h"

class ADC_{
public:
    void ADCx_Init();
    u16 get_ADC_value(u8 ch, u8 times);
    float get_delay_times(u16 ADC_value);
    float get_ADC_voltage_value(u16 ADC_value);
};

#endif
