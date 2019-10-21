#include <WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>

#include "BaseConfig.h"

#include <Shifty.h>
#include <INTERVAL.h>

#include <NetworkFunctions.h>
#include <OTAFunctions.h>
#include <MqttFunctions.h>
#include <MqttController.hpp>
#include <RemoteDebugFunctions.h>
#include <TimeFunctions.hpp>
#include <DisplayFunctions.h>
#include <ControllerConfig.h>

#include <BangBangController.h>
#include <OnOffTheromostat.h>
#include <ShiftyValveDriver.h>
#include <OpenDrainInterfaceDriver.h>

#include "pins.h"

Shifty shifty;

SPIClass SPI1(HSPI);
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ OUTPUT_CLOCK_PIN /* A4 */ , /* data=*/ OUTPUT_DATA_PIN /* A2 */, /* CS=*/ 26 /* A3 */, /* reset=*/ 27);
//U8G2_ST7920_128X64_F_2ND_HW_SPI u8g2(U8G2_R0, DISPLAY_CS_PIN, DISPLAY_RST_PIN);

RemoteDebug Debug;

WiFiClient espClient;

ValveDriver       *valvedriver[N_OUTPUTPORT];
InterfaceDriver   *interfacedriver[N_INTERFACE];
Thermostat        *thermostate[N_INTERFACE];
HeatingController *heatcontrollers[N_OUTPUTPORT];
uint8_t n_heatcontroller = 0;

boolean display = true;

PubSubClient pubsubclient(mqtt_server, 1883, espClient);
MqttController mqtt_controller(pubsubclient,device_name,mqtt_user,mqtt_pw);
void mqtt_callback_func(const char* topic, const byte* payload, unsigned int length) { mqtt_controller.callback(topic, payload,length); }

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,HIGH);

  // Set all interfaces to input
  for (uint8_t i=0;i<N_INTERFACE;i++) {
    pinMode(INTERFACE[i],INPUT);
  }

  // Init shifty and ...
  shifty.setBitCount(16);
  shifty.setPins(OUTPUT_DATA_PIN, OUTPUT_CLOCK_PIN, OUTPUT_LATCH_PIN);
  // ... switch all ports off
  for (uint8_t i = 0; i<16; i++)
    shifty.writeBit(i,LOW);

  display = beginDisplay(u8g2);

  // Connect wifi
  if(!startNetwork(ssid,password,device_name)) {

    Serial.println("Connection Failed! Rebooting...");

    if(display) {
      u8g2.drawStr(0,20,"Wifi failed.");
      u8g2.sendBuffer();
    }

    delay(5000);
    ESP.restart();
  }

  u8g2.clearBuffer();          // clear the internal memory
  if(display) {
    u8g2.drawStr(0,10,"Wifi:");
    u8g2.drawStr(50,10,WiFi.localIP().toString().c_str());
    u8g2.sendBuffer();
  }

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pubsubclient.setCallback(mqtt_callback_func);

  // Start network services
  startOTA(device_name, ota_password);
  beginRemoteDebug(device_name);

  // Wait for debug connections
  while(millis()<10000) {
    ArduinoOTA.handle();
    Debug.handle();
    INTERVAL(1000) {
      debugI("Initial wait %lu",millis());
    }
  }

  updateNTP(gmtOffset_sec, dlsOffset_sec, ntpserver);

  // Configure periphery drivers and heating controllers
  configControllers();
}

void loop() {
  // Handle background services
  ArduinoOTA.handle();
  Debug.handle();
  mqtt_controller.handle();
  
  // Handle heat controllers
  INTERVAL(100) {
    for (uint8_t i = 0; i<n_heatcontroller; i++) {
      debugV("main: Handling controller %d",i);
      heatcontrollers[i]->handle();
    }
  }

  //Read interfaces and print status to display
  INTERVAL(1000) {
    if(display) {
      updateDisplay(u8g2,valvedriver,N_OUTPUTPORT,heatcontrollers,n_heatcontroller);
    }
  }

  // Flash LED
  INTERVAL(1000) {
    digitalWrite(LED_PIN,!digitalRead(LED_PIN));
  }

  INTERVAL(60000) {
    printLocalTime();
  }

  INTERVAL(24*3600000) {
    updateNTP(gmtOffset_sec, dlsOffset_sec, ntpserver);
  }
}
