#include "low_power.h"

void setSleepMode(SLPCTRL_SMODE_t sleepMode) {
  SLPCTRL.CTRLA = sleepMode;
}