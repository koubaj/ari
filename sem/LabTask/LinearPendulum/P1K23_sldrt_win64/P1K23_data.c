/*
 * P1K23_data.c
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

/* Block parameters (default storage) */
P_P1K23_T P1K23_P = {
  /* Mask Parameter: PIDController1_D
   * Referenced by: '<S79>/Derivative Gain'
   */
  7.4102,

  /* Mask Parameter: PIDController_D
   * Referenced by: '<S31>/Derivative Gain'
   */
  16.2,

  /* Mask Parameter: AnalogOutput_FinalValue
   * Referenced by: '<S3>/Analog Output'
   */
  0.0,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S34>/Integral Gain'
   */
  1.14,

  /* Mask Parameter: PIDController1_InitialConditionForFilter
   * Referenced by: '<S80>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditionForFilter
   * Referenced by: '<S32>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditionForIntegrator
   * Referenced by: '<S37>/Integrator'
   */
  0.0,

  /* Mask Parameter: AnalogOutput_InitialValue
   * Referenced by: '<S3>/Analog Output'
   */
  0.0,

  /* Mask Parameter: EncoderInput_InputFilter
   * Referenced by: '<S3>/Encoder Input'
   */
  0.0,

  /* Mask Parameter: EncoderInput_MaxMissedTicks
   * Referenced by: '<S3>/Encoder Input'
   */
  200.0,

  /* Mask Parameter: AnalogOutput_MaxMissedTicks
   * Referenced by: '<S3>/Analog Output'
   */
  200.0,

  /* Mask Parameter: DigitalInput_MaxMissedTicks
   * Referenced by: '<S3>/Digital Input'
   */
  100.0,

  /* Mask Parameter: PIDController1_N
   * Referenced by: '<S88>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S40>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController1_P
   * Referenced by: '<S90>/Proportional Gain'
   */
  1.0,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S42>/Proportional Gain'
   */
  10.2,

  /* Mask Parameter: EncoderInput_YieldWhenWaiting
   * Referenced by: '<S3>/Encoder Input'
   */
  1.0,

  /* Mask Parameter: AnalogOutput_YieldWhenWaiting
   * Referenced by: '<S3>/Analog Output'
   */
  1.0,

  /* Mask Parameter: DigitalInput_YieldWhenWaiting
   * Referenced by: '<S3>/Digital Input'
   */
  0.0,

  /* Mask Parameter: DigitalInput_BitMode
   * Referenced by: '<S3>/Digital Input'
   */
  0,

  /* Mask Parameter: EncoderInput_Channels
   * Referenced by: '<S3>/Encoder Input'
   */
  { 0, 1 },

  /* Mask Parameter: AnalogOutput_Channels
   * Referenced by: '<S3>/Analog Output'
   */
  0,

  /* Mask Parameter: DigitalInput_Channels
   * Referenced by: '<S3>/Digital Input'
   */
  2,

  /* Mask Parameter: AnalogOutput_RangeMode
   * Referenced by: '<S3>/Analog Output'
   */
  1,

  /* Mask Parameter: AnalogOutput_VoltRange
   * Referenced by: '<S3>/Analog Output'
   */
  0,

  /* Expression: 0
   * Referenced by: '<Root>/Constant1'
   */
  0.0,

  /* Expression: -2*pi/4096
   * Referenced by: '<S3>/Angle conversion'
   */
  -0.0015339807878856412,

  /* Expression: -0.3
   * Referenced by: '<Root>/Constant'
   */
  -0.3,

  /* Expression: -0.093/4096
   * Referenced by: '<S3>/Position.  conversion'
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

  /* Computed Parameter: ManualSwitch_CurrentSetting
   * Referenced by: '<Root>/Manual Switch'
   */
  1U,

  /* Computed Parameter: ManualSwitch1_CurrentSetting
   * Referenced by: '<Root>/Manual Switch1'
   */
  0U
};
