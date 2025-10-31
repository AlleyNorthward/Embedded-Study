#ifndef _INPUT_HPP
#define _INPUT_HPP

#include "system.h"

typedef u16 TIM5_Typedef;
class Input_{
public:
    static u8 TIM5_CH1_CAPTURE_STA;
    static u16 TIM5_CH1_CAPTURE_VAL;
    Input_(){};
    Input_(TIM5_Typedef per, TIM5_Typedef psc);
};

#endif
