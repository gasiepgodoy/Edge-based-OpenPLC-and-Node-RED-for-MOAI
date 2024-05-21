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





static inline REAL __DAQ_AI_I_INT_TO_REAL1(BOOL EN,
  INT IN,
  DAQ_AI_I *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_INT_TO_REAL12_ENO,);
  __res = INT_TO_REAL(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_INT_TO_REAL12_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_AI_I_DIV__REAL__REAL__REAL2(BOOL EN,
  REAL IN1,
  REAL IN2,
  DAQ_AI_I *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV11_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV11_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AI_I_MOVE__INT__INT3(BOOL EN,
  INT IN,
  DAQ_AI_I *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE81_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE81_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AI_I_MOVE__INT__INT4(BOOL EN,
  INT IN,
  DAQ_AI_I *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE9_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE9_ENO,,__TMP_ENO);
  return __res;
}

void DAQ_AI_I_init__(DAQ_AI_I *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->DAQ_AI_I_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_AI_I_STACK,0,retain)
  __INIT_VAR(data__->DAQ_AI_I_CHANNEL,0,retain)
  __INIT_VAR(data__->DAQ_AI_I_ANSWER,0,retain)
  __INIT_EXTERNAL(BOOL,DAQ_AI_I_ENABLE_PSM,data__->DAQ_AI_I_ENABLE_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AI_I_STACK_PSM,data__->DAQ_AI_I_STACK_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AI_I_CHANNEL_PSM,data__->DAQ_AI_I_CHANNEL_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AI_I_PSM,data__->DAQ_AI_I_PSM,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV11_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV11_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE81_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE9_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE9_OUT,0,retain)
}

// Code part
void DAQ_AI_I_body__(DAQ_AI_I *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_INT_TO_REAL12_OUT,,__DAQ_AI_I_INT_TO_REAL1(
    (BOOL)__GET_VAR(data__->DAQ_AI_I_ENABLE,),
    (INT)__GET_EXTERNAL(data__->DAQ_AI_I_PSM,),
    data__));
  __SET_VAR(data__->,_TMP_DIV11_OUT,,__DAQ_AI_I_DIV__REAL__REAL__REAL2(
    (BOOL)__GET_VAR(data__->DAQ_AI_I_ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL12_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV11_ENO,)) {
    __SET_VAR(data__->,DAQ_AI_I_ANSWER,,__GET_VAR(data__->_TMP_DIV11_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE81_OUT,,__DAQ_AI_I_MOVE__INT__INT3(
    (BOOL)__GET_VAR(data__->DAQ_AI_I_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AI_I_STACK,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE81_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AI_I_STACK_PSM,,__GET_VAR(data__->_TMP_MOVE81_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE9_OUT,,__DAQ_AI_I_MOVE__INT__INT4(
    (BOOL)__GET_VAR(data__->DAQ_AI_I_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AI_I_CHANNEL,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE9_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AI_I_CHANNEL_PSM,,__GET_VAR(data__->_TMP_MOVE9_OUT,));
  };
  __SET_EXTERNAL(data__->,DAQ_AI_I_ENABLE_PSM,,__GET_VAR(data__->DAQ_AI_I_ENABLE,));

  goto __end;

__end:
  return;
} // DAQ_AI_I_body__() 





static inline REAL __DAQ_AI_U_INT_TO_REAL1(BOOL EN,
  INT IN,
  DAQ_AI_U *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_INT_TO_REAL12_ENO,);
  __res = INT_TO_REAL(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_INT_TO_REAL12_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_AI_U_DIV__REAL__REAL__REAL2(BOOL EN,
  REAL IN1,
  REAL IN2,
  DAQ_AI_U *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV11_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV11_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AI_U_MOVE__INT__INT3(BOOL EN,
  INT IN,
  DAQ_AI_U *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE81_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE81_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AI_U_MOVE__INT__INT4(BOOL EN,
  INT IN,
  DAQ_AI_U *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE9_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE9_ENO,,__TMP_ENO);
  return __res;
}

void DAQ_AI_U_init__(DAQ_AI_U *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->DAQ_AI_U_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_AI_U_STACK,0,retain)
  __INIT_VAR(data__->DAQ_AI_U_CHANNEL,0,retain)
  __INIT_VAR(data__->DAQ_AI_U_ANSWER,0,retain)
  __INIT_VAR(data__->DAQ_AI_U_ENABLE_PSM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_AI_U_STACK_PSM,0,retain)
  __INIT_VAR(data__->DAQ_AI_U_CHANNEL_PSM,0,retain)
  __INIT_VAR(data__->DAQ_AI_U_PSM,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV11_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV11_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE81_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE9_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE9_OUT,0,retain)
}

// Code part
void DAQ_AI_U_body__(DAQ_AI_U *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_INT_TO_REAL12_OUT,,__DAQ_AI_U_INT_TO_REAL1(
    (BOOL)__GET_VAR(data__->DAQ_AI_U_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AI_U_PSM,),
    data__));
  __SET_VAR(data__->,_TMP_DIV11_OUT,,__DAQ_AI_U_DIV__REAL__REAL__REAL2(
    (BOOL)__GET_VAR(data__->DAQ_AI_U_ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL12_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV11_ENO,)) {
    __SET_VAR(data__->,DAQ_AI_U_ANSWER,,__GET_VAR(data__->_TMP_DIV11_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE81_OUT,,__DAQ_AI_U_MOVE__INT__INT3(
    (BOOL)__GET_VAR(data__->DAQ_AI_U_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AI_U_STACK,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE81_ENO,)) {
    __SET_VAR(data__->,DAQ_AI_U_STACK_PSM,,__GET_VAR(data__->_TMP_MOVE81_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE9_OUT,,__DAQ_AI_U_MOVE__INT__INT4(
    (BOOL)__GET_VAR(data__->DAQ_AI_U_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AI_U_CHANNEL,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE9_ENO,)) {
    __SET_VAR(data__->,DAQ_AI_U_CHANNEL_PSM,,__GET_VAR(data__->_TMP_MOVE9_OUT,));
  };
  __SET_VAR(data__->,DAQ_AI_U_ENABLE_PSM,,__GET_VAR(data__->DAQ_AI_U_ENABLE,));

  goto __end;

__end:
  return;
} // DAQ_AI_U_body__() 





static inline INT __DAQ_DI_OPTO_MOVE__INT__INT1(BOOL EN,
  INT IN,
  DAQ_DI_OPTO *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE81_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE81_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_DI_OPTO_MOVE__INT__INT2(BOOL EN,
  INT IN,
  DAQ_DI_OPTO *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE9_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE9_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_DI_OPTO_INT_TO_REAL3(BOOL EN,
  INT IN,
  DAQ_DI_OPTO *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_INT_TO_REAL12_ENO,);
  __res = INT_TO_REAL(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_INT_TO_REAL12_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_DI_OPTO_DIV__REAL__REAL__REAL4(BOOL EN,
  REAL IN1,
  REAL IN2,
  DAQ_DI_OPTO *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV19_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV19_ENO,,__TMP_ENO);
  return __res;
}

void DAQ_DI_OPTO_init__(DAQ_DI_OPTO *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->DAQ_DI_OPTO_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_DI_OPTO_STACK,0,retain)
  __INIT_VAR(data__->DAQ_DI_OPTO_CHANNEL,0,retain)
  __INIT_VAR(data__->DAQ_DI_OPTO_ANSWER,0,retain)
  __INIT_EXTERNAL(BOOL,DAQ_DI_OPTO_ENABLE_PSM,data__->DAQ_DI_OPTO_ENABLE_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_DI_OPTO_STACK_PSM,data__->DAQ_DI_OPTO_STACK_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_DI_OPTO_CHANNEL_PSM,data__->DAQ_DI_OPTO_CHANNEL_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_DI_OPTO_PSM,data__->DAQ_DI_OPTO_PSM,retain)
  __INIT_VAR(data__->_TMP_MOVE81_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE9_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE9_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV19_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV19_OUT,0,retain)
}

// Code part
void DAQ_DI_OPTO_body__(DAQ_DI_OPTO *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_MOVE81_OUT,,__DAQ_DI_OPTO_MOVE__INT__INT1(
    (BOOL)__GET_VAR(data__->DAQ_DI_OPTO_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_DI_OPTO_STACK,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE81_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_DI_OPTO_STACK_PSM,,__GET_VAR(data__->_TMP_MOVE81_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE9_OUT,,__DAQ_DI_OPTO_MOVE__INT__INT2(
    (BOOL)__GET_VAR(data__->DAQ_DI_OPTO_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_DI_OPTO_CHANNEL,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE9_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_DI_OPTO_CHANNEL_PSM,,__GET_VAR(data__->_TMP_MOVE9_OUT,));
  };
  __SET_VAR(data__->,_TMP_INT_TO_REAL12_OUT,,__DAQ_DI_OPTO_INT_TO_REAL3(
    (BOOL)__GET_VAR(data__->DAQ_DI_OPTO_ENABLE,),
    (INT)__GET_EXTERNAL(data__->DAQ_DI_OPTO_PSM,),
    data__));
  __SET_VAR(data__->,_TMP_DIV19_OUT,,__DAQ_DI_OPTO_DIV__REAL__REAL__REAL4(
    (BOOL)__GET_VAR(data__->DAQ_DI_OPTO_ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL12_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV19_ENO,)) {
    __SET_VAR(data__->,DAQ_DI_OPTO_ANSWER,,__GET_VAR(data__->_TMP_DIV19_OUT,));
  };
  __SET_EXTERNAL(data__->,DAQ_DI_OPTO_ENABLE_PSM,,__GET_VAR(data__->DAQ_DI_OPTO_ENABLE,));

  goto __end;

__end:
  return;
} // DAQ_DI_OPTO_body__() 





static inline INT __DAQ_AO_I_RD_MOVE__INT__INT1(BOOL EN,
  INT IN,
  DAQ_AO_I_RD *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE81_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE81_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_I_RD_MOVE__INT__INT2(BOOL EN,
  INT IN,
  DAQ_AO_I_RD *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE9_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE9_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_AO_I_RD_INT_TO_REAL3(BOOL EN,
  INT IN,
  DAQ_AO_I_RD *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_INT_TO_REAL12_ENO,);
  __res = INT_TO_REAL(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_INT_TO_REAL12_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_AO_I_RD_DIV__REAL__REAL__REAL4(BOOL EN,
  REAL IN1,
  REAL IN2,
  DAQ_AO_I_RD *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV19_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV19_ENO,,__TMP_ENO);
  return __res;
}

void DAQ_AO_I_RD_init__(DAQ_AO_I_RD *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->DAQ_AO_I_RD_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_AO_I_RD_STACK,0,retain)
  __INIT_VAR(data__->DAQ_AO_I_RD_CHANNEL,0,retain)
  __INIT_VAR(data__->DAQ_AO_I_RD_ANSWER,0,retain)
  __INIT_EXTERNAL(BOOL,DAQ_AO_I_RD_ENABLE_PSM,data__->DAQ_AO_I_RD_ENABLE_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_I_RD_STACK_PSM,data__->DAQ_AO_I_RD_STACK_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_I_RD_CHANNEL_PSM,data__->DAQ_AO_I_RD_CHANNEL_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_I_RD_PSM,data__->DAQ_AO_I_RD_PSM,retain)
  __INIT_VAR(data__->_TMP_MOVE81_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE9_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE9_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV19_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV19_OUT,0,retain)
}

// Code part
void DAQ_AO_I_RD_body__(DAQ_AO_I_RD *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_MOVE81_OUT,,__DAQ_AO_I_RD_MOVE__INT__INT1(
    (BOOL)__GET_VAR(data__->DAQ_AO_I_RD_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_I_RD_STACK,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE81_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_I_RD_STACK_PSM,,__GET_VAR(data__->_TMP_MOVE81_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE9_OUT,,__DAQ_AO_I_RD_MOVE__INT__INT2(
    (BOOL)__GET_VAR(data__->DAQ_AO_I_RD_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_I_RD_CHANNEL,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE9_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_I_RD_CHANNEL_PSM,,__GET_VAR(data__->_TMP_MOVE9_OUT,));
  };
  __SET_VAR(data__->,_TMP_INT_TO_REAL12_OUT,,__DAQ_AO_I_RD_INT_TO_REAL3(
    (BOOL)__GET_VAR(data__->DAQ_AO_I_RD_ENABLE,),
    (INT)__GET_EXTERNAL(data__->DAQ_AO_I_RD_PSM,),
    data__));
  __SET_VAR(data__->,_TMP_DIV19_OUT,,__DAQ_AO_I_RD_DIV__REAL__REAL__REAL4(
    (BOOL)__GET_VAR(data__->DAQ_AO_I_RD_ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL12_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV19_ENO,)) {
    __SET_VAR(data__->,DAQ_AO_I_RD_ANSWER,,__GET_VAR(data__->_TMP_DIV19_OUT,));
  };
  __SET_EXTERNAL(data__->,DAQ_AO_I_RD_ENABLE_PSM,,__GET_VAR(data__->DAQ_AO_I_RD_ENABLE,));

  goto __end;

__end:
  return;
} // DAQ_AO_I_RD_body__() 





static inline INT __DAQ_AO_U_RD_MOVE__INT__INT1(BOOL EN,
  INT IN,
  DAQ_AO_U_RD *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE81_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE81_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_U_RD_MOVE__INT__INT2(BOOL EN,
  INT IN,
  DAQ_AO_U_RD *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE9_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE9_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_AO_U_RD_INT_TO_REAL3(BOOL EN,
  INT IN,
  DAQ_AO_U_RD *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_INT_TO_REAL12_ENO,);
  __res = INT_TO_REAL(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_INT_TO_REAL12_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_AO_U_RD_DIV__REAL__REAL__REAL4(BOOL EN,
  REAL IN1,
  REAL IN2,
  DAQ_AO_U_RD *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV19_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV19_ENO,,__TMP_ENO);
  return __res;
}

void DAQ_AO_U_RD_init__(DAQ_AO_U_RD *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->DAQ_AO_U_RD_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_AO_U_RD_STACK,0,retain)
  __INIT_VAR(data__->DAQ_AO_U_RD_CHANNEL,0,retain)
  __INIT_VAR(data__->DAQ_AO_U_RD_ANSWER,0,retain)
  __INIT_EXTERNAL(BOOL,DAQ_AO_U_RD_ENABLE_PSM,data__->DAQ_AO_U_RD_ENABLE_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_U_RD_STACK_PSM,data__->DAQ_AO_U_RD_STACK_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_U_RD_CHANNEL_PSM,data__->DAQ_AO_U_RD_CHANNEL_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_U_RD_PSM,data__->DAQ_AO_U_RD_PSM,retain)
  __INIT_VAR(data__->_TMP_MOVE81_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE9_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE9_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV19_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV19_OUT,0,retain)
}

// Code part
void DAQ_AO_U_RD_body__(DAQ_AO_U_RD *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_MOVE81_OUT,,__DAQ_AO_U_RD_MOVE__INT__INT1(
    (BOOL)__GET_VAR(data__->DAQ_AO_U_RD_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_U_RD_STACK,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE81_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_U_RD_STACK_PSM,,__GET_VAR(data__->_TMP_MOVE81_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE9_OUT,,__DAQ_AO_U_RD_MOVE__INT__INT2(
    (BOOL)__GET_VAR(data__->DAQ_AO_U_RD_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_U_RD_CHANNEL,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE9_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_U_RD_CHANNEL_PSM,,__GET_VAR(data__->_TMP_MOVE9_OUT,));
  };
  __SET_VAR(data__->,_TMP_INT_TO_REAL12_OUT,,__DAQ_AO_U_RD_INT_TO_REAL3(
    (BOOL)__GET_VAR(data__->DAQ_AO_U_RD_ENABLE,),
    (INT)__GET_EXTERNAL(data__->DAQ_AO_U_RD_PSM,),
    data__));
  __SET_VAR(data__->,_TMP_DIV19_OUT,,__DAQ_AO_U_RD_DIV__REAL__REAL__REAL4(
    (BOOL)__GET_VAR(data__->DAQ_AO_U_RD_ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL12_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV19_ENO,)) {
    __SET_VAR(data__->,DAQ_AO_U_RD_ANSWER,,__GET_VAR(data__->_TMP_DIV19_OUT,));
  };
  __SET_EXTERNAL(data__->,DAQ_AO_U_RD_ENABLE_PSM,,__GET_VAR(data__->DAQ_AO_U_RD_ENABLE,));

  goto __end;

__end:
  return;
} // DAQ_AO_U_RD_body__() 





static inline INT __DAQ_AO_OD_RD_MOVE__INT__INT1(BOOL EN,
  INT IN,
  DAQ_AO_OD_RD *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE81_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE81_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_OD_RD_MOVE__INT__INT2(BOOL EN,
  INT IN,
  DAQ_AO_OD_RD *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE9_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE9_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_AO_OD_RD_INT_TO_REAL3(BOOL EN,
  INT IN,
  DAQ_AO_OD_RD *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_INT_TO_REAL12_ENO,);
  __res = INT_TO_REAL(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_INT_TO_REAL12_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __DAQ_AO_OD_RD_DIV__REAL__REAL__REAL4(BOOL EN,
  REAL IN1,
  REAL IN2,
  DAQ_AO_OD_RD *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV19_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV19_ENO,,__TMP_ENO);
  return __res;
}

void DAQ_AO_OD_RD_init__(DAQ_AO_OD_RD *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->DAQ_AO_OD_RD_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_AO_OD_RD_STACK,0,retain)
  __INIT_VAR(data__->DAQ_AO_OD_RD_CHANNEL,0,retain)
  __INIT_VAR(data__->DAQ_AO_OD_RD_ANSWER,0,retain)
  __INIT_EXTERNAL(BOOL,DAQ_AO_OD_RD_ENABLE_PSM,data__->DAQ_AO_OD_RD_ENABLE_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_OD_RD_STACK_PSM,data__->DAQ_AO_OD_RD_STACK_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_OD_RD_CHANNEL_PSM,data__->DAQ_AO_OD_RD_CHANNEL_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_OD_RD_PSM,data__->DAQ_AO_OD_RD_PSM,retain)
  __INIT_VAR(data__->_TMP_MOVE81_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE9_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE9_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL12_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV19_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV19_OUT,0,retain)
}

// Code part
void DAQ_AO_OD_RD_body__(DAQ_AO_OD_RD *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_MOVE81_OUT,,__DAQ_AO_OD_RD_MOVE__INT__INT1(
    (BOOL)__GET_VAR(data__->DAQ_AO_OD_RD_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_OD_RD_STACK,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE81_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_OD_RD_STACK_PSM,,__GET_VAR(data__->_TMP_MOVE81_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE9_OUT,,__DAQ_AO_OD_RD_MOVE__INT__INT2(
    (BOOL)__GET_VAR(data__->DAQ_AO_OD_RD_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_OD_RD_CHANNEL,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE9_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_OD_RD_CHANNEL_PSM,,__GET_VAR(data__->_TMP_MOVE9_OUT,));
  };
  __SET_VAR(data__->,_TMP_INT_TO_REAL12_OUT,,__DAQ_AO_OD_RD_INT_TO_REAL3(
    (BOOL)__GET_VAR(data__->DAQ_AO_OD_RD_ENABLE,),
    (INT)__GET_EXTERNAL(data__->DAQ_AO_OD_RD_PSM,),
    data__));
  __SET_VAR(data__->,_TMP_DIV19_OUT,,__DAQ_AO_OD_RD_DIV__REAL__REAL__REAL4(
    (BOOL)__GET_VAR(data__->DAQ_AO_OD_RD_ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL12_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV19_ENO,)) {
    __SET_VAR(data__->,DAQ_AO_OD_RD_ANSWER,,__GET_VAR(data__->_TMP_DIV19_OUT,));
  };
  __SET_EXTERNAL(data__->,DAQ_AO_OD_RD_ENABLE_PSM,,__GET_VAR(data__->DAQ_AO_OD_RD_ENABLE,));

  goto __end;

__end:
  return;
} // DAQ_AO_OD_RD_body__() 





static inline INT __DAQ_AO_U_WT_MOVE__INT__INT1(BOOL EN,
  INT IN,
  DAQ_AO_U_WT *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE81_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE81_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_U_WT_MOVE__INT__INT2(BOOL EN,
  INT IN,
  DAQ_AO_U_WT *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE9_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE9_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_U_WT_MOVE__INT__INT3(BOOL EN,
  INT IN,
  DAQ_AO_U_WT *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE12_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE12_ENO,,__TMP_ENO);
  return __res;
}

void DAQ_AO_U_WT_init__(DAQ_AO_U_WT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->DAQ_AO_U_WT_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_AO_U_WT_STACK,0,retain)
  __INIT_VAR(data__->DAQ_AO_U_WT_CHANNEL,0,retain)
  __INIT_VAR(data__->DAQ_AO_U_WT_VALUE,0,retain)
  __INIT_EXTERNAL(BOOL,DAQ_AO_U_WT_ENABLE_PSM,data__->DAQ_AO_U_WT_ENABLE_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_U_WT_STACK_PSM,data__->DAQ_AO_U_WT_STACK_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_U_WT_CHANNEL_PSM,data__->DAQ_AO_U_WT_CHANNEL_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_U_WT_VALUE_PSM,data__->DAQ_AO_U_WT_VALUE_PSM,retain)
  __INIT_VAR(data__->_TMP_MOVE81_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE9_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE9_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE12_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE12_OUT,0,retain)
}

// Code part
void DAQ_AO_U_WT_body__(DAQ_AO_U_WT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_MOVE81_OUT,,__DAQ_AO_U_WT_MOVE__INT__INT1(
    (BOOL)__GET_VAR(data__->DAQ_AO_U_WT_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_U_WT_STACK,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE81_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_U_WT_STACK_PSM,,__GET_VAR(data__->_TMP_MOVE81_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE9_OUT,,__DAQ_AO_U_WT_MOVE__INT__INT2(
    (BOOL)__GET_VAR(data__->DAQ_AO_U_WT_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_U_WT_CHANNEL,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE9_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_U_WT_CHANNEL_PSM,,__GET_VAR(data__->_TMP_MOVE9_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE12_OUT,,__DAQ_AO_U_WT_MOVE__INT__INT3(
    (BOOL)__GET_VAR(data__->DAQ_AO_U_WT_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_U_WT_VALUE,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE12_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_U_WT_VALUE_PSM,,__GET_VAR(data__->_TMP_MOVE12_OUT,));
  };
  __SET_EXTERNAL(data__->,DAQ_AO_U_WT_ENABLE_PSM,,__GET_VAR(data__->DAQ_AO_U_WT_ENABLE,));

  goto __end;

__end:
  return;
} // DAQ_AO_U_WT_body__() 





static inline BOOL __DAQ_AO_I_WT_MOVE__BOOL__BOOL1(BOOL EN,
  BOOL IN,
  DAQ_AO_I_WT *data__)
{
  BOOL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE5_ENO,);
  __res = MOVE__BOOL__BOOL(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE5_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_I_WT_MOVE__INT__INT2(BOOL EN,
  INT IN,
  DAQ_AO_I_WT *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE81_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE81_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_I_WT_MOVE__INT__INT3(BOOL EN,
  INT IN,
  DAQ_AO_I_WT *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE9_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE9_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_I_WT_MOVE__INT__INT4(BOOL EN,
  INT IN,
  DAQ_AO_I_WT *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE12_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE12_ENO,,__TMP_ENO);
  return __res;
}

void DAQ_AO_I_WT_init__(DAQ_AO_I_WT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->DAQ_AO_I_WT_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_AO_I_WT_STACK,0,retain)
  __INIT_VAR(data__->DAQ_AO_I_WT_CHANNEL,0,retain)
  __INIT_VAR(data__->DAQ_AO_I_WT_VALUE,0,retain)
  __INIT_EXTERNAL(BOOL,DAQ_AO_I_WT_ENABLE_PSM,data__->DAQ_AO_I_WT_ENABLE_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_I_WT_STACK_PSM,data__->DAQ_AO_I_WT_STACK_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_I_WT_CHANNEL_PSM,data__->DAQ_AO_I_WT_CHANNEL_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_I_WT_VALUE_PSM,data__->DAQ_AO_I_WT_VALUE_PSM,retain)
  __INIT_VAR(data__->_TMP_MOVE5_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE5_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE9_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE9_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE12_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE12_OUT,0,retain)
}

// Code part
void DAQ_AO_I_WT_body__(DAQ_AO_I_WT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_MOVE5_OUT,,__DAQ_AO_I_WT_MOVE__BOOL__BOOL1(
    (BOOL)__GET_VAR(data__->DAQ_AO_I_WT_ENABLE,),
    (BOOL)1,
    data__));
  if (__GET_VAR(data__->_TMP_MOVE5_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_I_WT_ENABLE_PSM,,__GET_VAR(data__->_TMP_MOVE5_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE81_OUT,,__DAQ_AO_I_WT_MOVE__INT__INT2(
    (BOOL)__GET_VAR(data__->DAQ_AO_I_WT_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_I_WT_STACK,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE81_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_I_WT_STACK_PSM,,__GET_VAR(data__->_TMP_MOVE81_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE9_OUT,,__DAQ_AO_I_WT_MOVE__INT__INT3(
    (BOOL)__GET_VAR(data__->DAQ_AO_I_WT_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_I_WT_CHANNEL,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE9_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_I_WT_CHANNEL_PSM,,__GET_VAR(data__->_TMP_MOVE9_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE12_OUT,,__DAQ_AO_I_WT_MOVE__INT__INT4(
    (BOOL)__GET_VAR(data__->DAQ_AO_I_WT_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_I_WT_VALUE,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE12_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_I_WT_VALUE_PSM,,__GET_VAR(data__->_TMP_MOVE12_OUT,));
  };
  __SET_EXTERNAL(data__->,DAQ_AO_I_WT_ENABLE_PSM,,__GET_VAR(data__->DAQ_AO_I_WT_ENABLE,));

  goto __end;

__end:
  return;
} // DAQ_AO_I_WT_body__() 





static inline INT __DAQ_AO_OD_WT_MOVE__INT__INT1(BOOL EN,
  INT IN,
  DAQ_AO_OD_WT *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE81_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE81_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_OD_WT_MOVE__INT__INT2(BOOL EN,
  INT IN,
  DAQ_AO_OD_WT *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE9_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE9_ENO,,__TMP_ENO);
  return __res;
}

static inline INT __DAQ_AO_OD_WT_MOVE__INT__INT3(BOOL EN,
  INT IN,
  DAQ_AO_OD_WT *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE12_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE12_ENO,,__TMP_ENO);
  return __res;
}

void DAQ_AO_OD_WT_init__(DAQ_AO_OD_WT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->DAQ_AO_OD_WT_ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DAQ_AO_OD_WT_STACK,0,retain)
  __INIT_VAR(data__->DAQ_AO_OD_WT_CHANNEL,0,retain)
  __INIT_VAR(data__->DAQ_AO_OD_WT_VALUE,0,retain)
  __INIT_EXTERNAL(BOOL,DAQ_AO_OD_WT_ENABLE_PSM,data__->DAQ_AO_OD_WT_ENABLE_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_OD_WT_STACK_PSM,data__->DAQ_AO_OD_WT_STACK_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_OD_WT_CHANNEL_PSM,data__->DAQ_AO_OD_WT_CHANNEL_PSM,retain)
  __INIT_EXTERNAL(INT,DAQ_AO_OD_WT_VALUE_PSM,data__->DAQ_AO_OD_WT_VALUE_PSM,retain)
  __INIT_VAR(data__->_TMP_MOVE81_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE81_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE9_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE9_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MOVE12_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE12_OUT,0,retain)
}

// Code part
void DAQ_AO_OD_WT_body__(DAQ_AO_OD_WT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_MOVE81_OUT,,__DAQ_AO_OD_WT_MOVE__INT__INT1(
    (BOOL)__GET_VAR(data__->DAQ_AO_OD_WT_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_OD_WT_STACK,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE81_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_OD_WT_STACK_PSM,,__GET_VAR(data__->_TMP_MOVE81_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE9_OUT,,__DAQ_AO_OD_WT_MOVE__INT__INT2(
    (BOOL)__GET_VAR(data__->DAQ_AO_OD_WT_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_OD_WT_CHANNEL,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE9_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_OD_WT_CHANNEL_PSM,,__GET_VAR(data__->_TMP_MOVE9_OUT,));
  };
  __SET_VAR(data__->,_TMP_MOVE12_OUT,,__DAQ_AO_OD_WT_MOVE__INT__INT3(
    (BOOL)__GET_VAR(data__->DAQ_AO_OD_WT_ENABLE,),
    (INT)__GET_VAR(data__->DAQ_AO_OD_WT_VALUE,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE12_ENO,)) {
    __SET_EXTERNAL(data__->,DAQ_AO_OD_WT_VALUE_PSM,,__GET_VAR(data__->_TMP_MOVE12_OUT,));
  };
  __SET_EXTERNAL(data__->,DAQ_AO_OD_WT_ENABLE_PSM,,__GET_VAR(data__->DAQ_AO_OD_WT_ENABLE,));

  goto __end;

__end:
  return;
} // DAQ_AO_OD_WT_body__() 





static inline INT __PID_4_0_MOVE__INT__INT1(BOOL EN,
  INT IN,
  PID_4_0 *data__)
{
  INT __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MOVE7_ENO,);
  __res = MOVE__INT__INT(EN,
    &__TMP_ENO,
    IN);
  __SET_VAR(,data__->_TMP_MOVE7_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PID_4_0_MUL__REAL__REAL2(BOOL EN,
  UINT __PARAM_COUNT,
  REAL IN1,
  REAL IN2,
  PID_4_0 *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MUL18_ENO,);
  __res = MUL__REAL__REAL(EN,
    &__TMP_ENO,
    __PARAM_COUNT,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_MUL18_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PID_4_0_MUL__REAL__REAL3(BOOL EN,
  UINT __PARAM_COUNT,
  REAL IN1,
  REAL IN2,
  PID_4_0 *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MUL37_ENO,);
  __res = MUL__REAL__REAL(EN,
    &__TMP_ENO,
    __PARAM_COUNT,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_MUL37_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PID_4_0_MUL__REAL__REAL4(BOOL EN,
  UINT __PARAM_COUNT,
  REAL IN1,
  REAL IN2,
  PID_4_0 *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MUL28_ENO,);
  __res = MUL__REAL__REAL(EN,
    &__TMP_ENO,
    __PARAM_COUNT,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_MUL28_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PID_4_0_MUL__REAL__REAL5(BOOL EN,
  UINT __PARAM_COUNT,
  REAL IN1,
  REAL IN2,
  PID_4_0 *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MUL29_ENO,);
  __res = MUL__REAL__REAL(EN,
    &__TMP_ENO,
    __PARAM_COUNT,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_MUL29_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PID_4_0_MUL__REAL__REAL6(BOOL EN,
  UINT __PARAM_COUNT,
  REAL IN1,
  REAL IN2,
  PID_4_0 *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_MUL34_ENO,);
  __res = MUL__REAL__REAL(EN,
    &__TMP_ENO,
    __PARAM_COUNT,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_MUL34_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PID_4_0_DIV__REAL__REAL__REAL7(BOOL EN,
  REAL IN1,
  REAL IN2,
  PID_4_0 *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV38_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV38_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PID_4_0_DIV__REAL__REAL__REAL8(BOOL EN,
  REAL IN1,
  REAL IN2,
  PID_4_0 *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV43_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV43_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PID_4_0_DIV__REAL__REAL__REAL9(BOOL EN,
  REAL IN1,
  REAL IN2,
  PID_4_0 *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV53_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV53_ENO,,__TMP_ENO);
  return __res;
}

static inline REAL __PID_4_0_DIV__REAL__REAL__REAL10(BOOL EN,
  REAL IN1,
  REAL IN2,
  PID_4_0 *data__)
{
  REAL __res;
  BOOL __TMP_ENO = __GET_VAR(data__->_TMP_DIV48_ENO,);
  __res = DIV__REAL__REAL__REAL(EN,
    &__TMP_ENO,
    IN1,
    IN2);
  __SET_VAR(,data__->_TMP_DIV48_ENO,,__TMP_ENO);
  return __res;
}

void PID_4_0_init__(PID_4_0 *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,PID4_ENABLED_PSM,data__->PID4_ENABLED_PSM,retain)
  __INIT_EXTERNAL(INT,CTRL_LOOP_INDEX_PSM,data__->CTRL_LOOP_INDEX_PSM,retain)
  __INIT_EXTERNAL(INT,KP_PSM,data__->KP_PSM,retain)
  __INIT_EXTERNAL(INT,TI_PSM,data__->TI_PSM,retain)
  __INIT_EXTERNAL(INT,TD_PSM,data__->TD_PSM,retain)
  __INIT_EXTERNAL(INT,PV_PSM,data__->PV_PSM,retain)
  __INIT_EXTERNAL(INT,SP_PSM,data__->SP_PSM,retain)
  __INIT_EXTERNAL(INT,ERROR_PSM,data__->ERROR_PSM,retain)
  __INIT_EXTERNAL(INT,INTEGRATIVE_PSM,data__->INTEGRATIVE_PSM,retain)
  __INIT_EXTERNAL(INT,TIMEPSM,data__->TIMEPSM,retain)
  __INIT_EXTERNAL(INT,OUT_CV_PSM,data__->OUT_CV_PSM,retain)
  __INIT_VAR(data__->CTRL_LOOP_INDEX,0,retain)
  __INIT_VAR(data__->KP,0,retain)
  __INIT_VAR(data__->TI,0,retain)
  __INIT_VAR(data__->TD,0,retain)
  __INIT_VAR(data__->SP,0,retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->ERROR,0,retain)
  __INIT_VAR(data__->INTEGRATIVE,0,retain)
  __INIT_VAR(data__->TIMEVAR,0,retain)
  __INIT_VAR(data__->OUT_CV,0,retain)
  __INIT_VAR(data__->_TMP_MOVE7_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MOVE7_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL18_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MUL18_OUT,0,retain)
  __INIT_VAR(data__->_TMP_REAL_TO_INT12_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL37_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MUL37_OUT,0,retain)
  __INIT_VAR(data__->_TMP_REAL_TO_INT15_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL28_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MUL28_OUT,0,retain)
  __INIT_VAR(data__->_TMP_REAL_TO_INT21_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL29_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MUL29_OUT,0,retain)
  __INIT_VAR(data__->_TMP_REAL_TO_INT24_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL34_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MUL34_OUT,0,retain)
  __INIT_VAR(data__->_TMP_REAL_TO_INT31_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL39_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV38_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV38_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL44_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV43_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV43_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL54_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV53_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV53_OUT,0,retain)
  __INIT_VAR(data__->_TMP_INT_TO_REAL49_OUT,0,retain)
  __INIT_VAR(data__->_TMP_DIV48_ENO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_DIV48_OUT,0,retain)
}

// Code part
void PID_4_0_body__(PID_4_0 *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_MOVE7_OUT,,__PID_4_0_MOVE__INT__INT1(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (INT)__GET_VAR(data__->CTRL_LOOP_INDEX,),
    data__));
  if (__GET_VAR(data__->_TMP_MOVE7_ENO,)) {
    __SET_EXTERNAL(data__->,CTRL_LOOP_INDEX_PSM,,__GET_VAR(data__->_TMP_MOVE7_OUT,));
  };
  __SET_VAR(data__->,_TMP_MUL18_OUT,,__PID_4_0_MUL__REAL__REAL2(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (UINT)2,
    (REAL)__GET_VAR(data__->TI,),
    (REAL)100.0,
    data__));
  __SET_VAR(data__->,_TMP_REAL_TO_INT12_OUT,,REAL_TO_INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->_TMP_MUL18_OUT,)));
  __SET_EXTERNAL(data__->,TI_PSM,,__GET_VAR(data__->_TMP_REAL_TO_INT12_OUT,));
  __SET_VAR(data__->,_TMP_MUL37_OUT,,__PID_4_0_MUL__REAL__REAL3(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (UINT)2,
    (REAL)__GET_VAR(data__->KP,),
    (REAL)100.0,
    data__));
  __SET_VAR(data__->,_TMP_REAL_TO_INT15_OUT,,REAL_TO_INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->_TMP_MUL37_OUT,)));
  __SET_EXTERNAL(data__->,KP_PSM,,__GET_VAR(data__->_TMP_REAL_TO_INT15_OUT,));
  __SET_VAR(data__->,_TMP_MUL28_OUT,,__PID_4_0_MUL__REAL__REAL4(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (UINT)2,
    (REAL)__GET_VAR(data__->SP,),
    (REAL)100.0,
    data__));
  __SET_VAR(data__->,_TMP_REAL_TO_INT21_OUT,,REAL_TO_INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->_TMP_MUL28_OUT,)));
  __SET_EXTERNAL(data__->,SP_PSM,,__GET_VAR(data__->_TMP_REAL_TO_INT21_OUT,));
  __SET_VAR(data__->,_TMP_MUL29_OUT,,__PID_4_0_MUL__REAL__REAL5(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (UINT)2,
    (REAL)__GET_VAR(data__->TD,),
    (REAL)100.0,
    data__));
  __SET_VAR(data__->,_TMP_REAL_TO_INT24_OUT,,REAL_TO_INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->_TMP_MUL29_OUT,)));
  __SET_EXTERNAL(data__->,TD_PSM,,__GET_VAR(data__->_TMP_REAL_TO_INT24_OUT,));
  __SET_VAR(data__->,_TMP_MUL34_OUT,,__PID_4_0_MUL__REAL__REAL6(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (UINT)2,
    (REAL)__GET_VAR(data__->PV,),
    (REAL)100.0,
    data__));
  __SET_VAR(data__->,_TMP_REAL_TO_INT31_OUT,,REAL_TO_INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->_TMP_MUL34_OUT,)));
  __SET_EXTERNAL(data__->,PV_PSM,,__GET_VAR(data__->_TMP_REAL_TO_INT31_OUT,));
  __SET_VAR(data__->,_TMP_INT_TO_REAL39_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_EXTERNAL(data__->ERROR_PSM,)));
  __SET_VAR(data__->,_TMP_DIV38_OUT,,__PID_4_0_DIV__REAL__REAL__REAL7(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL39_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV38_ENO,)) {
    __SET_VAR(data__->,ERROR,,__GET_VAR(data__->_TMP_DIV38_OUT,));
  };
  __SET_VAR(data__->,_TMP_INT_TO_REAL44_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_EXTERNAL(data__->INTEGRATIVE_PSM,)));
  __SET_VAR(data__->,_TMP_DIV43_OUT,,__PID_4_0_DIV__REAL__REAL__REAL8(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL44_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV43_ENO,)) {
    __SET_VAR(data__->,INTEGRATIVE,,__GET_VAR(data__->_TMP_DIV43_OUT,));
  };
  __SET_VAR(data__->,_TMP_INT_TO_REAL54_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_EXTERNAL(data__->OUT_CV_PSM,)));
  __SET_VAR(data__->,_TMP_DIV53_OUT,,__PID_4_0_DIV__REAL__REAL__REAL9(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL54_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV53_ENO,)) {
    __SET_VAR(data__->,OUT_CV,,__GET_VAR(data__->_TMP_DIV53_OUT,));
  };
  __SET_VAR(data__->,_TMP_INT_TO_REAL49_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_EXTERNAL(data__->TIMEPSM,)));
  __SET_VAR(data__->,_TMP_DIV48_OUT,,__PID_4_0_DIV__REAL__REAL__REAL10(
    (BOOL)__GET_VAR(data__->ENABLE,),
    (REAL)__GET_VAR(data__->_TMP_INT_TO_REAL49_OUT,),
    (REAL)100.0,
    data__));
  if (__GET_VAR(data__->_TMP_DIV48_ENO,)) {
    __SET_VAR(data__->,TIMEVAR,,__GET_VAR(data__->_TMP_DIV48_OUT,));
  };
  __SET_EXTERNAL(data__->,PID4_ENABLED_PSM,,__GET_VAR(data__->ENABLE,));

  goto __end;

__end:
  return;
} // PID_4_0_body__() 





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
  __SET_VAR(data__->TON1.,IN,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->TON1.,PT,,__time_to_timespec(1, 5000, 0, 0, 0, 0));
  TON_body__(&data__->TON1);

  goto __end;

__end:
  return;
} // A_MAIN_ROUTINE_body__() 





