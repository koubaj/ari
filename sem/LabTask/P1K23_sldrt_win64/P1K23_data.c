/*
 * P1K23_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "P1K23".
 *
 * Model version              : 9.2
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon May  4 11:40:24 2026
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "P1K23.h"
#include "P1K23_private.h"

/* Block parameters (default storage) */
P_P1K23_T P1K23_P = {
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

  /* Expression: -1
   * Referenced by: '<Root>/Gain1'
   */
  -1.0,

  /* Expression: 1
   * Referenced by: '<Root>/Step'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 0.35
   * Referenced by: '<Root>/Step'
   */
  0.35,

  /* Expression: -0.093/4096
   * Referenced by: '<S1>/Position.  conversion'
   */
  -2.2705078125E-5,

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

  /* Expression: -2*pi/4096
   * Referenced by: '<S1>/Angle conversion'
   */
  -0.0015339807878856412,

  /* Computed Parameter: Directionswitch_CurrentSetting
   * Referenced by: '<Root>/Direction switch'
   */
  0U
};
