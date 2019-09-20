#pragma once

#include <Arduino.h>

const uint8_t INTERFACE[] = { 32,  33,  22,  4,   16,  17,  5,   18,  19,  21  };
const uint8_t N_INTERFACE = sizeof(INTERFACE)/sizeof(INTERFACE[0]);


const uint8_t OUTPUTPORT[] = { 8, 9, 10, 11, 12, 13, 14, 15, 0, 1 };
const uint8_t N_OUTPUTPORT = sizeof(OUTPUTPORT)/sizeof(OUTPUTPORT[0]);

const uint8_t LED_PIN = 23;

const uint8_t OUTPUT_CLOCK_PIN = 14;
const uint8_t OUTPUT_DATA_PIN = 13;
const uint8_t OUTPUT_LATCH_PIN = 25;
