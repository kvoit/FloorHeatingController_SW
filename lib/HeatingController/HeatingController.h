#pragma once

#include <Arduino.h>
#include <AnalogValveDriver.hpp>
#include <Thermostat.h>
#include <HeatingControllerListener.hpp>
#include <vector>

class HeatingController {
    public:
    HeatingController(const char* name, AnalogValveDriver &vd, Thermostat &t, float temp)
        : name(name), vd(vd), t(t) {
            this->setTemp(temp,true);
    }
    virtual void handle();
    virtual void setEnabled(boolean enabled);
    virtual boolean isEnabled(void) { return this->enabled; }
    virtual void setTemp(float temp, boolean silent = false);
    virtual void setValveLevel(uint8_t valve_level);
    virtual float getTemp() { return this->temp; }
    virtual float getThermTemp() { return t.getTemp(); }
    const char* getName() { return name; };

    void addListener(HeatingControllerListener *l);
    AnalogValveDriver& getValveDriver() { return vd; };

    protected:
    const char* name;
    AnalogValveDriver& vd;
    Thermostat& t;
    volatile float temp;
    volatile boolean enabled = true;
    std::vector<HeatingControllerListener*> listener;
};

