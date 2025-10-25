#include "static_manager.hpp"

BEEP* StaticBuilder::beep[] = {0};
LED* StaticBuilder::led[2] = {0};
KEY* StaticBuilder::key[4] = {0};


extern "C" void EXTI0_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line0) == SET){
        StaticBuilder::key[3]->exti_on(LED::on_global, 0);
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

extern "C" void EXTI2_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line2) == SET){
        StaticBuilder::key[2]->exti_on(LED::off_global, 0);
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

extern "C" void EXTI3_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line3) == SET){
        StaticBuilder::key[1]->exti_on(BEEP::on_global, 0);
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

extern "C" void EXTI4_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line4) == SET){
        StaticBuilder::key[0]->exti_on(BEEP::off_global, 0);
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

extern "C" void TIM4_IRQHandler(void){
    if(TIM_GetITStatus(TIM4, TIM_IT_Update)){ 
        StaticBuilder::led[0]->reverse();
    }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
