#pragma once

#include <pins.h>
#include <BangBangController.h>
#include <OnOffTheromostat.h>
#include <ShiftyValveDriver.h>
#include <OpenDrainInterfaceDriver.h>
#include <PWMValveDriverDecorator.hpp>
#include <MqttController.hpp>
#include <MqttThermostat.hpp>
#include <MqttJsonThermostat.hpp>
#include <ThermostatMaxDecorator.hpp>
#include <MqttHeatingListener.hpp>
#include <MqttHcEnabler.hpp>

#define MQTT_TOPIC_BASE "home-uk/heating/"

void configControllers(void);