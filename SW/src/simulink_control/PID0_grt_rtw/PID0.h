/*
 * PID0.h
 *
 * Code generation for model "PID0".
 *
 * Model version              : 1.5
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Tue Sep 10 11:53:22 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#ifndef RTW_HEADER_PID0_h_
#define RTW_HEADER_PID0_h_
#ifndef PID0_COMMON_INCLUDES_
# define PID0_COMMON_INCLUDES_
#include <float.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#endif                                 /* PID0_COMMON_INCLUDES_ */

#include "PID0_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
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
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T Sum;                          /* '<S3>/Sum' */
  real_T Sum_a;                        /* '<S4>/Sum' */
  real_T Sum_b;                        /* '<S2>/Sum' */
} B_PID0_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK;                  /* '<S3>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_g;                /* '<S4>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_h;                /* '<S2>/Derivative' */
} DW_PID0_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S4>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S2>/Integrator' */
} X_PID0_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S4>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S2>/Integrator' */
} XDot_PID0_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S3>/Integrator' */
  boolean_T Integrator_CSTATE_a;       /* '<S4>/Integrator' */
  boolean_T Integrator_CSTATE_c;       /* '<S2>/Integrator' */
} XDis_PID0_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T ist_pitch;                    /* '<Root>/ist_pitch' */
  real_T ist_roll;                     /* '<Root>/ist_roll' */
  real_T ist_azimuth;                  /* '<Root>/ist_azimuth' */
  real_T control_msgpitch;             /* '<Root>/control_msg.pitch' */
  real_T control_msgroll;              /* '<Root>/control_msg.roll' */
  real_T control_msgazimuth;           /* '<Root>/control_msg.azimuth' */
} ExtU_PID0_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T ctrl_pitch;                   /* '<Root>/ctrl_pitch' */
  real_T ctrl_roll;                    /* '<Root>/ctrl_roll' */
  real_T ctrl_azimuth;                 /* '<Root>/ctrl_azimuth' */
} ExtY_PID0_T;

/* Parameters (auto storage) */
struct P_PID0_T_ {
  real_T P_Value;                      /* Expression: 1
                                        * Referenced by: '<S3>/P'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S3>/Integrator'
                                        */
  real_T I_Value;                      /* Expression: 1
                                        * Referenced by: '<S3>/I'
                                        */
  real_T D_Value;                      /* Expression: 1
                                        * Referenced by: '<S3>/D'
                                        */
  real_T P_Value_d;                    /* Expression: 1
                                        * Referenced by: '<S4>/P'
                                        */
  real_T Integrator_IC_d;              /* Expression: 0
                                        * Referenced by: '<S4>/Integrator'
                                        */
  real_T I_Value_b;                    /* Expression: 1
                                        * Referenced by: '<S4>/I'
                                        */
  real_T D_Value_l;                    /* Expression: 1
                                        * Referenced by: '<S4>/D'
                                        */
  real_T P_Value_j;                    /* Expression: 1
                                        * Referenced by: '<S2>/P'
                                        */
  real_T Integrator_IC_m;              /* Expression: 0
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T I_Value_a;                    /* Expression: 1
                                        * Referenced by: '<S2>/I'
                                        */
  real_T D_Value_b;                    /* Expression: 1
                                        * Referenced by: '<S2>/D'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PID0_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    real_T *contStates;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[3];
    real_T odeF[3][3];
    ODE3_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_PID0_T PID0_P;

/* Block signals (auto storage) */
extern B_PID0_T PID0_B;

/* Continuous states (auto storage) */
extern X_PID0_T PID0_X;

/* Block states (auto storage) */
extern DW_PID0_T PID0_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_PID0_T PID0_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_PID0_T PID0_Y;

/* Model entry point functions */
extern void PID0_initialize(void);
extern void PID0_step(void);
extern void PID0_terminate(void);

/* Real-time Model object */
extern RT_MODEL_PID0_T *const PID0_M;

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
 * hilite_system('complementary_controller/PID Controller')    - opens subsystem complementary_controller/PID Controller
 * hilite_system('complementary_controller/PID Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'complementary_controller'
 * '<S1>'   : 'complementary_controller/PID Controller'
 * '<S2>'   : 'complementary_controller/PID Controller/PID Azimuth'
 * '<S3>'   : 'complementary_controller/PID Controller/PID Pitch'
 * '<S4>'   : 'complementary_controller/PID Controller/PID Roll'
 */
#endif                                 /* RTW_HEADER_PID0_h_ */
