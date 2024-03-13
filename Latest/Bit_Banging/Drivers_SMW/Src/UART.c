/*
 * UART.c
 *
 *  Created on: Jan 12, 2024
 *      Author: 10820302
 */
#include "UART.h"

/*
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 								APIs
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*
 * Enable and Initializing APIs
 */
#define ERROR  0x00
#define SUCESS 0x01
/*********************************************************************
 * @fn      		  - UART_EN_DI
 *
 * @brief             -	Checks if the UART is in running mode / in idle mode
 * 					  - for setting / disabling UART respectively
 *
 * @param[in]         -	UART Configuration Variable
 * @param[in]         -	Enable or Disable
 * @param[in]         -
 *
 * @return            - SUCCESS / ERROR
 *
 * @Note              -	APPLICATION LAYER API
 * 					  -	Useful while non blocking project//UART guarding API

 */
uint8_t UART_EN_DI(UART_Config_t * pUART_Conf , uint8_t ENorDI)
{
	if(ENorDI == SET)
	{
		if(pUART_Conf->Status == RESET)
		{
			pUART_Conf->Status = SET;
			return SUCESS;
		}
		else
			return ERROR;
	}
	else
	{
		if(pUART_Conf->Status == SET)
		{
			pUART_Conf->Status = RESET;
			return SUCESS;
		}
		else
			return ERROR;
	}
}
/*********************************************************************
 * @fn      		  -	UART_INI_DEINI
 *
 * @brief             -	Initializes or Deinitializes The GPIO & functionality
 *
 *
 * @param[in]         -	Pointer to the UART Handler
 * @param[in]         -	INITIALIZE or DEINITIALISE Macro
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              -	APPLICATION LAYER API
 *

 */
void UART_INI_DEINI(UART_Handler_t * pUART_Handler, uint8_t INIorDEINI)
{if(INIorDEINI == INITIALIZE)
{
	if(pUART_Handler->UART_Config.Status == SET)
	{
			//GPIO set
			//Peripheral Enable
		GPIO_EN_DI(pUART_Handler->UART_Config.pPort, ENABLE);

		//TX PIN
		pUART_Handler->TX.config.Mode = GPIO_MODE_OUT;
		pUART_Handler->TX.config.OSpeed = GPIO_OSPEED_VH;
		pUART_Handler->TX.config.OType = GPIO_OTYPE_PP;
		pUART_Handler->TX.config.PUPD = GPIO_PUPD_PU;
		pUART_Handler->TX.config.Pin = pUART_Handler->UART_Config.PIN_TX;
		pUART_Handler->TX.config.pPort = pUART_Handler->UART_Config.pPort;

		if(pUART_Handler->UART_Config.TX_EN == SET)
			{GPIO_INI(&pUART_Handler->TX);}

		//RX PIN
		pUART_Handler->RX.config.Mode = GPIO_MODE_IN;
		pUART_Handler->RX.config.PUPD = GPIO_PUPD_NO;
		pUART_Handler->RX.config.Pin = pUART_Handler->UART_Config.PIN_TX;
		pUART_Handler->RX.config.pPort = pUART_Handler->UART_Config.pPort;

		if(pUART_Handler->UART_Config.TX_EN == SET)
			{GPIO_INI(&pUART_Handler->TX);}



	}
}
else
{
	GPIO_EN_DI(pUART_Handler->UART_Config.pPort, DISABLE);
}


}

/*
 * Transmission APIs
 */

/*********************************************************************
 * @fn      		  -	UART_Baudrate
 *
 * @brief             -	Sets delays according to baud rate
 * 					  -
 *
 * @param[in]         -	Division of Peripheral clock acc to baudrate
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -	none
 *
 * @Note              -	DRIVER HELPER API
 *

 */
#define Freq_clk   			16000000
void UART_Baudrate(uint8_t Baud_rate, uint8_t divisions)
{
	int8_t div;
	if (divisions == UART_OVRSAMP_8)
		div = 8;
	else
		div = 16;

	uint8_t count = Freq_clk /(2 * (div) * (Baud_rate));    //as loop takes 2 cycles
	//add delays according to the div number
	// Fclk=16Mhz ; 1/16Mhz = time period of a cycle ; 2 cycles for for loop assumned
	//hence loop repetition = Fclk/2xFbaud;
	for(; count >0; count--);//assumption :- this takes 2 cycles of processing time

}

/*********************************************************************
 * @fn      		  - UART_Oversampling
 *
 * @brief             - Receives Bit accurately by set oversampling
 * 					  -
 *
 * @param[in]         -	Pointer to UART Handler
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - Received BIT
 *
 * @Note              -	DRIVER HELPER API
 *

 */
uint8_t UART_Oversampling(UART_Handler_t * pUART_Handler)
{

}

