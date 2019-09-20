#pragma once
#include <Arduino.h>

class Thermostat {
    public:
        virtual void handle(void) {};
        virtual float getTemp() {return 0;};
};