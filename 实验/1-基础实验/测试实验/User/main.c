#include "system.h"
#include "utils.h"
#include "led.h"
#include "systick.h"
#include "beep.h"
#include "key.h"

int main(){	
	KEY_PRESS_TypeDef key;

	SysTick_Init(SYSTICK_72MHz);
	LED_Init();
	BEEP_Init();
	KEY_Init();

	while(1){
		key = KEY_Scan(KEY_SINGLE);
		switch (key){
			case KEY_UP_PRESS: Set_LED(LED1, LIGHT); break;
			case KEY0_PRESS: Set_BEEP(ENABLE); break;
			case KEY1_PRESS: Set_LED(LED1, DARK); break;
			case KEY2_PRESS: Set_BEEP(DISABLE); break;
		}
		Heartbeat_LED();
	}
}


