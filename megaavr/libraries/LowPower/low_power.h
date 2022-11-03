/*
The rough draft of the low_power.h file was first created by Charles Jeffries.
Only a small part of that is implemented here. The complete low_power.h file
will be added to this project later.
https://github.com/jnbrauer/SER401-2022-Group39-Documentation/blob/MALS-70-low-power-api-stubs/Low%20Power/low_power.h
*/
#ifndef LOW_POWER_H
#define LOW_POWER_H

#define power_down_mode SLPCTRL_SMODE_t::SLPCTRL_SMODE_PDOWN_gc
#define standby_mode SLPCTRL_SMODE_t::SLPCTRL_SMODE_STDBY_gc
#define idle_mode SLPCTRL_SMODE_t::SLPCTRL_SMODE_IDLE_gc

//////////////////////////////////////////////////////////////
//                  General Sleep API                       //
//////////////////////////////////////////////////////////////

public:
	/*
	Sets the sleep mode to the specified mode. Does NOT automatically enter sleep.
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

#endif