#ifndef _BEEP_HPP
#define _BEEP_HPP

#include "system.h"


#define BEEP_RCC_MASK           RCC_APB2Periph_GPIOB
#define BEEP_PIN_MASK           GPIO_Pin_8
#define BEEP_PORT_ADDR          GPIOB

#define SET_BEEP                PBout(8)

class BEEP{
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
    放在这里,过于冗杂.s
    */
private:
    uint16_t BEEP_PIN;
    GPIO_TypeDef* BEEP_PORT;

    void Init_BEEP(uint32_t rcc, uint16_t pin, GPIO_TypeDef* port);
public:
    BEEP();
    BEEP(uint32_t BEEP_RCC, uint16_t BEEP_PIN, GPIO_TypeDef* BEEP_PORT);
    void on(bool IsOwn = true);
    void off(bool IsOwn = true);
};

class BEEPStaticBuilder{
public:
    static BEEP* beep;
    static void on();
    static void off();
};
#endif
