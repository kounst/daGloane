/*
 * PID_Controller.h
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
#ifndef RTW_HEADER_PID_Controller_h_
#define RTW_HEADER_PID_Controller_h_
#ifndef PID_Controller_COMMON_INCLUDES_
# define PID_Controller_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* PID_Controller_COMMON_INCLUDES_ */

#include "PID_Controller_types.h"

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
  real_T UD_DSTATE;                    /* '<S6>/UD' */
  real_T DiscreteTimeIntegrator_DSTATE_d;/* '<S4>/Discrete-Time Integrator' */
  real_T UD_DSTATE_n;                  /* '<S7>/UD' */
  real_T DiscreteTimeIntegrator_DSTATE_g;/* '<S2>/Discrete-Time Integrator' */
  real_T UD_DSTATE_a;                  /* '<S5>/UD' */
} DW_PID_Controller_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T ist_pitch;                    /* '<Root>/ist_pitch' */
  real_T ist_roll;                     /* '<Root>/ist_roll' */
  real_T ist_azimuth;                  /* '<Root>/ist_azimuth' */
  real_T control_msgpitch;             /* '<Root>/control_msg.pitch' */
  real_T control_msgroll;              /* '<Root>/control_msg.roll' */
  real_T control_msgazimuth;           /* '<Root>/control_msg.azimuth' */
} ExtU_PID_Controller_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T ctrl_pitch;                   /* '<Root>/ctrl_pitch' */
  real_T ctrl_roll;                    /* '<Root>/ctrl_roll' */
  real_T ctrl_azimuth;                 /* '<Root>/ctrl_azimuth' */
} ExtY_PID_Controller_T;

/* Parameters (auto storage) */
struct P_PID_Controller_T_ {
  real_T P_Value;                      /* Expression: 1
                                        * Referenced by: '<S3>/P'
                                        */
  real_T DiscreteTimeIntegrator_gainval;/* Computed Parameter: DiscreteTimeIntegrator_gainval
                                         * Referenced by: '<S3>/Discrete-Time Integrator'
                                         */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<S3>/Discrete-Time Integrator'
                                        */
  real_T DiscreteTimeIntegrator_UpperSat;/* Expression: 0.5*10^18
                                          * Referenced by: '<S3>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_LowerSat;/* Expression: -0.5*10^37
                                          * Referenced by: '<S3>/Discrete-Time Integrator'
                                          */
  real_T I_Value;                      /* Expression: 1
                                        * Referenced by: '<S3>/I'
                                        */
  real_T D_Value;                      /* Expression: 1
                                        * Referenced by: '<S3>/D'
                                        */
  real_T TSamp_WtEt;                   /* Computed Parameter: TSamp_WtEt
                                        * Referenced by: '<S6>/TSamp'
                                        */
  real_T UD_InitialCondition;          /* Expression: ICPrevScaledInput
                                        * Referenced by: '<S6>/UD'
                                        */
  real_T P_Value_d;                    /* Expression: 1
                                        * Referenced by: '<S4>/P'
                                        */
  real_T DiscreteTimeIntegrator_gainva_j;/* Computed Parameter: DiscreteTimeIntegrator_gainva_j
                                          * Referenced by: '<S4>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_c;  /* Expression: 0
                                        * Referenced by: '<S4>/Discrete-Time Integrator'
                                        */
  real_T DiscreteTimeIntegrator_UpperS_j;/* Expression: 0.5*10^18
                                          * Referenced by: '<S4>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_LowerS_d;/* Expression: -0.5*10^37
                                          * Referenced by: '<S4>/Discrete-Time Integrator'
                                          */
  real_T I_Value_b;                    /* Expression: 1
                                        * Referenced by: '<S4>/I'
                                        */
  real_T D_Value_l;                    /* Expression: 1
                                        * Referenced by: '<S4>/D'
                                        */
  real_T TSamp_WtEt_p;                 /* Computed Parameter: TSamp_WtEt_p
                                        * Referenced by: '<S7>/TSamp'
                                        */
  real_T UD_InitialCondition_n;        /* Expression: ICPrevScaledInput
                                        * Referenced by: '<S7>/UD'
                                        */
  real_T P_Value_j;                    /* Expression: 1
                                        * Referenced by: '<S2>/P'
                                        */
  real_T DiscreteTimeIntegrator_gainv_jy;/* Computed Parameter: DiscreteTimeIntegrator_gainv_jy
                                          * Referenced by: '<S2>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_cx; /* Expression: 0
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  real_T DiscreteTimeIntegrator_UpperS_e;/* Expression: 0.5*10^18
                                          * Referenced by: '<S2>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_LowerS_a;/* Expression: -0.5*10^37
                                          * Referenced by: '<S2>/Discrete-Time Integrator'
                                          */
  real_T I_Value_a;                    /* Expression: 1
                                        * Referenced by: '<S2>/I'
                                        */
  real_T D_Value_b;                    /* Expression: 1
                                        * Referenced by: '<S2>/D'
                                        */
  real_T TSamp_WtEt_pt;                /* Computed Parameter: TSamp_WtEt_pt
                                        * Referenced by: '<S5>/TSamp'
                                        */
  real_T UD_InitialCondition_m;        /* Expression: ICPrevScaledInput
                                        * Referenced by: '<S5>/UD'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PID_Controller_T {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
extern P_PID_Controller_T PID_Controller_P;

/* Block states (auto storage) */
extern DW_PID_Controller_T PID_Controller_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_PID_Controller_T PID_Controller_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_PID_Controller_T PID_Controller_Y;

/* Model entry point functions */
extern void PID_Controller_initialize(void);
extern void PID_Controller_step(void);
extern void PID_Controller_terminate(void);

/* Real-time Model object */
extern RT_MODEL_PID_Controller_T *const PID_Controller_M;

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
 * hilite_system('complementary_controller/PID_Controller')    - opens subsystem complementary_controller/PID_Controller
 * hilite_system('complementary_controller/PID_Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'complementary_controller'
 * '<S1>'   : 'complementary_controller/PID_Controller'
 * '<S2>'   : 'complementary_controller/PID_Controller/PID_Azimuth'
 * '<S3>'   : 'complementary_controller/PID_Controller/PID_Pitch'
 * '<S4>'   : 'complementary_controller/PID_Controller/PID_Roll'
 * '<S5>'   : 'complementary_controller/PID_Controller/PID_Azimuth/Discrete Derivative'
 * '<S6>'   : 'complementary_controller/PID_Controller/PID_Pitch/Discrete Derivative'
 * '<S7>'   : 'complementary_controller/PID_Controller/PID_Roll/Discrete Derivative'
 */
#endif                                 /* RTW_HEADER_PID_Controller_h_ */
