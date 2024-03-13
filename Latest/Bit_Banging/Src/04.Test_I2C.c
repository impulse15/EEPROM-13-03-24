/*
 * 04.Test_I2C.c
 *
 *  Created on: Mar 5, 2024
 *      Author: 10820302
 */




#include <stdint.h>
#include "G0B1RE.h"
#include "GPIO.h"
#include "I2C.h"
#include <string.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay_2(void)
{
	for(uint32_t i=0; i<300000 ; i++)
	{}
}


void I2C_Setup(I2C_handler_t* I2C)
{
	I2C->i2c_config.Baudrate = 0;  //garbage
	I2C->i2c_config.Memory = 0;
	I2C->i2c_config.PIN_SCLK=5;
	I2C->i2c_config.PIN_SDA_w=12;
	I2C->i2c_config.PIN_SDA_r=11;
	I2C->i2c_config.Page=0;
	I2C->i2c_config.STATUS = RESET;
	I2C->i2c_config.pPort= GPIOA;
	I2C->i2c_config.slave_address=0x50;
}

int main()
{
	I2C_handler_t I2C;
	uint8_t send_msg[]= "Lord RAM";
	uint8_t rec_msg[100];


	I2C_Setup(&I2C);

	if(I2C_En_or_DI(&I2C.i2c_config, ENABLE)==SUCESS)
	{
		I2C_INI_DEINI(&I2C, INITIALIZE);
	//	I2C_Send_Msg(&I2C, send_msg,19);
	//	I2C_Start_End(&I2C, STOP);
		//delay
delay_2();
		I2C_Send_Msg(&I2C, send_msg,0);
		//MAKE SDA_w and SCLK 1 (open drain) initial inactive condition
		GPIO_PIN_SEND(I2C.SDA_w.pGPIO,I2C.SDA_w.config.Pin, SET);

		GPIO_PIN_SEND(I2C.SCLK.pGPIO,I2C.SCLK.config.Pin, SET);		//sequence matters

		//brief delay_1
delay_2();

		I2C_Rec_Msg(&I2C, rec_msg,19);
		I2C_INI_DEINI(&I2C, DEINITIALIZE);

		if(send_msg[0] == rec_msg[0])
		{
			//balle balle
			delay_1(1);
		}
	}
	I2C_En_or_DI(&I2C.i2c_config, DISABLE);






}

