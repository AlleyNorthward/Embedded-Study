#ifndef _USART_HPP
#define _USART_HPP

#include "system.h"
#include "stdio.h"

#define USART1_REC_LEN                  200

class USART{
public:
    static u8 USART1_RX_BUF[USART1_REC_LEN];
    static u16 USART1_RX_STA;
    void Init_USART1(u32 baud_rate);
    void send_data_USART1();
};

#endif
