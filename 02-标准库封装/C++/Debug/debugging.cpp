#include "debugging.hpp"
#include "systick.h"

void Debug::init(){
    SysTick_Init(SYSTICK_72MHz);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    this->debugging_printf();
}

void Debug::run(){}
