#include "beep.hpp"
#include "construction.hpp"

void BEEP::Init_BEEP(uint32_t rcc, uint16_t pin, GPIO_TypeDef* port, volatile unsigned long PX){
    GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(rcc, ENABLE);

	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(port, &GPIO_InitStructure);
	
	// GPIO_ResetBits(port, pin);
    PX = 0;
}
BEEP::BEEP(){
    BeepMapping_TypeDef& beep = getBeepMapping();
    Init_BEEP(beep.BEEP_RCC_MASK, beep.BEEP_PIN_MASK, beep.BEEP_PORT_ADDR, *beep.SET_BEEP);
}


void BEEP::on(){
    BeepMapping_TypeDef& beep = getBeepMapping();
    *beep.SET_BEEP= 1;
}

void BEEP::off(){
    BeepMapping_TypeDef& beep = getBeepMapping();
    *beep.SET_BEEP = 0;
}




