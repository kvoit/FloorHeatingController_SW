#include <WiFi.h>
#include "BaseConfig.h"

const char* mqtt_topic_tree              = MQTT_TOPIC_BASE "controller/#";
const char* mqtt_topic_thermostat[]      = {
  MQTT_TOPIC_BASE "thermostat/0/",
  MQTT_TOPIC_BASE "thermostat/1/",
  MQTT_TOPIC_BASE "thermostat/2/",
  MQTT_TOPIC_BASE "thermostat/3/",
  MQTT_TOPIC_BASE "thermostat/4/",
  MQTT_TOPIC_BASE "thermostat/5/",
  MQTT_TOPIC_BASE "thermostat/6/",
  MQTT_TOPIC_BASE "thermostat/7/",
  MQTT_TOPIC_BASE "thermostat/8/",
  MQTT_TOPIC_BASE "thermostat/9/"
};
uint8_t mqtt_topic_thermostat_N = 10;
const char* mqtt_topic_circuit[]      = {
  MQTT_TOPIC_BASE "circuit/0/",
  MQTT_TOPIC_BASE "circuit/1/",
  MQTT_TOPIC_BASE "circuit/2/",
  MQTT_TOPIC_BASE "circuit/3/",
  MQTT_TOPIC_BASE "circuit/4/",
  MQTT_TOPIC_BASE "circuit/5/",
  MQTT_TOPIC_BASE "circuit/6/",
  MQTT_TOPIC_BASE "circuit/7/",
  MQTT_TOPIC_BASE "circuit/8/",
  MQTT_TOPIC_BASE "circuit/9/"
};
uint8_t mqtt_topic_circuit_N = 10;
