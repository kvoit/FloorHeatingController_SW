#include <OpenDrainInterfaceDriver.h>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

uint8_t OpenDrainInterfaceDriver::digitalRead(void) {
    uint8_t pin_value = ::digitalRead(pin);
    // debugV("Pin value read to %d", pin_value);
    return pin_value;
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