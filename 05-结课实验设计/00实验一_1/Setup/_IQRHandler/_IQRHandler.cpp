#include "static_manager.hpp"
#include "IQR_manager.hpp"

extern "C" void EXTI0_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line0) == SET){
        IQRManager::exti0_handler();
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
}
