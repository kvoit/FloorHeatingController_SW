#include <OpenDrainInterfaceDriver.h>

uint8_t OpenDrainInterfaceDriver::digitalRead(void) {
    return ::digitalRead(pin);
}

void OpenDrainInterfaceDriver::digitalWrite(uint8_t value){
    if(value) {
        ::pinMode(pin,INPUT);
    }
    else {
        ::pinMode(pin,OUTPUT);
        ::digitalWrite(pin,LOW); // General safety, since HIGH could create a short circuit. Should not be necessary, though.
    }
}