
#ifndef __AP_HAL_BEAGLEBONE_CLASS_H__
#define __AP_HAL_BEAGLEBONE_CLASS_H__

#include <AP_HAL.h>

#include "AP_HAL_BeagleBone_Namespace.h"

class HAL_BeagleBone : public AP_HAL::HAL {
public:
    HAL_BeagleBone();
    void init(int argc, char * const * argv) const;
};

extern const HAL_BeagleBone AP_HAL_BeagleBone;

#endif // __AP_HAL_BEAGLEBONE_CLASS_H__

