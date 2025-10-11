#include "system.h"
#include "led.h"
#include "clock.h"
#include "systick.h"
#include "beep.h"
#include "key.h"



int main(){
	u8 key = 0;
	u8 i = 0;

	Init_SysTick(SYSTICK_72MHz);
	Init_led();
	Init_BEEP();
	Init_KEY();
	while(1){
		
		key = KEY_Scan(0);
		switch (key){
			case KEY_UP_PRESS: SET_LED1 = LIGHT; break;
			case KEY0_PRESS: BEEP=0; break;
			case KEY1_PRESS: SET_LED1 = DARK; break;
			case KEY2_PRESS: BEEP = 1; break;
		}
		
		i++;
		if (i % 20 == 0) LED0 = !LED0;

		delay_ms(10);
	}
}

