#pragma once

#include<ValveDriver.h>

class AnalogValveDriver : public ValveDriver
{
    public:
    virtual void setLevel(uint8_t level);
    virtual void setOnLevel(uint8_t onfflevel);
    virtual void setOffLevel(uint8_t offlevel);
    virtual uint8_t getLevel(void);
};