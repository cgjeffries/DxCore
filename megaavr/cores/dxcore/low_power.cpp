#include "Arduino.h"

// MALS-89
void setSleepMode(uint8_t sleepMode) {
  SLPCTRL.CTRLA = sleepMode; // Bit 0 - SEN - will go back to 0
}

// MALS-90
void enableSleepMode() {
  // SLPCTRL.CTRLA = 0b00000000 | 0b00000001 = 0b00000001
  SLPCTRL.CTRLA |= 1; // Bit 0 - SEN - will be set to 1
}

// MALS-90
void disableSleepMode() {
  // SLPCTRL.CTRLA = 0b00000001 & 0b11111110 = 0b00000000
  SLPCTRL.CTRLA &= ~(1); // Bit 0 - SEN - will be set to 0
}

// MALS-91
void enterSleep(bool flushSerial) {
  if (flushSerial)
    Serial.flush();
  asm("sleep \n");
}

// MALS-89, MALS-90, & MALS-91 combined
void sleepSimple(uint8_t sleepMode, bool flushSerial) {
  setSleepMode(sleepMode);
  enableSleepMode();
  enterSleep(flushSerial);
}