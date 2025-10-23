#ifndef _BEEP_H
#define _BEEP_H

#include "system.h"

#define BEEP_RCC_MASK               RCC_APB2Periph_GPIOB
#define BEEP_PIN_MASK               GPIO_Pin_8
#define BEEP_PORT_ADDRESS           GPIOB

#define SET_BEEP                        PBout(8)
void BEEP_Init(void);
u8 IS_INIT_BEEP(void);
void Set_IsInitBeep(void);
void Set_BEEP(FunctionalState State);
#endif
