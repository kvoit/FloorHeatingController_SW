#pragma once

#include <HeatingController.h>

class BangBangController : public HeatingController {
    public:
        BangBangController(ValveDriver &vd, Thermostat &t, float switch_temp, float hysteresis)
            : HeatingController(vd,t), switch_temp(switch_temp), hysteresis(hysteresis) {};
        BangBangController(ValveDriver &vd, Thermostat &t, float switch_temp)
            : BangBangController(vd,t,switch_temp,3) {};

        virtual void handle();

    protected:
        float switch_temp;
        float hysteresis;
};