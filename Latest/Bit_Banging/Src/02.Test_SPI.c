
/*
 * 02.Test_SPI.c
 *
 *  Created on: Jan 5, 2024
 *      Author: Sarang
 */

#include <stdint.h>
#include "G0B1RE.h"
#include "GPIO.h"
#include "SPI.h"
#include <string.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void SPI_Setup(SPI_Handler_t * SPI)
{
	SPI->SPI_Config.Baudrate = SPI_BAUDRATE_DIV2;
	SPI->SPI_Config.CPHA = SPI_CPHA_EN;
	SPI->SPI_Config.CPOL = SPI_CPOL_DI;
	SPI->SPI_Config.DATA_Format = SPI_DATA_FORMAT_MSBF;
	SPI->SPI_Config.DATA_Size = SPI_DATA_Size_8bits;
	SPI->SPI_Config.PIN_CLK = PIN_10;
	SPI->SPI_Config.PIN_MISO = PIN_12;
	SPI->SPI_Config.PIN_MOSI = PIN_11;
	SPI->SPI_Config.PIN_NS = PIN_5;
	SPI->SPI_Config.pPort = GPIOA;
	SPI->SPI_Config.STATUS = RESET;
}
void User_Led_Init(void)
{
	GPIO_Handler_t User_Led;
	User_Led.config.Mode = GPIO_MODE_OUT;
	User_Led.config.OType = GPIO_OTYPE_PP;
	User_Led.config.Pin = PIN_5;
	User_Led.config.pPort = GPIOA;
	GPIO_EN_DI(GPIOA, ENABLE);
	GPIO_INI(&User_Led);



}

uint16_t Calc_check(uint8_t * msg)
{
	uint16_t count=0;
	for(uint8_t i=0; i< 12 ;i++)
	{
		count+= *msg;
		msg++;
	}
	return count;
}


int main()
{
	SPI_Handler_t SPI;
	const uint8_t send_msg[]= "Hi I am Waje";
	uint8_t rec_msg[12];
uint16_t calc_sentmsg;
calc_sentmsg = Calc_check(send_msg);
	SPI_Setup(&SPI);

	if(SPI_EN_DI(&SPI.SPI_Config, ENABLE))
	{
		SPI_INI_DEINI(&SPI, INITIALIZE);
		SPI_MSG_Send_Rec(&SPI, send_msg, rec_msg, 12);
		SPI_INI_DEINI(&SPI, DEINITIALIZE);
	}

	uint16_t calc_recmsg;
	calc_recmsg = Calc_check(rec_msg);

	//initialize user led for showing the message received = transfered

	User_Led_Init();
	while (calc_recmsg == calc_sentmsg)
	{
		GPIO_PIN_Toggle(GPIOA,PIN_5);
		delay();
	}



}
/*
SPI->SPI_Config.PIN_CLK = PIN_4;
SPI->SPI_Config.PIN_MISO = PIN_6;
SPI->SPI_Config.PIN_MOSI = PIN_5;
SPI->SPI_Config.PIN_NS = PIN_7;
SPI->SPI_Config.pPort = GPIOA;
SPI->SPI_Config.STATUS = RESET;
*/
