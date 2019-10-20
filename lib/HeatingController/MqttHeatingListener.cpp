#include<MqttHeatingListener.hpp>

#include<RemoteDebug.h>
extern RemoteDebug Debug;

void MqttHeatingListener::setEnabled(bool status) {
    char buffer[64];
    strncpy(buffer,topic,64);
    strncat(buffer,"/enabled",64);
    mqtt.sendMessage(buffer,status?"1":"0");
}

void MqttHeatingListener::setValveState(bool state) {
    debugD("Setting valve state");
    char buffer[64];
    strncpy(buffer,topic,64);
    strncat(buffer,"/valve_state",64);
    mqtt.sendMessage(buffer,state?"1":"0");
}

void MqttHeatingListener::setValveLevel(uint8_t level) {
    char buffer[64];
    strncpy(buffer,topic,64);
    strncat(buffer,"/valve_level",64);
    char buffer2[10];
    itoa(level,buffer2,10);
    mqtt.sendMessage(buffer,buffer2);
}