/*********************************************************************
 * @fn      		  -	UART_STOP_BIT
 *
 * @brief             -	This function sets the stop bit as configures
 * 					  -
 *
 * @param[in]         -	pointer to the UART Handler
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              -	DRIVER HELPER API
 *

 */
void UART_STOP_Bit(UART_Handler_t * pUart_Handler)
{
	for(uint8_t i=0;i < pUart_Handler->UART_Config.STOP_Bits ;i++)
	{
		//Call for half Baud rate delay
		//STOP BIT macros are written as multiples of half baudrate
		UART_Baudrate(pUart_Handler->UART_Config.Baudrate, 2);
	}
}
/*********************************************************************
 * @fn      		  -	UART_STOP_BIT
 *
 * @brief             -	This function sets the stop bit as configures
 * 					  -
 *
 * @param[in]         -	pointer to the UART Handler
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              -	DRIVER HELPER API
 *

 */
#define SUCCESS			SET
uint8_t UART_START_falling_edge(UART_Handler_t * pUart_Handler)
{	uint8_t sample=0x00;
	while(1)
	{
		sample |= GPIO_PIN_READ(pUart_Handler->RX.pGPIO, pUart_Handler->RX.config.Pin);                          //keep sampling the  bits from lsb and shift left; detect the start sequence
		if((sample & (0x01)) == RESET)
			{if((sample & (0x0E)) == 0x0E)
				return SUCCESS;}
		sample = sample << 1;
		UART_Baudrate(pUart_Handler->UART_Config.Baudrate, pUart_Handler->UART_Config.OverSampMode);			//add delay according to Baudrate and oversampling mode
	}

}


#define START_VERIFIED_NONOISE     	0x001
#define START_VERIFIED_NOISE		0x002
#define FAIL						0x000
uint8_t UART_SART_Bit_Detect(UART_Handler_t * pUart_Handler)
{uint8_t set1=0x00,set2=0x00;
	while (1)																//polling for repeatedly checking start condition
	{ UART_START_falling_edge(pUart_Handler);
		//delay of 1/16 or 1/8 baut rate X 2

		//scan for set1 , 3 samples
				set1 |= GPIO_PIN_READ(pUart_Handler->RX.pGPIO, pUart_Handler->RX.config.Pin);
				//delay of 1/16 or 1/8 baut rate X 2

				set1 = set1 << 1;
				set1 |= GPIO_PIN_READ(pUart_Handler->RX.pGPIO, pUart_Handler->RX.config.Pin);
				//delay of 1/16 or 1/8 baut rate X 2

				set1 = set1 << 1;
				set1 |= GPIO_PIN_READ(pUart_Handler->RX.pGPIO, pUart_Handler->RX.config.Pin);


		//scan for set2, 3 samples
				//delay of 1/16 or 1/8 baut rate

				//scan for set1 , 3 samples
						set2 |= GPIO_PIN_READ(pUart_Handler->RX.pGPIO, pUart_Handler->RX.config.Pin);
						//delay of 1/16 or 1/8 baut rate

						set2 = set2 << 1;
						set2 |= GPIO_PIN_READ(pUart_Handler->RX.pGPIO, pUart_Handler->RX.config.Pin);
						//delay of 1/16 or 1/8 baut rate

						set2 = set2 << 1;
						set2 |= GPIO_PIN_READ(pUart_Handler->RX.pGPIO, pUart_Handler->RX.config.Pin);

		state1 = (set1 | 0x01) + ((set1 | 0x02)>>1) + ((set1|0x04)>>2);
		state2 = (set2 | 0x01) + ((set2 | 0x02)>>1) + ((set2|0x04)>>2);

		if ((state1 < 2)||(state < 2 ))						 // atleast one of two state satisfied :- start sequence verified
		{

		if(!((state1 < 2)&&(state < 2 )))					//atleast one of the condition failed :- noise detected
		{
			//delay of baud rate X 8						synchronizing with the start bit
			return START_VERIFIEDm_NOISE;
		}
		else
		{
			//delay of baud rate X8								synchronizing with the start bit
			return START_VERIFIED_NONOISE;
		}



		}
}}
/*********************************************************************
 * @fn      		  - UART_Start_End
 *
 * @brief             -	This function sets START bit and STOP bit as configured
 * 					  -
 *
 * @param[in]         -	pointer to the UART Handler
 * @param[in]         -	START or END Macros
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              - DRIVER HELPER API
 *

 */
void UART_Start_End(UART_Handler_t * pUART_Handler, uint8_t StartorEnd)
{
	if(StartorEnd == SET)
	{


	//start bit
	GPIO_PIN_SEND(pUART_Handler->TX.pGPIO, pUART_Handler->TX.config.Pin, RESET);
	}
	else
	{
	//parity call:- To be implemented later




		//STOP BIT
		UART_STOP_Bit(pUART_Handler);

	}
}


