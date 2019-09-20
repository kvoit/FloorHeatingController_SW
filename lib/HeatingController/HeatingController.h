#pragma once

#include <Arduino.h>
#include <ValveDriver.h>
#include <Thermostat.h>

class HeatingController {
    public:
        HeatingController(ValveDriver &vd, Thermostat &t)
            : vd(vd), t(t) {};
        virtual void handle() { t.handle(); vd.handle(); };

    protected:
        ValveDriver vd;
        Thermostat t;
};

