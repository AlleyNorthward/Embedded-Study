@author 巷北  
@time 2025.10.17 22:15
# 简介
这部分代码比较长哈,但是`GPIO`底层硬件原理已经彻底分析过了,这里感觉问题不是太大.理解之后,就会好很多的.

- [函数总览](#函数总览)
- [硬件原理](#硬件原理)
- [参数分析](#参数分析)
  - [参数一](#参数一)
  - [参数二](#参数二)
- [寄存器分析](#寄存器分析)
- [代码分析](#代码分析)
  - [宏观思想](#宏观思想)
  - [源码拆解](#源码拆解)
- [硬件反馈](#硬件反馈)

## 函数总览
~~~C
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));  
  
/*---------------------------- GPIO Mode Configuration -----------------------*/
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
    /* Check the parameters */
    assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
    /* Output mode */
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
/*---------------------------- GPIO CRL Configuration ------------------------*/
  /* Configure the eight low port pins */
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* Get the port pins position */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding low control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* Set the corresponding ODR bit */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOx->CRL = tmpreg;
  }
/*---------------------------- GPIO CRH Configuration ------------------------*/
  /* Configure the eight high port pins */
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* Get the port pins position */
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding high control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
        /* Set the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
}
~~~
- 逻辑部分,我觉得应该不是问题,主要问题是,寄存器赋值操作不太熟悉,还有就是内部的一些参数,不知道什么意思.
- 感觉细细拆解下来,应该也不是问题,慢慢来,问题不大.
## 硬件原理
- `GPIO`硬件原理之前分析过了,这里不再重复.
## 参数分析
### 参数一
- `GPIO_TypeDef* GPIOx`参数这一块,太熟悉了.
~~~C
typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
} GPIO_TypeDef;
~~~
- 进入可见`GPIOx`的这么多寄存器.十分熟悉吧?前两个是低位,高位配置寄存器,每`4`位一组,`IDR`,`ODR`似乎是读写寄存器.`BSRR`是置位/重置位寄存器,共高低两组.`BRR`是`BSRR`高位简化版寄存器.`LCKR`是配置锁寄存器吧,不熟悉.
- `GPIOx`有下面几个:
~~~C
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)
~~~
- 这些存储着对应基地址(GPIOx),每个基地址都有对应的寄存器,寄存器又按位划分出`Pin`脚对应配置.
### 参数二
- `GPIO_InitTypeDef* GPIO_InitStruct`
- 这个分析过寄存器配置`led`后,似乎也变得很明确了.我们也来分析一下.
~~~C
typedef struct
{
  uint16_t GPIO_Pin; 
  GPIOSpeed_TypeDef GPIO_Speed; 
  GPIOMode_TypeDef GPIO_Mode;   
}GPIO_InitTypeDef;
~~~
- 这里可以知道,给某管脚配置速度与模式
- 其中模式结构体如下:
~~~C
typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;
~~~
- 关于模式结构体,我觉得有些问题.之前硬件部分分析,速度和模式需要`4`位二进制数.可是这里给的是`8`位二进制数.跟我的理解有冲突.所以现在先不分析,接着往下看.
~~~C
#define GPIO_Pin_0                 ((uint16_t)0x0001)  
#define GPIO_Pin_1                 ((uint16_t)0x0002)  
#define GPIO_Pin_2                 ((uint16_t)0x0004)  
#define GPIO_Pin_3                 ((uint16_t)0x0008)  
#define GPIO_Pin_4                 ((uint16_t)0x0010)  
#define GPIO_Pin_5                 ((uint16_t)0x0020)  
#define GPIO_Pin_6                 ((uint16_t)0x0040)  
#define GPIO_Pin_7                 ((uint16_t)0x0080)  
#define GPIO_Pin_8                 ((uint16_t)0x0100)  
#define GPIO_Pin_9                 ((uint16_t)0x0200)  
#define GPIO_Pin_10                ((uint16_t)0x0400)  
#define GPIO_Pin_11                ((uint16_t)0x0800)  
#define GPIO_Pin_12                ((uint16_t)0x1000)  
#define GPIO_Pin_13                ((uint16_t)0x2000)  
#define GPIO_Pin_14                ((uint16_t)0x4000)  
#define GPIO_Pin_15                ((uint16_t)0x8000)  
#define GPIO_Pin_All               ((uint16_t)0xFFFF)   
~~~
- 这是`Pin`脚,分析一下,还是掩码,且是`16`位二进制数.具体怎么操作,还需要去看函数具体原理.
~~~C
typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;
~~~
- 这是速度,发现是个枚举.这么来看,前面的`8`位二进制数,可能有对应的运算,从而转换成`4`位二进制数.
- 还没有分析代码,将上述内容贴给了`ai`分析后,果然变成了`4`位二进制数.当然,这是`ai`说的,具体逻辑还需要分析源代码.另外,关于模式与速度的`4`位二进制数,还需要结合手册,详细分析.
## 寄存器分析
- 关于`GPIO`寄存器,之前分析过了,这里不再重复.这里主要分析的是`CNF`和`MODE`的关系,这样便于下面对代码的分析.
- `CNF`对应的是输入或输出.何时输入呢?何时输出呢?也很简单.
  - 当`MODE==00`时`CNF`为输入模式.其中`00 01 10`分别对应模拟输入,浮空输入,上拉/下拉输入模式,`11`保留.
  - 当`MODE>00 即01 10 11`时,为输出模式.其中`00 01 10 11`分别为推挽输出,开漏输出,复用推挽,复用开漏.
- `MODE`一方面控制输入输出模式,一方面决定输出速度(输入没有速度).其中`00 01 10 11`分别代表着输入模式, 输出模式(最大10MHZ),输出模式(最大2MHZ),输出模式(最大50MHZ).
- 复位状态(初始态),`CRL`寄存器初值为`0x44444444`,其中`4`是`0100`,即输入模式,且为浮空状态.
- 有了上述拆解,那么下面的代码分析,相对可能就会容易很多了.
- 再补充一下吧.
  - `IDR`,是`Input Data Register`,输入数据寄存器,也就是读取引脚实际电平输入(外部信号的电平状态)`IDR`只读不写.
  - `ODR`,是`Out Data Register`, 输出数据寄存器.所谓的输出,确实是向外界输出,但同时,也会将对应信号传递给`cpu`.那么谁控制`ODR`呢?没错,就是`BSRR`和`BRR`.输入输出模式下`ODR`都有重要作用.
## 代码分析
- 整个代码的逻辑其实十分清晰.
- 不过由于内部使用指针,十六进制,`& |= <<`等运算符,掩码,标志位等等很多概念,当然,还有f但知识,但凡有一点不会,几乎无法进行下去.
- 我上面铺垫了很多,之前基础也分析了很多,软件层面也剖析了很多,所以,现在几乎能看懂各个表示的含义了.
- 那么,所谓的代码分析,也就仅仅变成逻辑分析了.掌握了逻辑分析,就可以自定义初始化`GPIO`了,这样对于深入理解硬件知识,很有帮助.
### 宏观思想
- 整体上,是将寄存器`CRL`和寄存器`CRH`分隔,也就是将高位`Pin`脚和低位`Pin`脚分开,取其一初始化.
- 内部是先找到配置位,然后分析是不是输入模式,是的话,就配置对应寄存器,不是的话就直接跳过.
- 最后给`CRL`(或`CRH`)寄存器赋值.
- 说的十分简单,我们接下来详细拆解吧.
### 源码拆解
- 默认的输入为`PB5`,推挽输出,`50MHZ`的情况.
~~~C
currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
{ 
  /* Check the parameters */
  assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
  /* Output mode */
  currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
}
~~~
- `GPIO_Mode`,我们之前说过了,是`8`位二进制数.
- 第一句的`0x0F`,就是获取低`4`位数.那么高`4`位是用来干什么的呢?
- 我分是判断位,`ST`公司添加的.用来判断输入还是输出的.后面有提示,这里先不说了.
- 推挽输出对应的`GPIO_Mode`是`GPIO_Mode_Out_PP = 0x10`.这里结构体内部赋值,进一步说明`ST`公司自己添加的,方便函数书写.
- 所以初始`currentmode = 0x00`.如果是其它模式,不是正好为`0x00`的.
- 接下来进入`if`语句了.其中的`0x10`,之前强调过了,这是判断位,判断第`4`位是否为`1`.
- 这里我分析了一下,其实就是`GPIO_Mode`高位为判断位,第`4`位为`1`,必然是输出模式,为`0`则是输入模式.所以这里只需要判断第`4`位(`0x10`)即可.
- 如果是输出模式,就进入循环,并且赋上输出速度.
- 综合来看,输入模式,就直接获取后`4`位,作为当前模式(`currentmode`),如果为输出模式,第`4`位置`1`,进入判断,并且给速度赋值.
  - 仔细对照了一下,确实没有任何问题.
  - `GPIO_Mode`中,高`4`位确实是用来区分输入输出模式的.后`4`位代表`CNF MODE`的.
  - 其中,输出模式只需要将第`4`位置`1`即可,输入需要置`0`.但输入彼此之间还需要区分,这样需要将高`4`位其他位置置`1`,分别表示模拟输入,浮空输入,上拉,下拉输入.不过上拉还是下拉,其`CNF MODE`是一样的,区别就是高位不同.
  - 输出模式呢,是`MODE`位置`00`,不过通过判断语句,进入后会置该位.
  - 软硬件逻辑是闭环的,一点问题都没有.
~~~C
if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
{
  tmpreg = GPIOx->CRL;
  for (pinpos = 0x00; pinpos < 0x08; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
    if (currentpin == pos)
    {
      pos = pinpos << 2;
      /* Clear the corresponding low control register bits */
      pinmask = ((uint32_t)0x0F) << pos;
      tmpreg &= ~pinmask;
      /* Write the mode configuration in the corresponding bits */
      tmpreg |= (currentmode << pos);
      /* Reset the corresponding ODR bit */
      if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
      {
        GPIOx->BRR = (((uint32_t)0x01) << pinpos);
      }
      else
      {
        /* Set the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
        }
      }
    }
  }
  GPIOx->CRL = tmpreg;
}
~~~
- 这里配置的是低`Pin`脚位.逐步分析一下.
- 初始判断语句,就是获取低`Pin`脚位.如果有`1`,表明是当前`Pin`脚,进入循环.
- 初始`tmpreg`是获取当前寄存器的值.之前说了,初始值为`0x44444444`.
- 计入循环,就是分析低位的哪个`Pin`脚,用`pinpos`表示.
- 我们一开始说的,分析的是`PB5`,所以`pinpos`为`5`,那么pos为`100000`.
- `currentpin`其实就是分析到底是不是当前`Pin`脚,如果是的话,进入判断.
- 判断中,`pos = 5 << 2`,这一句其实非常之好.为什么呢?
  - 首先,`pos`并不是掩码,也不是地址,而是指当前`Pin`脚,在`CRL`中的位置.
  - 因为`CRL`寄存器的每个`Pin`脚占`4`位,所以`Pin5`对应的是`[23:20]`.其实`pos`就是`5*4`.
  - 这里采用左移两位的方式,来计算`pos`.本质上,`pos = 5*4 = 5<<2 = 20`.
  - 所以,这里的`pos`相当于`20`,就是我们接下来移位的位数,这样我们可以直接操作`CRL`的`[23:20]`位,也就是直接配置`Pin5`.
- 接下来是将`tmpreg`中`[23:20]`位赋空,然后写入`currentmode`(关于`currentmode`上面分析过了,一点逻辑毛病也没有,就是存储着当前运行模式)
- 然后就是配置输入模式了.如果不是输入模式,直接给`CRL`赋值(`tmpreg`),然后语句结束.
- 如果是输入模式,那么判断是否是下拉输入.是下拉输入的话,则将`BRR`(应该是`BSRR`的高`16`位)的`pinpos`位置`1`(`BRR`寄存器调节低电平输出的,所以下拉输入是输入低电平,符合硬件知识分析)
- 如果不是下拉输入,则继续判断是否是上拉输入.使得话,则将`BSRR`寄存器对应位置置`1`,输出高电平.
- 另一个则是一样的.
## 硬件反馈
- 软件部分分析完后,硬件方面有了更深层次的理解,所以需要重新梳理一下.
- 基本线路是:`flash`烧录程序后,会以机器指令形式存储 -> `cpu`执行程序,运算/分析 -> `cpu`通过各种寄存器向指定地址发送运算结果 -> 该地址外设寄存器收到结果,并更新信息 -> 外设寄存器根据信息做出指定动作.
- 当然,`cpu`可以读取某地址的寄存器内容,信息也是通过总线传递了.另外,中断机制,也会向`cpu`发送请求信号.
- 对于点亮`led`,运行过程是这样的:时钟使能,`GPIO`初始化,并且确定了输出模式,输出速度.然后,我们通过`BSRR`,`BRR`,可以操作`ODR`寄存器,在引脚上输出高低电平,从而熄灭或点亮`led`.
- 对于控制`key`,`GPIO`初始化后,设计的模式是上拉输入或者下拉输入,这些信息存放到`cpu`中.当`key`按下,有电平输入,信息存放到`IDR`中.`cpu`不会随时监听,需要时会读取`IDR`的值,判断`key`是否按下.
- 关于`IDR`寄存器,只有低`16`位存放`Pin`脚电平信息,高`16`位置空,只能读.`ODR`一样,但是可读可写.
- 所以这么来看,`IDR`与`cpu`有联系,而`ODR`一般通过`BRR BSRR`来间接修改电平,从而做出输出电平的动作.
- 不过,我们明明可以直接操作`ODR`,为什么非得要通过`BRR BSRR`来间接操作呢?
  - 我们可以通过`|= &=`来直接操作`ODR`,但是问题是,这样会生成三条机器指令(读,改,写),指令之间有时间差,如果此时发生中断,而中断程序修改了`ODR`别的位,可能发生意外.
  - 而`BRR BSRR`是直接写(直接赋`=`),而且也强调过了,这是只写寄存器,写完后清空,不会影响`ODR`其它位,没有中断风险,十分安全的原子级的位控制寄存器(原子级是依次不可分割的操作).
