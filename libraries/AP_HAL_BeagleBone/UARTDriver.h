
#ifndef __AP_HAL_BEAGLEBONE_UARTDRIVER_H__
#define __AP_HAL_BEAGLEBONE_UARTDRIVER_H__

#include <AP_HAL_BeagleBone.h>

#include <../AP_HAL_Linux/UARTDriver.h>

class BeagleBone::BeagleBoneUARTDriver : public Linux::LinuxUARTDriver {
public:
    BeagleBoneUARTDriver(bool default_console)
        : Linux::LinuxUARTDriver(default_console) {}
};

#endif // __AP_HAL_BEAGLEBONE_UARTDRIVER_H__
