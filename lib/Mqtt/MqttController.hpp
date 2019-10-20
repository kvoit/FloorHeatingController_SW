#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <MqttListener.hpp>
#include <Messenger.hpp>

class MqttListener;
class MqttController : public Messenger{
    public:
    MqttController(PubSubClient &psc, const char* mqttName, const char* mqttUser, const char* mqttPassword) 
        : psc(psc), mqttName(mqttName), mqttUser(mqttUser), mqttPassword(mqttPassword) {};

    void reg(MqttListener* ml);
    void begin(void);
    void handle(void);
    void callback(const char* topic, const byte* payload, unsigned int length);
    bool sendMessage(const char* topic, const char* msg, bool retain=true);

    protected:
    bool reconnect();
    std::vector<MqttListener*> listener;

    PubSubClient& psc;
    const char* mqttName;
    const char* mqttUser;
    const char* mqttPassword;
};
