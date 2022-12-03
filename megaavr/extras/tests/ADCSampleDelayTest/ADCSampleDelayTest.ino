#define da_Serial Serial1
#define VDD_REF 0x05
#define INPUT_PIN A0
#define LED_PIN 13
#define SAMPLE_NUMBER 64

void setup() {
  da_Serial.begin(38400);

  analogReference(VDD_REF);
  analogReadResolution(12);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  da_Serial.println("Sample delay: 0");
  analogReadSampleDelay(0);
  rawSample();
 
  da_Serial.println("Sample delay: 5");
  analogReadSampleDelay(5);
  rawSample();

  da_Serial.println("Sample delay: 10");
  analogReadSampleDelay(10);
  rawSample();

  da_Serial.println("Sample delay: 15");
  analogReadSampleDelay(15);
  rawSample();

  delay(5000);
}

void rawSample() {
  int adc_value, sample_index;

  digitalWrite(LED_PIN, HIGH);
  da_Serial.println("begin:");
  for (sample_index = 0; sample_index < SAMPLE_NUMBER; sample_index++) {

    adc_value = analogRead(INPUT_PIN);
    da_Serial.print(sample_index);
    da_Serial.print(",");
    da_Serial.println(adc_value);
  }

  da_Serial.println("end:\n\n");
  digitalWrite(LED_PIN, LOW);  
}
