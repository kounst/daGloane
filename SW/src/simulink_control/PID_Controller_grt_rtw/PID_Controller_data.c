/*
 * PID_Controller_data.c
 *
 * Code generation for model "PID_Controller".
 *
 * Model version              : 1.12
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Mon Sep 16 12:23:48 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "PID_Controller.h"
#include "PID_Controller_private.h"

/* Block parameters (auto storage) */
P_PID_Controller_T PID_Controller_P = {
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/P'
                                        */
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
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/I'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/D'
                                        */
  1000.0,                              /* Computed Parameter: TSamp_WtEt
                                        * Referenced by: '<S6>/TSamp'
                                        */
  0.0,                                 /* Expression: ICPrevScaledInput
                                        * Referenced by: '<S6>/UD'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S4>/P'
                                        */
  0.001,                               /* Computed Parameter: DiscreteTimeIntegrator_gainva_j
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
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S4>/I'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S4>/D'
                                        */
  1000.0,                              /* Computed Parameter: TSamp_WtEt_p
                                        * Referenced by: '<S7>/TSamp'
                                        */
  0.0,                                 /* Expression: ICPrevScaledInput
                                        * Referenced by: '<S7>/UD'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/P'
                                        */
  0.001,                               /* Computed Parameter: DiscreteTimeIntegrator_gainv_jy
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  5.0E+17,                             /* Expression: 0.5*10^18
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  -5.0E+36,                            /* Expression: -0.5*10^37
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/I'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/D'
                                        */
  1000.0,                              /* Computed Parameter: TSamp_WtEt_pt
                                        * Referenced by: '<S5>/TSamp'
                                        */
  0.0                                  /* Expression: ICPrevScaledInput
                                        * Referenced by: '<S5>/UD'
                                        */
};
