#include <DisplayFunctions.h>

void updateDisplay(U8G2 &u8g2, ValveDriver *valvedriver[], uint8_t n_valvedriver) {
  for(uint8_t i=0;i<n_valvedriver;i++) {
    u8g2.setColorIndex(valvedriver[i]->getState());
    u8g2.drawBox(1+6*i,59,4,4);
    u8g2.setColorIndex(1);
  }

  u8g2.sendBuffer();
}
