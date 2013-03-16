/*
 * TIM.h
 *
 *  Created on: Nov 3, 2012
 *      Author: konstantin
 */

#ifndef TIM_H_
#define TIM_H_

void TIM4_Configuration();
void SysTick_Configuration(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

#endif /* TIM_H_ */
