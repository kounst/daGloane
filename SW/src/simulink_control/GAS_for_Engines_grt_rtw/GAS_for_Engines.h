/*
 * GAS_for_Engines.h
 *
 * Code generation for model "GAS_for_Engines".
 *
 * Model version              : 1.39
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Tue Nov 12 14:36:05 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Passed (9), Warnings (2), Error (0)
 */
#ifndef RTW_HEADER_GAS_for_Engines_h_
#define RTW_HEADER_GAS_for_Engines_h_
#ifndef GAS_for_Engines_COMMON_INCLUDES_
# define GAS_for_Engines_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* GAS_for_Engines_COMMON_INCLUDES_ */

#include "GAS_for_Engines_types.h"

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

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T ctrl_pitch;                   /* '<Root>/ctrl_pitch' */
  real_T ctrl_roll;                    /* '<Root>/ctrl_roll' */
  real_T ctrl_azimuth;                 /* '<Root>/ctrl_azimuth' */
  real_T control_msgthrottle;          /* '<Root>/control_msg.throttle' */
} ExtU_GAS_for_Engines_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T out_e1;                       /* '<Root>/out_e1' */
  real_T out_e2;                       /* '<Root>/out_e2' */
  real_T out_e3;                       /* '<Root>/out_e3' */
  real_T out_e4;                       /* '<Root>/out_e4' */
} ExtY_GAS_for_Engines_T;

/* Real-time Model Data Structure */
struct tag_RTM_GAS_for_Engines_T {
  const char_T *errorStatus;
};

/* External inputs (root inport signals with auto storage) */
extern ExtU_GAS_for_Engines_T GAS_for_Engines_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_GAS_for_Engines_T GAS_for_Engines_Y;

/* Model entry point functions */
extern void GAS_for_Engines_initialize(void);
extern void GAS_for_Engines_step(void);
extern void GAS_for_Engines_terminate(void);

/* Real-time Model object */
extern RT_MODEL_GAS_for_Engines_T *const GAS_for_Engines_M;

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
 * hilite_system('complementary_controller/GAS_for_Engines')    - opens subsystem complementary_controller/GAS_for_Engines
 * hilite_system('complementary_controller/GAS_for_Engines/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'complementary_controller'
 * '<S1>'   : 'complementary_controller/GAS_for_Engines'
 * '<S2>'   : 'complementary_controller/GAS_for_Engines/GAS_E1'
 * '<S3>'   : 'complementary_controller/GAS_for_Engines/GAS_E2'
 * '<S4>'   : 'complementary_controller/GAS_for_Engines/GAS_E3'
 * '<S5>'   : 'complementary_controller/GAS_for_Engines/GAS_E4'
 */
#endif                                 /* RTW_HEADER_GAS_for_Engines_h_ */
