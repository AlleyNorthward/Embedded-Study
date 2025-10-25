#ifndef _BEEP_HPP
#define _BEEP_HPP

#include "system.h"

typedef struct{
    uint32_t BEEP_RCC_MASK;
    GPIO_TypeDef* BEEP_PORT_ADDR;
    uint16_t BEEP_PIN_MASK;
    volatile unsigned long* SET_BEEP;
    u8 CNT;
}BeepMapping_TypeDef;

class BEEP{
private:
    BeepMapping_TypeDef& SingleBeep;
public:
    BEEP(BeepMapping_TypeDef& beep);
    void on(){*SingleBeep.SET_BEEP= 1;};
    void off(){*SingleBeep.SET_BEEP = 0;};
    
    static void on_global(u8 i);
    static void off_global(u8 i);
};


#endif

/*
@author 巷北
@time 2025.10.19 20:41
    还是想用C++来写,这样练习的更多.所以来重新封装一下.
    看了RCC使能函数,一定会重复使用的.想了想,其实就是调整
对应寄存器的位为1,重复使用没有影响.但是不要失能,避免影响
其他器件.

@author 巷北
@time 2025.10.20 16:34
    又修改了一下, .hpp中定义, .cpp中实现.因为补充代码的话,全
放在这里,过于冗杂.

@author 巷北
@time 2025.10.23 21:01
    注释换到下面来了,放在上面看着奇怪.
*/

