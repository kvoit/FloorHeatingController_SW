#include <TimerControllerInterface.hpp>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

void TimerControllerInterface::handle() {
  if(!getLocalTime(&timeinfo)){
      debugE("Failed to obtain NTP time for time command");
      return;
  }
  for(TimeControllerCommand* c : commands) {
    if(c->run==false && (c->dow==timeinfo.tm_wday || c->dow==-1) && c->hour==timeinfo.tm_hour && c->minute==timeinfo.tm_min) {
      c->run=true;
      if(c->do_enable) {
          debugD("Timer: Setting enable status to %d",c->enable);
          hc.setEnabled(c->enable);
      }
      if(c->do_temp) {
          debugD("Timer: Setting temp to %d",c->temp);
          hc.setTemp(c->temp);
      }
      if(c->do_valve_level) {
          debugD("Timer: Setting level to %d",c->valve_level);
          hc.getValveDriver().setOnLevel(c->valve_level);
      }
    } else if(c->run==true && ((c->dow!=timeinfo.tm_wday && c->dow!=-1) || c->hour!=timeinfo.tm_hour || c->minute!=timeinfo.tm_min)) {        
      c->run=false;
    } else {
    }
  }
}

void TimerControllerInterface::add(TimeControllerCommand* com) {
  commands.push_back(com);
}

bool operator==(TimeControllerCommand& com1, TimeControllerCommand&& com2) {
  return com1.dow==com2.dow && com1.hour==com2.hour && com1.minute==com2.minute;
}
TimeControllerCommand& operator+(TimeControllerCommand& com1, TimeControllerCommand&& com2) {
  return com1;
}