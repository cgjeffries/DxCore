/*
  Program demonstrating getAnalogReadConfig.
*/

#define da_Serial Serial1


void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {

    
    da_Serial.println("Initial get Config (Saved):");
    ADCConfig defaultConfig = ADCConfig_default;
    analogReadConfig(defaultConfig);

    printConfigTable(getAnalogReadConfig());

    da_Serial.println("get config after updating to arbitrary config:");
    ADCConfig modConfig = {
      .convMode = 1,
      .muxNeg = 10, // Not used
      .resolution = 12,
      .prescaler = 128,
      .sampleNum = 2,
      .sampleDelay = 1,
      .sampleLen = 12
    };
    analogReadConfig(modConfig);
    printConfigTable(getAnalogReadConfig());

    printSeperator();

    delay(5000);
  }

void printConfigTable(ADCConfig config) {
  da_Serial.printf("VREF: %d\n", getAnalogReference());
  da_Serial.printf("| %-10s| %-12s| %-12s| %-12s| %-12s| %-12s| %-12s|", 
  "convMode","muxNeg", "resolution", "prescaler",
  "sampleNum","sampleDelay","sampleLen");
  da_Serial.println();
  da_Serial.printf("| %-10d| %-12d| %-12d| %-12d| %-12d| %-12d| %-12d|", 
  config.convMode,config.muxNeg,config.resolution,config.prescaler,
  config.sampleNum,config.sampleDelay,config.sampleLen);
  da_Serial.println();
}

void printSeperator() {
  da_Serial.print("-------------------------------------------------");
  da_Serial.println("------------------------------------------------");
}
