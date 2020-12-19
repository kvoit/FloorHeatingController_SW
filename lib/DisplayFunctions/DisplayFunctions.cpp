#include <DisplayFunctions.h>

#include <RemoteDebug.h>
extern RemoteDebug Debug;
extern tm starttime;

boolean beginDisplay(U8G2 &u8g2) {
  // Display starting info, break with blink code if LCD cannot be started
  if (u8g2.begin()) {
    Serial.println("Started LCD");
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Starting ...");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display

    return true;
  } else {
    Serial.println("LCD failed");
    /*while(true) 
    {
      digitalWrite(LED_PIN,HIGH);
      delay(400);
      digitalWrite(LED_PIN,LOW);
      delay(200);
    }*/
    return false;
  }
}

void updateDisplay(U8G2 &u8g2, ValveDriver *valvedriver[], uint8_t n_valvedriver, HeatingController *heatingcontroller[], uint8_t n_heatingcontroller) {
  // debugV("Start display update");
  if(!getLocalTime(&timeinfo)){
    debugE("Failed to obtain NTP time");
    return;
  }
  // debugV("Retrieved time");
  char datestring[20];
  sprintf(datestring,"%04d/%02d/%02d %02d:%02d:%02d",1900+timeinfo.tm_year,timeinfo.tm_mon+1,timeinfo.tm_mday,timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
  // debugV("Formated time");
  u8g2.setColorIndex(0);
  u8g2.drawBox(0,11,128,10);  
  u8g2.setColorIndex(1);
  u8g2.drawStr(0,20,datestring);
  
  // debugV("Drew time");
  u8g2.drawBox(0,46,128,18);
  for(uint8_t i=0;i<n_heatingcontroller;i++) {
    u8g2.setColorIndex(heatingcontroller[i]->isEnabled());
    u8g2.drawBox(1+6*i,47,4,4);
  }
  for(uint8_t i=0;i<n_heatingcontroller;i++) {
    u8g2.setColorIndex(heatingcontroller[i]->getValveDriver().getState());
    u8g2.drawBox(1+6*i,53,4,4);
  }
  for(uint8_t i=0;i<n_valvedriver;i++) {
    u8g2.setColorIndex(valvedriver[i]->getState());
    u8g2.drawBox(1+6*i,59,4,4);
  }
  u8g2.setColorIndex(1);
  // debugV("Drew boxes");
  u8g2.sendBuffer();
  // debugV("End display update");
}
