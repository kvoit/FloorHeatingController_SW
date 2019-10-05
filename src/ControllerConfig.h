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

void configControllers(void);