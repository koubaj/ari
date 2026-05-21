/*
 * state.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "state".
 *
 * Model version              : 9.9
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu May 21 13:35:31 2026
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "state.h"
#include "state_private.h"
#include "state_dt.h"

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
B_state_T state_B;

/* Continuous states */
X_state_T state_X;

/* Block states (default storage) */
DW_state_T state_DW;

/* Real-time model */
static RT_MODEL_state_T state_M_;
RT_MODEL_state_T *const state_M = &state_M_;
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(state_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(state_M, 2);
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
  (state_M->Timing.TaskCounters.TID[2])++;
  if ((state_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.005s, 0.0s] */
    state_M->Timing.TaskCounters.TID[2] = 0;
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
  int_T nXc = 10;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  state_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  state_output0();
  state_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE5_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  state_output0();
  state_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE5_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  state_output0();
  state_derivatives();

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
  state_output0();
  state_derivatives();

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
  state_output0();
  state_derivatives();

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
void state_output0(void)               /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_EncoderInput[2];
  real_T rtb_StateSpace1_idx_0;
  real_T rtb_StateSpace1_idx_1;
  real_T rtb_StateSpace1_idx_2;
  real_T rtb_StateSpace1_idx_3;
  real_T rtb_StateSpace_idx_0;
  real_T rtb_StateSpace_idx_1;
  real_T rtb_StateSpace_idx_2;
  real_T rtb_StateSpace_idx_3;
  int32_T rtb_StateSpace_idx_0_tmp;
  int_T ci;
  if (rtmIsMajorTimeStep(state_M)) {
    /* set solver stop time */
    if (!(state_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&state_M->solverInfo, ((state_M->Timing.clockTickH0
        + 1) * state_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&state_M->solverInfo, ((state_M->Timing.clockTick0 +
        1) * state_M->Timing.stepSize0 + state_M->Timing.clockTickH0 *
        state_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(state_M)) {
    state_M->Timing.t[0] = rtsiGetT(&state_M->solverInfo);
  }

  /* StateSpace: '<Root>/State-Space' */
  rtb_StateSpace_idx_0 = 0.0;
  rtb_StateSpace_idx_1 = 0.0;
  rtb_StateSpace_idx_2 = 0.0;
  rtb_StateSpace_idx_3 = 0.0;

  /* StateSpace: '<Root>/State-Space1' */
  rtb_StateSpace1_idx_0 = 0.0;
  rtb_StateSpace1_idx_1 = 0.0;
  rtb_StateSpace1_idx_2 = 0.0;
  rtb_StateSpace1_idx_3 = 0.0;
  for (ci = 0; ci < 4; ci++) {
    /* StateSpace: '<Root>/State-Space' incorporates:
     *  StateSpace: '<Root>/State-Space1'
     */
    rtb_StateSpace_idx_0_tmp = ci << 2;
    rtb_StateSpace_idx_0 += state_P.StateSpace_C[rtb_StateSpace_idx_0_tmp] *
      state_X.StateSpace_CSTATE[ci];
    rtb_StateSpace_idx_1 += state_P.StateSpace_C[rtb_StateSpace_idx_0_tmp + 1] *
      state_X.StateSpace_CSTATE[ci];
    rtb_StateSpace_idx_2 += state_P.StateSpace_C[rtb_StateSpace_idx_0_tmp + 2] *
      state_X.StateSpace_CSTATE[ci];
    rtb_StateSpace_idx_3 += state_P.StateSpace_C[rtb_StateSpace_idx_0_tmp + 3] *
      state_X.StateSpace_CSTATE[ci];

    /* StateSpace: '<Root>/State-Space1' incorporates:
     *  StateSpace: '<Root>/State-Space'
     */
    rtb_StateSpace1_idx_0 += state_P.StateSpace1_C[rtb_StateSpace_idx_0_tmp] *
      state_X.StateSpace1_CSTATE[ci];
    rtb_StateSpace1_idx_1 += state_P.StateSpace1_C[rtb_StateSpace_idx_0_tmp + 1]
      * state_X.StateSpace1_CSTATE[ci];
    rtb_StateSpace1_idx_2 += state_P.StateSpace1_C[rtb_StateSpace_idx_0_tmp + 2]
      * state_X.StateSpace1_CSTATE[ci];
    rtb_StateSpace1_idx_3 += state_P.StateSpace1_C[rtb_StateSpace_idx_0_tmp + 3]
      * state_X.StateSpace1_CSTATE[ci];
  }

  /* ManualSwitch: '<Root>/Manual Switch1' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain1'
   *  ManualSwitch: '<Root>/Manual Switch3'
   */
  if (state_P.ManualSwitch1_CurrentSetting == 1) {
    /* Gain: '<Root>/Gain1' incorporates:
     *  ManualSwitch: '<Root>/Manual Switch3'
     */
    if (state_P.ManualSwitch3_CurrentSetting == 1) {
      rtb_StateSpace1_idx_0 = rtb_StateSpace_idx_0;
      rtb_StateSpace1_idx_1 = rtb_StateSpace_idx_1;
      rtb_StateSpace1_idx_2 = rtb_StateSpace_idx_2;
      rtb_StateSpace1_idx_3 = rtb_StateSpace_idx_3;
    }

    rtb_StateSpace_idx_1 = ((state_P.K_new_down[0] * rtb_StateSpace1_idx_0 +
      state_P.K_new_down[1] * rtb_StateSpace1_idx_1) + state_P.K_new_down[2] *
      rtb_StateSpace1_idx_2) + state_P.K_new_down[3] * rtb_StateSpace1_idx_3;
  } else {
    if (state_P.ManualSwitch3_CurrentSetting == 1) {
      /* Gain: '<Root>/Gain' incorporates:
       *  ManualSwitch: '<Root>/Manual Switch3'
       */
      rtb_StateSpace1_idx_0 = rtb_StateSpace_idx_0;
      rtb_StateSpace1_idx_1 = rtb_StateSpace_idx_1;
      rtb_StateSpace1_idx_2 = rtb_StateSpace_idx_2;
      rtb_StateSpace1_idx_3 = rtb_StateSpace_idx_3;
    }

    rtb_StateSpace_idx_1 = ((state_P.K_new_up[0] * rtb_StateSpace1_idx_0 +
      state_P.K_new_up[1] * rtb_StateSpace1_idx_1) + state_P.K_new_up[2] *
      rtb_StateSpace1_idx_2) + state_P.K_new_up[3] * rtb_StateSpace1_idx_3;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch1' */

  /* ManualSwitch: '<Root>/Manual Switch' incorporates:
   *  Gain: '<Root>/Gain2'
   *  Gain: '<Root>/Gain3'
   *  Integrator: '<Root>/Integrator1'
   */
  if (state_P.ManualSwitch_CurrentSetting == 1) {
    rtb_StateSpace_idx_0 = state_P.K_I_up * state_X.Integrator1_CSTATE;
  } else {
    rtb_StateSpace_idx_0 = state_P.K_I_down * state_X.Integrator1_CSTATE;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */

  /* Sum: '<Root>/Sum' */
  rtb_StateSpace_idx_1 = (0.0 - rtb_StateSpace_idx_0) - rtb_StateSpace_idx_1;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_StateSpace_idx_1 > state_P.Saturation_UpperSat) {
    rtb_StateSpace_idx_1 = state_P.Saturation_UpperSat;
  } else if (rtb_StateSpace_idx_1 < state_P.Saturation_LowerSat) {
    rtb_StateSpace_idx_1 = state_P.Saturation_LowerSat;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Sum: '<Root>/Sum3' */
  state_B.MotorVoltage = rtb_StateSpace_idx_1;
  if (rtmIsMajorTimeStep(state_M)) {
    /* S-Function (sldrtei): '<S1>/Encoder Input' */
    /* S-Function Block: <S1>/Encoder Input */
    {
      ENCODERINPARM parm;
      parm.quad = (QUADMODE) 2;
      parm.index = (INDEXPULSE) 1;
      parm.infilter = state_P.EncoderInput_InputFilter;
      RTBIO_DriverIO(0, ENCODERINPUT, IOREAD, 2, state_P.EncoderInput_Channels,
                     &rtb_EncoderInput[0], &parm);
    }

    /* Gain: '<S1>/Position.  conversion' */
    state_B.Positionconversion = state_P.Positionconversion_Gain *
      rtb_EncoderInput[0];
  }

  /* TransferFcn: '<Root>/Rychlost' */
  state_B.Speed = 0.0;
  state_B.Speed += state_P.Rychlost_C * state_X.Rychlost_CSTATE;
  state_B.Speed += state_P.Rychlost_D * state_B.Positionconversion;
  if (rtmIsMajorTimeStep(state_M)) {
    /* Gain: '<S1>/Angle conversion' */
    state_B.Angleconversion = state_P.Angleconversion_Gain * rtb_EncoderInput[1];

    /* S-Function (sldrtao): '<S1>/Analog Output' */
    /* S-Function Block: <S1>/Analog Output */
    {
      {
        ANALOGIOPARM parm;
        parm.mode = (RANGEMODE) state_P.AnalogOutput_RangeMode;
        parm.rangeidx = state_P.AnalogOutput_VoltRange;
        RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                       &state_P.AnalogOutput_Channels, ((real_T*)
          (&state_B.MotorVoltage)), &parm);
      }
    }

    /* ManualSwitch: '<Root>/Manual Switch2' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<Root>/Constant1'
     */
    if (state_P.ManualSwitch2_CurrentSetting == 1) {
      rtb_StateSpace_idx_0 = state_P.Constant1_Value;
    } else {
      rtb_StateSpace_idx_0 = state_P.Constant_Value;
    }

    /* End of ManualSwitch: '<Root>/Manual Switch2' */

    /* Sum: '<Root>/Sum1' */
    state_B.Sum1 = rtb_StateSpace_idx_0 - state_B.Positionconversion;
  }

  /* SignalConversion generated from: '<Root>/State-Space' */
  state_B.TmpSignalConversionAtStateSpaceInport1[0] = rtb_StateSpace_idx_1;
  state_B.TmpSignalConversionAtStateSpaceInport1[1] = state_B.Positionconversion;
  state_B.TmpSignalConversionAtStateSpaceInport1[2] = state_B.Angleconversion;
}

/* Model update function for TID0 */
void state_update0(void)               /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(state_M)) {
    rt_ertODEUpdateContinuousStates(&state_M->solverInfo);
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
  if (!(++state_M->Timing.clockTick0)) {
    ++state_M->Timing.clockTickH0;
  }

  state_M->Timing.t[0] = rtsiGetSolverStopTime(&state_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++state_M->Timing.clockTick1)) {
    ++state_M->Timing.clockTickH1;
  }

  state_M->Timing.t[1] = state_M->Timing.clockTick1 * state_M->Timing.stepSize1
    + state_M->Timing.clockTickH1 * state_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void state_derivatives(void)
{
  XDot_state_T *_rtXdot;
  int32_T StateSpace_CSTATE_tmp;
  int_T ci;
  _rtXdot = ((XDot_state_T *) state_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = state_B.Sum1;

  /* Derivatives for StateSpace: '<Root>/State-Space' */
  _rtXdot->StateSpace_CSTATE[0] = 0.0;
  _rtXdot->StateSpace_CSTATE[1] = 0.0;
  _rtXdot->StateSpace_CSTATE[2] = 0.0;
  _rtXdot->StateSpace_CSTATE[3] = 0.0;
  for (ci = 0; ci < 4; ci++) {
    StateSpace_CSTATE_tmp = ci << 2;
    _rtXdot->StateSpace_CSTATE[0] += (state_P.A_up[StateSpace_CSTATE_tmp] -
      state_ConstP.StateSpace_rtw_collapsed_sub_expr_6[StateSpace_CSTATE_tmp]) *
      state_X.StateSpace_CSTATE[ci];
    _rtXdot->StateSpace_CSTATE[1] += (state_P.A_up[StateSpace_CSTATE_tmp + 1] -
      state_ConstP.StateSpace_rtw_collapsed_sub_expr_6[StateSpace_CSTATE_tmp + 1])
      * state_X.StateSpace_CSTATE[ci];
    _rtXdot->StateSpace_CSTATE[2] += (state_P.A_up[StateSpace_CSTATE_tmp + 2] -
      state_ConstP.StateSpace_rtw_collapsed_sub_expr_6[StateSpace_CSTATE_tmp + 2])
      * state_X.StateSpace_CSTATE[ci];
    _rtXdot->StateSpace_CSTATE[3] += (state_P.A_up[StateSpace_CSTATE_tmp + 3] -
      state_ConstP.StateSpace_rtw_collapsed_sub_expr_6[StateSpace_CSTATE_tmp + 3])
      * state_X.StateSpace_CSTATE[ci];
  }

  for (ci = 0; ci < 3; ci++) {
    _rtXdot->StateSpace_CSTATE[0] += state_P.StateSpace_B[ci << 2] *
      state_B.TmpSignalConversionAtStateSpaceInport1[ci];
    _rtXdot->StateSpace_CSTATE[1] += state_P.StateSpace_B[(ci << 2) + 1] *
      state_B.TmpSignalConversionAtStateSpaceInport1[ci];
    _rtXdot->StateSpace_CSTATE[2] += state_P.StateSpace_B[(ci << 2) + 2] *
      state_B.TmpSignalConversionAtStateSpaceInport1[ci];
    _rtXdot->StateSpace_CSTATE[3] += state_P.StateSpace_B[(ci << 2) + 3] *
      state_B.TmpSignalConversionAtStateSpaceInport1[ci];
  }

  /* End of Derivatives for StateSpace: '<Root>/State-Space' */

  /* Derivatives for StateSpace: '<Root>/State-Space1' */
  _rtXdot->StateSpace1_CSTATE[0] = 0.0;
  _rtXdot->StateSpace1_CSTATE[1] = 0.0;
  _rtXdot->StateSpace1_CSTATE[2] = 0.0;
  _rtXdot->StateSpace1_CSTATE[3] = 0.0;
  for (ci = 0; ci < 4; ci++) {
    StateSpace_CSTATE_tmp = ci << 2;
    _rtXdot->StateSpace1_CSTATE[0] += (state_P.A_down[StateSpace_CSTATE_tmp] -
      state_ConstP.StateSpace1_rtw_collapsed_sub_expr_10[StateSpace_CSTATE_tmp])
      * state_X.StateSpace1_CSTATE[ci];
    StateSpace_CSTATE_tmp = (ci << 2) + 1;
    _rtXdot->StateSpace1_CSTATE[1] += (state_P.A_down[StateSpace_CSTATE_tmp] -
      state_ConstP.StateSpace1_rtw_collapsed_sub_expr_10[StateSpace_CSTATE_tmp])
      * state_X.StateSpace1_CSTATE[ci];
    StateSpace_CSTATE_tmp = (ci << 2) + 2;
    _rtXdot->StateSpace1_CSTATE[2] += (state_P.A_down[StateSpace_CSTATE_tmp] -
      state_ConstP.StateSpace1_rtw_collapsed_sub_expr_10[StateSpace_CSTATE_tmp])
      * state_X.StateSpace1_CSTATE[ci];
    StateSpace_CSTATE_tmp = (ci << 2) + 3;
    _rtXdot->StateSpace1_CSTATE[3] += (state_P.A_down[StateSpace_CSTATE_tmp] -
      state_ConstP.StateSpace1_rtw_collapsed_sub_expr_10[StateSpace_CSTATE_tmp])
      * state_X.StateSpace1_CSTATE[ci];
  }

  for (ci = 0; ci < 3; ci++) {
    _rtXdot->StateSpace1_CSTATE[0] += state_P.StateSpace1_B[ci << 2] *
      state_B.TmpSignalConversionAtStateSpaceInport1[ci];
    _rtXdot->StateSpace1_CSTATE[1] += state_P.StateSpace1_B[(ci << 2) + 1] *
      state_B.TmpSignalConversionAtStateSpaceInport1[ci];
    _rtXdot->StateSpace1_CSTATE[2] += state_P.StateSpace1_B[(ci << 2) + 2] *
      state_B.TmpSignalConversionAtStateSpaceInport1[ci];
    _rtXdot->StateSpace1_CSTATE[3] += state_P.StateSpace1_B[(ci << 2) + 3] *
      state_B.TmpSignalConversionAtStateSpaceInport1[ci];
  }

  /* End of Derivatives for StateSpace: '<Root>/State-Space1' */

  /* Derivatives for TransferFcn: '<Root>/Rychlost' */
  _rtXdot->Rychlost_CSTATE = 0.0;
  _rtXdot->Rychlost_CSTATE += state_P.Rychlost_A * state_X.Rychlost_CSTATE;
  _rtXdot->Rychlost_CSTATE += state_B.Positionconversion;
}

/* Model output function for TID2 */
void state_output2(void)               /* Sample time: [0.005s, 0.0s] */
{
  /* local block i/o variables */
  boolean_T rtb_DigitalInput;

  /* S-Function (sldrtdi): '<S1>/Digital Input' */
  /* S-Function Block: <S1>/Digital Input */
  {
    double inval[1];
    double* invalp = inval;
    RTBIO_DriverIO(0, DIGITALINPUT, IOREAD, 1, &state_P.DigitalInput_Channels,
                   inval, &state_P.DigitalInput_BitMode);
    rtb_DigitalInput = (boolean_T) *invalp++;
  }

  /* Stop: '<S1>/Stop Simulation' */
  if (rtb_DigitalInput) {
    rtmSetStopRequested(state_M, 1);
  }

  /* End of Stop: '<S1>/Stop Simulation' */
}

/* Model update function for TID2 */
void state_update2(void)               /* Sample time: [0.005s, 0.0s] */
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
  if (!(++state_M->Timing.clockTick2)) {
    ++state_M->Timing.clockTickH2;
  }

  state_M->Timing.t[2] = state_M->Timing.clockTick2 * state_M->Timing.stepSize2
    + state_M->Timing.clockTickH2 * state_M->Timing.stepSize2 * 4294967296.0;
}

/* Model wrapper function for compatibility with a static main program */
void state_output(int_T tid)
{
  switch (tid) {
   case 0 :
    state_output0();
    break;

   case 2 :
    state_output2();
    break;

   default :
    break;
  }
}

/* Model wrapper function for compatibility with a static main program */
void state_update(int_T tid)
{
  switch (tid) {
   case 0 :
    state_update0();
    break;

   case 2 :
    state_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void state_initialize(void)
{
  /* Start for S-Function (sldrtao): '<S1>/Analog Output' */

  /* S-Function Block: <S1>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) state_P.AnalogOutput_RangeMode;
      parm.rangeidx = state_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1, &state_P.AnalogOutput_Channels,
                     &state_P.AnalogOutput_InitialValue, &parm);
    }
  }

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  state_X.Integrator1_CSTATE = state_P.Integrator1_IC;

  /* InitializeConditions for StateSpace: '<Root>/State-Space' */
  state_X.StateSpace_CSTATE[0] = state_P.StateSpace_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/State-Space1' */
  state_X.StateSpace1_CSTATE[0] = state_P.StateSpace1_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/State-Space' */
  state_X.StateSpace_CSTATE[1] = state_P.StateSpace_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/State-Space1' */
  state_X.StateSpace1_CSTATE[1] = state_P.StateSpace1_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/State-Space' */
  state_X.StateSpace_CSTATE[2] = state_P.StateSpace_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/State-Space1' */
  state_X.StateSpace1_CSTATE[2] = state_P.StateSpace1_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/State-Space' */
  state_X.StateSpace_CSTATE[3] = state_P.StateSpace_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/State-Space1' */
  state_X.StateSpace1_CSTATE[3] = state_P.StateSpace1_InitialCondition;

  /* InitializeConditions for S-Function (sldrtei): '<S1>/Encoder Input' */

  /* S-Function Block: <S1>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 1;
    parm.infilter = state_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IORESET, 2, state_P.EncoderInput_Channels,
                   NULL, &parm);
  }

  /* InitializeConditions for TransferFcn: '<Root>/Rychlost' */
  state_X.Rychlost_CSTATE = 0.0;
}

/* Model terminate function */
void state_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<S1>/Analog Output' */

  /* S-Function Block: <S1>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) state_P.AnalogOutput_RangeMode;
      parm.rangeidx = state_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1, &state_P.AnalogOutput_Channels,
                     &state_P.AnalogOutput_FinalValue, &parm);
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
  state_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  state_update(tid);
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
  state_initialize();
}

void MdlTerminate(void)
{
  state_terminate();
}

/* Registration function */
RT_MODEL_state_T *state(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  state_P.EncoderInput_InputFilter = rtInf;

  /* initialize real-time model */
  (void) memset((void *)state_M, 0,
                sizeof(RT_MODEL_state_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&state_M->solverInfo, &state_M->Timing.simTimeStep);
    rtsiSetTPtr(&state_M->solverInfo, &rtmGetTPtr(state_M));
    rtsiSetStepSizePtr(&state_M->solverInfo, &state_M->Timing.stepSize0);
    rtsiSetdXPtr(&state_M->solverInfo, &state_M->derivs);
    rtsiSetContStatesPtr(&state_M->solverInfo, (real_T **) &state_M->contStates);
    rtsiSetNumContStatesPtr(&state_M->solverInfo, &state_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&state_M->solverInfo,
      &state_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&state_M->solverInfo,
      &state_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&state_M->solverInfo,
      &state_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&state_M->solverInfo, (&rtmGetErrorStatus(state_M)));
    rtsiSetRTModelPtr(&state_M->solverInfo, state_M);
  }

  rtsiSetSimTimeStep(&state_M->solverInfo, MAJOR_TIME_STEP);
  state_M->intgData.y = state_M->odeY;
  state_M->intgData.f[0] = state_M->odeF[0];
  state_M->intgData.f[1] = state_M->odeF[1];
  state_M->intgData.f[2] = state_M->odeF[2];
  state_M->intgData.f[3] = state_M->odeF[3];
  state_M->intgData.f[4] = state_M->odeF[4];
  state_M->intgData.f[5] = state_M->odeF[5];
  state_M->contStates = ((real_T *) &state_X);
  rtsiSetSolverData(&state_M->solverInfo, (void *)&state_M->intgData);
  rtsiSetSolverName(&state_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = state_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    state_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    state_M->Timing.sampleTimes = (&state_M->Timing.sampleTimesArray[0]);
    state_M->Timing.offsetTimes = (&state_M->Timing.offsetTimesArray[0]);

    /* task periods */
    state_M->Timing.sampleTimes[0] = (0.0);
    state_M->Timing.sampleTimes[1] = (0.001);
    state_M->Timing.sampleTimes[2] = (0.005);

    /* task offsets */
    state_M->Timing.offsetTimes[0] = (0.0);
    state_M->Timing.offsetTimes[1] = (0.0);
    state_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(state_M, &state_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = state_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = state_M->Timing.perTaskSampleHitsArray;
    state_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    state_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(state_M, 10.0);
  state_M->Timing.stepSize0 = 0.001;
  state_M->Timing.stepSize1 = 0.001;
  state_M->Timing.stepSize2 = 0.005;

  /* External mode info */
  state_M->Sizes.checksums[0] = (2400066694U);
  state_M->Sizes.checksums[1] = (1656031503U);
  state_M->Sizes.checksums[2] = (1888843413U);
  state_M->Sizes.checksums[3] = (3692017894U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    state_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(state_M->extModeInfo,
      &state_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(state_M->extModeInfo, state_M->Sizes.checksums);
    rteiSetTPtr(state_M->extModeInfo, rtmGetTPtr(state_M));
  }

  state_M->solverInfoPtr = (&state_M->solverInfo);
  state_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&state_M->solverInfo, 0.001);
  rtsiSetSolverMode(&state_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  state_M->blockIO = ((void *) &state_B);

  {
    state_B.MotorVoltage = 0.0;
    state_B.Positionconversion = 0.0;
    state_B.Speed = 0.0;
    state_B.Angleconversion = 0.0;
    state_B.Sum1 = 0.0;
    state_B.TmpSignalConversionAtStateSpaceInport1[0] = 0.0;
    state_B.TmpSignalConversionAtStateSpaceInport1[1] = 0.0;
    state_B.TmpSignalConversionAtStateSpaceInport1[2] = 0.0;
  }

  /* parameters */
  state_M->defaultParam = ((real_T *)&state_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &state_X;
    state_M->contStates = (x);
    (void) memset((void *)&state_X, 0,
                  sizeof(X_state_T));
  }

  /* states (dwork) */
  state_M->dwork = ((void *) &state_DW);
  (void) memset((void *)&state_DW, 0,
                sizeof(DW_state_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    state_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  state_M->Sizes.numContStates = (10); /* Number of continuous states */
  state_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  state_M->Sizes.numY = (0);           /* Number of model outputs */
  state_M->Sizes.numU = (0);           /* Number of model inputs */
  state_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  state_M->Sizes.numSampTimes = (3);   /* Number of sample times */
  state_M->Sizes.numBlocks = (35);     /* Number of blocks */
  state_M->Sizes.numBlockIO = (6);     /* Number of block outputs */
  state_M->Sizes.numBlockPrms = (130); /* Sum of parameter "widths" */
  return state_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
