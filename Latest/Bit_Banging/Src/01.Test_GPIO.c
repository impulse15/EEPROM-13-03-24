/*
 * 01.Test_GPIO.c
 *
 *  Created on: Jan 4, 2024
 *      Author: 10820302
 */

/*
 * Objective :- To test all the features of GPIO engine related to BIT banging
 */

#include <stdint.h>
#include "G0B1RE.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
void delay(void)
{
	for (int i=0; i<400000; i++)
	{}
}

void User_LED_Setup(GPIO_Handler_t * User_Led)
{
	User_Led->config.Mode = GPIO_MODE_OUT;
	User_Led->config.OSpeed = GPIO_OSPEED_H;
	User_Led->config.OType = GPIO_OTYPE_PP;
	User_Led->config.pPort= GPIOA;
	User_Led->config.Pin= PIN_5;
	User_Led->config.PUPD=GPIO_PUPD_NO;
}

void User_Button_Setup(GPIO_Handler_t * User_Button)
{
	User_Button->config.Mode = GPIO_MODE_IN;
	User_Button->config.OSpeed = GPIO_OSPEED_H;
	User_Button->config.OType = GPIO_OTYPE_PP;
	User_Button->config.pPort= GPIOC;
	User_Button->config.Pin= PIN_13;
	User_Button->config.PUPD=GPIO_PUPD_NO;
}

int main(void)
{


	GPIO_Handler_t User_Led;
	User_LED_Setup(&User_Led);
	GPIO_EN_DI(User_Led.config.pPort, ENABLE);
	GPIO_INI(&User_Led);

	GPIO_Handler_t User_Button;
	User_Button_Setup(&User_Button);
	GPIO_EN_DI(User_Button.config.pPort, ENABLE);
	GPIO_INI(&User_Button);

	while(1)
	{
		if(!(User_Button.pGPIO->Data_IN & (0x1 << User_Button.config.Pin)))
	{GPIO_PIN_Toggle(User_Led.pGPIO, User_Led.config.Pin);
		delay();}

	}
}
