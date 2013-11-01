
#ifndef __AP_HAL_BEAGLEBONE_NAMESPACE_H__
#define __AP_HAL_BEAGLEBONE_NAMESPACE_H__

/* While not strictly required, names inside the BeagleBone namespace are prefixed
 * with BeagleBone for clarity. (Some of our users aren't familiar with all of the
 * C++ namespace rules.)
 */

namespace BeagleBone {
    class BeagleBoneUARTDriver;
    class BeagleBoneI2CDriver;
    class BeagleBoneSPIDeviceManager;
    class BeagleBoneSPIDeviceDriver;
    class BeagleBoneAnalogSource;
    class BeagleBoneAnalogIn;
    class BeagleBoneStorage;
    class BeagleBoneGPIO;
    class BeagleBoneDigitalSource;
    class BeagleBoneRCInput;
    class BeagleBoneRCOutput;
    class BeagleBoneSemaphore;
    class BeagleBoneScheduler;
    class BeagleBoneUtil;
}

#endif // __AP_HAL_BEAGLEBONE_NAMESPACE_H__

