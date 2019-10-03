#pragma once

#include <Arduino.h>
#include <ValveDriver.h>
#include <Thermostat.h>

class HeatingController {
    public:
    HeatingController(ValveDriver *vd, Thermostat *t, float temp)
        : vd(vd), t(t), temp(temp) {}
    virtual void handle();
    virtual void setEnabled(boolean enabled);
    virtual boolean isEnabled(void) { return this->enabled; }
    virtual void setTemp(float temp) { this->temp = temp; }
    virtual float getTemp() { return this->temp; }

    protected:
    ValveDriver* vd;
    Thermostat* t;
    float temp;
    boolean enabled = true;
};

