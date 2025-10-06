#include "stm32f10x.h"
#include "led.h"
int main(){
	LED_INIT();
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	GPIO_ResetBits(GPIOE, GPIO_Pin_5);
	while(1){
		
	}
}

