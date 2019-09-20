#ifndef __INTERVAL__h__
#define __INTERVAL__h__

#include <Arduino.h>

extern bool DoINTERVAL; // Merker für das Interval Macro

// Start of Interval Macro
#define INTERVAL(interval)                     \
{                                              \
  static unsigned long lastHit = 0;            \
  DoINTERVAL = millis() - lastHit >= interval; \
  if(DoINTERVAL) lastHit = millis();           \
}                                              \
if(DoINTERVAL)
// End of Interval Macro 


#endif