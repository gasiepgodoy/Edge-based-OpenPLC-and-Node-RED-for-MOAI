print("╔==========================================================╗")
print("║                  Version control                         ║")
print("║    Issue: E.Viana 03.05.2024                             ║")
print("║    PSM code: OpenPLC_Libraries.txt                       ║")
print("║    PLC code:                                             ║")
print("╚==========================================================╝")
#      ╔=======================================╗
#      ║         Libraries import              ║
#      ╚=======================================╝
import psm
import math
import time
from time import sleep
from datetime import date
from datetime import datetime
import re
import os
import nats
import pynats
from MoleculerClient import MoleculerClient
#     ╔=======================================╗
#     ║      Global Variables Definition      ║
#     ╚=======================================╝

clock_counter = 0
counter = 0
var_state = False
sec_diff = 0   # Time interval calculation variable
DAQ_AI_I = 0

# ============ Variables initialization for PID4.0 ==============
ERROR       = [ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
INTEGRATIVE = [ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
TIME        = [ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0]
OUT_CV      = [ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
# ===============================================================
# ================ Historical file creation =====================
myFile = open("c:/MyData/PSM_CODE_r01.txt", "w")
myFile.write("")  # Clean the above file
myFile.close()

#      === Historical file header preparation === 
with open("c:/MyData/PSM_CODE_r01.txt", 'a') as f:  # It creates the header of a new log file
    f.write("Time")             #Date & Time string
    f.write("			")      #Tab spacing
    f.write("VAR001")
    f.write("	")  		    #Tab spacing
    f.write("VAR002")
    f.write("	")  	 	    #Tab spacing
    f.write("VAR003")
    f.write("	")  		    #Tab spacing
    f.write("VAR004")
    f.write("	")  		    #Tab spacing
    f.write("VAR005")
    f.write("		")  	    #Tab spacing
    f.write("VAR006")
    f.write('\n')
    f.close() 
#      ╔=======================================╗
#      ║    Hardware Initialization Routine    ║
#      ╚=======================================╝
def hardware_init():
    #Insert your hardware initialization code in here
    psm.start()
#      ╔=======================================╗
#      ║            PSM Main Routine           ║
#      ╚=======================================╝
def mol_client():
#      ╔========================================================╗
#      ║         Kp, Ti & Td data reading from PLC              ║
#      ╚========================================================╝	

    DAQ_PID40_Enabled =  psm.get_var("QX1.4")
    if DAQ_PID40_Enabled == 1:
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="pid-4.0-mesh-1-rasp-105", url='nats://192.168.1.201:4222')
        LOOP_INDEX = psm.get_var("QW23")
        KP_PSM     = float(psm.get_var("QW24"))/100.0
        TI_PSM     = float(psm.get_var("QW25"))/100.0
        TD_PSM     = float(psm.get_var("QW26"))/100.0
        PV_PSM     = float(psm.get_var("QW27"))/100.0
        SP_PSM     = float(psm.get_var("QW28"))/100.0

#      ╔=====================================================================================================================╗
#      ║                                       Moleculer Client PID4.0 Opening Request Code                                  ║
#      ╚=====================================================================================================================╝
         
#      ╔========================================================╗
#      ║            Code for PID 4 implementation               ║
#      ╚========================================================╝
        global ERROR
        global INTEGRATIVE
        global TIME
        global OUT_CV

        PID4_DATA_IN = moleculer.call('control-mesh-31.pidplus', {"ti": TI_PSM, "td": TD_PSM, "kp": KP_PSM, "pv": PV_PSM, "setpoint": SP_PSM, "error": ERROR[LOOP_INDEX], "integrative": INTEGRATIVE[LOOP_INDEX], "manipulatedVariable": OUT_CV[LOOP_INDEX], "time": TIME[LOOP_INDEX] }  )
        print(PID4_DATA_IN)
        PID4_DATA_IN = re.findall(r'\[.*?]', str(PID4_DATA_IN))

        for i in range(8): PID4_DATA_IN[i]=PID4_DATA_IN[i].replace("[","")
        for i in range(8): PID4_DATA_IN[i]=PID4_DATA_IN[i].replace("]","")
        OUT_CV[LOOP_INDEX]       = float(PID4_DATA_IN[0])
        ERROR[LOOP_INDEX]        = float(PID4_DATA_IN[1])
        INTEGRATIVE[LOOP_INDEX]  = float(PID4_DATA_IN[2])
        TIME[LOOP_INDEX]         =      (PID4_DATA_IN[3])	

        psm.set_var( "IW26", abs(int(ERROR[LOOP_INDEX]*100)) )
        psm.set_var( "IW27", abs(int(INTEGRATIVE[LOOP_INDEX]*100)) )
       #psm.set_var( "IW28", TIME[LOOP_INDEX]*100 )   # This integer is too large to be passed to OpenPLC !!!
        psm.set_var( "IW29", int(OUT_CV[LOOP_INDEX]*100) )

        print("OUT_CV: ", OUT_CV[LOOP_INDEX]) 
        print("Erro: ",        abs(int(ERROR[LOOP_INDEX]      *100))  )
        print("Integrativo: ", abs(int(INTEGRATIVE[LOOP_INDEX]*100))  )

        #time.sleep(0.05) #50ms
#      ╔=====================================================================================================================╗
#      ║                                 1)  Moleculer Client DAQ_AO_U_WT                                                    ║
#      ╚=====================================================================================================================╝
    DAQ_AO_U_WT_ENABLE = psm.get_var("QX0.3")
    if DAQ_AO_U_WT_ENABLE == 1 :
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="megaind-rpi-raspberry-3", url='nats://192.168.1.201:4222') 
        DAQ_AO_U_WT_STACK   = psm.get_var("QW2")
        DAQ_AO_U_WT_CHANNEL = psm.get_var("QW3")
        DAQ_AO_U_WT_VALUE   = psm.get_var("QW4")
        print(DAQ_AO_U_WT_VALUE)
        DAQ_AO_U_WT = moleculer.call('megaind-rpi-v8.setOutputVoltage', { "stack": DAQ_AO_U_WT_STACK, "channel": DAQ_AO_U_WT_CHANNEL, "value": DAQ_AO_U_WT_VALUE } )
        DAQ_AO_U_WT_ENABLE  = 0
    #if DAQ_AO_U_WT_ENABLE == 0 :
        #none
#      ╔=====================================================================================================================╗
#      ║                                2)   Moleculer Client DAQ_AO_U_RD                                                    ║
#      ╚=====================================================================================================================╝
    DAQ_AO_U_RD_ENABLE = psm.get_var("QX0.4")
    if DAQ_AO_U_RD_ENABLE == 1:
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="megaind-rpi-raspberry-3", url='nats://192.168.1.201:4222') 
        DAQ_AO_U_RD_STACK    = psm.get_var("QW5")
        DAQ_AO_U_RD_CHANNEL  = psm.get_var("QW6")
        DAQ_AO_U_RD = moleculer.call('megaind-rpi-v8.getOutputVoltage', {"stack": DAQ_AO_U_RD_STACK, "channel": DAQ_AO_U_RD_CHANNEL} )
        DAQ_AO_U_RD_ENABLE   = 0
        psm.set_var("IW21", int(DAQ_AO_U_RD * 100.0)) 
