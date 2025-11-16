#ifndef _SET_UP_HPP
#define _SET_UP_HPP

#include "static_manager.hpp"

class SetUp{
private:
    USART usart;
    TFTLCD_ tftlcd;
    LED led1;
protected:
    SetUp();
    void tft_lcd_init();
    void tft_lcd_run();
};
#endif

/*
    @author 巷北
    @time 2025.10.27 8:41
        想了想还是不传参, 不论如何都需要自己配置,那配置的时候直接指定参数即可.
    毕竟这是应用层,传参还显得很杂乱.
*/
