#pragma once
#include <Arduino.h>

class OutputDriver {
    public:
    virtual void writeOutput(const uint8_t newstate);
    uint8_t getState() const { return state; }

    protected:
    uint8_t state;
};