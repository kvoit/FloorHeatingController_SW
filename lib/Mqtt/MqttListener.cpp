#include <MqttListener.hpp>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

MqttListener::MqttListener(MqttController* mqtt_controller, const char* topic) 
        : mqtt_controller(mqtt_controller), topic(topic) {

        mqtt_controller->reg(this);
    };