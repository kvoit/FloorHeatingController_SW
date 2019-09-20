#include <ShiftyValveDriver.h>

uint8_t ShiftyValveDriver::getState(void) {
    return shift.readBit(pin);
};

void ShiftyValveDriver::setState(const uint8_t value) {
    return shift.writeBit(pin,value);
};