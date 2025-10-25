#include "system.h"
#include "beep.hpp"
#include "construction.hpp"
#include "led.hpp"
#include "static_manager.hpp"
#include "exti.hpp"
#include "systick.h"
int main(){	 

    BEEP beep(PeripheralMapping::beep0);
	LED led0(PeripheralMapping::led0), led1(PeripheralMapping::led1);
	KEY key0(PeripheralMapping::key0), key1(PeripheralMapping::key1), key2(PeripheralMapping::key2), key3(PeripheralMapping::key3);
	ExternalInterrupt exti;
	exti.Init_EXTI(PeripheralMapping::exti0);
	exti.Init_EXTI(PeripheralMapping::exti2);
	exti.Init_EXTI(PeripheralMapping::exti3);
	exti.Init_EXTI(PeripheralMapping::exti4);
	
	while(1){
		led1.Heart_Beat();
	}
}