#      ╔=====================================================================================================================╗
#      ║                               3)    Moleculer Client DAQ_AI_U                                                       ║
#      ╚=====================================================================================================================╝
    DAQ_AI_U_ENABLE = psm.get_var("QX0.5")
    if DAQ_AI_U_ENABLE == 1:
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="megaind-rpi-raspberry-3", url='nats://192.168.1.201:4222') 
        DAQ_AI_U_STACK    = psm.get_var("QW7")
        DAQ_AI_U_CHANNEL  = psm.get_var("QW8")
        DAQ_AI_U = moleculer.call('megaind-rpi-v8.getInputVoltage', {"stack": DAQ_AI_U_STACK, "channel": DAQ_AI_U_CHANNEL} )
        DAQ_AI_U_ENABLE   = 0
        psm.set_var("IW22", int(DAQ_AI_U * 100.0)) 

        #print("DAQ_AI_U: ",DAQ_AI_U) 
#      ╔=====================================================================================================================╗
#      ║                               4)    Moleculer Client DAQ_AO_I_WT                                                    ║
#      ╚=====================================================================================================================╝
    DAQ_AO_I_WT_ENABLE = psm.get_var("QX0.6")
    if DAQ_AO_I_WT_ENABLE == 1 :
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="megaind-rpi-raspberry-3", url='nats://192.168.1.201:4222') 
        DAQ_AO_I_WT_STACK   = psm.get_var("QW9")
        DAQ_AO_I_WT_CHANNEL = psm.get_var("QW10")
        DAQ_AO_I_WT_VALUE   = psm.get_var("QW11")
        DAQ_AO_I_WT = moleculer.call('megaind-rpi-v8.setOutputCurrent', { "stack": DAQ_AO_I_WT_STACK, "channel": DAQ_AO_I_WT_CHANNEL, "value": DAQ_AO_I_WT_VALUE } )
        DAQ_AO_I_WT_ENABLE  = 0
