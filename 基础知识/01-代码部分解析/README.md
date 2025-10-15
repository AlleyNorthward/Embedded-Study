@auther 巷北  
@time 2025.10.13 10:54
# 简介

这部分主要是说说代码问题.其实也不是代码,而是C语言的相关语法.对着写,虽然能大致明白什么意思,不过不仔细研究一下肯定也是不行的,仍需要深究一下,这样后面才不会云里雾里的.  

- [目前问题](#目前问题)
- [学习总结](#学习总结)
- [C语言问题](#C语言问题)
    - [指针](#指针)
        - [基础认识](#基础认识)
        - [进阶](#进阶)
            - [(int*) p](#intp)
			- [空指针](#空指针)
			- [函数指针](#函数指针)
			- [指针函数](#指针函数)
			- [宏定义指针](#宏定义指针)
		- [嵌入式指针应用](#嵌入式指针应用)
			- [小试牛刀](#小试牛刀)
			- [结构体指针](#结构体指针)
- [库函数映射关系](#库函数映射关系)
    - [基础知识](#基础知识)
        - [寄存器](#寄存器)
        - [掩码(`mask`)](#掩码mask)
        - [&|!运算符](#运算符)
    - [库函数知识](#库函数知识)
        - [类型](#类型)
        - [结构体变量分配](#结构体变量分配)
    - [库函数分析](#库函数分析)
        - [举例1](#举例1)
        - [举例2](#举例2)
        - [举例3](#举例3)



## 目前问题
- 宏定义后,类型问题
- 指针问题
- 变量问题(u8,u16等)
- 命名规范问题
- 函数理解
- 管脚地址问题
- C语言操作方法(~,|等)

> 似乎就这么多.等后面遇到了,再进行添加吧.下面将会解决这些问题,但是,并不是按照上面的顺序来解决的,而是按照实验所做过的顺序来的(也不一定,想怎么写就怎么写吧.不过疑问肯定都会解决的.).目前已经做到实验十了,这里先从实验四开始慢慢地分析.另外,前三个实验,有两个模版没必要说,还有一个直接操作寄存器,其实也就是对管脚地址的理解,偏向底层,这里先不分析,等后面对这些中间层的东西掌握明白后,再去回看一下就可以.  

## 学习总结
- 目前为止(实验十),这部分的内容,跟纯软件代码学习这部分不太一样.
    - 后者(纯软件)我总结的是,先理解,再去多写代码,写代码的过程中,排错并加深理解.
    - 前者(嵌入式)目前总结的是,直接跟着视频写代码,写完代码后,再去理解.因为底层内容太乏味,本来不会的话,看一遍视频,也是纯浪费时间,跟没看差别不大(可能计算机学习,更偏向于软件部分吧.).
    - 不论前者还是后者,共性是一样的,千万不要背代码,写多了就自然而然的.
- 嵌入式,先跟着视频写代码,后面理解的关键是,建立映射关系.这个函数,对应着操作硬件哪个部分,理清之后,再去看相关知识,就不会这么乏味了.了解到相关知识后呢,又会反馈到软件层面,对相关函数的使用也就更明确了.

> 总结来看:
> - 后续实验,直接跟着写代码
> - 得到硬件部分反馈后,再去ai了解
> - 然后再看视频(十分明确的话,不看视频也没关系)
> - 最后,建立函数与硬件部分映射关系,清晰地知道,操纵这个函数,实际是操纵的硬件哪个部分.

## C语言问题
关于C语言的问题,肯定是很多的,而且是需要随时整理的.有了理解就会在此写写.

### 指针
指针绝对是个大问题.因为刚学的时候,没有理解.也不是没有理解吧,是缺少实际应用,很难建立自己的认识. 那么这次,我们就来攻克它吧,因为对于嵌入式而言,确实是比较底层的了,对于相关地址的操作也是非常多的,所以不论如何,都需要有自己独立的认识.

#### 基础认识
***注意***:这部分是必须要理解的.理解之后,才能往下深入.
~~~C
int main(){
	int x = 42;
	int* p;
	p = &x;
	printf("%d, %d, %d", p, *p, x);
	return 0;
}
~~~
- 一般,我们会写`int *p`,但是我上面写的是`int* p`.这么写的优劣,我下面会专门强调.
    - 我的写法,强调的是指针类型**变量**`p`,我这里强调的`p`,是个变量,其次,才是指针类型.
    - 为什么这么强调呢?下面再来说说.
        - 普通类型变量,例如`int x`也好,其它的也罢,后续我们都会对变量`x`进行操作,非常自然.
        - 可是我自己,如果这么定义了`int *p`,我会很自然地认为`*p`是一个整体,所以非常容易搞混(比如操作`p`还是`*p`啊等等),这样不利于真正理解指针.
        - 所以,为了专门强调`p`首先是个变量,其次才是指针类型,于是,才有了上述定义方式`int* p`.
        - 这两种方式, C语言解读上没有区别,但是对于我个人的理解,却天差地别,所以还是一定要做出区分的.
    - 定义`int* p`之后,就要知道,我们操作的变量是`p`.由于它是一个指针类型,那么对于`int`类型变量`x`而言,我们不能直接`p = x`这么赋值,而是应该将`x`的地址赋值给`p`.于是,就有了`p = &x`.
    - 所以,`&x`是什么类型呢?没错,就是`int*`类型, 相同类型才能直接赋值.
    - 那么`*p`又是什么呢?这里的`*p`,其实就是解引用的的意思,获取当前地址存储的信息的.由于我们知道,`p = &x`, 那么`*p = *&x`,也就是`x`.
    - 所以说,定义时的`int*`, 代表的是指针类型变量.而我们使用`*p`,就是解引用操作.注意,解引用操作,目前只能应用于`int*`变量,而不能应用于`int`类型.
- 那么,假如,我有个变量`h`, 如果它是`int`类型,不能使用`*h`,不过可以使用`&h`取地址.而如果它是`int*`,则可以使用`*h`.
- 我自己定义的方式,就是便于理解,专门强调`p`只是一个变量,只不过是`int*`类型的,我们需要操作的仍是`p`,操作`*p`的话就是解引用,获取值.
- 这么定义(`int* p`)的坏处是什么呢?如果,有如下定义方式:`int* p, b`, 其中,`p`是指针类型变量, 而`b`是`int`类型变量,所以这么做会产生混淆.
> **总结**:`int* p`是指针类型变量.对于`int x`,`&x`也是`int*`类型变量.所以可以直接如下赋值`p = &x`.而`*p`是解引用,相当于`*&x`,也就直接等于`x`.所以,`*`是取值,而`&`是取地址.

> 定义时的`int* p`的`*`和使用时的`*p`的`*`,含义不同.前者为声明中的一部分,后者为解引用操作.

> 最终,`int* p`, 我们可以取其值,使用`*p`, 对于`int x`,我们可以取其地址,也就是`&x`.这也就是`int*`与`int`之间转换的方式.

> 对于`int* p`, 我们不仅可以对它取值,也可以取地址(`p`变量本身地址).也就是`*p`,`&p`一起使用.而对于`int x`, 我们只能取地址, 也就是`&x`,而不能取值,`*x', 因为`*`取值操作,只能对指针使用.
#### 进阶
进阶这部分慢慢弄吧,也没必要专门搜集,意义不大.我就将嵌入式中遇到的一些指针操作放进来,便于理解吧.不过前面的,我还是会放一些我自己曾经不太理解的问题.

##### (int*)p

下面代码是我现改的.请问有错误吗?
~~~C
int main(){
	int x = 42;
	int a;
	(int*) a;
	a = &x;
	printf("%d, %d, %d", a, *a, &x);
	return 0;
}
~~~
**答案**:有错误,编译器不通过.
- `a`是`int`类型,虽然有`(int*)`强制转化,但是无论如何,我们也无法将`a`强制转化,它仍然是`int`类型.不过我们可以给其赋值,也就是如下操作:
~~~C
int main(){
	int x = 42;
	int a;
	int* p = (int*) a;
	p = &x;
	printf("%d, %d, %d", p, *p, &x);
	return 0;
}
~~~
- 需要注意,这样会有潜在风险,`int`为四个字节,而指针为八字节,所以不建议这么操作.但是在`keil`,`ARM`芯片中,是32位,都是四字节,不会产生问题,所以标准库中,会有很多类似操作.举下面这个例子:
~~~C
int main(){
	int x = 42;
	int a_int = 0x1234;     
	int* p = (int*)a_int;   
	printf("%p\n", (void*)p);
}
~~~
- 还是解释一下吧.`a_int`,不论其是几进制,都是`int`类型.所以`0x1234`虽然是十六进制,但是仍然为`int`类型,我们不能直接赋值给指针.所以,我们可以将其强制转化为指针类型变量,这样就能直接赋值了.后面的`%p`是为了输出十六进制.`(void*)`是消除警告,知道这么操作就行.

**另**
上面的例子,是将整型,强制转化为整型指针,还有种情况是指针的强制类型转化.在课本`P181`页.我这里就简单说说,能看明白就看明白,看不明白也没事,实际操作时遇到,产生疑问后再去解决,印象更加深刻.

~~~C
int main(){
    int n = 3, * p;
    double* q;
    void* gp1, * gp2;
    gp1 = &n;
    p = (int*) gp1;
    printf("%d, %d", *p, *gp1);
	q = (double*) gp1;
    return 0;
}
~~~
- 如上代码,`gp1`是`void*`类型,`p`赋值时,类型不匹配,可以强制转化一下,然后赋值.
- 后面输出的`*gp1`就不对了.因为前面也说了,`(int*) gp1`,是赋值操作,并不会将`gp1`强制转化,它`仍然为(void*)`类型.
- 后面的`q`的赋值也不对.因为`void*`虽然是通用指针,但是当它指向`int`类型数据后,只能强制转化为`(int*)`,而不能转化为`(double*)`.虽然不会报错,但是输出结果不符合预期.
- 还有其它可能,比如`int`型指针强制转换为`double`型指针.但是这个做似乎意义不大.因为`int*`指向的是`int`数据,转换为`double*`,仍然无法访问.
> 总结来看,指针之间的强制转化,需要循序指针类型与普通类型相匹配,否则转化没有意义.

##### 空指针
代码示例如下
- 示例1
~~~C
int f(...){
	int* p, n = 3;
	*p = 2;
	...
}
~~~
这个肯定是错误的.因为指针`p`并没有指向合法变量,就直接赋值.
- 示例2
~~~C
void swap(int* p, int* q){
	int t = *p;
	*p = *q;
	*q = t;
}

int main(){
	int p, n = 3;
	swap(&p, &n);
}
~~~
这样做是不安全的.因为`p`未赋值,所以会造成意想不到的情况.如果直接传入`p`,很明显的错误,就是类型不匹配.

##### 函数指针

- 刚开始学的时候,确实不懂,毕竟也缺少实际应用.写了那么多`python`之后,这部分变得很明确了.`python`高级设计模式,看了很多,跟着`manim`也学了很多.突然领悟的地方是,看着个类,传入了个类名参数.当时思考为什么传入类名,而不是这个类的实例化对象呢?因为这样可以自主确定该类的生命周期,需要使用的时候,可以类名()来实例化.  
- 可是这跟函数指针有什么关系呢?  
- 很有关系.因为在`python`中,将函数,类等等赋予变量,很容易,毕竟无需类型要求.可是在`C/C++`中,这种操作就不行.我们想将函数,类赋予某变量,或者想延缓其生命周期,仍需赋予某变量,那么对于这个变量而言,是什么类型呢?函数指针类型.这也是其存在的意义.
- 当前,`C/C++`的设计方面,涉及的很少,所以函数指针在平时刷题时,也都很少用到(其实也没用过).但是有了`python`的实际应用,也知道了它的意义,所以理解起来也就更加轻松了.

~~~C
int foo() { return 42; }

int (*p)();  // 函数指针
p = foo;     // 合法
int result = p(); // 调用函数
~~~

- 上面是`ai`的例子,知道就行.等后续需要的时候,再专门详细研究就可以.
- `int (*p)` 和 `int* p` 含义是一样的.而`int (*p)()`这样才代表函数指针.
- 下面再贴上一个简单应用吧.

~~~C
int max(int a, int b){
    return (a > b) ? a : b;
}
int min(int a, int b){
    return (a < b) ? a : b;
}
int compute_extreme(int a, int b, int (*func)(int, int)){
    return func(a, b);
}
int main(){
    int a = 3;
    int b = 4;

    int c = compute_extreme(a, b, max);
    int d = compute_extreme(a, b, min);

    printf("%d, %d", c, d);

    return 0;
}
~~~
- `compute_extreme()`函数,有很多实现方式.比如,可以传入一个`flag`,根据其值,判断调用`min()`还是`max()`.不过这样的问题,需要写判断语句,相对于这个而言,不够简洁.
- 当然,也可以直接调用函数,不用再定义`compute_extreme`.因为我这个函数十分简单,可以不用定义.但如果当项目十分庞大,需要复杂的`comopute_extreme`的时候,函数传参的意义十分有必要的.
- 这个例子也能很明显地看出来生命周期的意义.我们将`max`或者`min`作为参数传入,可以随时通过`func()`调用,不用担心其他问题.

##### 指针函数

这部分任重道远,先放个例子,后面实际应用的时候再说吧.
~~~C
#include <stdio.h>

int* getPointerToInt() {
    static int x = 10; // 注意：必须是静态变量，否则返回局部变量地址非法
    return &x;
}

int main() {
    int *p = getPointerToInt(); // 调用指针函数
    printf("%d\n", *p);         // 输出 10
    return 0;
}
~~~

嗨,我以为什么呢...就是返回值是个指针.比如想返回数组,就需要返回值为指针类型.相较于函数指针,难度也不是很大.

##### 宏定义指针
因为在嵌入式应用中,其库都是将指针通过宏的方式定义好的,并不是传统的定义方式,所以这里专门来分析一下.
~~~C
#define MY_RCC_BASE				0x1234
#define Test_RCC                (*(int*)MY_RCC_BASE)
int main(){
    printf("%d", Test_RCC); // 不行,卡住.
    /*
        原因:
            MY_RCC_BASE,确实就是一个值,0x1234,转化为十进制也好,二进制也罢,都是等价的.
        而且宏定义的时候,并没有定义类型,所以这一步没有任何问题.
            如果添加强制类型转换,则对于(int*)MY_RCC_BASE而言,就是在告诉C语言,0x1234不
        再是一个普通的数了,它现在是一个地址.
            而(*(int*)MY_RCC_BASE)就是在获取当前地址下的值.
            所以main中,我试图访问这个数,但是访问不了.原因就是这个地址是电脑中真实存在的
        地址,也就是在告诉操作系统:我想去访问内存地址 0x00001234 处的 4 个字节,并把
        它解释成一个 int.
            但是程序只能访问 操作系统分配的内存区域(进程空间),0x1234是我们抽象出来的,
        一般情况下,操作系统会介入终止访问,所以才无法输出.
            但是这行代码,确实很好的模拟了嵌入式库中各种定义,也能更好地明白.
    */
    return 0;
}
~~~
为了更加真实地模拟,我们就用计算机真实存在的地址来举例.
~~~C
int fake_reg = 1234;
#define MY_RCC_BASE             &fake_reg
#define Test_RCC                (*(int*)MY_RCC_BASE)
int main(){
    printf("%d, %p, %p", Test_RCC, &Test_RCC, MY_RCC_BASE); 
    return 0;
    //输出结果:
    // 1234, 0000000000403010, 0000000000403010
}
~~~
- 我用`fake_reg`来抽象模拟.
- `(int*)`强制类型转化其实多余了,因为`&fake_reg`本身就是`int*`类型(前面说过了).但是没有去掉,就是为了模拟.
- 从输出结果来看,Test_RCC就是一个普通变量,不是一个指针变量.如果下面这种定义方式,就是指针变量了.
~~~C
#define Test_RCC			((int*)MY_RCC_BASE)
~~~
- 因为`*`就是取值的意思,给地址取值,赋值给某变量,那么这个变量其实就是对应的是这个值.而该变量的地址,与值的地址相同.所以从`printf()`也能看到,`&Test_RCC = MY_RCC_BASE`.
- 这样我后面嵌入式应用中,可能就说错了.
- 为了便于理解,我下面再贴一下`Test_RCC`为指针的情况.
~~~C
int fake_reg = 1234;
#define MY_RCC_BASE             &fake_reg
#define Test_RCC                ((int*)MY_RCC_BASE)
int main(){
    printf("%d, %p, %p", *Test_RCC, Test_RCC, MY_RCC_BASE); 
    return 0;
    // 输出同上
}
~~~
- 这样似乎就能区分了.
- 还有一个问题是,我发现无法对`Test_RCC`取值(`&Test_RCC`),这样会漂红.
- 这里其实就是宏定义指针跟普通指针定义之间的区别了.宏定义,其实就是直接替换(比如`*Test_RCC`替换后就是`*((int*)MY_RCC_BASE)`),并没有显式的左值(其实也就是没有实际的地址空间),所以不能直接取值.
- 上面说的指针,可以取值和取地址操作,而宏定义的指针,只能取值,而不能取地址.

#### 嵌入式指针应用
有了上面的基础后,这部分就比较容易理解了.这里还是举例子,实际应用的例子.不过是慢慢积累的,而不是一次性总结完的.

##### 小试牛刀
先来看看下面的宏定义
~~~C
#define GPIOA_BASE 0x40020000 
#define GPIOA_ODR (*(volatile unsigned int*)(GPIOA_BASE + 0x14))
~~~
有何区别?
- 对于`GPIOA_BASE`而言,它就仅仅代表的是`GPIO`的基地址,仅此而已,无法读写相关内容.
	- 需要注意的是,`stm32`是`32`位的,在`C`中,经常用`8`位`16`进制来表示其`32`位`2`进制数.
	- 另外,我们之前也专门强调过了,数据类型与进制数无关.所以`0x40020000`可以转换为对应二进制数,也可以转换为对应十进制数,含义都是一模一样的.只不过习惯上用十六进制来表示,因为确实容易读取.
- 结合前面的**宏定义指针**,很明确,`GPIOA_ODR`就是一个普通变量,其值就是`GPIOA_BASE + 0x14`下的值.其地址也就是`GPIOA_BASE + 0x14`.
- `GPIOA_ODR`本身并没有地址,这也是它与普通指针的区别.
##### 结构体指针
代码示例
~~~C
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR; 
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef*)RCC_BASE)
~~~
- 这里的GPIOA是一个结构体指针.
- 想对结构体内部变量进行读取操作,可以直接`GPIOA -> MODER = ?`操作.相当于`(*GPIOA).MODER = ?`.
- 注意,上面的`?`是值,还是地址?这是非常关键的.`->`其实就是访问变量`MODER`,所以`GPIOA->MODER`本身就是一个变量,并不是指针.
- `?`这里对应的其实是值.因为我们有数据类型(`uint32_t`),其实也就代表它有地址了.并且其地址,是基于`GPIOA`的地址获取的.比如,`MODER`的地址可能为`RCC_BASE + 0x20`,具体的要看芯片内部地址的划分了.
- 不过从`C`中怎么抽象划分地址的,我还没仔细看库,所以知道`GPIOA`是结构体指针,指向基地址`RCC_BASE`,其结构体内部的变量,已经按照基地址,分配好了本身的地址.
- 明白了.注意,其类型都是`uint32_t`,`32`位,四个字节.所以从上到下,每个变量相对于`GPIOA`地址偏移四个字节.虽然没有显式地规定,但是`C`的结构体决定了其地址这么分配.
> 有了这些先决条件后,再去分析库,就会好很多了.

## 库函数映射关系
关于这里的结构还没有想好,不过已经明白很多了,所以尽量把想说的点都说了.
### 基础知识
#### 寄存器
- 关于寄存器,我就简单说说吧,因为确实没有理解.
- 寄存器是CPU内部高速存储单元,软件通过它进行运算和控制,硬件通过它执行指令.
- 所以,寄存器相当于软件与硬件之间的桥梁.
- 我们操作`GPIO`,实际上就是将软件信息(二进制)传递给寄存器,从而操作寄存器当中的值(二进制),从而实现对`GPIO`的操作.
- GPIO寄存器(通常在外设寄存器地址空间中)存储了对应引脚的控制状态,写寄存器即改变引脚电平或模式.
#### 掩码(`mask`)
- 那么我们如何操作寄存器的值呢?
- 通过`mask`来操作.比如,我们知道某寄存器地址,它有对应的值,对应这硬件的某个状态.软件端,我可以通过指针访问这个地址,并且通过掩码,来修改这个值,从而改变硬件的状态.
- 掩码其实也是二进制值,在`C`中通过`8`位`16`进制来表示.
#### &|~运算符
- 有了掩码,如何跟寄存器的值做运算呢??没错,就是通过`&,|,~`,分别代表按位与,按位或,取反.哦对了,还有`^`,好像是按位异或.
- 这些运算符,可以|=,&= ~等赋值方式,修改寄存器内部某地址下的值,从而让硬件做出对应的变化.
- 不过这些底层的运算,标准库已经给我们封装好了,不用专门记忆.但是,知道对应过程,可以便于我们理解.
### 库函数知识
#### 类型
- 关于变量类型,我目前只知道`uint32_t`,和其他的结构体变量,其它的后续再说.
- 关于这个类型`uint32_t`,是地址类型,也是掩码类型.当然,有的掩码是`uint16_t`,等等.
- 那么如何区分我们需要操作的是地址还是掩码呢?
- 看宏定义,当出现`((...Typedef*)0x....)`时,是个结构体指针,结构体内部,对应着一系列变量.这些变量的地址,就代表着寄存器相关部位的实际地址.我们将掩码,通过运算符操作运算,就会修改这些变量的值,从而达到操控寄存器的目的.(关于结构体内部变量地址如何划分的,我们后面再说)
- 有时候函数传参,需要我们传`uint32_t`类型,那么大概率是相关掩码.有时候需要我们传+时,是个指针,函数内部会帮我们将相关掩码运算实现,从而达到操控寄存器的目的.当然,还有其它传参,这点不关注.
- 看了看,`u8`等,是上面的缩写.除此之外,还有`bool`(`FunctionalState`)类型,似乎就这么多.
#### 结构体变量内存分配
- 对于结构体内部变量,一般情况也是`uint32_t`类型.我们给其赋值,并不是赋值的地址,而是掩码.那么其地址如何分配的呢?
- 关于结构体指针,它一定指向某个地址,也就是寄存器的某个部分.结构体内部变量由于是`uint32_t`类型,占四个字节,所以,其变量从上到下会沿着初始指针指向的基地址偏移四位.最终地址就这么划分出来了.我们想操作内部的值,只需要指针访问改变就可以了.
- 可能是芯片设计吧,要不然不可能这么巧合.
#### 区分掩码和地址
- 赋值的,一定是掩码(或值),被赋值的,是变量,存在地址.
- 以`uintx_t`传参的,是掩码,以`((...Typedef*)0x....)`这种形式传参的,是指针,指针内部指向的,是变量,存在地址.
- 还有就是宏定义部分,`8`位十六进制数,大概率是地址,小于`8`位的大概率是掩码.
- 另外,宏名中带有`BASE`的,是地址,单独只有十六进制数值,却没有其它的(添加其它基地址, 名字不带有`BASE`的),大概率是掩码.
- 上面说的都不一定,经验之谈,具体问题具体分析.
- 下面说个例子吧.
~~~C
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BSRR = GPIO_Pin;
}
~~~
- 很明显,BSRR是具体变量,给其地址赋值,而GPIO_Pin是掩码.
- 这里也不是掩码,GPIO_Pin是值.因为没有`&|^`等运算符.
- 所以说,具体问题,具体分析,哈哈.

### 库函数分析
上面说了这么多,感觉也说完了.下面就结合实际,分析一下吧.还是只分析小灯的,其它的大差不差了.
#### 举例1
~~~C
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
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
- 这是一个APB2总线上的时钟控制函数.看参数,我们知道,前者`RCC_APB2Periph`是掩码,后者`NewState`是`bool`类型,相当于开关.
- 后面,我们看到,指针`RCC`指向其结构体变量`APB2ENR`,并且赋值了`RCC_APB2Periph`,从而达到使能或禁止时钟的目的.
- 接下来,我们去底层,看看变量`RCC_APB2Periph`和`NewState`.
~~~C
#define RCC_APB2Periph_GPIOB             ((uint32_t)0x00000008)
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
~~~
- 可以看到,基本符合我们的分析.上面的虽然是八位,但是明显没有`BASE`.下面的,很明显就是`bool`类型,用于判断的.
#### 举例2
~~~C
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));  
  ...
}
~~~
- 这个初始化函数,太长了,只贴出来部分.
- GPIOx,必然为指针,指向某地址,操控着某些变量.
- GPIO_InitStruct也是指针,也指向某地址,但是是否是寄存器地址呢?目前不得而知,得去判断一下.
- 溯源`GPIOx`.
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

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE) || \
                                    ((PERIPH) == GPIOF) || \
                                    ((PERIPH) == GPIOG))

#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
~~~

- 结合来看,这里要求我们我们传入指针,但是该指针,并不要求我们自己在外面控制,而是函数中帮我们赋值了.所以结合来看,这里其实就是要让我们传入待操作端口地址.
- 那么我们再来看看第二个参数吧.
~~~C
typedef struct
{
  uint16_t GPIO_Pin;             /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */

  GPIOSpeed_TypeDef GPIO_Speed;  /*!< Specifies the speed for the selected pins.
                                      This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIOMode_TypeDef GPIO_Mode;    /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_TypeDef */
}GPIO_InitTypeDef;


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

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_AIN) || ((MODE) == GPIO_Mode_IN_FLOATING) || \
                            ((MODE) == GPIO_Mode_IPD) || ((MODE) == GPIO_Mode_IPU) || \
                            ((MODE) == GPIO_Mode_Out_OD) || ((MODE) == GPIO_Mode_Out_PP) || \
                            ((MODE) == GPIO_Mode_AF_OD) || ((MODE) == GPIO_Mode_AF_PP))


#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14 selected */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15 selected */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /*!< All pins selected */

#define IS_GPIO_PIN(PIN) ((((PIN) & (uint16_t)0x00) == 0x00) && ((PIN) != (uint16_t)0x00))

typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_10MHz) || ((SPEED) == GPIO_Speed_2MHz) || \
                              ((SPEED) == GPIO_Speed_50MHz))
~~~
- 这里也是传入的指针.但是跟上面不同的是,这里需要我们在外部自己配置好了,然后再传入地址.
- 那么这两个指针有何不同呢?
- 第一个指针,指向的地址是寄存器地址.
- 第二个指针,就是单纯地枚举,枚举的是掩码变量.这就是不同.
- 可以看到,上面不论是`Pin`,还是`Mode`,还是`Speed`,都是需要用户选择的.而每一个都对应着一个掩码,从而在初始化的时候,对寄存器地址相关值进行配置.
- 所以,一开始说的, 传入变量,`Typedef*`是地址,也有可能不对,因为也可能是多掩码的结构体.
- 我往下看了看,还是符合地址在等号左,掩码在等号右侧的关系.
- 我问了一下`ai`,第二个参数命名可以不用传递指针,为什么非要穿指针,它是这么回复的.
    - 减少栈空间占用.结构体是按值传递的,如果不用指针,那么整个结构体会被复制一份到栈上.在嵌入式系统中,栈很小(有时只有几百字节),传指针更节省内存.指针传递只占4字节(ARM Cortex-M上),而结构体可能有好几十字节.
    - 兼容性与灵活性更好.传指针后,可以直接修改外部结构体内容(虽然GPIO_Init里没改),但:某些其他外设初始化函数可能会修改用户传入的结构体(例如DMA,SPI初始化结构体).保持统一接口风格更方便维护.换句话说,这种设计是一种统一接口规范.
    - 减少拷贝,提高效率.函数参数传递指针,只需传递地址,不用把整个结构体复制一遍.嵌入式场景下追求速度和代码体积,这是优化的一部分.
- 好吧,那我们也多用指针操作吧.
#### 举例3
~~~C
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BSRR = GPIO_Pin;
}
~~~
- 上面的明白了,这个也就明白了.不多bb了.
