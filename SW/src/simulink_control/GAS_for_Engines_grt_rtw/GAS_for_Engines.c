/*
 * GAS_for_Engines.c
 *
 * Code generation for model "GAS_for_Engines".
 *
 * Model version              : 1.12
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Mon Sep 16 12:24:03 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
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
  /* Outport: '<Root>/out_e1' incorporates:
   *  Constant: '<S2>/weight_azimuth_e1'
   *  Constant: '<S2>/weight_pitch_e1'
   *  Constant: '<S2>/weight_roll_e1'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Inport: '<Root>/ctrl_throttle'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Product: '<S2>/Product2'
   *  Sum: '<S2>/Sum'
   */
  GAS_for_Engines_Y.out_e1 = ((GAS_for_Engines_U.ctrl_pitch *
    GAS_for_Engines_P.weight_pitch_e1_Value + GAS_for_Engines_U.ctrl_roll *
    GAS_for_Engines_P.weight_roll_e1_Value) + GAS_for_Engines_U.ctrl_azimuth *
    GAS_for_Engines_P.weight_azimuth_e1_Value) + GAS_for_Engines_U.ctrl_throttle;

  /* Outport: '<Root>/out_e2' incorporates:
   *  Constant: '<S3>/weight_azimuth_e2'
   *  Constant: '<S3>/weight_pitch_e2'
   *  Constant: '<S3>/weight_roll_e2'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Inport: '<Root>/ctrl_throttle'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product2'
   *  Sum: '<S3>/Sum'
   */
  GAS_for_Engines_Y.out_e2 = ((GAS_for_Engines_U.ctrl_pitch *
    GAS_for_Engines_P.weight_pitch_e2_Value + GAS_for_Engines_U.ctrl_roll *
    GAS_for_Engines_P.weight_roll_e2_Value) + GAS_for_Engines_U.ctrl_azimuth *
    GAS_for_Engines_P.weight_azimuth_e2_Value) + GAS_for_Engines_U.ctrl_throttle;

  /* Outport: '<Root>/out_e3' incorporates:
   *  Constant: '<S4>/weight_azimuth_e3'
   *  Constant: '<S4>/weight_pitch_e3'
   *  Constant: '<S4>/weight_roll_e3'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Inport: '<Root>/ctrl_throttle'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product2'
   *  Sum: '<S4>/Sum'
   */
  GAS_for_Engines_Y.out_e3 = ((GAS_for_Engines_U.ctrl_pitch *
    GAS_for_Engines_P.weight_pitch_e3_Value + GAS_for_Engines_U.ctrl_roll *
    GAS_for_Engines_P.weight_roll_e3_Value) + GAS_for_Engines_U.ctrl_azimuth *
    GAS_for_Engines_P.weight_azimuth_e3_Value) + GAS_for_Engines_U.ctrl_throttle;

  /* Outport: '<Root>/out_e4' incorporates:
   *  Constant: '<S5>/weight_azimuth_e4'
   *  Constant: '<S5>/weight_pitch_e4'
   *  Constant: '<S5>/weight_roll_e4'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Inport: '<Root>/ctrl_throttle'
   *  Product: '<S5>/Product'
   *  Product: '<S5>/Product1'
   *  Product: '<S5>/Product2'
   *  Sum: '<S5>/Sum'
   */
  GAS_for_Engines_Y.out_e4 = ((GAS_for_Engines_U.ctrl_pitch *
    GAS_for_Engines_P.weight_pitch_e4_Value + GAS_for_Engines_U.ctrl_roll *
    GAS_for_Engines_P.weight_roll_e4_Value) + GAS_for_Engines_U.ctrl_azimuth *
    GAS_for_Engines_P.weight_azimuth_e4_Value) + GAS_for_Engines_U.ctrl_throttle;
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
