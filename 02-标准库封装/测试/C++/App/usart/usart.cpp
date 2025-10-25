#include "usart.hpp"

u8 USART::USART1_RX_BUF[200];
u16 USART::USART1_RX_STA = 0;  

void USART::Init_USART1(u32 baud_rate){
    USART1_RX_STA = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baud_rate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART::send_data_USART1(){
    u16 t = 0;
    u16 len = 0;
    if(USART1_RX_STA&0x8000){
        len = USART1_RX_STA&0x3fff;
        for(t = 0; t < len; t++){
            USART_SendData(USART1, USART1_RX_BUF[t]);
            while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
        }
        USART1_RX_STA = 0;
    }
}

extern "C" void USART1_IRQHandler(void){
    u8 r;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
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
}
