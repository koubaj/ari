/*
 * pid_pos_data.c
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

/* Block parameters (default storage) */
P_pid_pos_T pid_pos_P = {
  /* Variable: Kd
   * Referenced by: '<S33>/Derivative Gain'
   */
  0.158,

  /* Variable: Kd_phi
   * Referenced by: '<S81>/Derivative Gain'
   */
  0.22,

  /* Variable: Ki
   * Referenced by: '<S36>/Integral Gain'
   */
  0.136,

  /* Variable: Kp
   * Referenced by: '<S44>/Proportional Gain'
   */
  0.522,

  /* Mask Parameter: AnalogOutput_FinalValue
   * Referenced by: '<S3>/Analog Output'
   */
  0.0,

  /* Mask Parameter: PIDController1_InitialConditionForFilter
   * Referenced by: '<S82>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditionForFilter
   * Referenced by: '<S34>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditionForIntegrator
   * Referenced by: '<S39>/Integrator'
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

  /* Mask Parameter: PIDController_LowerSaturationLimit
   * Referenced by:
   *   '<S46>/Saturation'
   *   '<S32>/DeadZone'
   */
  -1.0,

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
   * Referenced by: '<S90>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S42>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController1_P
   * Referenced by: '<S92>/Proportional Gain'
   */
  0.0,

  /* Mask Parameter: PIDController_UpperSaturationLimit
   * Referenced by:
   *   '<S46>/Saturation'
   *   '<S32>/DeadZone'
   */
  1.0,

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

  /* Expression: 1
   * Referenced by: '<Root>/Saturation'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<Root>/Saturation'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S30>/Constant1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Step3'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step3'
   */
  0.0,

  /* Expression: -0.4
   * Referenced by: '<Root>/Step3'
   */
  -0.4,

  /* Expression: 1.6
   * Referenced by: '<Root>/Transport Delay'
   */
  1.6,

  /* Expression: 0
   * Referenced by: '<Root>/Transport Delay'
   */
  0.0,

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

  /* Expression: 0
   * Referenced by: '<S30>/ZeroGain'
   */
  0.0,

  /* Computed Parameter: Memory_InitialCondition
   * Referenced by: '<S30>/Memory'
   */
  false,

  /* Computed Parameter: ManualSwitch_CurrentSetting
   * Referenced by: '<Root>/Manual Switch'
   */
  1U,

  /* Computed Parameter: ManualSwitch1_CurrentSetting
   * Referenced by: '<Root>/Manual Switch1'
   */
  0U
};
