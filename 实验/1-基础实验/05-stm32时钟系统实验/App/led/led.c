#include "stm32f10x.h"
#include "led.h"

void Init_led(void){

    GPIO_InitTypeDef GPIO_Init_LED;
    GPIO_Init_LED.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init_LED.GPIO_Pin = LED0_PIN;
    GPIO_Init_LED.GPIO_Speed = GPIO_Speed_50MHz;
    RCC_APB2PeriphClockCmd(RCC_LED0, ENABLE);
    GPIO_Init(LED0_PORT, & GPIO_Init_LED);
    GPIO_SetBits(LED0_PORT, LED0_PIN);

    GPIO_Init_LED.GPIO_Pin = LED1_PIN;
    RCC_APB2PeriphClockCmd(RCC_LED1, ENABLE);
    GPIO_Init(LED1_PORT,& GPIO_Init_LED);
    GPIO_SetBits(LED1_PORT, LED1_PIN);
}
