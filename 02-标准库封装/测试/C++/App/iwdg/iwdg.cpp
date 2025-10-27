#include "iwdg.hpp"
#include "static_manager.hpp"
#include "stdio.h"

IWDG_::IWDG_(IWDG_Prescaler_TypeDef pre, IWDG_ReloadRegister_TypeDef rlr){
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(pre);
    IWDG_SetReload(rlr);
    IWDG_ReloadCounter();
    IWDG_Enable();
}

void IWDG_::IWDG_FeedDog(){
    IWDG_ReloadCounter();
}

void IWDG_::feed_back(){
    IWDG_::IWDG_FeedDog();
    LED::off_global(1);
    printf("Feed Dog\r\n");
}
