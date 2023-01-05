#pragma once

#include<Arduino.h>
#include<HeatingControllerListener.hpp>
#include<HeatingController.h>
#include<MqttListener.hpp>
#include<MqttController.hpp>
#include<INTERVAL.h>

using namespace std;

class MqttControllerInterface : public MqttListener, public HeatingControllerListener {
    public:
    MqttControllerInterface(MqttController& mqtt_controller, const char* topic, HeatingController& hc, const char *current_temperature_topic=NULL)
    : MqttListener(mqtt_controller, strcat(strcat(strcpy(new char[strlen(topic)+strlen(hc.getName())+3], topic), hc.getName()),"/#")), hc(hc), current_temperature_topic(current_temperature_topic) {
        hc.addListener(this);
    };

    virtual void setEnabled(bool status, boolean settopic = true);
    virtual void setValveState(bool status, boolean settopic = true);
    virtual void setValveLevel(uint8_t level, boolean settopic = true);
    virtual void setTemp(float temp, boolean settopic = true);
    virtual bool presentMessage(const char *topic,const char *payload);
    virtual void sendMQTTDiscoveryMsg();
    virtual void handle(void);

    protected:
    HeatingController& hc;
    const char *current_temperature_topic;
};