
.origin 0
.entrypoint WRITE_PPM_INIT

#include "WritePPM.hp"

//#define FRAME_WIDTH 1000000000 // 1 second in ns (3B9ACA00) 
//#define FRAME_WIDTH 250000000 // 1/4 second in ns
#define FRAME_WIDTH 20000000  // 20ms
//#define FRAME_WIDTH 100000000 // 100ms
//#define FRAME_WIDTH 10000000 // 10ms

.macro processChannel
.mparam bitNum, dataOffset
    // load channel data
    LBCO regPulseWidth, CONST_PRUDRAM, dataOffset, 8
    
    QBBS PROCESS_EXIT, R30, bitNum // pulse already started for this frame
    QBLT PROCESS_EXIT, regPulseStartDelay, regFrameElapsedTime
    // time to start pulse and update StartDelay for next frame 
    SET r30, bitNum
    MOV r0, FRAME_WIDTH
    SUB regPulseStartDelay, r0, regPulseWidth
    // save new regPulseStartDelay (regPulseWidth only changes externally)
    SBCO regPulseStartDelay, CONST_PRUDRAM, dataOffset + 4, 4 

PROCESS_EXIT:
.endm

WRITE_PPM_INIT:

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

    // zero output register (lower half)
    ZERO &R30, 2
 
    //MOV         r0, 2000000
    //SBCO        r0, CONST_PRUDRAM, 0, 4 

WRITE_PPM_INTERVAL:
    // update current and frameElapsed times
    MOV r0, IEP_COUNT
    LBBO regCurrentTime, r0, 0, 4
    SUB regFrameElapsedTime, regCurrentTime, regFrameStartTime

    processChannel 0, 0x00
    processChannel 1, 0x08
    processChannel 2, 0x10
    processChannel 3, 0x18
//    processChannel 4, 0x20
//    processChannel 5, 0x28
//    processChannel 6, 0x30
//    processChannel 7, 0x38

    MOV r0, FRAME_WIDTH 
    QBGT WRITE_PPM_INTERVAL, regFrameElapsedTime, r0
    // Frame has ended, clear output bits and update start of next frame
    ZERO &R30, 2
    MOV regFrameStartTime, regCurrentTime
    JMP WRITE_PPM_INTERVAL

    HALT // never get here
