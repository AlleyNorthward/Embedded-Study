#include "beep.h"

void Init_BEEP(void){
    
    GPIO_InitTypeDef GPIO_Init_BEEP;

    GPIO_Init_BEEP.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init_BEEP.GPIO_Pin = BEEP_PIN;
    GPIO_Init_BEEP.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(RCC_BEEP, ENABLE);
    GPIO_Init(BEEP_PORT, &GPIO_Init_BEEP);

    GPIO_ResetBits(BEEP_PORT, BEEP_PIN);
}
