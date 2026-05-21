/*
 * pid_pos_dt.h
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

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(void*),
  sizeof(action_T),
  2*sizeof(uint32_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&pid_pos_B.Step3), 0, 0, 12 },

  { (char_T *)(&pid_pos_B.DataTypeConv2), 2, 0, 1 },

  { (char_T *)(&pid_pos_B.AND3), 8, 0, 1 }
  ,

  { (char_T *)(&pid_pos_DW.TransportDelay_RWORK.modelTStart), 0, 0, 1 },

  { (char_T *)(&pid_pos_DW.TransportDelay_PWORK.TUbufferPtrs[0]), 11, 0, 9 },

  { (char_T *)(&pid_pos_DW.TransportDelay_IWORK.Tail), 10, 0, 1 },

  { (char_T *)(&pid_pos_DW.Memory_PreviousInput), 8, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  7U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&pid_pos_P.Kd), 0, 0, 21 },

  { (char_T *)(&pid_pos_P.DigitalInput_BitMode), 6, 0, 7 },

  { (char_T *)(&pid_pos_P.Saturation_UpperSat), 0, 0, 16 },

  { (char_T *)(&pid_pos_P.Memory_InitialCondition), 8, 0, 1 },

  { (char_T *)(&pid_pos_P.ManualSwitch_CurrentSetting), 3, 0, 2 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  5U,
  rtPTransitions
};

/* [EOF] pid_pos_dt.h */
