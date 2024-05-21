void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void B_PID4_ROUTINE_init__(B_PID4_ROUTINE *data__, BOOL retain) {
  __INIT_EXTERNAL(BOOL,ALWAYS_FALSE,data__->ALWAYS_FALSE,retain)
  __INIT_EXTERNAL(BOOL,ALIVE,data__->ALIVE,retain)
  __INIT_EXTERNAL(BOOL,ALWAYS_TRUE,data__->ALWAYS_TRUE,retain)
  __INIT_VAR(data__->PIT_129,0,retain)
  __INIT_VAR(data__->PIT_118,0,retain)
  __INIT_VAR(data__->LIT_125,0,retain)
  __INIT_VAR(data__->FIT_116,0,retain)
  __INIT_VAR(data__->PUMP_CH,2,retain)
  __INIT_VAR(data__->PUMP_SPEED,0,retain)
  __INIT_VAR(data__->KP,0,retain)
  __INIT_VAR(data__->ERROR,0,retain)
  __INIT_VAR(data__->INTEGRATIVE,0,retain)
  __INIT_VAR(data__->SETPOINT_GEN,0,retain)
  __INIT_VAR(data__->TIMEVAR,0,retain)
  __INIT_EXTERNAL(INT,PID_OUT,data__->PID_OUT,retain)
  DAQ_AI_I_init__(&data__->DAQ_AI_I0,retain);
  PID_4_0_init__(&data__->PID_4_00,retain);
  DAQ_AO_U_WT_init__(&data__->DAQ_AO_U_WT0,retain);
  __INIT_VAR(data__->_TMP_REAL_TO_INT90_OUT,0,retain)
}

// Code part
void B_PID4_ROUTINE_body__(B_PID4_ROUTINE *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->DAQ_AI_I0.,DAQ_AI_I_ENABLE,,__GET_EXTERNAL(data__->ALWAYS_TRUE,));
  __SET_VAR(data__->DAQ_AI_I0.,DAQ_AI_I_STACK,,0);
  __SET_VAR(data__->DAQ_AI_I0.,DAQ_AI_I_CHANNEL,,3);
  DAQ_AI_I_body__(&data__->DAQ_AI_I0);
  __SET_VAR(data__->,LIT_125,,__GET_VAR(data__->DAQ_AI_I0.DAQ_AI_I_ANSWER,));
  __SET_VAR(data__->PID_4_00.,CTRL_LOOP_INDEX,,1);
  __SET_VAR(data__->PID_4_00.,KP,,30.0);
  __SET_VAR(data__->PID_4_00.,TI,,5.0);
  __SET_VAR(data__->PID_4_00.,TD,,0.01);
  __SET_VAR(data__->PID_4_00.,SP,,50.0);
  __SET_VAR(data__->PID_4_00.,PV,,__GET_VAR(data__->LIT_125,));
  PID_4_0_body__(&data__->PID_4_00);
  __SET_VAR(data__->,_TMP_REAL_TO_INT90_OUT,,REAL_TO_INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->PID_4_00.OUT_CV,)));
  __SET_VAR(data__->,PUMP_SPEED,,__GET_VAR(data__->_TMP_REAL_TO_INT90_OUT,));
  __SET_VAR(data__->,INTEGRATIVE,,__GET_VAR(data__->PID_4_00.INTEGRATIVE,));
  __SET_VAR(data__->,TIMEVAR,,__GET_VAR(data__->PID_4_00.TIMEVAR,));
  __SET_EXTERNAL(data__->,PID_OUT,,__GET_VAR(data__->_TMP_REAL_TO_INT90_OUT,));
  __SET_VAR(data__->DAQ_AO_U_WT0.,DAQ_AO_U_WT_ENABLE,,__GET_EXTERNAL(data__->ALWAYS_TRUE,));
  __SET_VAR(data__->DAQ_AO_U_WT0.,DAQ_AO_U_WT_STACK,,0);
  __SET_VAR(data__->DAQ_AO_U_WT0.,DAQ_AO_U_WT_CHANNEL,,2);
  __SET_VAR(data__->DAQ_AO_U_WT0.,DAQ_AO_U_WT_VALUE,,__GET_VAR(data__->PUMP_SPEED,));
  DAQ_AO_U_WT_body__(&data__->DAQ_AO_U_WT0);

  goto __end;

__end:
  return;
} // B_PID4_ROUTINE_body__() 





void A_MAIN_ROUTINE_init__(A_MAIN_ROUTINE *data__, BOOL retain) {
  __INIT_EXTERNAL(BOOL,ALIVE,data__->ALIVE,retain)
  __INIT_VAR(data__->ALIVE0,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON0,retain);
  TON_init__(&data__->TON1,retain);
  __INIT_EXTERNAL(BOOL,ALWAYS_FALSE,data__->ALWAYS_FALSE,retain)
  __INIT_EXTERNAL(BOOL,ALWAYS_TRUE,data__->ALWAYS_TRUE,retain)
  __INIT_EXTERNAL(REAL,DAQ_AI_I_CH1,data__->DAQ_AI_I_CH1,retain)
  __INIT_EXTERNAL(REAL,DAQ_AI_I_CH2,data__->DAQ_AI_I_CH2,retain)
  __INIT_EXTERNAL(REAL,DAQ_AI_I_CH3,data__->DAQ_AI_I_CH3,retain)
  __INIT_EXTERNAL(REAL,DAQ_AI_I_CH4,data__->DAQ_AI_I_CH4,retain)
  TON_init__(&data__->TON2,retain);
  TON_init__(&data__->TON3,retain);
}

// Code part
void A_MAIN_ROUTINE_body__(A_MAIN_ROUTINE *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->TON0.,IN,,!(__GET_VAR(data__->TON1.Q,)));
  __SET_VAR(data__->TON0.,PT,,__time_to_timespec(1, 5000, 0, 0, 0, 0));
  TON_body__(&data__->TON0);
  __SET_EXTERNAL(data__->,ALIVE,,__GET_VAR(data__->TON0.Q,));
  if (__GET_EXTERNAL(data__->ALWAYS_FALSE,)) {
    __SET_EXTERNAL(data__->,ALWAYS_FALSE,,__BOOL_LITERAL(FALSE));
  };
  if (!(__GET_EXTERNAL(data__->ALWAYS_TRUE,))) {
    __SET_EXTERNAL(data__->,ALWAYS_TRUE,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->TON2.,IN,,!(__GET_VAR(data__->TON3.Q,)));
  __SET_VAR(data__->TON2.,PT,,__time_to_timespec(1, 10000, 0, 0, 0, 0));
  TON_body__(&data__->TON2);
  __SET_VAR(data__->,ALIVE0,,__GET_VAR(data__->TON2.Q,));
  __SET_VAR(data__->TON1.,IN,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->TON1.,PT,,__time_to_timespec(1, 5000, 0, 0, 0, 0));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->TON3.,IN,,__GET_VAR(data__->TON2.Q,));
  __SET_VAR(data__->TON3.,PT,,__time_to_timespec(1, 10000, 0, 0, 0, 0));
  TON_body__(&data__->TON3);

  goto __end;

__end:
  return;
} // A_MAIN_ROUTINE_body__() 





