#pragma once
#include "stm32f10x.h"

class LED{
private:
    uint32_t RCC_PORT;
    uint16_t PIN;
    GPIO_TypeDef* PORT;
public:
    LED(
        uint32_t _RCC_PORT,
        uint16_t _PIN,
        GPIO_TypeDef* _PORT
    ):RCC_PORT(_RCC_PORT), PIN(_PIN), PORT(_PORT){
        RCC_APB2PeriphClockCmd(RCC_PORT, ENABLE);
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_Init(PORT, &GPIO_InitStructure);

        GPIO_SetBits(PORT, PIN);
    }
    void on(){
        GPIO_ResetBits(PORT, PIN);
    }
    void off(){
        GPIO_SetBits(PORT, PIN);
    }
};
