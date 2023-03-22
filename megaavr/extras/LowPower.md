# LowPower.cpp
    This document is a comprehensive list of all the functions from LowPower.cpp. Each function includes descriptions for how they change the hardware to decrease the power draw for DxCore microcontrollers.
    All information for the hardware changes and interrupts can be found in the AVR128DA48 datasheet from Microchip which can be found here: https://www.microchip.com/en-us/product/AVR128DA48

## setSleepMode(SLPCTRL_SMODE_t sleepMode)
Description: 

    Sets the microcontroller's specified sleep mode, but does not enter sleep mode automatically.

Arguments: 
    
    sleepMode - the type of sleep mode the microcontroller will use when it enters sleep mode.

Returns: 
    
    nothing

Hardware Changes: 

    On the Sleep Controller (SLPCTRL), Control A (CTRLA) register, Sleep Enable (SEN, bit 0) will be set to 1 if it was already on or turned off. Also, bit 1, bit 2, or bit 3 will be on depending on the given sleep mode being Idle, Standby, or Power-Down respectively.

Notes: 
    
    This function must be called before enableSleepMode() and enterSleepMode(bool flushSerial). Also, the different sleep modes are from DxCore/megaavr/extras/ioheaders/ for the board's respective header file such as ioavr128da48.h for the AVR128DA48.

## enableSleepMode()
Description: 

    Enables sleep mode to be activated. It does not cause the microcontroller to go to sleep.

Arguments: 

    nothing

Returns: 

    nothing

Hardware Changes: 

    SLPCTRL, Control A register, SEN (bit 0) will be set to 1.

Notes:

    This function must be called before enterSleepMode(bool flushSerial).

## disableSleepMode()
Description: 

    Disables sleep mode to be activated.

Arguments: 

    nothing

Returns: 
    
    nothing

Hardware Changes: 

    SLPCTRL, Control A register, SEN (bit 0) will be set to 0.

Notes:

    nothing

## enterSleep(bool flushSerial)
Description: 

    If SLPCTRL, Control A register, SEN (bit 0) is set to 1 by enableSleepMode(), then the microcontroller will sleep using the sleep mode that was provided from setSleepMode(SLPCTRL_SMODE_t sleepMode).

Arguments: 

    flushSerial - If set to true, the function will flush all the serial ports of the microcontroller. Serial 0 through 5 will be flushed if flushSerial is true.

Returns: 

    nothing

Hardware Changes: 

    When the microcontroller enters Idle mode, all peripherals and clocks will continue to run except for the CPU peripheral. In Standby mode, only the TRC, EDT, BOD, EVSYS, CCL, ACn, ADCn, DACn, PTC, ZCDn, TCAn, and TCBn peripherals will run. Plus, the main clock, RTC clock, WDT oscillator, BOD oscillator, and CCL clock will continue to run in Standby mode. In Power-Down mode, only the TRC, EDT, BOD, and EVSYS peripherals will run while the RTC clock, WDT oscillator, and BOD oscillator will continue to run.

Notes:

    The microcontroller will wake up to different sources depending on the sleep mode given. In Idle mode, all interrupts will wake up the microcontroller. In Standby, only the Port Pin, BOD VLM, RTC, TWI Address Match, CCL, USART Start-Of-Frame, TCAn, TCBn, ACn, ADCn, PTC, and ZCD interrupts will work to wake up the microcontroller. In Power-Down, if VREGCTRL (Voltage Regulator Control)

## sleepSimple(SLPCTRL_SMODE_t sleepMode, bool flushSerial)
Description: 

    Calls setSleepMode(SLPCTRL_SMODE_t sleepMode), enableSleepMode(), and enterSleep(bool flushSerial = true) to set the sleep mode, enable it, and enter it in one function.

Arguments: 

    sleepMode - the type of sleep mode the microcontroller will use when it enters sleep mode.
    flushSerial - If set to true, the function will flush all the serial ports of the microcontroller. Serial 0 through 5 will be flushed if flushSerial is true.

Returns: 

    nothing

Hardware Changes: 

    Refer to the hardware changes from the setSleepMode(SLPCTRL_SMODE_t sleepMode), enableSleepMode(), and enterSleep(bool flushSerial = true) since this function uses all three of them in succession.

Notes:

    nothing

## RTCSync()
Description: 

    This supplementary function is used to wait for the RTC register to sync with main clock to prevent odd behavior if the RTC runs on a different clock.

Arguments: 

    nothing

Returns: 

    nothing

Hardware Changes: 

    The RTC register syncs with the main clock.

Notes:

    This function is used in wakeUsingRTC(), setRTCPerTime(uint32_t millis), and disableRTC().

## wakeUsingRTC()
Description: 

    This function will enable the RTC and its overflow interrupt to wake up the sleeping microcontroller in Standby mode.

