
#ifndef __AP_HAL_BEAGLEBONE_SPIDRIVER_H__
#define __AP_HAL_BEAGLEBONE_SPIDRIVER_H__

#include <AP_HAL_BeagleBone.h>
#include "Semaphores.h"

#include <../AP_HAL_Linux/SPIDriver.h>

class BeagleBone::BeagleBoneSPIDeviceDriver : public Linux::LinuxSPIDeviceDriver {
public:
    BeagleBoneSPIDeviceDriver(const char *spipath, uint8_t mode, uint8_t bitsPerWord, uint32_t speed)
        : Linux::LinuxSPIDeviceDriver(spipath, mode, bitsPerWord, speed) {}
};

class BeagleBone::BeagleBoneSPIDeviceManager : public Linux::LinuxSPIDeviceManager {
public:
    BeagleBoneSPIDeviceManager() : Linux::LinuxSPIDeviceManager() {}
};

#endif // __AP_HAL_BEAGLEBONE_SPIDRIVER_H__
