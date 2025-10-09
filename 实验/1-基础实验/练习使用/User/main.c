#include "stm32f10x.h"
#include "led.h"

int main(){
	Init_led();
	GPIO_ResetBits(LED0_PORT, LED0_GPIO_PIN);
	
	while(1){
		
	}
}

