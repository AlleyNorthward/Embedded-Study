#include "static_manager.hpp"
#include "IQR_manager.hpp"

extern "C" void EXTI0_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line0) == SET){
        IQRManager::exti0_handler();
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
}

extern "C" void TIM4_IRQHandler(void){
    if(TIM_GetITStatus(TIM4, TIM_IT_Update)){ 
        IQRManager::tim4_handler();
    }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
