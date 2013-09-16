/*
 * PID_Controller.c
 *
 * Code generation for model "PID_Controller".
 *
 * Model version              : 1.13
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Mon Sep 16 14:23:05 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
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
  real_T rtb_TSamp_f;
  real_T rtb_Sum_b;
  real_T rtb_TSamp_b;

  /* Sum: '<S3>/Sum' incorporates:
   *  Inport: '<Root>/control_msg.pitch'
   *  Inport: '<Root>/ist_pitch'
   */
  rtb_Sum = PID_Controller_U.control_msgpitch - PID_Controller_U.ist_pitch;

  /* SampleTimeMath: '<S6>/TSamp'
   *
   * About '<S6>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = rtb_Sum * PID_Controller_P.TSamp_WtEt;

  /* Outport: '<Root>/ctrl_pitch' incorporates:
   *  Constant: '<S3>/D'
   *  Constant: '<S3>/I'
   *  Constant: '<S3>/P'
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product2'
   *  Sum: '<S3>/Sum1'
   *  Sum: '<S6>/Diff'
   *  UnitDelay: '<S6>/UD'
   */
  PID_Controller_Y.ctrl_pitch = (rtb_Sum * PID_Controller_P.P_Value +
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE * PID_Controller_P.I_Value)
    + (rtb_TSamp - PID_Controller_DW.UD_DSTATE) * PID_Controller_P.D_Value;

  /* Sum: '<S4>/Sum' incorporates:
   *  Inport: '<Root>/control_msg.roll'
   *  Inport: '<Root>/ist_roll'
   */
  rtb_Sum_a = PID_Controller_U.control_msgroll - PID_Controller_U.ist_roll;

  /* SampleTimeMath: '<S7>/TSamp'
   *
   * About '<S7>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp_f = rtb_Sum_a * PID_Controller_P.TSamp_WtEt_p;

  /* Outport: '<Root>/ctrl_roll' incorporates:
   *  Constant: '<S4>/D'
   *  Constant: '<S4>/I'
   *  Constant: '<S4>/P'
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product2'
   *  Sum: '<S4>/Sum1'
   *  Sum: '<S7>/Diff'
   *  UnitDelay: '<S7>/UD'
   */
  PID_Controller_Y.ctrl_roll = (rtb_Sum_a * PID_Controller_P.P_Value_d +
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d *
    PID_Controller_P.I_Value_b) + (rtb_TSamp_f - PID_Controller_DW.UD_DSTATE_n) *
    PID_Controller_P.D_Value_l;

  /* Sum: '<S2>/Sum' incorporates:
   *  Inport: '<Root>/control_msg.azimuth'
   *  Inport: '<Root>/ist_azimuth'
   */
  rtb_Sum_b = PID_Controller_U.control_msgazimuth - PID_Controller_U.ist_azimuth;

  /* SampleTimeMath: '<S5>/TSamp'
   *
   * About '<S5>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp_b = rtb_Sum_b * PID_Controller_P.TSamp_WtEt_pt;

  /* Outport: '<Root>/ctrl_azimuth' incorporates:
   *  Constant: '<S2>/D'
   *  Constant: '<S2>/I'
   *  Constant: '<S2>/P'
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Product: '<S2>/Product2'
   *  Sum: '<S2>/Sum1'
   *  Sum: '<S5>/Diff'
   *  UnitDelay: '<S5>/UD'
   */
  PID_Controller_Y.ctrl_azimuth = (rtb_Sum_b * PID_Controller_P.P_Value_j +
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g *
    PID_Controller_P.I_Value_a) + (rtb_TSamp_b - PID_Controller_DW.UD_DSTATE_a) *
    PID_Controller_P.D_Value_b;

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE +=
    PID_Controller_P.DiscreteTimeIntegrator_gainval * rtb_Sum;
  if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE >=
      PID_Controller_P.DiscreteTimeIntegrator_UpperSat) {
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE =
      PID_Controller_P.DiscreteTimeIntegrator_UpperSat;
  } else {
    if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE <=
        PID_Controller_P.DiscreteTimeIntegrator_LowerSat) {
      PID_Controller_DW.DiscreteTimeIntegrator_DSTATE =
        PID_Controller_P.DiscreteTimeIntegrator_LowerSat;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S6>/UD' */
  PID_Controller_DW.UD_DSTATE = rtb_TSamp;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d +=
    PID_Controller_P.DiscreteTimeIntegrator_gainva_j * rtb_Sum_a;
  if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d >=
      PID_Controller_P.DiscreteTimeIntegrator_UpperS_j) {
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d =
      PID_Controller_P.DiscreteTimeIntegrator_UpperS_j;
  } else {
    if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d <=
        PID_Controller_P.DiscreteTimeIntegrator_LowerS_d) {
      PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d =
        PID_Controller_P.DiscreteTimeIntegrator_LowerS_d;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S7>/UD' */
  PID_Controller_DW.UD_DSTATE_n = rtb_TSamp_f;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g +=
    PID_Controller_P.DiscreteTimeIntegrator_gainv_jy * rtb_Sum_b;
  if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g >=
      PID_Controller_P.DiscreteTimeIntegrator_UpperS_e) {
    PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g =
      PID_Controller_P.DiscreteTimeIntegrator_UpperS_e;
  } else {
    if (PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g <=
        PID_Controller_P.DiscreteTimeIntegrator_LowerS_a) {
      PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g =
        PID_Controller_P.DiscreteTimeIntegrator_LowerS_a;
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
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE =
    PID_Controller_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for UnitDelay: '<S6>/UD' */
  PID_Controller_DW.UD_DSTATE = PID_Controller_P.UD_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_d =
    PID_Controller_P.DiscreteTimeIntegrator_IC_c;

  /* InitializeConditions for UnitDelay: '<S7>/UD' */
  PID_Controller_DW.UD_DSTATE_n = PID_Controller_P.UD_InitialCondition_n;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  PID_Controller_DW.DiscreteTimeIntegrator_DSTATE_g =
    PID_Controller_P.DiscreteTimeIntegrator_IC_cx;

  /* InitializeConditions for UnitDelay: '<S5>/UD' */
  PID_Controller_DW.UD_DSTATE_a = PID_Controller_P.UD_InitialCondition_m;
}

/* Model terminate function */
void PID_Controller_terminate(void)
{
  /* (no terminate code required) */
}