Arguments: 

    nothing

Returns: 

    nothing

Hardware Changes: 

    The RTC.CLKSEL (RTC's Clock Selection at 0x07) is set to the clock source OSC32K (set as 0x01 for the CLKSEL bits) which is 1.024 kHz. Also, the RTC.INTCTRL (RTC's Interrupt Control at 0x02) is enabled by setting its bit 0 to the value of 1. Finally, the RTC.CTRLA will enable the RTC for Standby mode.

Notes:

    nothing

## setRTCPerTime(uint32_t millis)
Description: 

    This function uses 1024 ticks per second to scale the millis to RTC ticks.

Arguments: 

    millis - the number of milliseconds.

Returns: 

    nothing

Hardware Changes: 

    RTC.PER (RTC's Period at 0x0A) will be set to the given milliseconds times 1024 ticks per second.

Notes:

    nothing

## attachRTCCNTInterrupt(voidFuncPtr func)
Description: 

    Sets the variable RTCCNTIntHandler to a voidFuncPtr.

Arguments: 

    func - the voidFuncPtr to be kept.

Returns: 

    nothing

Hardware Changes: 

    nothing

Notes:

    nothing

## detachRTCCNTInterrupt()
Description: 

    Sets the variable RTCCNTIntHandler to a nullptr.

Arguments: 

    nothing

Returns: 

    nothing

Hardware Changes: 

    nothing

Notes:

    nothing

## disableRTC()
Description: 

    This function will disable the microcontroller's Real-Time Counter (RTC) to prevent interrupt generation from this peripheral.

Arguments: 

    nothing

Returns: 

    nothing

Hardware Changes: 

    RTC.CTRLA will be set to 0 across all of its bits.

Notes:

    nothing

## delaySleep(uint32_t millis)
Description: 

    Calling this function will set the microcontroller to Standby sleep mode for a given number of milliseconds.

Arguments: 

    millis - the number of milliseconds that the microcontroller will sleep before waking up.

Returns: 

    nothing

Hardware Changes: 

    Hardware changes are from the use of these functions in this order: setRTCPerTime, wakeUsingRTC, setSleepMode, enableSleepMode, enterSleepMode, and disableRTC.

Notes:

    nothing

## disableInputBuffers()
Description: 

    Using this function will lower the microcontroller's power draw by disabling all of its input buffers.

Arguments: 

    nothing

Returns: 

    nothing

Hardware Changes: 

    Only PORTA.PINCONFIG (Multi-Pin Configuration located at 0x0B) is disabled since this register is shared among all the ports. Then, PORTA through PORTF's PINCTRLUPD (Multi-Pin Control Update Mask) is set to 0xFF.

Notes:

    Disabling the input buffers will ensure that they do not consume excess power when their pins change state.

## enableInputBuffers()
Description: 

    Call the function to enable all input buffers for all ports.

Arguments: 

    nothing

Returns: 

    nothing

Hardware Changes: 

    Only PORTA.PINCONFIG (Multi-Pin Configuration located at 0x0B) is enabled since this register is shared among all the ports. Then, PORTA through PORTF's PINCTRLUPD (Multi-Pin Control Update Mask) is set to 0xFF.

Notes:

    This is the opposite of disableInputBuffers(), so the power draw of the microcontroller will increase.

## set_tca0_sleep(bool enable)
Description: 

    Enables/disables the peripheral TCA0 (Timer/Counter Type A instance 0, base address is 0x0A00).

Arguments: 

    enable - sets TCA0.SINGLE.CTRLA at bit position 3 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    TCA0.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.

Notes:

    TCA0.CTRLA will stay in its place during single or split mode.

## set_tca1_sleep(bool enable)
Description: 

    Enables/disables the peripheral TCA1 (Timer/Counter Type A instance 1, base address is 0x0A40).

Arguments: 

    enable - sets TCA1.SINGLE.CTRLA at bit position 3 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    TCA1.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.
    TCA1.CTRLA will stay in its place during single or split mode.

Notes:

    This function is only available if TCA1 is defined for the microcontroller.

## set_tcb0_sleep(bool enable)
Description: 

    Enables/disables the peripheral TCB0 (Timer/Counter Type B instance 0, base address is 0x0B00).

Arguments: 

    enable - sets TCB0.CTRLA at bit position 2 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    TCB0.CTRLA at bit position 2 will be enabled/disabled depending on the enable variable.

Notes:

    nothing

## set_tcb1_sleep(bool enable)
Description: 

    Enables/disables the peripheral TCB1 (Timer/Counter Type B instance 1, base address is 0x0B10).

Arguments: 

    enable - sets TCB1.CTRLA at bit position 2 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    TCB1.CTRLA at bit position 2 will be enabled/disabled depending on the enable variable.

Notes:

    This function is only available if TCB1 is defined for the microcontroller.

## set_rtc_sleep(bool enable)
Description: 

    Enables/disables the peripheral RTC (Real-Time Counter, base address is 0x0140).

Arguments: 

    enable - sets RTC.CTRLA at bit position 3 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    RTC.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.

Notes:

    nothing

## set_ccl_sleep(bool enable)
Description: 

    Enables/disables the peripheral CCL (Configurable Custom Logic, base address is 0x01C0).

Arguments: 

    enable - sets CCL.CTRLA at bit position 2 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    CCL.CTRLA at bit position 2 will be enabled/disabled depending on the enable variable.

Notes:

    nothing

## set_ac0_sleep(bool enable)
Description: 

    Enables/disables the peripheral AC0 (Analog Comparator 0, base address is 0x0680).

Arguments: 

    enable - sets AC0.CTRLA at bit position 3 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    AC0.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.

Notes:

    nothing

## set_ac1_sleep(bool enable)
Description: 

    Enables/disables the peripheral AC1 (Analog Comparator 1, base address is 0x0688).

Arguments: 

    enable - sets AC1.CTRLA at bit position 3 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    AC1.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.

Notes:

    This function is only available if AC1 is defined for the microcontroller.

## set_ac2_sleep(bool enable)
Description: 

    Enables/disables the peripheral AC2 (Analog Comparator 2, base address is 0x0690).

Arguments: 

    enable - sets AC2.CTRLA at bit position 3 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    AC2.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.

Notes:

    This function is only available if AC2 is defined for the microcontroller.

## set_adc0_sleep(bool enable)
Description: 

    Enables/disables the peripheral ADC0 (Analog-to-Digital Converter 0, base address is 0x0600).

Arguments: 

    enable - sets ADC0.CTRLA at bit position 3 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    ADC0.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.

Notes:

    nothing

## set_dac0_sleep(bool enable)
Description: 

    Enables/disables the peripheral DAC0 (Digital-to-Analog converter 0, base address is 0x06A0).

Arguments: 

    enable - sets DAC0.CTRLA at bit position 3 to be 0 or 1.

Returns: 

    nothing

Hardware Changes: 

    DAC0.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.

Notes:

    nothing

## set_zcd0_sleep(bool enable)
Description: 

    Enables/disables the peripheral ZCD0 (Zero-Cross Detector 0, base address is 0x06C0).

Arguments: 

    enable - sets ZCD0.CTRLA at bit position 3 to be 0 or 1.

Returns: 
    
    nothing

Hardware Changes: 

    ZCD0.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.

Notes:

    nothing

## set_zcd1_sleep(bool enable)
Description: 

    Enables/disables the peripheral ZCD1 (Zero-Cross Detector 1, base address is 0x06C8).

Arguments: 

    enable - sets ZCD1.CTRLA at bit position 3 to be 0 or 1.

Returns: 
    
    nothing

Hardware Changes: 

    ZCD1.CTRLA at bit position 3 will be enabled/disabled depending on the enable variable.

Notes:

    This function is only available if ZCD1 is defined for the microcontroller.

## disableAllPeripheralsDuringSleep()
Description: 

    Disables all possible peripherals of the microcontroller to reduce power draw while the microcontroller is asleep.

Arguments: 

    nothing

Returns: 

    nothing

Hardware Changes:

    Peripherals disabled include TCA0, TCA1, TCB0, TCB1, RTC, CCL, AC0, AC1, AC2, ADC0, DAC0, ZCD0, and ZCD1.

Notes:

    It is recommended to call this function at the beginning of the program.

## enableAllPeripheralsDuringSleep()
Description: 

    Enables all possible peripherals of the microcontroller during sleep.

Arguments: 

    nothing

Returns: 
    
    nothing

Hardware Changes: 

    Peripherals enabled include TCA0, TCA1, TCB0, TCB1, RTC, CCL, AC0, AC1, AC2, ADC0, DAC0, ZCD0, and ZCD1.

Notes:

    This function reversed the effects of disableAllPeripheralsDuringSleep().

## disableAllFloatingPins(bool value)
Description: 

    This function sets each pin on the microcontroller board to be OUTPUT and 0 or 1 depending on the value variable to remove floating pins to lower the power draw of the board.

Arguments:

    value - set each OUTPUT pin to be LOW or HIGH depending on the board configuration to lower the power draw of the microcontroller board.

Returns: 

    nothing

Hardware Changes: 

    All pins of the microcontroller board will be set to OUTPUT and 0 or 1 depending on the given value variable.

Notes:

    This function should be called at the beginning of the program so that it does not unintentionally change the settings of the pins.
