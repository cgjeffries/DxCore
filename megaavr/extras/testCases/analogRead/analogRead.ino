/*
  Program demonstrating analogReadConfig modifying ADC configurations.
*/
#include <Comparator.h>
#define da_Serial Serial1

int SINGLE_POS = A0;
int DIFF_POS = ADC_DACREF0;
int POS_PIN = A0; //A0; // Positive pin (DAC or swap `A0;` to use external pin PD0) 
int NEG_PIN = A0; // select the input pin NEGATIVE (PD0 -> pins-arduino.h )
int RES = 10;
int CONVMODE = 0;

// 1.024, 2.048, 4.096, 2.500, 4.006 
double VADCREF = 1.024; // VREF;  (Set VREF in setVREF() for expected value)
double EXTERNAL_PIN = 1.25; // POSITIVE input pin volatge
double DAC_REF = 2.500; 
// modify to match input pin voltage (ie. if VREF is 1.024v and input pin is 0.5v expected should be ~512) 
// expected = VREF / EXTERNAL_PIN
int16_t expected = 0; 
uint16_t expected_10_single = ( EXTERNAL_PIN / VADCREF ) * 1024; 
uint16_t expected_12_single = ( EXTERNAL_PIN / VADCREF ) * 4096; 
// Differential equations "reversed" from datasheet, DAC must be positive input, external negative.
int16_t expected_10_diff = ( ( (EXTERNAL_PIN - DAC_REF) / VADCREF ) * 512 );
int16_t expected_12_diff = ( ( (EXTERNAL_PIN - DAC_REF) / VADCREF ) * 2048 ); 


void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {
    // Set DAC -> POSITIVE -> Magnitude of variance
    setDAC(DAC_REF);
    setVREF(VADCREF);

    // convMode (0 = Single, 1 = Double) (default 0)
    // muxNeg (Neg pin value for differential mode) (default 0)
    // resolution (12-bit or 10-bit) (default 10)
    // prescaler (2, 4, 8, 12, 16, 20, 24, 28, 32, 48, 64, 96, 128, 256)
    // sampleNum (1, 2, 4, 8, 16, 32, 64, 128) (default 0) result multiplier  
    // sampleDelay (values 0-15) (default 0) 
    // sampleLen
    RES = 10;
    CONVMODE = 0;
    POS_PIN = SINGLE_POS;
    expected = expected_10_single;
    

    printSeperator();
    da_Serial.println("             10 bit Single-Ended test");
    print10_single();
    da_Serial.println();
    printSeperator();

    da_Serial.println("prescalar Test");
    prescalarTest(2);
    prescalarTest(4);
    prescalarTest(8);
    prescalarTest(12);
    prescalarTest(16);
    prescalarTest(20);
    prescalarTest(24);
    prescalarTest(28);
    prescalarTest(32);
    prescalarTest(48);
    prescalarTest(64);
    prescalarTest(96);
    prescalarTest(128);
    prescalarTest(256);
    printSeperator();
  
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

    da_Serial.println("sampleNum Test");
    sampleNumTest(1);
    sampleNumTest(2);
    sampleNumTest(4);
    sampleNumTest(8);
    sampleNumTest(16);
    sampleNumTest(32);
    sampleNumTest(64);
    sampleNumTest(128);
    printConfigTable(getAnalogReadConfig());
    printSeperator();


    RES = 12;
    CONVMODE = 0;
    expected = expected_12_single;
    printSeperator();
    da_Serial.println("             12 bit Single-Ended test");
    print12_single();
    printSeperator();
    da_Serial.println("sampleNum Test");
    sampleNumTest(1);
    sampleNumTest(2);
    sampleNumTest(4);
    sampleNumTest(8);
    sampleNumTest(16);
    sampleNumTest(32);
    sampleNumTest(64);
    sampleNumTest(128);

    printConfigTable(getAnalogReadConfig());
    printSeperator();

    RES = 10;
    CONVMODE = 1;
    POS_PIN = DIFF_POS;
    expected = 0;
    expected = expected_10_diff;
    printSeperator();
    da_Serial.println("             10 bit Differential test");
    print10_diff();
    printSeperator();
    da_Serial.println("sampleNum Test");
    sampleNumTest(1);
    sampleNumTest(2);
    sampleNumTest(4);
    sampleNumTest(8);
    sampleNumTest(16);
    sampleNumTest(32);
    sampleNumTest(64);
    sampleNumTest(128);
    printConfigTable(getAnalogReadConfig());
    printSeperator();

    RES = 12;
    CONVMODE = 1;
    expected = expected_12_diff;
    printSeperator();
    da_Serial.println("             12 bit Differential test");
    print12_diff();
    printSeperator();
    da_Serial.println("sampleNum Test");
    sampleNumTest(1);
    sampleNumTest(2);
    sampleNumTest(4);
    sampleNumTest(8);
    sampleNumTest(16);
    sampleNumTest(32);
    sampleNumTest(64);
    sampleNumTest(128);
    printConfigTable(getAnalogReadConfig());
    printSeperator();

    

    delay(5000);
  }

