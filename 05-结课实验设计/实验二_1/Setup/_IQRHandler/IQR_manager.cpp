#include "IQR_manager.hpp"
#include "setup.hpp"

void IQRManager::tim4_handler(){
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

    if(led_on && seconds > 0){
        seconds--;
        if(seconds == 0){
            LED::off_global(0);
            led_on = false;
            TIM_Cmd(TIM4, DISABLE);
        }
    }
}

void IQRManager::usart1_handler(){
    u8 r;
    r = USART_ReceiveData(USART1);
    if(!RX_FINISHED(USART::USART1_RX_STA)){
        if(RX_RECEIVED_CR(USART::USART1_RX_STA)){
            if(r!=LF_ASCII) USART::USART1_RX_STA = 0;
            else USART::USART1_RX_STA |= RX_FINISHED_MASK;
        }
        else{
            if(r == CR_ASCII) USART::USART1_RX_STA |= RX_RECEIVED_CR_MASK;
            else{
                USART::USART1_RX_BUF[USART::USART1_RX_STA & RX_13_LOW_BITS] = r;
                USART::USART1_RX_STA++;
                if(USART::USART1_RX_STA > (USART1_REC_LEN - 1)) USART::USART1_RX_STA = 0;
            }
        }
    }
}
