#include <MqttController.hpp>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

void MqttController::begin() {
  
}

void MqttController::handle() {
    if (!psc.connected()) {
        reconnect();
    }
    psc.loop();
}

void MqttController::reg(MqttListener* ml) {
  listener.push_back(ml);
}

bool MqttController::reconnect() {
    if (psc.connect(mqttName, mqttUser, mqttPassword)) {
        for(MqttListener* ml : listener) {
            bool subsc_stat = psc.subscribe(ml->getMQTTTopic());
            debugD("Subscribing to %s (%d)",ml->getMQTTTopic(),subsc_stat);
        }
        return true;
    }
    return false;
}

void MqttController::callback(const char* topic, const byte* payload, unsigned int length) {
  debugD("MQTT msg received in %s",topic);
    // Make const char* from byte*
  char p_payload[length + 1];
  for (int i = 0; i < length; i++)
  {
    p_payload[i] = payload[i];
  }
  p_payload[length] = '\0';

  for (MqttListener* ml : listener)
  {
    if (!strcmp(ml->getMQTTTopic(), topic))
    {
      debugD("MQTT msg matched with listener");
      if(ml->parsePayload(p_payload))
        return;
    }
  }
}

bool MqttController::sendMessage(const char* topic, const char* msg, bool retain) {
  this->handle();
  if( !psc.publish(topic, msg, retain) )
  {
    debugE("Failed MQTT '%s'",msg);
    debugE("%s",topic);
    return false;
  } else {
    debugD("MQTT '%s'",msg);
    debugD("%s",topic);
    return true;
  }
  this->handle();
}