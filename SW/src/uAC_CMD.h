/*
 * uAC_CMD.h
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 */

#ifndef UAC_CMD_H_
#define UAC_CMD_H_

void uAC_CMD_attach(void);
void uac_tx_task(void);
void Hello_CMD (int argc, char *argv[]);
void get_MPU6000_data(int argc, char *argv[]);
void get_LiPoVoltage(int argc, char *argv[]);
void get_Switch(int argc, char *argv[]);
void PwrOff(int argc, char *argv[]);
void ACC_angle(int argc, char *argv[]);
void get_angle(int argc, char *argv[]);
void MPU_cmd(int argc, char *argv[]);
void setpwm_cmd(int argc, char *argv[]);
void setled_cmd(int argc, char *argv[]);
void set_kalman(int argc, char *argv[]);
void bluetooth_send(int argc, char *argv[]);
void bluetooth_config(int argc, char *argv[]);


#endif /* UAC_CMD_H_ */
