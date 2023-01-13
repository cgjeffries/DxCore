#include "Arduino.h"

//////////////////////////////////////////////////////////////
//                  General Sleep API                       //
//////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////
//                  Common Sleep API                        //
//////////////////////////////////////////////////////////////

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

/*
Notes: 
  * STILL NEEDS TO BE TESTED
  * This function is the result of much suffering. Ask Charles for details...
  * Do we need to #define ERRATA_USART_WAKE so that the fix is applied in the ISR in UART.cpp?
  *  
  * attempt at a TL:DR: The Start of Frame Detection Enable bit (SFDEN) basically just allows the RX complete interrupts to continue functioning while
    the system is asleep. Without it set the USART will not be able to receive data while the system is asleep. Unfortunately, there is a bug
    in the silicon with this feature. From my understanding, if, while the system is awake, you attempt to read from the input buffer as a new byte
    is being received on the data line, AND the SFDEN bit is set, the data may/will be corrupted. To work around this bug, the SFD bit must be 
    unset before any read operations take place on the hardware buffer. The ISR for the RX Complete interrupt in DxCore does this automatically 
    (if ERRATA_USART_WAKE is defined...), so we don't need to directly do that here. However, because the ISR unsets SFDEN and does not set it back,
    we must set SFDEN every time right before we go to sleep if we wish it to be active.
*/
void sleepUntilSerial(uint8_t byte, HardwareSerial serialInstance){
  while(serialInstance.read() != -1){ //flush read buffer before sleeping
  }
  bool correctByteReceived == false;
  while(!correctByteReceived){
    serialInstance._hwserial_module->CTRLB |= USART_SFDEN_bm; //we must enable start of frame detection EVERY TIME because the bugfix in USART.cpp will disable it every time the system is woken from that source.
    sleepSimple(SLPCTRL_SMODE_t::SLPCTRL_SMODE_STDBY_gc, true) //can we get away without flushing tx? Might take a while to flush everything constantly...
    //ISR handles incoming byte, stores it in buffer, then program execution resumes right here
    int receivedByte;
    while((recievedByte = serialInstance.peek()) != -1){ //we may have received multiple bytes in this time.
      if(recievedByte == byte){
        correctByteReceived = true; //we found the correct byte so set the correct flag to true and break
        break;
      }
      else{
        serialInstance.read(); //flush the incorrect byte out
      }
    }
  }

  serialInstance._hwserial_module->CTRLB &= ~USART_SFDEN_bm; //disable start of frame detection as a precaution (should already be disabled)
}

//////////////////////////////////////////////////////////////
//                  Power Draw Utilities                    //
//////////////////////////////////////////////////////////////

/*
Disables all input buffers. Input buffers consume power when the pins they serve change states, so disabling them
entirely will prevent that source of power loss.
*/
void disableInputBuffers(){
  //PORT_ISC = PORT_ISC_t::PORT_ISC_INPUT_DISABLE_gc;
  PORTA.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc; //pinconfig register is shared across all port banks
  PORTA.PINCTRLUPD = 0xff;
  PORTB.PINCTRLUPD = 0xff;
  PORTC.PINCTRLUPD = 0xff;
  PORTD.PINCTRLUPD = 0xff;
  PORTE.PINCTRLUPD = 0xff;
  PORTF.PINCTRLUPD = 0xff;
}

/*
Enables all input buffers. Reverses the effects of disableInputBuffers().
*/
void enableInputBuffers(){
  //PORT_ISC = PORT_ISC_t::PORT_ISC_INTDISABLE_gc; //default value
  PORTA.PINCONFIG = PORT_ISC_t::PORT_ISC_INTDISABLE_gc;
  PORTA.PINCTRLUPD = 0xff;
  PORTB.PINCTRLUPD = 0xff;
  PORTC.PINCTRLUPD = 0xff;
  PORTD.PINCTRLUPD = 0xff;
  PORTE.PINCTRLUPD = 0xff;
  PORTF.PINCTRLUPD = 0xff;
}

/*       TCA        */
void set_tca0_sleep(bool enable){
  //single or split doesn't matter, CTRLA is in the same place either way
  if(enable){
    TCA0.SINGLE.CTRLA |= 0x80;
  }
  else{
    TCA0.SINGLE.CTRLA &= ~(0x80);
  }
}

#ifdef TCA1
void set_tca1_sleep(bool enable){
  //single or split doesn't matter, CTRLA is in the same place either way
  if(enable){
    TCA1.SINGLE.CTRLA |= 0x80;
  }
  else{
    TCA1.SINGLE.CTRLA &= ~(0x80);
  }
}
#endif

