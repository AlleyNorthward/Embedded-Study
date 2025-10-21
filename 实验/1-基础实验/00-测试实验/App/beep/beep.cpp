#include "beep.hpp"

void BEEP::Init_BEEP(uint32_t rcc, uint16_t pin, GPIO_TypeDef* port){  
    this->BEEP_PIN = pin;
    this->BEEP_PORT = port;

    GPIO_InitTypeDef BEEP_Structure;
    BEEP_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
    BEEP_Structure.GPIO_Pin = pin;
    BEEP_Structure.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(rcc, ENABLE);
    GPIO_Init(port, &BEEP_Structure);
    GPIO_ResetBits(port, pin);
}

BEEP::BEEP(){
    Init_BEEP(BEEP_RCC_MASK, BEEP_PIN_MASK, BEEP_PORT_ADDR);
}

BEEP::BEEP(uint32_t BEEP_RCC, uint16_t BEEP_PIN, GPIO_TypeDef* BEEP_PORT){
    Init_BEEP(BEEP_RCC, BEEP_PIN, BEEP_PORT);
}

void BEEP::on(bool IsOwn){
    if (IsOwn) SET_BEEP = 1;
    else GPIO_SetBits(BEEP_PORT, BEEP_PIN);
}

void BEEP::off(bool IsOwn){
    if (IsOwn) SET_BEEP = 0;
    else GPIO_ResetBits(BEEP_PORT, BEEP_PIN);
}


BEEP* BEEPStaticBuilder::beep = 0;

void BEEPStaticBuilder::on(){
    if(beep) beep->on();
}

void BEEPStaticBuilder::off(){
    if(beep) beep->off();
}

