const int ledPin = 20; // PC6

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);

  delaySleep(3000);
  
  digitalWrite(ledPin, LOW);
  delay(3000);
}
