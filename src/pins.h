#pragma once

#include <WiFi.h>

const uint8_t N_INTERFACE = 10;
const uint8_t INTERFACE[N_INTERFACE] = { 32,  33,  22,  4,   16,  17,  5,   18,  19,  21  };
uint8_t interface_state[N_INTERFACE] = { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW };

uint8_t id = 0;
uint8_t OUTPUTSTATE = LOW;
const uint8_t N_OUTPUTPORT = 10;
const uint8_t OUTPUTPORT[N_OUTPUTPORT] = { 8, 9, 10, 11, 12, 13, 14, 15, 0, 1 };

const uint8_t LED_PIN = 23;

const uint8_t OUTPUT_CLOCK_PIN = 14;
const uint8_t OUTPUT_DATA_PIN = 13;
const uint8_t OUTPUT_LATCH_PIN = 25;
