/*
 * GPIO.c
 *
 *  Created on: Nov 13, 2010
 *      Author: konstantin
 */


/* Private define ------------------------------------------------------------*/
#define LED1_PIN                GPIO_Pin_8
#define LED2_PIN		        GPIO_Pin_9
#define LED1_GPIO_PORT			GPIOC
#define LED2_GPIO_PORT			GPIOC



/* Private typedef -----------------------------------------------------------*/
typedef enum 
{
  LED1 = 0,
  LED2 = 1,
} Led_TypeDef;



void GPIO_Configuration(void);
uint8_t debounce(uint16_t IOstate);
void LEDToggle(Led_TypeDef Led);
void LEDOn(Led_TypeDef Led);
void LEDOff(Led_TypeDef Led);


