#include "exti.h"
#include "systick.h"
#include "led.h"
#include "beep.h"
#include "key.h"

/*
    @author 巷北
    @time 2025.10.16 10:09
        这部分,有很多写的方式.但是为了简单化,统一化,还是选择
    用基本方式来写吧.
*/
void EXTI_USING_KEY_Init(void){

    // 这是关键点,一定要先初始化KEY!
    if(!IS_INIT_KEY()) KEY_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // 复位与使能时钟.并且配置中断线.
    RCC_APB2PeriphClockCmd(RCC_EXTI_MASK, ENABLE);

    GPIO_EXTILineConfig(EXTI_KEY_UP_SOURCE_PORT_MASK, EXTI_KEY_UP_SOURCE_PIN_MASK);
    GPIO_EXTILineConfig(EXTI_KEY_SOURCE_PORT_MASK, EXTI_KEY0_SOURCE_PIN_MASK);
    GPIO_EXTILineConfig(EXTI_KEY_SOURCE_PORT_MASK, EXTI_KEY1_SOURCE_PIN_MASK);
    GPIO_EXTILineConfig(EXTI_KEY_SOURCE_PORT_MASK, EXTI_KEY2_SOURCE_PIN_MASK);

    // 这里定义NVIC初始化参数.使用了指针,练习目的.也可以四个变量,循环赋值.
    // NVIC控制器选择中断通道(IRQn),优先级,子优先级,中断通道使能.
    NVIC_InitTypeDef NVIC_KEY_UP_Init;
    NVIC_InitTypeDef* NVIC_KEY0_Init = &NVIC_KEY_UP_Init;
    NVIC_InitTypeDef* NVIC_KEY1_Init = &NVIC_KEY_UP_Init;
    NVIC_InitTypeDef* NVIC_KEY2_Init = &NVIC_KEY_UP_Init;

    NVIC_KEY_UP_Init.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_KEY_UP_Init.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_KEY_UP_Init.NVIC_IRQChannelSubPriority = 3;
    NVIC_KEY_UP_Init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_KEY_UP_Init);

    NVIC_KEY0_Init->NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_KEY0_Init->NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(NVIC_KEY0_Init);

    NVIC_KEY1_Init->NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_KEY1_Init->NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(NVIC_KEY1_Init);

    NVIC_KEY2_Init->NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_KEY2_Init->NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(NVIC_KEY2_Init);
    
    // 这个是EXTI(外部事件/中断外设)初始化
    // Trigger是判断外部向内部的输入电流.
    EXTI_InitTypeDef EXTI_KEY_UP_Init;
    EXTI_InitTypeDef *EXTI_KEY_Init = &EXTI_KEY_UP_Init;

    EXTI_KEY_UP_Init.EXTI_Line = EXTI_Line0;
    EXTI_KEY_UP_Init.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_KEY_UP_Init.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_KEY_UP_Init.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_KEY_UP_Init);

    EXTI_KEY_Init->EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
    EXTI_KEY_Init->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(EXTI_KEY_Init);
}

void EXTI0_IRQHandler(void){

    if(EXTI_GetITStatus(EXTI_Line0) == SET){
        delay_ms(10);
        
        if(CHECK_KEY_UP == KEY_HIGH){
            Set_LED(LED1, LIGHT);
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI2_IRQHandler(void){

    if(EXTI_GetITStatus(EXTI_Line2) == SET){
        delay_ms(10);

        if(CHECK_KEY2 == KEY_LOW){
            Set_BEEP(ENABLE);
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void){

    if(EXTI_GetITStatus(EXTI_Line3) == SET){
        delay_ms(10);
        
        if(CHECK_KEY1 == KEY_LOW){
            Set_LED(LED1, DARK);
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void){

    if(EXTI_GetITStatus(EXTI_Line4) == SET){
        delay_ms(10);

        if(CHECK_KEY0 == KEY_LOW){
            Set_BEEP(DISABLE);
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line4);
}
