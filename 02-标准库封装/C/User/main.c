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
	while(1)
	{
		i++;
		if(i%20==0)
		{
			SET_LED0=!SET_LED0;
		}
		delay_ms(10);
	}
}

