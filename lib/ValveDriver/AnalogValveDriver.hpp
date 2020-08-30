#pragma once

#include<ValveDriver.h>

class AnalogValveDriver : public ValveDriver
{
    public:
    virtual void setLevel(uint8_t level);
    virtual uint8_t getLevel(void);
};