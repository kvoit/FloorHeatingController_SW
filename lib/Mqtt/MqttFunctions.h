#pragma once

#include <WiFi.h>
#include <PubSubClient.h>
#include <INTERVAL.h>

void mqtt_callback(char* topic, byte* payload, unsigned int length);
bool mqtt_reconnect(PubSubClient &mqttclient, const char *device_name, const char *user_name, const char *mqtt_pw, const char *mqtt_topic_tree);
bool mqtt_check(PubSubClient &mqttclient, uint16_t mqttReconnectInterval, const char *device_name, const char *user_name, const char *mqtt_pw, const char *mqtt_topic_tree);