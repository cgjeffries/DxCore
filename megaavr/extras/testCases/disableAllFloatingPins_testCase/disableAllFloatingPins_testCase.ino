const int ledPin = 20; // PC6
const int userSwitchPin = 21; // PC7

// Use a voltmeter or power debugger to check the power draw
void setup() {
  Serial1.begin(38400);
}

void loop() {
  // Most pins set to pin mode OUTPUT and digital writing HIGH
  disableAllFloatingPins(HIGH);
  pinMode(userSwitchPin, INPUT_PULLUP); // PC7 has an internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(userSwitchPin), wake_up, CHANGE);
  digitalWrite(ledPin, HIGH); // HIGH is picked since that turns off the LED on the AVR128DA48 board

  delay(1000);
  Serial1.println("HIGH : STANDBY");
  sleepSimple(SLEEP_MODE_STANDBY, true); // Press user switch here
  delay(2000);
  Serial1.println("HIGH : IDLE");
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(2000);

  // Most pins set to pin mode OUTPUT and digital writing LOW
  disableAllFloatingPins(LOW);
  pinMode(userSwitchPin, INPUT_PULLUP); // PC7 has an internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(userSwitchPin), wake_up, CHANGE);
  digitalWrite(ledPin, HIGH);

  delay(1000);
  Serial1.println("LOW : STANDBY");
  sleepSimple(SLEEP_MODE_STANDBY, true); // Press user switch here
  delay(2000);
  Serial1.println("LOW : IDLE");
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(2000);

  Serial1.println(" - Looped - ");
}

void wake_up() {
  Serial1.println("[Woken up]");
}