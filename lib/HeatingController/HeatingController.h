#pragma once

#include <Arduino.h>
#include <ValveDriver.h>
#include <Thermostat.h>
#include <HeatingControllerListener.hpp>

class HeatingController {
    public:
    HeatingController(const char* name, ValveDriver &vd, Thermostat &t, float temp)
        : name(name), vd(vd), t(t), temp(temp) {
    }
    virtual void handle();
    virtual void setEnabled(boolean enabled);
    virtual boolean isEnabled(void) { return this->enabled; }
    virtual void setTemp(float temp) { this->temp = temp; }
    virtual float getTemp() { return this->temp; }
    const char* getName() { return name; };

    void setListener(HeatingControllerListener *l);
    ValveDriver& getValveDriver() { return vd; };

    protected:
    const char* name;
    ValveDriver& vd;
    Thermostat& t;
    float temp;
    boolean enabled = true;
    HeatingControllerListener *listener = 0;
};

