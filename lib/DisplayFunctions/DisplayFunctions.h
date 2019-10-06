#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <ValveDriver.h>
#include <HeatingController.h>
#include <TimeFunctions.hpp>

boolean beginDisplay(U8G2 &u8g2);

void updateDisplay(U8G2 &u8g2, ValveDriver *valvedriver[], uint8_t n_valvedriver, HeatingController *heatingcontroller[], uint8_t n_heatingcontroller);