
/*
 * GPIO_DRIVER.H
 *
 *  Created on: Dec 11, 2023
 *      Author: 10820302
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_


#include "G0B1RE.h"


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 					Macros
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*
 * PORT
 */
/*No Need of this as REGDEF structure is also there
 * #define PORT_A			0x00
#define PORT_B			0x01
#define PORT_C			0x02
#define PORT_D			0x03
#define PORT_E			0x04
#define PORT_F			0x05
#define PORT_G			0x06
*/


/*
 * PIN
 */
#define PIN_0			0x00
#define PIN_1			0x01
#define PIN_2			0x02
#define PIN_3			0x03
#define PIN_4			0x04
#define PIN_5			0x05
#define PIN_6			0x06
#define PIN_7			0x07
#define PIN_8			0x08
#define PIN_9			0x09
#define PIN_10			0x0A
#define PIN_11			0x0B
#define PIN_12			0x0C
#define PIN_13			0x0D
#define PIN_14			0x0E
#define PIN_15			0x0F

/*
 * MODE @GPIO_MODE
 */
#define GPIO_MODE_IN		0x00
#define GPIO_MODE_OUT		0x01
#define GPIO_MODE_AF		0x02
#define GPIO_MODE_AN		0x03

/*
 *  OutType
 */
#define GPIO_OTYPE_PP		0x00
#define GPIO_OTYPE_OD		0x01

/*
 * OutputSpeed
 */
#define GPIO_OSPEED_VL		0x00
#define GPIO_OSPEED_L		0x01
#define GPIO_OSPEED_H		0x02
#define GPIO_OSPEED_VH		0x03
/*
 * Pull up pull down
 */
#define GPIO_PUPD_NO		0x00
#define GPIO_PUPD_PU		0x01
#define GPIO_PUPD_PD		0x02
/*
 * Alternate Function
 */


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 		Handler and Configuration Structure
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 */
/*
 * Configuration structure
 */
typedef struct
{
	GPIO_Regdef_t * pPort;
	uint8_t Pin;
	uint8_t Mode;
	uint8_t OType;
	uint8_t PUPD;
	uint8_t OSpeed;
	uint8_t AF;
}GPIO_Config_t;

/*
 * Handler structure
 */
typedef struct
{
	GPIO_Regdef_t* pGPIO;
	GPIO_Config_t config;

}GPIO_Handler_t;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * 				API Declaration
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*
 * The declaration establishes the names and characteristics
 * of a function but does not allocate storage for it, while
 * the definition specifies the body for a function, associates
 * an identifier with the function, and allocates storage for it.
 */

/*
So first I need to configure the peripheral
(first check and initialization of car)
(define every gear function (r/f), )
application layer does the steering and makes use of the defined gear for a function
*/

/*
 * 			Initializing API
 */
void GPIO_EN_DI (GPIO_Regdef_t * pGPIO, uint8_t ENorDI);
void GPIO_INI (GPIO_Handler_t * pHandler);
/*
 * 			Send data receive data
 */
void GPIO_PIN_SEND(GPIO_Regdef_t * pGPIO, uint8_t PIN, uint8_t SETorRESET);
uint8_t GPIO_PIN_READ(GPIO_Regdef_t * pGPIO, uint8_t PIN);
void GPIO_PORT_SEND(GPIO_Regdef_t * pGPIO, uint16_t Data);
uint16_t GPIO_PORT_READ(GPIO_Regdef_t * pGPIO);
void GPIO_PIN_Toggle(GPIO_Regdef_t * pGPIO, uint8_t PIN);

/*
 * Blocking APIs
 */

/*
 * Internal APIs
 */


#endif /* INC_GPIO_H_ */
