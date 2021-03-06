/*
 * TIM.c
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 */



/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "TIM.h"



static __IO uint32_t TimingDelay;


void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;


	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 24000;
	TIM_TimeBaseStructure.TIM_Prescaler = 8;//(uint16_t) (SystemCoreClock / 24000000) - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 8000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 8000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 8000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC3Init(TIM3, &TIM_OCInitStructure);

	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 8000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC4Init(TIM3, &TIM_OCInitStructure);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}



void LED_Timer_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;


	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 32000;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//(uint16_t) (SystemCoreClock / 24000000) - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);

	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC2Init(TIM2, &TIM_OCInitStructure);

	TIM_Cmd(TIM2, ENABLE);
}



void PWM_update(uint8_t channel, uint16_t pulswidth)
{
	pulswidth *= 8;
	switch(channel)
	{
	case 0:
		TIM_SetCompare1(TIM3, pulswidth);
		TIM_SetCompare2(TIM3, pulswidth);
		TIM_SetCompare3(TIM3, pulswidth);
		TIM_SetCompare4(TIM3, pulswidth);
		break;
	case 1:
		TIM_SetCompare1(TIM3, pulswidth);
		break;
	case 2:
		TIM_SetCompare2(TIM3, pulswidth);
		break;
	case 3:
		TIM_SetCompare3(TIM3, pulswidth);
		break;
	case 4:
		TIM_SetCompare4(TIM3, pulswidth);
		break;
	default:
		break;
	}
}


void LED_update(uint8_t channel, uint16_t pulswidth)
{
	pulswidth *= 32;
	switch(channel)
	{
	case 0:
		TIM_SetCompare1(TIM2, pulswidth);
		TIM_SetCompare2(TIM2, pulswidth);
		break;
	case 1:
		TIM_SetCompare1(TIM2, pulswidth);
		break;
	case 2:
		TIM_SetCompare2(TIM2, pulswidth);
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
