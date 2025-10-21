#include "exti.hpp"
void ExternalInterrupt::Config_EXTI(uint8_t EXTI_IRQn, uint8_t sub, uint32_t EXTI_Line, EXTITrigger_TypeDef Trigger){
    NVIC_InitTypeDef NVIC_EXTI_Structure;
    EXTI_InitTypeDef EXTI_Structure;

    NVIC_EXTI_Structure.NVIC_IRQChannel = EXTI_IRQn;
    NVIC_EXTI_Structure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_EXTI_Structure.NVIC_IRQChannelSubPriority = sub;
    NVIC_EXTI_Structure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_EXTI_Structure);

    EXTI_Structure.EXTI_Line = EXTI_Line;
    EXTI_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_Structure.EXTI_Trigger = Trigger;
    EXTI_Structure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_Structure);
}

void ExternalInterrupt::Init_EXTI(ChoseExti _exti, uint32_t NVIC_PriorityGroup){
    assert_param(IS_CHOSED_EXTI(_exti));
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
    RCC_APB2PeriphClockCmd(RCC_EXTI_MASK, ENABLE);
    
    switch(_exti){
        case EXTI0:
            GPIO_EXTILineConfig(EXTI_KEY_UP_SOURCE_PORT_MASK, EXTI_KEY_UP_SOURCE_PIN_MASK);
            Config_EXTI(EXTI0_IRQn, 3, EXTI_Line0, EXTI_Trigger_Rising);
            break;
        case EXTI2:
            GPIO_EXTILineConfig(EXTI_KEY_SOURCE_PORT_MASK, EXTI_KEY2_SOURCE_PIN_MASK);
            Config_EXTI(EXTI2_IRQn, 2, EXTI_Line2, EXTI_Trigger_Falling);
            break;
        case EXTI3:
            GPIO_EXTILineConfig(EXTI_KEY_SOURCE_PORT_MASK, EXTI_KEY1_SOURCE_PIN_MASK);
            Config_EXTI(EXTI3_IRQn, 1, EXTI_Line3, EXTI_Trigger_Falling);
            break;
        case EXTI4:
            GPIO_EXTILineConfig(EXTI_KEY_SOURCE_PORT_MASK, EXTI_KEY0_SOURCE_PIN_MASK);
            Config_EXTI(EXTI4_IRQn, 0, EXTI_Line4, EXTI_Trigger_Falling);
            break;
        default:
            break;
    }
}
void ExternalInterrupt::Init_EXTI(uint32_t RCC_EXTI, uint8_t GPIO_PortSource, uint8_t GPIO_PinSource, NVIC_InitTypeDef* NVIC_InitStruct, EXTI_InitTypeDef* EXTI_InitStruct, uint32_t NVIC_PriorityGroup){
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
    RCC_APB2PeriphClockCmd(RCC_EXTI, ENABLE);

    GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);
    NVIC_Init(NVIC_InitStruct);
    EXTI_Init(EXTI_InitStruct);
}



Callback EXTIManager::callbacks[5] = {0};
void EXTIManager::attach(uint8_t line, Callback cb){
    EXTIManager::callbacks[line] = cb;
}

void EXTIManager::handle(uint8_t line){
    if(EXTIManager::callbacks[line]) EXTIManager::callbacks[line]();
}

extern "C" void EXTI0_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line0) == SET){
        EXTIManager::handle(0);
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

extern "C" void EXTI2_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line2) == SET){
        EXTIManager::handle(2);
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

extern "C" void EXTI3_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line3) == SET){
        EXTIManager::handle(3);
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

extern "C" void EXTI4_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line4) == SET){
        EXTIManager::handle(4);
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}
