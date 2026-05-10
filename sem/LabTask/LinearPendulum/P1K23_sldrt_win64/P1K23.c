/*
 * P1K23.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "P1K23".
 *
 * Model version              : 9.3
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon May  4 12:39:39 2026
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "P1K23.h"
#include "P1K23_private.h"
#include "P1K23_dt.h"

/* options for Simulink Desktop Real-Time board 0 */
static double SLDRTBoardOptions0[] = {
  0.0,
};

/* list of Simulink Desktop Real-Time timers */
const int SLDRTTimerCount = 2;
const double SLDRTTimers[4] = {
  0.001, 0.0,
  0.005, 0.0,
};

/* list of Simulink Desktop Real-Time boards */
const int SLDRTBoardCount = 1;
SLDRTBOARD SLDRTBoards[1] = {
  { "Humusoft/MF624", 4294967295U, 1, SLDRTBoardOptions0 },
};

/* Block signals (default storage) */
B_P1K23_T P1K23_B;

/* Continuous states */
X_P1K23_T P1K23_X;

/* Block states (default storage) */
DW_P1K23_T P1K23_DW;

/* Real-time model */
static RT_MODEL_P1K23_T P1K23_M_;
RT_MODEL_P1K23_T *const P1K23_M = &P1K23_M_;
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(P1K23_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(P1K23_M, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (P1K23_M->Timing.TaskCounters.TID[2])++;
  if ((P1K23_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    P1K23_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE5_A[6] = {
    1.0/5.0, 3.0/10.0, 4.0/5.0, 8.0/9.0, 1.0, 1.0
  };

  static const real_T rt_ODE5_B[6][6] = {
    { 1.0/5.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

    { 3.0/40.0, 9.0/40.0, 0.0, 0.0, 0.0, 0.0 },

    { 44.0/45.0, -56.0/15.0, 32.0/9.0, 0.0, 0.0, 0.0 },

    { 19372.0/6561.0, -25360.0/2187.0, 64448.0/6561.0, -212.0/729.0, 0.0, 0.0 },

    { 9017.0/3168.0, -355.0/33.0, 46732.0/5247.0, 49.0/176.0, -5103.0/18656.0,
      0.0 },

    { 35.0/384.0, 0.0, 500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE5_IntgData *id = (ODE5_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T *f4 = id->f[4];
  real_T *f5 = id->f[5];
  real_T hB[6];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  P1K23_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  P1K23_output0();
  P1K23_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE5_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  P1K23_output0();
  P1K23_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE5_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  P1K23_output0();
  P1K23_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++) {
    hB[i] = h * rt_ODE5_B[3][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  P1K23_output0();
  P1K23_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++) {
    hB[i] = h * rt_ODE5_B[4][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  P1K23_output0();
  P1K23_derivatives();

  /* tnew = t + hA(6);
     ynew = y + f*hB(:,6); */
  for (i = 0; i <= 5; i++) {
    hB[i] = h * rt_ODE5_B[5][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4] + f5[i]*hB[5]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void P1K23_output0(void)               /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_EncoderInput[2];
  real_T rtb_Sum_h;
  real_T tmp;
  if (rtmIsMajorTimeStep(P1K23_M)) {
    /* set solver stop time */
    if (!(P1K23_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&P1K23_M->solverInfo, ((P1K23_M->Timing.clockTickH0
        + 1) * P1K23_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&P1K23_M->solverInfo, ((P1K23_M->Timing.clockTick0 +
        1) * P1K23_M->Timing.stepSize0 + P1K23_M->Timing.clockTickH0 *
        P1K23_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(P1K23_M)) {
    P1K23_M->Timing.t[0] = rtsiGetT(&P1K23_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(P1K23_M)) {
    /* S-Function (sldrtei): '<S3>/Encoder Input' */
    /* S-Function Block: <S3>/Encoder Input */
    {
      ENCODERINPARM parm;
      parm.quad = (QUADMODE) 2;
      parm.index = (INDEXPULSE) 1;
      parm.infilter = P1K23_P.EncoderInput_InputFilter;
      RTBIO_DriverIO(0, ENCODERINPUT, IOREAD, 2, P1K23_P.EncoderInput_Channels,
                     &rtb_EncoderInput[0], &parm);
    }

    /* Gain: '<S3>/Angle conversion' */
    P1K23_B.Angleconversion = P1K23_P.Angleconversion_Gain * rtb_EncoderInput[1];

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    rtb_Sum_h = P1K23_P.Constant1_Value - P1K23_B.Angleconversion;

    /* Gain: '<S90>/Proportional Gain' */
    P1K23_B.ProportionalGain = P1K23_P.PIDController1_P * rtb_Sum_h;

    /* Gain: '<S79>/Derivative Gain' */
    P1K23_B.DerivativeGain = P1K23_P.PIDController1_D * rtb_Sum_h;

    /* Gain: '<S3>/Position.  conversion' */
    P1K23_B.Positionconversion = P1K23_P.Positionconversion_Gain *
      rtb_EncoderInput[0];

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/Constant'
     */
    rtb_Sum_h = P1K23_P.Constant_Value - P1K23_B.Positionconversion;

    /* Gain: '<S42>/Proportional Gain' */
    P1K23_B.ProportionalGain_m = P1K23_P.PIDController_P * rtb_Sum_h;

    /* Gain: '<S31>/Derivative Gain' */
    P1K23_B.DerivativeGain_l = P1K23_P.PIDController_D * rtb_Sum_h;
  }

  /* Gain: '<S88>/Filter Coefficient' incorporates:
   *  Integrator: '<S80>/Filter'
   *  Sum: '<S80>/SumD'
   */
  P1K23_B.FilterCoefficient = (P1K23_B.DerivativeGain - P1K23_X.Filter_CSTATE) *
    P1K23_P.PIDController1_N;

  /* Gain: '<S40>/Filter Coefficient' incorporates:
   *  Integrator: '<S32>/Filter'
   *  Sum: '<S32>/SumD'
   */
  P1K23_B.FilterCoefficient_g = (P1K23_B.DerivativeGain_l -
    P1K23_X.Filter_CSTATE_n) * P1K23_P.PIDController_N;

  /* ManualSwitch: '<Root>/Manual Switch1' incorporates:
   *  ManualSwitch: '<Root>/Manual Switch'
   */
  if (P1K23_P.ManualSwitch1_CurrentSetting == 1) {
    /* Sum: '<Root>/Sum3' */
    P1K23_B.Sum3 = 0.0;
  } else {
    if (P1K23_P.ManualSwitch_CurrentSetting == 1) {
      /* ManualSwitch: '<Root>/Manual Switch' */
      tmp = 0.0;
    } else {
      /* ManualSwitch: '<Root>/Manual Switch' incorporates:
       *  Sum: '<S94>/Sum'
       */
      tmp = P1K23_B.ProportionalGain + P1K23_B.FilterCoefficient;
    }

    /* Sum: '<Root>/Sum3' incorporates:
     *  Integrator: '<S37>/Integrator'
     *  Sum: '<Root>/Sum2'
     *  Sum: '<S46>/Sum'
     */
    P1K23_B.Sum3 = ((P1K23_B.ProportionalGain_m + P1K23_X.Integrator_CSTATE) +
                    P1K23_B.FilterCoefficient_g) - tmp;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch1' */

  /* TransferFcn: '<Root>/Rychlost' */
  P1K23_B.Speed = 0.0;
  P1K23_B.Speed += P1K23_P.Rychlost_C * P1K23_X.Rychlost_CSTATE;
  P1K23_B.Speed += P1K23_P.Rychlost_D * P1K23_B.Positionconversion;
  if (rtmIsMajorTimeStep(P1K23_M)) {
    /* Gain: '<S34>/Integral Gain' */
    P1K23_B.IntegralGain = P1K23_P.PIDController_I * rtb_Sum_h;

    /* S-Function (sldrtao): '<S3>/Analog Output' */
    /* S-Function Block: <S3>/Analog Output */
    {
      {
        ANALOGIOPARM parm;
        parm.mode = (RANGEMODE) P1K23_P.AnalogOutput_RangeMode;
        parm.rangeidx = P1K23_P.AnalogOutput_VoltRange;
        RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                       &P1K23_P.AnalogOutput_Channels, ((real_T*) (&P1K23_B.Sum3)),
                       &parm);
      }
    }
  }
}

/* Model update function for TID0 */
void P1K23_update0(void)               /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(P1K23_M)) {
    rt_ertODEUpdateContinuousStates(&P1K23_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P1K23_M->Timing.clockTick0)) {
    ++P1K23_M->Timing.clockTickH0;
  }

  P1K23_M->Timing.t[0] = rtsiGetSolverStopTime(&P1K23_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P1K23_M->Timing.clockTick1)) {
    ++P1K23_M->Timing.clockTickH1;
  }

  P1K23_M->Timing.t[1] = P1K23_M->Timing.clockTick1 * P1K23_M->Timing.stepSize1
    + P1K23_M->Timing.clockTickH1 * P1K23_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void P1K23_derivatives(void)
{
  XDot_P1K23_T *_rtXdot;
  _rtXdot = ((XDot_P1K23_T *) P1K23_M->derivs);

  /* Derivatives for Integrator: '<S80>/Filter' */
  _rtXdot->Filter_CSTATE = P1K23_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S37>/Integrator' */
  _rtXdot->Integrator_CSTATE = P1K23_B.IntegralGain;

  /* Derivatives for Integrator: '<S32>/Filter' */
  _rtXdot->Filter_CSTATE_n = P1K23_B.FilterCoefficient_g;

  /* Derivatives for TransferFcn: '<Root>/Rychlost' */
  _rtXdot->Rychlost_CSTATE = 0.0;
  _rtXdot->Rychlost_CSTATE += P1K23_P.Rychlost_A * P1K23_X.Rychlost_CSTATE;
  _rtXdot->Rychlost_CSTATE += P1K23_B.Positionconversion;
}

/* Model output function for TID2 */
void P1K23_output2(void)               /* Sample time: [0.005s, 0.0s] */
{
  /* local block i/o variables */
  boolean_T rtb_DigitalInput;

  /* S-Function (sldrtdi): '<S3>/Digital Input' */
  /* S-Function Block: <S3>/Digital Input */
  {
    double inval[1];
    double* invalp = inval;
    RTBIO_DriverIO(0, DIGITALINPUT, IOREAD, 1, &P1K23_P.DigitalInput_Channels,
                   inval, &P1K23_P.DigitalInput_BitMode);
    rtb_DigitalInput = (boolean_T) *invalp++;
  }

  /* Stop: '<S3>/Stop Simulation' */
  if (rtb_DigitalInput) {
    rtmSetStopRequested(P1K23_M, 1);
  }

  /* End of Stop: '<S3>/Stop Simulation' */
}

/* Model update function for TID2 */
void P1K23_update2(void)               /* Sample time: [0.005s, 0.0s] */
{
  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P1K23_M->Timing.clockTick2)) {
    ++P1K23_M->Timing.clockTickH2;
  }

  P1K23_M->Timing.t[2] = P1K23_M->Timing.clockTick2 * P1K23_M->Timing.stepSize2
    + P1K23_M->Timing.clockTickH2 * P1K23_M->Timing.stepSize2 * 4294967296.0;
}

/* Model wrapper function for compatibility with a static main program */
void P1K23_output(int_T tid)
{
  switch (tid) {
   case 0 :
    P1K23_output0();
    break;

   case 2 :
    P1K23_output2();
    break;

   default :
    break;
  }
}

/* Model wrapper function for compatibility with a static main program */
void P1K23_update(int_T tid)
{
  switch (tid) {
   case 0 :
    P1K23_update0();
    break;

   case 2 :
    P1K23_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void P1K23_initialize(void)
{
  /* Start for S-Function (sldrtao): '<S3>/Analog Output' */

  /* S-Function Block: <S3>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) P1K23_P.AnalogOutput_RangeMode;
      parm.rangeidx = P1K23_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1, &P1K23_P.AnalogOutput_Channels,
                     &P1K23_P.AnalogOutput_InitialValue, &parm);
    }
  }

  /* InitializeConditions for S-Function (sldrtei): '<S3>/Encoder Input' */

  /* S-Function Block: <S3>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 1;
    parm.infilter = P1K23_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IORESET, 2, P1K23_P.EncoderInput_Channels,
                   NULL, &parm);
  }

  /* InitializeConditions for Integrator: '<S80>/Filter' */
  P1K23_X.Filter_CSTATE = P1K23_P.PIDController1_InitialConditionForFilter;

  /* InitializeConditions for Integrator: '<S37>/Integrator' */
  P1K23_X.Integrator_CSTATE =
    P1K23_P.PIDController_InitialConditionForIntegrator;

  /* InitializeConditions for Integrator: '<S32>/Filter' */
  P1K23_X.Filter_CSTATE_n = P1K23_P.PIDController_InitialConditionForFilter;

  /* InitializeConditions for TransferFcn: '<Root>/Rychlost' */
  P1K23_X.Rychlost_CSTATE = 0.0;
}

/* Model terminate function */
void P1K23_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<S3>/Analog Output' */

  /* S-Function Block: <S3>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) P1K23_P.AnalogOutput_RangeMode;
      parm.rangeidx = P1K23_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1, &P1K23_P.AnalogOutput_Channels,
                     &P1K23_P.AnalogOutput_FinalValue, &parm);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  if (tid == 1)
    tid = 0;
  P1K23_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  P1K23_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  P1K23_initialize();
}

void MdlTerminate(void)
{
  P1K23_terminate();
}

/* Registration function */
RT_MODEL_P1K23_T *P1K23(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  P1K23_P.EncoderInput_InputFilter = rtInf;

  /* initialize real-time model */
  (void) memset((void *)P1K23_M, 0,
                sizeof(RT_MODEL_P1K23_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&P1K23_M->solverInfo, &P1K23_M->Timing.simTimeStep);
    rtsiSetTPtr(&P1K23_M->solverInfo, &rtmGetTPtr(P1K23_M));
    rtsiSetStepSizePtr(&P1K23_M->solverInfo, &P1K23_M->Timing.stepSize0);
    rtsiSetdXPtr(&P1K23_M->solverInfo, &P1K23_M->derivs);
    rtsiSetContStatesPtr(&P1K23_M->solverInfo, (real_T **) &P1K23_M->contStates);
    rtsiSetNumContStatesPtr(&P1K23_M->solverInfo, &P1K23_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&P1K23_M->solverInfo,
      &P1K23_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&P1K23_M->solverInfo,
      &P1K23_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&P1K23_M->solverInfo,
      &P1K23_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&P1K23_M->solverInfo, (&rtmGetErrorStatus(P1K23_M)));
    rtsiSetRTModelPtr(&P1K23_M->solverInfo, P1K23_M);
  }

  rtsiSetSimTimeStep(&P1K23_M->solverInfo, MAJOR_TIME_STEP);
  P1K23_M->intgData.y = P1K23_M->odeY;
  P1K23_M->intgData.f[0] = P1K23_M->odeF[0];
  P1K23_M->intgData.f[1] = P1K23_M->odeF[1];
  P1K23_M->intgData.f[2] = P1K23_M->odeF[2];
  P1K23_M->intgData.f[3] = P1K23_M->odeF[3];
  P1K23_M->intgData.f[4] = P1K23_M->odeF[4];
  P1K23_M->intgData.f[5] = P1K23_M->odeF[5];
  P1K23_M->contStates = ((real_T *) &P1K23_X);
  rtsiSetSolverData(&P1K23_M->solverInfo, (void *)&P1K23_M->intgData);
  rtsiSetSolverName(&P1K23_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = P1K23_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    P1K23_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    P1K23_M->Timing.sampleTimes = (&P1K23_M->Timing.sampleTimesArray[0]);
    P1K23_M->Timing.offsetTimes = (&P1K23_M->Timing.offsetTimesArray[0]);

    /* task periods */
    P1K23_M->Timing.sampleTimes[0] = (0.0);
    P1K23_M->Timing.sampleTimes[1] = (0.001);
    P1K23_M->Timing.sampleTimes[2] = (0.005);

    /* task offsets */
    P1K23_M->Timing.offsetTimes[0] = (0.0);
    P1K23_M->Timing.offsetTimes[1] = (0.0);
    P1K23_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(P1K23_M, &P1K23_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = P1K23_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = P1K23_M->Timing.perTaskSampleHitsArray;
    P1K23_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    P1K23_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(P1K23_M, 18.0);
  P1K23_M->Timing.stepSize0 = 0.001;
  P1K23_M->Timing.stepSize1 = 0.001;
  P1K23_M->Timing.stepSize2 = 0.005;

  /* External mode info */
  P1K23_M->Sizes.checksums[0] = (690020118U);
  P1K23_M->Sizes.checksums[1] = (3038441451U);
  P1K23_M->Sizes.checksums[2] = (2516309144U);
  P1K23_M->Sizes.checksums[3] = (477416451U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    P1K23_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(P1K23_M->extModeInfo,
      &P1K23_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(P1K23_M->extModeInfo, P1K23_M->Sizes.checksums);
    rteiSetTPtr(P1K23_M->extModeInfo, rtmGetTPtr(P1K23_M));
  }

  P1K23_M->solverInfoPtr = (&P1K23_M->solverInfo);
  P1K23_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&P1K23_M->solverInfo, 0.001);
  rtsiSetSolverMode(&P1K23_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  P1K23_M->blockIO = ((void *) &P1K23_B);

  {
    P1K23_B.Angleconversion = 0.0;
    P1K23_B.ProportionalGain = 0.0;
    P1K23_B.DerivativeGain = 0.0;
    P1K23_B.FilterCoefficient = 0.0;
    P1K23_B.Positionconversion = 0.0;
    P1K23_B.ProportionalGain_m = 0.0;
    P1K23_B.DerivativeGain_l = 0.0;
    P1K23_B.FilterCoefficient_g = 0.0;
    P1K23_B.Sum3 = 0.0;
    P1K23_B.Speed = 0.0;
    P1K23_B.IntegralGain = 0.0;
  }

  /* parameters */
  P1K23_M->defaultParam = ((real_T *)&P1K23_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &P1K23_X;
    P1K23_M->contStates = (x);
    (void) memset((void *)&P1K23_X, 0,
                  sizeof(X_P1K23_T));
  }

  /* states (dwork) */
  P1K23_M->dwork = ((void *) &P1K23_DW);
  (void) memset((void *)&P1K23_DW, 0,
                sizeof(DW_P1K23_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    P1K23_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  P1K23_M->Sizes.numContStates = (4);  /* Number of continuous states */
  P1K23_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  P1K23_M->Sizes.numY = (0);           /* Number of model outputs */
  P1K23_M->Sizes.numU = (0);           /* Number of model inputs */
  P1K23_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  P1K23_M->Sizes.numSampTimes = (3);   /* Number of sample times */
  P1K23_M->Sizes.numBlocks = (35);     /* Number of blocks */
  P1K23_M->Sizes.numBlockIO = (11);    /* Number of block outputs */
  P1K23_M->Sizes.numBlockPrms = (35);  /* Sum of parameter "widths" */
  return P1K23_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
