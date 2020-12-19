#include<MqttThermostat.hpp>

#include <RemoteDebug.h>
extern RemoteDebug Debug;


bool MqttThermostat::parsePayload(const char *payload) {
    temp = atof(payload);
    debugD("Setting temp to %f from %s",temp,this->getMQTTTopic());
    return false;
}