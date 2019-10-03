#include <MqttController.h>

extern RemoteDebug Debug;

void MqttController::begin() {}

bool MqttController::parsePayload(const char *payload) {
    if ( !strcmp(payload, "ON") )
    {
        hc->setEnabled(1);
        return true;
    }
    else if ( !strcmp(payload, "OFF") )
    {
        hc->setEnabled(0);
        return true;
    }
    else
    {
        if(strlen(payload)<6) //Cannot contain TEMP command
            return false;
        if(strstr(payload, "TEMP") == NULL)
            return false;

        float set_temp = atof(&payload[5]);
        hc->setTemp(set_temp);
    }
    return false;
}

void MqttController::getMQTTStateTopic(char *topicstr) {

}

void MqttController::getMQTTCommandTopic(char *topicstr) {

}