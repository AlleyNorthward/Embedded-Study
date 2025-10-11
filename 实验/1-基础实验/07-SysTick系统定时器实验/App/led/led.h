#ifndef _LED_H
#define _LED_H

#include "system.h"

/*
    @auther 巷北
    @time 2025.10.10 19:54
        这些应该是刚才自己写的.由于可能会时不时地添加些
    东西,所以还是写点注释比较好.
        下面内容对应基础实验5.主要是GPIO的管脚,端口,还有
    还有相关外设时钟的定义,主要面对的对象是LED灯.
*/
#define RCC_LED0                RCC_APB2Periph_GPIOB
#define LED0_PORT               GPIOB
#define LED0_PIN                GPIO_Pin_5

#define RCC_LED1                RCC_APB2Periph_GPIOE
#define LED1_PORT               GPIOE
#define LED1_PIN                GPIO_Pin_5

/*
    @auther 巷北
    @time 2025.10.10 19:57
        下面是位带点亮操作.原理没有看, 主要先来看看代码,了解一下.
        原本代码是这么点亮的:
                    PBout(5) = 0
        这么点灭的:
                    PBout(5) = 1
        从编程角度而言,太过于抽象.从用户角度来看,虽然很简单,但是
    却不好理解.所有有了下面的宏定义.点亮, 点灭的代码就变成下面的了:
                    SET_LED0 = LIGHT
                    SET_LED0 = DARD
        这样就更容易理解了.
*/

#define SET_LED0                PBout(5)
#define SET_LED1                PEout(5)

#define LIGHT                   0
#define DARK                    1
void Init_led(void);
#endif
