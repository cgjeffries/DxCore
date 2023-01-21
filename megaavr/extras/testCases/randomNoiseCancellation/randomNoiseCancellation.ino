#define da_Serial Serial1
#define INPUT_PIN A0
#define SAMPLE_NUMBER 128

ADCConfig defaultConfig;

void sample(int divisor) {
  uint16_t adc_value, sample_index;

  da_Serial.println("begin:");
  for (sample_index = 0; sample_index < SAMPLE_NUMBER; sample_index++) {
    adc_value = (uint16_t) analogRead(INPUT_PIN);

    da_Serial.printf("%d %d", sample_index, adc_value/divisor);
    da_Serial.println();
  }

  da_Serial.println("end\n\n");
}

void setup() {
  da_Serial.begin(38400);

  analogReference(VREF_REFSEL_2V500_gc);

  defaultConfig = getAnalogReadConfig();
}

void loop() {
  da_Serial.println("---------- Sample with default settings: ----------");
  analogReadConfig(defaultConfig);
  sample(1);

  da_Serial.println("---------- Sample with 8-sample accumulation ----------");
  analogReadSampleNum(8);
  sample(8);

  da_Serial.println("---------- Sample with 32-sample accumulation ----------");
  analogReadSampleNum(32);
  sample(32);

  da_Serial.println("---------- Sample with 64-sample accumulation ----------");
  analogReadSampleNum(64);
  sample(64);

  da_Serial.println("---------- Sample with 128-sample accumulation ----------");
  analogReadSampleNum(128);
  sample(64); // Only divide by 64 due to value truncation when using 128 samples

  delay(5000);
}
