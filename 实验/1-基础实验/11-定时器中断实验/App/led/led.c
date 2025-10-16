#include "led.h"

static u8 IsInitLed = 0;
u8 IS_INIT_LED(void){return IsInitLed;}
void Set_IsInitLed(void){IsInitLed = 1;}

/*
	@author 巷北
	@time 2025.10.14 14:06
		这是小灯初始化函数.思想非常简单,开启时钟,GPIO初始化,默认设置为低电平.
		我下面为了区分小灯的GPIO端口的不同,定义了两个变量,一个是GPIO_LED0_Init,
	另一个是GPIO_LED1_Init指针.其实第二个指针不用定义,直接去修改第一个变量的值
	即可.但是我还是想用双变量区分GPIO的端口,所以定义了两个变量,且为了节省空间,第
	二个变量为指针类型.
*/
void LED_Init(void){

	GPIO_InitTypeDef GPIO_LED0_Init;
	GPIO_InitTypeDef *GPIO_LED1_Init = &GPIO_LED0_Init;

	GPIO_LED0_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_LED0_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_LED0_Init.GPIO_Pin = LED0_PIN_MASK;

	RCC_APB2PeriphClockCmd(LED0_RCC_MASK, ENABLE);
	GPIO_Init(LED0_PORT_ADDRESS, &GPIO_LED0_Init);
	GPIO_SetBits(LED0_PORT_ADDRESS, LED0_PIN_MASK);

	GPIO_LED1_Init->GPIO_Pin = LED1_PIN_MASK;
	RCC_APB2PeriphClockCmd(LED1_RCC_MASK, ENABLE);
	GPIO_Init(LED1_PORT_ADDRESS, GPIO_LED1_Init);
	GPIO_SetBits(LED1_PORT_ADDRESS, LED1_PIN_MASK);

	Set_IsInitLed();
}

/*
	@author 巷北
	@time 2025.10.14 14:10
		下面这个函数, 是控制小灯的开关.不过感觉名字起的不太好,却没有更好的
	命名方式,哈哈.
		需要注意,port为指针类型.因为其指向的端口是指针类型,回溯一下可以清晰地
	看到.pin也是同样的道理.
		这个函数主要是为了隐藏细节,避免用户直接操控GPIO_ResetBits()函数,提供
	接口, 方便用户操作.另外,还有位带操作,直接操控小灯的,太过于抽象,刚开始可能
	还知道什么意思,可是时间一长,就会忘掉.
*/

void Control_LED(ChoseLed LED, LedState LED_State){
	assert_param(IS_LED_STATE(LED_State));
	assert_param(IS_CHOSED_LED(LED));
	if (!IS_INIT_LED()) LED_Init();

	GPIO_TypeDef* port;
	uint16_t pin;

	if (LED == LED0){
		port = LED0_PORT_ADDRESS;
		pin = LED0_PIN_MASK;
	}
	else{
		port = LED1_PORT_ADDRESS;
		pin = LED1_PIN_MASK;
	}
	if (LED_State == LIGHT){
		GPIO_ResetBits(port, pin);
	}
	else{
		GPIO_SetBits(port, pin);
	}
}

/*
	@author 巷北
	@time 2025.10.14 15:08
		下面是使用位带控制小灯开关的. 仍然将抽象部分隐藏了,提供接口给用户.
	--------------------------------------------------------------------
*/
void Set_LED(ChoseLed LED, LedState LED_State){
	assert_param(IS_LED_STATE(LED_State));
	assert_param(IS_CHOSED_LED(LED));
	if (!IS_INIT_LED()) LED_Init(); 

	if (LED == LED0) SET_LED0 = LED_State;
	else SET_LED1 = LED_State;
}

