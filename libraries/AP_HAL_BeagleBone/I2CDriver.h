
#ifndef __AP_HAL_BEAGLEBONE_I2CDRIVER_H__
#define __AP_HAL_BEAGLEBONE_I2CDRIVER_H__

#include <AP_HAL_BeagleBone.h>

#include <../AP_HAL_Linux/I2CDriver.h>

class BeagleBone::BeagleBoneI2CDriver : public Linux::LinuxI2CDriver {
public:
    BeagleBoneI2CDriver(AP_HAL::Semaphore* semaphore, const char *device)
        : Linux::LinuxI2CDriver(semaphore, device) {}
};

#endif // __AP_HAL_BEAGLEBONE_I2CDRIVER_H__
