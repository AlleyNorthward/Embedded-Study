#include "system.h"
#include "systick.h"
#include "led.hpp"
#include "key.hpp"
int main(){	 
    LED led0(LED0);
    LED led1(LED1);
    LEDStaticBuilder::led[0] = &led0;
    
    KEY key0(KEY0);
    KEY key1(KEY1);
	while(1){
        key0.on(KEY_SINGLE, LEDStaticBuilder::led0_on);
        key1.on(KEY_SINGLE, LEDStaticBuilder::led0_off);
        led1.Heart_Beat();
	}
}


