#include<MqttHeatingListener.hpp>

void MqttHeatingListener::setEnabled(bool status) {
    char buffer[128];
    strcat(buffer,"enabled/");
    mqtt.sendMessage(buffer,status?"1":"0");
}

void MqttHeatingListener::setValveState(bool state) {
    char buffer[128];
    strcat(buffer,"valve_state/");
    mqtt.sendMessage(buffer,state?"1":"0");
}

void MqttHeatingListener::setValveLevel(uint8_t level) {
    char buffer[128];
    strcat(buffer,"valve_level/");
    char buffer2[4];
    itoa(level,buffer2,10);
    mqtt.sendMessage(buffer,buffer2);
}
