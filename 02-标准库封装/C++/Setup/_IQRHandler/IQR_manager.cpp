#include "IQR_manager.hpp"
#include "input.hpp"
#include "setup.hpp"

void IQRManager::exti0_handler(){}

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

void IQRManager::tim4_handler(){}

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

void IQRManager::usart1_dma_handler(){
    volatile uint32_t tmp;
    tmp = USART1->SR;
    tmp = USART1->DR;

    DMA_Cmd(DMA1_Channel5, DISABLE);
    u16 len = DMA_REC_LEN - DMA_GetCurrDataCounter(DMA1_Channel5);

    if(len >= 2 && DMA_::DMA_RX_buf[len-2] == 0x0D && DMA_::DMA_RX_buf[len-1] == 0x0A){
            printf("received length: %d.", len - 2);
        }

    DMA_SetCurrDataCounter(DMA1_Channel5, DMA_REC_LEN);
    DMA_Cmd(DMA1_Channel5, ENABLE);
}

void IQRManager::wwdg_handler(){
    WWDG_SetCounter(0x7f);
    WWDG_ClearFlag();
    StaticBuilder::led[1]->reverse();
}

void IQRManager::tim5_handler(){
    if((Input_::TIM5_CH1_CAPTURE_STA & 0x80) == 0){
        if(TIM_GetITStatus(TIM5, TIM_IT_Update)){
            if(Input_::TIM5_CH1_CAPTURE_STA & 0x40){
                if((Input_::TIM5_CH1_CAPTURE_STA & 0x3f) == 0x3f){
                    Input_::TIM5_CH1_CAPTURE_STA |= 0x80;
                    Input_::TIM5_CH1_CAPTURE_VAL = 0xffff;
                }
                else{
                    Input_::TIM5_CH1_CAPTURE_STA++;
                }
            }
        }
        if(TIM_GetITStatus(TIM5, TIM_IT_CC1)){
            if(Input_::TIM5_CH1_CAPTURE_STA & 0x40){
                Input_::TIM5_CH1_CAPTURE_STA |= 0x80;
                Input_::TIM5_CH1_CAPTURE_VAL = TIM_GetCapture1(TIM5);
                TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);
            }
            else{
                Input_::TIM5_CH1_CAPTURE_STA = 0;
                Input_::TIM5_CH1_CAPTURE_VAL = 0;
                Input_::TIM5_CH1_CAPTURE_STA |= 0x40;
                TIM_Cmd(TIM5, DISABLE);
                TIM_SetCounter(TIM5, 0);
                TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);
                TIM_Cmd(TIM5, ENABLE);
            }
        }
    }
}
