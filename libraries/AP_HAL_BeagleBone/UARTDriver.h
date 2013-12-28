
#ifndef __AP_HAL_BEAGLEBONE_UARTDRIVER_H__
#define __AP_HAL_BEAGLEBONE_UARTDRIVER_H__

#include <AP_HAL_BeagleBone.h>

#include <../AP_HAL_Linux/UARTDriver.h>
#include <../AP_HAL_AVR_SITL/UARTDriver.h>

class BeagleBone::BeagleBoneUARTDriver : public Linux::LinuxUARTDriver {
public:
    BeagleBoneUARTDriver(bool default_console)
        : Linux::LinuxUARTDriver(default_console) {}
};

class BeagleBone::BeagleBoneTCPUARTDriver : public AVR_SITL::SITLUARTDriver {
public:
    BeagleBoneTCPUARTDriver(const uint8_t portNumber, void *)
        : SITLUARTDriver(0, NULL) {}
};

#endif // __AP_HAL_BEAGLEBONE_UARTDRIVER_H__
