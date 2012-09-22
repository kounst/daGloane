/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO/STM32
**                STMicroelectronics STM32F10x Standard Peripherals Library
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Atollic TrueSTUDIO(R) toolchain.
**
**
*****************************************************************************
*/

/* Includes */
#include <stddef.h>
#include "stm32f10x.h"
#include "GPIO.h"
#include "UART.h"
#include "ADC.h"
#include "TIM.h"




/* Private typedef */
/* Private define  */


/* Private macro */
/* Private variables */
static __IO uint32_t TimingDelay;

/* Global variables */
volatile char uart_buffer[500];
extern uint16_t lipo_voltage;

/* Private function prototypes */
void RCC_Configuration(void);
void NVIC_Configuration(void);
void SysTick_Configuration(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	uint16_t lipo_voltage_v, lipo_voltage_mv;

    /* System Clocks Configuration */
    RCC_Configuration();

    /* NVIC Configuration */
    NVIC_Configuration();

    /* Systick Configuration */
    SysTick_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* ADC Configuration */
    ADC1_Configuration();

    /* UART1 Configuration */
    UART1_Configuration();

    /* TIM3 Configuration */
    TIM3_Configuration();

    /* keep DCDC form turning off again (set Power_ON_µC)*/
    GPIOB->BSRR = GPIO_Pin_2;

    //LEDOn(LED2);

    /* convert lipo voltage to V and mV as tiny printf does not support floating point numbers */
    lipo_voltage_v = (int)((float)lipo_voltage/952 + 0.5);
    lipo_voltage_mv = (int)((((float)lipo_voltage/952) - (float)lipo_voltage_v)*1000);

    sprintf(uart_buffer,"Hello, my name is daGloane! Servus! \r\n"
    					"LiPo_Voltage = %d.%dV\r\n\0", lipo_voltage_v, lipo_voltage_mv);
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

  /* Infinite loop */
  while (1)
  {
	Delay(10);

	//GPIOB->ODR ^= GPIO_Pin_0;

  }
}



void RCC_Configuration(void)
{
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();

   /* PCLK1 = HCLK/2 */
  RCC_PCLK1Config(RCC_HCLK_Div2);

  //RCC_ADCCLKConfig(RCC_PCLK2_Div4);

  /* GPIOA, GPIOB and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |  RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  /* USART1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* TIM3 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

//  /* Enable the TIM3 gloabal interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//
//
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
//
//  /* Enable the USART2 Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);


  /* SysTick Priority */
  NVIC_SetPriority(SysTick_IRQn, 2);
}

/**
  * @brief  Configures the SysTick.
  * @param  None
  * @retval None
  */
void SysTick_Configuration(void)
{

  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config(SystemCoreClock / 1000))
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



/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}

