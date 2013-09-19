/*
 * Complementary_Filter.c
 *
 * Code generation for model "Complementary_Filter".
 *
 * Model version              : 1.20
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Thu Sep 19 13:47:59 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
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
  real_T rtb_Sum;
  real_T rtb_Sum1;

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
  rtb_Sum = (Complementary_Filter_P.Zeitschritt_Gain *
             Complementary_Filter_U.mpu_45gyro_x +
             Complementary_Filter_DW.UnitDelay_DSTATE) *
    Complementary_Filter_P.gain_gyro_to_ist_pitch_Value +
    Complementary_Filter_U.acc_pitch *
    Complementary_Filter_P.gain_acc_to_ist_pitch_Value;

  /* Outport: '<Root>/ist_pitch' */
  Complementary_Filter_Y.ist_pitch = rtb_Sum;

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
  rtb_Sum1 = (Complementary_Filter_P.Zeitschritt_Gain_a *
              Complementary_Filter_U.mpu_45gyro_y +
              Complementary_Filter_DW.UnitDelay_DSTATE_j) *
    Complementary_Filter_P.gain_gyro_to_ist_roll_Value +
    Complementary_Filter_U.acc_roll *
    Complementary_Filter_P.gain_acc_to_ist_roll_Value;

  /* Outport: '<Root>/ist_roll' */
  Complementary_Filter_Y.ist_roll = rtb_Sum1;

  /* Outport: '<Root>/ist_azimuth' incorporates:
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator'
   */
  Complementary_Filter_Y.ist_azimuth =
    Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  Complementary_Filter_DW.UnitDelay_DSTATE = rtb_Sum;

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  Complementary_Filter_DW.UnitDelay_DSTATE_j = rtb_Sum1;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' incorporates:
   *  Update for Inport: '<Root>/mpu_45.gyro_z'
   */
  Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE +=
    Complementary_Filter_P.DiscreteTimeIntegrator_gainval *
    Complementary_Filter_U.mpu_45gyro_z;
  if (Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE >=
      Complementary_Filter_P.DiscreteTimeIntegrator_UpperSat) {
    Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE =
      Complementary_Filter_P.DiscreteTimeIntegrator_UpperSat;
  } else {
    if (Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE <=
        Complementary_Filter_P.DiscreteTimeIntegrator_LowerSat) {
      Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE =
        Complementary_Filter_P.DiscreteTimeIntegrator_LowerSat;
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
  Complementary_Filter_DW.UnitDelay_DSTATE =
    Complementary_Filter_P.UnitDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S4>/Unit Delay' */
  Complementary_Filter_DW.UnitDelay_DSTATE_j =
    Complementary_Filter_P.UnitDelay_InitialCondition_d;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  Complementary_Filter_DW.DiscreteTimeIntegrator_DSTATE =
    Complementary_Filter_P.DiscreteTimeIntegrator_IC;
}

/* Model terminate function */
void Complementary_Filter_terminate(void)
{
  /* (no terminate code required) */
}
