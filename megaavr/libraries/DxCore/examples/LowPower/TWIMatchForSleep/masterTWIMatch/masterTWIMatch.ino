// Used master_write.ino from libraries\Wire\examples\master_write
// in the DxCore package by MX682X for reference

// Master is ATmega328P XPlained Mini board
// Recommended baud for Serial is 57600
#include <Wire.h>

#define MasterSerial Serial

unsigned long serialBaud = 57600;

uint8_t twiAddress = 0x08;
bool useInternalPullups = false;

char serialInput[32] = {};
int8_t serialInputLength = 0;

int delayTime = 1000;

void setup() {
  MasterSerial.begin(serialBaud);
  wakeWithTWIMatch(useInternalPullups);
}

void loop() {
  if (MasterSerial.available() > 0) {
    readFromSerial();
    if (serialInputLength > 0) {
      sendDataWire(twiAddress);
    }
    serialInputLength = 0;
    serialInput[32] = {};
    MasterSerial.flush();
  }
}

void wakeWithTWIMatch(bool useInternalPullups) {
  if (useInternalPullups) {
    //Wire.usePullups(); // Not included in the default Arduino libraries
  }
  Wire.begin();
}

void readFromSerial() {
  MasterSerial.write("Reading message...\n");
  while (serialInputLength <= 30) {
    while (MasterSerial.available() == 0); // Wait until all bytes are taken in
    char character = MasterSerial.read();
    if (character == '\r' || character == '\n') {
      break;
    }
    serialInput[serialInputLength++] = character;
  }
}

void sendDataWire(uint8_t twiAddress) {
  MasterSerial.write("Sending message to slave!\n");

  // Initial communication to wake up the sleeping slave microcontroller
  Wire.beginTransmission(twiAddress);
  Wire.endTransmission();

  Wire.beginTransmission(twiAddress);
  for (int inputIndex = 0; inputIndex < serialInputLength; inputIndex++) {
    Wire.write(serialInput[inputIndex]);
  }
  Wire.write("\r\n");
  Wire.endTransmission();
}
