
#include "RCOutput.h"

using namespace BeagleBone;

void BeagleBoneRCOutput::init(void* unused)
{
    uid_t euid;
    /* Initialize the PRU */
    if ((euid = geteuid()) != 0)
        hal.scheduler->panic("PRUSS requires root privs to load code!");
    if (prussdrv_init() != 0)
        hal.scheduler->panic("RCOutput: prussdrv_init() failed!");
    if (prussdrv_open(PRU_EVTOUT_0) != 0)
        hal.scheduler->panic("RCOutput: prussdrv_open() failed!");
    if (prussdrv_exec_program(OUT_PRU_NUM, WRITEPPM_FILE) != 0)
        hal.scheduler->panic("RCOutput: prussdrv_exec_program failed to open READPPM_FILE!");
    if (prussdrv_map_prumem (OUT_PRU_DATARAM, &dataMem) != 0)
        hal.scheduler->panic("RCOutput: prussdrv_map_prumem failed to map PRU memory!");
}

void BeagleBoneRCOutput::set_freq(uint32_t chmask, uint16_t freq_hz) 
{
    hal.console->printf("RCOutput: No support for varying output frequency currently!");
}

uint16_t BeagleBoneRCOutput::get_freq(uint8_t ch) 
{
    return 50;
}

void BeagleBoneRCOutput::enable_ch(uint8_t ch)
{
 // all channels are always enabled  
}

void BeagleBoneRCOutput::enable_mask(uint32_t chmask)
{
 // all channels are always enabled
}


void BeagleBoneRCOutput::disable_ch(uint8_t ch)
{
 // all channels are always enabled
}


void BeagleBoneRCOutput::disable_mask(uint32_t chmask)
{
 // all channels are always enabled
}


void BeagleBoneRCOutput::write(uint8_t ch, uint16_t period_us)
{
    if (ch >= BEAGLEBONE_RC_OUTPUT_NUM_CHANNELS)
        return;
    // write to memory
}

void BeagleBoneRCOutput::write(uint8_t ch, uint16_t* period_us, uint8_t len)
{
    for (uint8_t i=0; i<len; i++) {
        write(i, period_us[i]);
    }
}

uint16_t BeagleBoneRCOutput::read(uint8_t ch)
{   
    if (ch >= BEAGLEBONE_RC_OUTPUT_NUM_CHANNELS)
        return 0;
    return _period[ch];
}

void BeagleBoneRCOutput::read(uint16_t* period_us, uint8_t len)
{
    for (uint8_t i=0; i<len; i++) 
        period_us[i] = read(i);
}

