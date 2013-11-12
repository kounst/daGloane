/*
 * PID_Controller.c
 *
 * Code generation for model "PID_Controller".
 *
 * Model version              : 1.39
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Tue Nov 12 14:16:57 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Passed (8), Warnings (3), Error (0)
 */
#include "PID_Controller.h"
#include "PID_Controller_private.h"

/* Block states (auto storage) */
DW_PID_Controller_T PID_Controller_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_PID_Controller_T PID_Controller_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_PID_Controller_T PID_Controller_Y;

/* Real-time model */
RT_MODEL_PID_Controller_T PID_Controller_M_;
RT_MODEL_PID_Controller_T *const PID_Controller_M = &PID_Controller_M_;

/* Model step function */
void PID_Controller_step(void)
{
  real_T rtb_Sum;
  real_T rtb_TSamp;
  real_T rtb_Sum_a;
  real_T rtb_TSamp_a;
  real_T rtb_Sum_b;
  real_T rtb_TSamp_b;

  /* Sum: '<S3>/Sum' incorporates:
   *  Inport: '<Root>/control_msg.pitch'
   *  Inport: '<Root>/ist_pitch'
   */
  rtb_Sum = PID_Controller_U.control_msgpitch - PID_Controller_U.Pitch;

  /* SampleTimeMath: '<S6>/TSamp'
   *
   * About '<S6>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = rtb_Sum * 250.0;

  /* Outport: '<Root>/ctrl_pitch' incorporates:
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
   *  Inport: '<Root>/pitch.d'
   *  Inport: '<Root>/pitch.i'
   *  Inport: '<Root>/pitch.p'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product2'
   *  Sum: '<S3>/Sum1'
   *  Sum: '<S6>/Diff'
   *  UnitDelay: '<S6>/UD'
   */
  PID_Controller_Y.ctrl_pitch = (rtb_Sum * PID_Controller_U.pitchp +
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE * PID_Controller_U.pitchi) +
    (rtb_TSamp - PID_Controller_DW.UD_DSTATE) * PID_Controller_U.pitchd;

  /* Sum: '<S4>/Sum' incorporates:
   *  Inport: '<Root>/control_msg.roll'
   *  Inport: '<Root>/ist_roll'
   */
  rtb_Sum_a = PID_Controller_U.control_msgroll - PID_Controller_U.Roll;

  /* SampleTimeMath: '<S7>/TSamp'
   *
   * About '<S7>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp_a = rtb_Sum_a * 250.0;

  /* Outport: '<Root>/ctrl_roll' incorporates:
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
   *  Inport: '<Root>/roll.d'
   *  Inport: '<Root>/roll.i'
   *  Inport: '<Root>/roll.p'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product2'
   *  Sum: '<S4>/Sum1'
   *  Sum: '<S7>/Diff'
   *  UnitDelay: '<S7>/UD'
   */
  PID_Controller_Y.ctrl_roll = (rtb_Sum_a * PID_Controller_U.rollp +
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d * PID_Controller_U.rolli)
    + (rtb_TSamp_a - PID_Controller_DW.UD_DSTATE_g) * PID_Controller_U.rolld;

  /* Sum: '<S2>/Sum' incorporates:
   *  Inport: '<Root>/control_msg.azimuth'
   *  Inport: '<Root>/ist_azimuth'
   */
  rtb_Sum_b = PID_Controller_U.control_msgazimuth - PID_Controller_U.Yaw;

  /* SampleTimeMath: '<S5>/TSamp'
   *
   * About '<S5>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp_b = rtb_Sum_b * 250.0;

  /* Outport: '<Root>/ctrl_azimuth' incorporates:
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator'
   *  Inport: '<Root>/azimuth.d'
   *  Inport: '<Root>/azimuth.i'
   *  Inport: '<Root>/azimuth.p'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Product: '<S2>/Product2'
   *  Sum: '<S2>/Sum1'
   *  Sum: '<S5>/Diff'
   *  UnitDelay: '<S5>/UD'
   */
  PID_Controller_Y.ctrl_azimuth = (rtb_Sum_b * PID_Controller_U.azimuthp +
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g *
    PID_Controller_U.azimuthi) + (rtb_TSamp_b - PID_Controller_DW.UD_DSTATE_a) *
    PID_Controller_U.azimuthd;

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE += 0.004 * rtb_Sum;
  if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE >= 5.0E+17) {
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE = 5.0E+17;
  } else {
    if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE <= -5.0E+17) {
      PID_Controller_DW.DiscreteTimeIntegrator_DSTATE = -5.0E+17;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S6>/UD' */
  PID_Controller_DW.UD_DSTATE = rtb_TSamp;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d += 0.004 * rtb_Sum_a;
  if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d >= 5.0E+17) {
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d = 5.0E+17;
  } else {
    if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d <= -5.0E+17) {
      PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d = -5.0E+17;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S7>/UD' */
  PID_Controller_DW.UD_DSTATE_g = rtb_TSamp_a;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g += 0.004 * rtb_Sum_b;
  if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g >= 5.0E+17) {
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g = 5.0E+17;
  } else {
    if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g <= -5.0E+17) {
      PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g = -5.0E+17;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S5>/UD' */
  PID_Controller_DW.UD_DSTATE_a = rtb_TSamp_b;
}

/* Model initialize function */
void PID_Controller_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(PID_Controller_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&PID_Controller_DW, 0,
                sizeof(DW_PID_Controller_T));

  /* external inputs */
  (void) memset((void *)&PID_Controller_U, 0,
                sizeof(ExtU_PID_Controller_T));

  /* external outputs */
  (void) memset((void *)&PID_Controller_Y, 0,
                sizeof(ExtY_PID_Controller_T));

  /* InitializeConditions for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE = 0.0;

  /* InitializeConditions for UnitDelay: '<S6>/UD' */
  PID_Controller_DW.UD_DSTATE = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d = 0.0;

  /* InitializeConditions for UnitDelay: '<S7>/UD' */
  PID_Controller_DW.UD_DSTATE_g = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g = 0.0;

  /* InitializeConditions for UnitDelay: '<S5>/UD' */
  PID_Controller_DW.UD_DSTATE_a = 0.0;
}

/* Model terminate function */
void PID_Controller_terminate(void)
{
  /* (no terminate code required) */
}
