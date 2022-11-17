#include "Arduino.h"
#include "api/ArduinoAPI.h"

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

//delaySleep Helper functions

//function to wait for the RTC register to sync with main clock. RTC can be run on different clock so waiting for this sync is good and prevents odd behavior from appearing.
void RTCSync(){
  while (RTC.STATUS > 0)
  {
    ;                                   /* Wait for all registers to be synchronized */
  }
}

//configure the RTC to enabled and set the overflow interrupt to enabled
void wakeUsingRTC(){
    /* Initialize RTC: */
  RTCSync();
  RTC.CLKSEL = RTC_CLKSEL_OSC1K_gc;  /* 1.024 kHz from OSC32K */
  RTC.INTCTRL = RTC_OVF_bm;					// enable overflow interrupt
  RTC.CTRLA = 0 | 0x80 | 1;		// set enabled in standby and enable RTC
}

//function that scales millis to RTC ticks based on 1024 ticks/sec
void setRTCPerTime(uint32_t millis){
  RTCSync();
  RTC.PER = (millis * 1024) / 1000;
}

//Is this something that we should be worried about? What if the user wants to define their own ISR?
//using #define guards for this. If the user needs this ISR for themselves they can #undef the RTC_WAKE_ISR.
#define RTC_WAKE_ISR
#ifdef RTC_WAKE_ISR
ISR(RTC_CNT_vect)
{
  RTC.INTFLAGS = RTC_OVF_bm;          /* Clear interrupt flag by writing '1' (required) */
}
#endif

//disable the RTC, that way it won't keep generating interrupts
void disableRTC(){
  RTCSync();
  RTC.CTRLA = 0;					// disable RTC
}

// MALS-92
/*
Utilize the Standby sleep mode to emulate the funcitonality of the standard arduino delay() function, at greatly 
reduced power draw.
*/
void delaySleep(uint32_t millis){
  setRTCPerTime(millis);
  wakeUsingRTC();
  setSleepMode(SLPCTRL_SMODE_t::SLPCTRL_SMODE_STDBY_gc);
  enableSleepMode();
  enterSleep(true); //explicitly flush serial buffers
  disableRTC();
}
