#include "IQR_manager.hpp"
#include "setup.hpp"

void IQRManager::exti0_handler(){
    SetUp::key_exti_func();
}

void IQRManager::tim4_handler(){
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    if(seconds > 0){
        seconds--;
        LED::off_global(0);
        delay_ms(50);
        LED::on_global(0);
        if(seconds == 0){
            TIM_Cmd(TIM4, DISABLE);
        }
    }
}
