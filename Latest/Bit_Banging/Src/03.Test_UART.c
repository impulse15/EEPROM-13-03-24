/*
 * 03.Test_UART.c
 *
 *  Created on: Jan 14, 2024
 *      Author: 10820302
 */
#include "G0B1RE.h"
#include "UART.h"

//problem with the file inclusion


void UART_Setup(UART_Handler_t * pUART)
{
	pUART->UART_Config.Baudrate = 2;
	pUART->UART_Config.Frame_format = UART_FRFRMT_8B;
	pUART->UART_Config.OverSampMode = UART_OVRSAMP_8;
	pUART->UART_Config.PIN_RX = PIN_0;
	pUART->UART_Config.PIN_TX = PIN_1;
	pUART->UART_Config.Parity_ENorDI = UART_PARITY_CTR_EI;
	pUART->UART_Config.Parity_Mode = UART_PARITY_MODE_EV;
	pUART->UART_Config.RX_EN = DISABLE;
	pUART->UART_Config.STOP_Bits = UART_STP_BIT_ONE;
	pUART->UART_Config.TX_EN = ENABLE;
	pUART->UART_Config.pPort = GPIOA;
	pUART->UART_Config.Status = DISABLE;

}



int main()
{
	uint8_t Msg_send[]="hi hello", Msg_rec[5];
	UART_Handler_t UART;
	UART_EN_DI(&(UART.UART_Config), ENABLE);
	UART_INI_DEINI(&UART, INITIALIZE);

	UART_MSG_SEND_REC(&UART, Msg_send, Msg_rec, 10);

	UART_INI_DEINI(&UART, DEINITIALIZE);
	UART_EN_DI(&(UART.UART_Config), DISABLE);

}
