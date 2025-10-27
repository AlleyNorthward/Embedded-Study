#ifndef _LED_HPP
#define _LED_HPP

#include "system.h"

typedef struct{
    uint32_t LED_RCC_MASK;
    GPIO_TypeDef* LED_PORT_ADDR;
    uint16_t LED_PIN_MASK;
    volatile unsigned long* SET_LED;
    u8 CNT;
}LedMapping_TypeDef;

class LED{
private:
    LedMapping_TypeDef& SingleLed;
public:
    LED(LedMapping_TypeDef& led);
    inline void on(){*SingleLed.SET_LED = 0;};
    inline void off(){*SingleLed.SET_LED = 1;};
    inline void reverse(){*SingleLed.SET_LED = !*SingleLed.SET_LED;};

    void static on_global(u8 i);
    void static off_global(u8 i);
    void Heart_Beat();
};

#endif

