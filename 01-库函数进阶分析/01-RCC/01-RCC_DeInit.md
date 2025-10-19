@author 巷北  
@time 2025.10.18 19:09 
# 简述
- 感觉时钟这块还是有些虚.想了想,可能是时钟这块,内部已经写好了,自动初始化的,不用自己主动去写,只能了解基础知识.  
- 根据实验,有自个自定义时钟的方式,所以专门记录一下内部函数.

- [原函数](#原函数)
- [RCC](#rcc寄存器)
- [函数解读](#函数解读)
## 原函数
~~~C
void RCC_DeInit(void)
{
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
#ifndef STM32F10X_CL
  RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
  RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif /* STM32F10X_CL */   
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#ifdef STM32F10X_CL
  /* Reset PLL2ON and PLL3ON bits */
  RCC->CR &= (uint32_t)0xEBFFFFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x00FF0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;      
#else
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;
#endif /* STM32F10X_CL */

}
~~~
- 这是原始函数.内部的寄存器还有没分析.我们根据函数执行内容,逐步分析.然后结合手册,看看每个寄存器所干的事,理解一下实现原理.
## RCC寄存器
~~~C
typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t APB2RSTR;
  __IO uint32_t APB1RSTR;
  __IO uint32_t AHBENR;
  __IO uint32_t APB2ENR;
  __IO uint32_t APB1ENR;
  __IO uint32_t BDCR;
  __IO uint32_t CSR;

#ifdef STM32F10X_CL  
  __IO uint32_t AHBRSTR;
  __IO uint32_t CFGR2;
#endif /* STM32F10X_CL */ 

#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)   
  uint32_t RESERVED0;
  __IO uint32_t CFGR2;
#endif /* STM32F10X_LD_VL || STM32F10X_MD_VL || STM32F10X_HD_VL */ 
} RCC_TypeDef;
~~~
- 昨天分析的时候说了,只分析`APB2ENR`(其实也没有完全分析),今天结合`RCC`来详细分析一下吧.
- `CR`是一个控制寄存器.共`32`位,但并不是每位都有用,而且这里的位,跟`GPIO`的`Pin`脚位整齐划分也不一样,有的`1`位,有的多位,分别操控着`RCC`.具体分配可以看手册,我等着后续分析函数的时候,再来分析.
- `CFGR`是时钟配置寄存器.我大体看了看,是根分频有关.
- `CIR`是时钟中断寄存器.看到中断,应该懂了.我这里也不多说了.
- `APB2RSTR`,`APB1RSTR`是对这俩总线上的外设复位的寄存器.其中`APB2`是使用了低`16`位,高`16`位没有使用.而`APB1`占满了,当然中间也有保留位.
- `ENR`是时钟使能寄存器,这里不多说了.
- 后面那来俩寄存器也就不说了.
- 感觉困惑的点,是前面这么多寄存器,不知道如何先使用.虽然系统帮我们初始化了,我们只需要操作`ENR`寄存器,直接使能就行,但仍感觉十分空虚...

## 函数解读
- 第一句是使能`HSI`内部高速时钟.手册里有.
- 复位系统总线和 `MCO` 输出配置，确保 `CFGR` 回到默认状态.
- 算了,还是不分析了.我们知道这个函数起的作用就行(这些寄存器的位,划分的没有逻辑,并不像`GPIO`那样条理,所以打算就此放过.知道它有这些寄存器即可).
- 放过放过.