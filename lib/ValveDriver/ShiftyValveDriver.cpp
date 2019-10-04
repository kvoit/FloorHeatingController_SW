#include <ShiftyValveDriver.h>

#include<RemoteDebug.h>
extern RemoteDebug Debug;

uint8_t ShiftyValveDriver::getState(void) {
    return state;
};

void ShiftyValveDriver::setState(const uint8_t value) {
    state = value;
    return shift.writeBit(pin,value);
};