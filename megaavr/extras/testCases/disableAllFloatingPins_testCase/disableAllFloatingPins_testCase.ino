// Use a voltmeter or power debugger to check the power draw
void setup() {
  delay(1000);
}

void loop() {
  delaySleep(2000);
  disableAllFloatingPins(true);
  delay(1000);
}
