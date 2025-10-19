#include "system.h"
#include "systick.h"
#include "led.hpp"
int main(){	

    LED led0(LED0);
    LED led1(LED1);
	SysTick_Init(SYSTICK_72MHz);

	while(1){
        led0.off();
        led1.on();
        delay_ms(500);
        led0.on();
        led1.off();
        delay_ms(500);
	}
}


