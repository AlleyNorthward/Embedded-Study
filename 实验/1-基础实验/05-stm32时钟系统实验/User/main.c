#include "stm32f10x.h"
#include "led.h"
#include "clock.h"g

int main(){
	RCC_HSE_Config(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);
	Init_led();
	while(1){
	GPIO_ResetBits(LED0_PORT, LED0_PIN);
	delay(6000000);
	GPIO_SetBits(LED0_PORT, LED0_PIN);
	delay(6000000);
	}
}

