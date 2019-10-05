#pragma once

#include <HeatingController.h>

class BangBangController : public HeatingController {
    public:
        BangBangController(ValveDriver *vd, Thermostat *t, float temp, float hysteresis=2)
            : HeatingController(vd,t,temp), hysteresis(hysteresis) {};

        virtual void handle();

    protected:
        float hysteresis;
};