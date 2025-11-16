#ifndef _SET_UP_HPP
#define _SET_UP_HPP

#include "static_manager.hpp"

class SetUp{
private:
    USART usart;
    LED led0; 
    TFTLCD_ tftlcd;
protected:
    SetUp();
    void testing_picture_init();
    void testing_picture_run();
};
#endif

