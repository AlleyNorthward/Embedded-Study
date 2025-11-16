#include "launch.hpp"
#include "systick.h"

void App::init(){
    SysTick_Init(SYSTICK_72MHz);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    this->tft_lcd_init();
}

void App::run(){
    this->tft_lcd_run();
}
