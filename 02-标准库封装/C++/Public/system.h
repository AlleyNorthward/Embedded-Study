#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "stm32f10x.h"

/*
    @author 巷北
    @time 2025.10.14 15:40
        这些都是教程给的.目前理解起来比较困难.不过像这种偏向底层的,当前也不需要理解,知道怎么用就行.毕竟库本事
    就是底层操作,我会用函数就行,但是函数怎么实现的,目前并不需要关心.等后面将基础知识都补充完全后,或者写了很多
    代码之后,再回过头来理解会更容易.所以没必要太着急,一口吃不成个胖子.
    ---------------------------------------------------------------------------------------------------
*/

#define BITBAND(addr, bitnum)       ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))

#define MEM_ADDR(addr)              *((volatile unsigned long *) (addr))
#define BIT_ADDR(addr, bitnum)      MEM_ADDR(BITBAND(addr, bitnum))

#define GPIOA_ODR_Addr              (GPIOA_BASE + 12)
#define GPIOB_ODR_Addr              (GPIOB_BASE + 12)
#define GPIOC_ODR_Addr              (GPIOC_BASE + 12)
#define GPIOD_ODR_Addr              (GPIOD_BASE + 12)
#define GPIOE_ODR_Addr              (GPIOE_BASE + 12)
#define GPIOF_ODR_Addr              (GPIOF_BASE + 12)
#define GPIOG_ODR_Addr              (GPIOG_BASE + 12)

#define GPIOA_IDR_Addr              (GPIOA_BASE + 8)
#define GPIOB_IDR_Addr              (GPIOB_BASE + 8)
#define GPIOC_IDR_Addr              (GPIOC_BASE + 8)
#define GPIOD_IDR_Addr              (GPIOD_BASE + 8)
#define GPIOE_IDR_Addr              (GPIOE_BASE + 8)
#define GPIOF_IDR_Addr              (GPIOF_BASE + 8)
#define GPIOG_IDR_Addr              (GPIOG_BASE + 8)

#define PAout(n)                    BIT_ADDR(GPIOA_ODR_Addr, n)
#define PAin(n)                     BIT_ADDR(GPIOA_IDR_Addr, n)

#define PBout(n)                    BIT_ADDR(GPIOB_ODR_Addr, n)
#define PBin(n)                     BIT_ADDR(GPIOB_IDR_Addr, n)

#define PCout(n)                    BIT_ADDR(GPIOC_ODR_Addr, n)
#define PCin(n)                     BIT_ADDR(GPIOC_IDR_Addr, n)

#define PDout(n)                    BIT_ADDR(GPIOD_ODR_Addr, n)
#define PDin(n)                     BIT_ADDR(GPIOD_IDR_Addr, n)

#define PEout(n)                    BIT_ADDR(GPIOE_ODR_Addr, n)
#define PEin(n)                     BIT_ADDR(GPIOE_IDR_Addr, n)

#define PFout(n)                    BIT_ADDR(GPIOF_ODR_Addr, n)
#define PFin(n)                     BIT_ADDR(GPIOF_IDR_Addr, n)

#define PGout(n)                    BIT_ADDR(GPIOG_ODR_Addr, n)
#define PGin(n)                     BIT_ADDR(GPIOG_IDR_Addr, n)

#endif
