
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "GPIO.h"
#include "UART.h"
#include "ADC.h"
#include "TIM.h"
#include "SPI.h"
#include "uAC.h"
#include "uAC_CMD.h"
// #include "kalman.h"
#include "com.h"

#include "Complementary_Filter.h"
// #include "PID_Controller.h"
// #include "GAS_for_Engines.h"

void Error_Handler(void);
void SystemClock_Config(void);

extern UART_HandleTypeDef huart1;

volatile uint8_t tick = 0;
volatile uint8_t enable_telemetry = 1;
volatile uint8_t enable_CompFlt = 0;

mpudata mpu;
mpudata mpu_45;
mpudata mpu_offset;

char telemetrybuf[200];

int32_t angle_est_x = 0;
int32_t angle_est_y = 0;
int32_t angle_est_z = 0;


int main(void)
{
  HAL_Init();

  SystemClock_Config();
  
  NVIC_Configuration();

  GPIO_Configuration();

  ADC1_Configuration();

  UART1_Configuration();

	/* UART2 Configuration for bluetooth AT command mode */
	UART2_Configuration_AT(115200);  

	/* SPI1 Configuration */
	SPI1_Configuration();  

	/* Init the uAC */
	uac_init();

	/* Attach uac commands */
	uAC_CMD_attach();  

	/* TIM2 Configuration */
	LED_Timer_Configuration();

	/* TIM3 Configuration */
	TIM3_Configuration();

	/* keep DC/DC form turning off again (set Power_ON_µC) */
  GPIOB->BSRR = GPIO_PIN_2;

  HAL_Delay(2000);

  /* Change PwrOff Pin config to input for reading tactile switch state */
  PwrOff_Pin_Reconfig();

  /* measure ACC channels while copter is stationary to obtain offsets. */
	GetCalibrationData();

  while (1)
  {
		if (tick == 1)
		{
      tick = 0;

			//read data from MPU-6000
			MPU_read(&mpu); 
      applyCalibration(&mpu, &mpu_offset);  
      if(enable_CompFlt)
      {
        CompFlt_step(&mpu);
      }

      //uac_printf("%i,%i,%i,%i,%i,%i\r\n", mpu.acc_x, mpu.acc_y, mpu.acc_z, mpu.gyro_x, mpu.gyro_y, mpu.gyro_z);
      //uac_printf("Hello");

      if(enable_telemetry)
      {
        snprintf(telemetrybuf, sizeof(telemetrybuf), "%i,%i,%i,%i,%i,%i,%i,%i,%i\r\n", mpu.acc_x, mpu.acc_y, mpu.acc_z, mpu.gyro_x, mpu.gyro_y, mpu.gyro_z, angle_est_x, angle_est_y, angle_est_z);
        HAL_UART_Transmit(&huart1, telemetrybuf, strlen(telemetrybuf), 100);
      }

      //HAL_Delay(100);


      // if( ((i/10)%2) == 0)
      //   uac_printf("Hello %i", i);
      uac_task();


      //If there are outgoing chars, send them
      uac_tx_task();
    }
  }
}


void GetCalibrationData()
{
	uint16_t i;
	int32_t neutralX = 0;
	int32_t neutralY = 0;
	int32_t neutralZ = 0;
	int32_t neutralPi = 0;
	int32_t neutralRo = 0;
	int32_t neutralYa = 0;

	for(i = 0; i < 512; i++)
	{
		//SPI1_read(ACCEL_XOUT_H ,mpu.bytes,14);
		MPU_read(&mpu);
		neutralX += mpu.acc_x;
		neutralY += mpu.acc_y;
		neutralZ += mpu.acc_z;
		neutralPi += mpu.gyro_x;
		neutralRo += mpu.gyro_y;
		neutralYa += mpu.gyro_z;
		HAL_Delay(10);
	}

	mpu_offset.acc_x = neutralX / 512;
	mpu_offset.acc_y = neutralY / 512;
	mpu_offset.acc_z = (neutralZ / 512)  - 16384;
	mpu_offset.gyro_x = neutralPi / 512;
	mpu_offset.gyro_y = neutralRo / 512;
	mpu_offset.gyro_z = neutralYa / 512;
}

void applyCalibration(mpudata *mpu, mpudata *mpu_offset)
{
  mpu->acc_x -= mpu_offset->acc_x;
  mpu->acc_y -= mpu_offset->acc_y;
  mpu->acc_z -= mpu_offset->acc_z;
  mpu->gyro_x -= mpu_offset->gyro_x;
  mpu->gyro_y -= mpu_offset->gyro_y;
  mpu->gyro_z -= mpu_offset->gyro_z;
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

  __HAL_RCC_USART1_CLK_ENABLE();
  __HAL_RCC_USART2_CLK_ENABLE();

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_AFIO_CLK_ENABLE();

  __HAL_RCC_ADC1_CLK_ENABLE();

  __HAL_RCC_TIM2_CLK_ENABLE();
  __HAL_RCC_TIM3_CLK_ENABLE();  

  __HAL_RCC_SPI1_CLK_ENABLE();
}

/**
 * @brief  Configures the nested vectored interrupt controller.
 * @param  None
 * @retval None
 */
void NVIC_Configuration(void)
{
	//NVIC_InitTypeDef NVIC_InitStructure;

	//  /* Enable the TIM3 gloabal interrupt */
	//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//  NVIC_Init(&NVIC_InitStructure);
	//
	//
	// NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init(&NVIC_InitStructure);
  HAL_NVIC_SetPriority(USART1_IRQn, 4, 2);
  HAL_NVIC_EnableIRQ(USART1_IRQn);

	// NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init(&NVIC_InitStructure);
  HAL_NVIC_SetPriority(SPI1_IRQn, 3, 2);
  //HAL_NVIC_EnableIRQ(SPI1_IRQn);  

	/* Enable the USART2 Interrupt */
	// NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init(&NVIC_InitStructure);
  HAL_NVIC_SetPriority(USART2_IRQn, 4, 3);
  HAL_NVIC_EnableIRQ(USART2_IRQn);  


	/* SysTick Priority */
	NVIC_SetPriority(SysTick_IRQn, 2);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
/*
void SysTick_Handler(void)
{
  HAL_IncTick();
}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1) {}
}


void MemManage_Handler(void)
{
  while (1) {}
}

void BusFault_Handler(void)
{
  while (1) {}
}

void UsageFault_Handler(void)
{
  while (1) {}
}

void SVC_Handler(void)
{
}


void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}
*/