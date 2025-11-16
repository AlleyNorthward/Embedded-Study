#include "static_manager.hpp"
#include "usart.hpp"
#include "IQR_manager.hpp"

extern "C" void EXTI0_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line0) == SET){
        IQRManager::exti0_handler();
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
}

extern "C" void EXTI2_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line2) == SET){
        IQRManager::exti2_handler();
    }
    EXTI_ClearITPendingBit(EXTI_Line2);
}

extern "C" void EXTI3_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line3) == SET){
        IQRManager::exti3_handler();
    }
    EXTI_ClearITPendingBit(EXTI_Line3);
}

extern "C" void EXTI4_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line4) == SET){
        IQRManager::exti4_handler();
    }
    EXTI_ClearITPendingBit(EXTI_Line4);
}

extern "C" void TIM4_IRQHandler(void){
    if(TIM_GetITStatus(TIM4, TIM_IT_Update)){ 
        IQRManager::tim4_handler();
    }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

extern "C" void USART1_IRQHandler(void){
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET){
        IQRManager::usart1_dma_handler();
    }
}

extern "C" void WWDG_IRQHandler(void){
    IQRManager::wwdg_handler();
}

extern "C" void TIM5_IRQHandler(void){
    IQRManager::tim5_handler();
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update);
}
