#pragma once

#include <MqttController.hpp>

class MqttController;
class MqttListener {
    public:
    MqttListener(MqttController* mqtt_controller, const char* topic);

    virtual void begin() {};
    virtual const char* getMQTTTopic() { return topic; };
    virtual bool parsePayload(const char *payload)=0;

    protected:
    MqttController* mqtt_controller;
    const char* topic;
};