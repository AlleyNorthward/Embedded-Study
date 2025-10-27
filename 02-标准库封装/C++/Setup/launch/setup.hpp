#ifndef _SET_UP_HPP
#define _SET_UP_HPP

#include "static_manager.hpp"

class SetUp{
private:
    u16 data_printf;
    float fdata_printf;
    u8 printf_i;

	LED led0, led1;
    KEY key0, key1, key2, key3;
    ExternalInterrupt exti0, exti2, exti3, exti4;
    BEEP beep;
    WDG_ wdg;
    USART usart;
    TIM time;
    static void feed_back_iwdg();
protected:
    SetUp();
    void Heart_Beat();
    void key_control();
    void iwdg_init();
    void key_control_iwdg();
    void printf_init();
    void printf_infos();
    void usart_init();
    void usart_infos();
    void breath_init_PWM();
    void breath_infos_PWM();
    void tim4_exti_init();
    void exti_key_control_init();
    void wwdg_init();
};
#endif

/*
    @author 巷北
    @time 2025.10.27 8:41
        想了想还是不传参, 不论如何都需要自己配置,那配置的时候直接指定参数即可.
    毕竟这是应用层,传参还显得很杂乱.
*/
