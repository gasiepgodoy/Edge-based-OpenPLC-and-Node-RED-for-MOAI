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
    Alive0 : BOOL;
    TON0 : TON;
    TON1 : TON;
  END_VAR
  VAR_EXTERNAL
    always_false : BOOL;
    always_true : BOOL;
  END_VAR
  VAR_EXTERNAL
    DAQ_AI_I_ch1 : REAL;
    DAQ_AI_I_ch2 : REAL;
    DAQ_AI_I_ch3 : REAL;
    DAQ_AI_I_ch4 : REAL;
  END_VAR
  VAR
    TON2 : TON;
    TON3 : TON;
  END_VAR

  TON0(IN := NOT(TON1.q), PT := T#5000ms);
  Alive := TON0.Q;
  IF always_false THEN
    always_false := FALSE; (*reset*)
  END_IF;
  IF NOT(always_true) THEN
    always_true := TRUE; (*set*)
  END_IF;
  TON2(IN := NOT(TON3.q), PT := T#10000ms);
  Alive0 := TON2.Q;
  TON1(IN := TON0.Q, PT := T#5000ms);
  TON3(IN := TON2.Q, PT := T#10000ms);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    VAR_GLOBAL
      always_false AT %QX0.0 : BOOL := 0;
      always_true AT %QX0.1 : BOOL := 1;
      Alive AT %QX0.2 : BOOL;
      DAQ_AI_I_ENABLE_PSM AT %QX1.0 : BOOL := 0;
      DAQ_AI_I_STACK_PSM AT %QW14 : INT := 0;
      DAQ_AI_I_CHANNEL_PSM AT %QW15 : INT := 0;
      DAQ_AI_I_PSM AT %IW20 : INT := 0;
      DAQ_AI_I_ch1 : REAL := 0;
      DAQ_AI_I_ch2 : REAL := 0;
      DAQ_AI_I_ch3 : REAL := 0;
      DAQ_AI_I_ch4 : REAL := 0;
      DAQ_AO_U_WT_ENABLE_PSM AT %QX0.3 : BOOL := 0;
      DAQ_AO_U_WT_STACK_PSM AT %QW2 : INT := 0;
      DAQ_AO_U_WT_CHANNEL_PSM AT %QW3 : INT := 0;
      DAQ_AO_U_WT_VALUE_PSM AT %QW4 : INT := 0;
      DAQ_AO_U_RD_ENABLE_PSM AT %QX0.4 : BOOL := 0;
      DAQ_AO_U_RD_STACK_PSM AT %QW5 : INT := 0;
      DAQ_AO_U_RD_CHANNEL_PSM AT %QW6 : INT := 0;
      DAQ_AO_U_RD_PSM AT %IW21 : INT := 0;
      DAQ_AI_U_ENABLE_PSM AT %QX0.5 : BOOL := 0;
      DAQ_AI_U_STACK_PSM AT %QW7 : INT := 0;
      DAQ_AI_U_CHANNEL_PSM AT %QW8 : INT := 0;
      DAQ_AI_U_PSM AT %IW22 : INT := 0;
      DAQ_AO_I_WT_ENABLE_PSM AT %QX0.6 : BOOL := 0;
      DAQ_AO_I_WT_STACK_PSM AT %QW9 : INT := 0;
      DAQ_AO_I_WT_CHANNEL_PSM AT %QW10 : INT := 0;
      DAQ_AO_I_WT_VALUE_PSM AT %QW11 : INT := 0;
      DAQ_AO_I_RD_ENABLE_PSM AT %QX0.7 : BOOL := 0;
      DAQ_AO_I_RD_STACK_PSM AT %QW12 : INT := 0;
      DAQ_AO_I_RD_CHANNEL_PSM AT %QW13 : INT := 0;
      DAQ_AO_I_RD_PSM AT %IW23 : INT := 0;
      DAQ_AO_OD_WT_ENABLE_PSM AT %QX1.1 : BOOL := 0;
      DAQ_AO_OD_WT_STACK_PSM AT %QW16 : INT := 0;
      DAQ_AO_OD_WT_CHANNEL_PSM AT %QW17 : INT := 0;
      DAQ_AO_OD_WT_VALUE_PSM AT %QW18 : INT := 0;
      DAQ_AO_OD_RD_ENABLE_PSM AT %QX1.2 : BOOL := 0;
      DAQ_AO_OD_RD_STACK_PSM AT %QW19 : INT := 0;
      DAQ_AO_OD_RD_CHANNEL_PSM AT %QW20 : INT := 0;
      DAQ_AO_OD_RD_PSM AT %IW24 : INT := 0;
      DAQ_DI_OPTO_ENABLE_PSM AT %QX1.3 : BOOL := 0;
      DAQ_DI_OPTO_STACK_PSM AT %QW21 : INT := 0;
      DAQ_DI_OPTO_CHANNEL_PSM AT %QW22 : INT := 0;
      DAQ_DI_OPTO_PSM AT %IW25 : INT := 0;
      PID4_ENABLED_PSM AT %QX1.4 : BOOL := 0;
      CTRL_LOOP_INDEX_PSM AT %QW23 : INT := 0;
      KP_PSM AT %QW24 : INT := 0;
      TI_PSM AT %QW25 : INT := 0;
      TD_PSM AT %QW26 : INT := 0;
      PV_PSM AT %QW27 : INT := 0;
      SP_PSM AT %QW28 : INT := 0;
      ERROR_PSM AT %IW26 : INT := 0;
      INTEGRATIVE_PSM AT %IW27 : INT := 0;
      TIMEpsm AT %IW28 : INT := 0;
      OUT_CV_PSM AT %IW29 : INT := 0;
      PID_OUT AT %QW29 : INT := 0;
    END_VAR
    TASK Main(INTERVAL := T#100ms,PRIORITY := 1);
    PROGRAM instance00 WITH Main : a_Main_routine;
    PROGRAM instance01 WITH Main : b_PID4_routine;
  END_RESOURCE
END_CONFIGURATION
