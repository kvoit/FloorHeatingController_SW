#pragma once

#include <Arduino.h>
#include <MqttListener.hpp>
#include <HeatingController.h>

class MqttHcEnabler : public MqttListener {
    public:
    MqttHcEnabler(MqttController& mqtt_controller, const char* topic, HeatingController* hc)
        : MqttListener(mqtt_controller, topic), hc(hc) {};
    virtual bool parsePayload(const char* payload);

    protected:
    HeatingController* hc;
};