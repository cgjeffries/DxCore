// Used slave_read.ino from libraries\Wire\examples\slave_read
// in the DxCore package by MX682X for reference

// Slave is AVR128DA48 Curiosity Nano board
// Recommended baud for Serial1 is 115200
#include <Wire.h>

#define SlaveSerial Serial1

unsigned long serialBaud = 115200;

SLPCTRL_SMODE_t sleepMode = SLEEP_MODE_STANDBY;
uint8_t twiAddress = 0x08;
bool useInternalPullups = false;
bool flushSerial = true;

int delayTime = 5000;
bool isAwake = false;

// Addresses 0x08 to 0x6F are available, the rest are for special cases found here:
// https://github.com/cgjeffries/DxCore/tree/master/megaavr/libraries/Wire
void setup() {
  SlaveSerial.begin(serialBaud);
  sleepUntilTWIMatch(twiAddress, useInternalPullups, SLEEP_MODE_STANDBY, flushSerial);
}

void loop() {
  delay(delayTime / 10);
  if (isAwake) {
    delay(delayTime);
    isAwake = false;
    sleepSimple(sleepMode, flushSerial);
  }
}

// MALS-115
void sleepUntilTWIMatch(uint8_t twiAddress, bool useInternalPullups, SLPCTRL_SMODE_t sleepMode, bool flushSerial) {
  if (useInternalPullups) {
    Wire.usePullups(); // Not recommended, not as reliable as exteral pullups
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
  isAwake = true;
}