/*
 * uAC_CMD.c
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>

#include "stm32f10x.h"
#include "main.h"
#include "kalman.h"
#include "GPIO.h"
#include "uAC.h"
#include "uAC_CMD.h"
#include "SPI.h"
#include "TIM.h"



extern mpudata mpu;
extern uint16_t lipo_voltage;
extern float acc_pitch, acc_roll;
extern kalman_data pitch_data;
extern kalman_data roll_data;


void uAC_CMD_attach(void)
{
	uac_attach("Hello",Hello_CMD);
	uac_attach("getMPU",get_MPU6000_data);
	uac_attach("getLiPo",get_LiPoVoltage);
	uac_attach("getSwitch", get_Switch);
	uac_attach("PwrOff", PwrOff);
	uac_attach("accangle", ACC_angle);
	uac_attach("getangle", get_angle);
	uac_attach("mpu", MPU_cmd);
	uac_attach("setpwm", setpwm_cmd);
}


void setpwm_cmd(int argc, char *argv[])
{
	if(argc == 2)
	{

		uint16_t puls = strtol(argv[1], NULL, 0);
		PWM_update(*argv[0] - 0x30, puls);


	}
	else
	{
		uac_printf("specify pwm channel (1..4) and duty-cycle (0..1000)");

	}
}



void MPU_cmd(int argc, char *argv[])
{
	uint8_t rw_byte;
	uint8_t address = 0;

	if(argc < 2)
	{
		uac_printf("specify whether you want to read from or write to one of the mpu's registers\n");

	}
	else
	{
		if(strlen(argv[1]) >= 2)
		{
			//convert ASCII representation of address to integer
			address = strtol(argv[1], NULL, 0);

			switch(*argv[0])
			{
				case 'r':

					SPI1_read(address ,&rw_byte,1);
					uac_printf("read address %s = %i: 0x%x\n", argv[1], address, rw_byte);

					break;

				case 'w':

					if(argc > 2)
					{
						//convert ASCII representation of data byte to integer
						rw_byte = strtol(argv[2], NULL, 0);
						SPI1_writebyte(address, rw_byte);
						uac_printf("write address %s = %i: 0x%x\n", argv[1], address, rw_byte);

					}
					else
					{
						uac_printf("write address missing\n");
					}

					break;

				default:
					break;
			}
		}
		else
		{
			uac_printf("not implemented 2\n");
		}
	}
}


void uac_tx_task(void)
{
	//If there are outgoing chars, send them
	if (uac_txavailable() && (USART_GetFlagStatus(USART1, USART_FLAG_TXE)))
	{
		//The ISR disables itself after the last char from the TX buffer is sent
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
}


void get_angle(int argc, char *argv[])
{
	if(!argc)
	{
	uac_printf("Roll Angle: %f\n", roll_data.x1);
	uac_printf("Pitch Angle: %f\n", pitch_data.x1);
	}
	else
	{
		switch (*argv[0]) {
			case 'p':
				uac_printf("Pitch Angle: %f\n", pitch_data.x1);
				break;

			case 'r':
				uac_printf("Roll Angle: %f\n", roll_data.x1);
				break;

			default:
				break;
		}
	}
}



//A console test command.
void Hello_CMD (int argc, char *argv[])
{
	uac_printf("Hello World!\n");
	int i;
	for (i=0;i<argc;i++)
	{
		uac_printf("%i: %s\n",i,argv[i]);
	}

}


void PwrOff(int argc, char *argv[])
{
	uac_printf("\nBye-bye!\n");
	while(uac_txavailable());	//wait for uac string to be sent
	GPIOB->BRR = GPIO_Pin_2;	//turn off DCDC
}

void ACC_angle(int argc, char *argv[])
{
	uac_printf("ACC_Roll_Angle: %2f\n",acc_roll);
	uac_printf("ACC_Pitch_Angle: %2f\n",acc_pitch);
}




void get_MPU6000_data(int argc, char *argv[])
{
	if(!argc)	//if they didn't give us a parameter
	{
				//give them everything!

		uac_printf("All data the MPU-6000 provides: \n");
		uac_printf("acc_x:  %i\ngyro_x: %i\n",mpu.words.acc_x, mpu.words.gyro_x);
		uac_printf("acc_y:  %i\ngyro_y: %i\n",mpu.words.acc_y, mpu.words.gyro_y);
		uac_printf("acc_z:  %i\ngyro_z: %i\n",mpu.words.acc_z, mpu.words.gyro_z);
		uac_printf("Temp: %i\n",mpu.words.temp);
	}
	else
	{
		//which axis do they want to know about?
		switch (*argv[0])
		{
			case 'x':
				uac_printf("acc_x:  %i\ngyro_x: %i\n",mpu.words.acc_x, mpu.words.gyro_x);

				break;
			case 'y':
				uac_printf("acc_y:  %i\ngyro_y: %i\n",mpu.words.acc_y, mpu.words.gyro_y);

				break;
			case 'z':
				uac_printf("acc_z:  %i\ngyro_z: %i\n",mpu.words.acc_z, mpu.words.gyro_z);

				break;
			case 't':
				uac_printf("Temp: %i\n",mpu.words.temp);

				break;
			default:
				break;
		}
	}
}


void get_Switch(int argc, char *argv[])
{
	char *state = "OFF";
	switch (debounce(GPIOA->IDR & 2))
				{
	case 1:
		state = "ON";
		break;
	case 0:
		state = "OFF";
		break;
	default:
		break;
				}
	uac_printf("SwitchState: %s",state);
}


void get_LiPoVoltage(int argc, char *argv[])
{
	uac_printf("LiPo_Voltage: %2fV\n",(float)lipo_voltage/952.558);
}
