// Used slave_read.ino from libraries\Wire\examples\slave_read
// in the DxCore package for reference

#include <Wire.h>

#define TestSerial Serial1

SLPCTRL_SMODE_t sleepMode = SLEEP_MODE_STANDBY;
uint8_t twiAddress = 0x08;
bool useInternalPullups = true;
bool flushSerial = true;

uint8_t delayTime = 100;

// Addresses 0x08 to 0x6F are available, the rest are for special cases found here:
// https://github.com/cgjeffries/DxCore/tree/master/megaavr/libraries/Wire
void setup() {
  TestSerial.begin(38400);
  sleepUntilTWIMatch(twiAddress, useInternalPullups, SLEEP_MODE_STANDBY, flushSerial);
}

void loop() {
  delay(delayTime);
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
  for (int bitPos = 0; bitPos < numMasterBytes; bitPos++) {
    TestSerial.write(Wire.read());
  }
}