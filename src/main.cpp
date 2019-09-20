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
BangBangController *heatcontrollers[N_OUTPUTPORT];
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
    thermostate[i]     = new OnOffTheromostat(*interfacedriver[i],100,-100);
    heatcontrollers[i] = new BangBangController(*valvedriver[i],*thermostate[i],20);
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

  // Display starting info, break with blink code if LCD cannot be started
  if (u8g2.begin()) {
    Serial.println("Started LCD");
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Starting PIO ...");  // write something to the internal memory
    u8g2.drawBox(0,58,60,6);
    u8g2.sendBuffer();          // transfer internal memory to the display
  } else {
    Serial.println("LCD failed");
    /*while(true) 
    {
      digitalWrite(LED_PIN,HIGH);
      delay(400);
      digitalWrite(LED_PIN,LOW);
      delay(200);
    }*/
    display = false;
  }

  // Connect wifi

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    if(display) {
      u8g2.drawStr(0,20,"Wifi failed.");
      u8g2.sendBuffer();
    }
    delay(5000);
    ESP.restart();
  }

  //u8g2.clearBuffer();          // clear the internal memory
  if(display) {
    u8g2.drawStr(0,20,"Connected to Wifi.");
    u8g2.sendBuffer();
  }
  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname(device_name);

  // No authentication by default
  ArduinoOTA.setPassword(ota_password);

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  if (MDNS.begin(device_name)) {
      Serial.print("* MDNS responder started. Hostname -> ");
      Serial.println(device_name);
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
