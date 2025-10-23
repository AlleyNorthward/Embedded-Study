#ifndef _LED_HPP
#define _LED_HPP

#include "system.h"
#include "systick.h"

#define LED0_RCC_MASK					RCC_APB2Periph_GPIOB
#define LED0_PORT_ADDR				    GPIOB
#define LED0_PIN_MASK					GPIO_Pin_5

#define LED1_RCC_MASK					RCC_APB2Periph_GPIOE
#define LED1_PORT_ADDR				    GPIOE
#define LED1_PIN_MASK					GPIO_Pin_5

typedef enum{LED0 = 0, LED1 = !LED0} ChoseLed;
#define IS_CHOSED_LED(LED)				(((LED) == LED0) || ((LED) == LED1))

#define SET_LED0                PBout(5)
#define SET_LED1                PEout(5)

class LED{
/*
    @author 巷北
    @time 2025.10.22
        思考了一下LED的设计模式,并不怎么好.为什么呢?设计LED的时候,总是考虑兼容外部设备,所以
    本来简洁清晰的描述,添加了很多复合选项,却也总显得十分杂乱.虽然重载可以使得灵活性增强,但是
    由于有很多宏定义和typedef的定义,重载过程中误用的话,也可能导致外部设备无法兼容.
        但是如果再设计一个新的ExtLED,这样跟LEDStaticBuilder无法兼容.可是对于静态管理类而言,
    本身面向的就是我这个类,而不是兼容外部设备,所以应该怎么弄呢?

        想了想,如果总是考虑,自己设备如何与外部设备兼容,那我为何
*/
private: 
    ChoseLed led;
    uint16_t LED_PIN;
    GPIO_TypeDef* LED_PORT;

    void Init_LED(uint32_t rcc, uint16_t pin, GPIO_TypeDef* port);
public:
    LED(ChoseLed _led);

    LED(uint32_t LED_RCC, uint16_t LED_PIN, GPIO_TypeDef* LED_PORT);
    // 注意, 默认低电平点亮.移至时注意.
    void on(bool IsOwn = true);
    void off(bool IsOwn = true);

    // 下面是额外封装方法
    void Heart_Beat(void);

};

class LEDStaticBuilder{
/*
    @author 巷北
    @time 2025.10.20 17:13
        静态/全局函数生成器. 不如python灵活,但是也有很多方法解决问题.
        现在全局和静态问题, 很难言.全局可以在led对象生成后写.但是这样
    每次都得写,缺少封装性. 提前写好, 又没有生成led对象,无法访问.on和.off,
    static放到LED类中也是面对的同一个境况.
        而这个类就是解决这个问题的.方法,函数提前写好,生命周期与led实例化
    同步.

------------------------------------------------------------------------------

    使用方法:
    LED led0(LED0);
    LED* LEDStaticBuilder::led[2] = {&led0, 0};
    注意, 这是在main全局中定义的. 这已经是目前最优解决方案了.之后就可以通过LEDStaticBuilder::访问函数了
*/

public:
    static LED* led[2];
    static void led0_on();
    static void led0_off();
    static void led1_on();
    static void led1_off();
};

#endif
