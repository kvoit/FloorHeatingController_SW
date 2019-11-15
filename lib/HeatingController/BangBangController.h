#pragma once

#include <HeatingController.h>

class BangBangController : public HeatingController {
    public:
        BangBangController(const char* name, ValveDriver &vd, Thermostat &t, float temp, float hysteresis=0.2)
            : HeatingController(name, vd,t,temp), hysteresis(hysteresis) {};

        virtual void handle();

    protected:
        float hysteresis;
};