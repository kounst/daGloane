/*
 * Complementary_Filter.h
 *
 * Code generation for model "Complementary_Filter".
 *
 * Model version              : 1.13
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Mon Sep 16 14:22:42 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Complementary_Filter_h_
#define RTW_HEADER_Complementary_Filter_h_
#ifndef Complementary_Filter_COMMON_INCLUDES_
# define Complementary_Filter_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Complementary_Filter_COMMON_INCLUDES_ */

#include "Complementary_Filter_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
  real_T UnitDelay_DSTATE;             /* '<S3>/Unit Delay' */
  real_T DiscreteTimeIntegrator_DSTATE_d;/* '<S4>/Discrete-Time Integrator' */
  real_T UnitDelay_DSTATE_j;           /* '<S4>/Unit Delay' */
  real_T DiscreteTimeIntegrator_DSTATE_f;/* '<S2>/Discrete-Time Integrator' */
} DW_Complementary_Filter_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T acc_pitch;                    /* '<Root>/acc_pitch' */
  real_T mpu_45gyro_x;                 /* '<Root>/mpu_45.gyro_x' */
  real_T acc_roll;                     /* '<Root>/acc_roll' */
  real_T mpu_45gyro_y;                 /* '<Root>/mpu_45.gyro_y' */
  real_T mpu_45gyro_z;                 /* '<Root>/mpu_45.gyro_z' */
} ExtU_Complementary_Filter_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T ist_pitch;                    /* '<Root>/ist_pitch' */
  real_T ist_roll;                     /* '<Root>/ist_roll' */
  real_T ist_azimuth;                  /* '<Root>/ist_azimuth' */
} ExtY_Complementary_Filter_T;

/* Parameters (auto storage) */
struct P_Complementary_Filter_T_ {
  real_T DiscreteTimeIntegrator_gainval;/* Computed Parameter: DiscreteTimeIntegrator_gainval
                                         * Referenced by: '<S3>/Discrete-Time Integrator'
                                         */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<S3>/Discrete-Time Integrator'
                                        */
  real_T DiscreteTimeIntegrator_UpperSat;/* Expression: 0.5*10^18
                                          * Referenced by: '<S3>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_LowerSat;/* Expression: -0.5*10^18
                                          * Referenced by: '<S3>/Discrete-Time Integrator'
                                          */
  real_T gain_gyro_to_ist_pitch_Value; /* Expression: 0.98
                                        * Referenced by: '<S3>/gain_gyro_to_ist_pitch'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay'
                                        */
  real_T gain_acc_to_ist_pitch_Value;  /* Expression: 0.02
                                        * Referenced by: '<S3>/gain_acc_to_ist_pitch'
                                        */
  real_T DiscreteTimeIntegrator_gainva_k;/* Computed Parameter: DiscreteTimeIntegrator_gainva_k
                                          * Referenced by: '<S4>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_m;  /* Expression: 0
                                        * Referenced by: '<S4>/Discrete-Time Integrator'
                                        */
  real_T DiscreteTimeIntegrator_UpperS_j;/* Expression: 0.5*10^18
                                          * Referenced by: '<S4>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_LowerS_l;/* Expression: -0.5*10^18
                                          * Referenced by: '<S4>/Discrete-Time Integrator'
                                          */
  real_T gain_gyro_to_ist_roll_Value;  /* Expression: 0.98
                                        * Referenced by: '<S4>/gain_gyro_to_ist_roll'
                                        */
  real_T UnitDelay_InitialCondition_d; /* Expression: 0
                                        * Referenced by: '<S4>/Unit Delay'
                                        */
  real_T gain_acc_to_ist_roll_Value;   /* Expression: 0.02
                                        * Referenced by: '<S4>/gain_acc_to_ist_roll'
                                        */
  real_T DiscreteTimeIntegrator_gainva_i;/* Computed Parameter: DiscreteTimeIntegrator_gainva_i
                                          * Referenced by: '<S2>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_k;  /* Expression: 0
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  real_T DiscreteTimeIntegrator_UpperS_a;/* Expression: 0.5*10^18
                                          * Referenced by: '<S2>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_LowerS_p;/* Expression: -0.5*10^18
                                          * Referenced by: '<S2>/Discrete-Time Integrator'
                                          */
};

/* Real-time Model Data Structure */
struct tag_RTM_Complementary_Filter_T {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
extern P_Complementary_Filter_T Complementary_Filter_P;

/* Block states (auto storage) */
extern DW_Complementary_Filter_T Complementary_Filter_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_Complementary_Filter_T Complementary_Filter_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Complementary_Filter_T Complementary_Filter_Y;

/* Model entry point functions */
extern void Complementary_Filter_initialize(void);
extern void Complementary_Filter_step(void);
extern void Complementary_Filter_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Complementary_Filter_T *const Complementary_Filter_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('complementary_controller/Complementary_Filter')    - opens subsystem complementary_controller/Complementary_Filter
 * hilite_system('complementary_controller/Complementary_Filter/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'complementary_controller'
 * '<S1>'   : 'complementary_controller/Complementary_Filter'
 * '<S2>'   : 'complementary_controller/Complementary_Filter/Azimuth_aus_Sensordaten'
 * '<S3>'   : 'complementary_controller/Complementary_Filter/Pitch_aus_Sensordaten'
 * '<S4>'   : 'complementary_controller/Complementary_Filter/Roll_aus_Sensordaten'
 */
#endif                                 /* RTW_HEADER_Complementary_Filter_h_ */
