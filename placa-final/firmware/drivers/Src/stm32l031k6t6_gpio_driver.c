/*
 * stm32l031k6t6_gpio_driver.c
 *
 *  Created on: 26 de ago de 2021
 *      Author: luan
 */

#include "stm32l031k6t6_gpio_driver.h"
#include <stdint.h>

/***********************************************************************************
 * @fn						- GPIO_PeriClockControl
 *
 * @brief					- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]				- Base address of the GPIO peripheral
 * @param[in]				- ENABLE or DISABLE macros
 *
 *
 * @return					- none
 *
 * @Note					- none

 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}

	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
	}

}

/***********************************************************************************
 * @fn						- GPIO_Init
 *
 * @brief					-
 *
 * @param[in]				-
 * @param[in]				-
 *
 *
 * @return					- none
 *
 * @Note					- none

 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;	//temp register
	uint32_t temp1 = 0;	//temp register
	uint32_t temp2 = 0;	//temp register
	//1 - Configure the mode of gpio pin

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ); // Each mode carries 2 bit to configure.																									   // For pin 0 --> MODE[0:1]. For pin 1 --> MODE[2:3]
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) + (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)%2 )); //clearing
		pGPIOHandle->pGPIOx->MODER |= temp; // Use bitwise or to change only the pin that was requested


	}else
	{
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// Configure Falling Edge
			EXTI->FTSR	|= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR	&= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// Configure Rising Edge
			EXTI->RTSR	|= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR	&= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FRT)
		{
			// Configure Falling and Rising Edge
			EXTI->FTSR	|= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR	|= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		// Configure de GPIO port selection in the SYSCGF_EXTICR
		temp1 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)/4;
		temp2 = ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)%4)*4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle ->pGPIOx);

		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] |= portcode << temp2;

		// Enable de EXTI interrupt delivery using IMR
		EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	}

	temp = 0;

	//2 - Configure the speed

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) + (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)%2 ));

	temp = 0;

	//3 - Configure the pull-up pull-down settings

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) + (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)%2 )); //clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	//4 - Configure the output type

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		// Configure the alt function registers.
		uint8_t	temp1,temp2;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~( 0xF << ( 4 * temp2 ) ); //clearing
		pGPIOHandle->pGPIOx->AFR[temp1]	|= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4 * temp2 ) );
	}

	//5 - Configure the Alternate Function
}

/***********************************************************************************
 * @fn						- GPIO_DeInit
 *
 * @brief					- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]				- Base address of the GPIO peripheral
 * @param[in]				- ENABLE or DISABLE macros
 *
 *
 * @return					- none
 *
 * @Note					- none

 */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
			{
				GPIOA_REG_RESET();
			}
			else if(pGPIOx == GPIOB)
			{
				GPIOB_REG_RESET();
			}
			else if(pGPIOx == GPIOC)
			{
				GPIOC_REG_RESET();
			}
			else if(pGPIOx == GPIOD)
			{
				GPIOD_REG_RESET();
			}
			else if(pGPIOx == GPIOE)
			{
				GPIOE_REG_RESET();
			}
			else if(pGPIOx == GPIOH)
			{
				GPIOH_REG_RESET();
			}


}

/***********************************************************************************
 * @fn						- ReadFormInputPin
 *
 * @brief					-
 *
 * @param[in]				- Base address of the GPIO peripheral
 * @param[in]				- ENABLE or DISABLE macros
 *
 *
 * @return					- none
 *
 * @Note					- none

 */

uint8_t GPIO_ReadFormInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{

	uint8_t value;
	value = (uint8_t )((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}


/***********************************************************************************
 * @fn						- GPIO_ReadFormInputPort
 *
 * @brief					- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]				- Base address of the GPIO peripheral
 * @param[in]				- ENABLE or DISABLE macros
 *
 *
 * @return					- none
 *
 * @Note					- none

 */

uint16_t GPIO_ReadFormInputPort(GPIO_RegDef_t *pGPIOx)

{
	uint16_t value;
	value = (uint16_t ) pGPIOx->IDR;
	return value;
}




/***********************************************************************************
 * @fn						- GPIO_WriteToOutputPin
 *
 * @brief					- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]				- Base address of the GPIO peripheral
 * @param[in]				- ENABLE or DISABLE macros
 *
 *
 * @return					- none
 *
 * @Note					- none

 */

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{

	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

/***********************************************************************************
 * @fn						- GPIO_WriteToOutputPort
 *
 * @brief					- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]				- Base address of the GPIO peripheral
 * @param[in]				- ENABLE or DISABLE macros
 *
 *
 * @return					- none
 *
 * @Note					- none

 */

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{

		pGPIOx->ODR = Value;

}

/***********************************************************************************
 * @fn						- GPIO_ToggleOutputPin
 *
 * @brief					- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]				- Base address of the GPIO peripheral
 * @param[in]				- ENABLE or DISABLE macros
 *
 *
 * @return					- none
 *
 * @Note					- none

 */

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{

	pGPIOx->ODR ^= (1 << PinNumber);

}

/***********************************************************************************
 * @fn						- GPIO_IRQConfig
 *
 * @brief					- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]				- Base address of the GPIO peripheral
 * @param[in]				- ENABLE or DISABLE macros
 *
 *
 * @return					- none
 *
 * @Note					- In this processor, the NVIC_ISER has 32 bits, to other microcontroller
 * 							this range can be different.

 */

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
	{

		*NVIC_ISER |= (1 << IRQNumber);


	}else
	{

	}





}


void GPIO_IRQPriorityConfig(uint8_t IRQPriority, uint8_t IRQNumber)

{

	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber%4;
	uint8_t shift_amount = (8 * iprx_section ) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_IPR_BASE_ADDR + iprx * 4) |= (IRQPriority << shift_amount);

}


/***********************************************************************************
 * @fn						- GPIO_IRQHandling
 *
 * @brief					- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]				- Base address of the GPIO peripheral
 * @param[in]				- ENABLE or DISABLE macros
 *
 *
 * @return					- none
 *
 * @Note					- none

 */

void GPIO_IRQHandling(uint8_t PinNumber)
{

}

