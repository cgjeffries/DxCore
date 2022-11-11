#include "api/ArduinoAPI.h"
#include "Arduino.h"


// Helper functions

void wake_using_RTC(){
    /* Initialize RTC: */
  while (RTC.STATUS > 0)
  {
    ;                                   /* Wait for all register to be synchronized */
  }
  RTC.CLKSEL = RTC_CLKSEL_OSC1K_gc;  /* 1.024 kHz from OSC32K */
  RTC.INTCTRL = RTC_OVF_bm;					// enable overflow interrupt
  RTC.CTRLA = 0 | 0x80 | 1;		// set enabled in standby and enable RTC
}

void set_RTC_per_time(uint32_t millis){
  while (RTC.STATUS > 0)
  {
    ;                                   /* Wait for all register to be synchronized */
  }
  RTC.PER = (millis * 1024) / 1000;
}

ISR(RTC_CNT_vect)
{
  RTC.INTFLAGS = RTC_OVF_bm;          /* Clear interrupt flag by writing '1' (required) */
}

void disable_RTC(){
  while (RTC.STATUS > 0)
  {
    ;                                   /* Wait for all register to be synchronized */
  }
  RTC.CTRLA = 0;					// disable RTC
}

void set_sleep_mode_standby(){
  SLPCTRL.CTRLA = SLPCTRL_SMODE_t::SLPCTRL_SMODE_STDBY_gc; //select power down state
}

void enable_sleep_mode(){
  SLPCTRL.CTRLA |= 1; //enable sleep
}

void enter_sleep_mode(){
  asm("sleep \n");
}

/*
Utilize the Standby sleep mode to emulate the funcitonality of the standard arduino delay() function, at greatly 
reduced power draw.
*/
void delaySleep(uint32_t millis){
  set_RTC_per_time(millis);
  wake_using_RTC();
  set_sleep_mode_standby();
  enable_sleep_mode();
  enter_sleep_mode();
  disable_RTC();
}
