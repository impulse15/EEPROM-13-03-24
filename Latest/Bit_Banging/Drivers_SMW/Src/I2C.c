/*
 * I2C.c
 *
 *  Created on: Feb 19, 2024
 *      Author: 10820302
 */

#include "I2C.h"


#define TIME_PERIOD		30			//itterations of for loop for 1 timeperiod of SCLK

//@TIME_DIVISIONS
#define ONE				1
#define HALF			2
#define QUARTER			4


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 						API Definition
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 */

/*********************************************************************
 * @fn      		  - I2C_EN_DI
 *
 * @brief             -	Checks if the I2C is in running mode / in idle mode
 * 					  -	for setting / disabling I2C respectively
 *
 * @param[in]         -	Pointer to I2C Configuration Variable
 * @param[in]         -	Enable or Disable
 * @param[in]         -
 *
 * @return            - SUCCESS / ERROR
 *
 * @Note              -	APPLICATION LAYER API
 * 						Useful while non blocking project

 */

uint8_t I2C_En_or_DI(I2C_config_t* pi2c_config, uint8_t EnorDi )
{
	if(EnorDi == SET)
	{
		if(pi2c_config->STATUS == RESET)
		{
			pi2c_config->STATUS = SET;

			return SUCESS;
		}
		else
			return ERROR;

	}
	else
	{
		if(pi2c_config->STATUS == SET)
		{
			pi2c_config->STATUS = RESET;
			return SUCESS;
		}
		else
			return ERROR;
	}
}

/*********************************************************************
 * @fn      		  - SPI_INI_DeINI
 *
 * @brief             - Initialize pins for respective functions
 *
 * @param[in]         -	Pointer to the I2C Handler register
 * @param[in]         -	INITIALISE or DEINITIALISE
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Creates a lot of big variables (APPLICATION LAYER API)

 */
void I2C_INI_DEINI (I2C_handler_t * pI2C_handler, uint8_t INIorDIINI)
{
	if(INIorDIINI == INITIALIZE)
	{
	if(pI2C_handler->i2c_config.STATUS== SET)
	{

	// Enable peripheral
	GPIO_EN_DI(pI2C_handler->i2c_config.pPort, ENABLE);

	/*
	 * GPIO pins initialize
	 */

	//SDA_w SETUP
	pI2C_handler->SDA_w.config.Mode = GPIO_MODE_OUT;
	pI2C_handler->SDA_w.config.OSpeed = GPIO_OSPEED_VH;
	pI2C_handler->SDA_w.config.OType = GPIO_OTYPE_OD;
	pI2C_handler->SDA_w.config.PUPD = GPIO_PUPD_PU;
	pI2C_handler->SDA_w.config.Pin = pI2C_handler->i2c_config.PIN_SDA_w;
	pI2C_handler->SDA_w.config.pPort = pI2C_handler->i2c_config.pPort;

	GPIO_INI(&pI2C_handler->SDA_w);

	//SDA_r Setup
	pI2C_handler->SDA_r.config.Mode = GPIO_MODE_IN;
	pI2C_handler->SDA_r.config.PUPD = GPIO_PUPD_PU;
	pI2C_handler->SDA_r.config.Pin = pI2C_handler->i2c_config.PIN_SDA_r;
	pI2C_handler->SDA_r.config.pPort = pI2C_handler->i2c_config.pPort;

	GPIO_INI(&pI2C_handler->SDA_r);

	//SCLK SETUP
	pI2C_handler->SCLK.config.Mode = GPIO_MODE_OUT;
	pI2C_handler->SCLK.config.OSpeed = GPIO_OSPEED_VH;
	pI2C_handler->SCLK.config.OType = GPIO_OTYPE_OD;
	pI2C_handler->SCLK.config.PUPD = GPIO_PUPD_PU;
	pI2C_handler->SCLK.config.Pin = pI2C_handler->i2c_config.PIN_SCLK;
	pI2C_handler->SCLK.config.pPort = pI2C_handler->i2c_config.pPort;

	GPIO_INI(&pI2C_handler->SCLK);


	}
	else
		I2C_Error_handler();
	}
	else
	{
		GPIO_EN_DI(pI2C_handler->i2c_config.pPort, DISABLE);
	}

	//MAKE SDA_w and SCLK 1 (open drain) initial inactive condition
	GPIO_PIN_SEND(pI2C_handler->SDA_w.pGPIO,pI2C_handler->SDA_w.config.Pin, SET);

	GPIO_PIN_SEND(pI2C_handler->SCLK.pGPIO,pI2C_handler->SCLK.config.Pin, SET);		//sequence matters

	//brief delay_1
	delay_1(ONE);
	delay_1(ONE);
	delay_1(ONE);

}

/*
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *
 * 									Send Receive API
 *
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 */

/*********************************************************************
 * @fn      		  - I2C_Start_End
 *
 * @brief             -	setups clock's initial & Final state with chip select activate & deactivate
 *
 * @param[in]         - I2C Handler pointer
 * @param[in]         -	START / STOP macros
 * @param[in]         -
 *
 * @return            -  None
 *
 * @Note              -	DRIVER HELPER API

 */

