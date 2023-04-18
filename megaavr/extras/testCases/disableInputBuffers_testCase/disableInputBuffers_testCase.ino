const int ledPin = 20; // PC6

// Use a voltmeter or power debugger to check the power draw
void setup() {
  Serial1.begin(38400);
}

void loop() {
  // Disable Input Buffers
  disableInputBuffers();
  Serial1.println("DISABLE : STANDBY");
  delaySleep(2000);
  Serial1.println("DISABLE : IDLE");
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(2000);
  Serial1.println("DISABLE : ACTIVE");
  disableSleepMode();
  delay(2000);

  // Enable Input Buffers
  enableInputBuffers();
  Serial1.println("ENABLE : STANDBY");
  delaySleep(2000);
  Serial1.println("ENABLE : IDLE");
  sleepSimple(SLEEP_MODE_IDLE, true);
  delay(2000);
  Serial1.println("ENABLE : ACTIVE");
  disableSleepMode();
  delay(2000);

  Serial1.println(" - Looped - ");
}
