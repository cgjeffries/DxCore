#define da_Serial Serial1
#define INPUT_PIN A0
#define NEGATIVE_PIN A1
#define SAMPLE_NUMBER 128

void printConvModeBit() {
  uint8_t convMode = (ADC0.CTRLA & ADC_CONVMODE_bm) >> 5;
  da_Serial.print("Conversion mode:");
  da_Serial.println(convMode);
}

void sample() {
  int adc_value, sample_index;

  da_Serial.println("begin:");
  for (sample_index = 0; sample_index < SAMPLE_NUMBER; sample_index++) {
    adc_value = analogRead(POS_PIN);

    da_Serial.printf(" %d\t%d", sample_index, adc_value/4);
    da_Serial.println();
  }

  da_Serial.println("end:\n\n");
}

void setup() {
  da_Serial.begin(38400);
}

void loop() {
  da_Serial.println("---------- Entering single-ended mode: ----------")
  analogReadEnableSingleEnded();  
  sample();

  da_Serial.println("---------- Entering differential mode: ----------")
  analogReadEnableDifferential(NEGATIVE_PIN);
  sample();

  delay(5000);
}
