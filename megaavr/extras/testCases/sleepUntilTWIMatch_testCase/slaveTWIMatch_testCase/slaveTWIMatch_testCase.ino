// Used slave_read.ino from libraries\Wire\examples\slave_read
// in the DxCore package by MX682X for reference

// Slave is AVR128DA48 Curiosity Nano board
// Recommended baud for Serial1 is 115200
#include <Wire.h>
#include "Arduino.h"


#define SlaveSerial Serial1

unsigned long serialBaud = 115200;

uint8_t sleepModeNum = 2;
SLPCTRL_SMODE_t sleepMode = SLEEP_MODE_PWR_DOWN;
uint8_t twiAddress = 0x08;
bool useInternalPullups = false;
bool flushSerial = true;

unsigned long delayTime = 1000;
bool isAwake = false;

// Addresses 0x08 to 0x6F are available, the rest are for special cases found here:
// https://github.com/cgjeffries/DxCore/tree/master/megaavr/libraries/Wire
void setup() {
  SlaveSerial.begin(serialBaud);
  pickSleepMode(sleepModeNum);
  sleepUntilTWIMatch(twiAddress, useInternalPullups, sleepMode, flushSerial);
}

void loop() {
  delay(delayTime / 10);
  if (isAwake) {
    delay(delayTime);
    isAwake = false;
    sleepSimple(sleepMode, flushSerial);
  }
}

void sleepUntilTWIMatch(uint8_t twiAddress, bool useInternalPullups, SLPCTRL_SMODE_t sleepMode, bool flushSerial) {
  if (useInternalPullups) {
    Wire.usePullups(); // Not recommended, not as reliable as exteral pullup resistors
  }
  Wire.begin(twiAddress);
  Wire.onReceive(receiveFromMaster);
  sleepSimple(sleepMode, flushSerial);
}

// This should wake the microcontroller when it's called as an event by the Wire
void receiveFromMaster(int16_t numMasterBytes) {
  SlaveSerial.write("Received from Master: ");
  for (int bitPos = 0; bitPos < numMasterBytes; bitPos++) {
    SlaveSerial.write(Wire.read());
  }
  if (++sleepModeNum > 2) {
    sleepModeNum = 0;
  }
  pickSleepMode(sleepModeNum);
  isAwake = true;
}

void pickSleepMode(uint8_t sleepModeNum) {
  if (sleepModeNum == 0) {
    SlaveSerial.write("Idle picked\n");
    sleepMode = SLEEP_MODE_IDLE;
  }
  else if (sleepModeNum == 1) {
    SlaveSerial.write("Standby picked\n");
    sleepMode = SLEEP_MODE_STANDBY;
  }
  else if (sleepModeNum == 2) {
    SlaveSerial.write("Power down picked\n");
    sleepMode = SLEEP_MODE_PWR_DOWN;
  }
}
