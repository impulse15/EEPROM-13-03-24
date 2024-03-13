/*
 * GPIO.c
 *
 *  Created on: Dec 12, 2023
 *      Author: 10820302
 */


#include "GPIO.h"


/*
 * 			Initializing API
 */

/*********************************************************************
 * @fn      		  - GPIO_EN_DI
 *
 * @brief             - Function Enables/Disables peripheral clock
 *
 * @param[in]         -	Macros of Base address of the GPIO peripheral
 * @param[in]         -	Enable/Disable macros
 * @param[in]         -
 *
 * @return            - None
 *
 * @Note              - APPLICATION LAYER API

 */
void GPIO_EN_DI (GPIO_Regdef_t * pGPIO, uint8_t ENorDI)
{
	if (ENorDI == ENABLE)
	{
		//enable this in RCC
		if (pGPIO == GPIOA)
		{
			RCC->IOPENR |= (0x01 << 0);
		}
		else if (pGPIO == GPIOB)
		{
			RCC->IOPENR |= (0x01 << 1);
		}
		else if (pGPIO == GPIOC)
		{
			RCC->IOPENR |= (0x01 << 2);
		}
		else if (pGPIO == GPIOD)
		{
			RCC->IOPENR |= (0x01 << 3);
		}
		else if (pGPIO == GPIOE)
		{
			RCC->IOPENR |= (0x01 << 4);
		}
		else if (pGPIO == GPIOF)
		{
			RCC->IOPENR |= (0x01 << 5);
		}

	}

	else
		{
		if (pGPIO == GPIOA)
		{
			RCC->IOPENR &= ~(0x01 << 0);
		}
		else if (pGPIO == GPIOB)
		{
			RCC->IOPENR &= ~(0x01 << 1);
		}
		else if (pGPIO == GPIOC)
		{
			RCC->IOPENR &= ~(0x01 << 2);
		}
		else if (pGPIO == GPIOD)
		{
			RCC->IOPENR &= ~(0x01 << 3);
		}
		else if (pGPIO == GPIOE)
		{
			RCC->IOPENR &= ~(0x01 << 4);
		}
		else if (pGPIO == GPIOF)
		{
			RCC->IOPENR &= ~(0x01 << 5);
		}

		}
	}

/*********************************************************************
 * @fn      		  - GPIO_INI
 *
 * @brief             - Initializes the Pin according to configuration variable
 *
 * @param[in]         -	Pointer to the GPIO_Handler
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - None
 *
 * @Note              - APPLICATION LAYER API

 */


void GPIO_INI (GPIO_Handler_t * pHandler)
{	//select the port
	pHandler->pGPIO=pHandler->config.pPort;

	//Enable the input

	//SET PUPD
	pHandler->pGPIO->PUPD &= ~(0x3 << 2*(pHandler->config.Pin));
	pHandler->pGPIO->PUPD |= pHandler->config.PUPD << 2*(pHandler->config.Pin);
	//SET ACCORDING TO MODE
	pHandler->pGPIO->Mode &= ~(0x3 << 2*(pHandler->config.Pin));						//logic missed ;corrected
	pHandler->pGPIO->Mode |= pHandler->config.Mode << 2*(pHandler->config.Pin);
	if(pHandler->config.Mode == GPIO_MODE_IN)
	{
		// Do Nothing
	}
	else if(pHandler->config.Mode == GPIO_MODE_OUT)
	{
		pHandler->pGPIO->OutType &= ~(0x1 << (pHandler->config.Pin));
		pHandler->pGPIO->OutType |= pHandler->config.OType << pHandler->config.Pin;
		pHandler->pGPIO->OutSpeed &= ~(0x3 << (pHandler->config.Pin));
		pHandler->pGPIO->OutSpeed |= pHandler->config.OSpeed << 2*(pHandler->config.Pin);
	}
	else if(pHandler->config.Mode == GPIO_MODE_AN)
	{
		//Analog Function
	}
	else if(pHandler->config.Mode == GPIO_MODE_AF)
	{
		//Alternate function
	}


}
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 						Send data receive data
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 */

/*********************************************************************
 * @fn      		  - GPIO_PIN_SEND
 *
 * @brief             - Output on the PiN
 *
 * @param[in]         - Macro of Base address of the GPIO peripheral
 * @param[in]         - Pin Number Macro
 * @param[in]         -	SET/RESET Macro
 *
 * @return            - None
 *
 * @Note              - APPLICATION LAYER API

 */
void GPIO_PIN_SEND(GPIO_Regdef_t * pGPIO, uint8_t PIN, uint8_t SETorRESET)
{
	if( SETorRESET == ENABLE)
	 pGPIO->Data_OUT |= 1 << PIN ;
	else
		pGPIO->Data_OUT &= ~(1 << PIN);
}

/*********************************************************************
 * @fn      		  - GPIO_PIN_READ
 *
 * @brief             - Input on the PiN
 *
 * @param[in]         - Macro of Base address of the GPIO peripheral
 * @param[in]         - Pin Number Macro
 * @param[in]         -
 *
 * @return            - 1 Byte Read value (Consider only LSB)
 *
 * @Note              - APPLICATION LAYER API

 */
uint8_t GPIO_PIN_READ(GPIO_Regdef_t * pGPIO, uint8_t PIN)
{
	if ((1<<PIN)& pGPIO->Data_IN)
		return 0x01;
	else
		return 0x00;
}

/*********************************************************************
 * @fn      		  - GPIO_PORT_SEND
 *
 * @brief             - Sends half word data through all the Pins of the port
 *
 * @param[in]         -	Pointer to the Base address of the GPIO peripheral Macros
 * @param[in]         -	16Bit data to be sent
 * @param[in]         -
 *
 * @return            - None
 *
 * @Note              - APPLICATION LAYER API

 */
void GPIO_PORT_SEND(GPIO_Regdef_t * pGPIO, uint16_t Data)
{
	pGPIO->Data_IN = Data;
}

/*********************************************************************
 * @fn      		  - GPIO_PORT_READ
 *
 * @brief             - Reads from all the 16 Pins of the Specific Port
 *
 * @param[in]         - Pointer to the Base address of the GPIO peripheral Macros
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - 16 Bit Read Data
 *
 * @Note              - APPLICATION LAYER API

 */
uint16_t GPIO_PORT_READ(GPIO_Regdef_t * pGPIO)
{
	return pGPIO->Data_IN;
}

/*********************************************************************
 * @fn      		  - GPIO_PIN_Toggle
 *
 * @brief             - Toggles the Pin which is set as output
 *
 * @param[in]         -	Base address of the GPIO peripheral Macro
 * @param[in]         -	Pin number Macro
 * @param[in]         -
 *
 * @return            -	None
 *
 * @Note              - APPLICATION LAYER API

 */
void GPIO_PIN_Toggle(GPIO_Regdef_t * pGPIO, uint8_t PIN)
{
	pGPIO->Data_OUT ^= (0x01 << PIN);
}
