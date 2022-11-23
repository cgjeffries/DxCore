/*
The low_power.h file was first created by Charles Jeffries.
This has all the functions from his header file.
https://github.com/jnbrauer/SER401-2022-Group39-Documentation/blob/MALS-70-low-power-api-stubs/Low%20Power/low_power.h
*/
#ifndef LOW_POWER_H
#define LOW_POWER_H

//////////////////////////////////////////////////////////////
//                  General Sleep API                       //
//////////////////////////////////////////////////////////////

/*
Sets the sleep mode to the specified mode. Does NOT automatically enter sleep.
Defined Sleep Modes in megaavr/extras/ioheaders/ioavr128da48.h:
    SLEEP_MODE_IDLE
    SLEEP_MODE_STANDBY
    SLEEP_MODE_PWR_DOWN
*/
void setSleepMode(SLPCTRL_SMODE_t sleepMode);

/*
Enables sleep mode. Does NOT automatically enter sleep.
*/
void enableSleepMode();

/*
Disables sleep mode.
*/
void disableSleepMode();

/*
Enters sleep mode. Sleep mode MUST be enabled and the mode must be set prior to calling this function.
Flushes Serial buffer before entering sleep if flushSerial is set to true.
*/
void enterSleep(bool flushSerial = true);

/*
One step sleep function. Sets the sleep mode, enables sleep, and enters sleep.
If flushSerial is true, also flushes the Serial buffer before sleeping.
*/
void sleepSimple(SLPCTRL_SMODE_t sleepMode, bool flushSerial = true);


//////////////////////////////////////////////////////////////
//                  Common Sleep API                        //
//////////////////////////////////////////////////////////////

/*
Utilize the Standby sleep mode to emulate the funcitonality of the standard arduino delay() function, at greatly 
reduced power draw.
*/
void delaySleep(uint32_t millis);

/*
Place the device in Standby sleep mode until the specified byte is recieved by the Serial peripheral.
*/
void sleepUntilSerial(uint8_t byte);

/*
Place the device in Standby sleep mode until the specified address is recieved by the TWI (I2C) peripheral.
*/
void sleepUntilTWIMatch(uint8_t address);


//////////////////////////////////////////////////////////////
//                  Power Draw Utilities                    //
//////////////////////////////////////////////////////////////

/*
Disables all input buffers. Input buffers consume power when the pins they serve change states, so disabling them
entirely will prevent that source of power loss.
*/
void disableInputBuffers();

/*
Sets all PORT pins to OUTPUT & HIGH. This should be called at the beginning of setup() then afterwards pins can be 
configured as desired. Reduces power consumption by preventing unused pins being left as floating, which can cause
them to rapidly toggle state, which causes input buffers to consume unnecessary power.
*/
void disableAllFloatingPins();

/*
Disables all peripherals in the system, including PWM timers. This should be called at the beginning of setup() then
desired peripherals can be re-enabled as needed. This reduces power draw by ensuring unneeded peripherals are turned
off during sleep.
*/
void disableAllPeripheralsDuringSleep();

/*
Does the opposite of disableAllPeripheralsDuringSleep; enables all peripheral clocks in sleep. Will significantly
increase sleep power consumption.
*/
void enableAllPeripheralsDuringSleep();

/*
Set the BOD (Brown Out Detection) to continuous mode for the fastest response, but also the highest power consumption.
*/
void bodSetContinuous();

/*
Set the BOD (Brown Out Detection) to polling mode for slower BOD response, but greatly reduced power consumption.
*/
void bodSetPolling();

/*
Disable the BOD (Brown Out Detection) for reduced power consumption. The system may behave unexpectedly in a 
brown-out scenario.
*/
void bodSetDisabled();

#endif