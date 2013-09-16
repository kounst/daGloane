/*
 * Complementary_Filter_data.c
 *
 * Code generation for model "Complementary_Filter".
 *
 * Model version              : 1.12
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Mon Sep 16 12:23:11 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "Complementary_Filter.h"
#include "Complementary_Filter_private.h"

/* Block parameters (auto storage) */
P_Complementary_Filter_T Complementary_Filter_P = {
  0.001,                               /* Computed Parameter: DiscreteTimeIntegrator_gainval
                                        * Referenced by: '<S3>/Discrete-Time Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Discrete-Time Integrator'
                                        */
  5.0E+17,                             /* Expression: 0.5*10^18
                                        * Referenced by: '<S3>/Discrete-Time Integrator'
                                        */
  -5.0E+36,                            /* Expression: -0.5*10^37
                                        * Referenced by: '<S3>/Discrete-Time Integrator'
                                        */
  0.98,                                /* Expression: 0.98
                                        * Referenced by: '<S3>/gain_gyro_to_ist_pitch'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S3>/gain_acc_to_ist_pitch'
                                        */
  0.001,                               /* Computed Parameter: DiscreteTimeIntegrator_gainva_k
                                        * Referenced by: '<S4>/Discrete-Time Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Discrete-Time Integrator'
                                        */
  5.0E+17,                             /* Expression: 0.5*10^18
                                        * Referenced by: '<S4>/Discrete-Time Integrator'
                                        */
  -5.0E+36,                            /* Expression: -0.5*10^37
                                        * Referenced by: '<S4>/Discrete-Time Integrator'
                                        */
  0.98,                                /* Expression: 0.98
                                        * Referenced by: '<S4>/gain_gyro_to_ist_roll'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Unit Delay'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S4>/gain_acc_to_ist_roll'
                                        */
  0.001,                               /* Computed Parameter: DiscreteTimeIntegrator_gainva_i
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  5.0E+17,                             /* Expression: 0.5*10^18
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  -5.0E+36                             /* Expression: -0.5*10^37
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
};
