#define da_Serial Serial1

void printRegisters() {
  da_Serial.print("ADC0.CTRLA = ");
  da_Serial.println(ADC0.CTRLA, BIN);
  da_Serial.print("ADC0.CTRLB = ");
  da_Serial.println(ADC0.CTRLB, BIN);
  da_Serial.print("ADC0.CTRLC = ");
  da_Serial.println(ADC0.CTRLC, BIN);
  da_Serial.print("ADC0.CTRLD = ");
  da_Serial.println(ADC0.CTRLD, BIN);

  da_Serial.print("ADC0.SAMPCTRL = ");
  da_Serial.println(ADC0.SAMPCTRL);
  da_Serial.print("ADC0.MUXNEG = ");
  da_Serial.println(ADC0.MUXNEG);
}

void setup() {
  da_Serial.begin(38400);

  delay(5000);

  da_Serial.println("Initial state: ");
  printRegisters();
}

void loop() {
  ADCConfig config = {
    .convMode = 0,
    .muxNeg = 0, // Not used
    .resolution = 10,
    .prescaler = 48,
    .sampleNum = 0,
    .sampleDelay = 0,
    .sampleLen = 14
  };
  analogReadConfig(config);

  da_Serial.println("Config 1:");
  printRegisters();

  config = ADCConfig_default;
  config.convMode = 1;
  config.muxNeg = A1;
  config.resolution = 12;
  config.sampleNum = 4;
  config.sampleDelay = 4;
  analogReadConfig(config);

  da_Serial.println("Config 2:");
  printRegisters();

  delay(5000);
}
