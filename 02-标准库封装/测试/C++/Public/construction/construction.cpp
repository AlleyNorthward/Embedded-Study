#include "construction.hpp"

/*
    @author 巷北
    @time 2025.10.23 22:25
        本来全局直接初始化结构体, 就很棒.但是存在问题,就是多文件调用顺序问题.不保证其他文件使用beep, 是否会受影响.
    为了安全,采用如下方式.这样在Beep类中随时调用.用户可以直接在下方进行修改,增强灵活性.
*/

BeepMapping_TypeDef& getBeepMapping() {
    static BeepMapping_TypeDef beep = {
        RCC_APB2Periph_GPIOB,
        GPIOB,
        GPIO_Pin_8,
        &PBout(8)
    };
    return beep;
}

