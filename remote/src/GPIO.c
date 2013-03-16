/*
 * GPIO.c
 *
 *  Created on: Nov 13, 2010
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "GPIO.h"



void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;



	/* Configure USART3 Tx (PB10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART3 Rx (PB11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* LED1 & LED2 */
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED2_PIN;
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

	/* TIM4 CH4 configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}





/**
 * @brief  Debounces a digital input.
 * @param  IOstate: Specifies the raw input state seen on the input port pin.

 * @retval 0, 1 this is the debounced input state
 */
uint8_t debounce(uint16_t IOstate)
{
	static uint32_t state = 0;
	static uint16_t debounce = 0;

	if(IOstate != 0)
		IOstate = 1;

	state = (state<<1) | IOstate;

	if(state == 0)
		debounce = 0;
	if(state == 0xFFFFFFFF)
		debounce = 1;

	return debounce;
}




const uint16_t GPIO_PIN[2] = {LED1_PIN, LED2_PIN};
GPIO_TypeDef* GPIO_PORT[2] = {LED1_GPIO_PORT, LED2_GPIO_PORT};

/**
 * @brief  Toggles the selected LED.
 * @param  Led: Specifies the Led to be toggled.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 * @retval None
 */
void LEDToggle(Led_TypeDef Led)
{
	GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**
 * @brief  Turns selected LED On.
 * @param  Led: Specifies the Led to be set on.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 * @retval None
 */
void LEDOn(Led_TypeDef Led)
{
	GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}

/**
 * @brief  Turns selected LED Off.
 * @param  Led: Specifies the Led to be set off.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 * @retval None
 */
void LEDOff(Led_TypeDef Led)
{
	GPIO_PORT[Led]->BRR = GPIO_PIN[Led];
}
