/*
 * Complementary_Filter.c
 *
 * Code generation for model "Complementary_Filter".
 *
 * Model version              : 1.21
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Thu Sep 19 14:24:11 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Passed (9), Warnings (2), Error (0)
 */
#include "Complementary_Filter.h"
#include "Complementary_Filter_private.h"

/* Block states (auto storage) */
DW_Complementary_Filter_T Complementary_Filter_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_Complementary_Filter_T Complementary_Filter_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_Complementary_Filter_T Complementary_Filter_Y;

/* Real-time model */
RT_MODEL_Complementary_Filter_T Complementary_Filter_M_;
RT_MODEL_Complementary_Filter_T *const Complementary_Filter_M =
  &Complementary_Filter_M_;

/* Model step function */
void Complementary_Filter_step(void)
{
  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S3>/gain_acc_to_ist_pitch'
   *  Constant: '<S3>/gain_gyro_to_ist_pitch'
   *  Gain: '<S3>/Zeitschritt'
   *  Inport: '<Root>/acc_pitch'
   *  Inport: '<Root>/mpu_45.gyro_x'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Sum: '<S3>/Add'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  Complementary_Filter_Y.ist_pitch = (0.004 *
    Complementary_Filter_U.mpu_45gyro_x +
    Complementary_Filter_DW.UnitDelay_DSTATE) * 0.98 +
    Complementary_Filter_U.acc_pitch * 0.02;

  /* Sum: '<S4>/Sum1' incorporates:
   *  Constant: '<S4>/gain_acc_to_ist_roll'
   *  Constant: '<S4>/gain_gyro_to_ist_roll'
   *  Gain: '<S4>/Zeitschritt'
   *  Inport: '<Root>/acc_roll'
   *  Inport: '<Root>/mpu_45.gyro_y'
   *  Product: '<S4>/Product2'
   *  Product: '<S4>/Product3'
   *  Sum: '<S4>/Sum2'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  Complementary_Filter_Y.ist_roll = (0.004 * Complementary_Filter_U.mpu_45gyro_y
    + Complementary_Filter_DW.UnitDelay_DSTATE_j) * 0.98 +
    Complementary_Filter_U.acc_roll * 0.02;

  /* Outport: '<Root>/ist_azimuth' incorporates:
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator'
   */
  Complementary_Filter_Y.ist_azimuth =
    Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  Complementary_Filter_DW.UnitDelay_DSTATE = Complementary_Filter_Y.ist_pitch;

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  Complementary_Filter_DW.UnitDelay_DSTATE_j = Complementary_Filter_Y.ist_roll;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' incorporates:
   *  Update for Inport: '<Root>/mpu_45.gyro_z'
   */
  Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE += 0.004 *
    Complementary_Filter_U.mpu_45gyro_z;
  if (Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE >= 5.0E+17) {
    Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE = 5.0E+17;
  } else {
    if (Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE <= -5.0E+17) {
      Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE = -5.0E+17;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
}

/* Model initialize function */
void Complementary_Filter_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Complementary_Filter_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Complementary_Filter_DW, 0,
                sizeof(DW_Complementary_Filter_T));

  /* external inputs */
  (void) memset((void *)&Complementary_Filter_U, 0,
                sizeof(ExtU_Complementary_Filter_T));

  /* external outputs */
  (void) memset((void *)&Complementary_Filter_Y, 0,
                sizeof(ExtY_Complementary_Filter_T));

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
  Complementary_Filter_DW.UnitDelay_DSTATE = 0.0;

  /* InitializeConditions for UnitDelay: '<S4>/Unit Delay' */
  Complementary_Filter_DW.UnitDelay_DSTATE_j = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE = 0.0;
}

/* Model terminate function */
void Complementary_Filter_terminate(void)
{
  /* (no terminate code required) */
}
