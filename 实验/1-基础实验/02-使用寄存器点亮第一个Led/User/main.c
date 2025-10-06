# include "stm32f10x.h"
void SystemInit(void){
	
}

int main(){
	RCC_APB2ENR |=1<<3;
	GPIOB_CRL &=~(0XF<<(4*5));
	GPIOB_CRL |=(3<<(4*5));
	GPIOB_BRR = (1<<(16+5));
	
	while(1){}
}



