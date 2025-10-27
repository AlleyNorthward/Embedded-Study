#include "launch.hpp"
#include "systick.h"

void App::init(){
    SysTick_Init(SYSTICK_72MHz);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    this->wwdg_init();
}

void App::run(){
    StaticBuilder::led[0]->off();
}
