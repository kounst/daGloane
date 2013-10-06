/*
 * GAS_for_Engines.c
 *
 * Code generation for model "GAS_for_Engines".
 *
 * Model version              : 1.21
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Thu Sep 19 14:25:48 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Passed (9), Warnings (2), Error (0)
 */
#include "GAS_for_Engines.h"
#include "GAS_for_Engines_private.h"

/* External inputs (root inport signals with auto storage) */
ExtU_GAS_for_Engines_T GAS_for_Engines_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_GAS_for_Engines_T GAS_for_Engines_Y;

/* Real-time model */
RT_MODEL_GAS_for_Engines_T GAS_for_Engines_M_;
RT_MODEL_GAS_for_Engines_T *const GAS_for_Engines_M = &GAS_for_Engines_M_;

/* Model step function */
void GAS_for_Engines_step(void)
{
  real_T u;

  /* Sum: '<S2>/Sum' incorporates:
   *  Constant: '<S2>/weight_azimuth_e1'
   *  Inport: '<Root>/control_msg.throttle'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product2'
   */
  u = (GAS_for_Engines_U.ctrl_azimuth * 0.1 + GAS_for_Engines_U.ctrl_pitch) +
    GAS_for_Engines_U.control_msgthrottle;

  /* Saturate: '<S2>/Saturation_e1' */
  if (u >= 1000.0) {
    u = 1000.0;
  } else {
    if (u <= 1.0) {
      u = 1.0;
    }
  }

  /* Outport: '<Root>/out_e1' incorporates:
   *  Constant: '<S2>/offset_e1'
   *  Saturate: '<S2>/Saturation_e1'
   *  Sum: '<S2>/add_offset'
   */
  GAS_for_Engines_Y.out_e1 = u + 1000.0;

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S3>/weight_azimuth_e2'
   *  Inport: '<Root>/control_msg.throttle'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_roll'
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product2'
   */
  u = (GAS_for_Engines_U.ctrl_azimuth * -0.1 + GAS_for_Engines_U.ctrl_roll) +
    GAS_for_Engines_U.control_msgthrottle;

  /* Saturate: '<S3>/Saturation_e2' */
  if (u >= 1000.0) {
    u = 1000.0;
  } else {
    if (u <= 1.0) {
      u = 1.0;
    }
  }

  /* Outport: '<Root>/out_e2' incorporates:
   *  Constant: '<S3>/offset_e2'
   *  Saturate: '<S3>/Saturation_e2'
   *  Sum: '<S3>/add_offset'
   */
  GAS_for_Engines_Y.out_e2 = u + 1000.0;

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/weight_azimuth_e3'
   *  Inport: '<Root>/control_msg.throttle'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product2'
   */
  u = (GAS_for_Engines_U.ctrl_azimuth * 0.1 + -GAS_for_Engines_U.ctrl_pitch) +
    GAS_for_Engines_U.control_msgthrottle;

  /* Saturate: '<S4>/Saturation_e3' */
  if (u >= 1000.0) {
    u = 1000.0;
  } else {
    if (u <= 1.0) {
      u = 1.0;
    }
  }

  /* Outport: '<Root>/out_e3' incorporates:
   *  Constant: '<S4>/offset_e3'
   *  Saturate: '<S4>/Saturation_e3'
   *  Sum: '<S4>/add_offset'
   */
  GAS_for_Engines_Y.out_e3 = u + 1000.0;

  /* Sum: '<S5>/Sum' incorporates:
   *  Constant: '<S5>/weight_azimuth_e4'
   *  Inport: '<Root>/control_msg.throttle'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_roll'
   *  Product: '<S5>/Product1'
   *  Product: '<S5>/Product2'
   */
  u = (GAS_for_Engines_U.ctrl_azimuth * -0.1 + -GAS_for_Engines_U.ctrl_roll) +
    GAS_for_Engines_U.control_msgthrottle;

  /* Saturate: '<S5>/Saturation_e4' */
  if (u >= 1000.0) {
    u = 1000.0;
  } else {
    if (u <= 1.0) {
      u = 1.0;
    }
  }

  /* Outport: '<Root>/out_e4' incorporates:
   *  Constant: '<S5>/offset_e4'
   *  Saturate: '<S5>/Saturation_e4'
   *  Sum: '<S5>/add_offset'
   */
  GAS_for_Engines_Y.out_e4 = u + 1000.0;
}

/* Model initialize function */
void GAS_for_Engines_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(GAS_for_Engines_M, (NULL));

  /* external inputs */
  (void) memset((void *)&GAS_for_Engines_U, 0,
                sizeof(ExtU_GAS_for_Engines_T));

  /* external outputs */
  (void) memset((void *)&GAS_for_Engines_Y, 0,
                sizeof(ExtY_GAS_for_Engines_T));
}

/* Model terminate function */
void GAS_for_Engines_terminate(void)
{
  /* (no terminate code required) */
}
