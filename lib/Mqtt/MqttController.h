#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <HeatingController.h>
#include <RemoteDebug.h>

class MqttController {
    public:
    MqttController(HeatingController* hc, const char* commandtopic, const char* statetopic) 
        : hc(hc), commandtopic(commandtopic), statetopic(statetopic) {};

    void begin();
    bool parsePayload(const char *payload);
    void getMQTTStateTopic(char *topicstr);
    void getMQTTCommandTopic(char *topicstr);

    protected:
    HeatingController* hc;
    const char* commandtopic;
    const char* statetopic;
};