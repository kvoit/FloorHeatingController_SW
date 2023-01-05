#include <MqttControllerInterface.hpp>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

void MqttControllerInterface::handle() {
    INTERVAL(600000,millis()) { // Occationally update MQTT status
        this->setEnabled(this->hc.isEnabled());
    }
}

void MqttControllerInterface::setEnabled(bool status, boolean settopic) {
    char buffer[64];
    strncpy(buffer,topic,(63<baselength)?63:baselength);
    buffer[(64<baselength)?64:(baselength)] = '\0';

    strncat(buffer,"/enabled",63);
    mqtt_controller.sendMessage(buffer,status?"1":"0");
    debugD("Setting Enable status to %i (%s)",status,topic);
    if(settopic) {
        strncat(buffer,"/set",63);
        mqtt_controller.sendMessage(buffer,status?"1":"0");
    }
}

void MqttControllerInterface::setValveState(bool state, boolean settopic) {
    debugD("Setting valve state");
    char buffer[64];
    strncpy(buffer,topic,(63<baselength)?63:baselength);
    buffer[(64<baselength)?64:(baselength)] = '\0';

    strncat(buffer,"/valve_state",63);
    mqtt_controller.sendMessage(buffer,state?"1":"0");

    if(settopic) {
        strncat(buffer,"/set",63);
        mqtt_controller.sendMessage(buffer,state?"1":"0");
    }
}

void MqttControllerInterface::setValveLevel(uint8_t level, boolean settopic) {
    char buffer[64];
    strncpy(buffer,topic,(63<baselength)?63:baselength);
    buffer[(64<baselength)?64:(baselength)] = '\0';

    strncat(buffer,"/valve_level",63);
    char buffer2[10];
    itoa(level,buffer2,10);
    debugD("Reporting level %s (%d) to %s",buffer2,level,buffer);
    mqtt_controller.sendMessage(buffer,buffer2);

    if(settopic) {
        strncat(buffer,"/set",63);
        mqtt_controller.sendMessage(buffer,buffer2);
    }
}

void MqttControllerInterface::setTemp(float temp, boolean settopic) {
    char buffer[64];  
    strncpy(buffer,topic,(63<baselength)?63:baselength);
    buffer[(64<baselength)?64:(baselength)] = '\0';

    strncat(buffer,"/temp",63);
    char buffer2[10];
    snprintf(buffer2,10,"%.2f",temp);
    mqtt_controller.sendMessage(buffer,buffer2);

    if(settopic) {
        strncat(buffer,"/set",63);
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
                debugI("Enabling %s (%s)",hc.getName(),topic);
                hc.setEnabled(1);
                return true;
            } else if ( !strcmp(payload, "0") ) {
                debugI("Disabling %s (%s)",hc.getName(),topic);
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

void MqttControllerInterface::sendMQTTDiscoveryMsg() {
    DynamicJsonDocument doc(1024);
    size_t n;

    char discovery_msg[1024]{};  
    char name_buffer[64]{};
    char unique_id_buffer[64]{};

    char base_topic[baselength+1]{};
    strncpy(base_topic,topic,baselength);

    char discovery_topic[128]{};
    char mode_state_topic[128]{};
    char mode_command_topic[128]{};
    char temperature_command_topic[128]{};
    char temperature_state_topic[128]{};

    // Climate
    doc.clear();

    snprintf(name_buffer, sizeof(name_buffer), "Thermostat (%s)", hc.getName());
    snprintf(unique_id_buffer, sizeof(name_buffer), "heating_climate_%s)", hc.getName());
    snprintf(discovery_topic, sizeof(discovery_topic), "homeassistant/climate/heating/climate_%s/config", hc.getName());
    snprintf(mode_state_topic, sizeof(mode_state_topic), "%s/valve_state", base_topic);
    snprintf(mode_command_topic, sizeof(mode_command_topic), "%s/valve_state/set", base_topic);
    snprintf(temperature_state_topic, sizeof(mode_state_topic), "%s/temp", base_topic);
    snprintf(temperature_command_topic, sizeof(mode_command_topic), "%s/temp/set", base_topic);
    
    doc["name"] = name_buffer;
    doc["unique_id"] = unique_id_buffer;
    doc["modes"][0]   = "off";
    doc["modes"][1]   = "heat";
    doc["mode_state_topic"] = mode_state_topic;
    doc["mode_state_template"] = "{% set values = { '0':'off', '1':'heat'} %} {{ values[value] if value in values.keys() else 'off' }}";
    doc["mode_command_topic"] = mode_command_topic;
    doc["mode_command_template"] = "{% set values = { 'off':'0', 'heat':'1'} %} {{ values[value] if value in values.keys() else 'off' }}";
    doc["temperature_state_topic"] = temperature_state_topic;
    doc["temperature_command_topic"] = temperature_command_topic;
    if(current_temperature_topic != NULL) {
        doc["current_temperature_topic"] = current_temperature_topic;
    }
    doc["temp_step"] = 0.1;
    doc["precision"] = 0.1;
    doc["device"]["name"] = "Heating Central Classic";
    doc["device"]["identifiers"][0] = "123654AB";

    n = serializeJson(doc, discovery_msg);   
    mqtt_controller.sendMessage(discovery_topic, discovery_msg, true);
    mqtt_controller.handle();

    // switch
    doc.clear();

    snprintf(name_buffer, sizeof(name_buffer), "Heating (%s)", hc.getName());
    snprintf(unique_id_buffer, sizeof(name_buffer), "heating_switch_%s)", hc.getName());
    snprintf(discovery_topic, sizeof(discovery_topic), "homeassistant/switch/heating/switch_%s/config", hc.getName());
    snprintf(mode_state_topic, sizeof(mode_state_topic), "%s/enabled", base_topic);
    snprintf(mode_command_topic, sizeof(mode_command_topic), "%s/enabled/set", base_topic);

    doc["name"] = name_buffer;
    doc["unique_id"] = unique_id_buffer;
    doc["state_topic"] = mode_state_topic;
    doc["command_topic"] = mode_command_topic;
    doc["payload_on"] = "1";
    doc["payload_off"] = "0";
    doc["optimistic"] = false;
    doc["retain"] = true;

    n = serializeJson(doc, discovery_msg);   
    mqtt_controller.sendMessage(discovery_topic, discovery_msg, true);
    mqtt_controller.handle();

    // binary_sensor
    doc.clear();

    snprintf(name_buffer, sizeof(name_buffer), "Valve state (%s)", hc.getName());
    snprintf(unique_id_buffer, sizeof(name_buffer), "heating_valve_state_%s)", hc.getName());
    snprintf(discovery_topic, sizeof(discovery_topic), "homeassistant/binary_sensor/heating/binary_sensor_%s/config", hc.getName());
    snprintf(mode_state_topic, sizeof(mode_state_topic), "%s/valve_state", base_topic);

    doc["name"] = name_buffer;
    doc["unique_id"] = unique_id_buffer;
    doc["state_topic"] = mode_state_topic;
    doc["payload_on"] = "1";
    doc["payload_off"] = "0";

    n = serializeJson(doc, discovery_msg);   
    mqtt_controller.sendMessage(discovery_topic, discovery_msg, true);
    mqtt_controller.handle();
}