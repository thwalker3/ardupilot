#include <AP_HAL.h>
#if CONFIG_HAL_BOARD == HAL_BOARD_BEAGLEBONE

#include "HAL_BeagleBone_Class.h"
#include "AP_HAL_BeagleBone_Private.h"

#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

using namespace BeagleBone;

// 3 serial ports on BeagleBone for now
static BeagleBoneUARTDriver uartADriver(true);
static BeagleBoneUARTDriver uartBDriver(false);
static BeagleBoneUARTDriver uartCDriver(false);

static BeagleBoneSemaphore  i2cSemaphore;
static BeagleBoneI2CDriver  i2cDriver(&i2cSemaphore, "/dev/i2c-2");
static BeagleBoneSPIDeviceManager spiDeviceManager;
static BeagleBoneAnalogIn analogIn;
static BeagleBoneStorage storageDriver;
static BeagleBoneGPIO gpioDriver;
static BeagleBoneRCInput rcinDriver;
static BeagleBoneRCOutput rcoutDriver;
static BeagleBoneScheduler schedulerInstance;
static BeagleBoneUtil utilInstance;

HAL_BeagleBone::HAL_BeagleBone() :
    AP_HAL::HAL(
        &uartADriver,
        &uartBDriver,
        &uartCDriver,
        &i2cDriver,
        &spiDeviceManager,
        &analogIn,
        &storageDriver,
        &uartADriver,
        &gpioDriver,
        &rcinDriver,
        &rcoutDriver,
        &schedulerInstance,
        &utilInstance)
{}

extern const AP_HAL::HAL& hal;

void HAL_BeagleBone::init(int argc,char* const argv[]) const 
{
    int opt;
    /*
      parse command line options
     */
    while ((opt = getopt(argc, argv, "A:B:C:h")) != -1) {
        switch (opt) {
        case 'A':
            uartADriver.set_device_path(optarg);
            break;
        case 'B':
            uartBDriver.set_device_path(optarg);
            break;
        case 'C':
            uartCDriver.set_device_path(optarg);
            break;
        case 'h':
            printf("Usage: -A uartAPath -B uartBPath -C uartCPath\n");
            exit(0);
        default:
            printf("Unknown option '%c'\n", (char)opt);
            exit(1);
        }
    }

    hal.scheduler->init(NULL);
    hal.uartA->begin(115200);
    hal.i2c->begin();
    hal.rcin->init(NULL);
    hal.rcout->init(NULL);
    //hal.analogin->init(NULL);
    //hal.gpio->init();
    //hal.spi->init(NULL);
}

const HAL_BeagleBone AP_HAL_BeagleBone;

#endif
