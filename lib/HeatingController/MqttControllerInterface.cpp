#include <MqttControllerInterface.hpp>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

void MqttControllerInterface::handle() {
    INTERVAL(600000,millis()) {
        this->setEnabled(this->hc.isEnabled());
    }
}

void MqttControllerInterface::setEnabled(bool status, boolean settopic) {
    char buffer[64];
    strncpy(buffer,topic,(63<baselength)?63:baselength);
    buffer[(64<baselength)?64:(baselength)] = '\0';

    strncat(buffer,"/enabled",64);
    mqtt_controller.sendMessage(buffer,status?"1":"0");

    if(settopic) {
        strncat(buffer,"/set",64);
        mqtt_controller.sendMessage(buffer,status?"1":"0");
    }
}

void MqttControllerInterface::setValveState(bool state, boolean settopic) {
    debugD("Setting valve state");
    char buffer[64];
    strncpy(buffer,topic,(63<baselength)?63:baselength);
    buffer[(64<baselength)?64:(baselength)] = '\0';

    strncat(buffer,"/valve_state",64);
    mqtt_controller.sendMessage(buffer,state?"1":"0");

    if(settopic) {
        strncat(buffer,"/set",64);
        mqtt_controller.sendMessage(buffer,state?"1":"0");
    }
}

void MqttControllerInterface::setValveLevel(uint8_t level, boolean settopic) {
    char buffer[64];
    strncpy(buffer,topic,(63<baselength)?63:baselength);
    buffer[(64<baselength)?64:(baselength)] = '\0';

    strncat(buffer,"/valve_level",64);
    char buffer2[10];
    itoa(level,buffer2,10);
    debugD("Reporting level %s (%d) to %s",buffer2,level,buffer);
    mqtt_controller.sendMessage(buffer,buffer2);

    if(settopic) {
        strncat(buffer,"/set",64);
        mqtt_controller.sendMessage(buffer,buffer2);
    }
}

void MqttControllerInterface::setTemp(float temp, boolean settopic) {
    char buffer[64];  
    strncpy(buffer,topic,(63<baselength)?63:baselength);
    buffer[(64<baselength)?64:(baselength)] = '\0';

    strncat(buffer,"/temp",64);
    char buffer2[10];
    snprintf(buffer2,10,"%.2f",temp);
    mqtt_controller.sendMessage(buffer,buffer2);

    if(settopic) {
        strncat(buffer,"/set",64);
        mqtt_controller.sendMessage(buffer,buffer2);
    }
}


bool MqttControllerInterface::presentMessage(const char *topic,const char *payload) {
    if(!strncmp(topic,this->getMQTTTopic(),baselength)) {
        if(!strcmp(&topic[baselength],"/temp/set")) {
            float set_temp = atof(payload);
            debugI("Setting temp for %s to %.2fC",hc.getName(),set_temp);
            hc.setTemp(set_temp);
            return true;
        } else if(!strcmp(&topic[baselength],"/enabled/set")) {
            if ( !strcmp(payload, "1") ) {
                debugI("Enabling %s",hc.getName());
                hc.setEnabled(1);
                return true;
            } else if ( !strcmp(payload, "0") ) {
                debugI("Disabling %s",hc.getName());
                hc.setEnabled(0);
                return true;
            }
            debugI("Unknown command for %s",hc.getName());
            return false;
        } else if(!strcmp(&topic[baselength],"/valve_level/set")) {
            uint8_t set_level = atoi(payload);
            debugI("Setting on valve level for %s (%s) to %d (%s)",hc.getName(), topic, set_level, payload);
            hc.getValveDriver().setOnLevel(set_level);
            return true;
        }
    }
    return false;
}