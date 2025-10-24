#include "system.h"
#include "beep.hpp"
#include "construction.hpp"
#include "led.hpp"
#include "systick.h"
int main(){	 

    BEEP beep(PeripheralMapping::beep0);
	LED led0(PeripheralMapping::led0), led1(PeripheralMapping::led1);
	KEY key0(PeripheralMapping::key0), key1(PeripheralMapping::key1), key2(PeripheralMapping::key2), key3(PeripheralMapping::key3);
	
	while(1){
		key0.on(KEY_SINGLE, LED::on_global, 0);
		key1.on(KEY_SINGLE, LED::off_global, 0);
		key2.on(KEY_SINGLE, BEEP::on_global, 0);
		key3.on(KEY_SINGLE, BEEP::off_global, 0);
		led1.Heart_Beat();
	}

}
