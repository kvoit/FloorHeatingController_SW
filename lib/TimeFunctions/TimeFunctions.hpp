#pragma once
#ifndef TIMEFUNCTONS_HPP
#define TIMEFUNCTONS_HPP

#include <WiFi.h>
#include <globalTimeinfo.h>

void updateNTP(uint32_t gmtOffset_sec, uint32_t dlsOffset_sec, const char* ntpserver);
void printLocalTime();

#endif