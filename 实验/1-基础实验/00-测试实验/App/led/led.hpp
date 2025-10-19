#ifndef _LED_HPP
#define _LED_HPP

#include "system.h"

#define LED0_RCC_MASK					RCC_APB2Periph_GPIOB
#define LED0_PORT_ADDR				    GPIOB
#define LED0_PIN_MASK					GPIO_Pin_5

#define LED1_RCC_MASK					RCC_APB2Periph_GPIOE
#define LED1_PORT_ADDR				    GPIOE
#define LED1_PIN_MASK					GPIO_Pin_5

typedef enum{LED0 = 0, LED1 = !LED0} ChoseLed;
#define IS_CHOSED_LED(LED)				(((LED) == LED0) || ((LED) == LED1))

#define SET_LED0                PBout(5)
#define SET_LED1                PEout(5)

class LED{

private: 
    ChoseLed led;
    uint16_t LED_PIN;
    GPIO_TypeDef* LED_PORT;

    void Init_LED(
        uint32_t rcc,
        uint16_t pin,
        GPIO_TypeDef* port
    ){
        this->LED_PIN = pin;
        this->LED_PORT = port;

        GPIO_InitTypeDef LED_Structure;

        LED_Structure.GPIO_Speed = GPIO_Speed_50MHz;
        LED_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
        LED_Structure.GPIO_Pin = pin;

        RCC_APB2PeriphClockCmd(rcc, ENABLE);
        GPIO_Init(port, &LED_Structure);
        GPIO_SetBits(port, pin);
    }

public:
    LED(ChoseLed _led):led(_led){
        assert_param(IS_CHOSED_LED(_led));

        if (_led == LED0){
            Init_LED(
                LED0_RCC_MASK,
                LED0_PIN_MASK,
                LED0_PORT_ADDR
            );
        }
        else{
            Init_LED(
                LED1_RCC_MASK,
                LED1_PIN_MASK,
                LED1_PORT_ADDR
            );
        }
    }

    LED(
        uint32_t LED_RCC,
        uint16_t LED_PIN,
        GPIO_TypeDef* LED_PORT
    ){
        Init_LED(
            LED_RCC,
            LED_PIN,
            LED_PORT
        );
    }

    // 注意, 默认低电平点亮.移至时注意.
    void on(bool IsOwn = true){
        if(IsOwn) {
            if(led == LED0) SET_LED0 = 1;
            else SET_LED1 = 1;
        }
        else GPIO_ResetBits(LED_PORT, LED_PIN);
    }

    void off(bool IsOwn = true){
        if(IsOwn){
            if(led == LED0) SET_LED0 = 0;
            else SET_LED1 = 0;
        }
        else GPIO_SetBits(LED_PORT, LED_PIN);
    }

};

#endif
