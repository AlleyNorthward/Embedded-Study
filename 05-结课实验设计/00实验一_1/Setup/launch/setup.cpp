#include "setup.hpp"

SetUp::SetUp():
led0(PeripheralMapping::led0),
led1(PeripheralMapping::led1),
key3(PeripheralMapping::key3)
{}

void SetUp::experience1_1_init(){
    time.Init_TIM3_CH2_PWM(500, 72 - 1);
    exti.Init_EXTI(PeripheralMapping::exti0);
}

void SetUp::experience1_1_run(){
    switch(KEY::mode){
        case 1: 
            TIM::reinit_TIM3_PWM();
            TIM_Cmd(TIM3, ENABLE);
            TIM::Breath_TIM3_PWM(300);
			break;
        case 2: 
            TIM_Cmd(TIM3, DISABLE);
            StaticBuilder::led[0]->reinit_led(PeripheralMapping::led0);
            LED::flash_mode(0);
			break;
        case 3: 
            LED::aircraft_navigation_light();
			break;
		default:
			break;
    }
}