/*********************************************************************
 * @fn      		  -	UART_Parity_Bit
 *
 * @brief             -	This function sets the parity bit as per the configuration
 * 					  -
 *
 * @param[in]         -	pointer to the UART Handler
 * @param[in]         -	EVEN(SET) or ODD(RESET) number of 1s in the Frame
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              -	DRIVER HELPER API
 *

 */
void UART_Parity_Bit(UART_Handler_t * pUart_Handler, uint8_t EVorOD_1s)
{//for transfer
	if(pUart_Handler->UART_Config.Parity_ENorDI == UART_PARITY_CTR_EI)
	{
		if(pUart_Handler->UART_Config.Parity_Mode == UART_PARITY_MODE_EV)
		{
			GPIO_PIN_SEND(pUart_Handler->TX.pGPIO, pUart_Handler->TX.config.Pin, !EVorOD_1s);
		}
		else
			GPIO_PIN_SEND(pUart_Handler->TX.pGPIO, pUart_Handler->TX.config.Pin, EVorOD_1s);
	}

	//for receive
	//?

}

/*********************************************************************
 * @fn      		  -	UART_Send_Rec_Bit
 *
 * @brief             -	This function sends and receives a bit of message
 * 					  -
 *
 * @param[in]         -	pointer to the UART Handler
 * @param[in]         -	Output to send; SET or RESET Macro
 * @param[in]         -
 *
 * @return            -	Received bit (LSB)
 *
 * @Note              -	DRIVER HELPER API
 *

 */
uint8_t UART_Send_Rec_Bit(UART_Handler_t * pUART_Handler,uint8_t SetorReset)
{
	uint8_t rec=0x00;

	//set the Bit on TX
		GPIO_PIN_SEND(pUART_Handler->TX.pGPIO, pUART_Handler->TX.config.Pin,SetorReset);
		//give a delay of set baudrate
		UART_Baudrate(6);						//decide baud rate

		//how does the asynchronous works between TX and RX?
				//resolved : full duplex or half duplex or simplex
return rec;
}


uint8_t UART_Rec_bit(UART_Handler_t * pUART_Handler)
{
	uint8_t rec=0x00;
	//delay of 3/7 peripheral frequency according to oversampling rate
	rec = GPIO_PIN_READ(pUART_Handler->RX.pGPIO,pUART_Handler->RX.config.Pin);
	return rec;

}
/*********************************************************************
 * @fn      		  -	UART_Send_Rec_Byte
 *
 * @brief             -	This function sends and receives a Byte of message with parity bit
 * 					  -
 *
 * @param[in]         -	pointer to the UART Handler
 * @param[in]         -	Pointer to the Message Byte to be transmitted
 * @param[in]         -	Pointer to the Received Byte of Message
 *
 * @return            -	None
 *
 * @Note              -	DRIVER HELPER API
 *

 */
void UART_Send_Rec_Byte(UART_Handler_t * pUART_Handler, uint8_t * pMSG_Send, uint8_t * pMSG_Rec)
{
	uint8_t send= * pMSG_Send, count=0;
	for(uint8_t i=0; i<8;i++)
	{
	UART_Send_Rec_Bit(pUART_Handler, (send & 0x01));
	if((send & 1) == 1)
	{
		count++;
	}
	send = send >> 1;
	}
	count++;			//for count%2 to intimate 1 for even nos of set bit
	UART_Parity_Bit(pUART_Handler, count%2);
}

void UART_Rec_Byte(UART_Handler_t * pUART_Handler, uint8_t * pMSG_Rec)
{
	uint rec=0x00;
	 for(uint8_t i=0;i<8;i++)
	 {
		 rec |= (UART_Rec_bit(pUART_Handler)<<7);
		 rec = rec >> 1;									 //lsb first

	 }
	 *pMSG_Rec = rec;
}
/*********************************************************************
 * @fn      		  - UART_MSG_SEND_REC
 *
 * @brief             -	This function sends a STOP Bit, Byte of message , parity bit & stop bit
 * 					  -
 *
 * @param[in]         -	Pointer to the UART Handler
 * @param[in]         -	Pointer to the message to be sent
 * @param[in]         - Pointer to the Message received
 *
 * @return            -	Length of message in Bytes
 *
 * @Note              -	APPLICATION LAYER API
 *

 */
void UART_MSG_SEND_REC(UART_Handler_t * pUART_Handler, uint8_t * pMSG_Send, uint8_t * pMSG_Rec , uint8_t length)
{
	if(pUART_Handler->UART_Config.Status == ENABLE)
	{
		//TX
		UART_Start_End(pUART_Handler, START);

		for(uint8_t i=0; i < length; ++i)
		{
		UART_Send_Rec_Byte(pUART_Handler, pMSG_Send, pMSG_Rec);
		pMSG_Send ++;
		pMSG_Rec ++;
		}

		UART_STOP_Bit(pUART_Handler);

		//RX
	}
}


