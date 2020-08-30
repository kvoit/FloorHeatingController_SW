#pragma once

#include <Arduino.h>
#include <AnalogValveDriver.hpp>
#include <Thermostat.h>
#include <HeatingControllerListener.hpp>

class HeatingController {
    public:
    HeatingController(const char* name, AnalogValveDriver &vd, Thermostat &t, float temp)
        : name(name), vd(vd), t(t) {
            this->setTemp(temp);
    }
    virtual void handle();
    virtual void setEnabled(boolean enabled);
    virtual boolean isEnabled(void) { return this->enabled; }
    virtual void setTemp(float temp);
    virtual float getTemp() { return this->temp; }
    virtual float getThermTemp() { return t.getTemp(); }
    const char* getName() { return name; };

    void setListener(HeatingControllerListener *l);
    AnalogValveDriver& getValveDriver() { return vd; };

    protected:
    const char* name;
    AnalogValveDriver& vd;
    Thermostat& t;
    float temp;
    boolean enabled = true;
    HeatingControllerListener *listener = 0;
};

