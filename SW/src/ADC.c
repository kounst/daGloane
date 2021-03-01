/*
 * ADC.c
 *
 *  Created on: Nov 13, 2010
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "ADC.h"

ADC_HandleTypeDef ADC_Handle;



/* Configuration of ADC1 */
void  ADC1_Configuration (void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_Handle.Instance = ADC1;
  ADC_Handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  ADC_Handle.Init.ScanConvMode = DISABLE;
  ADC_Handle.Init.ContinuousConvMode = ENABLE;
  ADC_Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  ADC_Handle.Init.NbrOfConversion = 1;

  HAL_ADC_Init(&ADC_Handle);

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&ADC_Handle, &sConfig);

  ADC_Enable(&ADC_Handle);

  HAL_ADC_Start(&ADC_Handle);

  // /* ADC1 regular channels configuration */
  // ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);     //voltage measurement
  
  // /* Enable ADC1 reset calibaration register */   
  // ADC_ResetCalibration(ADC1);
  
  // /* Check the end of ADC1 reset calibration register */
  // while(ADC_GetResetCalibrationStatus(ADC1));

  // /* Start ADC1 calibaration */
  // ADC_StartCalibration(ADC1);
  
  // /* Check the end of ADC1 calibration */
  // while(ADC_GetCalibrationStatus(ADC1));

  // ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
