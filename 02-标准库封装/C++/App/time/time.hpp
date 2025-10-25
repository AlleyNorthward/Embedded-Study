#ifndef _TIM_HPP
#define _TIM_HPP

#include "system.h"

typedef u16 TIM3_TypeDef;
typedef u16 TIM4_TypeDef;

class TIM{
public:
    void Init_TIM4(TIM4_TypeDef per, TIM4_TypeDef psc);
    void Init_TIM3_CH2_PWM(TIM3_TypeDef per, TIM3_TypeDef psc);
    static void Breath_TIM3_PWM(TIM3_TypeDef per);
};

#endif

/*
    @author 巷北
    @time 2025.10.25
        这里目前还没有通用性.仍在思考,呼吸灯模式设计放到LED中呢,还是放到这里呢?
*/
