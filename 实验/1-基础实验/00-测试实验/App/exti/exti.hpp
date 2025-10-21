#ifndef _EXTI_HPP
#define _EXTI_HPP

#include "system.h"
#include "key.hpp"
#include "led.hpp"
#include "beep.hpp"

#define RCC_EXTI_MASK                       RCC_APB2Periph_AFIO

#define EXTI_KEY_UP_SOURCE_PORT_MASK        GPIO_PortSourceGPIOA
#define EXTI_KEY_SOURCE_PORT_MASK           GPIO_PortSourceGPIOE

#define EXTI_KEY_UP_SOURCE_PIN_MASK         GPIO_PinSource0
#define EXTI_KEY0_SOURCE_PIN_MASK           GPIO_PinSource4
#define EXTI_KEY1_SOURCE_PIN_MASK           GPIO_PinSource3
#define EXTI_KEY2_SOURCE_PIN_MASK           GPIO_PinSource2

typedef enum{
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,
    EXTI4,
    EXTI5_9,
    EXTI10_15,
}ChoseExti;
#define IS_CHOSED_EXTI(EXTI)                 (((EXTI) == EXTI0) || ((EXTI) == EXTI1) || ((EXTI) == EXTI2) || ((EXTI) == EXTI3) || ((EXTI) == EXTI4) || ((EXTI) == EXTI5_9) || ((EXTI) == (EXTI10_15)))

typedef void (*Callback)();

class ExternalInterrupt{
    /*
    什么设计思想呢?是否需要实例化出来多个exti对象?
    根本没有必要.抽象出来一个exti对象,内部封装多个
    初始化exti方法即可.
    */
private:
    void Config_EXTI(uint8_t EXTI_IRQn, uint8_t sub, uint32_t EXTI_Line, EXTITrigger_TypeDef Trigger);
public:
    void Init_EXTI(ChoseExti _exti, uint32_t NVIC_PriorityGroup = NVIC_PriorityGroup_2);
    void Init_EXTI(uint32_t RCC_EXTI, uint8_t GPIO_PortSource, uint8_t GPIO_PinSource, NVIC_InitTypeDef* NVIC_InitStruct, EXTI_InitTypeDef* EXTI_InitStruct, uint32_t NVIC_PriorityGroup = NVIC_PriorityGroup_2);
};

class EXTIManager{
public:
    static Callback callbacks[5];
    static void attach(uint8_t line, Callback cb);
    static void handle(uint8_t line);
};
#endif
