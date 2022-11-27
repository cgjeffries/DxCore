#define da_Serial Serial1

void setup() {
  da_Serial.begin(38400);
  disableAllFloatingPins(HIGH);
  sleepSimple(SLEEP_MODE_STANDBY, true);
}

void loop() {
  //delay(2000);
  //da_Serial.println(NUM_DIGITAL_PINS);
  sleepSimple(SLEEP_MODE_STANDBY, true);
}
