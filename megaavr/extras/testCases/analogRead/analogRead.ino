/*
  Program demonstrating analogReadConfig modifying ADC configurations.
*/
#define da_Serial Serial1

int SINGLE_POS = A0;

// 1.024, 2.048, 4.096, 2.500, 4.006 
double VADCREF = 2.048; // VREF;  (Set VREF in setVREF() for expected value)
double POS_VIN = 0.5; // POSITIVE input pin volatge
// modify to match input pin voltage (ie. if VREF is 1.024v and input pin is 0.5v expected should be ~512) 
uint16_t expected = ( POS_VIN / VADCREF ) * 1000; 

void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {
    setVREF(VADCREF);

    // convMode (0 = Single, 1 = Double) (default 0)
    // muxNeg (Neg pin value for differential mode) (default 0)
    // resolution (12-bit or 10-bit) (default 10)
    // prescaler (2, 4, 8, 12, 16, 20, 24, 28, 32, 48, 64, 96, 128, 256)
    // sampleNum (1, 2, 4, 8, 16, 32, 64, 128) (default 0) result multiplier  
    // sampleDelay (values 0-15) (default 0) 
    // sampleLen

    da_Serial.println("sampleDelay Test");
    for (int i = 0; i <= 10; i++) {
      sampleDelayTest(pow(2,i));
    }
    printSeperator();

    da_Serial.println("sampleLen Test");
    for (int i = 0; i <= 8; i++) {
      sampleLenTest(pow(2,i));
    }
    printSeperator();
  

    delay(5000);
  }


void sampleDelayTest(int sampDelay){
  setADC(0, 10, 10, 2, 1, sampDelay, 1);
  da_Serial.printf("Sample Delay %d  --- (Expected, Result) -> (%d, %d)", sampDelay, expected, analogRead(SINGLE_POS));
  da_Serial.println();
}

void sampleLenTest(int sampLen){
  setADC(0, 10, 10, 2, 1, 1, sampLen);
  da_Serial.printf("Sample Length %d  --- (Expected, Result) -> (%d, %d)", sampLen, expected, analogRead(SINGLE_POS));
  da_Serial.println();
}

void setADC(int _convMode,
            int _muxNeg,
            int _resolution,
            int16_t _prescaler,
            int _sampleNum,
            int _sampleDelay,
            int _sampleLen){

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
    //printConfigTable(getAnalogReadConfig());
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
  da_Serial.println();
}

void setVREF(double ref){
  // DxCore Refrence Voltage modes at `megaavr\extras\Ref_Analog.md`
    /*| AVR Dx/Ex-series (all)                  | Voltage | Minimum Vdd | Mode # |
      |-----------------------------------------|---------|-------------|--------|
      | `VDD` (default)                         | Vcc/Vdd |             |      5 |
      | `INTERNAL1V024`                         | 1.024 V |      2.5* V |      0 |
      | `INTERNAL2V048`                         | 2.048 V |      2.5  V |      1 |
      | `INTERNAL4V096`                         | 4.096 V |      4.55 V |      2 |
      | `INTERNAL2V500`                         | 2.500 V |      2.7  V |      3 |
      | `INTERNAL4V1` (alias of INTERNAL4V096)  | 4.006 V |      4.55 V |      2 |
      | `EXTERNAL` (DA pin PD7)                    | VREF pin|        VREF |      6 |
        */
    // VREF mode (magnitude)
    if (ref == 1.024){
      analogReference(INTERNAL1V024);
    } else if(ref == 2.048){
      analogReference(INTERNAL2V048);
    } else if(ref == 4.096){
      analogReference(INTERNAL4V096);
    } else if(ref == 2.500){
      analogReference(INTERNAL2V500);
    } else if(ref == 4.006){
      analogReference(INTERNAL4V1);
    } else {
      analogReference(VDD);
    } 
}
