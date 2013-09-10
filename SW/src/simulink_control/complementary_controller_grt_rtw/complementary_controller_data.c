/*
 * complementary_controller_data.c
 *
 * Code generation for model "complementary_controller".
 *
 * Model version              : 1.5
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Tue Sep 10 10:42:33 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "complementary_controller.h"
#include "complementary_controller_private.h"

/* Block parameters (auto storage) */
P_complementary_controller_T complementary_controller_P = {
  0.98,                                /* Expression: 0.98
                                        * Referenced by: '<S5>/Constant'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S5>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Unit Delay'
                                        */
  0.98,                                /* Expression: 0.98
                                        * Referenced by: '<S6>/Constant2'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S6>/Constant3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Unit Delay'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S13>/Integrator'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S11>/Integrator'
                                        */
};
