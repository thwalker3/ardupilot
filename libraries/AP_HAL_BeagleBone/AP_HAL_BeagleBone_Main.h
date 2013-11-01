

#ifndef __AP_HAL_BEAGLEBONE_MAIN_H__
#define __AP_HAL_BEAGLEBONE_MAIN_H__

#if CONFIG_HAL_BOARD == HAL_BOARD_BEAGLEBONE
#define AP_HAL_MAIN() extern "C" {\
int main (int argc, char * const argv[]) {        \
	hal.init(argc, argv);			\
        setup();\
        hal.scheduler->system_initialized(); \
        for(;;) loop();\
        return 0;\
    }\
    }
#endif // HAL_BOARD_BEAGLEBONE

#endif // __AP_HAL_BEAGLEBONE_MAIN_H__
