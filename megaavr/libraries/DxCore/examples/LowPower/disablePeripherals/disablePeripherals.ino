const int ledPin = 20; // PC6

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  disableAllPeripheralsDuringSleep();
  delaySleep(2000);
  enableAllPeripheralsDuringSleep();
  delaySleep(2000);
}
