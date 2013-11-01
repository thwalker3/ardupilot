
.origin 0
.entrypoint READ_PPM_INIT

#include "ReadPPM.hp"

.macro processChannel
.mparam inputBit, dataOffset
        // load channel data
        LBCO regLastRising, CONST_PRUDRAM, dataOffset, 16
        QBBS READ_HIGH, regCurrentInput, inputBit
        JMP READ_LOW

READ_HIGH:
        QBBC RISING_EDGE, regLastInput, inputBit
        JMP PROCESS_EXIT // high to high

RISING_EDGE:
        MOV regLastRising, regCurrentTime
        JMP PROCESS_EXIT

READ_LOW:
        QBBC PROCESS_EXIT, regLastInput, inputBit // low to low
        // falling edge, calculate frame and pulse width
        SUB regFrameWidth, regCurrentTime, regLastFalling // frame width
        SUB regPulseWidth, regCurrentTime, regLastRising // pulse width
        MOV regLastFalling, regCurrentTime

PROCESS_EXIT:
        // copy lastRising/Falling and frame/pulse width to RAM
        SBCO regLastRising, CONST_PRUDRAM, dataOffset, 16
.endm

READ_PPM_INIT:

    // Enable OCP master port (clear SYSCFG[STANDBY_INIT])
    LBCO        r0, CONST_PRUCFG, 4, 4
    CLR         r0, r0, 4 
    SBCO        r0, CONST_PRUCFG, 4, 4

    // PRU ref: 5.4.6 (CTIBR_0) Constant Table Block Index Register 0
    // bits 0-7 set C24 to point to CONST_PRUDRAM (0x00000000)
    MOV       r0, 0
    MOV       r1, CTBIR_0
    SBBO      r0, r1, 0, 4

    // WARNING: we are using the same timers in both PRU0 and PRU1, so any changes
    //          to the below must be identical in both sets of code!!!
    // PRU ref: 9.3 (IEP) Industrial Ethernet Peripheral
    // Make sure "compensation" is off (9.3.4)
    MOV         r0, 0
    MOV         r1, IEP_COMPEN
    SBBO        r0, r1, 0, 4 
    // And "compare" functionality is disabled as well (9.3.5)
    MOV         r0, 0
    MOV         r1, IEP_CMP_STATUS
    SBBO        r0, r1, 0, 4
    // should really verify iep_clk is set and enabled (both default)
    // Enable IEP counter
    MOV         r0, (IEP_CFG_DEFAULT | IEP_CNT_ENABLE)
    MOV         r1, IEP_GLOBAL_CFG
    SBBO        r0, r1, 0, 4 

    // Set intial values
    MOV regLastInput, r31
    MOV regLastRising, 0
    MOV regLastFalling, 0
    // how about rising/falling and frame/pulse width?
    // or just always discard first reading

READ_PPM_INTERVAL:

    MOV regCurrentInput, r31
    MOV r0, IEP_COUNT 
    LBBO regCurrentTime, r0, 0, 4
    // subtract 10ns? 

    processChannel 0, 0x00 
    processChannel 1, 0x10
    processChannel 2, 0x20
    processChannel 3, 0x30
    processChannel 4, 0x40
    processChannel 5, 0x50

    MOV regLastInput, regCurrentInput
    JMP READ_PPM_INTERVAL
    HALT // never get here
