#include "BaseConfig.h"

#include <WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>
 
#include <Shifty.h>
#include <INTERVAL.h>

#include <NetworkFunctions.h>
#include <OTAFunctions.h>
#include <MqttFunctions.h>
#include <RemoteDebugFunctions.h>
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

ValveDriver       *valvedriver[N_OUTPUTPORT];
InterfaceDriver   *interfacedriver[N_OUTPUTPORT];
Thermostat        *thermostate[N_OUTPUTPORT];
HeatingController *heatcontrollers[N_OUTPUTPORT];

boolean display = true;


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
  u8g2.drawBox(0,58,60,6);
  if(display) {
    u8g2.drawStr(0,10,"Wifi:");
    u8g2.drawStr(50,10,WiFi.localIP().toString().c_str());
    u8g2.sendBuffer();
  }

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start network services
  startOTA(device_name, ota_password);
  beginRemoteDebug(device_name);

  // Configure periphery drivers and heating controllers
  for(uint8_t i=0;i<N_OUTPUTPORT;i++) {
    valvedriver[i]     = new ShiftyValveDriver(shifty,OUTPUTPORT[i]);
    interfacedriver[i] = new OpenDrainInterfaceDriver(INTERFACE[i]);
    thermostate[i]     = new OnOffTheromostat(interfacedriver[i],100,-100);
    heatcontrollers[i] = new BangBangController(valvedriver[i],thermostate[i],20);
  }
}

void loop() {
  // Handle background services
  ArduinoOTA.handle();
  Debug.handle();
  
  // Handle heat controllers
  INTERVAL(1000) {
    for (uint8_t i = 0; i<N_OUTPUTPORT; i++) {
      heatcontrollers[i]->handle();
      debugV("Handling heatcontroller %d",i);
    }
  }

  // Read interfaces and print status to display
  INTERVAL(100) {
    if(display) {
      updateDisplay(u8g2,valvedriver,N_OUTPUTPORT);
    }
  }

  // Flash LED
  INTERVAL(1000) {
    digitalWrite(LED_PIN,!digitalRead(LED_PIN));
  }
}
