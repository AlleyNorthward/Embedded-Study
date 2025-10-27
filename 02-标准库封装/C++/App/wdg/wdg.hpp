#ifndef _IWDG_HPP
#define _IWDG_HPP

#include "system.h"
typedef u8 IWDG_Prescaler_TypeDef;
typedef u16 IWDG_ReloadRegister_TypeDef;

class WDG_{
public:
    void IWDG_Init(IWDG_Prescaler_TypeDef per, IWDG_ReloadRegister_TypeDef rls);
    void IWDG_FeedDog();

    void WWDG_Init();
};


#endif
