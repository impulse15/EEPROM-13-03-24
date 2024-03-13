/*
 * G0B1RE.h
 *
 *  Created on: Dec 11, 2023
 *      Author: 10820302
 */

#ifndef INC_G0B1RE_H_
#define INC_G0B1RE_H_

#include <stdint.h>

//macors

#define vol_			volatile
#define ENABLE 			0x1
#define DISABLE 		0x0
#define SET				ENABLE
#define RESET			DISABLE
#define INITIALIZE		SET
#define DEINITIALIZE	RESET
/*
 * This header file contains addresses of the peripheral memory and structures of the of the engine registers.
 */
#define BASEADDR_RAM        0x00000000
#define BASEADDR_FLASH      0x08000000
#define BASEADDR_ROM        0x1FFF0000  //not sure about
#define BASEADDR_OTP        0x1FFF7000
#define BASEADDR_PERIPHERAL 0x40000000


#define BASEADDR_BUS_APB1	(BASEADDR_PERIPHERAL + 0x00000000)
//#define BASEADDR_BUS_APB2	(BASEADDR_PERIPHERAL + 0x20000)
#define BASEADDR_BUS_AHB	(BASEADDR_PERIPHERAL + 0x0020000)
#define BASEADDR_BUS_IOPORT	(BASEADDR_PERIPHERAL + 0x10000000)


#define BASEADDR_BUS_AHB_RCC	(BASEADDR_BUS_AHB + 0x00001000)


#define BASEADDR_IOPORT_GPIOA	(BASEADDR_BUS_IOPORT + 0x0000)
#define BASEADDR_IOPORT_GPIOB	(BASEADDR_BUS_IOPORT + 0x0400)
#define BASEADDR_IOPORT_GPIOC	(BASEADDR_BUS_IOPORT + 0x0800)
#define BASEADDR_IOPORT_GPIOD	(BASEADDR_BUS_IOPORT + 0x0C00)
#define BASEADDR_IOPORT_GPIOE	(BASEADDR_BUS_IOPORT + 0x1000)
#define BASEADDR_IOPORT_GPIOF	(BASEADDR_BUS_IOPORT + 0x1400)
#define BASEADDR_IOPORT_GPIOG	(BASEADDR_BUS_IOPORT + 0x1800)

typedef struct {
	uint32_t vol_ Mode ;
	uint32_t vol_ OutType;
	uint32_t vol_ OutSpeed;
	uint32_t vol_ PUPD;
	uint32_t vol_ Data_IN;
	uint32_t vol_ Data_OUT;
	uint32_t vol_ BSRR;
	uint32_t vol_ LCKR;
	uint32_t vol_ AFRL[2];
	uint32_t vol_ BRR;
}GPIO_Regdef_t;

#define GPIOA ((GPIO_Regdef_t *)BASEADDR_IOPORT_GPIOA)
#define GPIOB ((GPIO_Regdef_t *)BASEADDR_IOPORT_GPIOB)
#define GPIOC ((GPIO_Regdef_t *)BASEADDR_IOPORT_GPIOC)
#define GPIOD ((GPIO_Regdef_t *)BASEADDR_IOPORT_GPIOD)
#define GPIOE ((GPIO_Regdef_t *)BASEADDR_IOPORT_GPIOE)
#define GPIOF ((GPIO_Regdef_t *)BASEADDR_IOPORT_GPIOF)
#define GPIOG ((GPIO_Regdef_t *)BASEADDR_IOPORT_GPIOG)

typedef struct {
	uint32_t vol_ CR;
	uint32_t vol_ ICSCR;
	uint32_t vol_ CFGR;
	uint32_t vol_ PLLCFGR;
	uint32_t vol_ const Reserved;
	uint32_t vol_ CRRCR;
	uint32_t vol_ CIER;
	uint32_t vol_ CIFR;
	uint32_t vol_ CICR;
	uint32_t vol_ IOPRSTR;
	uint32_t vol_ AHBRSTR;
	uint32_t vol_ AHBRSTR1;
	uint32_t vol_ AHBRSTR2;
	uint32_t vol_ IOPENR;
	uint32_t vol_ AHBENR;
	uint32_t vol_ APBENR1;
	uint32_t vol_ APBENR2;
	uint32_t vol_ IOPSMENR;
	uint32_t vol_ AHBSMENR;
	uint32_t vol_ APBSMENR1;
	uint32_t vol_ APBSMENR2;
	uint32_t vol_ CCIPR;
	uint32_t vol_ CCIPR2;
	uint32_t vol_ BDCR;
	uint32_t vol_ const CSR;
}RCC_Regdef_t;

#define RCC ((RCC_Regdef_t *) BASEADDR_BUS_AHB_RCC)

/*
 * Drivers are ready?
 * clock and peripheral
 * configure clock
 * have a good timing parameters
 * have an idea
 * gpio drivers can I build in a day(polling)( have to no option)
 * just whatever is necessary only that
 *
 */

#include "GPIO.h"
//#include "SPI.h"
#endif /* INC_G0B1RE_H_ */
