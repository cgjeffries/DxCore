const int ledPin = 20; // PC6

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);

  delaySleep(1000);
  
  digitalWrite(ledPin, LOW);
  delay(2000);
}
