/*
 * stm32l031k6t6.h
 *
 *  Created on: Aug 25, 2021
 *      Author: Luan S. P. Crozatti
 */

#ifndef INC_STM32L031K6T6_H_
#define INC_STM32L031K6T6_H_

#include<stdint.h>

#define __vo volatile

/**************************** Processor Specific Details ************************/
/*
 * ARM Cortex M0+ Processor NVIC ISER register address
 */

#define NVIC_ISER				( (__vo uint32_t*)0xE000E100 )

#define NVIC_ICER				( (__vo uint32_t*)0xE000E180 )

#define NVIC_IPR_BASE_ADDR		( (__vo uint32_t*)0xE000E400 )

#define NO_PR_BITS_IMPLEMENTED	4
/*
 * base adresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR		0x08000000U /* <Base address of Flash Memory> */
#define SRAM_BASEADDR		0x20000000U	/* <Base address of SRAM> */

/* If you have another SRAM/ROM, add here */

/*
 * base adresses of different bus domains (AHB, APBX and IOPORT)
 */

#define PERIPH_BASE			0x40000000U	/* <Base address of Peripheral Registers> */
#define APB1_BASEADDR		PERIPH_BASE	/* <Base address of APB1 - Peripheral in this location: TIMER2> */
#define APB2_BASEADDR		0x40010000U	/* <Base address of APB2 - Peripheral in this location: SYSCFG,
COMP> */
#define AHB_BASEADDR		0x40020000U	/* <Base address of AHB - Peripheral in this location: DMA1> */
#define IOPORT_BASEADDR		0x50000000U	/* <Base address of IOPORT - Peripheral in this location: GPIOA> */

/*
 * base adresses of peripherals which are hanging on IOPORT bus
 */

#define GPIOA_BASEADDR		(IOPORT_BASEADDR + 0x0000)
#define GPIOB_BASEADDR		(IOPORT_BASEADDR + 0x0400)
#define GPIOC_BASEADDR		(IOPORT_BASEADDR + 0x0800)
#define GPIOD_BASEADDR		(IOPORT_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR		(IOPORT_BASEADDR + 0x1000)
#define GPIOH_BASEADDR		(IOPORT_BASEADDR + 0x1C00)

/*
 * base adresses of peripherals which are hanging on APB1 bus
 */

#define	I2C1_BASEADDR		(APB1_BASEADDR + 0x5400)
#define	I2C2_BASEADDR		(APB1_BASEADDR + 0x5800)
#define	I2C3_BASEADDR		(APB1_BASEADDR + 0x7800)

#define SPI2_BASEADDR		(APB1_BASEADDR + 0x3800)

#define LPUART1_BASEADDR	(APB1_BASEADDR + 0X4800)

#define USART2_BASEADDR		(APB1_BASEADDR + 0x4400)
#define USART4_BASEADDR		(APB1_BASEADDR + 0x4C00)
#define USART5_BASEADDR		(APB1_BASEADDR + 0x5000)

/*
 * base adresses of peripherals which are hanging on APB2 bus
 */

#define	EXTI_BASEADDR		(APB2_BASEADDR + 0x0400)
#define	SPI1_BASEADDR		(APB2_BASEADDR + 0x3000)
#define	USART1_BASEADDR		(APB2_BASEADDR + 0x3800)
#define	SYSCFG_BASEADDR		(APB2_BASEADDR + 0x0000)

/*
 * base adresses of peripherals which are hanging on AHB bus
 */

#define	RCC_BASEADDR		(AHB_BASEADDR + 0x1000)



/*
 * Peripheral register definition structures
 */


/*
 * Peripheral register definition structures for GPIO
 */
typedef struct
{
	__vo uint32_t MODER;			/*< GPIO port mode register Address offset: 0x00>*/
	__vo uint32_t OTYPER;			/*< GPIO port output type register Address offset: 0x04>*/
	__vo uint32_t OSPEEDR;			/*< GPIO port output speed register Address offset: 0x00>*/
	__vo uint32_t PUPDR;			/*< GPIO port pull-up/pull-down register Address offset: 0x00>*/
	__vo uint32_t IDR;				/*< GPIO port input data register Address offset: 0x00>*/
	__vo uint32_t ODR;				/*< GPIO port output data register Address offset: 0x00>*/
	__vo uint32_t BSRR;				/*< GPIO port bit set/reset register Address offset: 0x00>*/
	__vo uint32_t LCKR;				/*< GPIO port configuration lock register Address offset: 0x00>*/
	__vo uint32_t AFR[2]; 			/*< GPIO alternate function low/high register Address offset: 0x00>*/ /*AFR[0] --> LOW || AFR[1] --> HIGH */
}GPIO_RegDef_t;


