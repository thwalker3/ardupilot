
#ifndef __AP_HAL_BEAGLEBONE_RCOUTPUT_H__
#define __AP_HAL_BEAGLEBONE_RCOUTPUT_H__

#include <AP_HAL_BeagleBone.h>
#include <AP_HAL.h>
extern const AP_HAL::HAL& hal;

// PRU driver header file
#include "prussdrv.h"
//#include <pruss_intc_mapping.h>
// geteuid()
#include <unistd.h>
#include <sys/types.h>

#define BEAGLEBONE_RC_OUTPUT_NUM_CHANNELS 8

#define OUT_PRU_NUM 1
#define OUT_PRU_DATARAM 1
#define WRITEPPM_FILE "/tmp/WritePPM.bin"

class BeagleBone::BeagleBoneRCOutput : public AP_HAL::RCOutput {
public:
    void     init(void* machtnichts);
    void     set_freq(uint32_t chmask, uint16_t freq_hz);
    uint16_t get_freq(uint8_t ch);
    void     enable_ch(uint8_t ch);
    void     enable_mask(uint32_t chmask);
    void     disable_ch(uint8_t ch);
    void     disable_mask(uint32_t chmask);
    void     write(uint8_t ch, uint16_t period_us);
    void     write(uint8_t ch, uint16_t* period_us, uint8_t len);
    uint16_t read(uint8_t ch);
    void     read(uint16_t* period_us, uint8_t len);

private:
    /* private variables to communicate with PRU */
    void *dataMem;
    unsigned int *dataMem_int;
 
    uint16_t _period[BEAGLEBONE_RC_OUTPUT_NUM_CHANNELS];
};

#endif // __AP_HAL_BEAGLEBONE_RCOUTPUT_H__
