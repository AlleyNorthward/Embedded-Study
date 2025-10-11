#include "system.h"
#include "led.h"
#include "clock.h"
#include "systick.h"



int main(){
	Init_SysTick(SYSTICK_72MHz);
	Init_led();
	while(1){
		SET_LED0 = LIGHT;
		delay_ms(500);
		SET_LED0 = DARK;
		delay_ms(500);
	}
}

