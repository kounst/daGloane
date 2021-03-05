/*
 * Complementary_Filter.c
 *
 *  Created on: Mar 02, 2021
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/

#include <stddef.h>
#include <stdio.h>
#include "Complementary_Filter.h"
#include "SPI.h"

extern int32_t angle_est_x;
extern int32_t angle_est_y;
extern int32_t angle_est_z;

void CompFlt_init()
{

}

void CompFlt_step(mpudata *mpu)
{
    float flt_ceff = 0.98;
    angle_est_x = flt_ceff*(angle_est_x + mpu->gyro_x/1024.0) + (1-flt_ceff)*mpu->acc_x;
    angle_est_y = flt_ceff*(angle_est_y + mpu->gyro_y/1024.0) + (1-flt_ceff)*mpu->acc_y;
    angle_est_z = flt_ceff*(angle_est_z + mpu->gyro_z/1024.0) + (1-flt_ceff)*mpu->acc_z;
}