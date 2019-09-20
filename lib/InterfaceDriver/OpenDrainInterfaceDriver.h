#pragma once

#include <InterfaceDriver.h>
        
class OpenDrainInterfaceDriver : public InterfaceDriver {
    public:
    OpenDrainInterfaceDriver(uint8_t pin)
        : pin(pin) {};
    virtual uint8_t digitalRead(void);
    virtual void digitalWrite(uint8_t);

    protected:
    uint8_t pin;
};