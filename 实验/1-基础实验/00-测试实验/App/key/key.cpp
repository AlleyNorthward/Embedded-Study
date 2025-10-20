#include "key.hpp"

void KEY::Init_KEY(uint32_t rcc, uint16_t pin, GPIO_TypeDef* port, GPIOMode_TypeDef mode){

    KeyState = 1;
    GPIO_InitTypeDef KEY_Structure;

    KEY_Structure.GPIO_Mode = mode;
    KEY_Structure.GPIO_Pin = pin;

    RCC_APB2PeriphClockCmd(rcc, ENABLE);
    GPIO_Init(port, &KEY_Structure);
}

KEY::KEY(ChoseKey _key):key(_key){
    assert_param(IS_CHOSED_KEY(_key));

    if(_key == KEY_UP){
        Init_KEY(KEY_UP_RCC_MASK, KEY_UP_PIN_MASK, KEY_UP_PORT_ADDR, GPIO_Mode_IPD);
    }
    else if(_key == KEY0){
        Init_KEY(KEY_RCC_MASK, KEY0_PIN_MASK, KEY0_PORT_ADDR);
    }
    else if(_key == KEY1){
        Init_KEY(KEY_RCC_MASK, KEY1_PIN_MASK, KEY1_PORT_ADDR);
    }
    else {
        Init_KEY(KEY_RCC_MASK, KEY2_PIN_MASK, KEY2_PORT_ADDR);
    }
}
KEY::KEY(uint32_t KEY_RCC, uint16_t KEY_PIN, GPIO_TypeDef* KEY_PORT, GPIOMode_TypeDef Mode){
    Init_KEY(KEY_RCC, KEY_PIN, KEY_PORT, Mode);
}

volatile unsigned long& KEY::get_PXin(){
    switch(key){
        case KEY0: return CHECK_KEY0;
        case KEY1: return CHECK_KEY1;
        case KEY2: return CHECK_KEY2;
        default:   return CHECK_KEY_UP;
    }
}


void KEY::on(KeyMode mode, void (*func)()){
    /*
        这里不知道PAin()能不能作为函数返回值直接返回
    为了安全起见, 这里不这么操作.
    */
    // volatile unsigned long* keyInputMap[4] = { &CHECK_KEY0, &CHECK_KEY1, &CHECK_KEY2, &CHECK_KEY_UP };
    // volatile unsigned long &CHECK_KEY = *keyInputMap[key];
    volatile unsigned long &CHECK_KEY = get_PXin();
    u8 level = 0;

    if(key == KEY_UP) level = 1;
    if(mode == KEY_HELD) KeyState = 1;

    if(KeyState == 1 && CHECK_KEY == level){
        delay_ms(10);
        KeyState = 0;
        func();
    }
    else if(KeyState == 0 && CHECK_KEY == !level) KeyState = 1;
}

void KEY::on(KeyMode mode, void (*func)(), volatile unsigned long& PXin, u8 level){
    // level代表高低电平.因为不确定上拉还是拉下,所以这里提供接口,灵活传参.
    if(mode == KEY_HELD) KeyState = 1;
    if(KeyState == 1 && PXin == level){
        delay_ms(10);
        KeyState = 0;
        func();
    }
    else if (KeyState == 0 && PXin == !level) KeyState = 1;
}