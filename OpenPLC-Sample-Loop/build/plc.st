TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK


PROGRAM b_PID4_routine
  VAR_EXTERNAL
    always_false : BOOL;
    Alive : BOOL;
    always_true : BOOL;
  END_VAR
  VAR
    PIT_129 : REAL;
    PIT_118 : REAL;
    LIT_125 : REAL;
    FIT_116 : REAL;
    PUMP_CH : INT := 2;
    PUMP_SPEED : INT := 0;
    KP : REAL;
    ERROR : REAL;
    INTEGRATIVE : REAL;
    SETPOINT_GEN : REAL;
    TIMEvar : REAL;
  END_VAR
  VAR_EXTERNAL
    PID_OUT : INT;
  END_VAR
  VAR
    DAQ_AI_I0 : DAQ_AI_I;
    PID_4_00 : PID_4_0;
    DAQ_AO_U_WT0 : DAQ_AO_U_WT;
    _TMP_REAL_TO_INT90_OUT : INT;
  END_VAR

  DAQ_AI_I0(DAQ_AI_I_ENABLE := 1, DAQ_AI_I_STACK := 0, DAQ_AI_I_CHANNEL := 3);
  LIT_125 := DAQ_AI_I0.DAQ_AI_I_ANSWER;
  PID_4_00(ENABLE := always_true, CTRL_LOOP_INDEX := 1, KP := 30.0, TI := 5.0, TD := 0.01, SP := 50.0, PV := LIT_125);
  _TMP_REAL_TO_INT90_OUT := REAL_TO_INT(PID_4_00.OUT_CV);
  PUMP_SPEED := _TMP_REAL_TO_INT90_OUT;
  INTEGRATIVE := PID_4_00.INTEGRATIVE;
  TIMEvar := PID_4_00.TIMEvar;
  ERROR := PID_4_00.ERROR;
  PID_OUT := _TMP_REAL_TO_INT90_OUT;
  DAQ_AO_U_WT0(DAQ_AO_U_WT_ENABLE := 1, DAQ_AO_U_WT_STACK := 0, DAQ_AO_U_WT_CHANNEL := 2, DAQ_AO_U_WT_VALUE := PUMP_SPEED);
END_PROGRAM

PROGRAM a_Main_routine
  VAR_EXTERNAL
    Alive : BOOL;
  END_VAR
  VAR
    TON0 : TON;
    TON1 : TON;
  END_VAR
  VAR_EXTERNAL
    always_false : BOOL;
    always_true : BOOL;
    DAQ_AI_I_ch1 : REAL;
    DAQ_AI_I_ch2 : REAL;
    DAQ_AI_I_ch3 : REAL;
    DAQ_AI_I_ch4 : REAL;
  END_VAR

  TON0(IN := NOT(TON1.q), PT := T#5000ms);
  Alive := TON0.Q;
  IF always_false THEN
    always_false := FALSE; (*reset*)
  END_IF;
  IF NOT(always_true) THEN
    always_true := TRUE; (*set*)
  END_IF;
  TON1(IN := TON0.Q, PT := T#5000ms);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    VAR_GLOBAL
      always_false : BOOL := 0;
      always_true : BOOL := 1;
      Alive : BOOL := 0;
      DAQ_AI_I_ENABLE_PSM : BOOL := 0;
      DAQ_AI_I_STACK_PSM : INT := 0;
      DAQ_AI_I_CHANNEL_PSM : INT := 0;
      DAQ_AI_I_PSM : INT := 0;
      DAQ_AI_I_ch1 : REAL := 0;
      DAQ_AI_I_ch2 : REAL := 0;
      DAQ_AI_I_ch3 : REAL := 0;
      DAQ_AI_I_ch4 : REAL := 0;
      DAQ_AO_U_WT_ENABLE_PSM : BOOL := 0;
      DAQ_AO_U_WT_STACK_PSM : INT := 0;
      DAQ_AO_U_WT_CHANNEL_PSM : INT := 0;
      DAQ_AO_U_WT_VALUE_PSM : INT := 0;
      DAQ_AO_U_RD_ENABLE_PSM : BOOL := 0;
      DAQ_AO_U_RD_STACK_PSM : INT := 0;
      DAQ_AO_U_RD_CHANNEL_PSM : INT := 0;
      DAQ_AO_U_RD_PSM : INT := 0;
      DAQ_AI_U_ENABLE_PSM : BOOL := 0;
      DAQ_AI_U_STACK_PSM : INT := 0;
      DAQ_AI_U_CHANNEL_PSM : INT := 0;
      DAQ_AI_U_PSM : INT := 0;
      DAQ_AO_I_WT_ENABLE_PSM : BOOL := 0;
      DAQ_AO_I_WT_STACK_PSM : INT := 0;
      DAQ_AO_I_WT_CHANNEL_PSM : INT := 0;
      DAQ_AO_I_WT_VALUE_PSM : INT := 0;
      DAQ_AO_I_RD_ENABLE_PSM : BOOL := 0;
      DAQ_AO_I_RD_STACK_PSM : INT := 0;
      DAQ_AO_I_RD_CHANNEL_PSM : INT := 0;
      DAQ_AO_I_RD_PSM : INT := 0;
      DAQ_AO_OD_WT_ENABLE_PSM : BOOL := 0;
      DAQ_AO_OD_WT_STACK_PSM : INT := 0;
      DAQ_AO_OD_WT_CHANNEL_PSM : INT := 0;
      DAQ_AO_OD_WT_VALUE_PSM : INT := 0;
      DAQ_AO_OD_RD_ENABLE_PSM : BOOL := 0;
      DAQ_AO_OD_RD_STACK_PSM : INT := 0;
      DAQ_AO_OD_RD_CHANNEL_PSM : INT := 0;
      DAQ_AO_OD_RD_PSM : INT := 0;
      DAQ_DI_OPTO_ENABLE_PSM : BOOL := 0;
      DAQ_DI_OPTO_STACK_PSM : INT := 0;
      DAQ_DI_OPTO_CHANNEL_PSM : INT := 0;
      DAQ_DI_OPTO_PSM : INT := 0;
      PID4_ENABLED_PSM : BOOL := 0;
      CTRL_LOOP_INDEX_PSM : INT := 0;
      KP_PSM : INT := 0;
      TI_PSM : INT := 0;
      TD_PSM : INT := 0;
      PV_PSM : INT := 0;
      SP_PSM : INT := 0;
      ERROR_PSM : INT := 0;
      INTEGRATIVE_PSM : INT := 0;
      TIMEpsm : INT := 0;
      OUT_CV_PSM : INT := 0;
      PID_OUT : INT := 0;
    END_VAR
    TASK Main(INTERVAL := T#100ms,PRIORITY := 1);
    PROGRAM instance00 WITH Main : a_Main_routine;
    PROGRAM instance01 WITH Main : b_PID4_routine;
  END_RESOURCE
END_CONFIGURATION
