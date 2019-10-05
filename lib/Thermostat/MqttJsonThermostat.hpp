#pragma once

#include <Arduino.h>
#include <MqttThermostat.hpp>
#include <ArduinoJson.h>

class MqttJsonThermostat : public MqttThermostat {
    public:
    MqttJsonThermostat(MqttController* mqtt_controller, const char* topic, const char* json_name="temperature")
        : MqttThermostat(mqtt_controller,topic), json_name(json_name) {};
    virtual bool parsePayload(const char* payload);
    virtual float getTemp() { return temp; }

    protected:
    const char* json_name;

};