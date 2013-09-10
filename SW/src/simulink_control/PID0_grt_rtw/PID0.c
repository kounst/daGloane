/*
 * PID0.c
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
#include "PID0.h"
#include "PID0_private.h"

/* Block signals (auto storage) */
B_PID0_T PID0_B;

/* Continuous states */
X_PID0_T PID0_X;

/* Block states (auto storage) */
DW_PID0_T PID0_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_PID0_T PID0_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_PID0_T PID0_Y;

/* Real-time model */
RT_MODEL_PID0_T PID0_M_;
RT_MODEL_PID0_T *const PID0_M = &PID0_M_;

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
  PID0_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  PID0_step();
  PID0_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  PID0_step();
  PID0_derivatives();

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
void PID0_step(void)
{
  /* local block i/o variables */
  real_T rtb_Derivative;
  real_T rtb_Product;
  real_T rtb_Product1;
  if (rtmIsMajorTimeStep(PID0_M)) {
    /* set solver stop time */
    if (!(PID0_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&PID0_M->solverInfo, ((PID0_M->Timing.clockTickH0 +
        1) * PID0_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&PID0_M->solverInfo, ((PID0_M->Timing.clockTick0 + 1)
        * PID0_M->Timing.stepSize0 + PID0_M->Timing.clockTickH0 *
        PID0_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(PID0_M)) {
    PID0_M->Timing.t[0] = rtsiGetT(&PID0_M->solverInfo);
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Inport: '<Root>/control_msg.pitch'
   *  Inport: '<Root>/ist_pitch'
   */
  PID0_B.Sum = PID0_U.control_msgpitch - PID0_U.ist_pitch;

  /* Product: '<S3>/Product' incorporates:
   *  Constant: '<S3>/P'
   */
  rtb_Product = PID0_B.Sum * PID0_P.P_Value;

  /* Integrator: '<S3>/Integrator' */
  rtb_Derivative = PID0_X.Integrator_CSTATE;

  /* Product: '<S3>/Product1' incorporates:
   *  Constant: '<S3>/I'
   */
  rtb_Product1 = rtb_Derivative * PID0_P.I_Value;

  /* Derivative: '<S3>/Derivative' */
  {
    real_T t = PID0_M->Timing.t[0];
    real_T timeStampA = PID0_DW.Derivative_RWORK.TimeStampA;
    real_T timeStampB = PID0_DW.Derivative_RWORK.TimeStampB;
    real_T *lastU = &PID0_DW.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &PID0_DW.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &PID0_DW.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      rtb_Derivative = (PID0_B.Sum - *lastU++) / deltaT;
    }
  }

  /* Outport: '<Root>/ctrl_pitch' incorporates:
   *  Constant: '<S3>/D'
   *  Product: '<S3>/Product2'
   *  Sum: '<S3>/Sum1'
   */
  PID0_Y.ctrl_pitch = (rtb_Product + rtb_Product1) + PID0_P.D_Value *
    rtb_Derivative;

  /* Sum: '<S4>/Sum' incorporates:
   *  Inport: '<Root>/control_msg.roll'
   *  Inport: '<Root>/ist_roll'
   */
  PID0_B.Sum_a = PID0_U.control_msgroll - PID0_U.ist_roll;

  /* Product: '<S4>/Product' incorporates:
   *  Constant: '<S4>/P'
   */
  rtb_Product = PID0_B.Sum_a * PID0_P.P_Value_d;

  /* Integrator: '<S4>/Integrator' */
  rtb_Derivative = PID0_X.Integrator_CSTATE_a;

  /* Product: '<S4>/Product1' incorporates:
   *  Constant: '<S4>/I'
   */
  rtb_Product1 = rtb_Derivative * PID0_P.I_Value_b;

  /* Derivative: '<S4>/Derivative' */
  {
    real_T t = PID0_M->Timing.t[0];
    real_T timeStampA = PID0_DW.Derivative_RWORK_g.TimeStampA;
    real_T timeStampB = PID0_DW.Derivative_RWORK_g.TimeStampB;
    real_T *lastU = &PID0_DW.Derivative_RWORK_g.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &PID0_DW.Derivative_RWORK_g.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &PID0_DW.Derivative_RWORK_g.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      rtb_Derivative = (PID0_B.Sum_a - *lastU++) / deltaT;
    }
  }

  /* Outport: '<Root>/ctrl_roll' incorporates:
   *  Constant: '<S4>/D'
   *  Product: '<S4>/Product2'
   *  Sum: '<S4>/Sum1'
   */
  PID0_Y.ctrl_roll = (rtb_Product + rtb_Product1) + PID0_P.D_Value_l *
    rtb_Derivative;

  /* Sum: '<S2>/Sum' incorporates:
   *  Inport: '<Root>/control_msg.azimuth'
   *  Inport: '<Root>/ist_azimuth'
   */
  PID0_B.Sum_b = PID0_U.control_msgazimuth - PID0_U.ist_azimuth;

  /* Product: '<S2>/Product' incorporates:
   *  Constant: '<S2>/P'
   */
  rtb_Product = PID0_B.Sum_b * PID0_P.P_Value_j;

  /* Integrator: '<S2>/Integrator' */
  rtb_Derivative = PID0_X.Integrator_CSTATE_c;

  /* Product: '<S2>/Product1' incorporates:
   *  Constant: '<S2>/I'
   */
  rtb_Product1 = rtb_Derivative * PID0_P.I_Value_a;

  /* Derivative: '<S2>/Derivative' */
  {
    real_T t = PID0_M->Timing.t[0];
    real_T timeStampA = PID0_DW.Derivative_RWORK_h.TimeStampA;
    real_T timeStampB = PID0_DW.Derivative_RWORK_h.TimeStampB;
    real_T *lastU = &PID0_DW.Derivative_RWORK_h.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &PID0_DW.Derivative_RWORK_h.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &PID0_DW.Derivative_RWORK_h.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      rtb_Derivative = (PID0_B.Sum_b - *lastU++) / deltaT;
    }
  }

  /* Outport: '<Root>/ctrl_azimuth' incorporates:
   *  Constant: '<S2>/D'
   *  Product: '<S2>/Product2'
   *  Sum: '<S2>/Sum1'
   */
  PID0_Y.ctrl_azimuth = (rtb_Product + rtb_Product1) + PID0_P.D_Value_b *
    rtb_Derivative;
  if (rtmIsMajorTimeStep(PID0_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(PID0_M->rtwLogInfo, (PID0_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(PID0_M)) {
    /* Update for Derivative: '<S3>/Derivative' */
    {
      real_T timeStampA = PID0_DW.Derivative_RWORK.TimeStampA;
      real_T timeStampB = PID0_DW.Derivative_RWORK.TimeStampB;
      real_T* lastTime = &PID0_DW.Derivative_RWORK.TimeStampA;
      real_T* lastU = &PID0_DW.Derivative_RWORK.LastUAtTimeA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastTime = &PID0_DW.Derivative_RWORK.TimeStampB;
          lastU = &PID0_DW.Derivative_RWORK.LastUAtTimeB;
        } else if (timeStampA >= timeStampB) {
          lastTime = &PID0_DW.Derivative_RWORK.TimeStampB;
          lastU = &PID0_DW.Derivative_RWORK.LastUAtTimeB;
        }
      }

      *lastTime = PID0_M->Timing.t[0];
      *lastU++ = PID0_B.Sum;
    }

    /* Update for Derivative: '<S4>/Derivative' */
    {
      real_T timeStampA = PID0_DW.Derivative_RWORK_g.TimeStampA;
      real_T timeStampB = PID0_DW.Derivative_RWORK_g.TimeStampB;
      real_T* lastTime = &PID0_DW.Derivative_RWORK_g.TimeStampA;
      real_T* lastU = &PID0_DW.Derivative_RWORK_g.LastUAtTimeA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastTime = &PID0_DW.Derivative_RWORK_g.TimeStampB;
          lastU = &PID0_DW.Derivative_RWORK_g.LastUAtTimeB;
        } else if (timeStampA >= timeStampB) {
          lastTime = &PID0_DW.Derivative_RWORK_g.TimeStampB;
          lastU = &PID0_DW.Derivative_RWORK_g.LastUAtTimeB;
        }
      }

      *lastTime = PID0_M->Timing.t[0];
      *lastU++ = PID0_B.Sum_a;
    }

    /* Update for Derivative: '<S2>/Derivative' */
    {
      real_T timeStampA = PID0_DW.Derivative_RWORK_h.TimeStampA;
      real_T timeStampB = PID0_DW.Derivative_RWORK_h.TimeStampB;
      real_T* lastTime = &PID0_DW.Derivative_RWORK_h.TimeStampA;
      real_T* lastU = &PID0_DW.Derivative_RWORK_h.LastUAtTimeA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastTime = &PID0_DW.Derivative_RWORK_h.TimeStampB;
          lastU = &PID0_DW.Derivative_RWORK_h.LastUAtTimeB;
        } else if (timeStampA >= timeStampB) {
          lastTime = &PID0_DW.Derivative_RWORK_h.TimeStampB;
          lastU = &PID0_DW.Derivative_RWORK_h.LastUAtTimeB;
        }
      }

      *lastTime = PID0_M->Timing.t[0];
      *lastU++ = PID0_B.Sum_b;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(PID0_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(PID0_M)!=-1) &&
          !((rtmGetTFinal(PID0_M)-(((PID0_M->Timing.clockTick1+
               PID0_M->Timing.clockTickH1* 4294967296.0)) * 0.001)) >
            (((PID0_M->Timing.clockTick1+PID0_M->Timing.clockTickH1*
               4294967296.0)) * 0.001) * (DBL_EPSILON))) {
        rtmSetErrorStatus(PID0_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&PID0_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++PID0_M->Timing.clockTick0)) {
      ++PID0_M->Timing.clockTickH0;
    }

    PID0_M->Timing.t[0] = rtsiGetSolverStopTime(&PID0_M->solverInfo);

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
      PID0_M->Timing.clockTick1++;
      if (!PID0_M->Timing.clockTick1) {
        PID0_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void PID0_derivatives(void)
{
  XDot_PID0_T *_rtXdot;
  _rtXdot = ((XDot_PID0_T *) PID0_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = PID0_B.Sum;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE_a = PID0_B.Sum_a;

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE_c = PID0_B.Sum_b;
}

/* Model initialize function */
void PID0_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)PID0_M, 0,
                sizeof(RT_MODEL_PID0_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PID0_M->solverInfo, &PID0_M->Timing.simTimeStep);
    rtsiSetTPtr(&PID0_M->solverInfo, &rtmGetTPtr(PID0_M));
    rtsiSetStepSizePtr(&PID0_M->solverInfo, &PID0_M->Timing.stepSize0);
    rtsiSetdXPtr(&PID0_M->solverInfo, &PID0_M->ModelData.derivs);
    rtsiSetContStatesPtr(&PID0_M->solverInfo, &PID0_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&PID0_M->solverInfo, &PID0_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&PID0_M->solverInfo, (&rtmGetErrorStatus(PID0_M)));
    rtsiSetRTModelPtr(&PID0_M->solverInfo, PID0_M);
  }

  rtsiSetSimTimeStep(&PID0_M->solverInfo, MAJOR_TIME_STEP);
  PID0_M->ModelData.intgData.y = PID0_M->ModelData.odeY;
  PID0_M->ModelData.intgData.f[0] = PID0_M->ModelData.odeF[0];
  PID0_M->ModelData.intgData.f[1] = PID0_M->ModelData.odeF[1];
  PID0_M->ModelData.intgData.f[2] = PID0_M->ModelData.odeF[2];
  PID0_M->ModelData.contStates = ((real_T *) &PID0_X);
  rtsiSetSolverData(&PID0_M->solverInfo, (void *)&PID0_M->ModelData.intgData);
  rtsiSetSolverName(&PID0_M->solverInfo,"ode3");
  rtmSetTPtr(PID0_M, &PID0_M->Timing.tArray[0]);
  rtmSetTFinal(PID0_M, 10.0);
  PID0_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    PID0_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(PID0_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(PID0_M->rtwLogInfo, (NULL));
    rtliSetLogT(PID0_M->rtwLogInfo, "tout");
    rtliSetLogX(PID0_M->rtwLogInfo, "");
    rtliSetLogXFinal(PID0_M->rtwLogInfo, "");
    rtliSetSigLog(PID0_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(PID0_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(PID0_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(PID0_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(PID0_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &PID0_Y.ctrl_pitch,
        &PID0_Y.ctrl_roll,
        &PID0_Y.ctrl_azimuth
      };

      rtliSetLogYSignalPtrs(PID0_M->rtwLogInfo, ((LogSignalPtrsType)
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
        "PID0/ctrl_pitch",
        "PID0/ctrl_roll",
        "PID0/ctrl_azimuth" };

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

      rtliSetLogYSignalInfo(PID0_M->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
      rt_LoggedCurrentSignalDimensions[2] = &rt_LoggedOutputWidths[2];
    }

    rtliSetLogY(PID0_M->rtwLogInfo, "yout");
  }

  /* block I/O */
  (void) memset(((void *) &PID0_B), 0,
                sizeof(B_PID0_T));

  /* states (continuous) */
  {
    (void) memset((void *)&PID0_X, 0,
                  sizeof(X_PID0_T));
  }

  /* states (dwork) */
  (void) memset((void *)&PID0_DW, 0,
                sizeof(DW_PID0_T));

  /* external inputs */
  (void) memset((void *)&PID0_U, 0,
                sizeof(ExtU_PID0_T));

  /* external outputs */
  (void) memset((void *)&PID0_Y, 0,
                sizeof(ExtY_PID0_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(PID0_M->rtwLogInfo, 0.0, rtmGetTFinal(PID0_M),
    PID0_M->Timing.stepSize0, (&rtmGetErrorStatus(PID0_M)));

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  PID0_X.Integrator_CSTATE = PID0_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S3>/Derivative' */
  PID0_DW.Derivative_RWORK.TimeStampA = rtInf;
  PID0_DW.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  PID0_X.Integrator_CSTATE_a = PID0_P.Integrator_IC_d;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  PID0_DW.Derivative_RWORK_g.TimeStampA = rtInf;
  PID0_DW.Derivative_RWORK_g.TimeStampB = rtInf;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  PID0_X.Integrator_CSTATE_c = PID0_P.Integrator_IC_m;

  /* InitializeConditions for Derivative: '<S2>/Derivative' */
  PID0_DW.Derivative_RWORK_h.TimeStampA = rtInf;
  PID0_DW.Derivative_RWORK_h.TimeStampB = rtInf;
}

/* Model terminate function */
void PID0_terminate(void)
{
  /* (no terminate code required) */
}
