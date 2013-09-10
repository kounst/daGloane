/*
 * complementary_controller.h
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
#ifndef RTW_HEADER_complementary_controller_h_
#define RTW_HEADER_complementary_controller_h_
#ifndef complementary_controller_COMMON_INCLUDES_
# define complementary_controller_COMMON_INCLUDES_
#include <float.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#endif                                 /* complementary_controller_COMMON_INCLUDES_ */

#include "complementary_controller_types.h"

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
  real_T UnitDelay;                    /* '<S5>/Unit Delay' */
  real_T Product1;                     /* '<S5>/Product1' */
  real_T Sum;                          /* '<S5>/Sum' */
  real_T UnitDelay_l;                  /* '<S6>/Unit Delay' */
  real_T Product3;                     /* '<S6>/Product3' */
  real_T Sum1;                         /* '<S6>/Sum1' */
  real_T Sum_l;                        /* '<S12>/Sum' */
  real_T Sum_a;                        /* '<S13>/Sum' */
  real_T Sum_b;                        /* '<S11>/Sum' */
} B_complementary_controller_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<S5>/Unit Delay' */
  real_T UnitDelay_DSTATE_j;           /* '<S6>/Unit Delay' */
} DW_complementary_controller_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S6>/Integrator' */
  real_T Integrator_CSTATE_j;          /* '<S4>/Integrator' */
  real_T Integrator_CSTATE_d;          /* '<S12>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S13>/Integrator' */
  real_T Integrator_CSTATE_c3;         /* '<S11>/Integrator' */
} X_complementary_controller_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S6>/Integrator' */
  real_T Integrator_CSTATE_j;          /* '<S4>/Integrator' */
  real_T Integrator_CSTATE_d;          /* '<S12>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S13>/Integrator' */
  real_T Integrator_CSTATE_c3;         /* '<S11>/Integrator' */
} XDot_complementary_controller_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S5>/Integrator' */
  boolean_T Integrator_CSTATE_c;       /* '<S6>/Integrator' */
  boolean_T Integrator_CSTATE_j;       /* '<S4>/Integrator' */
  boolean_T Integrator_CSTATE_d;       /* '<S12>/Integrator' */
  boolean_T Integrator_CSTATE_a;       /* '<S13>/Integrator' */
  boolean_T Integrator_CSTATE_c3;      /* '<S11>/Integrator' */
} XDis_complementary_controller_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (auto storage) */
struct P_complementary_controller_T_ {
  real_T Constant_Value;               /* Expression: 0.98
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 0.02
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S5>/Integrator'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<S5>/Unit Delay'
                                        */
  real_T Constant2_Value;              /* Expression: 0.98
                                        * Referenced by: '<S6>/Constant2'
                                        */
  real_T Constant3_Value;              /* Expression: 0.02
                                        * Referenced by: '<S6>/Constant3'
                                        */
  real_T Integrator_IC_g;              /* Expression: 0
                                        * Referenced by: '<S6>/Integrator'
                                        */
  real_T UnitDelay_InitialCondition_d; /* Expression: 0
                                        * Referenced by: '<S6>/Unit Delay'
                                        */
  real_T Integrator_IC_e;              /* Expression: 0
                                        * Referenced by: '<S4>/Integrator'
                                        */
  real_T Integrator_IC_o;              /* Expression: 0
                                        * Referenced by: '<S12>/Integrator'
                                        */
  real_T Integrator_IC_d;              /* Expression: 0
                                        * Referenced by: '<S13>/Integrator'
                                        */
  real_T Integrator_IC_m;              /* Expression: 0
                                        * Referenced by: '<S11>/Integrator'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_complementary_control_T {
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
    real_T odeY[6];
    real_T odeF[3][6];
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
extern P_complementary_controller_T complementary_controller_P;

/* Block signals (auto storage) */
extern B_complementary_controller_T complementary_controller_B;

/* Continuous states (auto storage) */
extern X_complementary_controller_T complementary_controller_X;

/* Block states (auto storage) */
extern DW_complementary_controller_T complementary_controller_DW;

/* Model entry point functions */
extern void complementary_controller_initialize(void);
extern void complementary_controller_step(void);
extern void complementary_controller_terminate(void);

/* Real-time Model object */
extern RT_MODEL_complementary_contro_T *const complementary_controller_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'complementary_controller'
 * '<S1>'   : 'complementary_controller/Complementary Filter'
 * '<S2>'   : 'complementary_controller/GAS for Engines'
 * '<S3>'   : 'complementary_controller/PID Controller'
 * '<S4>'   : 'complementary_controller/Complementary Filter/Azimuth aus Sensordaten'
 * '<S5>'   : 'complementary_controller/Complementary Filter/Pitch aus Sensordaten'
 * '<S6>'   : 'complementary_controller/Complementary Filter/Roll aus Sensordaten'
 * '<S7>'   : 'complementary_controller/GAS for Engines/GAS E1'
 * '<S8>'   : 'complementary_controller/GAS for Engines/GAS E2'
 * '<S9>'   : 'complementary_controller/GAS for Engines/GAS E3'
 * '<S10>'  : 'complementary_controller/GAS for Engines/GAS E4'
 * '<S11>'  : 'complementary_controller/PID Controller/PID Azimuth'
 * '<S12>'  : 'complementary_controller/PID Controller/PID Pitch'
 * '<S13>'  : 'complementary_controller/PID Controller/PID Roll'
 */
#endif                                 /* RTW_HEADER_complementary_controller_h_ */