// uint16_t expected_10_single = ( EXTERNAL_PIN / VADCREF ) * 1024; 
void print10_single(){
  da_Serial.print("( ");
  da_Serial.print(EXTERNAL_PIN);
  da_Serial.print(" / ");
  da_Serial.print( VADCREF);
  da_Serial.print(" ) * 1024 = ");
  da_Serial.print(expected);
  da_Serial.println();
}
void print12_single(){
  da_Serial.print("( ");
  da_Serial.print(EXTERNAL_PIN);
  da_Serial.print(" / ");
  da_Serial.print( VADCREF);
  da_Serial.print(" ) * 4096 = ");
  da_Serial.print(expected);
  da_Serial.println();
}
void print10_diff(){
  da_Serial.print("( ( ");
  da_Serial.print(EXTERNAL_PIN);
  da_Serial.print(" - ");
  da_Serial.print(DAC_REF);
  da_Serial.print(" ) / ");
  da_Serial.print( VADCREF);
  da_Serial.print(" ) * 512 = ");
  da_Serial.print(expected);
  da_Serial.println();
}
void print12_diff(){
  da_Serial.print("( ( ");
  da_Serial.print(EXTERNAL_PIN);
  da_Serial.print(" - ");
  da_Serial.print(DAC_REF);  
  da_Serial.print(" ) / ");
  da_Serial.print( VADCREF);
  da_Serial.print(" ) * 2048 = ");
  da_Serial.print(expected);
  da_Serial.println();
}


void prescalarTest(uint16_t presc){
  setADC(CONVMODE, NEG_PIN, RES, presc, 1, 1, 1);
  da_Serial.printf("Prescalar Value %d  --- (Expected, Result) -> (%d, %d)", presc, expected, analogRead(POS_PIN));
  da_Serial.println();
}

void sampleNumTest(uint16_t sampNum){
  setADC(CONVMODE, NEG_PIN, RES, 2, sampNum, 1, 1);
  if (sampNum == 1) {
    da_Serial.printf("Sample Number %d  --- (Expected, Result) -> (%d, %d)", sampNum, expected*sampNum, analogRead(POS_PIN));
  } else {
    da_Serial.printf("Sample Number %d  --- (Expected, Result) -> (%d, %d)", sampNum, expected*sampNum, analogRead(POS_PIN));
  }
  da_Serial.println();
}

void sampleDelayTest(int sampDelay){
  setADC(CONVMODE, NEG_PIN, RES, 2, 1, sampDelay, 1);
  da_Serial.printf("Sample Delay %d  --- (Expected, Result) -> (%d, %d)", sampDelay, expected, analogRead(POS_PIN));
  da_Serial.println();
}

void sampleLenTest(int sampLen){
  setADC(CONVMODE, NEG_PIN, RES, 2, 1, 1, sampLen);
  da_Serial.printf("Sample Length %d  --- (Expected, Result) -> (%d, %d)", sampLen, expected, analogRead(POS_PIN));
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

void setDAC(double ref) {
    // DxCore Refrence Voltage modes at `megaavr\extras\Ref_Analog.md`
    /*  vref_1v024 = 0x00, // 1.024V
        vref_2v048 = 0x01, // 2.048V
        vref_2v500 = 0x02, // 2.5V
        vref_2v5   = 0x02,
        vref_4v096 = 0x03, // 4.096V
        vref_vdd   = 0x07, // VDD as reference
        */
    Comparator.input_n = comparator::in_n::dacref;

    if (ref == 1.024){
      Comparator.reference = comparator::ref::vref_1v024;
    } else if(ref == 2.048){
      da_Serial.print("REF IS 2.048");
      Comparator.reference = comparator::ref::vref_2v048;
    } else if(ref == 2.500){
      Comparator.reference = comparator::ref::vref_2v500;
    } else if(ref == 4.096){
      Comparator.reference = comparator::ref::vref_4v096;
    } else {
      Comparator.reference = comparator::ref::vref_1v024; 
    } 
    
    Comparator.init();
    Comparator.start();
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