#      ╔=====================================================================================================================╗
#      ║                               5)    Moleculer Client DAQ_AO_I_RD                                                    ║
#      ╚=====================================================================================================================╝
    DAQ_AO_I_RD_ENABLE = psm.get_var("QX0.7")
    if DAQ_AO_I_RD_ENABLE == 1:
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="megaind-rpi-raspberry-3", url='nats://192.168.1.201:4222') 
        DAQ_AO_I_RD_STACK    = psm.get_var("QW12")
        DAQ_AO_I_RD_CHANNEL  = psm.get_var("QW13")
        DAQ_AO_I_RD = moleculer.call('megaind-rpi-v8.getOutputCurrent', {"stack": DAQ_AO_I_RD_STACK, "channel": DAQ_AO_I_RD_CHANNEL} )
        DAQ_AO_I_RD_ENABLE   = 0
        psm.set_var("IW23", int(DAQ_AO_I_RD * 100.0)) 
#      ╔=====================================================================================================================╗
#      ║                                6)   Moleculer Client DAQ_AI_I                                                       ║
#      ╚=====================================================================================================================╝
    DAQ_AI_I_ENABLE = psm.get_var("QX1.0")
    if DAQ_AI_I_ENABLE == 1:
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="megaind-rpi-raspberry-3", url='nats://192.168.1.201:4222') 
        DAQ_AI_I_STACK    = psm.get_var("QW14")
        DAQ_AI_I_CHANNEL  = psm.get_var("QW15")
        DAQ_AI_I = moleculer.call('megaind-rpi-v8.getInputCurrent', {"stack": DAQ_AI_I_STACK, "channel": DAQ_AI_I_CHANNEL} )
        DAQ_AI_I_ENABLE   = 0
        psm.set_var("IW20", int(DAQ_AI_I * 100.0)) 

        #print("DAQ_AI_I: ",DAQ_AI_I) 

    #if DAQ_AI_I_ENABLE == 0:
        #psm.set_var("IW20", int(0))
#      ╔=====================================================================================================================╗
#      ║                               7)   Moleculer Client DAQ_AO_OD_WT                                                    ║
#      ╚=====================================================================================================================╝
    DAQ_AO_OD_WT_ENABLE = psm.get_var("QX1.1")
    if DAQ_AO_OD_WT_ENABLE == 1 :
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="megaind-rpi-raspberry-3", url='nats://192.168.1.201:4222') 
        DAQ_AO_OD_WT_STACK   = psm.get_var("QW16")
        DAQ_AO_OD_WT_CHANNEL = psm.get_var("QW17")
        DAQ_AO_OD_WT_VALUE   = psm.get_var("QW18")
        DAQ_AO_OD_WT = moleculer.call('megaind-rpi-v8.setOutputOpenDrain', { "stack": DAQ_AO_OD_WT_STACK, "channel": DAQ_AO_OD_WT_CHANNEL, "value": DAQ_AO_OD_WT_VALUE } )
        DAQ_AO_OD_WT_ENABLE  = 0
