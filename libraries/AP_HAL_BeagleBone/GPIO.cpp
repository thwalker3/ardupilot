
#include "GPIO.h"

using namespace BeagleBone;

BeagleBoneGPIO::BeagleBoneGPIO()
{}

void BeagleBoneGPIO::init()
{}

void BeagleBoneGPIO::pinMode(uint8_t pin, uint8_t output)
{}

int8_t BeagleBoneGPIO::analogPinToDigitalPin(uint8_t pin)
{
	return -1;
}


uint8_t BeagleBoneGPIO::read(uint8_t pin) {
    return 0;
}

void BeagleBoneGPIO::write(uint8_t pin, uint8_t value)
{}

void BeagleBoneGPIO::toggle(uint8_t pin)
{}

/* Alternative interface: */
AP_HAL::DigitalSource* BeagleBoneGPIO::channel(uint16_t n) {
    return new BeagleBoneDigitalSource(0);
}

/* Interrupt interface: */
bool BeagleBoneGPIO::attach_interrupt(uint8_t interrupt_num, AP_HAL::Proc p,
        uint8_t mode) {
    return true;
}

bool BeagleBoneGPIO::usb_connected(void)
{
    return false;
}

BeagleBoneDigitalSource::BeagleBoneDigitalSource(uint8_t v) :
    _v(v)
{}

void BeagleBoneDigitalSource::mode(uint8_t output)
{}

uint8_t BeagleBoneDigitalSource::read() {
    return _v;
}

void BeagleBoneDigitalSource::write(uint8_t value) {
    _v = value;
}

void BeagleBoneDigitalSource::toggle() {
    _v = !_v;
}
