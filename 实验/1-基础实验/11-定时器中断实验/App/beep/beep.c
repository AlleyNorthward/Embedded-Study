#include "beep.h"
static u8 IsInitBeep = 0;
u8 IS_INIT_BEEP(void){return IsInitBeep;}
void Set_IsInitBeep(void){IsInitBeep = 1;}

void BEEP_Init(void){
    GPIO_InitTypeDef GPIO_BEEP_Init;

    GPIO_BEEP_Init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_BEEP_Init.GPIO_Pin = BEEP_PIN_MASK;
    GPIO_BEEP_Init.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(BEEP_RCC_MASK, ENABLE);
    GPIO_Init(BEEP_PORT_ADDRESS, &GPIO_BEEP_Init);
    GPIO_ResetBits(BEEP_PORT_ADDRESS, BEEP_PIN_MASK);

    Set_IsInitBeep();
}

void Set_BEEP(FunctionalState BEEP_State) {
    if (!IS_INIT_BEEP()) BEEP_Init();
    SET_BEEP = BEEP_State;
}
