#include <MqttControllerInterface.hpp>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

void MqttControllerInterface::setEnabled(bool status) {
    char buffer[64];
    strncpy(buffer,topic,64);
    strncat(buffer,"/enabled",64);
    mqtt_controller.sendMessage(buffer,status?"1":"0");
}

void MqttControllerInterface::setValveState(bool state) {
    debugD("Setting valve state");
    char buffer[64];
    strncpy(buffer,topic,64);
    strncat(buffer,"/valve_state",64);
    mqtt_controller.sendMessage(buffer,state?"1":"0");
}

void MqttControllerInterface::setValveLevel(uint8_t level) {
    char buffer[64];
    strncpy(buffer,topic,64);
    strncat(buffer,"/valve_level",64);
    char buffer2[10];
    itoa(level,buffer2,10);
    mqtt_controller.sendMessage(buffer,buffer2);
}

void MqttControllerInterface::setTemp(float temp) {
    char buffer[64];
    strncpy(buffer,topic,64);
    strncat(buffer,"/temp",64);
    char buffer2[10];
    snprintf(buffer2,10,"%.2f",temp);
    mqtt_controller.sendMessage(buffer,buffer2);
}


bool MqttControllerInterface::parsePayload(const char *payload) {
    if ( !strcmp(payload, "ON") )
    {
        hc.setEnabled(1);
        return true;
    }
    else if ( !strcmp(payload, "OFF") )
    {
        hc.setEnabled(0);
        return true;
    }
    else
    {
        debugD("%s received command '%s'",hc.getName(),payload);
        if(strlen(payload)<6) //Cannot contain any command
            return false;
        if(strstr(payload, "TEMP") != NULL) {
            float set_temp = atof(&payload[4]);
            debugD("Setting %s temp to %.2f",hc.getName(),set_temp);
            hc.setTemp(set_temp);
            return true;
        } else if (strstr(payload, "VLEVEL") != NULL) {
            uint8_t set_level = atoi(&payload[6]);
            debugD("Setting %s valve level to %d",hc.getName(),set_level);
            hc.getValveDriver().setLevel(set_level);
            return true;
        }
    }
    return false;
}