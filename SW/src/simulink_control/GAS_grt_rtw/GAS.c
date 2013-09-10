/*
 * GAS.c
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
#include "GAS.h"
#include "GAS_private.h"

/* External inputs (root inport signals with auto storage) */
ExtU_GAS_T GAS_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_GAS_T GAS_Y;

/* Real-time model */
RT_MODEL_GAS_T GAS_M_;
RT_MODEL_GAS_T *const GAS_M = &GAS_M_;

/* Model step function */
void GAS_step(void)
{
  /* Outport: '<Root>/out_e1' incorporates:
   *  Constant: '<S2>/weight_azimuth_e1'
   *  Constant: '<S2>/weight_pitch_e1'
   *  Constant: '<S2>/weight_roll_e1'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Inport: '<Root>/ctrl_throttle'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Product: '<S2>/Product2'
   *  Sum: '<S2>/Sum'
   */
  GAS_Y.out_e1 = ((GAS_U.ctrl_pitch * GAS_P.weight_pitch_e1_Value +
                   GAS_U.ctrl_roll * GAS_P.weight_roll_e1_Value) +
                  GAS_U.ctrl_azimuth * GAS_P.weight_azimuth_e1_Value) +
    GAS_U.ctrl_throttle;

  /* Outport: '<Root>/out_e2' incorporates:
   *  Constant: '<S3>/weight_azimuth_e2'
   *  Constant: '<S3>/weight_pitch_e2'
   *  Constant: '<S3>/weight_roll_e2'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product2'
   *  Sum: '<S3>/Sum'
   */
  GAS_Y.out_e2 = ((GAS_U.ctrl_pitch * GAS_P.weight_pitch_e2_Value +
                   GAS_U.ctrl_roll * GAS_P.weight_roll_e2_Value) +
                  GAS_U.ctrl_azimuth * GAS_P.weight_azimuth_e2_Value) + 0.0;

  /* Outport: '<Root>/out_e3' incorporates:
   *  Constant: '<S4>/weight_azimuth_e3'
   *  Constant: '<S4>/weight_pitch_e3'
   *  Constant: '<S4>/weight_roll_e3'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product2'
   *  Sum: '<S4>/Sum'
   */
  GAS_Y.out_e3 = ((GAS_U.ctrl_pitch * GAS_P.weight_pitch_e3_Value +
                   GAS_U.ctrl_roll * GAS_P.weight_roll_e3_Value) +
                  GAS_U.ctrl_azimuth * GAS_P.weight_azimuth_e3_Value) + 0.0;

  /* Outport: '<Root>/out_e4' incorporates:
   *  Constant: '<S5>/weight_azimuth_e4'
   *  Constant: '<S5>/weight_pitch_e4'
   *  Constant: '<S5>/weight_roll_e4'
   *  Inport: '<Root>/ctrl_azimuth'
   *  Inport: '<Root>/ctrl_pitch'
   *  Inport: '<Root>/ctrl_roll'
   *  Product: '<S5>/Product'
   *  Product: '<S5>/Product1'
   *  Product: '<S5>/Product2'
   *  Sum: '<S5>/Sum'
   */
  GAS_Y.out_e4 = ((GAS_U.ctrl_pitch * GAS_P.weight_pitch_e4_Value +
                   GAS_U.ctrl_roll * GAS_P.weight_roll_e4_Value) +
                  GAS_U.ctrl_azimuth * GAS_P.weight_azimuth_e4_Value) + 0.0;

  /* Matfile logging */
  rt_UpdateTXYLogVars(GAS_M->rtwLogInfo, (&GAS_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(GAS_M)!=-1) &&
        !((rtmGetTFinal(GAS_M)-GAS_M->Timing.taskTime0) >
          GAS_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(GAS_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++GAS_M->Timing.clockTick0)) {
    ++GAS_M->Timing.clockTickH0;
  }

  GAS_M->Timing.taskTime0 = GAS_M->Timing.clockTick0 * GAS_M->Timing.stepSize0 +
    GAS_M->Timing.clockTickH0 * GAS_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void GAS_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)GAS_M, 0,
                sizeof(RT_MODEL_GAS_T));
  rtmSetTFinal(GAS_M, 10.0);
  GAS_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    GAS_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(GAS_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(GAS_M->rtwLogInfo, (NULL));
    rtliSetLogT(GAS_M->rtwLogInfo, "tout");
    rtliSetLogX(GAS_M->rtwLogInfo, "");
    rtliSetLogXFinal(GAS_M->rtwLogInfo, "");
    rtliSetSigLog(GAS_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(GAS_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(GAS_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(GAS_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(GAS_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &GAS_Y.out_e1,
        &GAS_Y.out_e2,
        &GAS_Y.out_e3,
        &GAS_Y.out_e4
      };

      rtliSetLogYSignalPtrs(GAS_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        1,
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1,
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        1,
        1,
        1,
        1
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0,
        0,
        0,
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL),
        (NULL),
        (NULL),
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4,
        4,
        4,
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0,
        0,
        0,
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "",
        "",
        "",
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "GAS/out_e1",
        "GAS/out_e2",
        "GAS/out_e3",
        "GAS/out_e4" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          4,
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

      rtliSetLogYSignalInfo(GAS_M->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
      rt_LoggedCurrentSignalDimensions[2] = &rt_LoggedOutputWidths[2];
      rt_LoggedCurrentSignalDimensions[3] = &rt_LoggedOutputWidths[3];
    }

    rtliSetLogY(GAS_M->rtwLogInfo, "yout");
  }

  /* external inputs */
  (void) memset((void *)&GAS_U, 0,
                sizeof(ExtU_GAS_T));

  /* external outputs */
  (void) memset((void *)&GAS_Y, 0,
                sizeof(ExtY_GAS_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(GAS_M->rtwLogInfo, 0.0, rtmGetTFinal(GAS_M),
    GAS_M->Timing.stepSize0, (&rtmGetErrorStatus(GAS_M)));
}

/* Model terminate function */
void GAS_terminate(void)
{
  /* (no terminate code required) */
}
