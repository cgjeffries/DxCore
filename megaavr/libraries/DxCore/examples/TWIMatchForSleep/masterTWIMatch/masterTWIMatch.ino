// Used master_write.ino from libraries\Wire\examples\master_write
// in the DxCore package for reference

#include <Wire.h>

#define TestSerial Serial1

uint8_t twiAddress = 0x08;
bool useInternalPullups = true;

char serialInput[32];
int8_t serialInputLength = 0;

int delayTime = 1000;

void setup() {
  TestSerial.begin(38400);
  wakeWithTWIMatch(useInternalPullups);
}

void loop() {
  delay(delayTime);
  TestSerial.write(0x11);
  if (TestSerial.available() > 0) {
    readFromSerial();
    if (serialInputLength > 0) {
      sendDataWire(twiAddress);
    }
    serialInputLength = 0;
  }
}

void wakeWithTWIMatch(bool useInternalPullups) {
  if (useInternalPullups) {
    Wire.usePullups(); // Not recommended, not as reliable as exteral pullups
  }
  Wire.begin();
}

void readFromSerial() {
  while (serialInputLength <= 30) {
    while (TestSerial.available() == 0); // Wait until all bytes are taken in
    char character = TestSerial.read();
    if (character == '\r' || character == '\n') {
      break;
    }
    serialInput[serialInputLength++] = character;
  }
}

void sendDataWire(uint8_t twiAddress) {
  Wire.beginTransmission(twiAddress);
  for (int inputIndex = 0; inputIndex < serialInputLength; inputIndex++) {
    Wire.write(serialInput[inputIndex]);
  }
  Wire.write("\r\n");
  Wire.endTransmission();
}