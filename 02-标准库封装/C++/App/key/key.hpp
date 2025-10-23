#ifndef _KEY_HPP
#define _KEY_HPP

#include "system.h"
#include "systick.h"
#include "beep.hpp"
#include "led.hpp"
#include "exti.hpp"

#define KEY_RCC_MASK                                RCC_APB2Periph_GPIOE
#define KEY_UP_RCC_MASK                             RCC_APB2Periph_GPIOA

#define KEY0_PIN_MASK                               GPIO_Pin_4
#define KEY1_PIN_MASK                               GPIO_Pin_3
#define KEY2_PIN_MASK                               GPIO_Pin_2
#define KEY_UP_PIN_MASK                             GPIO_Pin_0

#define KEY_PORT_ADDR                               GPIOE
#define KEY0_PORT_ADDR                              GPIOE
#define KEY1_PORT_ADDR                              GPIOE
#define KEY2_PORT_ADDR                              GPIOE
#define KEY_UP_PORT_ADDR                            GPIOA

#define CHECK_KEY_UP                                PAin(0)
#define CHECK_KEY0                                  PEin(4)
#define CHECK_KEY1                                  PEin(3)
#define CHECK_KEY2                                  PEin(2)

typedef enum{KEY_HELD = 1, KEY_SINGLE = !KEY_HELD} KeyMode;
#define IS_KEY_MODE(KEY_MODE)			(((KEY_MODE) == KEY_HELD) || ((KEY_MODE) == KEY_SINGLE))

typedef enum{
    KEY0,
    KEY1,
    KEY2,
    KEY_UP
}ChoseKey;
#define IS_CHOSED_KEY(KEY)              (((KEY) == KEY0) || ((KEY) == KEY1) || ((KEY) == KEY2) || ((KEY) == KEY_UP))
/*
    @author 巷北
    @time 2025.10.20 11:22
        想了想设计模式,打算分别编写按键吧,使用时就实例化对应的key.
    C中的那个编写方法,是一次性操作四个按键,但是也并不是每次都会使用
    四个按键.我这样呢, 实例化会有些开销,但可以忽略不计.
        然后打算按下按键时,传入一个函数参数, 抽象为按键按下时的产生
    效果.函数怎么写呢?打算函数内部实例化一个对象,然后再操作.不过这样
    开销占用不知道大不大.先写写吧.
*/
class KEY{
private:
    ChoseKey key;
    u8 KeyState;
    GPIO_TypeDef* KEY_PORT;
    uint16_t KEY_PIN;

    void Init_KEY(uint32_t rcc, uint16_t pin, GPIO_TypeDef* port, GPIOMode_TypeDef mode = GPIO_Mode_IPU);
public:
    KEY(ChoseKey _key);
    KEY(uint32_t KEY_RCC, uint16_t KEY_PIN, GPIO_TypeDef* KEY_PORT, GPIOMode_TypeDef Mode = GPIO_Mode_IPU);
    volatile unsigned long& get_PXin();

    void on(KeyMode mode, void (*func)());
    void on(KeyMode mode, void (*func)(), volatile unsigned long& PXin, u8 level = 0);
    void on(KeyMode mode, void (*func)(), u8 level, bool IsOwn); // 外接低电平,level传0.eg:KEY_UP外接高电平, level=1.

    // 下面这两个是配置中断按键控制函数.直接使用on不可行. 不过缺少一般性.为具备一般性,可以参考on的视线效果.
    bool is_pressed();
    void exti_on(void (*func)());
};

class KEYStaticBuilder{
public:
    static KEY* key[4];
    static void EXTI0_KEY_UP();
    static void EXTI4_KEY0();
    static void EXTI3_KEY1();
    static void EXTI2_KEY2();
};

class KeyExtiManager{
public:
    KeyExtiManager();
};
#endif
