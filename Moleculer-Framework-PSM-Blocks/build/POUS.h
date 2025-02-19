#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// PROGRAM B_PID4_ROUTINE
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(BOOL,ALWAYS_FALSE)
  __DECLARE_EXTERNAL(BOOL,ALIVE)
  __DECLARE_EXTERNAL(BOOL,ALWAYS_TRUE)
  __DECLARE_VAR(REAL,PIT_129)
  __DECLARE_VAR(REAL,PIT_118)
  __DECLARE_VAR(REAL,LIT_125)
  __DECLARE_VAR(REAL,FIT_116)
  __DECLARE_VAR(INT,PUMP_CH)
  __DECLARE_VAR(INT,PUMP_SPEED)
  __DECLARE_VAR(REAL,KP)
  __DECLARE_VAR(REAL,ERROR)
  __DECLARE_VAR(REAL,INTEGRATIVE)
  __DECLARE_VAR(REAL,SETPOINT_GEN)
  __DECLARE_VAR(REAL,TIMEVAR)
  __DECLARE_EXTERNAL(INT,PID_OUT)
  DAQ_AI_I DAQ_AI_I0;
  PID_4_0 PID_4_00;
  DAQ_AO_U_WT DAQ_AO_U_WT0;
  __DECLARE_VAR(INT,_TMP_REAL_TO_INT90_OUT)

} B_PID4_ROUTINE;

void B_PID4_ROUTINE_init__(B_PID4_ROUTINE *data__, BOOL retain);
// Code part
void B_PID4_ROUTINE_body__(B_PID4_ROUTINE *data__);
// PROGRAM A_MAIN_ROUTINE
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(BOOL,ALIVE)
  __DECLARE_VAR(BOOL,ALIVE0)
  TON TON0;
  TON TON1;
  __DECLARE_EXTERNAL(BOOL,ALWAYS_FALSE)
  __DECLARE_EXTERNAL(BOOL,ALWAYS_TRUE)
  __DECLARE_EXTERNAL(REAL,DAQ_AI_I_CH1)
  __DECLARE_EXTERNAL(REAL,DAQ_AI_I_CH2)
  __DECLARE_EXTERNAL(REAL,DAQ_AI_I_CH3)
  __DECLARE_EXTERNAL(REAL,DAQ_AI_I_CH4)
  TON TON2;
  TON TON3;

} A_MAIN_ROUTINE;

void A_MAIN_ROUTINE_init__(A_MAIN_ROUTINE *data__, BOOL retain);
// Code part
void A_MAIN_ROUTINE_body__(A_MAIN_ROUTINE *data__);
#endif //__POUS_H
