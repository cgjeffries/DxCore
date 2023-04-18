// Used master_write.ino from libraries\Wire\examples\master_write
// in the DxCore package by MX682X for reference

// Master is ATmega328P XPlained Mini board
// Recommended baud for Serial is 57600

// Automatic master idea from Jude Brauer
#include <Wire.h>

#define MasterSerial Serial

unsigned long serialBaud = 57600;
uint8_t twiAddress = 0x08;
int delayTime = 2000;

void setup() {
  MasterSerial.begin(serialBaud);
  Wire.begin();
}

void loop() {
  sendDataWire(twiAddress);
  delay(delayTime);
}

void sendDataWire(uint8_t twiAddress) {
  MasterSerial.write("Sending message to slave!\n");

  // Initial communication to wake up the sleeping slave microcontroller
  Wire.beginTransmission(twiAddress);
  Wire.endTransmission();

  Wire.beginTransmission(twiAddress);
  Wire.write("Testing...\r\n");
  Wire.endTransmission();
}