/*       TCB        */
void set_tcb0_sleep(bool enable){
  if(enable){
    TCB0.CTRLA |= 0x40;
  }
  else{
    TCB0.CTRLA &= ~(0x40);
  }
}

#ifdef TCB1
void set_tcb1_sleep(bool enable){
  if(enable){
    TCB1.CTRLA |= 0x40;
  }
  else{
    TCB1.CTRLA &= ~(0x40);
  }
}
#endif

/*       RTC        */
void set_rtc_sleep(bool enable){
  if(enable){
    RTC.CTRLA |= 0x80;
  }
  else{
    RTC.CTRLA &= ~(0x80);
  }
}

/*       CCL        */
void set_ccl_sleep(bool enable){
  if(enable){
    CCL.CTRLA |= 0x40;
  }
  else{
    CCL.CTRLA &= ~(0x40);
  }
}

/*       AC        */
void set_ac0_sleep(bool enable){
  if(enable){
    AC0.CTRLA |= 0x80;
  }
  else{
    AC0.CTRLA &= ~(0x80);
  }
}

#ifdef AC1
void set_ac1_sleep(bool enable){
  if(enable){
    AC1.CTRLA |= 0x80;
  }
  else{
    AC1.CTRLA &= ~(0x80);
  }
}
#endif

#ifdef AC2
void set_ac2_sleep(bool enable){
  if(enable){
    AC2.CTRLA |= 0x80;
  }
  else{
    AC2.CTRLA &= ~(0x80);
  }
}
#endif

/*       ADC        */
void set_adc0_sleep(bool enable){
  if(enable){
    ADC0.CTRLA |= 0x80;
  }
  else{
    ADC0.CTRLA &= ~(0x80);
  }
}

/*       DAC        */
void set_dac0_sleep(bool enable){
  if(enable){
    DAC0.CTRLA |= 0x80;
  }
  else{
    DAC0.CTRLA &= ~(0x80);
  }
}

/*       ZCD        */
void set_zcd0_sleep(bool enable){
  if(enable){
    ZCD0.CTRLA |= 0x80;
  }
  else{
    ZCD0.CTRLA &= ~(0x80);
  }
}

#ifdef ZCD1
void set_zcd1_sleep(bool enable){
  if(enable){
    ZCD1.CTRLA |= 0x80;
  }
  else{
    ZCD1.CTRLA &= ~(0x80);
  }
}
#endif

/*
Disables all peripherals in the system during sleep, including PWM timers. This should be called at the beginning of setup() then
desired peripherals can be re-enabled as needed. This reduces power draw by ensuring unneeded peripherals are turned
off during sleep.
*/
void disableAllPeripheralsDuringSleep(){
  set_tca0_sleep(false);
  #ifdef TCA1
  set_tca1_sleep(false);
  #endif
  set_tcb0_sleep(false);
  #ifdef TCB1
  set_tcb1_sleep(false);
  #endif
  set_rtc_sleep(false);
  set_ccl_sleep(false);
  set_ac0_sleep(false);
  #ifdef AC1
  set_ac1_sleep(false);
  #endif
  #ifdef AC2
  set_ac2_sleep(false);
  #endif
  set_adc0_sleep(false);
  set_dac0_sleep(false);
  set_zcd0_sleep(false);
  #ifdef ZCD1
  set_zcd1_sleep(false);
  #endif
}

void enableAllPeripheralsDuringSleep(){
  set_tca0_sleep(true);
  #ifdef TCA1
  set_tca1_sleep(true);
  #endif
  set_tcb0_sleep(true);
  #ifdef TCB1
  set_tcb1_sleep(true);
  #endif
  set_rtc_sleep(true);
  set_ccl_sleep(true);
  set_ac0_sleep(true);
  #ifdef AC1
  set_ac1_sleep(true);
  #endif
  #ifdef AC2
  set_ac2_sleep(true);
  #endif
  set_adc0_sleep(true);
  set_dac0_sleep(true);
  set_zcd0_sleep(true);
  #ifdef ZCD1
  set_zcd1_sleep(true);
  #endif
}

/*
Sources for the NUM_DIGITAL_PINS:
https://arduino.stackexchange.com/questions/36674/how-to-get-number-of-available-pins-in-code
https://forum.arduino.cc/t/where-can-i-find-the-pins_arduino-h-of-atmega328/385006
Also, you may take a look at DxCore/megaavr/variants/48pin-standard/pins_arduino.h
*/
void disableAllFloatingPins(bool value) {
  for (uint32_t pinNum = 0; pinNum <= NUM_DIGITAL_PINS; pinNum++) {
    pinMode(pinNum, OUTPUT);
    digitalWrite(pinNum, value);
  }
}