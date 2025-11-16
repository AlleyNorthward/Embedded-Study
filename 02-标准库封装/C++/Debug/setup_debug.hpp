#ifndef _SET_UP_DEBUG_HPP
#define _SET_UP_DEBUG_HPP

#include "static_manager.hpp"

class SetUpDebug{
private:
    USART usart;
protected:
    SetUpDebug();
    void debugging_printf();
public:
    void printf_encode(u8* p);
};
#endif

/*
    @author 巷北
    @time 2025.10.27 8:41
        想了想还是不传参, 不论如何都需要自己配置,那配置的时候直接指定参数即可.
    毕竟这是应用层,传参还显得很杂乱.
*/
