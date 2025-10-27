#include "wdg.hpp"
#include "static_manager.hpp"
#include "stdio.h"

void WDG_::IWDG_Init(IWDG_Prescaler_TypeDef pre, IWDG_ReloadRegister_TypeDef rlr){
    StaticBuilder::wdg = this;
    
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(pre);
    IWDG_SetReload(rlr);
    IWDG_ReloadCounter();
    IWDG_Enable();
}

void WDG_::IWDG_FeedDog(){
    IWDG_ReloadCounter();
}

void WDG_::WWDG_Init(){
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    WWDG_SetWindowValue(0x5f);
    WWDG_SetPrescaler(WWDG_Prescaler_8);

    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
    WWDG_Enable(0x7f);
    WWDG_ClearFlag();
    WWDG_EnableIT();
}