/*
 * state_data.c
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

/* Block parameters (default storage) */
P_state_T state_P = {
  /* Variable: A_down
   * Referenced by: '<Root>/State-Space1'
   */
  { -3.3780689819429126, 1.0, 40.425145141315937, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0064684247577219437, 0.0, -0.677407243920814, 1.0, 1.2651762476600847, 0.0,
    -132.49586832997781, 0.0 },

  /* Variable: A_up
   * Referenced by: '<Root>/State-Space'
   */
  { -3.3780689819429126, 1.0, -40.425145141315937, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0064684247577219437, 0.0, -0.677407243920814, 1.0, 1.2651762476600847,
    0.0, 132.49586832997781, 0.0 },

  /* Variable: K_I_down
   * Referenced by: '<Root>/Gain3'
   */
  -4.5863188615609518,

  /* Variable: K_I_up
   * Referenced by: '<Root>/Gain2'
   */
  12.179974998288932,

  /* Variable: K_new_down
   * Referenced by: '<Root>/Gain1'
   */
  { 2.9030103663405202, 7.6274058431281739, -0.14515941860843187,
    -3.4682856021848 },

  /* Variable: K_new_up
   * Referenced by: '<Root>/Gain'
   */
  { -7.95648610871727, -18.285388595088612, 1.2999883756526764,
    14.745475851973454 },

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
   * Referenced by: '<Root>/Constant1'
   */
  0.0,

  /* Expression: -0.3
   * Referenced by: '<Root>/Constant'
   */
  -0.3,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator1'
   */
  0.0,

  /* Expression: [B_up, L_up]
   * Referenced by: '<Root>/State-Space'
   */
  { 4.7292965747200775, 0.0, 56.595203197842309, 0.0, 619.35402176226853,
    53.341201079012322, -2034.160209624818, -37.132367502588224,
    -103.27483458093444, -4.0057551782714018, 1388.3281082791018,
    67.603322695123182 },

  /* Expression: eye(4)
   * Referenced by: '<Root>/State-Space'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0 },

  /* Expression: 0
   * Referenced by: '<Root>/State-Space'
   */
  0.0,

  /* Expression: [B_down, L_down]
   * Referenced by: '<Root>/State-Space1'
   */
  { 4.7292965747200775, 0.0, -56.595203197842309, 0.0, 146.07908260614067,
    27.706739435663511, 1019.8122903593647, 35.961859948003536,
    6.8077610650057405, 0.39917629328120696, 148.68363228080906,
    33.23778433847216 },

  /* Expression: eye(4)
   * Referenced by: '<Root>/State-Space1'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0 },

  /* Expression: 0
   * Referenced by: '<Root>/State-Space1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Saturation'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<Root>/Saturation'
   */
  -1.0,

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

  /* Computed Parameter: ManualSwitch_CurrentSetting
   * Referenced by: '<Root>/Manual Switch'
   */
  0U,

  /* Computed Parameter: ManualSwitch3_CurrentSetting
   * Referenced by: '<Root>/Manual Switch3'
   */
  0U,

  /* Computed Parameter: ManualSwitch1_CurrentSetting
   * Referenced by: '<Root>/Manual Switch1'
   */
  1U,

  /* Computed Parameter: ManualSwitch2_CurrentSetting
   * Referenced by: '<Root>/Manual Switch2'
   */
  0U
};

/* Constant parameters (default storage) */
const ConstP_state_T state_ConstP = {
  /* Expression: A_down-L_down*C
   * Referenced by: '<Root>/State-Space1'
   */
  { 0.0, 0.0, 0.0, 0.0, 146.07908260614067, 27.706739435663511,
    1019.8122903593647, 35.961859948003536, 0.0, 0.0, 0.0, 0.0,
    6.8077610650057405, 0.39917629328120696, 148.68363228080906,
    33.23778433847216 },

  /* Expression: A_up-L_up*C
   * Referenced by: '<Root>/State-Space'
   */
  { 0.0, 0.0, 0.0, 0.0, 619.35402176226853, 53.341201079012322,
    -2034.160209624818, -37.132367502588224, 0.0, 0.0, 0.0, 0.0,
    -103.27483458093444, -4.0057551782714018, 1388.3281082791018,
    67.603322695123182 }
};
