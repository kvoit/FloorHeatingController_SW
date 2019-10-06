#pragma once

#include <Thermostat.h>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

template<uint16_t T>
class TheromostatMaxDecorator : public Thermostat {
    public:
    TheromostatMaxDecorator(Thermostat *t, uint32_t retain_interval)
        : t(t), retain_interval(retain_interval) {
        last_retain = millis();
        std::fill(temp_history,temp_history+n_temp_history-1,-275.0);
        temp_history[0] = 10001.0; // Will be overwritten during first history write
    }

    virtual float getTemp() {
        if (temp_history[i_temp_history] >= 10000) // Catches nonsense values of uninitialized thermostats
            return t->getTemp();
        else
            return *std::max_element(temp_history,temp_history+n_temp_history-1);
    }

    virtual void handle(void) {
        t->handle();

        if(millis()-last_retain > retain_interval/10) {
            last_retain = millis();
            temp_history[i_temp_history] = t->getTemp();
            i_temp_history = (i_temp_history+1)%n_temp_history;
        }
    }

    protected:
    Thermostat *t;
    const uint32_t retain_interval;
    uint32_t last_retain;
    float temp_history[T];
    const uint16_t n_temp_history = T;
    uint16_t i_temp_history = 0;
};
