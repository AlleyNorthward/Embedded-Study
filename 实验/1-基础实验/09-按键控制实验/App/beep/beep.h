#ifndef _BEEP_H
#define _BEEP_H

#include "system.h"

#define RCC_BEEP                RCC_APB2Periph_GPIOB
#define BEEP_PIN                GPIO_Pin_8
#define BEEP_PORT               GPIOB

#define BEEP                    PBout(8)
void Init_BEEP(void);

#endif
