#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <MqttListener.hpp>
#include <Thermostat.h>

class MqttThermostat : public MqttListener, public Thermostat {
    public:
    MqttThermostat(MqttController* mqtt_controller, const char* topic)
        : MqttListener(mqtt_controller,topic) {};
    virtual bool parsePayload(const char* payload);
    virtual float getTemp() { return temp; }

    protected:
    float temp = 1000; 
};