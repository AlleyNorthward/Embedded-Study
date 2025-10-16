#include "key.h"
#include "systick.h"

static u8 IsInitKey = 0;
u8 IS_INIT_KEY(void){return IsInitKey;}
void Set_IsInitKey(void){IsInitKey = 1;}

void KEY_Init(void){
    
    GPIO_InitTypeDef GPIO_KEY_UP_Init;
    GPIO_InitTypeDef* GPIO_KEY_Init = &GPIO_KEY_UP_Init;

    GPIO_KEY_UP_Init.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_KEY_UP_Init.GPIO_Pin = KEY_UP_PIN_MASK;
    
    RCC_APB2PeriphClockCmd(KEY_RCC_MASK | KEY_UP_RCC_MASK, ENABLE);
    GPIO_Init(KEY_UP_PORT_ADDRESS, &GPIO_KEY_UP_Init);

    GPIO_KEY_Init -> GPIO_Mode = GPIO_Mode_IPU;
    GPIO_KEY_Init -> GPIO_Pin = KEY0_PIN_MASK | KEY1_PIN_MASK | KEY2_PIN_MASK;

    GPIO_Init(KEY_PORT_ADDRESS, GPIO_KEY_Init);

    Set_IsInitKey();

}

// mode = 0, 单次检测按键
// mode = 1, 连续检测按键
KEY_PRESS_TypeDef KEY_Scan(KeyMode mode){
    if (!IS_INIT_KEY()) KEY_Init();
    
    static u8 key = 1;
    if(mode == KEY_HELD) key = 1;
    
    if (key == 1 && (CHECK_KEY_UP == KEY_HIGH || CHECK_KEY0 == KEY_LOW || CHECK_KEY1 == KEY_LOW || CHECK_KEY2 == KEY_LOW)){
        delay_ms(10); // 消抖
        if (CHECK_KEY_UP == KEY_HIGH) return KEY_UP_PRESS;
        else if (CHECK_KEY0 == KEY_LOW) return KEY0_PRESS;
        else if (CHECK_KEY1 == KEY_LOW) return KEY1_PRESS;
        else if (CHECK_KEY2 == KEY_LOW) return KEY2_PRESS;
    }

    else if(key == 0 && (CHECK_KEY_UP == KEY_LOW && CHECK_KEY0 == KEY_HIGH && CHECK_KEY1 == KEY_HIGH && CHECK_KEY2 == KEY_HIGH)){
        key = 1;
    }
    return KEY_PRESS_NONE;
}

