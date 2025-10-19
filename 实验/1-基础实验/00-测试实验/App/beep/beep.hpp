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
    */
private:
    uint16_t BEEP_PIN;
    GPIO_TypeDef* BEEP_PORT;

    void Init_BEEP(
        uint32_t rcc,
        uint16_t pin,
        GPIO_TypeDef* port
    ){  
        this->BEEP_PIN = pin;
        this->BEEP_PORT = port;

        GPIO_InitTypeDef BEEP_Structure;
        BEEP_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
        BEEP_Structure.GPIO_Pin = pin;
        BEEP_Structure.GPIO_Speed = GPIO_Speed_50MHz;

        RCC_APB2PeriphClockCmd(rcc, ENABLE);
        GPIO_Init(port, &BEEP_Structure);
        GPIO_ResetBits(port, pin);
    }

public:
    BEEP(){
        Init_BEEP(
            BEEP_RCC_MASK,
            BEEP_PIN_MASK,
            BEEP_PORT_ADDR
        );
    }

    BEEP(
        uint32_t BEEP_RCC,
        uint16_t BEEP_PIN,
        GPIO_TypeDef* BEEP_PORT
    ){
        Init_BEEP(BEEP_RCC, BEEP_PIN, BEEP_PORT);
    }

    void on(bool IsOwn = true){
        if (IsOwn) SET_BEEP = 1;
        else GPIO_SetBits(BEEP_PORT, BEEP_PIN);
    }

    void off(bool IsOwn = true){
        if (IsOwn) SET_BEEP = 0;
        else GPIO_ResetBits(BEEP_PORT, BEEP_PIN);
    }

};

#endif
