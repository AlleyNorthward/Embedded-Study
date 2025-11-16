#include "led.hpp"
#include "static_manager.hpp"

LED::LED(LedMapping_TypeDef& led):SingleLed(led){
    StaticBuilder::led[SingleLed.CNT] = this;
    GPIO_InitTypeDef LED_Structure;

    LED_Structure.GPIO_Speed = GPIO_Speed_50MHz;
    LED_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
    LED_Structure.GPIO_Pin = SingleLed.LED_PIN_MASK;

    RCC_APB2PeriphClockCmd(SingleLed.LED_RCC_MASK, ENABLE);
    GPIO_Init(SingleLed.LED_PORT_ADDR, &LED_Structure);
	*SingleLed.SET_LED = 1;
}

void LED::reinit_led(LedMapping_TypeDef& led){
    GPIO_InitTypeDef LED_Structure;

    LED_Structure.GPIO_Speed = GPIO_Speed_50MHz;
    LED_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
    LED_Structure.GPIO_Pin = SingleLed.LED_PIN_MASK;

    GPIO_Init(SingleLed.LED_PORT_ADDR, &LED_Structure);
    *SingleLed.SET_LED = 1;
}

void LED::on_global(u8 i){
    StaticBuilder::led[i]->on();
}

void LED::off_global(u8 i){
    StaticBuilder::led[i]->off();
}

void LED::Heart_Beat(void){
    static u8 i = 0;
    i++;
    if(i % 20 == 0){*SingleLed.SET_LED = !(*SingleLed.SET_LED);}
    delay_ms(10);
}

void LED::flash_mode(u8 i){
    StaticBuilder::led[i]->on();
    delay_ms(100);
    StaticBuilder::led[i]->off();
    delay_ms(100);
    StaticBuilder::led[i]->on();
    delay_ms(100);
    StaticBuilder::led[i]->off();
    delay_ms(500);
}

void LED::aircraft_navigation_light(){
    StaticBuilder::led[0]->on();
    delay_ms(80);
    StaticBuilder::led[0]->off();
    delay_ms(920);

    StaticBuilder::led[1]->on();
    delay_ms(80);
    StaticBuilder::led[1]->off();
    delay_ms(920);
}
