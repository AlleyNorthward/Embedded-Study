#include "exti.h"
#include "systick.h"
#include "key.h"
#include "led.h"
#include "beep.h"

void Init_EXTI(void){
    NVIC_InitTypeDef NVIC_Init_Structure;
    NVIC_Init_Structure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;

    RCC_APB2PeriphClockCmd(RCC_EXIT, ENABLE);

    GPIO_EXTILineConfig(EXIT_KEY_UP_PORT, EXIT_KEY_UP_Pin);
    GPIO_EXTILineConfig(EXIT_KEY_PORT, EXIT_KEY0_Pin);
    GPIO_EXTILineConfig(EXIT_KEY_PORT, EXIT_KEY1_Pin);
    GPIO_EXTILineConfig(EXIT_KEY_PORT, EXIT_KEY2_Pin);

    NVIC_Init(&NVIC_Init_Structure);

    NVIC_Init_Structure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_Init_Structure);

    NVIC_Init_Structure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_Init_Structure);

    NVIC_Init_Structure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_Init_Structure);

    

    EXTI_InitTypeDef EXTI_Init_Structure;
    EXTI_Init_Structure.EXTI_Line = EXTI_Line0;
    EXTI_Init_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_Init_Structure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init_Structure.EXTI_LineCmd = ENABLE;

    EXTI_Init(&EXTI_Init_Structure);

    EXTI_Init_Structure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
    EXTI_Init_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_Init_Structure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init_Structure.EXTI_LineCmd = ENABLE;

    EXTI_Init(&EXTI_Init_Structure);

}

void EXTI0_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line0) == SET){

        delay_ms(10);
        if(KEY_UP == 1){
            SET_LED1 = LIGHT;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI2_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line2) == SET){

        delay_ms(10);
        if(KEY2 == 0){
           BEEP = 1; 
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line3) == SET){

        delay_ms(10);
        if(KEY1 == 0){
            SET_LED1 = DARK;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line4) == SET){

        delay_ms(10);
        if(KEY0 == 0){
            BEEP = 0;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line4);
}
