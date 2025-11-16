#ifndef _USART_HPP
#define _USART_HPP

#include "system.h"
#include "stdio.h"

#define USART1_REC_LEN                  200

#define RX_FINISHED_MASK                0x8000
#define RX_RECEIVED_CR_MASK             0x4000
#define RX_13_LOW_BITS                  0x3fff

#define RX_FINISHED(INFO)               ((INFO) & RX_FINISHED_MASK)
#define RX_RECEIVED_CR(INFO)            ((INFO) & RX_RECEIVED_CR_MASK)
#define LF_ASCII                        0x0A // /n
#define CR_ASCII                        0x0D // /r

class USART{
public:
    static u8 USART1_RX_BUF[USART1_REC_LEN];
    static u16 USART1_RX_STA;
    void Init_USART1(u32 baud_rate);
    void send_data_to_computer_USART1();
    static u16 get_RX_BUF();
};

#endif
