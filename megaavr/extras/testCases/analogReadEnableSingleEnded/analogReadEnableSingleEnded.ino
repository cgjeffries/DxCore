#define da_Serial Serial1
#define INPUT_PIN A0
#define NEGATIVE_PIN A1

void setup() {
  da_Serial.begin(38400);
}

void loop() {
  analogReadEnableSingleEnded();  
  da_Serial.print("Single-ended reading: ")
  da_Serial.println(analogRead(INPUT_PIN));

  analogReadEnableDifferential(NEGATIVE_PIN);
  da_Serial.print("Differential reading: ")
  da_Serial.println(analogRead(INPUT_PIN));

  delay(1000);
}
