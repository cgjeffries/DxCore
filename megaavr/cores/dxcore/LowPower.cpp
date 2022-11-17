#include "Arduino.h"

// MALS-89
void setSleepMode(SLPCTRL_SMODE_t sleepMode) {
  SLPCTRL.CTRLA &= SLPCTRL_SEN_bm; // SLPCTRL_SEN_bm = 0x01 = 0b00000001
  SLPCTRL.CTRLA |= sleepMode;
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
  if (flushSerial) {
    // The #if defined(USART#) parts were inspired by the last parts of HardwareSerial.h
    // https://github.com/cgjeffries/DxCore/blob/master/megaavr/cores/dxcore/HardwareSerial.h
    #if defined(USART0)
      Serial0.flush();
    #endif
    #if defined(USART1)
      Serial1.flush();
    #endif
    #if defined(USART2)
      Serial2.flush();
    #endif
    #if defined(USART3)
      Serial3.flush();
    #endif
    #if defined(USART4)
      Serial4.flush();
    #endif
    #if defined(USART5)
      Serial5.flush();
    #endif
  }

  asm("sleep \n");
}

// MALS-89, MALS-90, & MALS-91 combined
void sleepSimple(SLPCTRL_SMODE_t sleepMode, bool flushSerial) {
  setSleepMode(sleepMode);
  enableSleepMode();
  enterSleep(flushSerial);
}