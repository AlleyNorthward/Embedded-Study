#include "system.h"
#include "utils.h"
#include "systick.h"
#include "time.h"

int main(){	

	SysTick_Init(SYSTICK_72MHz);

	TIM4_Init(1000, 36000 - 1);
	while(1){
		Heartbeat_LED();
	}
}


