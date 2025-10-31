#include "static_manager.hpp"
#include "IQR_manager.hpp"

extern "C" void TIM4_IRQHandler(void){
    if(TIM_GetITStatus(TIM4, TIM_IT_Update)){ 
        IQRManager::tim4_handler();
    }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

extern "C" void USART1_IRQHandler(void){
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
        IQRManager::usart1_handler();
    }
}

