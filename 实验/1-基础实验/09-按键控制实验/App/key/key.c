#include "key.h"
#include "systick.h"

void Init_KEY(void){
    
    GPIO_InitTypeDef GPIO_Init_Key;

    GPIO_Init_Key.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init_Key.GPIO_Pin = KEY_UP_PIN;
    
    RCC_APB2PeriphClockCmd(RCC_KEY | RCC_KEY_UP, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_KEY_UP, ENABLE);
    GPIO_Init(KEY_UP_PORT, &GPIO_Init_Key);

    GPIO_Init_Key.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init_Key.GPIO_Pin = KEY0_PIN | KEY1_PIN | KEY2_PIN;

    GPIO_Init(KEY_PORT, &GPIO_Init_Key);

}

// mode = 0, 单次检测按键
// mode = 1, 连续检测按键
u8 KEY_Scan(u8 mode){
    
    static u8 key = 1;
    if(mode == 1) key = 1;
    
    if (key == 1 && (KEY_UP == 1 || KEY0 == 0 || KEY1 == 0 || KEY2 == 0)){
        delay_ms(10); // 消抖
        key = 0;
        if (KEY_UP == 1) return KEY_UP_PRESS;
        else if (KEY0 == 0) return KEY0_PRESS;
        else if (KEY1 == 0) return KEY1_PRESS;
        else if (KEY2 == 0) return KEY2_PRESS;
    }

    else if(key == 0 && (KEY_UP == 0 && KEY0 == 1 && KEY1 == 1 && KEY2 == 1)){
        key = 1;
    }
    return 0;
}

