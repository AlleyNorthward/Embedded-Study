#include "led.hpp"

void LED::Init_LED(uint32_t rcc, uint16_t pin, GPIO_TypeDef* port){
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


LED::LED(ChoseLed _led):led(_led){
    assert_param(IS_CHOSED_LED(_led));

    if (_led == LED0){
        Init_LED(LED0_RCC_MASK, LED0_PIN_MASK, LED0_PORT_ADDR);
    }
    else{
        Init_LED(LED1_RCC_MASK, LED1_PIN_MASK, LED1_PORT_ADDR);
    }
}

LED::LED(uint32_t LED_RCC, uint16_t LED_PIN, GPIO_TypeDef* LED_PORT){
    Init_LED(LED_RCC, LED_PIN, LED_PORT);
}

// 注意, 默认低电平点亮.移植时注意.
void LED::on(bool IsOwn){
    if(IsOwn) {
        if(led == LED0) SET_LED0 = 0;
        else SET_LED1 = 0;
    }
    else GPIO_ResetBits(LED_PORT, LED_PIN);
}

void LED::off(bool IsOwn){
    if(IsOwn){
        if(led == LED0) SET_LED0 = 1;
        else SET_LED1 = 1;
    }
    else GPIO_SetBits(LED_PORT, LED_PIN);
}

void LED::Heart_Beat(void){
    static u8 i = 0;
    i++;
    if(i % 20 == 0){
        if(led == LED0) SET_LED0 = !SET_LED0;
        else SET_LED1 = !SET_LED1;
    }
    delay_ms(10);
}


LED* LEDStaticBuilder::led[2] = {0,0};

void LEDStaticBuilder::led0_on(){
    if(led[0]) led[0]->on();
}

void LEDStaticBuilder::led0_off(){
    if(led[0]) led[0]->off();
}

void LEDStaticBuilder::led1_on(){
    if(led[1]) led[1]->on();
}

void LEDStaticBuilder::led1_off(){
    if(led[1]) led[1]->off();
}

