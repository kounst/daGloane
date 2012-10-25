/*
 * GPIO.c
 *
 *  Created on: Nov 13, 2010
 *      Author: konstantin
 */


/* Private define ------------------------------------------------------------*/
#define LED1_PIN                GPIO_Pin_3
#define LED2_PIN		        GPIO_Pin_15
#define LED1_GPIO_PORT			GPIOB
#define LED2_GPIO_PORT			GPIOA



/* Private typedef -----------------------------------------------------------*/
typedef enum 
{
  LED1 = 0,
  LED2 = 1,
} Led_TypeDef;



void GPIO_Configuration(void);
uint8_t debounce(uint16_t IOstate);
void PWR_Buttom_handler(void);
void LEDToggle(Led_TypeDef Led);
void LEDOn(Led_TypeDef Led);
void LEDOff(Led_TypeDef Led);
void HeartBeat(void);