/*
 * Peripheral register definition structures for RCC
 */
typedef struct
{
	__vo uint32_t CR;					/*< Clock control register: 0x00>*/
	__vo uint32_t ICSCR;				/*< Internal clock sources calibration register: 0x04>*/
	uint32_t RESERVED0;					/*< Reserved0: 0x08>*/
	__vo uint32_t CFGR;					/*< Clock configuration register Address offset: 0x0C>*/
	__vo uint32_t CIER;					/*< Clock interrupt enable register Address offset: 0x10>*/
	__vo uint32_t CIFR;					/*< Clock interrupt flag register Address offset: 0x14>*/
	__vo uint32_t CICR;					/*< Clock interrupt clear register Address offset: 0x18>*/
	__vo uint32_t IOPRSTR;				/*< GPIO reset register Address offset: 0x1C>*/
	__vo uint32_t AHBRSTR;				/*< AHB peripheral reset register Address offset: 0x20>*/
	__vo uint32_t APB2RSTR; 			/*< APB2 peripheral reset register Address offset: 0x24>*/
	__vo uint32_t APB1RSTR; 			/*< APB1 peripheral reset register Address offset: 0x28>*/
	__vo uint32_t IOPENR; 				/*< GPIO clock enable register Address offset: 0x2C>*/
	__vo uint32_t AHBENR; 				/*< AHB peripheral clock enable register Address offset: 0x30>*/
	__vo uint32_t APB2ENR; 				/*< APB2 peripheral clock enable register Address offset: 0x34>*/
	__vo uint32_t APB1ENR; 				/*< APB1 peripheral clock enable register Address offset: 0x38>*/
	__vo uint32_t IOPSMENR; 			/*< GPIO clock enable in Sleep mode register Address offset: 0x3C>*/
	__vo uint32_t AHBSMENR; 			/*< AHB peripheral clock enable in Sleep mode register Address offset: 0x40>*/
	__vo uint32_t APB2SMENR; 			/*< APB2 peripheral clock enable in Sleep mode register Address offset: 0x44>*/
	__vo uint32_t APB1SMENR; 			/*< APB1 peripheral clock enable in Sleep mode register Address offset: 0x48>*/
	__vo uint32_t CCIPR; 				/*< Clock configuration register Address offset: 0x4C>*/
	__vo uint32_t CSR; 					/*< Control/status register Address offset: 0x50>*/
}RCC_RegDef_t;


/*
 * Peripheral register definition structures for EXTI
 */

typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;

/*
 * Peripheral register definition structures for SYSCFG
 */

typedef struct
{
	__vo uint32_t CFGR1;
	__vo uint32_t CFGR2;
	__vo uint32_t EXTICR[4];
	__vo uint32_t COMP1_CTRL;
	__vo uint32_t COMP2_CTRL;
	__vo uint32_t CFGR3;
}SYSCFG_RegDef_t;


/*
 * peripheral definitions ( Peripheral base addresses typecasted to xxx_RegDef_t )
 */

#define GPIOA	((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB	((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC	((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD	((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE	((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH	((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC		((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI	((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG	((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()	( RCC->IOPENR |= ( 1 << 0 ) )
#define GPIOB_PCLK_EN()	( RCC->IOPENR |= ( 1 << 1 ) )
#define GPIOC_PCLK_EN()	( RCC->IOPENR |= ( 1 << 2 ) )
#define GPIOD_PCLK_EN()	( RCC->IOPENR |= ( 1 << 3 ) )
#define GPIOE_PCLK_EN()	( RCC->IOPENR |= ( 1 << 4 ) )
#define GPIOH_PCLK_EN()	( RCC->IOPENR |= ( 1 << 7 ) )


/*
 * Clock Enable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_EN()	( RCC->APB1ENR |= ( 1 << 21 ) )
#define I2C2_PCLK_EN()	( RCC->APB1ENR |= ( 1 << 22 ) )
#define I2C3_PCLK_EN()	( RCC->APB1ENR |= ( 1 << 30 ) )

/*
 * Clock Enable Macros for SPIx peripherals
 */

#define SPI1_PCLK_EN()	( RCC->APB2ENR |= ( 1 << 12 ) )
#define SPI2_PCLK_EN()	( RCC->APB1ENR |= ( 1 << 14 ) )

/*
 * Clock Enable Macros for USARTx peripherals
 */

