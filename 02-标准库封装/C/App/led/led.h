#ifndef _LED_H
#define _LED_H

#include "system.h"

/*
    @author 巷北
    @time 2025.10.14 13:57
        目前自己更新了一下命名规则, 有条理, 有依据地命名, 方便自己理解的命令方式.
        下面宏定义, 包含后缀, 其中MASK代表的是掩码, 也就是操作数. 如果包含位运算,
    就用掩码,后缀是MASK, 如果不要要位运算, 只是赋值, 那么后缀名位VALUE.另一个后缀
    是ADDRESS, 代表的是地址的意思.有这个后缀的,表示大概率是地址, 定义变量的时候,类
    型需要细心观察.
        再下面是枚举定义,并且有类型检查.模仿的库中定义方式吧,也不是很困难.
    --------------------------------------------------------------------------
*/

#define LED0_RCC_MASK					RCC_APB2Periph_GPIOB
#define LED0_PORT_ADDRESS				GPIOB
#define LED0_PIN_MASK					GPIO_Pin_5

#define LED1_RCC_MASK					RCC_APB2Periph_GPIOE
#define LED1_PORT_ADDRESS				GPIOE
#define LED1_PIN_MASK					GPIO_Pin_5

typedef enum{DARK = 1, LIGHT = !DARK} LedState;
#define IS_LED_STATE(LED_STATE)			(((LED_STATE) == DARK) || ((LED_STATE) == LIGHT))

typedef enum{LED0 = 0, LED1 = !LED0} ChoseLed;
#define IS_CHOSED_LED(LED)				(((LED) == LED0) || ((LED) == LED1))

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
    -------------------------------------------------------------

*/

#define SET_LED0                PBout(5)
#define SET_LED1                PEout(5)

void LED_Init(void);
u8 IS_INIT_LED(void);
void Set_IsInitLed(void);

void Control_LED(ChoseLed LED, LedState LED_State);
void Set_LED(ChoseLed LED, LedState);
#endif
