#pragma once

#include <Arduino.h>
#include <ValveDriver.h>
#include <Thermostat.h>

class HeatingController {
    public:
    HeatingController(ValveDriver *vd, Thermostat *t)
        : vd(vd), t(t) {}
    virtual void handle();
    virtual void setEnabled(boolean enabled);
    virtual boolean isEnabled(void) { return this->enabled; }

    protected:
    boolean enabled = true;
    ValveDriver* vd;
    Thermostat* t;
};