#define USART1_PCLK_EN()	( RCC->APB2ENR |= ( 1 << 14 ) )
#define USART2_PCLK_EN()	( RCC->APB1ENR |= ( 1 << 17 ) )
#define USART4_PCLK_EN()	( RCC->APB1ENR |= ( 1 << 19 ) )
#define USART5_PCLK_EN()	( RCC->APB1ENR |= ( 1 << 20 ) )

/*
 * Clock Enable Macros for SYSCFG peripherals
 */

#define SYSCFG_PCLK_EN()	( RCC->APB2ENR |= ( 1 << 0 ) )

/*
 * Clock Disable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()	( RCC->IOPENR &= ~( 1 << 0 ) )
#define GPIOB_PCLK_DI()	( RCC->IOPENR &= ~( 1 << 1 ) )
#define GPIOC_PCLK_DI()	( RCC->IOPENR &= ~( 1 << 2 ) )
#define GPIOD_PCLK_DI()	( RCC->IOPENR &= ~( 1 << 3 ) )
#define GPIOE_PCLK_DI()	( RCC->IOPENR &= ~( 1 << 4 ) )
#define GPIOH_PCLK_DI()	( RCC->IOPENR &= ~( 1 << 7 ) )


/*
 * Clock Disable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_DI()	( RCC->APB1ENR &= ~( 1 << 21 ) )
#define I2C2_PCLK_DI()	( RCC->APB1ENR &= ~( 1 << 22 ) )
#define I2C3_PCLK_DI()	( RCC->APB1ENR &= ~( 1 << 30 ) )

/*
 * Clock Disable Macros for SPIx peripherals
 */

#define SPI1_PCLK_DI()	( RCC->APB2ENR &= ~( 1 << 12 ) )
#define SPI2_PCLK_DI()	( RCC->APB1ENR &= ~( 1 << 14 ) )

/*
 * Clock Disable Macros for USARTx peripherals
 */

#define USART1_PCLK_DI()	( RCC->APB2ENR &= ~( 1 << 14 ) )
#define USART2_PCLK_DI()	( RCC->APB1ENR &= ~( 1 << 17 ) )
#define USART4_PCLK_DI()	( RCC->APB1ENR &= ~( 1 << 19 ) )
#define USART5_PCLK_DI()	( RCC->APB1ENR &= ~( 1 << 20 ) )

/*
 * Clock Disable Macros for SYSCFG peripherals
 */

#define SYSCFG_PCLK_DI()	( RCC->APB2ENR &= ~( 1 << 0 ) )

/*
 * Macros to reset GPIOx peripherals
 */

#define GPIOA_REG_RESET()	do{( RCC -> IOPRSTR |= ( 1 << 0 ) ); ( RCC -> IOPRSTR &= ~( 1 << 0 ) ); }while(0)
#define GPIOB_REG_RESET()	do{( RCC -> IOPRSTR |= ( 1 << 1 ) ); ( RCC -> IOPRSTR &= ~( 1 << 1 ) ); }while(0)
#define GPIOC_REG_RESET()	do{( RCC -> IOPRSTR |= ( 1 << 2 ) ); ( RCC -> IOPRSTR &= ~( 1 << 2 ) ); }while(0)
#define GPIOD_REG_RESET()	do{( RCC -> IOPRSTR |= ( 1 << 3 ) ); ( RCC -> IOPRSTR &= ~( 1 << 3 ) ); }while(0)
#define GPIOE_REG_RESET()	do{( RCC -> IOPRSTR |= ( 1 << 4 ) ); ( RCC -> IOPRSTR &= ~( 1 << 4 ) ); }while(0)
#define GPIOH_REG_RESET()	do{( RCC -> IOPRSTR |= ( 1 << 7 ) ); ( RCC -> IOPRSTR &= ~( 1 << 7 ) ); }while(0)

#define GPIO_BASEADDR_TO_CODE(x)	(	(x == GPIOA) ? 0 :\
										(x == GPIOB) ? 1 :\
										(x == GPIOC) ? 2 :\
										(x == GPIOD) ? 3 :\
										(x == GPIOE) ? 4 :\
										(x == GPIOH) ? 5 :0	)

//Some generic macros

#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

// Generic macros for IRQ numbers

#define	IRQ_NO_EXTI1_0		5
#define	IRQ_NO_EXTI3_2		6
#define	IRQ_NO_EXTI15_4		7

#include "stm32l031k6t6_gpio_driver.h"


#endif /* INC_STM32L031K6T6_H_ */
