#pragma once

#include <Arduino.h>

class InterfaceDriver {
    public:
        virtual void handle(void) {};
        virtual uint8_t digitalRead(void)=0;
        virtual void digitalWrite(uint8_t)=0;
};