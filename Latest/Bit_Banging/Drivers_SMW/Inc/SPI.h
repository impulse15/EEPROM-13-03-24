/*
 * SPI.h
 *
 *  Created on: Dec 20, 2023
 *      Author: 10820302
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "G0B1RE.h"
#include "GPIO.h"


/**************************************************************
 * 				Macros for configuration register
 **************************************************************/

#define SPI_CPOL_EN		SET
#define SPI_CPOL_DI		RESET
#define SPI_CPHA_EN		SET
#define SPI_CPHA_DI		RESET

#define SPI_BAUDRATE_DIV2		0x00
#define SPI_BAUDRATE_DIV4		0x01
#define SPI_BAUDRATE_DIV8		0x02
#define SPI_BAUDRATE_DIV16		0X03
#define SPI_BAUDRATE_DIV32		0X04
#define SPI_BAUDRATE_DIV64		0X05
#define SPI_BAUDRATE_DIV128		0X06
#define SPI_BAUDRATE_DIV256		0X07


#define SPI_DATA_FORMAT_MSBF		RESET
#define SPI_DATA_FORMAT_LSBF 		SET

#define SPI_MSG_8Bit				0x00
#define SPI_MSG_16Bit				0x01

#define SPI_DATA_Size_8bits			0x00
#define SPI_DATA_Size_16bits		0x01




/*
 *user configuration register
 */
typedef struct
{	uint8_t STATUS;
	uint8_t CPOL;
	uint8_t CPHA;
	uint8_t Baudrate;
	uint8_t * MSG_Receive;
	uint8_t	DATA_Format;
	GPIO_Regdef_t * pPort;
	uint8_t PIN_MOSI;
	uint8_t	PIN_MISO;
	uint8_t PIN_NS;
	uint8_t PIN_CLK;
	uint8_t DATA_Size;							//Only 8bits implemented
	/*CPOL
		CPHA
		speed
		data_send
		data_receive
		Bit size         once confirm this
		mode only receive only send      //make it as one function only @send_receive */
}SPI_config_t;



typedef struct{
	SPI_config_t SPI_Config;
	GPIO_Handler_t MOSI;
	GPIO_Handler_t MISO;
	GPIO_Handler_t CLK;
	GPIO_Handler_t NS;
}SPI_Handler_t;
/*
 * Handler for SPI bit banging
 * No handler required
 */


/*
 * make a drive for
 * toggle
 * send a bit
 * send a byte
 * receive a bit
 * receive a byte
 * clock handler ( set and drive the pin)
 * handler for CPOL CPHA
 * independent helper API for the MOSI and MISO
 * select pin
 * no clock stretching hence no clock check
 *
 */

/*
 * Initialize SPI by configuring GPIO Pins.
 */
uint8_t SPI_EN_DI(SPI_config_t * pSPI_config, uint8_t EnorDi);
void SPI_INI_DEINI (SPI_Handler_t * pSPI_Handler, uint8_t INIorDIINI);
/*
 * Send Receive API
 */
void SPI_Start_End(SPI_Handler_t * pSPI_Handler, uint8_t STARTorSTOP);
void SPI_Clk_toggle(GPIO_Handler_t * pClk_handler);
uint8_t SPI_Bit_Send_Rec(SPI_Handler_t * pSPI_Handler ,uint8_t SETorReset);
void SPI_Byte_Send_Rec(SPI_Handler_t * pSPI_Handler,uint8_t * MSG_send , uint8_t * MSG_REC);
void SPI_MSG_Send_Rec(SPI_Handler_t * pSPI_Handler, uint8_t * MSG_send , uint8_t * MSG_REC, uint32_t Length );


/*
 * timing APIs
*/




/*
 * initial setup according to cpha cpol
 * send bit api use toggle feature
 * send whole byte( size variable
 * send message (collection of bytes)
 */


#endif /* INC_SPI_H_ */
