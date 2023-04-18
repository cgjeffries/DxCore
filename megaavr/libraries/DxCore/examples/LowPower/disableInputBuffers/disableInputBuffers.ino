void setup() {
  //pinMode(ledPin, OUTPUT);
  
  disableAllPeripheralsDuringSleep();
}


void loop() {
  enableInputBuffers();
  delaySleep(2000);

  disableInputBuffers();
  delaySleep(2000);
}
