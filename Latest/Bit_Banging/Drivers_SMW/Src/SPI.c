/*
 * SPI.c
 *
 *  Created on: Dec 28, 2023
 *      Author: 10820302
 */


#include "SPI.h"

void delay(void)
{
	for (int i=0; i<30000; i++)
	{}
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 						API Definition
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 */
#define ERROR  0x00
#define SUCESS 0x01
/*********************************************************************
 * @fn      		  - SPI_EN_DI
 *
 * @brief             -	Checks if the SPI is in running mode / in idle mode
 * 					  -	for setting / disabling SPI respectively
 *
 * @param[in]         -	Pointer to SPI Configuration Variable
 * @param[in]         -	Enable or Disable
 * @param[in]         -
 *
 * @return            - SUCCESS / ERROR
 *
 * @Note              -	APPLICATION LAYER API
 * 						Useful while non blocking project

 */
uint8_t SPI_EN_DI(SPI_config_t * pSPI_config, uint8_t EnorDi)
{
	if(EnorDi == SET)
	{
		if(pSPI_config->STATUS == RESET)
		{
			pSPI_config->STATUS = SET;
			return SUCESS;
		}
		else
			return ERROR;

	}
	else
	{
		if(pSPI_config->STATUS == SET)
		{
			pSPI_config->STATUS = RESET;
			return SUCESS;
		}
		else
			return ERROR;
	}
}


/*********************************************************************
 * @fn      		  - SPI_INI
 *
 * @brief             - Initialize pins for respective functions
 *
 * @param[in]         -	Pointer to the SPI Handler register
 * @param[in]         -	INITIALISE or DEINITIALISE
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Creates a lot of big variables (APPLICATION LAYER API)

 */
void SPI_INI_DEINI (SPI_Handler_t * pSPI_Handler, uint8_t INIorDIINI)
{
	if(INIorDIINI == INITIALIZE)
	{
	if(pSPI_Handler->SPI_Config.STATUS== SET)
	{

	// Enable peripheral
	GPIO_EN_DI(pSPI_Handler->SPI_Config.pPort, ENABLE);

	/*
	 * GPIO pins initialize
	 */

	//MOSI SETUP
	pSPI_Handler->MOSI.config.Mode = GPIO_MODE_OUT;
	pSPI_Handler->MOSI.config.OSpeed = GPIO_OSPEED_VH;
	pSPI_Handler->MOSI.config.OType = GPIO_OTYPE_PP;
	pSPI_Handler->MOSI.config.PUPD = GPIO_PUPD_PD;
	pSPI_Handler->MOSI.config.Pin = pSPI_Handler->SPI_Config.PIN_MOSI;
	pSPI_Handler->MOSI.config.pPort = pSPI_Handler->SPI_Config.pPort;

	GPIO_INI(&pSPI_Handler->MOSI);

	//MISO SETUP
	pSPI_Handler->MISO.config.Mode = GPIO_MODE_IN;
	pSPI_Handler->MISO.config.OSpeed = GPIO_OSPEED_VH;
	pSPI_Handler->MISO.config.PUPD = GPIO_PUPD_NO;
	pSPI_Handler->MISO.config.Pin = pSPI_Handler->SPI_Config.PIN_MISO;
	pSPI_Handler->MISO.config.pPort = pSPI_Handler->SPI_Config.pPort;

	GPIO_INI(&pSPI_Handler->MISO);

	//CLK SETUP

	pSPI_Handler->CLK.config.Mode = GPIO_MODE_OUT;
	pSPI_Handler->CLK.config.OSpeed = GPIO_OSPEED_VH;
	pSPI_Handler->CLK.config.OType = GPIO_OTYPE_PP;
	pSPI_Handler->CLK.config.PUPD = GPIO_PUPD_NO;
	pSPI_Handler->CLK.config.Pin = pSPI_Handler->SPI_Config.PIN_CLK;
	pSPI_Handler->CLK.config.pPort = pSPI_Handler->SPI_Config.pPort;

	GPIO_INI(&pSPI_Handler->CLK);

	//CHIP SELECT SETUP

	pSPI_Handler->NS.config.Mode = GPIO_MODE_OUT;
	pSPI_Handler->NS.config.OSpeed = GPIO_OSPEED_VH;
	pSPI_Handler->NS.config.OType = GPIO_OTYPE_PP;
	pSPI_Handler->NS.config.PUPD = GPIO_PUPD_NO;
	pSPI_Handler->NS.config.Pin = pSPI_Handler->SPI_Config.PIN_NS;
	pSPI_Handler->NS.config.pPort = pSPI_Handler->SPI_Config.pPort;

	GPIO_INI(&pSPI_Handler->NS);
	}
	}
	else
	{
		GPIO_EN_DI(pSPI_Handler->SPI_Config.pPort, DISABLE);
	}

}

/*
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *
 * 									Send Receive API
 *
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 */
#define START	SET
#define STOP	RESET
/*********************************************************************
 * @fn      		  - SPI_Start_End
 *
 * @brief             -	setups clock's initial & Final state with chip select activate & deactivate
 *
 * @param[in]         - SPI Handler pointer
 * @param[in]         -	START / STOP macros
 * @param[in]         -
 *
 * @return            -  None
 *
 * @Note              -	DRIVER HELPER API

 */

void SPI_Start_End(SPI_Handler_t * pSPI_Handler, uint8_t STARTorSTOP)
{if(STARTorSTOP == START)
	{
		if(pSPI_Handler->SPI_Config.STATUS == SET)
		{




			//SETUP CLOCK POLARITY
			if(pSPI_Handler->SPI_Config.CPOL == SPI_CPOL_EN)
			{
				GPIO_PIN_SEND(pSPI_Handler->CLK.pGPIO, pSPI_Handler->SPI_Config.PIN_CLK, SET);
			}
			else
			{
				GPIO_PIN_SEND(pSPI_Handler->CLK.pGPIO, pSPI_Handler->SPI_Config.PIN_CLK, RESET);

			}

			//NS low
			GPIO_PIN_SEND(pSPI_Handler->NS.pGPIO, pSPI_Handler->SPI_Config.PIN_NS, RESET);
		 }

	}
else
	{
		GPIO_PIN_SEND(pSPI_Handler->NS.pGPIO, pSPI_Handler->SPI_Config.PIN_NS, SET);
	}
}

/*********************************************************************
 * @fn      		  - SPI_Clk_toggle
 *
 * @brief             - Toggles the clock signal
 *
 * @param[in]         -	pointer to the CLK handler
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - None
 *
 * @Note              -	DRIVER HELPER API

 */
void SPI_Clk_toggle(GPIO_Handler_t * pClk_handler)
{
	GPIO_PIN_Toggle(pClk_handler->pGPIO, pClk_handler->config.Pin);
}

/*********************************************************************
 * @fn      		  - SPI_Bit_Send_Rec
 *
 * @brief             -	receives a bit and sends a bit according to CPHA
 *
 * @param[in]         -	Pointer to SPI Handler
 * @param[in]         -	SET / RESET macros for output bit
 * @param[in]         -
 *
 * @return            - SET / RESET macros for input bit
 *
 * @Note              -	timing between the clock toggle is pending
 * 						DRIVER HELPER API

 */
uint8_t SPI_Bit_Send_Rec(SPI_Handler_t * pSPI_Handler ,uint8_t SETorReset)
{	uint16_t receive_bit=0x00;

	if(pSPI_Handler->SPI_Config.CPHA == RESET)
	{	//clk toggle
		SPI_Clk_toggle(&(pSPI_Handler->CLK));
		//scan input
		receive_bit = pSPI_Handler->MISO.pGPIO->Data_IN & (1 << pSPI_Handler->SPI_Config.PIN_MISO);

		receive_bit = receive_bit >> pSPI_Handler->SPI_Config.PIN_MISO;
		//time delay..................pending
		delay();

		//clk toggle
		SPI_Clk_toggle(&(pSPI_Handler->CLK));
		//output a bit
		GPIO_PIN_SEND(pSPI_Handler->MOSI.pGPIO, pSPI_Handler->MOSI.config.Pin, SETorReset);

		delay();
	}
	else
	{
		//clk toggle
		SPI_Clk_toggle(&(pSPI_Handler->CLK));
		//output a bit
		GPIO_PIN_SEND(pSPI_Handler->MOSI.pGPIO, pSPI_Handler->MOSI.config.Pin, SETorReset);

		//time delay.................pending
		delay();
		//clk toggle
		SPI_Clk_toggle(&(pSPI_Handler->CLK));

		//scan input
		receive_bit = pSPI_Handler->MISO.pGPIO->Data_IN & (1 << pSPI_Handler->SPI_Config.PIN_MISO);
		receive_bit = receive_bit >> pSPI_Handler->SPI_Config.PIN_MISO;

		delay();
	}

	return (uint8_t) receive_bit;
}

/*********************************************************************
 * @fn      		  -	SPI_Byte_Send_Rec
 *
 * @brief             -	Sends and receives a Byte of data
 *
 * @param[in]         -	pointer to SPI Handler
 * @param[in]         -	pointer to MSG to be sent
 * @param[in]         -	pointer to MSG to be stored
 *
 * @return            -	None
 *
 * @Note              -	DRIVER LEVEL API

 */
void SPI_Byte_Send_Rec(SPI_Handler_t * pSPI_Handler,uint8_t * pMSG_send , uint8_t * pMSG_REC)
{	uint8_t rec=0x00,send;
	send=*pMSG_send;
	if(pSPI_Handler->SPI_Config.DATA_Format == SPI_DATA_FORMAT_MSBF)
	{
		for(int i=0;i<8;++i)
		{
			rec |= SPI_Bit_Send_Rec(pSPI_Handler, (send & (1<<7))>>7);        //has form of 0b0000000x
			if(i == 7)
				{break;}
			send = send << 1;
			rec = rec << 1;
		}
	}
	else if(pSPI_Handler->SPI_Config.DATA_Format == SPI_DATA_FORMAT_LSBF)
		{
			for(int i=0;i<8;++i)
				{
					rec |= SPI_Bit_Send_Rec(pSPI_Handler, (send & 1) );        //has form of 0b0000000X
					send = send >> 1;
					rec = rec >> 1;
				}
		}

	*pMSG_REC = rec;
}

/*********************************************************************
 * @fn      		  - SPI_MSG_Send_Rec
 *
 * @brief             - Sends and receive 8 bit format messages
 *
 * @param[in]         -	pointer to the Handler
 * @param[in]         -	Pointer to the message to be sent
 * @param[in]         -	Pointer to the message to be stored
 * @param[in]         -	Length of the send and receive data(max of both)
 * @return            -	None
 *
 * @Note              -	APPLCATION LAYER API

 */
void SPI_MSG_Send_Rec(SPI_Handler_t * pSPI_Handler, uint8_t * pMSG_send , uint8_t * pMSG_REC, uint32_t Length )
{
	if(pSPI_Handler->SPI_Config.STATUS == SET)
	{
		SPI_Start_End(pSPI_Handler, START);

		for(int i=0;i<Length;i++ )
		{
			SPI_Byte_Send_Rec(pSPI_Handler, pMSG_send, pMSG_REC);
			pMSG_send++;
			pMSG_REC++;
		}

		SPI_Start_End(pSPI_Handler, STOP);
		SPI_EN_DI(&pSPI_Handler->SPI_Config, RESET);

	}

}


