#pragma once

#include <Thermostat.h>
#include <InterfaceDriver.h>

class OnOffTheromostat : public Thermostat {
    public:
    OnOffTheromostat(InterfaceDriver *ifd, float on_temp, float off_temp)
        : ifd(ifd), on_temp(on_temp), off_temp(off_temp) {}
    virtual float getTemp();
    virtual void handle(void);

    protected:
    InterfaceDriver *ifd;
    float on_temp;
    float off_temp;
};