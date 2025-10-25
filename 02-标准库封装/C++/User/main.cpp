#include "system.h"
#include "construction.hpp"
#include "time.hpp"
int main(){	 

	SysTick_Init(SYSTICK_72MHz);
	LED led0(PeripheralMapping::led0), led1(PeripheralMapping::led1);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM time;
	time.Init_TIM4(1000, 36000 - 1);
	
	while(1){
		led1.Heart_Beat();
	}
}
