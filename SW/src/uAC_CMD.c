/*
 * uAC_CMD.c
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>

#include "stm32f1xx_hal.h"
#include "main.h"
//#include "kalman.h"
#include "GPIO.h"
#include "uAC.h"
#include "uAC_CMD.h"
#include "SPI.h"
#include "TIM.h"
#include "com.h"
#include "UART.h"

extern UART_HandleTypeDef huart1;

extern mpudata mpu;
extern volatile uint16_t lipo_voltage;
// extern float acc_pitch, acc_roll;
// extern kalman_data pitch_data;
// extern kalman_data roll_data;
extern msg1 control_msg;
extern msg2 config_msg;

extern volatile uint8_t enable_telemetry;
extern volatile uint8_t enable_CompFlt;

extern uint8_t receive_buffer[256];


void uAC_CMD_attach(void)
{
	uac_attach("Hello",Hello_CMD);
	uac_attach("getMPU",get_MPU6000_data);
	uac_attach("getLiPo",get_LiPoVoltage);
	uac_attach("getSwitch", get_Switch);
	uac_attach("PwrOff", PwrOff);
	//uac_attach("accangle", ACC_angle);
	//uac_attach("getangle", get_angle);
	//uac_attach("mpu", MPU_cmd);
	uac_attach("setpwm", setpwm_cmd);
	uac_attach("setled", setled_cmd);
	//uac_attach("kalman", set_kalman);
	uac_attach("bt", bluetooth_send);
	//uac_attach("btconf", bluetooth_config);
	//uac_attach("btmsg", bluetooth_msg);
	uac_attach("getpwm", getpwm_cmd);
	uac_attach("telemetry", startTelemetry_cmd);
	uac_attach("stop", stopTelemetry_cmd);
	uac_attach("compflt", CompFlt_cmd);
	uac_attach("getConfData", getConfData_cmd);
	uac_attach("readCOMbuf", readCOMbuf_cmd);
	uac_attach("mpuread", mpuread_cmd);
}

void mpuread_cmd(int argc, char *argv[])
{
	
	if(argc > 0)
	{
		if(*argv[0] == '1')
		{
			MPU_read_IT(&mpu);
		}
		else
		{
			MPU_read(&mpu);
		}
	}	
}

void readCOMbuf_cmd(int argc, char *argv[])
{
	uac_printf("COM buffer: %x %x %x %x %x %x %x %x %x %x %x %x %x %x", receive_buffer[0],  receive_buffer[1], receive_buffer[2], receive_buffer[3], receive_buffer[4], receive_buffer[5], receive_buffer[6], receive_buffer[7], receive_buffer[8], receive_buffer[9], receive_buffer[10], receive_buffer[11], receive_buffer[12], receive_buffer[13], receive_buffer[14]);
}


void getConfData_cmd(int argc, char *argv[])
{
	uac_printf("Config msg: %x %x %x %x %x %x %x %x %x", config_msg.bytes[0], config_msg.bytes[1], config_msg.bytes[2], config_msg.bytes[3], config_msg.bytes[4], config_msg.bytes[5], config_msg.bytes[6], config_msg.bytes[7], config_msg.bytes[8]);
	
}

void startTelemetry_cmd(int argc, char *argv[])
{
	enable_telemetry = 1;
}


void stopTelemetry_cmd(int argc, char *argv[])
{
	enable_telemetry = 0;
}

void CompFlt_cmd(int argc, char *argv[])
{
	if(argc > 0)
	{
		if(*argv[0] == '1')
		{
			enable_CompFlt = 1;
		}
		else
		{
			enable_CompFlt = 0;
		}
	}
}


// void bluetooth_msg(int argc, char *argv[])
// {
// 	uint8_t bytes_to_send[20];
// 	uint8_t i;
// 	for(i = 0; i < argc; i++)
// 	{
// 		bytes_to_send[i] = strtol(argv[i], NULL, 0);
// 	}
// 	send_data(1, bytes_to_send, argc);
// }

// void bluetooth_config(int argc, char *argv[])
// {
// 	if(argc >= 1)
// 	{
// 		UART2_Configuration_AT(strtol(argv[0], NULL, 0));
// 	}
// }


void bluetooth_send(int argc, char *argv[])
{
	char *buffer;
	uint8_t strlength;

	if(argc >= 0)
	{
		strlength = strlen(argv[0]);
		buffer = alloca(strlength + 2);
		strcpy(buffer, argv[0]);
		buffer[strlength] = 0x0D;
		buffer[strlength + 1] = 0x0A;

		send_to_buffer(buffer, strlength + 2, 0);
	}
}


// void set_kalman(int argc, char *argv[])
// {
// 	uac_printf("R = ( %f , %f )\n",pitch_data.r1, pitch_data.r2);
// 	uac_printf("Q = ( %f , %f , %f )\n\n",pitch_data.q1, pitch_data.q2, pitch_data.q3);
// 	if(argc >= 2)
// 	{
// 		switch (*argv[0])
// 		{
// 		case 'r':

// 			pitch_data.r1 = strtol(argv[1], NULL, 0);
// 			pitch_data.r2 = strtol(argv[2], NULL, 0);

// 			roll_data.r1 = strtol(argv[1], NULL, 0);
// 			roll_data.r2 = strtol(argv[2], NULL, 0);

// 			uac_printf("R = ( %f , %f )\n",pitch_data.r1, pitch_data.r2);
// 			break;

// 		case 'q':

// 			pitch_data.q1 = strtol(argv[1], NULL, 0);
// 			pitch_data.q2 = strtol(argv[2], NULL, 0);

// 			roll_data.q1 = strtol(argv[1], NULL, 0);
// 			roll_data.q2 =  strtol(argv[2], NULL, 0);

// 			if(argc >= 3)
// 			{
// 				roll_data.q3 =  strtol(argv[3], NULL, 0);
// 				pitch_data.q3 = strtol(argv[3], NULL, 0);
// 			}
// 			uac_printf("Q = ( %f , %f , %f )\n",pitch_data.q1, pitch_data.q2, pitch_data.q3);
// 			break;
// 		}

// 	}
// }



void setpwm_cmd(int argc, char *argv[])
{
	if(argc == 2)
	{

		uint16_t puls = strtol(argv[1], NULL, 0);
		PWM_update(*argv[0] - 0x30, puls);


	}
	else
	{
		uac_printf("specify pwm channel (1..4) and duty-cycle (0..3000ms)");

	}
}

void getpwm_cmd(int argc, char *argv[])
{
	uac_printf("Throttle %i", control_msg.throttle);
}


void setled_cmd(int argc, char *argv[])
{
	if(argc == 2)
	{

		uint16_t puls = strtol(argv[1], NULL, 0);
		LED_update(*argv[0] - 0x30, puls);


	}
	else
	{
		uac_printf("specify pwm channel (1..2) and duty-cycle (0..1000)");

	}
}



// void MPU_cmd(int argc, char *argv[])
// {
// 	uint8_t rw_byte;
// 	uint8_t address = 0;

// 	if(argc < 2)
// 	{
// 		uac_printf("specify whether you want to read from or write to one of the mpu's registers\n");

// 	}
// 	else
// 	{
// 		if(strlen(argv[1]) >= 2)
// 		{
// 			//convert ASCII representation of address to integer
// 			address = strtol(argv[1], NULL, 0);

// 			switch(*argv[0])
// 			{
// 				case 'r':

// 					SPI1_read(address ,&rw_byte,1);
// 					uac_printf("read address %s = %i: 0x%x\n", argv[1], address, rw_byte);

// 					break;

// 				case 'w':

// 					if(argc > 2)
// 					{
// 						//convert ASCII representation of data byte to integer
// 						rw_byte = strtol(argv[2], NULL, 0);
// 						SPI1_writebyte(address, rw_byte);
// 						uac_printf("write address %s = %i: 0x%x\n", argv[1], address, rw_byte);

// 					}
// 					else
// 					{
// 						uac_printf("write address missing\n");
// 					}

// 					break;

// 				default:
// 					break;
// 			}
// 		}
// 		else
// 		{
// 			uac_printf("not implemented 2\n");
// 		}
// 	}
// }


void uac_tx_task(void)
{
	//If there are outgoing chars, send them
	if(uac_txavailable() && __HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE))
	//if (uac_txavailable() && (USART_GetFlagStatus(USART1, USART_FLAG_TXE)))
	{
		//The ISR disables itself after the last char from the TX buffer is sent
		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
	}
}


// void get_angle(int argc, char *argv[])
// {
// 	if(!argc)
// 	{
// 	uac_printf("Roll Angle: %f\n", roll_data.x1);
// 	uac_printf("Pitch Angle: %f\n", pitch_data.x1);
// 	uac_printf("Roll Velocity: %f\n", roll_data.x2);
// 	uac_printf("Pitch Velocity: %f\n", pitch_data.x2);
// 	uac_printf("Roll Bias: %f\n", roll_data.x3);
// 	uac_printf("Pitch Bias: %f\n", pitch_data.x3);
// 	}
// 	else
// 	{
// 		switch (*argv[0]) {
// 			case 'p':
// 				uac_printf("Pitch Angle: %f\n", pitch_data.x1);
// 				break;

// 			case 'r':
// 				uac_printf("Roll Angle: %f\n", roll_data.x1);
// 				break;

// 			default:
// 				break;
// 		}
// 	}
// }



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
	HAL_Delay(500);
	GPIOB->BRR = GPIO_PIN_2;	//turn off DCDC
}

// void ACC_angle(int argc, char *argv[])
// {
// 	uac_printf("ACC_Roll_Angle: %2f\n",acc_roll);
// 	uac_printf("ACC_Pitch_Angle: %2f\n",acc_pitch);
// }




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
