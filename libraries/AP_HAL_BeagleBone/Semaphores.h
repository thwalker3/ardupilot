
#ifndef __AP_HAL_BEAGLEBONE_SEMAPHORE_H__
#define __AP_HAL_BEAGLEBONE_SEMAPHORE_H__

#include <AP_HAL_BeagleBone.h>

#include <../AP_HAL_Linux/Semaphores.h>

class BeagleBone::BeagleBoneSemaphore : public Linux::LinuxSemaphore {
public:
    BeagleBoneSemaphore() : Linux::LinuxSemaphore() {};
};

#endif // __AP_HAL_BEAGLEBONE_SEMAPHORE_H__
