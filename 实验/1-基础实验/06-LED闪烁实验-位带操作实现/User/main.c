#include "system.h"
#include "led.h"
#include "clock.h"

int main(){
	Init_led();
	while(1){
		SET_LED0 = LIGHT;
		delay(DELAY_500MS);
		SET_LED0 = DARK;
		delay(DELAY_500MS);
	}
}

