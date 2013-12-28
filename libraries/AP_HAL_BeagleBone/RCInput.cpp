#include "RCInput.h"

using namespace BeagleBone;
BeagleBoneRCInput::BeagleBoneRCInput()
{}

/*
 * Examples from a Hobbyking 6ch RX
 * stick 
 * 011875C1:001243C8 low
 * 011877BA:001E20E9 high
 * dial
 * 01186D65:000F4CFE low
 * 011877BA:001ECF4E high
 */

void BeagleBoneRCInput::init(void* unused)
{
    uid_t euid;
    /* Initialize the PRU */
    if ((euid = geteuid()) != 0)
        hal.scheduler->panic("PRUSS requires root privs to load code!");
    if (prussdrv_init() != 0)
        hal.scheduler->panic("RCInput: prussdrv_init() failed!");
    if (prussdrv_open(PRU_EVTOUT_0) != 0)
        hal.scheduler->panic("RCInput: prussdrv_open() failed!");
    if (prussdrv_exec_program(IN_PRU_NUM, READPPM_FILE) != 0)
        hal.scheduler->panic("RCInput: prussdrv_exec_program failed to open READPPM_FILE!");
    if (prussdrv_map_prumem (IN_PRU_DATARAM, &dataMem) != 0)
        hal.scheduler->panic("RCInput: prussdrv_map_prumem failed to map PRU memory!");
}
    
uint8_t BeagleBoneRCInput::valid_channels() { return _valid_channels; }

/* constrain captured pulse to be between min and max pulsewidth. */
static inline uint16_t constrain_pulse(uint16_t p) {
    if (p > RC_INPUT_MAX_PULSEWIDTH) return RC_INPUT_MAX_PULSEWIDTH;
    if (p < RC_INPUT_MIN_PULSEWIDTH) return RC_INPUT_MIN_PULSEWIDTH;
    return p;
}

uint16_t BeagleBoneRCInput::read(uint8_t ch) {
    if (ch >= BEAGLEBONE_RC_INPUT_NUM_CHANNELS)
        return 0;
    if (_override[ch]) 
        return _override[ch];
    return constrain_pulse(dataMem_int[3] / dataMem_int[2]);
}

uint8_t BeagleBoneRCInput::read(uint16_t* periods, uint8_t len) {
    if (len > BEAGLEBONE_RC_INPUT_NUM_CHANNELS) 
        len = BEAGLEBONE_RC_INPUT_NUM_CHANNELS;
    for (uint8_t i = 0; i < len; i++){
        periods[i] = read(i);
    }
    return len;
}

bool BeagleBoneRCInput::set_overrides(int16_t *overrides, uint8_t len) {
    bool res = false;
    for (uint8_t i = 0; i < len; i++) {
        res |= set_override(i, overrides[i]);
    }
    return res;
}

bool BeagleBoneRCInput::set_override(uint8_t channel, int16_t override) {
    if (override < 0) return false; /* -1: no change. */
    if (channel < BEAGLEBONE_RC_INPUT_NUM_CHANNELS) {
        _override[channel] = override;
        if (override != 0) {
            _valid_channels = 1;
            return true;
        }
    }
    return false;
}

void BeagleBoneRCInput::clear_overrides()
{
    for (uint8_t i = 0; i < BEAGLEBONE_RC_INPUT_NUM_CHANNELS; i++) {
        _override[i] = 0;
    }
}

