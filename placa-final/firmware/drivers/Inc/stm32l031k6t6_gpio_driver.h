/*
 * stm32l031k6t6_gpio_driver.h
 *
 *  Created on: 26 de ago de 2021
 *      Author: luan
 */

#ifndef SRC_STM32L031K6T6_GPIO_DRIVER_H_
#define SRC_STM32L031K6T6_GPIO_DRIVER_H_

#include "stm32l031k6t6.h"

/*
 * This is a Handle structure for GPIO pin
 */


typedef struct
{
	uint8_t GPIO_PinNumber;					/*<		Possible values from @GPIO_PIN_NUMBERS 	>*/
	uint8_t GPIO_PinMode;					/*<		Possible values from @GPIO_PIN_MODES 	>*/
	uint8_t GPIO_PinSpeed;					/*< 	Possible values from @GPIO_PIN_SPEEDS 	>*/
	uint8_t GPIO_PinPuPdControl;			/*< 	Possible values from @GPIO_PIN_PUPD 	>*/
	uint8_t GPIO_PinOPType;					/*< 	Possible values from @GPIO_PIN_OPTYPE 	>*/
	uint8_t GPIO_PinAltFunMode;				/*< 	Possible values from @GPIO_PIN_ALTFUN 	>*/
}GPIO_PinConfig_t;


typedef struct
{

	GPIO_RegDef_t *pGPIOx;					/*This holds the base address of the GPIO pin port to which the pin belongs*/
	GPIO_PinConfig_t GPIO_PinConfig;		/*This holds GPIO pin configuration settings*/

}GPIO_Handle_t;

/*
 * @GPIO_PIN_Numbers
 * GPIO pin possible numbers
 *
 * @Note:
 * For my category (L031X --> Category 2) the ports that are full-featured (0 to 15): GPIOA and GPIOB
 * For other available ports, GPIOC and GPIOH, the range that we can use are GPIOC[0][13:15] / GPIOH[0:1]
 * GPIOD and GPIOE isn't available in this category.
 * Therefore, for others STM32L0XX, check the datasheet to reference in the right way.
 */

#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15


/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */

#define GPIO_MODE_INPUT 	0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4			// Interrupt mode - Falling edge
#define	GPIO_MODE_IT_RT		5			// Interrupt mode - Rising edge
#define	GPIO_MODE_IT_FRT	6			// Interrupt mode - Falling/Rising edge

/*
 * @GPIO_PIN_OPTYPE
 * GPIO pin possible output types
 */

#define GPIO_OP_TYPE_PP		0			// Push pull
#define GPIO_OP_TYPE_OD		1			// Open drain

/*
 * @GPIO_PIN_SPEEDS
 * GPIO pin possible output speeds
 */

#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

/*
 * @GPIO_PIN_PUPD
 * GPIO pin pull up and pull down configuration macros
 */

#define GPIO_NO_PUPD		0			// No pull-up or pull-down
#define	GPIO_PIN_PU			1
#define GPIO_PIN_PD			2

/**************************************************************************************************************
 * 							APIs supported by this driver - GPIOA & GPIOB Section
 **************************************************************************************************************/


/*
 * Peripheral Clock setup
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * Init and De Init
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data read and write
 */

uint8_t GPIO_ReadFormInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFormInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 * IRQ Configuration and ISR handling
 */

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);



#endif /* SRC_STM32L031K6T6_GPIO_DRIVER_H_ */
