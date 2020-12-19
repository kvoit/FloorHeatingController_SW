#pragma once
#include <Arduino.h>

class HeatingControllerListener {
    public:
    virtual void setEnabled(bool status, boolean persist = true) {};
    virtual void setValveState(bool status, boolean persist = true) {};
    virtual void setValveLevel(uint8_t level, boolean persist = true) {};
    virtual void setTemp(float temp, boolean persist = true) {};

    virtual void handle(void) {};

    // We do not declare a heating controller here, since we might want to use a child class
};