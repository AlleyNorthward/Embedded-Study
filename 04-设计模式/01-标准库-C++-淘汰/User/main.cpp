#include "system.h"
#include "systick.h"
#include "led.hpp"
#include "usart.hpp"
#include "construction.hpp"
#include "static_manager.hpp"
#include "iwdg.hpp"

int main(){
	SysTick_Init(SYSTICK_72MHz);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED led0(PeripheralMapping::led0), led1(PeripheralMapping::led1);
	USART usart;
	usart.Init_USART1(115200);

	KEY key3(PeripheralMapping::key3);
	IWDG_ iwdg(4, 800);

	led1.on();
	printf("Reset System\r\n");

	while(1){
		key3.on(KEY_SINGLE, IWDG_::feed_back);
		led0.Heart_Beat();
	}
}
