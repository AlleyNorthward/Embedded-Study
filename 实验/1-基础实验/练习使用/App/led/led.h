#ifndef _LED_H

#define _LED_H
#define LED0_RCC_PORT               RCC_APB2Periph_GPIOB
#define LED0_PORT                   GPIOB
#define LED0_GPIO_PIN               GPIO_Pin_5
#define LED0_GPIO_MODE              GPIO_Mode_Out_PP

void Init_led(void);

#endif
