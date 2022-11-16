#include "api/ArduinoAPI.h"
#include "Arduino.h"


// Helper functions

//function to wait for the RTC register to sync with main clock. RTC can be run on different clock so waiting for this sync is good and prevents odd behavior from appearing.
void RTC_sync(){
  while (RTC.STATUS > 0)
  {
    ;                                   /* Wait for all registers to be synchronized */
  }
}

//configure the RTC to enabled and set the overflow interrupt to enabled
void wake_using_RTC(){
    /* Initialize RTC: */
  RTC_sync();
  RTC.CLKSEL = RTC_CLKSEL_OSC1K_gc;  /* 1.024 kHz from OSC32K */
  RTC.INTCTRL = RTC_OVF_bm;					// enable overflow interrupt
  RTC.CTRLA = 0 | 0x80 | 1;		// set enabled in standby and enable RTC
}

//function that scales millis to RTC ticks based on 1024 ticks/sec
void set_RTC_per_time(uint32_t millis){
  RTC_sync();
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
void disable_RTC(){
  RTC_sync();
  RTC.CTRLA = 0;					// disable RTC
}

//temp function, will be replaced with call to API-adhered function
void set_sleep_mode_standby(){
  SLPCTRL.CTRLA = SLPCTRL_SMODE_t::SLPCTRL_SMODE_STDBY_gc; //select power down state
}

//temp function, will be replaced with call to API-adhered function
void enable_sleep_mode(){
  SLPCTRL.CTRLA |= 1; //enable sleep
}

//temp function, will be replaced with call to API-adhered function
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
