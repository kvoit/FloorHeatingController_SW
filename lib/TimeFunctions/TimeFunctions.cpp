#include <TimeFunctions.hpp>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

void updateNTP(uint32_t gmtOffset_sec, uint32_t dlsOffset_sec, const char* ntpserver) {
    configTime(gmtOffset_sec, dlsOffset_sec, ntpserver);
}

void printLocalTime()
{
  if(!getLocalTime(&timeinfo)){
    debugE("Failed to obtain NTP time");
    return;
  }
  debugD("%04d/%02d/%02d %02d:%02d:%02d",1900+timeinfo.tm_year,timeinfo.tm_mon+1,timeinfo.tm_mday,timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
}