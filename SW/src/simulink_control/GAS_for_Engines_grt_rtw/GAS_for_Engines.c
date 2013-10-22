/*
 * GAS_for_Engines.c
 *
 * Code generation for model "GAS_for_Engines".
 *
 * Model version              : 1.35
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Tue Oct 22 14:01:02 2013
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
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product2'
   */
  u = GAS_for_Engines_U.ctrl_azimuth * 0.1 + GAS_for_Engines_U.ctrl_pitch;

  /* Saturate: '<S2>/-500...+500ms' */
  if (u >= 500.0) {
    u = 500.0;
  } else {
    if (u <= -500.0) {
      u = -500.0;
    }
  }

  /* Sum: '<S2>/add_offset1' incorporates:
   *  Inport: '<Root>/control_msg.throttle'
   *  Saturate: '<S2>/-500...+500ms'
   */
  GAS_for_Engines_Y.out_e1 = u + GAS_for_Engines_U.control_msgthrottle;

  /* Saturate: '<S2>/1000...2000ms' */
  if (GAS_for_Engines_Y.out_e1 >= 2000.0) {
    /* Sum: '<S2>/add_offset1' incorporates:
     *  Outport: '<Root>/out_e1'
     */
    GAS_for_Engines_Y.out_e1 = 2000.0;
  } else {
    if (GAS_for_Engines_Y.out_e1 <= 1000.0) {
      /* Sum: '<S2>/add_offset1' incorporates:
       *  Outport: '<Root>/out_e1'
       */
      GAS_for_Engines_Y.out_e1 = 1000.0;
    }
  }

  /* End of Saturate: '<S2>/1000...2000ms' */

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S3>/weight_azimuth_e2'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_roll'
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product2'
   */
  u = GAS_for_Engines_U.ctrl_azimuth * -0.1 + GAS_for_Engines_U.ctrl_roll;

  /* Saturate: '<S3>/-500...+500ms' */
  if (u >= 500.0) {
    u = 500.0;
  } else {
    if (u <= -500.0) {
      u = -500.0;
    }
  }

  /* Sum: '<S3>/add_offset' incorporates:
   *  Inport: '<Root>/control_msg.throttle'
   *  Saturate: '<S3>/-500...+500ms'
   */
  GAS_for_Engines_Y.out_e2 = u + GAS_for_Engines_U.control_msgthrottle;

  /* Saturate: '<S3>/1000...2000ms' */
  if (GAS_for_Engines_Y.out_e2 >= 2000.0) {
    /* Sum: '<S3>/add_offset' incorporates:
     *  Outport: '<Root>/out_e2'
     */
    GAS_for_Engines_Y.out_e2 = 2000.0;
  } else {
    if (GAS_for_Engines_Y.out_e2 <= 1000.0) {
      /* Sum: '<S3>/add_offset' incorporates:
       *  Outport: '<Root>/out_e2'
       */
      GAS_for_Engines_Y.out_e2 = 1000.0;
    }
  }

  /* End of Saturate: '<S3>/1000...2000ms' */

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/weight_azimuth_e3'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product2'
   */
  u = GAS_for_Engines_U.ctrl_azimuth * 0.1 + -GAS_for_Engines_U.ctrl_pitch;

  /* Saturate: '<S4>/-500...+500ms' */
  if (u >= 500.0) {
    u = 500.0;
  } else {
    if (u <= -500.0) {
      u = -500.0;
    }
  }

  /* Sum: '<S4>/add_offset' incorporates:
   *  Inport: '<Root>/control_msg.throttle'
   *  Saturate: '<S4>/-500...+500ms'
   */
  GAS_for_Engines_Y.out_e3 = u + GAS_for_Engines_U.control_msgthrottle;

  /* Saturate: '<S4>/1000...2000ms' */
  if (GAS_for_Engines_Y.out_e3 >= 2000.0) {
    /* Sum: '<S4>/add_offset' incorporates:
     *  Outport: '<Root>/out_e3'
     */
    GAS_for_Engines_Y.out_e3 = 2000.0;
  } else {
    if (GAS_for_Engines_Y.out_e3 <= 1000.0) {
      /* Sum: '<S4>/add_offset' incorporates:
       *  Outport: '<Root>/out_e3'
       */
      GAS_for_Engines_Y.out_e3 = 1000.0;
    }
  }

  /* End of Saturate: '<S4>/1000...2000ms' */

  /* Sum: '<S5>/Sum' incorporates:
   *  Constant: '<S5>/weight_azimuth_e4'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_roll'
   *  Product: '<S5>/Product1'
   *  Product: '<S5>/Product2'
   */
  u = GAS_for_Engines_U.ctrl_azimuth * -0.1 + -GAS_for_Engines_U.ctrl_roll;

  /* Saturate: '<S5>/-500...+500ms' */
  if (u >= 500.0) {
    u = 500.0;
  } else {
    if (u <= -500.0) {
      u = -500.0;
    }
  }

  /* Sum: '<S5>/add_offset' incorporates:
   *  Inport: '<Root>/control_msg.throttle'
   *  Saturate: '<S5>/-500...+500ms'
   */
  GAS_for_Engines_Y.out_e4 = u + GAS_for_Engines_U.control_msgthrottle;

  /* Saturate: '<S5>/1000...2000ms' */
  if (GAS_for_Engines_Y.out_e4 >= 2000.0) {
    /* Sum: '<S5>/add_offset' incorporates:
     *  Outport: '<Root>/out_e4'
     */
    GAS_for_Engines_Y.out_e4 = 2000.0;
  } else {
    if (GAS_for_Engines_Y.out_e4 <= 1000.0) {
      /* Sum: '<S5>/add_offset' incorporates:
       *  Outport: '<Root>/out_e4'
       */
      GAS_for_Engines_Y.out_e4 = 1000.0;
    }
  }

  /* End of Saturate: '<S5>/1000...2000ms' */
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
