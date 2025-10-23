#include "system.h"
#include "systick.h"
#include "led.hpp"
#include "key.hpp"
#include "beep.hpp"
int main(){	 
    SysTick_Init(SYSTICK_72MHz);
    
    LED led0(LED0);
    LED led1(LED1);
    LEDStaticBuilder::led[1] = &led1;

    BEEP beep;
    BEEPStaticBuilder::beep = &beep;

    KEY key0(KEY0);
    KEY key1(KEY1);
    KEY key2(KEY2);
    KEY key_up(KEY_UP);

    KEYStaticBuilder::key[0] = &key0;
    KEYStaticBuilder::key[1] = &key1;
    KEYStaticBuilder::key[2] = &key2;
    KEYStaticBuilder::key[3] = &key_up;

    ExternalInterrupt exti;
    exti.Init_EXTI(EXTI0);
    exti.Init_EXTI(EXTI2);
    exti.Init_EXTI(EXTI3);
    exti.Init_EXTI(EXTI4);
    
    KeyExtiManager k;
	while(1){
        led0.Heart_Beat();
	}
}


