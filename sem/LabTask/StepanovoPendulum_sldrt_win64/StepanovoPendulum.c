/*
 * StepanovoPendulum.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "StepanovoPendulum".
 *
 * Model version              : 9.8
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon May 18 14:08:00 2026
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "StepanovoPendulum.h"
#include "StepanovoPendulum_private.h"
#include "StepanovoPendulum_dt.h"

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
B_StepanovoPendulum_T StepanovoPendulum_B;

/* Continuous states */
X_StepanovoPendulum_T StepanovoPendulum_X;

/* Block states (default storage) */
DW_StepanovoPendulum_T StepanovoPendulum_DW;

/* Real-time model */
static RT_MODEL_StepanovoPendulum_T StepanovoPendulum_M_;
RT_MODEL_StepanovoPendulum_T *const StepanovoPendulum_M = &StepanovoPendulum_M_;
static void rate_monotonic_scheduler(void);

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                 /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;
  real_T* tBuf = uBuf + bufSz;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(StepanovoPendulum_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(StepanovoPendulum_M, 2);
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
  (StepanovoPendulum_M->Timing.TaskCounters.TID[2])++;
  if ((StepanovoPendulum_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    StepanovoPendulum_M->Timing.TaskCounters.TID[2] = 0;
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
  int_T nXc = 5;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  StepanovoPendulum_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  StepanovoPendulum_output0();
  StepanovoPendulum_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE5_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  StepanovoPendulum_output0();
  StepanovoPendulum_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE5_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  StepanovoPendulum_output0();
  StepanovoPendulum_derivatives();

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
  StepanovoPendulum_output0();
  StepanovoPendulum_derivatives();

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
  StepanovoPendulum_output0();
  StepanovoPendulum_derivatives();

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
void StepanovoPendulum_output0(void)   /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_TransportDelay;
  real_T rtb_EncoderInput[2];
  real_T tmp;
  if (rtmIsMajorTimeStep(StepanovoPendulum_M)) {
    /* set solver stop time */
    if (!(StepanovoPendulum_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&StepanovoPendulum_M->solverInfo,
                            ((StepanovoPendulum_M->Timing.clockTickH0 + 1) *
        StepanovoPendulum_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&StepanovoPendulum_M->solverInfo,
                            ((StepanovoPendulum_M->Timing.clockTick0 + 1) *
        StepanovoPendulum_M->Timing.stepSize0 +
        StepanovoPendulum_M->Timing.clockTickH0 *
        StepanovoPendulum_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(StepanovoPendulum_M)) {
    StepanovoPendulum_M->Timing.t[0] = rtsiGetT(&StepanovoPendulum_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(StepanovoPendulum_M)) {
    /* S-Function (sldrtei): '<S1>/Encoder Input' */
    /* S-Function Block: <S1>/Encoder Input */
    {
      ENCODERINPARM parm;
      parm.quad = (QUADMODE) 2;
      parm.index = (INDEXPULSE) 1;
      parm.infilter = StepanovoPendulum_P.EncoderInput_InputFilter;
      RTBIO_DriverIO(0, ENCODERINPUT, IOREAD, 2,
                     StepanovoPendulum_P.EncoderInput_Channels,
                     &rtb_EncoderInput[0], &parm);
    }

    /* Gain: '<S1>/Position.  conversion' */
    StepanovoPendulum_B.Positionconversion =
      StepanovoPendulum_P.Positionconversion_Gain * rtb_EncoderInput[0];
  }

  /* Step: '<Root>/Step2' */
  if (StepanovoPendulum_M->Timing.t[0] < StepanovoPendulum_P.Step2_Time) {
    /* Step: '<Root>/Step2' */
    StepanovoPendulum_B.Step2 = StepanovoPendulum_P.Step2_Y0;
  } else {
    /* Step: '<Root>/Step2' */
    StepanovoPendulum_B.Step2 = StepanovoPendulum_P.Step2_YFinal;
  }

  /* End of Step: '<Root>/Step2' */

  /* TransportDelay: '<Root>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &StepanovoPendulum_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T simTime = StepanovoPendulum_M->Timing.t[0];
    real_T tMinusDelay = simTime - StepanovoPendulum_P.t2;
    rtb_TransportDelay = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *uBuffer,
      StepanovoPendulum_DW.TransportDelay_IWORK.CircularBufSize,
      &StepanovoPendulum_DW.TransportDelay_IWORK.Last,
      StepanovoPendulum_DW.TransportDelay_IWORK.Tail,
      StepanovoPendulum_DW.TransportDelay_IWORK.Head,
      StepanovoPendulum_P.TransportDelay_InitOutput,
      0,
      0);
  }

  /* ManualSwitch: '<Root>/Manual Switch' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain2'
   *  Sum: '<Root>/Sum'
   */
  if (StepanovoPendulum_P.ManualSwitch_CurrentSetting == 1) {
    tmp = StepanovoPendulum_P.A1 * StepanovoPendulum_B.Step2 +
      StepanovoPendulum_P.A2 * rtb_TransportDelay;
  } else {
    tmp = StepanovoPendulum_B.Step2;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */

  /* Sum: '<Root>/Sum3' */
  StepanovoPendulum_B.Sum3 = tmp - StepanovoPendulum_B.Positionconversion;
  if (rtmIsMajorTimeStep(StepanovoPendulum_M)) {
    /* Gain: '<S1>/Angle conversion' */
    StepanovoPendulum_B.Angleconversion =
      StepanovoPendulum_P.Angleconversion_Gain * rtb_EncoderInput[1];

    /* Sum: '<Root>/Sum4' incorporates:
     *  Constant: '<Root>/Constant'
     */
    StepanovoPendulum_B.Sum4 = StepanovoPendulum_P.Constant_Value -
      StepanovoPendulum_B.Angleconversion;

    /* Gain: '<Root>/Gain4' */
    StepanovoPendulum_B.Gain4 = StepanovoPendulum_P.Gain4_Gain *
      StepanovoPendulum_B.Sum4;
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain3'
   *  Gain: '<Root>/Gain5'
   *  Gain: '<Root>/Gain6'
   *  Gain: '<Root>/Gain9'
   *  Integrator: '<Root>/Integrator'
   *  Integrator: '<Root>/Integrator1'
   *  Sum: '<Root>/Sum2'
   *  Sum: '<Root>/Sum6'
   *  TransferFcn: '<Root>/Transfer Fcn'
   *  TransferFcn: '<Root>/Transfer Fcn1'
   */
  StepanovoPendulum_B.Sum1 = ((StepanovoPendulum_P.TransferFcn_C *
    StepanovoPendulum_X.TransferFcn_CSTATE + StepanovoPendulum_P.TransferFcn_D *
    StepanovoPendulum_B.Sum3) * StepanovoPendulum_P.Gain9_Gain +
    (StepanovoPendulum_P.Gain3_Gain * StepanovoPendulum_X.Integrator_CSTATE +
     StepanovoPendulum_P.Gain_Gain * StepanovoPendulum_B.Sum3)) -
    ((StepanovoPendulum_P.TransferFcn1_C *
      StepanovoPendulum_X.TransferFcn1_CSTATE +
      StepanovoPendulum_P.TransferFcn1_D * StepanovoPendulum_B.Sum4) *
     StepanovoPendulum_P.Gain6_Gain + (StepanovoPendulum_P.Gain5_Gain *
      StepanovoPendulum_X.Integrator1_CSTATE + StepanovoPendulum_B.Gain4));

  /* TransferFcn: '<Root>/Rychlost' */
  StepanovoPendulum_B.Speed = 0.0;
  StepanovoPendulum_B.Speed += StepanovoPendulum_P.Rychlost_C *
    StepanovoPendulum_X.Rychlost_CSTATE;
  StepanovoPendulum_B.Speed += StepanovoPendulum_P.Rychlost_D *
    StepanovoPendulum_B.Positionconversion;
  if (rtmIsMajorTimeStep(StepanovoPendulum_M)) {
    /* S-Function (sldrtao): '<S1>/Analog Output' */
    /* S-Function Block: <S1>/Analog Output */
    {
      {
        ANALOGIOPARM parm;
        parm.mode = (RANGEMODE) StepanovoPendulum_P.AnalogOutput_RangeMode;
        parm.rangeidx = StepanovoPendulum_P.AnalogOutput_VoltRange;
        RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                       &StepanovoPendulum_P.AnalogOutput_Channels, ((real_T*)
          (&StepanovoPendulum_B.Sum1)), &parm);
      }
    }
  }
}

/* Model update function for TID0 */
void StepanovoPendulum_update0(void)   /* Sample time: [0.0s, 0.0s] */
{
  /* Update for TransportDelay: '<Root>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &StepanovoPendulum_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T simTime = StepanovoPendulum_M->Timing.t[0];
    StepanovoPendulum_DW.TransportDelay_IWORK.Head =
      ((StepanovoPendulum_DW.TransportDelay_IWORK.Head <
        (StepanovoPendulum_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
       (StepanovoPendulum_DW.TransportDelay_IWORK.Head+1) : 0);
    if (StepanovoPendulum_DW.TransportDelay_IWORK.Head ==
        StepanovoPendulum_DW.TransportDelay_IWORK.Tail) {
      StepanovoPendulum_DW.TransportDelay_IWORK.Tail =
        ((StepanovoPendulum_DW.TransportDelay_IWORK.Tail <
          (StepanovoPendulum_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (StepanovoPendulum_DW.TransportDelay_IWORK.Tail+1) : 0);
    }

    (*uBuffer + StepanovoPendulum_DW.TransportDelay_IWORK.CircularBufSize)
      [StepanovoPendulum_DW.TransportDelay_IWORK.Head] = simTime;
    (*uBuffer)[StepanovoPendulum_DW.TransportDelay_IWORK.Head] =
      StepanovoPendulum_B.Step2;
  }

  if (rtmIsMajorTimeStep(StepanovoPendulum_M)) {
    rt_ertODEUpdateContinuousStates(&StepanovoPendulum_M->solverInfo);
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
  if (!(++StepanovoPendulum_M->Timing.clockTick0)) {
    ++StepanovoPendulum_M->Timing.clockTickH0;
  }

  StepanovoPendulum_M->Timing.t[0] = rtsiGetSolverStopTime
    (&StepanovoPendulum_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++StepanovoPendulum_M->Timing.clockTick1)) {
    ++StepanovoPendulum_M->Timing.clockTickH1;
  }

  StepanovoPendulum_M->Timing.t[1] = StepanovoPendulum_M->Timing.clockTick1 *
    StepanovoPendulum_M->Timing.stepSize1 +
    StepanovoPendulum_M->Timing.clockTickH1 *
    StepanovoPendulum_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void StepanovoPendulum_derivatives(void)
{
  XDot_StepanovoPendulum_T *_rtXdot;
  _rtXdot = ((XDot_StepanovoPendulum_T *) StepanovoPendulum_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = StepanovoPendulum_B.Sum3;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += StepanovoPendulum_P.TransferFcn_A *
    StepanovoPendulum_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += StepanovoPendulum_B.Sum3;

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = StepanovoPendulum_B.Sum4;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = 0.0;
  _rtXdot->TransferFcn1_CSTATE += StepanovoPendulum_P.TransferFcn1_A *
    StepanovoPendulum_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += StepanovoPendulum_B.Sum4;

  /* Derivatives for TransferFcn: '<Root>/Rychlost' */
  _rtXdot->Rychlost_CSTATE = 0.0;
  _rtXdot->Rychlost_CSTATE += StepanovoPendulum_P.Rychlost_A *
    StepanovoPendulum_X.Rychlost_CSTATE;
  _rtXdot->Rychlost_CSTATE += StepanovoPendulum_B.Positionconversion;
}

/* Model output function for TID2 */
void StepanovoPendulum_output2(void)   /* Sample time: [0.005s, 0.0s] */
{
  /* local block i/o variables */
  boolean_T rtb_DigitalInput;

  /* S-Function (sldrtdi): '<S1>/Digital Input' */
  /* S-Function Block: <S1>/Digital Input */
  {
    double inval[1];
    double* invalp = inval;
    RTBIO_DriverIO(0, DIGITALINPUT, IOREAD, 1,
                   &StepanovoPendulum_P.DigitalInput_Channels, inval,
                   &StepanovoPendulum_P.DigitalInput_BitMode);
    rtb_DigitalInput = (boolean_T) *invalp++;
  }

  /* Stop: '<S1>/Stop Simulation' */
  if (rtb_DigitalInput) {
    rtmSetStopRequested(StepanovoPendulum_M, 1);
  }

  /* End of Stop: '<S1>/Stop Simulation' */
}

/* Model update function for TID2 */
void StepanovoPendulum_update2(void)   /* Sample time: [0.005s, 0.0s] */
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
  if (!(++StepanovoPendulum_M->Timing.clockTick2)) {
    ++StepanovoPendulum_M->Timing.clockTickH2;
  }

  StepanovoPendulum_M->Timing.t[2] = StepanovoPendulum_M->Timing.clockTick2 *
    StepanovoPendulum_M->Timing.stepSize2 +
    StepanovoPendulum_M->Timing.clockTickH2 *
    StepanovoPendulum_M->Timing.stepSize2 * 4294967296.0;
}

/* Model wrapper function for compatibility with a static main program */
void StepanovoPendulum_output(int_T tid)
{
  switch (tid) {
   case 0 :
    StepanovoPendulum_output0();
    break;

   case 2 :
    StepanovoPendulum_output2();
    break;

   default :
    break;
  }
}

/* Model wrapper function for compatibility with a static main program */
void StepanovoPendulum_update(int_T tid)
{
  switch (tid) {
   case 0 :
    StepanovoPendulum_update0();
    break;

   case 2 :
    StepanovoPendulum_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void StepanovoPendulum_initialize(void)
{
  /* Start for TransportDelay: '<Root>/Transport Delay' */
  {
    real_T *pBuffer = &StepanovoPendulum_DW.TransportDelay_RWORK.TUbufferArea[0];
    StepanovoPendulum_DW.TransportDelay_IWORK.Tail = 0;
    StepanovoPendulum_DW.TransportDelay_IWORK.Head = 0;
    StepanovoPendulum_DW.TransportDelay_IWORK.Last = 0;
    StepanovoPendulum_DW.TransportDelay_IWORK.CircularBufSize = 1024;
    pBuffer[0] = StepanovoPendulum_P.TransportDelay_InitOutput;
    pBuffer[1024] = StepanovoPendulum_M->Timing.t[0];
    StepanovoPendulum_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
  }

  /* Start for S-Function (sldrtao): '<S1>/Analog Output' */

  /* S-Function Block: <S1>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) StepanovoPendulum_P.AnalogOutput_RangeMode;
      parm.rangeidx = StepanovoPendulum_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &StepanovoPendulum_P.AnalogOutput_Channels,
                     &StepanovoPendulum_P.AnalogOutput_InitialValue, &parm);
    }
  }

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  StepanovoPendulum_X.Integrator_CSTATE = StepanovoPendulum_P.Integrator_IC;

  /* InitializeConditions for S-Function (sldrtei): '<S1>/Encoder Input' */

  /* S-Function Block: <S1>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 1;
    parm.infilter = StepanovoPendulum_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IORESET, 2,
                   StepanovoPendulum_P.EncoderInput_Channels, NULL, &parm);
  }

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  StepanovoPendulum_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  StepanovoPendulum_X.Integrator1_CSTATE = StepanovoPendulum_P.Integrator1_IC;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn1' */
  StepanovoPendulum_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Rychlost' */
  StepanovoPendulum_X.Rychlost_CSTATE = 0.0;
}

/* Model terminate function */
void StepanovoPendulum_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<S1>/Analog Output' */

  /* S-Function Block: <S1>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) StepanovoPendulum_P.AnalogOutput_RangeMode;
      parm.rangeidx = StepanovoPendulum_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &StepanovoPendulum_P.AnalogOutput_Channels,
                     &StepanovoPendulum_P.AnalogOutput_FinalValue, &parm);
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
  StepanovoPendulum_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  StepanovoPendulum_update(tid);
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
  StepanovoPendulum_initialize();
}

void MdlTerminate(void)
{
  StepanovoPendulum_terminate();
}

/* Registration function */
RT_MODEL_StepanovoPendulum_T *StepanovoPendulum(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  StepanovoPendulum_P.EncoderInput_InputFilter = rtInf;

  /* initialize real-time model */
  (void) memset((void *)StepanovoPendulum_M, 0,
                sizeof(RT_MODEL_StepanovoPendulum_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&StepanovoPendulum_M->solverInfo,
                          &StepanovoPendulum_M->Timing.simTimeStep);
    rtsiSetTPtr(&StepanovoPendulum_M->solverInfo, &rtmGetTPtr
                (StepanovoPendulum_M));
    rtsiSetStepSizePtr(&StepanovoPendulum_M->solverInfo,
                       &StepanovoPendulum_M->Timing.stepSize0);
    rtsiSetdXPtr(&StepanovoPendulum_M->solverInfo, &StepanovoPendulum_M->derivs);
    rtsiSetContStatesPtr(&StepanovoPendulum_M->solverInfo, (real_T **)
                         &StepanovoPendulum_M->contStates);
    rtsiSetNumContStatesPtr(&StepanovoPendulum_M->solverInfo,
      &StepanovoPendulum_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&StepanovoPendulum_M->solverInfo,
      &StepanovoPendulum_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&StepanovoPendulum_M->solverInfo,
      &StepanovoPendulum_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&StepanovoPendulum_M->solverInfo,
      &StepanovoPendulum_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&StepanovoPendulum_M->solverInfo, (&rtmGetErrorStatus
      (StepanovoPendulum_M)));
    rtsiSetRTModelPtr(&StepanovoPendulum_M->solverInfo, StepanovoPendulum_M);
  }

  rtsiSetSimTimeStep(&StepanovoPendulum_M->solverInfo, MAJOR_TIME_STEP);
  StepanovoPendulum_M->intgData.y = StepanovoPendulum_M->odeY;
  StepanovoPendulum_M->intgData.f[0] = StepanovoPendulum_M->odeF[0];
  StepanovoPendulum_M->intgData.f[1] = StepanovoPendulum_M->odeF[1];
  StepanovoPendulum_M->intgData.f[2] = StepanovoPendulum_M->odeF[2];
  StepanovoPendulum_M->intgData.f[3] = StepanovoPendulum_M->odeF[3];
  StepanovoPendulum_M->intgData.f[4] = StepanovoPendulum_M->odeF[4];
  StepanovoPendulum_M->intgData.f[5] = StepanovoPendulum_M->odeF[5];
  StepanovoPendulum_M->contStates = ((real_T *) &StepanovoPendulum_X);
  rtsiSetSolverData(&StepanovoPendulum_M->solverInfo, (void *)
                    &StepanovoPendulum_M->intgData);
  rtsiSetSolverName(&StepanovoPendulum_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = StepanovoPendulum_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    StepanovoPendulum_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    StepanovoPendulum_M->Timing.sampleTimes =
      (&StepanovoPendulum_M->Timing.sampleTimesArray[0]);
    StepanovoPendulum_M->Timing.offsetTimes =
      (&StepanovoPendulum_M->Timing.offsetTimesArray[0]);

    /* task periods */
    StepanovoPendulum_M->Timing.sampleTimes[0] = (0.0);
    StepanovoPendulum_M->Timing.sampleTimes[1] = (0.001);
    StepanovoPendulum_M->Timing.sampleTimes[2] = (0.005);

    /* task offsets */
    StepanovoPendulum_M->Timing.offsetTimes[0] = (0.0);
    StepanovoPendulum_M->Timing.offsetTimes[1] = (0.0);
    StepanovoPendulum_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(StepanovoPendulum_M, &StepanovoPendulum_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = StepanovoPendulum_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits =
      StepanovoPendulum_M->Timing.perTaskSampleHitsArray;
    StepanovoPendulum_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    StepanovoPendulum_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(StepanovoPendulum_M, 20.0);
  StepanovoPendulum_M->Timing.stepSize0 = 0.001;
  StepanovoPendulum_M->Timing.stepSize1 = 0.001;
  StepanovoPendulum_M->Timing.stepSize2 = 0.005;

  /* External mode info */
  StepanovoPendulum_M->Sizes.checksums[0] = (1474020641U);
  StepanovoPendulum_M->Sizes.checksums[1] = (2452536550U);
  StepanovoPendulum_M->Sizes.checksums[2] = (3920135429U);
  StepanovoPendulum_M->Sizes.checksums[3] = (2303527394U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    StepanovoPendulum_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(StepanovoPendulum_M->extModeInfo,
      &StepanovoPendulum_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(StepanovoPendulum_M->extModeInfo,
                        StepanovoPendulum_M->Sizes.checksums);
    rteiSetTPtr(StepanovoPendulum_M->extModeInfo, rtmGetTPtr(StepanovoPendulum_M));
  }

  StepanovoPendulum_M->solverInfoPtr = (&StepanovoPendulum_M->solverInfo);
  StepanovoPendulum_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&StepanovoPendulum_M->solverInfo, 0.001);
  rtsiSetSolverMode(&StepanovoPendulum_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  StepanovoPendulum_M->blockIO = ((void *) &StepanovoPendulum_B);

  {
    StepanovoPendulum_B.Positionconversion = 0.0;
    StepanovoPendulum_B.Step2 = 0.0;
    StepanovoPendulum_B.Sum3 = 0.0;
    StepanovoPendulum_B.Angleconversion = 0.0;
    StepanovoPendulum_B.Sum4 = 0.0;
    StepanovoPendulum_B.Gain4 = 0.0;
    StepanovoPendulum_B.Sum1 = 0.0;
    StepanovoPendulum_B.Speed = 0.0;
  }

  /* parameters */
  StepanovoPendulum_M->defaultParam = ((real_T *)&StepanovoPendulum_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &StepanovoPendulum_X;
    StepanovoPendulum_M->contStates = (x);
    (void) memset((void *)&StepanovoPendulum_X, 0,
                  sizeof(X_StepanovoPendulum_T));
  }

  /* states (dwork) */
  StepanovoPendulum_M->dwork = ((void *) &StepanovoPendulum_DW);
  (void) memset((void *)&StepanovoPendulum_DW, 0,
                sizeof(DW_StepanovoPendulum_T));
  StepanovoPendulum_DW.TransportDelay_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      StepanovoPendulum_DW.TransportDelay_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    StepanovoPendulum_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  StepanovoPendulum_M->Sizes.numContStates = (5);/* Number of continuous states */
  StepanovoPendulum_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  StepanovoPendulum_M->Sizes.numY = (0);/* Number of model outputs */
  StepanovoPendulum_M->Sizes.numU = (0);/* Number of model inputs */
  StepanovoPendulum_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  StepanovoPendulum_M->Sizes.numSampTimes = (3);/* Number of sample times */
  StepanovoPendulum_M->Sizes.numBlocks = (34);/* Number of blocks */
  StepanovoPendulum_M->Sizes.numBlockIO = (8);/* Number of block outputs */
  StepanovoPendulum_M->Sizes.numBlockPrms = (44);/* Sum of parameter "widths" */
  return StepanovoPendulum_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
