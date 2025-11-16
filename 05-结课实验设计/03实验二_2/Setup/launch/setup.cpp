#include "setup.hpp"

float SetUp::delay_times = 500;
u16 SetUp::count_ = 0;

SetUp::SetUp():led0(PeripheralMapping::led0){}

void SetUp::adc_init(){
    adc.ADCx_Init();
    time.Init_TIM4(71, 999);
    TIM_Cmd(TIM4, ENABLE);
}

void SetUp::adc_run(){
    u16 ADC_value = adc.get_ADC_value(ADC_Channel_1, 20);
    delay_times = (u16)(adc.get_delay_times(ADC_value) + 0.5f);
}
