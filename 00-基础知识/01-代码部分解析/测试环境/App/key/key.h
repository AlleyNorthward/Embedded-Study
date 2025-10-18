#ifndef _KEY_H
#define _KEY_H

#include "system.h"

#define RCC_KEY                         RCC_APB2Periph_GPIOE
#define RCC_KEY_UP                      RCC_APB2Periph_GPIOA

#define KEY0_PIN                        GPIO_Pin_4
#define KEY1_PIN                        GPIO_Pin_3
#define KEY2_PIN                        GPIO_Pin_2
#define KEY_UP_PIN                      GPIO_Pin_0

#define KEY_PORT                        GPIOE
#define KEY0_PORT                       GPIOE
#define KEY1_PORT                       GPIOE
#define KEY2_PORT                       GPIOE
#define KEY_UP_PORT                     GPIOA

#define KEY_UP                          PAin(0)
#define KEY0                            PEin(4)
#define KEY1                            PEin(3)
#define KEY2                            PEin(2)

#define KEY_UP_PRESS                    1
#define KEY0_PRESS                      2
#define KEY1_PRESS                      3
#define KEY2_PRESS                      4

u8 KEY_Scan(u8 mode);
void Init_KEY(void);

#endif
