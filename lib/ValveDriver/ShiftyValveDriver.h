#pragma once

#include <ValveDriver.h>
#include <Shifty.h>

class ShiftyValveDriver : public ValveDriver {
    public:
    ShiftyValveDriver(Shifty* shift, uint8_t pin)
        : shift(shift), pin(pin), state(LOW) {}

    virtual void setState(const uint8_t newstate);
    virtual uint8_t getState();

    protected:
    Shifty* shift;
    uint8_t pin;
    uint8_t state;
};