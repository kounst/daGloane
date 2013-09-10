/*
 * complementary_controller.c
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

/* Block signals (auto storage) */
B_complementary_controller_T complementary_controller_B;

/* Continuous states */
X_complementary_controller_T complementary_controller_X;

/* Block states (auto storage) */
DW_complementary_controller_T complementary_controller_DW;

/* Real-time model */
RT_MODEL_complementary_contro_T complementary_controller_M_;
RT_MODEL_complementary_contro_T *const complementary_controller_M =
  &complementary_controller_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  complementary_controller_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  complementary_controller_step();
  complementary_controller_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  complementary_controller_step();
  complementary_controller_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void complementary_controller_step(void)
{
  if (rtmIsMajorTimeStep(complementary_controller_M)) {
    /* set solver stop time */
    if (!(complementary_controller_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&complementary_controller_M->solverInfo,
                            ((complementary_controller_M->Timing.clockTickH0 + 1)
        * complementary_controller_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&complementary_controller_M->solverInfo,
                            ((complementary_controller_M->Timing.clockTick0 + 1)
        * complementary_controller_M->Timing.stepSize0 +
        complementary_controller_M->Timing.clockTickH0 *
        complementary_controller_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(complementary_controller_M)) {
    complementary_controller_M->Timing.t[0] = rtsiGetT
      (&complementary_controller_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(complementary_controller_M)) {
    /* UnitDelay: '<S5>/Unit Delay' */
    complementary_controller_B.UnitDelay =
      complementary_controller_DW.UnitDelay_DSTATE;

    /* Product: '<S5>/Product1' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    complementary_controller_B.Product1 = 0.0 *
      complementary_controller_P.Constant1_Value;
  }

  /* Sum: '<S5>/Sum' incorporates:
   *  Constant: '<S5>/Constant'
   *  Integrator: '<S5>/Integrator'
   *  Product: '<S5>/Product'
   *  Sum: '<S5>/Sum1'
   */
  complementary_controller_B.Sum = (complementary_controller_X.Integrator_CSTATE
    + complementary_controller_B.UnitDelay) *
    complementary_controller_P.Constant_Value +
    complementary_controller_B.Product1;
  if (rtmIsMajorTimeStep(complementary_controller_M)) {
    /* UnitDelay: '<S6>/Unit Delay' */
    complementary_controller_B.UnitDelay_l =
      complementary_controller_DW.UnitDelay_DSTATE_j;

    /* Product: '<S6>/Product3' incorporates:
     *  Constant: '<S6>/Constant3'
     */
    complementary_controller_B.Product3 = 0.0 *
      complementary_controller_P.Constant3_Value;
  }

  /* Sum: '<S6>/Sum1' incorporates:
   *  Constant: '<S6>/Constant2'
   *  Integrator: '<S6>/Integrator'
   *  Product: '<S6>/Product2'
   *  Sum: '<S6>/Sum2'
   */
  complementary_controller_B.Sum1 =
    (complementary_controller_X.Integrator_CSTATE_c +
     complementary_controller_B.UnitDelay_l) *
    complementary_controller_P.Constant2_Value +
    complementary_controller_B.Product3;

  /* Sum: '<S12>/Sum' */
  complementary_controller_B.Sum_l = 0.0 - complementary_controller_B.Sum;

  /* Sum: '<S13>/Sum' */
  complementary_controller_B.Sum_a = 0.0 - complementary_controller_B.Sum1;

  /* Sum: '<S11>/Sum' incorporates:
   *  Integrator: '<S4>/Integrator'
   */
  complementary_controller_B.Sum_b = 0.0 -
    complementary_controller_X.Integrator_CSTATE_j;
  if (rtmIsMajorTimeStep(complementary_controller_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(complementary_controller_M->rtwLogInfo,
                        (complementary_controller_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(complementary_controller_M)) {
    if (rtmIsMajorTimeStep(complementary_controller_M)) {
      /* Update for UnitDelay: '<S5>/Unit Delay' */
      complementary_controller_DW.UnitDelay_DSTATE =
        complementary_controller_B.Sum;

      /* Update for UnitDelay: '<S6>/Unit Delay' */
      complementary_controller_DW.UnitDelay_DSTATE_j =
        complementary_controller_B.Sum1;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(complementary_controller_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(complementary_controller_M)!=-1) &&
          !((rtmGetTFinal(complementary_controller_M)-
             (((complementary_controller_M->Timing.clockTick1+
                complementary_controller_M->Timing.clockTickH1* 4294967296.0)) *
              0.001)) > (((complementary_controller_M->Timing.clockTick1+
                           complementary_controller_M->Timing.clockTickH1*
                           4294967296.0)) * 0.001) * (DBL_EPSILON))) {
        rtmSetErrorStatus(complementary_controller_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&complementary_controller_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++complementary_controller_M->Timing.clockTick0)) {
      ++complementary_controller_M->Timing.clockTickH0;
    }

    complementary_controller_M->Timing.t[0] = rtsiGetSolverStopTime
      (&complementary_controller_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      complementary_controller_M->Timing.clockTick1++;
      if (!complementary_controller_M->Timing.clockTick1) {
        complementary_controller_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void complementary_controller_derivatives(void)
{
  XDot_complementary_controller_T *_rtXdot;
  _rtXdot = ((XDot_complementary_controller_T *)
             complementary_controller_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S5>/Integrator' */
  _rtXdot->Integrator_CSTATE = 0.0;

  /* Derivatives for Integrator: '<S6>/Integrator' */
  _rtXdot->Integrator_CSTATE_c = 0.0;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE_j = 0.0;

  /* Derivatives for Integrator: '<S12>/Integrator' */
  _rtXdot->Integrator_CSTATE_d = complementary_controller_B.Sum_l;

  /* Derivatives for Integrator: '<S13>/Integrator' */
  _rtXdot->Integrator_CSTATE_a = complementary_controller_B.Sum_a;

  /* Derivatives for Integrator: '<S11>/Integrator' */
  _rtXdot->Integrator_CSTATE_c3 = complementary_controller_B.Sum_b;
}

/* Model initialize function */
void complementary_controller_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)complementary_controller_M, 0,
                sizeof(RT_MODEL_complementary_contro_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&complementary_controller_M->solverInfo,
                          &complementary_controller_M->Timing.simTimeStep);
    rtsiSetTPtr(&complementary_controller_M->solverInfo, &rtmGetTPtr
                (complementary_controller_M));
    rtsiSetStepSizePtr(&complementary_controller_M->solverInfo,
                       &complementary_controller_M->Timing.stepSize0);
    rtsiSetdXPtr(&complementary_controller_M->solverInfo,
                 &complementary_controller_M->ModelData.derivs);
    rtsiSetContStatesPtr(&complementary_controller_M->solverInfo,
                         &complementary_controller_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&complementary_controller_M->solverInfo,
      &complementary_controller_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&complementary_controller_M->solverInfo,
                          (&rtmGetErrorStatus(complementary_controller_M)));
    rtsiSetRTModelPtr(&complementary_controller_M->solverInfo,
                      complementary_controller_M);
  }

  rtsiSetSimTimeStep(&complementary_controller_M->solverInfo, MAJOR_TIME_STEP);
  complementary_controller_M->ModelData.intgData.y =
    complementary_controller_M->ModelData.odeY;
  complementary_controller_M->ModelData.intgData.f[0] =
    complementary_controller_M->ModelData.odeF[0];
  complementary_controller_M->ModelData.intgData.f[1] =
    complementary_controller_M->ModelData.odeF[1];
  complementary_controller_M->ModelData.intgData.f[2] =
    complementary_controller_M->ModelData.odeF[2];
  complementary_controller_M->ModelData.contStates = ((real_T *)
    &complementary_controller_X);
  rtsiSetSolverData(&complementary_controller_M->solverInfo, (void *)
                    &complementary_controller_M->ModelData.intgData);
  rtsiSetSolverName(&complementary_controller_M->solverInfo,"ode3");
  rtmSetTPtr(complementary_controller_M,
             &complementary_controller_M->Timing.tArray[0]);
  rtmSetTFinal(complementary_controller_M, 10.0);
  complementary_controller_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    complementary_controller_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(complementary_controller_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(complementary_controller_M->rtwLogInfo, (NULL));
    rtliSetLogT(complementary_controller_M->rtwLogInfo, "tout");
    rtliSetLogX(complementary_controller_M->rtwLogInfo, "");
    rtliSetLogXFinal(complementary_controller_M->rtwLogInfo, "");
    rtliSetSigLog(complementary_controller_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(complementary_controller_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(complementary_controller_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(complementary_controller_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(complementary_controller_M->rtwLogInfo, 1);
    rtliSetLogY(complementary_controller_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(complementary_controller_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(complementary_controller_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &complementary_controller_B), 0,
                sizeof(B_complementary_controller_T));

  /* states (continuous) */
  {
    (void) memset((void *)&complementary_controller_X, 0,
                  sizeof(X_complementary_controller_T));
  }

  /* states (dwork) */
  (void) memset((void *)&complementary_controller_DW, 0,
                sizeof(DW_complementary_controller_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(complementary_controller_M->rtwLogInfo, 0.0,
    rtmGetTFinal(complementary_controller_M),
    complementary_controller_M->Timing.stepSize0, (&rtmGetErrorStatus
    (complementary_controller_M)));

  /* InitializeConditions for Integrator: '<S5>/Integrator' */
  complementary_controller_X.Integrator_CSTATE =
    complementary_controller_P.Integrator_IC;

  /* InitializeConditions for UnitDelay: '<S5>/Unit Delay' */
  complementary_controller_DW.UnitDelay_DSTATE =
    complementary_controller_P.UnitDelay_InitialCondition;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  complementary_controller_X.Integrator_CSTATE_c =
    complementary_controller_P.Integrator_IC_g;

  /* InitializeConditions for UnitDelay: '<S6>/Unit Delay' */
  complementary_controller_DW.UnitDelay_DSTATE_j =
    complementary_controller_P.UnitDelay_InitialCondition_d;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  complementary_controller_X.Integrator_CSTATE_j =
    complementary_controller_P.Integrator_IC_e;

  /* InitializeConditions for Integrator: '<S12>/Integrator' */
  complementary_controller_X.Integrator_CSTATE_d =
    complementary_controller_P.Integrator_IC_o;

  /* InitializeConditions for Integrator: '<S13>/Integrator' */
  complementary_controller_X.Integrator_CSTATE_a =
    complementary_controller_P.Integrator_IC_d;

  /* InitializeConditions for Integrator: '<S11>/Integrator' */
  complementary_controller_X.Integrator_CSTATE_c3 =
    complementary_controller_P.Integrator_IC_m;
}

/* Model terminate function */
void complementary_controller_terminate(void)
{
  /* (no terminate code required) */
}
