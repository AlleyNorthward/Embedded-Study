@author 巷北  
@time 2025.10.17 21:14
# 简介
- 很经典的一个函数,几乎是软件端使用的第一个函数.
- 之前也解读过,但是没有深入,如今深入解读一下

- [函数总览](#函数总览)
- [硬件原理](#硬件原理)
- [参数分析](#参数分析)
  - [参数一](#参数一)
  - [参数二](#参数二)
- [寄存器分析](#寄存器分析)
- [代码分析](#代码分析)

## 函数总览
~~~C
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}
~~~
- 函数很简单,我这里弄主要是先弄个架构,方便后续好参考架构
## 硬件原理
- 这部分前面说过很多了,这里不再重述.
## 参数分析
### 参数一
- `RCC_APB2Periph`.
- 溯源发现,其对应可能宏如下所示:
~~~C
#define RCC_APB2Periph_AFIO              ((uint32_t)0x00000001)
#define RCC_APB2Periph_GPIOA             ((uint32_t)0x00000004)
#define RCC_APB2Periph_GPIOB             ((uint32_t)0x00000008)
#define RCC_APB2Periph_GPIOC             ((uint32_t)0x00000010)
#define RCC_APB2Periph_GPIOD             ((uint32_t)0x00000020)
#define RCC_APB2Periph_GPIOE             ((uint32_t)0x00000040)
#define RCC_APB2Periph_GPIOF             ((uint32_t)0x00000080)
#define RCC_APB2Periph_GPIOG             ((uint32_t)0x00000100)
#define RCC_APB2Periph_ADC1              ((uint32_t)0x00000200)
#define RCC_APB2Periph_ADC2              ((uint32_t)0x00000400)
#define RCC_APB2Periph_TIM1              ((uint32_t)0x00000800)
#define RCC_APB2Periph_SPI1              ((uint32_t)0x00001000)
#define RCC_APB2Periph_TIM8              ((uint32_t)0x00002000)
#define RCC_APB2Periph_USART1            ((uint32_t)0x00004000)
#define RCC_APB2Periph_ADC3              ((uint32_t)0x00008000)
#define RCC_APB2Periph_TIM15             ((uint32_t)0x00010000)
#define RCC_APB2Periph_TIM16             ((uint32_t)0x00020000)
#define RCC_APB2Periph_TIM17             ((uint32_t)0x00040000)
#define RCC_APB2Periph_TIM9              ((uint32_t)0x00080000)
#define RCC_APB2Periph_TIM10             ((uint32_t)0x00100000)
#define RCC_APB2Periph_TIM11             ((uint32_t)0x00200000)
~~~
- 注意,右侧是十六进制编码,对应的是`2^0 2^2 2^2...2^21`,分别是`RCC`寄存器的`0-21`位,不过`1`位(`2^1`)保留了,我也不知道为啥.
- 我们注意到,`RCC_APB2Periph_GPIOB`的掩码值是`0x00000008`,就是十进制的`3`,跟我们之前分析寄存器操作`led`相符合.
- 所以这些内容呢,就是`APB2`外设上对应的掩码值,也就是写给寄存器的值,就是指针指向某地址后'写'的值.
- 我们分析的这个函数,就是使能`APB2`总线上外设时钟的函数,所以这里汇总的就是`APB2`
### 参数二 
- `FunctionalState NewState`
- 分析后,源代码如下:
~~~C
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
~~~
- 这个就是一个枚举方式.怎么说呢,我也模仿过了,不难理解,不详细解释了.
## 寄存器分析
- 回看原函数,我们发现有这么个操作`RCC->APB2ENR |= RCC_APB2Periph`,跟我们之前直接操作`APB2ENR`有些不同.
- 其实原理就是,`RCC`是个结构体,将所有的`RCC`相关的寄存器,都存放到了这个结构体里.
- 进入`RCC`后,我们发现其是这样的:
~~~C
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
~~~
- 再进入`RCC_Typedef`后,发现是这样的:
~~~C
typedef struct
{
  __IO uint32_t CR;           // 偏移0x00
  __IO uint32_t CFGR;         // 偏移0x04
  __IO uint32_t CIR;          // 偏移0x08
  __IO uint32_t APB2RSTR;     // 偏移0x0C
  __IO uint32_t APB1RSTR;     // 偏移0x10
  __IO uint32_t AHBENR;       // 偏移0x14
  __IO uint32_t APB2ENR;      // 偏移0x18
  __IO uint32_t APB1ENR;      // 偏移0x1C
  __IO uint32_t BDCR;         // ...
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
- 下面的宏,就不分析了,结构体内部存储的,就是所有`RCC`相关的寄存器.
- 这些寄存器,我们就只看`APB2ENR`(因为其它的没用过(其实有些看名字就知道操作是类似的)).
- 结构体内部元素顺序是确定的.因为对于`RCC`指针而言,其地址就是首地址,结构体内部地址是基地址顺次偏移的(代码注释中标注了)
- 所以`RCC->APB2ENR`,就是专门指向了该寄存器地址.`0x18`也与我们分析`led`寄存器点亮时的地址相同.
## 代码分析
- 代码没啥好分析的,就是简单的逻辑判断,然后再进行相关位运算,就可以使能对应外设.
- 深入明白原理后,可以直接`RCC->APB2ENR |= RCC_APB2Periph`,曾倩效率.
- 拆解完后发现,自己重新宏定义的宏名字,简直一坨.