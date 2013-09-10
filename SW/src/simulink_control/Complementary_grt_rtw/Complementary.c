/*
 * Complementary.c
 *
 * Code generation for model "Complementary".
 *
 * Model version              : 1.5
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Tue Sep 10 12:03:21 2013
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "Complementary.h"
#include "Complementary_private.h"

/* Block signals (auto storage) */
B_Complementary_T Complementary_B;

/* Continuous states */
X_Complementary_T Complementary_X;

/* Block states (auto storage) */
DW_Complementary_T Complementary_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_Complementary_T Complementary_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_Complementary_T Complementary_Y;

/* Real-time model */
RT_MODEL_Complementary_T Complementary_M_;
RT_MODEL_Complementary_T *const Complementary_M = &Complementary_M_;

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
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Complementary_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Complementary_step();
  Complementary_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Complementary_step();
  Complementary_derivatives();

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
void Complementary_step(void)
{
  if (rtmIsMajorTimeStep(Complementary_M)) {
    /* set solver stop time */
    if (!(Complementary_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Complementary_M->solverInfo,
                            ((Complementary_M->Timing.clockTickH0 + 1) *
        Complementary_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Complementary_M->solverInfo,
                            ((Complementary_M->Timing.clockTick0 + 1) *
        Complementary_M->Timing.stepSize0 + Complementary_M->Timing.clockTickH0 *
        Complementary_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Complementary_M)) {
    Complementary_M->Timing.t[0] = rtsiGetT(&Complementary_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Complementary_M)) {
    /* UnitDelay: '<S3>/Unit Delay' */
    Complementary_B.UnitDelay = Complementary_DW.UnitDelay_DSTATE;
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant1'
   *  Inport: '<Root>/acc_pitch'
   *  Integrator: '<S3>/Integrator'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Sum: '<S3>/Sum1'
   */
  Complementary_B.Sum = (Complementary_X.Integrator_CSTATE +
    Complementary_B.UnitDelay) * Complementary_P.Constant_Value +
    Complementary_U.acc_pitch * Complementary_P.Constant1_Value;

  /* Outport: '<Root>/ist_pitch' */
  Complementary_Y.ist_pitch = Complementary_B.Sum;
  if (rtmIsMajorTimeStep(Complementary_M)) {
    /* UnitDelay: '<S4>/Unit Delay' */
    Complementary_B.UnitDelay_l = Complementary_DW.UnitDelay_DSTATE_j;
  }

  /* Sum: '<S4>/Sum1' incorporates:
   *  Constant: '<S4>/Constant2'
   *  Constant: '<S4>/Constant3'
   *  Inport: '<Root>/acc_roll'
   *  Integrator: '<S4>/Integrator'
   *  Product: '<S4>/Product2'
   *  Product: '<S4>/Product3'
   *  Sum: '<S4>/Sum2'
   */
  Complementary_B.Sum1 = (Complementary_X.Integrator_CSTATE_c +
    Complementary_B.UnitDelay_l) * Complementary_P.Constant2_Value +
    Complementary_U.acc_roll * Complementary_P.Constant3_Value;

  /* Outport: '<Root>/ist_roll' */
  Complementary_Y.ist_roll = Complementary_B.Sum1;

  /* Outport: '<Root>/ist_azimuth' incorporates:
   *  Integrator: '<S2>/Integrator'
   */
  Complementary_Y.ist_azimuth = Complementary_X.Integrator_CSTATE_j;
  if (rtmIsMajorTimeStep(Complementary_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(Complementary_M->rtwLogInfo, (Complementary_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Complementary_M)) {
    if (rtmIsMajorTimeStep(Complementary_M)) {
      /* Update for UnitDelay: '<S3>/Unit Delay' */
      Complementary_DW.UnitDelay_DSTATE = Complementary_B.Sum;

      /* Update for UnitDelay: '<S4>/Unit Delay' */
      Complementary_DW.UnitDelay_DSTATE_j = Complementary_B.Sum1;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Complementary_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Complementary_M)!=-1) &&
          !((rtmGetTFinal(Complementary_M)-(((Complementary_M->Timing.clockTick1
               +Complementary_M->Timing.clockTickH1* 4294967296.0)) * 0.001)) >
            (((Complementary_M->Timing.clockTick1+
               Complementary_M->Timing.clockTickH1* 4294967296.0)) * 0.001) *
            (DBL_EPSILON))) {
        rtmSetErrorStatus(Complementary_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&Complementary_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Complementary_M->Timing.clockTick0)) {
      ++Complementary_M->Timing.clockTickH0;
    }

    Complementary_M->Timing.t[0] = rtsiGetSolverStopTime
      (&Complementary_M->solverInfo);

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
      Complementary_M->Timing.clockTick1++;
      if (!Complementary_M->Timing.clockTick1) {
        Complementary_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Complementary_derivatives(void)
{
  XDot_Complementary_T *_rtXdot;
  _rtXdot = ((XDot_Complementary_T *) Complementary_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S3>/Integrator' incorporates:
   *  Derivatives for Inport: '<Root>/mpu_45.gyro_x'
   */
  _rtXdot->Integrator_CSTATE = Complementary_U.mpu_45gyro_x;

  /* Derivatives for Integrator: '<S4>/Integrator' incorporates:
   *  Derivatives for Inport: '<Root>/mpu_45.gyro_y'
   */
  _rtXdot->Integrator_CSTATE_c = Complementary_U.mpu_45gyro_y;

  /* Derivatives for Integrator: '<S2>/Integrator' incorporates:
   *  Derivatives for Inport: '<Root>/mpu_45.gyro_z'
   */
  _rtXdot->Integrator_CSTATE_j = Complementary_U.mpu_45gyro_z;
}

/* Model initialize function */
void Complementary_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Complementary_M, 0,
                sizeof(RT_MODEL_Complementary_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Complementary_M->solverInfo,
                          &Complementary_M->Timing.simTimeStep);
    rtsiSetTPtr(&Complementary_M->solverInfo, &rtmGetTPtr(Complementary_M));
    rtsiSetStepSizePtr(&Complementary_M->solverInfo,
                       &Complementary_M->Timing.stepSize0);
    rtsiSetdXPtr(&Complementary_M->solverInfo,
                 &Complementary_M->ModelData.derivs);
    rtsiSetContStatesPtr(&Complementary_M->solverInfo,
                         &Complementary_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&Complementary_M->solverInfo,
      &Complementary_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&Complementary_M->solverInfo, (&rtmGetErrorStatus
      (Complementary_M)));
    rtsiSetRTModelPtr(&Complementary_M->solverInfo, Complementary_M);
  }

  rtsiSetSimTimeStep(&Complementary_M->solverInfo, MAJOR_TIME_STEP);
  Complementary_M->ModelData.intgData.y = Complementary_M->ModelData.odeY;
  Complementary_M->ModelData.intgData.f[0] = Complementary_M->ModelData.odeF[0];
  Complementary_M->ModelData.intgData.f[1] = Complementary_M->ModelData.odeF[1];
  Complementary_M->ModelData.intgData.f[2] = Complementary_M->ModelData.odeF[2];
  Complementary_M->ModelData.contStates = ((real_T *) &Complementary_X);
  rtsiSetSolverData(&Complementary_M->solverInfo, (void *)
                    &Complementary_M->ModelData.intgData);
  rtsiSetSolverName(&Complementary_M->solverInfo,"ode3");
  rtmSetTPtr(Complementary_M, &Complementary_M->Timing.tArray[0]);
  rtmSetTFinal(Complementary_M, 10.0);
  Complementary_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    Complementary_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Complementary_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Complementary_M->rtwLogInfo, (NULL));
    rtliSetLogT(Complementary_M->rtwLogInfo, "tout");
    rtliSetLogX(Complementary_M->rtwLogInfo, "");
    rtliSetLogXFinal(Complementary_M->rtwLogInfo, "");
    rtliSetSigLog(Complementary_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Complementary_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Complementary_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(Complementary_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(Complementary_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &Complementary_Y.ist_pitch,
        &Complementary_Y.ist_roll,
        &Complementary_Y.ist_azimuth
      };

      rtliSetLogYSignalPtrs(Complementary_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        1,
        1,
        1
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0,
        0,
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL),
        (NULL),
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4,
        4,
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0,
        0,
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "",
        "",
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "Complementary/ist_pitch",
        "Complementary/ist_roll",
        "Complementary/ist_azimuth" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          3,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedCurrentSignalDimensionsSize,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(Complementary_M->rtwLogInfo,
                            rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
      rt_LoggedCurrentSignalDimensions[2] = &rt_LoggedOutputWidths[2];
    }

    rtliSetLogY(Complementary_M->rtwLogInfo, "yout");
  }

  /* block I/O */
  (void) memset(((void *) &Complementary_B), 0,
                sizeof(B_Complementary_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Complementary_X, 0,
                  sizeof(X_Complementary_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Complementary_DW, 0,
                sizeof(DW_Complementary_T));

  /* external inputs */
  (void) memset((void *)&Complementary_U, 0,
                sizeof(ExtU_Complementary_T));

  /* external outputs */
  (void) memset((void *)&Complementary_Y, 0,
                sizeof(ExtY_Complementary_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Complementary_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Complementary_M), Complementary_M->Timing.stepSize0,
    (&rtmGetErrorStatus(Complementary_M)));

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  Complementary_X.Integrator_CSTATE = Complementary_P.Integrator_IC;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
  Complementary_DW.UnitDelay_DSTATE = Complementary_P.UnitDelay_InitialCondition;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  Complementary_X.Integrator_CSTATE_c = Complementary_P.Integrator_IC_g;

  /* InitializeConditions for UnitDelay: '<S4>/Unit Delay' */
  Complementary_DW.UnitDelay_DSTATE_j =
    Complementary_P.UnitDelay_InitialCondition_d;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  Complementary_X.Integrator_CSTATE_j = Complementary_P.Integrator_IC_e;
}

/* Model terminate function */
void Complementary_terminate(void)
{
  /* (no terminate code required) */
}
