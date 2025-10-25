#include "beep.hpp"
#include "construction.hpp"
#include "static_manager.hpp"

BEEP::BEEP(BeepMapping_TypeDef& beep):SingleBeep(beep){// 引用成员只能这么初始化
    StaticBuilder::beep[SingleBeep.CNT] = this;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(SingleBeep.BEEP_RCC_MASK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = SingleBeep.BEEP_PIN_MASK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SingleBeep.BEEP_PORT_ADDR, &GPIO_InitStructure);

    *SingleBeep.SET_BEEP = 0;
}

void BEEP::on_global(u8 i){
    StaticBuilder::beep[i]->on();
}

void BEEP::off_global(u8 i){
    StaticBuilder::beep[i]->off();
}
