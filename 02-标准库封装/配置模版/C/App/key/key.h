#ifndef _KEY_H
#define _KEY_H

#include "system.h"

#define KEY_RCC_MASK                                RCC_APB2Periph_GPIOE
#define KEY_UP_RCC_MASK                             RCC_APB2Periph_GPIOA

#define KEY0_PIN_MASK                               GPIO_Pin_4
#define KEY1_PIN_MASK                               GPIO_Pin_3
#define KEY2_PIN_MASK                               GPIO_Pin_2
#define KEY_UP_PIN_MASK                             GPIO_Pin_0

#define KEY_PORT_ADDRESS                            GPIOE
#define KEY0_PORT_ADDRESS                           GPIOE
#define KEY1_PORT_ADDRESS                           GPIOE
#define KEY2_PORT_ADDRESS                           GPIOE
#define KEY_UP_PORT_ADDRESS                         GPIOA

#define CHECK_KEY_UP                                PAin(0)
#define CHECK_KEY0                                  PEin(4)
#define CHECK_KEY1                                  PEin(3)
#define CHECK_KEY2                                  PEin(2)

typedef enum {
    KEY_PRESS_NONE = 0,
    KEY_UP_PRESS,  
    KEY0_PRESS,
    KEY1_PRESS,
    KEY2_PRESS
} KEY_PRESS_TypeDef;

#define KEY_HIGH                                    1
#define KEY_LOW                                     0

typedef enum{KEY_HELD = 1, KEY_SINGLE = !KEY_HELD} KeyMode;
#define IS_KEY_MODE(KEY_MODE)			(((KEY_MODE) == KEY_HELD) || ((KEY_MODE) == KEY_SINGLE))

void KEY_Init(void);
u8 IS_INIT_KEY(void);
KEY_PRESS_TypeDef KEY_Scan(KeyMode mode);

#endif
