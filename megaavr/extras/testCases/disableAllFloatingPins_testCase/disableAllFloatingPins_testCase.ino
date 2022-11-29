const int userSwitchPin = 21; // PC7

void wake_up() {
  
}

// Use a voltmeter or power debugger to check the power draw
void setup() {
  attachInterrupt(digitalPinToInterrupt(userSwitchPin), wake_up, RISING);
}

void loop() {
  // All pins set to pin mode OUTPUT and digital writing HIGH
  disableAllFloatingPins(HIGH);
  delay(2000);
  sleepSimple(SLEEP_MODE_PWR_DOWN, true);
  delay(2000);
  sleepSimple(SLEEP_MODE_STANDBY, true);
  delay(2000);
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(2000);

  // All pins set to pin mode OUTPUT and digital writing LOW
  disableAllFloatingPins(LOW);
  delay(2000);
  sleepSimple(SLEEP_MODE_PWR_DOWN, true);
  delay(2000);
  sleepSimple(SLEEP_MODE_STANDBY, true);
  delay(2000);
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(2000);
}