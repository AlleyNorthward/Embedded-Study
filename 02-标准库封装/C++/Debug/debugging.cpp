#include "debugging.hpp"
#include "systick.h"

void Debug::init(){
    SysTick_Init(SYSTICK_72MHz);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    this->usart_init();
}

void Debug::run(){
    this->usart_infos();
    this->Heart_Beat();
}
