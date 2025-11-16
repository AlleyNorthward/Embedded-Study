#include "key.hpp"
#include "static_manager.hpp"

u8 KEY::mode = 0;
KEY::KEY(KeyMapping_TypeDef& key):KeyState(1), SingleKey(key){
    StaticBuilder::key[SingleKey.CNT] = this;
    GPIO_InitTypeDef KEY_Structure;

    if(SingleKey.LEVEL == HIGH_LEVEL) KEY_Structure.GPIO_Mode = GPIO_Mode_IPD;
    else KEY_Structure.GPIO_Mode = GPIO_Mode_IPU;
    KEY_Structure.GPIO_Pin = SingleKey.KEY_PIN_MASK;

    RCC_APB2PeriphClockCmd(SingleKey.KEY_RCC_MASK, ENABLE);
    GPIO_Init(SingleKey.KEY_PORT_ADDR, &KEY_Structure);
}

void KEY::on(KeyMode_TypeDef mode, KeyFunc_TypeDef func, u8 i){
	assert_param(IS_KEY_MODE(mode));
    if(mode == KEY_HELD) KeyState = 1;

    if(KeyState == 1 && *SingleKey.CHECK_KEY == SingleKey.LEVEL){
        delay_ms(10);
        KeyState = 0;
        func(i);
    }
    else if(KeyState == 0 && *SingleKey.CHECK_KEY == !SingleKey.LEVEL) KeyState = 1;
}

void KEY::on(KeyMode_TypeDef mode, KeyFunc_zero_TypeDef func){
	assert_param(IS_KEY_MODE(mode));
    if(mode == KEY_HELD) KeyState = 1;

    if(KeyState == 1 && *SingleKey.CHECK_KEY == SingleKey.LEVEL){
        delay_ms(10);
        KeyState = 0;
        func();
    }
    else if(KeyState == 0 && *SingleKey.CHECK_KEY == !SingleKey.LEVEL) KeyState = 1;
}

void KEY::on(KeyMode_TypeDef mode, KeyFunc1_TypeDef func, u16 config_num){
	assert_param(IS_KEY_MODE(mode));
    if(mode == KEY_HELD) KeyState = 1;

    if(KeyState == 1 && *SingleKey.CHECK_KEY == SingleKey.LEVEL){
        delay_ms(10);
        KeyState = 0;
        func(config_num);
    }
    else if(KeyState == 0 && *SingleKey.CHECK_KEY == !SingleKey.LEVEL) KeyState = 1;
}

void KEY::check_single_key(){
    mode++;
    if(mode > 3) mode = 1;
}
