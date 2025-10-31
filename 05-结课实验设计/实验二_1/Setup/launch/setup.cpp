#include "setup.hpp"

volatile bool led_on = false;
volatile u16 seconds = 0;

SetUp::SetUp():
led0(PeripheralMapping::led0),
led1(PeripheralMapping::led1)
{}

void SetUp::Heart_Beat(){
    StaticBuilder::led[1]->Heart_Beat();
}

void SetUp::usart_init(){
    usart.Init_USART1(115200);
    time.Init_TIM4(9999, 7199);
}

void SetUp::usart_infos(){
    if(RX_FINISHED(USART::USART1_RX_STA)){
        u16 count = USART::get_RX_BUF();
        if(count > 0){
            seconds = count;
            LED::on_global(0);
            led_on = true;
            TIM_Cmd(TIM4, ENABLE);
        }
    }
}
