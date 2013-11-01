
#ifndef __AP_HAL_BEAGLEBONE_SCHEDULER_H__
#define __AP_HAL_BEAGLEBONE_SCHEDULER_H__

#include <AP_HAL_BeagleBone.h>

#include <../AP_HAL_Linux/Scheduler.h>

class BeagleBone::BeagleBoneScheduler : public Linux::LinuxScheduler {
public:
    BeagleBoneScheduler() : Linux::LinuxScheduler() {}
};

#endif // __AP_HAL_BEAGLEBONE_SCHEDULER_H__
