/*
 * StepanovoPendulum_data.c
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

/* Block parameters (default storage) */
P_StepanovoPendulum_T StepanovoPendulum_P = {
  /* Variable: A1
   * Referenced by: '<Root>/Gain1'
   */
  0.58116524735258523,

  /* Variable: A2
   * Referenced by: '<Root>/Gain2'
   */
  0.41883475264741482,

  /* Variable: t2
   * Referenced by: '<Root>/Transport Delay'
   */
  0.2895001263455691,

  /* Mask Parameter: AnalogOutput_FinalValue
   * Referenced by: '<S1>/Analog Output'
   */
  0.0,

  /* Mask Parameter: AnalogOutput_InitialValue
   * Referenced by: '<S1>/Analog Output'
   */
  0.0,

  /* Mask Parameter: EncoderInput_InputFilter
   * Referenced by: '<S1>/Encoder Input'
   */
  0.0,

  /* Mask Parameter: EncoderInput_MaxMissedTicks
   * Referenced by: '<S1>/Encoder Input'
   */
  200.0,

  /* Mask Parameter: AnalogOutput_MaxMissedTicks
   * Referenced by: '<S1>/Analog Output'
   */
  200.0,

  /* Mask Parameter: DigitalInput_MaxMissedTicks
   * Referenced by: '<S1>/Digital Input'
   */
  100.0,

  /* Mask Parameter: EncoderInput_YieldWhenWaiting
   * Referenced by: '<S1>/Encoder Input'
   */
  1.0,

  /* Mask Parameter: AnalogOutput_YieldWhenWaiting
   * Referenced by: '<S1>/Analog Output'
   */
  1.0,

  /* Mask Parameter: DigitalInput_YieldWhenWaiting
   * Referenced by: '<S1>/Digital Input'
   */
  0.0,

  /* Mask Parameter: DigitalInput_BitMode
   * Referenced by: '<S1>/Digital Input'
   */
  0,

  /* Mask Parameter: EncoderInput_Channels
   * Referenced by: '<S1>/Encoder Input'
   */
  { 0, 1 },

  /* Mask Parameter: AnalogOutput_Channels
   * Referenced by: '<S1>/Analog Output'
   */
  0,

  /* Mask Parameter: DigitalInput_Channels
   * Referenced by: '<S1>/Digital Input'
   */
  2,

  /* Mask Parameter: AnalogOutput_RangeMode
   * Referenced by: '<S1>/Analog Output'
   */
  1,

  /* Mask Parameter: AnalogOutput_VoltRange
   * Referenced by: '<S1>/Analog Output'
   */
  0,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Gain3'
   */
  0.0,

  /* Expression: -0.093/4096
   * Referenced by: '<S1>/Position.  conversion'
   */
  -2.2705078125E-5,

  /* Expression: 1
   * Referenced by: '<Root>/Step2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step2'
   */
  0.0,

  /* Expression: 0.4
   * Referenced by: '<Root>/Step2'
   */
  0.4,

  /* Expression: 0
   * Referenced by: '<Root>/Transport Delay'
   */
  0.0,

  /* Expression: 3
   * Referenced by: '<Root>/Gain'
   */
  3.0,

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<Root>/Transfer Fcn'
   */
  -100.0,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<Root>/Transfer Fcn'
   */
  -10000.0,

  /* Computed Parameter: TransferFcn_D
   * Referenced by: '<Root>/Transfer Fcn'
   */
  100.0,

  /* Expression: 0.5
   * Referenced by: '<Root>/Gain9'
   */
  0.5,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Gain5'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Constant'
   */
  0.0,

  /* Expression: -2*pi/4096
   * Referenced by: '<S1>/Angle conversion'
   */
  -0.0015339807878856412,

  /* Expression: 1
   * Referenced by: '<Root>/Gain4'
   */
  1.0,

  /* Computed Parameter: TransferFcn1_A
   * Referenced by: '<Root>/Transfer Fcn1'
   */
  -100.0,

  /* Computed Parameter: TransferFcn1_C
   * Referenced by: '<Root>/Transfer Fcn1'
   */
  -10000.0,

  /* Computed Parameter: TransferFcn1_D
   * Referenced by: '<Root>/Transfer Fcn1'
   */
  100.0,

  /* Expression: 0.1
   * Referenced by: '<Root>/Gain6'
   */
  0.1,

  /* Computed Parameter: Rychlost_A
   * Referenced by: '<Root>/Rychlost'
   */
  -25.0,

  /* Computed Parameter: Rychlost_C
   * Referenced by: '<Root>/Rychlost'
   */
  -625.0,

  /* Computed Parameter: Rychlost_D
   * Referenced by: '<Root>/Rychlost'
   */
  25.0,

  /* Computed Parameter: ManualSwitch_CurrentSetting
   * Referenced by: '<Root>/Manual Switch'
   */
  0U
};
