/*
 * pid_pos.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "pid_pos".
 *
 * Model version              : 9.6
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu May 21 12:50:19 2026
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pid_pos.h"
#include "pid_pos_private.h"
#include "pid_pos_dt.h"

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
B_pid_pos_T pid_pos_B;

/* Continuous states */
X_pid_pos_T pid_pos_X;

/* Block states (default storage) */
DW_pid_pos_T pid_pos_DW;

/* Real-time model */
static RT_MODEL_pid_pos_T pid_pos_M_;
RT_MODEL_pid_pos_T *const pid_pos_M = &pid_pos_M_;
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
  rtmSampleHitPtr[1] = rtmStepTask(pid_pos_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(pid_pos_M, 2);
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
  (pid_pos_M->Timing.TaskCounters.TID[2])++;
  if ((pid_pos_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    pid_pos_M->Timing.TaskCounters.TID[2] = 0;
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
  pid_pos_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  pid_pos_output0();
  pid_pos_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE5_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  pid_pos_output0();
  pid_pos_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE5_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  pid_pos_output0();
  pid_pos_derivatives();

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
  pid_pos_output0();
  pid_pos_derivatives();

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
  pid_pos_output0();
  pid_pos_derivatives();

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
void pid_pos_output0(void)             /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_TransportDelay;
  real_T rtb_EncoderInput[2];
  real_T rtb_IntegralGain;
  real_T rtb_SignPreSat;
  real_T rtb_Sum2;
  real_T u0;
  if (rtmIsMajorTimeStep(pid_pos_M)) {
    /* set solver stop time */
    if (!(pid_pos_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&pid_pos_M->solverInfo,
                            ((pid_pos_M->Timing.clockTickH0 + 1) *
        pid_pos_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&pid_pos_M->solverInfo,
                            ((pid_pos_M->Timing.clockTick0 + 1) *
        pid_pos_M->Timing.stepSize0 + pid_pos_M->Timing.clockTickH0 *
        pid_pos_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(pid_pos_M)) {
    pid_pos_M->Timing.t[0] = rtsiGetT(&pid_pos_M->solverInfo);
  }

  /* Step: '<Root>/Step3' */
  if (pid_pos_M->Timing.t[0] < pid_pos_P.Step3_Time) {
    /* Step: '<Root>/Step3' */
    pid_pos_B.Step3 = pid_pos_P.Step3_Y0;
  } else {
    /* Step: '<Root>/Step3' */
    pid_pos_B.Step3 = pid_pos_P.Step3_YFinal;
  }

  /* End of Step: '<Root>/Step3' */

  /* TransportDelay: '<Root>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)&pid_pos_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T simTime = pid_pos_M->Timing.t[0];
    real_T tMinusDelay = simTime - pid_pos_P.TransportDelay_Delay;
    rtb_TransportDelay = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *uBuffer,
      pid_pos_DW.TransportDelay_IWORK.CircularBufSize,
      &pid_pos_DW.TransportDelay_IWORK.Last,
      pid_pos_DW.TransportDelay_IWORK.Tail,
      pid_pos_DW.TransportDelay_IWORK.Head,
      pid_pos_P.TransportDelay_InitOutput,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(pid_pos_M)) {
    /* S-Function (sldrtei): '<S3>/Encoder Input' */
    /* S-Function Block: <S3>/Encoder Input */
    {
      ENCODERINPARM parm;
      parm.quad = (QUADMODE) 2;
      parm.index = (INDEXPULSE) 1;
      parm.infilter = pid_pos_P.EncoderInput_InputFilter;
      RTBIO_DriverIO(0, ENCODERINPUT, IOREAD, 2, pid_pos_P.EncoderInput_Channels,
                     &rtb_EncoderInput[0], &parm);
    }

    /* Gain: '<S3>/Angle conversion' */
    pid_pos_B.Angleconversion = pid_pos_P.Angleconversion_Gain *
      rtb_EncoderInput[1];

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    rtb_IntegralGain = pid_pos_P.Constant1_Value_k - pid_pos_B.Angleconversion;

    /* Gain: '<S92>/Proportional Gain' */
    pid_pos_B.ProportionalGain = pid_pos_P.PIDController1_P * rtb_IntegralGain;

    /* Gain: '<S81>/Derivative Gain' */
    pid_pos_B.DerivativeGain = pid_pos_P.Kd_phi * rtb_IntegralGain;

    /* Gain: '<S3>/Position.  conversion' */
    pid_pos_B.Positionconversion = pid_pos_P.Positionconversion_Gain *
      rtb_EncoderInput[0];

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/Constant'
     */
    rtb_IntegralGain = pid_pos_P.Constant_Value - pid_pos_B.Positionconversion;

    /* Gain: '<S44>/Proportional Gain' */
    pid_pos_B.ProportionalGain_m = pid_pos_P.Kp * rtb_IntegralGain;

    /* Gain: '<S33>/Derivative Gain' */
    pid_pos_B.DerivativeGain_l = pid_pos_P.Kd * rtb_IntegralGain;
  }

  /* Gain: '<S90>/Filter Coefficient' incorporates:
   *  Integrator: '<S82>/Filter'
   *  Sum: '<S82>/SumD'
   */
  pid_pos_B.FilterCoefficient = (pid_pos_B.DerivativeGain -
    pid_pos_X.Filter_CSTATE) * pid_pos_P.PIDController1_N;

  /* Gain: '<S42>/Filter Coefficient' incorporates:
   *  Integrator: '<S34>/Filter'
   *  Sum: '<S34>/SumD'
   */
  pid_pos_B.FilterCoefficient_g = (pid_pos_B.DerivativeGain_l -
    pid_pos_X.Filter_CSTATE_n) * pid_pos_P.PIDController_N;

  /* Sum: '<S48>/Sum' incorporates:
   *  Integrator: '<S39>/Integrator'
   */
  rtb_SignPreSat = (pid_pos_B.ProportionalGain_m + pid_pos_X.Integrator_CSTATE)
    + pid_pos_B.FilterCoefficient_g;

  /* ManualSwitch: '<Root>/Manual Switch1' incorporates:
   *  Saturate: '<S46>/Saturation'
   */
  if (pid_pos_P.ManualSwitch1_CurrentSetting == 1) {
    /* Sum: '<Root>/Sum3' incorporates:
     *  Sum: '<Root>/Sum5'
     */
    pid_pos_B.MotorVoltage = pid_pos_B.Step3 - rtb_TransportDelay;
  } else {
    if (rtb_SignPreSat > pid_pos_P.PIDController_UpperSaturationLimit) {
      /* Saturate: '<S46>/Saturation' */
      rtb_Sum2 = pid_pos_P.PIDController_UpperSaturationLimit;
    } else if (rtb_SignPreSat < pid_pos_P.PIDController_LowerSaturationLimit) {
      /* Saturate: '<S46>/Saturation' */
      rtb_Sum2 = pid_pos_P.PIDController_LowerSaturationLimit;
    } else {
      /* Saturate: '<S46>/Saturation' */
      rtb_Sum2 = rtb_SignPreSat;
    }

    /* ManualSwitch: '<Root>/Manual Switch' incorporates:
     *  Saturate: '<S46>/Saturation'
     *  Sum: '<S96>/Sum'
     */
    if (pid_pos_P.ManualSwitch_CurrentSetting == 1) {
      u0 = 0.0;
    } else {
      u0 = pid_pos_B.ProportionalGain + pid_pos_B.FilterCoefficient;
    }

    /* End of ManualSwitch: '<Root>/Manual Switch' */

    /* Sum: '<Root>/Sum2' */
    u0 = rtb_Sum2 - u0;

    /* Saturate: '<Root>/Saturation' */
    if (u0 > pid_pos_P.Saturation_UpperSat) {
      /* Sum: '<Root>/Sum3' */
      pid_pos_B.MotorVoltage = pid_pos_P.Saturation_UpperSat;
    } else if (u0 < pid_pos_P.Saturation_LowerSat) {
      /* Sum: '<Root>/Sum3' */
      pid_pos_B.MotorVoltage = pid_pos_P.Saturation_LowerSat;
    } else {
      /* Sum: '<Root>/Sum3' */
      pid_pos_B.MotorVoltage = u0;
    }

    /* End of Saturate: '<Root>/Saturation' */
  }

  /* End of ManualSwitch: '<Root>/Manual Switch1' */

  /* TransferFcn: '<Root>/Rychlost' */
  pid_pos_B.Speed = 0.0;
  pid_pos_B.Speed += pid_pos_P.Rychlost_C * pid_pos_X.Rychlost_CSTATE;
  pid_pos_B.Speed += pid_pos_P.Rychlost_D * pid_pos_B.Positionconversion;
  if (rtmIsMajorTimeStep(pid_pos_M)) {
  }

  /* Gain: '<S30>/ZeroGain' */
  rtb_Sum2 = pid_pos_P.ZeroGain_Gain * rtb_SignPreSat;

  /* DeadZone: '<S32>/DeadZone' */
  if (rtb_SignPreSat > pid_pos_P.PIDController_UpperSaturationLimit) {
    rtb_SignPreSat -= pid_pos_P.PIDController_UpperSaturationLimit;
  } else if (rtb_SignPreSat >= pid_pos_P.PIDController_LowerSaturationLimit) {
    rtb_SignPreSat = 0.0;
  } else {
    rtb_SignPreSat -= pid_pos_P.PIDController_LowerSaturationLimit;
  }

  /* End of DeadZone: '<S32>/DeadZone' */
  if (rtmIsMajorTimeStep(pid_pos_M)) {
    /* Gain: '<S36>/Integral Gain' */
    rtb_IntegralGain *= pid_pos_P.Ki;

    /* Signum: '<S30>/SignPreIntegrator' */
    if (rtb_IntegralGain < 0.0) {
      /* DataTypeConversion: '<S30>/DataTypeConv2' */
      u0 = -1.0;
    } else if (rtb_IntegralGain > 0.0) {
      /* DataTypeConversion: '<S30>/DataTypeConv2' */
      u0 = 1.0;
    } else if (rtb_IntegralGain == 0.0) {
      /* DataTypeConversion: '<S30>/DataTypeConv2' */
      u0 = 0.0;
    } else {
      /* DataTypeConversion: '<S30>/DataTypeConv2' */
      u0 = (rtNaN);
    }

    /* End of Signum: '<S30>/SignPreIntegrator' */

    /* DataTypeConversion: '<S30>/DataTypeConv2' */
    if (rtIsNaN(u0)) {
      u0 = 0.0;
    } else {
      u0 = fmod(u0, 256.0);
    }

    /* DataTypeConversion: '<S30>/DataTypeConv2' */
    pid_pos_B.DataTypeConv2 = (int8_T)(u0 < 0.0 ? (int32_T)(int8_T)-(int8_T)
      (uint8_T)-u0 : (int32_T)(int8_T)(uint8_T)u0);
  }

  /* Signum: '<S30>/SignPreSat' */
  if (rtb_SignPreSat < 0.0) {
    /* DataTypeConversion: '<S30>/DataTypeConv1' */
    u0 = -1.0;
  } else if (rtb_SignPreSat > 0.0) {
    /* DataTypeConversion: '<S30>/DataTypeConv1' */
    u0 = 1.0;
  } else if (rtb_SignPreSat == 0.0) {
    /* DataTypeConversion: '<S30>/DataTypeConv1' */
    u0 = 0.0;
  } else {
    /* DataTypeConversion: '<S30>/DataTypeConv1' */
    u0 = (rtNaN);
  }

  /* End of Signum: '<S30>/SignPreSat' */

  /* DataTypeConversion: '<S30>/DataTypeConv1' */
  if (rtIsNaN(u0)) {
    u0 = 0.0;
  } else {
    u0 = fmod(u0, 256.0);
  }

  /* Logic: '<S30>/AND3' incorporates:
   *  DataTypeConversion: '<S30>/DataTypeConv1'
   *  RelationalOperator: '<S30>/Equal1'
   *  RelationalOperator: '<S30>/NotEqual'
   */
  pid_pos_B.AND3 = ((rtb_Sum2 != rtb_SignPreSat) && ((u0 < 0.0 ? (int32_T)
    (int8_T)-(int8_T)(uint8_T)-u0 : (int32_T)(int8_T)(uint8_T)u0) ==
    pid_pos_B.DataTypeConv2));
  if (rtmIsMajorTimeStep(pid_pos_M)) {
    /* Switch: '<S30>/Switch' incorporates:
     *  Memory: '<S30>/Memory'
     */
    if (pid_pos_DW.Memory_PreviousInput) {
      /* Switch: '<S30>/Switch' incorporates:
       *  Constant: '<S30>/Constant1'
       */
      pid_pos_B.Switch = pid_pos_P.Constant1_Value;
    } else {
      /* Switch: '<S30>/Switch' */
      pid_pos_B.Switch = rtb_IntegralGain;
    }

    /* End of Switch: '<S30>/Switch' */

    /* S-Function (sldrtao): '<S3>/Analog Output' */
    /* S-Function Block: <S3>/Analog Output */
    {
      {
        ANALOGIOPARM parm;
        parm.mode = (RANGEMODE) pid_pos_P.AnalogOutput_RangeMode;
        parm.rangeidx = pid_pos_P.AnalogOutput_VoltRange;
        RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                       &pid_pos_P.AnalogOutput_Channels, ((real_T*)
          (&pid_pos_B.MotorVoltage)), &parm);
      }
    }
  }
}

/* Model update function for TID0 */
void pid_pos_update0(void)             /* Sample time: [0.0s, 0.0s] */
{
  /* Update for TransportDelay: '<Root>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)&pid_pos_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T simTime = pid_pos_M->Timing.t[0];
    pid_pos_DW.TransportDelay_IWORK.Head =
      ((pid_pos_DW.TransportDelay_IWORK.Head <
        (pid_pos_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
       (pid_pos_DW.TransportDelay_IWORK.Head+1) : 0);
    if (pid_pos_DW.TransportDelay_IWORK.Head ==
        pid_pos_DW.TransportDelay_IWORK.Tail) {
      pid_pos_DW.TransportDelay_IWORK.Tail =
        ((pid_pos_DW.TransportDelay_IWORK.Tail <
          (pid_pos_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (pid_pos_DW.TransportDelay_IWORK.Tail+1) : 0);
    }

    (*uBuffer + pid_pos_DW.TransportDelay_IWORK.CircularBufSize)
      [pid_pos_DW.TransportDelay_IWORK.Head] = simTime;
    (*uBuffer)[pid_pos_DW.TransportDelay_IWORK.Head] = pid_pos_B.Step3;
  }

  if (rtmIsMajorTimeStep(pid_pos_M)) {
    /* Update for Memory: '<S30>/Memory' */
    pid_pos_DW.Memory_PreviousInput = pid_pos_B.AND3;
  }

  if (rtmIsMajorTimeStep(pid_pos_M)) {
    rt_ertODEUpdateContinuousStates(&pid_pos_M->solverInfo);
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
  if (!(++pid_pos_M->Timing.clockTick0)) {
    ++pid_pos_M->Timing.clockTickH0;
  }

  pid_pos_M->Timing.t[0] = rtsiGetSolverStopTime(&pid_pos_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++pid_pos_M->Timing.clockTick1)) {
    ++pid_pos_M->Timing.clockTickH1;
  }

  pid_pos_M->Timing.t[1] = pid_pos_M->Timing.clockTick1 *
    pid_pos_M->Timing.stepSize1 + pid_pos_M->Timing.clockTickH1 *
    pid_pos_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void pid_pos_derivatives(void)
{
  XDot_pid_pos_T *_rtXdot;
  _rtXdot = ((XDot_pid_pos_T *) pid_pos_M->derivs);

  /* Derivatives for Integrator: '<S82>/Filter' */
  _rtXdot->Filter_CSTATE = pid_pos_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S39>/Integrator' */
  _rtXdot->Integrator_CSTATE = pid_pos_B.Switch;

  /* Derivatives for Integrator: '<S34>/Filter' */
  _rtXdot->Filter_CSTATE_n = pid_pos_B.FilterCoefficient_g;

  /* Derivatives for TransferFcn: '<Root>/Rychlost' */
  _rtXdot->Rychlost_CSTATE = 0.0;
  _rtXdot->Rychlost_CSTATE += pid_pos_P.Rychlost_A * pid_pos_X.Rychlost_CSTATE;
  _rtXdot->Rychlost_CSTATE += pid_pos_B.Positionconversion;
}

/* Model output function for TID2 */
void pid_pos_output2(void)             /* Sample time: [0.005s, 0.0s] */
{
  /* local block i/o variables */
  boolean_T rtb_DigitalInput;

  /* S-Function (sldrtdi): '<S3>/Digital Input' */
  /* S-Function Block: <S3>/Digital Input */
  {
    double inval[1];
    double* invalp = inval;
    RTBIO_DriverIO(0, DIGITALINPUT, IOREAD, 1, &pid_pos_P.DigitalInput_Channels,
                   inval, &pid_pos_P.DigitalInput_BitMode);
    rtb_DigitalInput = (boolean_T) *invalp++;
  }

  /* Stop: '<S3>/Stop Simulation' */
  if (rtb_DigitalInput) {
    rtmSetStopRequested(pid_pos_M, 1);
  }

  /* End of Stop: '<S3>/Stop Simulation' */
}

/* Model update function for TID2 */
void pid_pos_update2(void)             /* Sample time: [0.005s, 0.0s] */
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
  if (!(++pid_pos_M->Timing.clockTick2)) {
    ++pid_pos_M->Timing.clockTickH2;
  }

  pid_pos_M->Timing.t[2] = pid_pos_M->Timing.clockTick2 *
    pid_pos_M->Timing.stepSize2 + pid_pos_M->Timing.clockTickH2 *
    pid_pos_M->Timing.stepSize2 * 4294967296.0;
}

/* Model wrapper function for compatibility with a static main program */
void pid_pos_output(int_T tid)
{
  switch (tid) {
   case 0 :
    pid_pos_output0();
    break;

   case 2 :
    pid_pos_output2();
    break;

   default :
    break;
  }
}

/* Model wrapper function for compatibility with a static main program */
void pid_pos_update(int_T tid)
{
  switch (tid) {
   case 0 :
    pid_pos_update0();
    break;

   case 2 :
    pid_pos_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void pid_pos_initialize(void)
{
  /* Start for TransportDelay: '<Root>/Transport Delay' */
  {
    real_T *pBuffer = &pid_pos_DW.TransportDelay_RWORK.TUbufferArea[0];
    pid_pos_DW.TransportDelay_IWORK.Tail = 0;
    pid_pos_DW.TransportDelay_IWORK.Head = 0;
    pid_pos_DW.TransportDelay_IWORK.Last = 0;
    pid_pos_DW.TransportDelay_IWORK.CircularBufSize = 1024;
    pBuffer[0] = pid_pos_P.TransportDelay_InitOutput;
    pBuffer[1024] = pid_pos_M->Timing.t[0];
    pid_pos_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
  }

  /* Start for S-Function (sldrtao): '<S3>/Analog Output' */

  /* S-Function Block: <S3>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) pid_pos_P.AnalogOutput_RangeMode;
      parm.rangeidx = pid_pos_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &pid_pos_P.AnalogOutput_Channels,
                     &pid_pos_P.AnalogOutput_InitialValue, &parm);
    }
  }

  /* InitializeConditions for S-Function (sldrtei): '<S3>/Encoder Input' */

  /* S-Function Block: <S3>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 1;
    parm.infilter = pid_pos_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IORESET, 2, pid_pos_P.EncoderInput_Channels,
                   NULL, &parm);
  }

  /* InitializeConditions for Integrator: '<S82>/Filter' */
  pid_pos_X.Filter_CSTATE = pid_pos_P.PIDController1_InitialConditionForFilter;

  /* InitializeConditions for Integrator: '<S39>/Integrator' */
  pid_pos_X.Integrator_CSTATE =
    pid_pos_P.PIDController_InitialConditionForIntegrator;

  /* InitializeConditions for Integrator: '<S34>/Filter' */
  pid_pos_X.Filter_CSTATE_n = pid_pos_P.PIDController_InitialConditionForFilter;

  /* InitializeConditions for TransferFcn: '<Root>/Rychlost' */
  pid_pos_X.Rychlost_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory' */
  pid_pos_DW.Memory_PreviousInput = pid_pos_P.Memory_InitialCondition;
}

/* Model terminate function */
void pid_pos_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<S3>/Analog Output' */

  /* S-Function Block: <S3>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) pid_pos_P.AnalogOutput_RangeMode;
      parm.rangeidx = pid_pos_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &pid_pos_P.AnalogOutput_Channels,
                     &pid_pos_P.AnalogOutput_FinalValue, &parm);
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
  pid_pos_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  pid_pos_update(tid);
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
  pid_pos_initialize();
}

void MdlTerminate(void)
{
  pid_pos_terminate();
}

/* Registration function */
RT_MODEL_pid_pos_T *pid_pos(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  pid_pos_P.EncoderInput_InputFilter = rtInf;

  /* initialize real-time model */
  (void) memset((void *)pid_pos_M, 0,
                sizeof(RT_MODEL_pid_pos_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&pid_pos_M->solverInfo, &pid_pos_M->Timing.simTimeStep);
    rtsiSetTPtr(&pid_pos_M->solverInfo, &rtmGetTPtr(pid_pos_M));
    rtsiSetStepSizePtr(&pid_pos_M->solverInfo, &pid_pos_M->Timing.stepSize0);
    rtsiSetdXPtr(&pid_pos_M->solverInfo, &pid_pos_M->derivs);
    rtsiSetContStatesPtr(&pid_pos_M->solverInfo, (real_T **)
                         &pid_pos_M->contStates);
    rtsiSetNumContStatesPtr(&pid_pos_M->solverInfo,
      &pid_pos_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&pid_pos_M->solverInfo,
      &pid_pos_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&pid_pos_M->solverInfo,
      &pid_pos_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&pid_pos_M->solverInfo,
      &pid_pos_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&pid_pos_M->solverInfo, (&rtmGetErrorStatus(pid_pos_M)));
    rtsiSetRTModelPtr(&pid_pos_M->solverInfo, pid_pos_M);
  }

  rtsiSetSimTimeStep(&pid_pos_M->solverInfo, MAJOR_TIME_STEP);
  pid_pos_M->intgData.y = pid_pos_M->odeY;
  pid_pos_M->intgData.f[0] = pid_pos_M->odeF[0];
  pid_pos_M->intgData.f[1] = pid_pos_M->odeF[1];
  pid_pos_M->intgData.f[2] = pid_pos_M->odeF[2];
  pid_pos_M->intgData.f[3] = pid_pos_M->odeF[3];
  pid_pos_M->intgData.f[4] = pid_pos_M->odeF[4];
  pid_pos_M->intgData.f[5] = pid_pos_M->odeF[5];
  pid_pos_M->contStates = ((real_T *) &pid_pos_X);
  rtsiSetSolverData(&pid_pos_M->solverInfo, (void *)&pid_pos_M->intgData);
  rtsiSetSolverName(&pid_pos_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = pid_pos_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    pid_pos_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    pid_pos_M->Timing.sampleTimes = (&pid_pos_M->Timing.sampleTimesArray[0]);
    pid_pos_M->Timing.offsetTimes = (&pid_pos_M->Timing.offsetTimesArray[0]);

    /* task periods */
    pid_pos_M->Timing.sampleTimes[0] = (0.0);
    pid_pos_M->Timing.sampleTimes[1] = (0.001);
    pid_pos_M->Timing.sampleTimes[2] = (0.005);

    /* task offsets */
    pid_pos_M->Timing.offsetTimes[0] = (0.0);
    pid_pos_M->Timing.offsetTimes[1] = (0.0);
    pid_pos_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(pid_pos_M, &pid_pos_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = pid_pos_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = pid_pos_M->Timing.perTaskSampleHitsArray;
    pid_pos_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    pid_pos_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(pid_pos_M, 15.0);
  pid_pos_M->Timing.stepSize0 = 0.001;
  pid_pos_M->Timing.stepSize1 = 0.001;
  pid_pos_M->Timing.stepSize2 = 0.005;

  /* External mode info */
  pid_pos_M->Sizes.checksums[0] = (424253741U);
  pid_pos_M->Sizes.checksums[1] = (4290173231U);
  pid_pos_M->Sizes.checksums[2] = (33802326U);
  pid_pos_M->Sizes.checksums[3] = (229526490U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    pid_pos_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(pid_pos_M->extModeInfo,
      &pid_pos_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(pid_pos_M->extModeInfo, pid_pos_M->Sizes.checksums);
    rteiSetTPtr(pid_pos_M->extModeInfo, rtmGetTPtr(pid_pos_M));
  }

  pid_pos_M->solverInfoPtr = (&pid_pos_M->solverInfo);
  pid_pos_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&pid_pos_M->solverInfo, 0.001);
  rtsiSetSolverMode(&pid_pos_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  pid_pos_M->blockIO = ((void *) &pid_pos_B);
  (void) memset(((void *) &pid_pos_B), 0,
                sizeof(B_pid_pos_T));

  {
    pid_pos_B.Step3 = 0.0;
    pid_pos_B.Angleconversion = 0.0;
    pid_pos_B.ProportionalGain = 0.0;
    pid_pos_B.DerivativeGain = 0.0;
    pid_pos_B.FilterCoefficient = 0.0;
    pid_pos_B.Positionconversion = 0.0;
    pid_pos_B.ProportionalGain_m = 0.0;
    pid_pos_B.DerivativeGain_l = 0.0;
    pid_pos_B.FilterCoefficient_g = 0.0;
    pid_pos_B.MotorVoltage = 0.0;
    pid_pos_B.Speed = 0.0;
    pid_pos_B.Switch = 0.0;
  }

  /* parameters */
  pid_pos_M->defaultParam = ((real_T *)&pid_pos_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &pid_pos_X;
    pid_pos_M->contStates = (x);
    (void) memset((void *)&pid_pos_X, 0,
                  sizeof(X_pid_pos_T));
  }

  /* states (dwork) */
  pid_pos_M->dwork = ((void *) &pid_pos_DW);
  (void) memset((void *)&pid_pos_DW, 0,
                sizeof(DW_pid_pos_T));
  pid_pos_DW.TransportDelay_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      pid_pos_DW.TransportDelay_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    pid_pos_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  pid_pos_M->Sizes.numContStates = (4);/* Number of continuous states */
  pid_pos_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  pid_pos_M->Sizes.numY = (0);         /* Number of model outputs */
  pid_pos_M->Sizes.numU = (0);         /* Number of model inputs */
  pid_pos_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  pid_pos_M->Sizes.numSampTimes = (3); /* Number of sample times */
  pid_pos_M->Sizes.numBlocks = (53);   /* Number of blocks */
  pid_pos_M->Sizes.numBlockIO = (14);  /* Number of block outputs */
  pid_pos_M->Sizes.numBlockPrms = (47);/* Sum of parameter "widths" */
  return pid_pos_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
