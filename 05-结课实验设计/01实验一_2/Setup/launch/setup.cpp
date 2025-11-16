#include "setup.hpp"

volatile bool led_on = false;
volatile u16 seconds = 0;

SetUp::SetUp():
led0(PeripheralMapping::led0),
led1(PeripheralMapping::led1),
key3(PeripheralMapping::key3)
{}

void SetUp::experience1_2_init(){
    time.Init_TIM4(9999, 7199);
    exti.Init_EXTI(PeripheralMapping::exti0);
}

void SetUp::experience1_2_run(){}

void SetUp::key_exti_func(){
    LED::on_global(0);
    seconds = 10;
    TIM_Cmd(TIM4, ENABLE);
}


