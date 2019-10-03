#pragma once

#include <HeatingController.h>

class BangBangController : public HeatingController {
    public:
        BangBangController(ValveDriver *vd, Thermostat *t, float temp, float hysteresis)
            : HeatingController(vd,t,temp), hysteresis(hysteresis) {};
        BangBangController(ValveDriver *vd, Thermostat *t, float temp)
            : BangBangController(vd,t,temp,3) {};

        virtual void handle();

    protected:
        float hysteresis;
};