void I2C_Start_End(I2C_handler_t * pI2C_Handler, uint8_t STARTorSTOP)
{if(STARTorSTOP == START)
	{
		if(pI2C_Handler->i2c_config.STATUS == SET)
		{


			//pull down SDA line
			GPIO_PIN_SEND(pI2C_Handler->SDA_w.pGPIO,pI2C_Handler->SDA_w.config.Pin, RESET);


			//delay_1
			delay_1(HALF);


			//pull down SCLK line

			GPIO_PIN_SEND(pI2C_Handler->SCLK.pGPIO,pI2C_Handler->SCLK.config.Pin, RESET);
			//quarter time period delay_1
			delay_1(QUARTER);
		}

	}
else
{
	//pull down sda line
	GPIO_PIN_SEND(pI2C_Handler->SDA_w.pGPIO,pI2C_Handler->SDA_w.config.Pin, RESET);

	//quarter delay_1
	delay_1(QUARTER);

	//clk high
	GPIO_PIN_SEND(pI2C_Handler->SCLK.pGPIO,pI2C_Handler->SCLK.config.Pin, SET);

	//quarter delay_1
	delay_1(QUARTER);

	//sda line high
	GPIO_PIN_SEND(pI2C_Handler->SDA_w.pGPIO,pI2C_Handler->SDA_w.config.Pin, SET);

}
}



/*********************************************************************
 * @fn      		  - I2C send bit
 *
 * @brief             - sends a bit according
 *
 * @param[in]         -	Pointer to I2C Handler
 * @param[in]         -	SET / RESET macros for output bit
 * @param[in]         -
 *
 * @return            - SET / RESET macros for input bit
 *
 * @Note              -	timing between the clock toggle is pending
 * 						DRIVER HELPER API

 */
void I2C_Send_Bit(I2C_handler_t* pi2c_handler ,uint8_t SETorReset)
{

	//data set

	GPIO_PIN_SEND(pi2c_handler->SDA_w.pGPIO, pi2c_handler->SDA_w.config.Pin, SETorReset);

	//quarter time period delay_1
	delay_1(QUARTER);

	//clk high
	GPIO_PIN_SEND(pi2c_handler->SCLK.pGPIO,pi2c_handler->SCLK.config.Pin, SET);

	//half time period delay_1
	delay_1(HALF);

	//clk low
	GPIO_PIN_SEND(pi2c_handler->SCLK.pGPIO,pi2c_handler->SCLK.config.Pin, RESET);

	//quarter time period delay_1
	delay_1(QUARTER);


}
/*********************************************************************
 * @fn      		  - I2C Rec bit
 *
 * @brief             - Rec a bit
 *
 * @param[in]         -	Pointer to I2C Handler
 * @param[in]         -	SET / RESET macros for output bit
 * @param[in]         -
 *
 * @return            - SET / RESET macros for input bit
 *
 * @Note              -	timing between the clock toggle is pending
 * 						DRIVER HELPER API

 */
uint8_t I2C_Rec_Bit(I2C_handler_t* pi2c_handler )
{
	uint8_t rec=0x00;
	//quarter time period delay_1
	delay_1(QUARTER);

	//clk high
	GPIO_PIN_SEND(pi2c_handler->SCLK.pGPIO,pi2c_handler->SCLK.config.Pin, SET);
	GPIO_PIN_SEND(pi2c_handler->SDA_w.pGPIO, pi2c_handler->SDA_w.config.Pin, SET);	//MAKING IT OPEN DRAIN

	//quarter time period delay_1
	delay_1(QUARTER);

	//data read

	rec=GPIO_PIN_READ(pi2c_handler->SDA_r.pGPIO, pi2c_handler->SDA_r.config.Pin);

	//quarter time period delay_1
	delay_1(QUARTER);

	//clk low
	GPIO_PIN_SEND(pi2c_handler->SCLK.pGPIO,pi2c_handler->SCLK.config.Pin, RESET);

	//quarter time period delay_1
	delay_1(QUARTER);

	return rec;

}

/*********************************************************************
 * @fn      		  -	I2C_Send_Byte
 *
 * @brief             -	Sends and receives a Byte of data
 *
 * @param[in]         -	pointer to I2C Handler
 * @param[in]         -	pointer to MSG to be sent
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              -	DRIVER LEVEL API

 */
void I2C_Send_Byte(I2C_handler_t* pi2c_handler,uint8_t * pMSG_send )
{
	uint8_t send;
	send=*pMSG_send;

		//send 1 byte of data


		for(int i=0;i<8;++i)
		{
		I2C_Send_Bit(pi2c_handler, (send & (1<<7))>>7);				//MSB First
			send = send << 1;
		}

		//receive ack for the byte of data
   	if(I2C_Ack_check(pi2c_handler)==NACK)
		{
   			send = send;
			I2C_Error_handler();
		}


}

/*********************************************************************
 * @fn      		  - I2C_address_Write
 *
 * @brief             -	writes address on the SDA_w line
 *
 * @param[in]         - I2C Handler pointer
 * @param[in]         -	Write or Read Macros
 * @param[in]         -
 *
 * @return            -  None
 *
 * @Note              -	DRIVER HELPER API

 */
