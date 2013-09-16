/*
 * GAS_for_Engines.c
 *
 * Code generation for model "GAS_for_Engines".
 *
 * Model version              : 1.13
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Mon Sep 16 14:23:19 2013
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
  real_T u;

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S3>/weight_azimuth_e1'
   *  Constant: '<S3>/weight_pitch_e1'
   *  Constant: '<S3>/weight_roll_e1'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Inport: '<Root>/ctrl_throttle'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product2'
   */
  u = ((GAS_for_Engines_U.ctrl_pitch * GAS_for_Engines_P.weight_pitch_e1_Value +
        GAS_for_Engines_U.ctrl_roll * GAS_for_Engines_P.weight_roll_e1_Value) +
       GAS_for_Engines_U.ctrl_azimuth *
       GAS_for_Engines_P.weight_azimuth_e1_Value) +
    GAS_for_Engines_U.ctrl_throttle;

  /* Saturate: '<S3>/Saturation_e1' */
  if (u >= GAS_for_Engines_P.Saturation_e1_UpperSat) {
    u = GAS_for_Engines_P.Saturation_e1_UpperSat;
  } else {
    if (u <= GAS_for_Engines_P.Saturation_e1_LowerSat) {
      u = GAS_for_Engines_P.Saturation_e1_LowerSat;
    }
  }

  /* Outport: '<Root>/out_e1' incorporates:
   *  Constant: '<S3>/offset_e1'
   *  Saturate: '<S3>/Saturation_e1'
   *  Sum: '<S3>/add_offset'
   */
  GAS_for_Engines_Y.out_e1 = u + GAS_for_Engines_P.offset_e1_Value;

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/weight_azimuth_e2'
   *  Constant: '<S4>/weight_pitch_e2'
   *  Constant: '<S4>/weight_roll_e2'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Inport: '<Root>/ctrl_throttle'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product2'
   */
  u = ((GAS_for_Engines_U.ctrl_pitch * GAS_for_Engines_P.weight_pitch_e2_Value +
        GAS_for_Engines_U.ctrl_roll * GAS_for_Engines_P.weight_roll_e2_Value) +
       GAS_for_Engines_U.ctrl_azimuth *
       GAS_for_Engines_P.weight_azimuth_e2_Value) +
    GAS_for_Engines_U.ctrl_throttle;

  /* Saturate: '<S4>/Saturation_e2' */
  if (u >= GAS_for_Engines_P.Saturation_e2_UpperSat) {
    u = GAS_for_Engines_P.Saturation_e2_UpperSat;
  } else {
    if (u <= GAS_for_Engines_P.Saturation_e2_LowerSat) {
      u = GAS_for_Engines_P.Saturation_e2_LowerSat;
    }
  }

  /* Outport: '<Root>/out_e2' incorporates:
   *  Constant: '<S4>/offset_e2'
   *  Saturate: '<S4>/Saturation_e2'
   *  Sum: '<S4>/add_offset'
   */
  GAS_for_Engines_Y.out_e2 = u + GAS_for_Engines_P.offset_e2_Value;

  /* Sum: '<S5>/Sum' incorporates:
   *  Constant: '<S5>/weight_azimuth_e3'
   *  Constant: '<S5>/weight_pitch_e3'
   *  Constant: '<S5>/weight_roll_e3'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Inport: '<Root>/ctrl_throttle'
   *  Product: '<S5>/Product'
   *  Product: '<S5>/Product1'
   *  Product: '<S5>/Product2'
   */
  u = ((GAS_for_Engines_U.ctrl_pitch * GAS_for_Engines_P.weight_pitch_e3_Value +
        GAS_for_Engines_U.ctrl_roll * GAS_for_Engines_P.weight_roll_e3_Value) +
       GAS_for_Engines_U.ctrl_azimuth *
       GAS_for_Engines_P.weight_azimuth_e3_Value) +
    GAS_for_Engines_U.ctrl_throttle;

  /* Saturate: '<S5>/Saturation_e3' */
  if (u >= GAS_for_Engines_P.Saturation_e3_UpperSat) {
    u = GAS_for_Engines_P.Saturation_e3_UpperSat;
  } else {
    if (u <= GAS_for_Engines_P.Saturation_e3_LowerSat) {
      u = GAS_for_Engines_P.Saturation_e3_LowerSat;
    }
  }

  /* Outport: '<Root>/out_e3' incorporates:
   *  Constant: '<S5>/offset_e3'
   *  Saturate: '<S5>/Saturation_e3'
   *  Sum: '<S5>/add_offset'
   */
  GAS_for_Engines_Y.out_e3 = u + GAS_for_Engines_P.offset_e3_Value;

  /* Sum: '<S2>/Sum' incorporates:
   *  Constant: '<S2>/weight_azimuth_e4'
   *  Constant: '<S2>/weight_pitch_e4'
   *  Constant: '<S2>/weight_roll_e4'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Inport: '<Root>/ctrl_throttle'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Product: '<S2>/Product2'
   */
  u = ((GAS_for_Engines_U.ctrl_pitch * GAS_for_Engines_P.weight_pitch_e4_Value +
        GAS_for_Engines_U.ctrl_roll * GAS_for_Engines_P.weight_roll_e4_Value) +
       GAS_for_Engines_U.ctrl_azimuth *
       GAS_for_Engines_P.weight_azimuth_e4_Value) +
    GAS_for_Engines_U.ctrl_throttle;

  /* Saturate: '<S2>/Saturation_e4' */
  if (u >= GAS_for_Engines_P.Saturation_e4_UpperSat) {
    u = GAS_for_Engines_P.Saturation_e4_UpperSat;
  } else {
    if (u <= GAS_for_Engines_P.Saturation_e4_LowerSat) {
      u = GAS_for_Engines_P.Saturation_e4_LowerSat;
    }
  }

  /* Outport: '<Root>/out_e4' incorporates:
   *  Constant: '<S2>/offset_e4'
   *  Saturate: '<S2>/Saturation_e4'
   *  Sum: '<S2>/add_offset'
   */
  GAS_for_Engines_Y.out_e4 = u + GAS_for_Engines_P.offset_e4_Value;
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
