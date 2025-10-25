#include "system.h"
#include "systick.h"
#include "led.hpp"
#include "usart.hpp"
#include "construction.hpp"
#include "static_manager.hpp"
int main(){
	SysTick_Init(SYSTICK_72MHz);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART usart1;
	usart1.Init_USART1(115200);
	LED led0(PeripheralMapping::led0);
	while(1){
		usart1.send_data_USART1();
		led0.Heart_Beat();
	}
}
