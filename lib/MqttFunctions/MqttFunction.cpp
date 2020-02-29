#include <MqttFunctions.h>

void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
//  // Make const char* from byte*
//  char message_buff[length + 1];
//  int i;
//  for (i = 0; i < length; i++)
//  {
//    message_buff[i] = payload[i];
//  }
//  message_buff[i] = '\0';
//  const char *p_payload = message_buff;
//  rdebugDln("%s: %s",topic,p_payload);
//  
//  for (int i = 0; i < mqtt_topic_thermostat_N; i++)
//  {
//    if (!strcmp(topic, mqtt_topic_thermostat))
//    {
//      light[i].parsePayload(p_payload);
//      return;
//    }
//  }

}

bool mqtt_reconnect(PubSubClient &mqttclient, const char *device_name, const char *user_name, const char *mqtt_pw, const char *mqtt_topic_tree) {
 // Loop until we're reconnected
    
  bool returnval = true;
  if (!mqttclient.connected()) {
//    DEBUG_PRINT("Attempting MQTT connection...");
    // Attempt to connect
    returnval=mqttclient.connect(device_name, user_name, mqtt_pw);
    if (returnval) {
      //DEBUG_PRINTLN("connected");
      mqttclient.subscribe(mqtt_topic_tree);
      //DEBUG_PRINT("Subscribed to: ");
      //DEBUG_PRINTLN(mqtt_topic_tree);
    } else {
      //DEBUG_PRINT("failed, rc=");
      //DEBUG_PRINT(mqttclient.state());
      //DEBUG_PRINTLN(" try again in 5 seconds");
    }
  }
  return returnval;
}

bool mqtt_check(PubSubClient &mqttclient, uint16_t mqttReconnectInterval, const char *device_name, const char *user_name, const char *mqtt_pw, const char *mqtt_topic_tree) {
    bool returnval = true;
    if (!mqttclient.connected()) {
        INTERVAL(mqttReconnectInterval,millis())
        {
            returnval = mqtt_reconnect(mqttclient, device_name, user_name, mqtt_pw, mqtt_topic_tree);
        }
    } else {
        mqttclient.loop();
    }
    return returnval;
}