#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "key.h"
#include "beep.h"
#include "exti.h"

int main()
{
	u8 i=0;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
	LED_Init();
	KEY_Init();
	BEEP_Init();
	EXTI_USING_KEY_Init();  
	volatile unsigned long* a;
	a = &PBout(5);
	while(1)
	{
		i++;
		if(i%20==0)
		{
			*a=!*a;
		}
		delay_ms(10);
	}
}

