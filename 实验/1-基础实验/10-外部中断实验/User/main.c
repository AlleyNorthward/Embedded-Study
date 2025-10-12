#include "system.h"
#include "led.h"
#include "systick.h"
#include "beep.h"
#include "key.h"
#include "exti.h"


int main(){
	u8 i = 0;

	Init_SysTick(SYSTICK_72MHz);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	Init_led();
	Init_BEEP();
	Init_KEY();
	Init_EXTI();

	while(1){
		i++;
		if (i % 20 == 0) LED0 = !LED0;

		delay_ms(10);
	}
}

