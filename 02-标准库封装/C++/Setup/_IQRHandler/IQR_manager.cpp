#include "IQR_manager.hpp"

void IQRManager::exti0_handler(){
    StaticBuilder::key[3]->exti_on(LED::on_global, 0);
}

// void IQRManager::exti1_handler(){}

void IQRManager::exti2_handler(){
    StaticBuilder::key[2]->exti_on(BEEP::on_global, 0);
}

void IQRManager::exti3_handler(){
    StaticBuilder::key[1]->exti_on(BEEP::off_global, 0);
}

void IQRManager::exti4_handler(){
    StaticBuilder::key[0]->exti_on(LED::off_global, 0);
}

void IQRManager::tim4_handler(){
    StaticBuilder::led[0]->reverse();    
}

void IQRManager::usart1_handler(){
    u8 r;
    r = USART_ReceiveData(USART1);
    if((USART::USART1_RX_STA&0x8000) == 0){
        if(USART::USART1_RX_STA&0x4000){
            if(r!=0x0a) USART::USART1_RX_STA = 0;
            else USART::USART1_RX_STA |= 0x8000;
        }
        else{
            if(r == 0x0d) USART::USART1_RX_STA |= 0x4000;
            else{
                USART::USART1_RX_BUF[USART::USART1_RX_STA&0x3FFF] = r;
                USART::USART1_RX_STA++;
                if(USART::USART1_RX_STA > (USART1_REC_LEN - 1)) USART::USART1_RX_STA = 0;
            }
        }
    }
}

void IQRManager::wwdg_handler(){
    WWDG_SetCounter(0x7f);
    WWDG_ClearFlag();
    StaticBuilder::led[1]->reverse();
}