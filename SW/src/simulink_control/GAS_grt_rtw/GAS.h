/*
 * GAS.h
 *
 * Code generation for model "GAS".
 *
 * Model version              : 1.5
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Tue Sep 10 12:04:14 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#ifndef RTW_HEADER_GAS_h_
#define RTW_HEADER_GAS_h_
#ifndef GAS_COMMON_INCLUDES_
# define GAS_COMMON_INCLUDES_
#include <float.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#endif                                 /* GAS_COMMON_INCLUDES_ */

#include "GAS_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T ctrl_pitch;                   /* '<Root>/ctrl_pitch' */
  real_T ctrl_roll;                    /* '<Root>/ctrl_roll' */
  real_T ctrl_azimuth;                 /* '<Root>/ctrl_azimuth' */
  real_T ctrl_throttle;                /* '<Root>/ctrl_throttle' */
} ExtU_GAS_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T out_e1;                       /* '<Root>/out_e1' */
  real_T out_e2;                       /* '<Root>/out_e2' */
  real_T out_e3;                       /* '<Root>/out_e3' */
  real_T out_e4;                       /* '<Root>/out_e4' */
} ExtY_GAS_T;

/* Parameters (auto storage) */
struct P_GAS_T_ {
  real_T weight_pitch_e1_Value;        /* Expression: 1
                                        * Referenced by: '<S2>/weight_pitch_e1'
                                        */
  real_T weight_roll_e1_Value;         /* Expression: 0
                                        * Referenced by: '<S2>/weight_roll_e1'
                                        */
  real_T weight_azimuth_e1_Value;      /* Expression: 0.1
                                        * Referenced by: '<S2>/weight_azimuth_e1'
                                        */
  real_T weight_pitch_e2_Value;        /* Expression: 0
                                        * Referenced by: '<S3>/weight_pitch_e2'
                                        */
  real_T weight_roll_e2_Value;         /* Expression: 1
                                        * Referenced by: '<S3>/weight_roll_e2'
                                        */
  real_T weight_azimuth_e2_Value;      /* Expression: -0.1
                                        * Referenced by: '<S3>/weight_azimuth_e2'
                                        */
  real_T weight_pitch_e3_Value;        /* Expression: -1
                                        * Referenced by: '<S4>/weight_pitch_e3'
                                        */
  real_T weight_roll_e3_Value;         /* Expression: 0
                                        * Referenced by: '<S4>/weight_roll_e3'
                                        */
  real_T weight_azimuth_e3_Value;      /* Expression: 0.1
                                        * Referenced by: '<S4>/weight_azimuth_e3'
                                        */
  real_T weight_pitch_e4_Value;        /* Expression: 0
                                        * Referenced by: '<S5>/weight_pitch_e4'
                                        */
  real_T weight_roll_e4_Value;         /* Expression: -1
                                        * Referenced by: '<S5>/weight_roll_e4'
                                        */
  real_T weight_azimuth_e4_Value;      /* Expression: -0.1
                                        * Referenced by: '<S5>/weight_azimuth_e4'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_GAS_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_GAS_T GAS_P;

/* External inputs (root inport signals with auto storage) */
extern ExtU_GAS_T GAS_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_GAS_T GAS_Y;

/* Model entry point functions */
extern void GAS_initialize(void);
extern void GAS_step(void);
extern void GAS_terminate(void);

/* Real-time Model object */
extern RT_MODEL_GAS_T *const GAS_M;

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
 * hilite_system('complementary_controller/GAS for Engines')    - opens subsystem complementary_controller/GAS for Engines
 * hilite_system('complementary_controller/GAS for Engines/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'complementary_controller'
 * '<S1>'   : 'complementary_controller/GAS for Engines'
 * '<S2>'   : 'complementary_controller/GAS for Engines/GAS E1'
 * '<S3>'   : 'complementary_controller/GAS for Engines/GAS E2'
 * '<S4>'   : 'complementary_controller/GAS for Engines/GAS E3'
 * '<S5>'   : 'complementary_controller/GAS for Engines/GAS E4'
 */
#endif                                 /* RTW_HEADER_GAS_h_ */
