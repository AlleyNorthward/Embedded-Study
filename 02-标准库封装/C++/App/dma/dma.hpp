#ifndef _DMA_HPP
#define _DMA_HPP

#include "system.h"
#define DMA_REC_LEN                     5000


class DMA_{
public:
    static u8 DMA_RX_buf[DMA_REC_LEN];
    static u16 DMA_RX_STA;
    void DMAx_Init(DMA_Channel_TypeDef* DMAy_Channelx, u32 par, u32 mar, u16 ndtr);
    void DMAx_usart_to_dma(DMA_Channel_TypeDef* DMAy_Channelx, u32 par, u32 mar, u16 ndtr);
    static void DMAx_Enable(DMA_Channel_TypeDef* DMAy_Channelx, u16 ndtr);
    void Testing_send_data(u8 *p);
    u16 get_buf_length();
};

#endif
