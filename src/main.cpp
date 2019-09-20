#include "BaseConfig.h"

#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <SPI.h>

#include <ArduinoOTA.h>
#include <RemoteDebug.h> 
#include <Shifty.h>
#include <INTERVAL.h>
#include <PubSubClient.h>

#include <NetworkFunctions.h>
#include <OTAFunctions.h>
#include <MqttFunctions.h>
#include <U8g2lib.h>
#include <DisplayFunctions.h>

#include <BangBangController.h>
#include <OnOffTheromostat.h>
#include <ShiftyValveDriver.h>
#include <OpenDrainInterfaceDriver.h>

#include "pins.h"

Shifty shifty;

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ OUTPUT_CLOCK_PIN /* A4 */ , /* data=*/ OUTPUT_DATA_PIN /* A2 */, /* CS=*/ 26 /* A3 */, /* reset=*/ 27);

RemoteDebug Debug;

WiFiClient espClient;
PubSubClient mqttclient(espClient);
const unsigned long mqttReconnectInterval = 5000;

// ShiftyValveDriver sd(shifty,OUTPUTPORT[0]);
ValveDriver       *valvedriver[N_OUTPUTPORT];
InterfaceDriver   *interfacedriver[N_OUTPUTPORT];
Thermostat        *thermostate[N_OUTPUTPORT];
HeatingController *heatcontrollers[N_OUTPUTPORT];
// //  = {
// //   new BangBangController(*valvedriver[0],*thermostate[0], 20)
// // };

boolean display = true;


void setup() {
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,HIGH);

  for(uint8_t i=0;i<N_OUTPUTPORT;i++) {
    valvedriver[i]     = new ShiftyValveDriver(shifty,OUTPUTPORT[i]);
    interfacedriver[i] = new OpenDrainInterfaceDriver(INTERFACE[i]);
    thermostate[i]     = new OnOffTheromostat(interfacedriver[i],100,-100);
    heatcontrollers[i] = new BangBangController(valvedriver[i],thermostate[i],20);
  }

  // Set all interfaces to input
  for (uint8_t i=0;i<N_INTERFACE;i++) {
    pinMode(INTERFACE[i],INPUT);
  }

  Serial.begin(115200);
  Serial.println("Booting");

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

  startOTA(device_name, ota_password);

  //u8g2.clearBuffer();          // clear the internal memory
  if(display) {
    u8g2.drawStr(0,20,"Connected to Wifi.");
    u8g2.sendBuffer();
  }

  MDNS.addService("telnet", "tcp", 23);

  Debug.begin(device_name); // Initiaze the telnet server
  Debug.setResetCmdEnabled(true); // Enable the reset command
  Debug.showTime(true); // To show time
  Debug.showProfiler(true); // To show profiler - time between messages of Debug
                              // Good to "begin ...." and "end ...." messages
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Handle background services
  ArduinoOTA.handle();
  Debug.handle();

  for (uint8_t i = 0; i<N_OUTPUTPORT; i++) {
    heatcontrollers[i]->handle();
  }

  INTERVAL(100) {
    if(display) {
      updateDisplay(u8g2,valvedriver,N_OUTPUTPORT);
    }
  }

  INTERVAL(1000) {
    digitalWrite(LED_PIN,!digitalRead(LED_PIN));
  }
  
  
}
