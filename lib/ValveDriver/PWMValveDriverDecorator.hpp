#pragma once 

#include<AnalogValveDriver.hpp>

class PWMValveDriverDecorator : public AnalogValveDriver
{
    public:
    PWMValveDriverDecorator(ValveDriver &vd, uint32_t pwm_period=3600000, uint8_t on_level=255, uint8_t off_level=0, uint8_t current_level=0, uint32_t offset=0) 
    : vd(vd), pwm_period(pwm_period), pwm_level(current_level), on_level(on_level), off_level(off_level) {
        last_on = millis()-offset;
    };

    virtual void setLevel(uint8_t pwm_level) { this->pwm_level = pwm_level; };
    virtual uint8_t getLevel(void) {return pwm_level;}

    virtual void setState(uint8_t state) { if(state) pwm_level=on_level; else pwm_level=off_level; this->handle(); };
    virtual uint8_t getState(void) {return pwm_level>off_level; };

    virtual void handle(void);

    protected:
    ValveDriver &vd;

    const uint32_t pwm_period;
    uint8_t pwm_level;

    const uint8_t on_level;
    const uint8_t off_level;

    uint32_t last_on;

    const uint8_t MAX_PWM_LEVEL = 255;
};