#define WRITE  	RESET
#define READ	SET

void I2C_address_Write(I2C_handler_t* pi2c_handler, uint8_t Write_or_Read)
{
	Write_or_Read |=(pi2c_handler->i2c_config.slave_address << 1);
	I2C_Send_Byte(pi2c_handler, &Write_or_Read);
}

void I2C_PageADDR_Write(I2C_handler_t* pi2c_handler)
{
	I2C_Send_Byte(pi2c_handler, &pi2c_handler->i2c_config.Page);
}

void I2C_MemADDR_Write(I2C_handler_t* pi2c_handler)
{
	I2C_Send_Byte(pi2c_handler, &pi2c_handler->i2c_config.Memory);
}

/*********************************************************************
 * @fn      		  - I2C_Ack_check
 *
 * @brief             -	receives a acknowledge byte receive or address detect
 *
 * @param[in]         - I2C Handler pointer
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  ACK or NACK
 *
 * @Note              -	DRIVER HELPER API

 */

uint8_t I2C_Ack_check(I2C_handler_t* pi2c_handler)
{
	return I2C_Rec_Bit(pi2c_handler);
}


/*********************************************************************
 * @fn      		  - I2C_Send_Msg
 *
 * @brief             -	This API sends the message using I2C protocol
 *
 * @param[in]         - I2C Handler pointer
 * @param[in]         -	pointer to the Send message variable
 * @param[in]         -	Length of the message
 *
 * @return            -  None
 *
 * @Note              -	APPLICATION LAYER API

 */

void I2C_Send_Msg(I2C_handler_t* pi2c_handler,uint8_t* pSEND_MSG,uint32_t Length)
{	uint8_t* pMSG = pSEND_MSG;
	//call start condition generator function
	I2C_Start_End(pi2c_handler, START);

	//address generating function
	I2C_address_Write(pi2c_handler, WRITE);

	//page address generating function
	I2C_PageADDR_Write(pi2c_handler);

	//memory address generating function
	I2C_MemADDR_Write(pi2c_handler);

	//data generating function
	if(Length != 0)
	{
			for(uint32_t i=0;i<Length;i++)
			{
				I2C_Send_Byte(pi2c_handler, pMSG);
				pMSG++;
			}
	}

	//stop condition generating function
	//I2C_Start_End(pi2c_handler, STOP);


}


/*********************************************************************
 * @fn      		  - I2C_Rec_Msg
 *
 * @brief             -	Receives a MSG from slave
 *
 * @param[in]         - Pointer to the I2C handler
 * @param[in]         -	Pointer to the buffer variable to store
 * @param[in]         - length of the message to be received
 *
 * @return            -  None
 *
 * @Note              -	APPLICATION LAYER API

 */

void I2C_Rec_Msg(I2C_handler_t* pi2c_handler,uint8_t* pREC_MSG,uint32_t Length)
{	uint8_t * pMSG = pREC_MSG;
	//dummy write
	//call start condition generator function
	I2C_Start_End(pi2c_handler, START);

	//address generating function
	I2C_address_Write(pi2c_handler, READ);

	//data reading function
	for(uint32_t i=0;i<Length;i++)
	{
		I2C_Rec_Byte(pi2c_handler, pMSG);
		pMSG++;
	}

	//stop condition generating function
//	I2C_Start_End(pi2c_handler, STOP);

	//disable function   .....in main?



}
/*********************************************************************
 * @fn      		  -	I2C_Rec_Byte
 *
 * @brief             -	Receives a Byte of data
 *
 * @param[in]         -	pointer to I2C Handler
 * @param[in]         -	pointer to MSG to be sent
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              -	DRIVER LEVEL API

 */
void I2C_Rec_Byte(I2C_handler_t* pi2c_handler,uint8_t * pMSG_Rec )
{
	uint8_t rec=0x00;


		//rec 1 byte of data

		int i=0;
		for(i=0;i<8;i++)
		{
			rec = rec << 1;
			rec |= I2C_Rec_Bit(pi2c_handler); 		//MSB First

		}

		*pMSG_Rec = rec;

		//send an ACK for the Byte received

		if(i==8)
		{
			I2C_Send_Bit(pi2c_handler, RESET);
		}
		else
		{
			rec= rec;
			I2C_Error_handler();
		}



}
/*********************************************************************
 * @fn      		  -	I2C_Error_handler
 *
 * @brief             -	Error handler in I2C communication
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              -	DRIVER LEVEL API / APPLICATION LAYER API

 */
void I2C_Error_handler(void)
{
	while(1);
}
/*********************************************************************
 * @fn      		  -	delay_1 functions
 *
 * @brief             -	provide delay_1 according to time period of the SCLK
 * @param[in]         -	MACROS @TIME_DIVISIONS
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              -	DRIVER LEVEL API / APPLICATION LAYER API

 */

void delay_1(uint8_t div)
{
	for (int i=0; i < TIME_PERIOD/div; i++)
	{}
}
