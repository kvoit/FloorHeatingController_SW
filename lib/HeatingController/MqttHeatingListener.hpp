#pragma once

#include<MqttController.hpp>
#include<HeatingControllerListener.hpp>

class MqttHeatingListener : public HeatingControllerListener {
    public:
    MqttHeatingListener(MqttController &mqtt, const char* topic) 
        : mqtt(mqtt), topic(topic) {}

    virtual void setEnabled(bool status);
    virtual void setValveState(bool status);
    virtual void setValveLevel(uint8_t level);

    MqttController &mqtt;
    const char* topic;
};