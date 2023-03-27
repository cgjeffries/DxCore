/*
  Program demonstrating analogReadConfig modifying ADC configurations.
*/

#define da_Serial Serial1
int _convMode = 1;
int _muxNeg = 10;
int _resolution = 12;
int _prescaler = 128;
int _sampleNum = 2;
int _sampleDelay = 1;
int _sampleLen = 12;


void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {
    da_Serial.println("Inital Analog Read Config:");
    printConfigTable(getAnalogReadConfig());
    

    da_Serial.println("Analog Read Config (Set Default):");
    ADCConfig defaultConfig = ADCConfig_default;
    analogReadConfig(defaultConfig);
    printConfigTable(getAnalogReadConfig());
    da_Serial.println("EXPECTED OUTPUT:");
    da_Serial.printf("| %-10d| %-12d| %-12d| %-12d| %-12d| %-12d| %-12d|", 
                      0, 120, 10, 20, 0, 0, 14);
    da_Serial.println();

    da_Serial.println("Analog Read Config (Set Arbitrary Values):");
    ADCConfig modConfig = {
      .convMode = _convMode,
      .muxNeg = _muxNeg,
      .resolution = _resolution,
      .prescaler = _prescaler,
      .sampleNum = _sampleNum,
      .sampleDelay = _sampleDelay,
      .sampleLen = _sampleLen 
    };
    analogReadConfig(modConfig);
    printConfigTable(getAnalogReadConfig());
    da_Serial.println("EXPECTED OUTPUT:");
    da_Serial.printf("| %-10d| %-12d| %-12d| %-12d| %-12d| %-12d| %-12d|", 
                      _convMode, _muxNeg, _resolution, _prescaler, 
                      _sampleNum, _sampleDelay, _sampleLen);
    da_Serial.println();

    printSeperator();

    delay(5000);
  }

void printConfigTable(ADCConfig config) {
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
