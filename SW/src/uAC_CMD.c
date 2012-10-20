/*
 * uAC_CMD.c
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"
#include "kalman.h"
#include "GPIO.h"
#include "uAC.h"
#include "uAC_CMD.h"


extern mpudata mpu;
extern uint16_t lipo_voltage;
extern float acc_pitch, acc_roll;
extern kalman_data pitch_data;
extern kalman_data roll_data;


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
		uac_printf("acc_x:  %i\ngyro_x: %i\n",mpu.acc_x, mpu.gyro_x);
		uac_printf("acc_y:  %i\ngyro_y: %i\n",mpu.acc_y, mpu.gyro_y);
		uac_printf("acc_z:  %i\ngyro_z: %i\n",mpu.acc_z, mpu.gyro_z);
		uac_printf("Temp: %i\n",mpu.temp);
	}
	else
	{
		//which axis do they want to know about?
		switch (*argv[0])
		{
			case 'x':
				uac_printf("acc_x:  %i\ngyro_x: %i\n",mpu.acc_x, mpu.gyro_x);

				break;
			case 'y':
				uac_printf("acc_y:  %i\ngyro_y: %i\n",mpu.acc_y, mpu.gyro_y);

				break;
			case 'z':
				uac_printf("acc_z:  %i\ngyro_z: %i\n",mpu.acc_z, mpu.gyro_z);

				break;
			case 't':
				uac_printf("Temp: %i\n",mpu.temp);

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