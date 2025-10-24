#include "construction.hpp"

BeepMapping_TypeDef PeripheralMapping::beep0 = {
    RCC_APB2Periph_GPIOB,
    GPIOB,
    GPIO_Pin_8,
    &PBout(8),
    0
};

LedMapping_TypeDef PeripheralMapping::led0 = {
    RCC_APB2Periph_GPIOB,
    GPIOB,
    GPIO_Pin_5,
    &PBout(5),
    0
};

LedMapping_TypeDef PeripheralMapping::led1 = {
    RCC_APB2Periph_GPIOE,
    GPIOE,
    GPIO_Pin_5,
    &PEout(5),
    1
};

KeyMapping_TypeDef PeripheralMapping::key0 = {
    RCC_APB2Periph_GPIOE,
    GPIOE,
    GPIO_Pin_4,
    &PEin(4),
    LOW_LEVEL,
    0
};

KeyMapping_TypeDef PeripheralMapping::key1 = {
    RCC_APB2Periph_GPIOE,
    GPIOE,
    GPIO_Pin_3,
    &PEin(3),
    LOW_LEVEL,
    1
};

KeyMapping_TypeDef PeripheralMapping::key2 = {
    RCC_APB2Periph_GPIOE,
    GPIOE,
    GPIO_Pin_2,
    &PEin(2),
    LOW_LEVEL,
    2
};

KeyMapping_TypeDef PeripheralMapping::key3 = {
    RCC_APB2Periph_GPIOA,
    GPIOA,
    GPIO_Pin_0,
    &PAin(0),
    HIGH_LEVEL,
    3
};

/*
    使用方式:
    - 不改变数量,只需要在下方映射函数修改对应变量即可.使用时,传入结构体名即可.
    - 更改数量,比如希望用4个led灯,可是我下方只提供了2个led.可以直接自己模仿led结构体形式
    写,不过不要忘了在construction的类中声明.调用时同上.
    - 静态文件也需要编写.方便全局调用,增强灵活性.尝试一下吧,尽量避免编写.但是如果想额外添加外设数量,不得不编写了.
    - 不使用的外设, 可以全部注释掉
*/

/*  
    
    ------------------------------------------修改日志记录--------------------------------------------------------

    @author 巷北
    @time 2025.10.23 22:25
        本来全局直接初始化结构体, 就很棒.但是存在问题,就是多文件调用顺序问题.不保证其他文件使用beep, 是否会受影响.
    为了安全,采用如下方式.这样在Beep类中随时调用.用户可以直接在下方进行修改,增强灵活性.

-------------------------------------------------------------------------------------------------------------------
    
    @author 巷北
    @time 2025.10.24 9:07
        灵活转换.如果应用在其他地方, 期望使用4个led小灯, 那么自己添加对应led映射函数即可.我这里只提供了两个,不代表只
    可以使用两个小灯. 也不行. 因为LED类内部都是写死了的,无缘无故多了两个小灯,不可能初始化的.未来数量的不确定,导致了这个
    问题...    

        换了很多模式,映射模式也好, 其它的也罢,都否决掉了.最后选择结构体直接调用,取消映射.但是类型名呢, 还是用映射表示吧.
        最后看起来,很简单的样子.可是其中修修改改,否决了很多模式,最后才选择出最简单的,占中较小的一个设计模式...

--------------------------------------------------------------------------------------------------------------------
*/
