#include "system.h"
#include "led.h"
#include "clock.h"
#include "systick.h"
#include "beep.h"
#include "key.h"
#include <stdio.h>

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

} MY_RCC_TypeDef;

__IO uint32_t fake_reg = 1234;
#define MY_RCC_BASE             &fake_reg
#define MY_RCC                 ((MY_RCC_TypeDef *)MY_RCC_BASE)
int main(){
    printf("%p, %p", MY_RCC_BASE, MY_RCC);
    MY_RCC -> CR = 0x0001;
    printf("\n");
    printf("%p", &(MY_RCC -> CR));
    return 0;
}