/*
 * UART.h
 *
 *  Created on: Jan 12, 2024
 *      Author: 10820302
 */
#include "G0B1RE.h"
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 							Macros
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
//@STOP_BIT
#define UART_STP_BIT_ONE			0x02
#define UART_STP_BIT_HALF			0x01
#define UART_STP_BIT_TWO			0x04
#define UART_STP_BIT_ONEHALF		0x03

//@PARITYCTR
#define UART_PARITY_CTR_DI			0x00
#define UART_PARITY_CTR_EI			0x01

//@PARITY_MODE
#define UART_PARITY_MODE_EV			0x00
#define UART_PARITY_MODE_OD			0x01

//@FRAME_FORMAT
#define UART_FRFRMT_8B				0x00
#define UART_FRFRMT_9B				0x01

//@OVERSAMP
#define UART_OVRSAMP_16				0x00
#define UART_OVRSAMP_8				0x01

//USED IN PARITY API
#define EVEN						SET
#define ODD							RESET

//USED IN START_STOP API
#define START 						SET
#define STOP						RESET

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 						Handler and configuration structure
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 */
typedef struct{
	uint8_t Status;
	GPIO_Regdef_t * pPort;
	uint8_t PIN_TX;
	uint8_t PIN_RX;
	uint16_t Baudrate;				//DIV_Mantissa[11:0]: mantissa of USARTDIV; DIV_Fraction[3:0]: fraction of USARTDIV
	uint8_t STOP_Bits;				//@STOP_BIT
	uint8_t Parity_ENorDI;			//@PARITYCTR
	uint8_t Parity_Mode;			//@PARITY_MODE
	uint8_t Frame_format;			//@FRAME_FORMAT
	//uint8_t Length;
	uint8_t OverSampMode;			//@OVERSAMP
	uint8_t TX_EN;
	uint8_t RX_EN;
	/*
	 * uint8_t RTS_EN;
	 * uint8_t CTS_EN;
	 */
}UART_Config_t;

typedef struct{
	GPIO_Handler_t TX;
	GPIO_Handler_t RX;
	/*
	 * 	GPIO_Handler_t RTS;
		GPIO_Handler_t CTS;
	 */
	UART_Config_t UART_Config;
}UART_Handler_t;

/*
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 								APIs
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*
 * Enable and Initializing APIs
 */
uint8_t UART_EN_DI(UART_Config_t * pUART_Conf , uint8_t ENorDI);
void UART_INI_DEINI(UART_Handler_t * pUART_Handler, uint8_t INIorDEINI);

/*
 * Transmission APIs
 */
void UART_Baudrate(uint8_t Baud_Div);
uint8_t UART_Oversampling(UART_Handler_t * pUART_Handler);
void UART_Start_End(UART_Handler_t * pUART_Handler, uint8_t StartorEnd);
void UART_STOP_Bit(UART_Handler_t * pUart_Handler);
void UART_Parity_Bit(UART_Handler_t * pUart_Handler, uint8_t EVorOD_1s);
uint8_t UART_Send_Rec_Bit(UART_Handler_t * pUART_Handler,uint8_t SetorReset);
void UART_Send_Rec_Byte(UART_Handler_t * pUART_Handler, uint8_t * MSG_Send, uint8_t * MSG_Rec);
void UART_MSG_SEND_REC(UART_Handler_t * pUART_Handler, uint8_t * pMSG_Send, uint8_t * pMSG_Rec , uint8_t length);



/*
 * Tasks to do:-
 * 					 write macros done
 	 	 	 	 	 modify api
 	 	 	 	 	 part1-write send APIs
 	 	 	 	 	 part2-write rec APIs
 	 	 	 	 	 	 	 include 'error invoke'


 */



/*
 * Look into :- deallocating Configuration memory after XXX_INI() API of every peripheral
 */

