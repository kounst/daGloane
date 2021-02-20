/*
 * GPIO.c
 *
 *  Created on: Nov 13, 2010
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x.h"
#include "stm32f1xx_hal.h"
#include "GPIO.h"
//#include "uAC.h"


void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	__HAL_AFIO_REMAP_SWJ_NOJTAG();
	__HAL_AFIO_REMAP_TIM3_PARTIAL();
	__HAL_AFIO_REMAP_TIM2_PARTIAL_1();
	// GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	// GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	// GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);

//   GPIO_InitTypeDef GPIO_InitStruct;
  
//   GPIO_InitStruct.Pin = GPIO_PIN_15;
//   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//   GPIO_InitStruct.Pull = GPIO_PULLUP;
//   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 

//   GPIO_InitStruct.Pin = GPIO_PIN_3;
//   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 

//   GPIO_InitStruct.Pin = GPIO_PIN_2;
//   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);   


	/* LED1 & LED2 */
	GPIO_InitStructure.Pin = LED1_PIN;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = LED2_PIN;
	HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

//	LEDOff(LED1);
//	LEDOff(LED2);

	/* Power_ON_�C */
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pin = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Power_OFF */
	GPIO_InitStructure.Pin = GPIO_PIN_1;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* MotorPWM 1..4 */
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_5;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* SPI Pin Configuration */
	/* SPI_CLK, SPI_MOSI and MISO */
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pin = GPIO_PIN_5 | GPIO_PIN_7;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* SPI_CS */
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pin = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	GPIO_InitStructure.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Voltage pin PA0 */
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Tx (PA9) as alternate function push-pull */
	GPIO_InitStructure.Pin = GPIO_PIN_9;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Rx (PA10) as input floating */
	GPIO_InitStructure.Pin = GPIO_PIN_10;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART2 Tx (PA2) as alternate function push-pull */
	GPIO_InitStructure.Pin = GPIO_PIN_2;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART2 Rx (PA3) as input floating */
	GPIO_InitStructure.Pin = GPIO_PIN_3;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

}


void PWR_Buttom_handler()
{
	static uint16_t TurnOff_count = 250;

	if(debounce(GPIOA->IDR & 2))		//tactile switch input
	{
		if(TurnOff_count)
		{
			TurnOff_count--;
			if(!(TurnOff_count % 100))
				uac_printf("TurnOff_count: %i\n", TurnOff_count/100);
			if(!TurnOff_count)
				uac_printf("\nBye-bye!\n");
		}
	}
	else
	{
		if(!TurnOff_count)
		{
			GPIOB->BRR = GPIO_PIN_2;	//turn off DCDC
		}
		else
		{
			TurnOff_count = 250;		//reset TurnOff delay
		}
	}
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

/**
 * @brief  Toggles LED1 with 1Hz 50% duty cycle
 * @param  none
 * @retval none
 */
void HeartBeat(void)
{
	static uint16_t heart_count = 0;
	static uint8_t fade_dir = 1;

	if(fade_dir)
		heart_count++;
	else
		heart_count--;

	if(heart_count == 1000)
	{
		fade_dir = 0;
	}
	if(heart_count == 0)
		fade_dir = 1;

	TIM_SetCompare2(TIM2, heart_count*32);

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