#include<MqttJsonThermostat.hpp>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

StaticJsonDocument<200> json_doc;
DeserializationError json_error;

bool MqttJsonThermostat::parsePayload(const char *payload) {

    json_error = deserializeJson(json_doc, payload);

    // Test if parsing succeeds.
    if (json_error) {
        debugE("deserializeJson() failed: %s",json_error.c_str());
        return false;
    }

    temp = json_doc[json_name];
    debugD("Setting temp to %f",temp);
    return false;
}