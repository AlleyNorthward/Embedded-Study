#include "utils.h"

void Heartbeat_LED(void){
    /*
        @author 巷北
        @time 2025.10.14 22:12
            只能同步进程, 所以外部如果有延时(使用了delay_ms),这里
        会同步受阻. 后续理解了,更换更好的检测方式.
    */
    if (!IS_INIT_LED()) LED_Init();
    static u8 i = 0;
    i++;
    if (i % 20 == 0) SET_LED0 = !SET_LED0;
	delay_ms(10);
}

