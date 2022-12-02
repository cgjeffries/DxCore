const int userSwitchPin = 21; // PC7

// Use a voltmeter or power debugger to check the power draw
void setup() {
  pinMode(userSwitchPin, INPUT_PULLUP); // PC7 has an internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(userSwitchPin), wake_up, CHANGE);
}

void loop() {
  // Peripherals Disabled
  disableAllPeripheralsDuringSleep();
  sleepSimple(SLEEP_MODE_STANDBY, true); // Press user switch here
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(3000);

  // Peripherals Enabled
  enableAllPeripheralsDuringSleep();
  sleepSimple(SLEEP_MODE_STANDBY, true); // Press user switch here
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(3000);
}

void wake_up() {

}