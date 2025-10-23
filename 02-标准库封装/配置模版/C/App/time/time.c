#include "time.h"
#include "led.h"

void TIM4_Init(u16 per, u16 psc){
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBase_Init;
    NVIC_InitTypeDef NVIC_TIM_Init;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBase_Init.TIM_Period = per;
    TIM_TimeBase_Init.TIM_Prescaler = psc;
    TIM_TimeBase_Init.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBase_Init.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBase_Init);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

    NVIC_TIM_Init.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_TIM_Init.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_TIM_Init.NVIC_IRQChannelSubPriority = 3;
    NVIC_TIM_Init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_TIM_Init);

    TIM_Cmd(TIM4, ENABLE);
}

void TIM4_IRQHandler(void){
    if(TIM_GetITStatus(TIM4, TIM_IT_Update)){
        if(!IS_INIT_LED()) LED_Init();
        SET_LED1 = !SET_LED1;
    }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
