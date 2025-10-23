#ifndef _CLOCK_H
#define _CLOCK_H

#include "system.h"

/*
    @author 巷北
    @time 2025.10.14 14:45
        这个时钟呢,目前还看不懂.先放在这吧.需要注意的是,如果不运行这行代码,delay函数就无法应用.
        另外,RCC_HSE_Config(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);这个函数默认为时钟频率为
    36(8/2*9).
        后续了解更多知识后,再来分析吧.
        delay函数定义如下:
    void delay(u32 ms){
	    while (ms --);
    }   
    --------------------------------------------------------------------------------------  
*/

void RCC_HSE_Config(u32 div, u32 pllm);

#endif
