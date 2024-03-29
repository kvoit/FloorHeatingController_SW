#pragma once

#include <Arduino.h>

#include<RemoteDebug.h>
extern RemoteDebug Debug;

class ValveDriver {
    public:
    virtual void handle(void) {};
    virtual void setState(const uint8_t newstate)=0;
    virtual uint8_t getState() = 0;
    virtual uint8_t getLevel(void) { return 0; };
};