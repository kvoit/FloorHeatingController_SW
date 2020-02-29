#pragma once

#include<Arduino.h>
#include<MqttListener.hpp>
#include<HeatingController.h>
#include<MqttController.hpp>
#include<HeatingControllerListener.hpp>

using namespace std;

class MqttControllerInterface : public MqttListener, public HeatingControllerListener {
    public:
    MqttControllerInterface(MqttController& mqtt_controller, const char* topic, HeatingController& hc)
    : MqttListener(mqtt_controller, string(topic)+hc.getName()), hc(hc) {
        hc.setListener(this);
    };
    private:


    public:
    virtual void setEnabled(bool status);
    virtual void setValveState(bool status);
    virtual void setValveLevel(uint8_t level);
    virtual void setTemp(float temp);

    virtual bool parsePayload(const char* payload);

    protected:
    HeatingController& hc;
};