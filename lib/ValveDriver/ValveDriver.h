#pragma once

#include <Arduino.h>

class ValveDriver {
    public:
    virtual void handle(void) {};
    virtual void setState(const uint8_t newstate) {};
    virtual uint8_t getState() {return 0;};
};