/*
 * I2C.h
 *
 *  Created on: Feb 19, 2024
 *      Author: 10820302
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "G0B1RE.h"
#include "GPIO.h"
/********************************
 * Macros
 */
#define ERROR  0x00
#define SUCESS 0x01

#define ACK 	RESET
#define NACK    SET

#define STOP	0
#define START	1

/***********************************
 * Config and Handler structure
 * *********************************
 */
typedef struct{
	uint8_t STATUS;
	uint8_t Baudrate;
	uint8_t slave_address;
	GPIO_Regdef_t * pPort;
	uint8_t PIN_SCLK;
	uint8_t	PIN_SDA_w;
	uint8_t	PIN_SDA_r;
	uint8_t Page;
	uint8_t Memory;

}I2C_config_t;

typedef struct {
I2C_config_t i2c_config;
GPIO_Handler_t SDA_w;
GPIO_Handler_t SDA_r;
GPIO_Handler_t SCLK;

}I2C_handler_t;

/**********************************************************************
 * 								 APIs
 ***********************************************************************/

void I2C_INI_DEINI (I2C_handler_t * pSPI_Handler, uint8_t INIorDIINI);
uint8_t I2C_En_or_DI(I2C_config_t* pi2c_config, uint8_t EnorDi );
void I2C_Send_Msg(I2C_handler_t* pi2c_handler,uint8_t* pSEND_MSG,uint32_t Length);

void I2C_address_Write(I2C_handler_t* pi2c_handler, uint8_t Write_or_Read);
//no need  void I2C_Clk_toggle(void);
void I2C_Send_Byte(I2C_handler_t* pi2c_handler,uint8_t * pMSG_send );
void I2C_Send_Bit(I2C_handler_t* pi2c_handler ,uint8_t SETorReset);
uint8_t I2C_Rec_Bit(I2C_handler_t* pi2c_handler );
void I2C_Rec_Byte(I2C_handler_t* pi2c_handler,uint8_t * pMSG_Rec );
void I2C_Rec_Msg(I2C_handler_t* pi2c_handler,uint8_t* pREC_MSG,uint32_t Length);
uint8_t I2C_Ack_check(I2C_handler_t* pi2c_handler);
void I2C_Error_handler(void);
void delay(uint8_t div);
void I2C_PageADDR_Write(I2C_handler_t* pi2c_handler);
void I2C_MemADDR_Write(I2C_handler_t* pi2c_handler);
void I2C_Start_End(I2C_handler_t * pI2C_Handler, uint8_t STARTorSTOP);
void delay_1(uint8_t div);

#endif /* INC_I2C_H_ */
