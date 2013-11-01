
#ifndef __AP_HAL_BEAGLEBONE_RCINPUT_H__
#define __AP_HAL_BEAGLEBONE_RCINPUT_H__

#include <AP_HAL_BeagleBone.h>
#include <AP_HAL.h>
extern const AP_HAL::HAL& hal;

// PRU driver header file
#include "prussdrv.h"
//#include <pruss_intc_mapping.h>
// geteuid()
#include <unistd.h>
#include <sys/types.h>


#define BEAGLEBONE_RC_INPUT_NUM_CHANNELS 8

#define IN_PRU_NUM 0
#define IN_PRU_DATARAM 0
#define READPPM_FILE "/tmp/ReadPPM.bin"

class BeagleBone::BeagleBoneRCInput : public AP_HAL::RCInput {
public:
    BeagleBoneRCInput();
    void init(void* machtnichts);
    uint8_t  valid_channels();
    uint16_t read(uint8_t ch);
    uint8_t read(uint16_t* periods, uint8_t len);

    bool set_overrides(int16_t *overrides, uint8_t len);
    bool set_override(uint8_t channel, int16_t override);
    void clear_overrides();

private:
    /* private variables to communicate with PRU */
    void *dataMem;
    unsigned int *dataMem_int;

    uint8_t  _valid_channels;

    /* override state */
    uint16_t _override[BEAGLEBONE_RC_INPUT_NUM_CHANNELS];

};

#endif // __AP_HAL_BEAGLEBONE_RCINPUT_H__
