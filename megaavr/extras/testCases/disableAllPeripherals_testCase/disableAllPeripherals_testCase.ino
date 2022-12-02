const int userSwitchPin = 21; // PC7

// Use a voltmeter or power debugger to check the power draw
void setup() {
  Serial1.begin(38400);
  pinMode(userSwitchPin, INPUT_PULLUP); // PC7 has an internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(userSwitchPin), wake_up, CHANGE);
}

void loop() {
  Serial1.println("Disabled Peripherals");
  disableAllPeripheralsDuringSleep();
  Serial1.println("Entering Standby Mode");
  sleepSimple(SLEEP_MODE_STANDBY, true);
  delaySleep(2000);
  Serial1.println("Entering Idle Mode");
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(2000);

  Serial1.println("Enabled Peripherals");
  enableAllPeripheralsDuringSleep();
  Serial1.println("Entering Standby Mode");
  sleepSimple(SLEEP_MODE_STANDBY, true);
  delaySleep(2000);
  Serial1.println("Entering Idle Mode");
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(2000);

  Serial1.println(" - Looped - ");
}

void wake_up() {
  Serial1.println("[Woken up]");
}