#include "stm32f10x.h"
#include "led.h"
void Init_led(void){

	GPIO_InitTypeDef GPIO_LED0_Init_Info;
	GPIO_LED0_Init_Info.GPIO_Pin = LED0_GPIO_PIN;
	GPIO_LED0_Init_Info.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_LED0_Init_Info.GPIO_Mode = LED0_GPIO_MODE;

	RCC_APB2PeriphClockCmd(LED0_RCC_PORT, ENABLE);
	GPIO_Init(LED0_PORT, & GPIO_LED0_Init_Info);
	GPIO_SetBits(LED0_PORT, LED0_GPIO_PIN);
}
