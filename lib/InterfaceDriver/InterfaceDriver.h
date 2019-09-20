#pragma once

#include <Arduino.h>

class InterfaceDriver {
    public:
        void handle(void) {};
        virtual uint8_t digitalRead(void) { return 0; };
        virtual void digitalWrite(uint8_t) {};
};