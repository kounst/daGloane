/*
 * TIM.h
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 */

void TIM3_Configuration(void);
void PWM_update(uint8_t, uint16_t);

void SysTick_Configuration(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void LED_Timer_Configuration(void);
void LED_update(uint8_t channel, uint16_t pulswidth);
void PWM_update(uint8_t channel, uint16_t pulswidth);
