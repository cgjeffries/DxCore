/*
The rough draft of the low_power.h file was first created by Charles Jeffries.
Only a small part of that is implemented here. The complete low_power.h file
will be added to this project later.
https://github.com/jnbrauer/SER401-2022-Group39-Documentation/blob/MALS-70-low-power-api-stubs/Low%20Power/low_power.h
*/

#define power_down_mode SLPCTRL_SMODE_t::SLPCTRL_SMODE_PDOWN_gc
#define standby_mode SLPCTRL_SMODE_t::SLPCTRL_SMODE_STDBY_gc
#define idle_mode SLPCTRL_SMODE_t::SLPCTRL_SMODE_IDLE_gc

//////////////////////////////////////////////////////////////
//                  General Sleep API                       //
//////////////////////////////////////////////////////////////

/*
Sets the sleep mode to the specified mode. Does NOT automatically enter sleep.
*/
public:
	void setSleepMode(SLPCTRL_SMODE_t sleepMode);