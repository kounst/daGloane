/*
 * TIM.c
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 */



/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "TIM.h"

TIM_HandleTypeDef htim2;

static __IO uint32_t TimingDelay;


void TIM3_Configuration(void)
{
	TIM_HandleTypeDef htim3 = {0};	
	TIM_OC_InitTypeDef sConfigOC = {0};	

	// TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// TIM_OCInitTypeDef  TIM_OCInitStructure;


	/* Time base configuration */
	htim3.Instance = TIM3;
	htim3.Init.Period = 20000;
	htim3.Init.Prescaler = 11;
	htim3.Init.ClockDivision = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  	// sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  	// HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

	HAL_TIM_Base_Init(&htim3);
	HAL_TIM_OC_Init(&htim3);
	//TIM_TimeBaseStructure.TIM_Period = 24000;
	// TIM_TimeBaseStructure.TIM_Prescaler = 8;//(uint16_t) (SystemCoreClock / 24000000) - 1;
	// TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	// TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	//TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.OCNIdleState = TIM_OCIDLESTATE_SET;
	sConfigOC.Pulse = 6000;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
	HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3);
	HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4);

	// TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// TIM_OCInitStructure.TIM_Pulse = 8000;
	// TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	// TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	// TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	// TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	// TIM_OC4Init(TIM3, &TIM_OCInitStructure);

	/* TIM3 enable counter */
	//TIM_Cmd(TIM3, ENABLE);
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_2);	
	HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_3);	
	HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_4);	
}



void LED_Timer_Configuration(void)
{
	
  	TIM_OC_InitTypeDef sConfigOC = {0};	
	// TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// TIM_OCInitTypeDef  TIM_OCInitStructure;


	// /* Time base configuration */
	htim2.Instance = TIM2;
	htim2.Init.Period = 10000;	// 10ms
	htim2.Init.Prescaler = 71;	// prescaler of 72 -> 1MHz
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&htim2);

	// TIM_TimeBaseStructure.TIM_Period = 32000;
	// TIM_TimeBaseStructure.TIM_Prescaler = 0;//(uint16_t) (SystemCoreClock / 24000000) - 1;
	// TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	// TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	// TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  	// sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  	// HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

	HAL_TIM_OC_Init(&htim2);

  	// sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  	// sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  	// HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

	// /* PWM1 Mode configuration: Channel1 */
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
	
	// TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// TIM_OCInitStructure.TIM_Pulse = 0;
	// TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	// TIM_OC1Init(TIM2, &TIM_OCInitStructure);

	// /* PWM1 Mode configuration: Channel2 */
	// TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// TIM_OCInitStructure.TIM_Pulse = 0;
	// TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	// TIM_OC2Init(TIM2, &TIM_OCInitStructure);

	// TIM_Cmd(TIM2, ENABLE);
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_2);
}

void enable_spi_timer()
{
	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
}

void disable_spi_timer()
{
	__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_UPDATE);
}



void PWM_update(uint8_t channel, uint16_t pulswidth)
{
	//pulswidth *= 8;
	switch(channel)
	{
	case 0:
		TIM3->CCR1 = pulswidth;
		TIM3->CCR2 = pulswidth;
		TIM3->CCR3 = pulswidth;
		TIM3->CCR4 = pulswidth;
		// TIM_SetCompare1(TIM3, pulswidth);
		// TIM_SetCompare2(TIM3, pulswidth);
		// TIM_SetCompare3(TIM3, pulswidth);
		// TIM_SetCompare4(TIM3, pulswidth);
		break;
	case 1:
		TIM3->CCR1 = pulswidth;
		//TIM_SetCompare1(TIM3, pulswidth);
		break;
	case 2:
		TIM3->CCR2 = pulswidth;
		//TIM_SetCompare2(TIM3, pulswidth);
		break;
	case 3:
		TIM3->CCR3 = pulswidth;
		//TIM_SetCompare3(TIM3, pulswidth);
		break;
	case 4:
		TIM3->CCR4 = pulswidth;
		//TIM_SetCompare4(TIM3, pulswidth);
		break;
	default:
		break;
	}
}


void LED_update(uint8_t channel, uint16_t pulswidth)
{
	switch(channel)
	{
	case 0:
		TIM2->CCR1 = pulswidth;
		TIM2->CCR2 = pulswidth;
		break;
	case 1:
		TIM2->CCR1 = pulswidth;
		break;
	case 2:
		TIM2->CCR2 = pulswidth;
		break;
	default:
		break;
	}
}




/**
 * @brief  Configures the SysTick.
 * @param  None
 * @retval None
 */
void SysTick_Configuration(void)
{

	/* Setup SysTick Timer for 4 msec interrupts  */
	if (SysTick_Config(SystemCoreClock / 250))
	{
		/* Capture error */
		while (1);
	}


}

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in milliseconds.
 * @retval None
 */
void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime;

	while(TimingDelay != 0);
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}
