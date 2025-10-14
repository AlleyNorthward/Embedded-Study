#include "utils.h"

void Heartbeat_LED(void){
    if (!IS_INIT_LED()) LED_Init();
    static u8 i = 0;
    i++;
    if (i % 20 == 0) SET_LED0 = !SET_LED0;
	delay_ms(10);
}