#      ╔=====================================================================================================================╗
#      ║                               8)   Moleculer Client DAQ_AO_OD_RD                                                    ║
#      ╚=====================================================================================================================╝
    DAQ_AO_OD_RD_ENABLE = psm.get_var("QX1.2")
    if DAQ_AO_OD_RD_ENABLE == 1:
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="megaind-rpi-raspberry-3", url='nats://192.168.1.201:4222') 
        DAQ_AO_OD_RD_STACK    = psm.get_var("QW19")
        DAQ_AO_OD_RD_CHANNEL  = psm.get_var("QW20")
        DAQ_AO_OD_RD = moleculer.call('megaind-rpi-v8.getOutputOpendrain', {"stack": DAQ_AO_OD_RD_STACK, "channel": DAQ_AO_OD_RD_CHANNEL} )
        DAQ_AO_OD_RD_ENABLE   = 0
        psm.set_var("IW24", int(DAQ_AO_OD_RD * 100.0)) 
#      ╔=====================================================================================================================╗
#      ║                                9)   Moleculer Client DAQ_DI_OPTO                                                    ║
#      ╚=====================================================================================================================╝
    DAQ_DI_OPTO_ENABLE = psm.get_var("QX1.3")
    if DAQ_DI_OPTO_ENABLE == 1:
        moleculer = MoleculerClient(node_id='python-node', moleculer_nodeID="megaind-rpi-raspberry-3", url='nats://192.168.1.201:4222') 
        DAQ_DI_OPTO_STACK    = psm.get_var("QW21")
        DAQ_DI_OPTO_CHANNEL  = psm.get_var("QW22")
        DAQ_DI_OPTO = moleculer.call('megaind-rpi-v8.getInputOpto', {"stack": DAQ_DI_OPTO_STACK, "channel": DAQ_DI_OPTO_CHANNEL} )
        DAQ_DI_OPTO_ENABLE   = 0
        psm.set_var("IW25", int(DAQ_DI_OPTO * 100.0)) 
#      ╔=====================================================================================================================╗
#      ║                                                 Timed routine [ 1..60s ]                                            ║
#      ║                                         Run every n seconds and write to a file	                             ║
#      ╚=====================================================================================================================╝ 	
    VAR01 = 1
    VAR02 = 2
    VAR03 = 3
    VAR04 = 4
    VAR05 = 5
    VAR06 = 6

    now = datetime.now()
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S") # Format date as: dd/mm/YY H:M:S
    my_sec = float(now.strftime("%S"))
    global sec_diff
    time_int = 5.0  #  Time interval in seconds for data collection
    if (my_sec / time_int - (int(my_sec / time_int)) == 0.000000 ):   # Check when timing is an integer (multiple of the time basis named time_int
        if sec_diff != my_sec:  # It guarantees there wont be two equal data registered simultaneously
            sec_diff = my_sec             
            with open("c:/MyData/PSM_CODE_r01.txt", 'a') as f:
                f.write(dt_string)  #Date & Time string
                f.write("	")      #Tab spacing
                f.write(str(VAR01))
                f.write("		")  #Tab spacing
                f.write(str(VAR02))
                f.write("		")  #Tab spacing
                f.write(str(VAR03))
                f.write("		")  #Tab spacing
                f.write(str(VAR04))
                f.write("		")  #Tab spacing
                f.write(str(VAR05))
                f.write("		")  #Tab spacing
                f.write(str(VAR06))
                f.write('\n')
                f.close()

            # ======= Output printing ==========
            print(dt_string) 
            print("=== Data for PSM ===") 
            # print("SP for TQ01 is:", SP_PROF_LEVEL)
    
if __name__ == "__main__":    
    hardware_init()
    while (not psm.should_quit()):
        mol_client()
        time.sleep(0.100) #You can adjust the psm cycle time here

#   === In case CPU goes to stop mode, clear all outputs ===
   
    psm.stop()