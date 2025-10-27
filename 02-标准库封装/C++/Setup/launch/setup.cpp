#include "setup.hpp"

void SetUp::feed_back_iwdg(){
    StaticBuilder::wdg->IWDG_FeedDog();
    LED::off_global(1);
    printf("Feed Dog\r\n");
}

SetUp::SetUp():
led0(PeripheralMapping::led0),
led1(PeripheralMapping::led1),
key0(PeripheralMapping::key0),
key1(PeripheralMapping::key1),
key2(PeripheralMapping::key2),
key3(PeripheralMapping::key3),
beep(PeripheralMapping::beep0){}

void SetUp::Heart_Beat(){
    StaticBuilder::led[1]->Heart_Beat();
}

void SetUp::key_control(){
    key0.on(KEY_SINGLE, LED::on_global, 0);
    key1.on(KEY_SINGLE, LED::off_global, 0);
    key2.on(KEY_SINGLE, BEEP::on_global, 0);
    key3.on(KEY_SINGLE, BEEP::off_global, 0);
}

void SetUp::iwdg_init(){
    usart.Init_USART1(115200);
    led1.off();
    printf("Reset System\r\n");
}

void SetUp::key_control_iwdg(){
    key3.on(KEY_SINGLE, SetUp::feed_back_iwdg);
}

void SetUp::printf_init(){
    data_printf = 1234;
    fdata_printf = 12.34;
    printf_i = 0;
    usart.Init_USART1(115200);
}

void SetUp::printf_infos(){
    printf_i ++;

    if(printf_i % 50 == 0){
        led0.reverse();

        printf("Integer::data = %d\r\n", data_printf);
        printf("Float::fdata = %.2f\r\n",fdata_printf);
        printf("OX::data = %x\r\n", data_printf);
        printf("O::data = %o\r\n", data_printf);
    }
    delay_ms(10);
}

void SetUp::usart_init(){
    usart.Init_USART1(115200);
}

void SetUp::usart_infos(){
    usart.send_data_USART1();
}

void SetUp::breath_init_PWM(){
    time.Init_TIM3_CH2_PWM(500, 72 - 1);
}

void SetUp::breath_infos_PWM(){
    TIM::Breath_TIM3_PWM(300);
}

void SetUp::tim4_exti_init(){
    time.Init_TIM4(1000, 36000 - 1);
}

void SetUp::exti_key_control_init(){
    exti0.Init_EXTI(PeripheralMapping::exti0);
    exti2.Init_EXTI(PeripheralMapping::exti2);
    exti3.Init_EXTI(PeripheralMapping::exti3);
    exti4.Init_EXTI(PeripheralMapping::exti4);
}

void SetUp::wwdg_init(){
    usart.Init_USART1(115200);

    led0.on();
    delay_ms(500);
    wdg.WWDG_Init();
}