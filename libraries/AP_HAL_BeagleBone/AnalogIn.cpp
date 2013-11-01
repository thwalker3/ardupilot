#include "AnalogIn.h"

using namespace BeagleBone;

BeagleBoneAnalogSource::BeagleBoneAnalogSource(float v) :
    _v(v)
{}

float BeagleBoneAnalogSource::read_average() {
    return _v;
}

float BeagleBoneAnalogSource::voltage_average() {
    return 5.0 * _v / 1024.0;
}

float BeagleBoneAnalogSource::voltage_latest() {
    return 5.0 * _v / 1024.0;
}

float BeagleBoneAnalogSource::read_latest() {
    return _v;
}

void BeagleBoneAnalogSource::set_pin(uint8_t p)
{}

void BeagleBoneAnalogSource::set_stop_pin(uint8_t p)
{}

void BeagleBoneAnalogSource::set_settle_time(uint16_t settle_time_ms)
{}

BeagleBoneAnalogIn::BeagleBoneAnalogIn()
{}

void BeagleBoneAnalogIn::init(void* machtnichts)
{}

AP_HAL::AnalogSource* BeagleBoneAnalogIn::channel(int16_t n) {
    return new BeagleBoneAnalogSource(1.11);
}


