#include "stm32f10x.h"
#include "led.hpp"
int main(){
	LED led1(RCC_APB2Periph_GPIOB, GPIO_Pin_5, GPIOB);
	LED led2(RCC_APB2Periph_GPIOE, GPIO_Pin_5, GPIOE);
	led1.on();
	led2.on();
	while(1){
		
	}
}

