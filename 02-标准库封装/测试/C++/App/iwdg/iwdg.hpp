#ifndef _IWDG_HPP
#define _IWDG_GPP

#include "system.h"
typedef u8 IWDG_Prescaler_TypeDef;
typedef u16 IWDG_ReloadRegister_TypeDef;

class IWDG_{
public:
    IWDG_(IWDG_Prescaler_TypeDef pre, IWDG_ReloadRegister_TypeDef rlr);
    static void IWDG_FeedDog();
    static void feed_back();
};

#endif
