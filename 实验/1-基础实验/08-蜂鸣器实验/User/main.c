#include "system.h"
#include "led.h"
#include "clock.h"
#include "systick.h"
#include "beep.h"



int main(){
	Init_SysTick(SYSTICK_72MHz);
	Init_led();
	Init_BEEP();

	while(1){

		LED1 = !LED1;
		BEEP = !BEEP;
		delay_ms(500);
	}
}

