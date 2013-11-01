
#ifndef __AP_HAL_BEAGLEBONE_UTIL_H__
#define __AP_HAL_BEAGLEBONE_UTIL_H__

#include <AP_HAL.h>
#include "AP_HAL_BeagleBone_Namespace.h"

class BeagleBone::BeagleBoneUtil : public AP_HAL::Util {
public:
    bool run_debug_shell(AP_HAL::BetterStream *stream) { return false; }
};

#endif // __AP_HAL_BEAGLEBONE_UTIL_H__
