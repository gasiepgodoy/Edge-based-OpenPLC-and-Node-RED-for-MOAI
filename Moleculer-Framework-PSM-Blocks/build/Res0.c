/*******************************************/
/*     FILE GENERATED BY iec2c             */
/* Editing this file is not recommended... */
/*******************************************/

#include "iec_std_lib.h"

// RESOURCE RES0

extern unsigned long long common_ticktime__;

#include "accessor.h"
#include "POUS.h"

#include "Config0.h"
__DECLARE_GLOBAL(BOOL,RES0,ALWAYS_FALSE)
__DECLARE_GLOBAL(BOOL,RES0,ALWAYS_TRUE)
__DECLARE_GLOBAL(BOOL,RES0,ALIVE)
__DECLARE_GLOBAL(BOOL,RES0,DAQ_AI_I_ENABLE_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AI_I_STACK_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AI_I_CHANNEL_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AI_I_PSM)
__DECLARE_GLOBAL(REAL,RES0,DAQ_AI_I_CH1)
__DECLARE_GLOBAL(REAL,RES0,DAQ_AI_I_CH2)
__DECLARE_GLOBAL(REAL,RES0,DAQ_AI_I_CH3)
__DECLARE_GLOBAL(REAL,RES0,DAQ_AI_I_CH4)
__DECLARE_GLOBAL(BOOL,RES0,DAQ_AO_U_WT_ENABLE_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_U_WT_STACK_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_U_WT_CHANNEL_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_U_WT_VALUE_PSM)
__DECLARE_GLOBAL(BOOL,RES0,DAQ_AO_U_RD_ENABLE_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_U_RD_STACK_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_U_RD_CHANNEL_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_U_RD_PSM)
__DECLARE_GLOBAL(BOOL,RES0,DAQ_AI_U_ENABLE_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AI_U_STACK_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AI_U_CHANNEL_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AI_U_PSM)
__DECLARE_GLOBAL(BOOL,RES0,DAQ_AO_I_WT_ENABLE_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_I_WT_STACK_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_I_WT_CHANNEL_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_I_WT_VALUE_PSM)
__DECLARE_GLOBAL(BOOL,RES0,DAQ_AO_I_RD_ENABLE_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_I_RD_STACK_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_I_RD_CHANNEL_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_I_RD_PSM)
__DECLARE_GLOBAL(BOOL,RES0,DAQ_AO_OD_WT_ENABLE_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_OD_WT_STACK_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_OD_WT_CHANNEL_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_OD_WT_VALUE_PSM)
__DECLARE_GLOBAL(BOOL,RES0,DAQ_AO_OD_RD_ENABLE_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_OD_RD_STACK_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_OD_RD_CHANNEL_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_AO_OD_RD_PSM)
__DECLARE_GLOBAL(BOOL,RES0,DAQ_DI_OPTO_ENABLE_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_DI_OPTO_STACK_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_DI_OPTO_CHANNEL_PSM)
__DECLARE_GLOBAL(INT,RES0,DAQ_DI_OPTO_PSM)
__DECLARE_GLOBAL(BOOL,RES0,PID4_ENABLED_PSM)
__DECLARE_GLOBAL(INT,RES0,CTRL_LOOP_INDEX_PSM)
__DECLARE_GLOBAL(INT,RES0,KP_PSM)
__DECLARE_GLOBAL(INT,RES0,TI_PSM)
__DECLARE_GLOBAL(INT,RES0,TD_PSM)
__DECLARE_GLOBAL(INT,RES0,PV_PSM)
__DECLARE_GLOBAL(INT,RES0,SP_PSM)
__DECLARE_GLOBAL(INT,RES0,ERROR_PSM)
__DECLARE_GLOBAL(INT,RES0,INTEGRATIVE_PSM)
__DECLARE_GLOBAL(INT,RES0,TIMEPSM)
__DECLARE_GLOBAL(INT,RES0,OUT_CV_PSM)
__DECLARE_GLOBAL(INT,RES0,PID_OUT)

#include "POUS.c"

BOOL MAIN;
A_MAIN_ROUTINE RES0__INSTANCE00;
#define INSTANCE00 RES0__INSTANCE00
B_PID4_ROUTINE RES0__INSTANCE01;
#define INSTANCE01 RES0__INSTANCE01

void RES0_init__(void) {
  BOOL retain;
  retain = 0;
  __INIT_GLOBAL(BOOL,ALWAYS_FALSE,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,ALWAYS_TRUE,__INITIAL_VALUE(1),retain)
  __INIT_GLOBAL(BOOL,ALIVE,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,DAQ_AI_I_ENABLE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AI_I_STACK_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AI_I_CHANNEL_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AI_I_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(REAL,DAQ_AI_I_CH1,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(REAL,DAQ_AI_I_CH2,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(REAL,DAQ_AI_I_CH3,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(REAL,DAQ_AI_I_CH4,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,DAQ_AO_U_WT_ENABLE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_U_WT_STACK_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_U_WT_CHANNEL_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_U_WT_VALUE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,DAQ_AO_U_RD_ENABLE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_U_RD_STACK_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_U_RD_CHANNEL_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_U_RD_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,DAQ_AI_U_ENABLE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AI_U_STACK_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AI_U_CHANNEL_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AI_U_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,DAQ_AO_I_WT_ENABLE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_I_WT_STACK_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_I_WT_CHANNEL_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_I_WT_VALUE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,DAQ_AO_I_RD_ENABLE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_I_RD_STACK_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_I_RD_CHANNEL_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_I_RD_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,DAQ_AO_OD_WT_ENABLE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_OD_WT_STACK_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_OD_WT_CHANNEL_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_OD_WT_VALUE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,DAQ_AO_OD_RD_ENABLE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_OD_RD_STACK_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_OD_RD_CHANNEL_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_AO_OD_RD_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,DAQ_DI_OPTO_ENABLE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_DI_OPTO_STACK_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_DI_OPTO_CHANNEL_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,DAQ_DI_OPTO_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,PID4_ENABLED_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,CTRL_LOOP_INDEX_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,KP_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,TI_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,TD_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,PV_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,SP_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,ERROR_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,INTEGRATIVE_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,TIMEPSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,OUT_CV_PSM,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,PID_OUT,__INITIAL_VALUE(0),retain)
  MAIN = __BOOL_LITERAL(FALSE);
  A_MAIN_ROUTINE_init__(&INSTANCE00,retain);
  B_PID4_ROUTINE_init__(&INSTANCE01,retain);
}

void RES0_run__(unsigned long tick) {
  MAIN = !(tick % 1);
  if (MAIN) {
    A_MAIN_ROUTINE_body__(&INSTANCE00);
  }
  if (MAIN) {
    B_PID4_ROUTINE_body__(&INSTANCE01);
  }
}

