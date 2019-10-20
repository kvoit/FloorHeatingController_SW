#pragma once
#include <Arduino.h>

class HeatingControllerListener {
    public:
    virtual void setEnabled(bool status) = 0;
    virtual void setValveState(bool status) = 0;
    virtual void setValveLevel(uint8_t level) = 0;
};