// Use a voltmeter or power debugger to check the power draw
void setup() {
}

void loop() {
  delay(1000);
  // Peripherals Disabled
  disableAllPeripheralsDuringSleep();
  delaySleep(2000);

  delay(1000);

  // Peripherals Enabled
  enableAllPeripheralsDuringSleep();
  delaySleep(2000);
}

void wake_up() {

}