#include "low_power.h"

// MALS-89
void setSleepMode(SLPCTRL_SMODE_t sleepMode) {
  SLPCTRL.CTRLA = sleepMode;
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
void enterSleep(bool flushSerial = true) {
  asm("sleep \n");
  if (flushSerial)
    Serial.flush();
}

// MALS-89, MALS-90, & MALS-91 combined
void sleepSimple(SLPCTRL_SMODE_t sleepMode, bool flushSerial = true) {
  setSleepMode(sleepMode);
  enableSleepMode();
  enterSleep(flushSerial);
}