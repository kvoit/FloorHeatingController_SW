#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <ValveDriver.h>

boolean beginDisplay(U8G2 &u8g2);

void updateDisplay(U8G2 &u8g2, ValveDriver *valvedriver[], uint8_t n_valvedriver);