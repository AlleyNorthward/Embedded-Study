#include "system.h"
#include "systick.h"
#include "time.hpp"
#include "led.hpp"
#include "construction.hpp"
#include "static_manager.hpp"
int main(){
	SysTick_Init(SYSTICK_72MHz);
	LED led0(PeripheralMapping::led0);
	TIM time;
	time.Init_TIM3_CH2_PWM(500, 72-1);
	while(1){
		TIM::Breath_TIM3_PWM(300);
	}
}
