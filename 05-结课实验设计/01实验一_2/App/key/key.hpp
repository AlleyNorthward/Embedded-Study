#ifndef _KEY_HPP
#define _KEY_HPP

#include "system.h"

typedef void (*KeyFunc_TypeDef)(u8);
typedef void (*KeyFunc_zero_TypeDef)();
typedef void (*KeyFunc1_TypeDef)(u16);

typedef enum{
    LOW_LEVEL,
    HIGH_LEVEL
}Level_TypdDef;
#define IS_LEVEL_TYPE(LEVEL) (((LEVEL) == HIGH_LEVEL) || ((LEVEL) == LOW_LEVEL))

typedef enum{
    KEY_HELD,
    KEY_SINGLE
}KeyMode_TypeDef;
#define IS_KEY_MODE(MODE) (((MODE) == KEY_HELD) || ((MODE) == KEY_SINGLE))

typedef struct{
    uint32_t KEY_RCC_MASK;
    GPIO_TypeDef* KEY_PORT_ADDR;
    uint16_t KEY_PIN_MASK;
    volatile unsigned long* CHECK_KEY;
    Level_TypdDef LEVEL;// 代表的是上升沿还是下降沿 直接交给用户处理吧,
    u8 CNT;
}KeyMapping_TypeDef;

class KEY{
private:
    u8 KeyState;
    KeyMapping_TypeDef& SingleKey;
public:
    static u8 mode;
    KEY(KeyMapping_TypeDef& key);
    void on(KeyMode_TypeDef mode, KeyFunc_TypeDef func, u8 i);
    void on(KeyMode_TypeDef mode, KeyFunc_zero_TypeDef func);
    void on(KeyMode_TypeDef mode, KeyFunc1_TypeDef func, u16 config_num);
    
    inline void exti_on(KeyFunc_TypeDef func, u8 i){
        if(*SingleKey.CHECK_KEY == SingleKey.LEVEL) func(i);
    }
    inline void exti_on(KeyFunc1_TypeDef func, u16 config_num){
        if(*SingleKey.CHECK_KEY == SingleKey.LEVEL) func(config_num);
    }
    inline void exti_on(KeyFunc_zero_TypeDef func){
        if(*SingleKey.CHECK_KEY == SingleKey.LEVEL) func();
    }
    static void check_single_key();
};

#endif

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
