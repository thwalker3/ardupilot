
#ifndef __AP_HAL_BEAGLEBONE_STORAGE_H__
#define __AP_HAL_BEAGLEBONE_STORAGE_H__

#include <AP_HAL_BeagleBone.h>
#include <../AP_HAL_Linux/Storage.h>

class BeagleBone::BeagleBoneStorage : public Linux::LinuxStorage {
public:
    BeagleBoneStorage() : Linux::LinuxStorage() {};
};

#endif // __AP_HAL_BEAGLEBONE_STORAGE_H__
