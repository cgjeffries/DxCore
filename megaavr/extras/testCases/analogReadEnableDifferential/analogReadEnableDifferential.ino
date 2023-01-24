/*
  Program demonstrating getAnalogEnableDifferential
*/
#include <Comparator.h>
#define da_Serial Serial1

int POS_PIN = ADC_DACREF0; //A0; // Positive pin (DAC or swap `A0;` to use external pin PD0) 
int NEG_PIN = A1; // select the input pin NEGATIVE (PD1 -> pins-arduino.h )

// Calculate Expected Value
double VAINP = 1.024; // POSITIVE (DAC) (Set reference in setDAC() for expected value)
double VAINN = 1.0; // NEGATIVE (external pin PD0)
double VADCREF = 1.024; // VREF;  (Set VREF in setVREF() for expected value)

void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {  

    // Set DAC -> POSITIVE -> Magnitude of variance
    setDAC();
    // Set VREF -> Magnitude of variance
    setVREF();
    
    sample();
    printExpectedOutput();
    printSeperator();

    delay(5000);
  }

void setDAC() {
	// DxCore Refrence Voltage modes at `megaavr\extras\Ref_Analog.md`
    /*| AVR Dx/Ex-series (all)                  | Voltage | Minimum Vdd | Mode # |
      |-----------------------------------------|---------|-------------|--------|
      | `VDD` (default)                         | Vcc/Vdd |             |      5 |
      | `INTERNAL1V024`                         | 1.024 V |      2.5* V |      0 |
      | `INTERNAL2V048`                         | 2.048 V |      2.5  V |      1 |
      | `INTERNAL4V096`                         | 4.096 V |      4.55 V |      2 |
      | `INTERNAL2V500`                         | 2.500 V |      2.7  V |      3 |
      | `INTERNAL4V1` (alias of INTERNAL4V096)  | 4.006 V |      4.55 V |      2 |
      | `EXTERNAL` (DA pin PD7)                 | VREF pin|        VREF |      6 |
        */
    DACReference(INTERNAL1V024)
}


void setVREF(){
  // DxCore Refrence Voltage modes at `megaavr\extras\Ref_Analog.md`
    /*| AVR Dx/Ex-series (all)                  | Voltage | Minimum Vdd | Mode # |
      |-----------------------------------------|---------|-------------|--------|
      | `VDD` (default)                         | Vcc/Vdd |             |      5 |
      | `INTERNAL1V024`                         | 1.024 V |      2.5* V |      0 |
      | `INTERNAL2V048`                         | 2.048 V |      2.5  V |      1 |
      | `INTERNAL4V096`                         | 4.096 V |      4.55 V |      2 |
      | `INTERNAL2V500`                         | 2.500 V |      2.7  V |      3 |
      | `INTERNAL4V1` (alias of INTERNAL4V096)  | 4.006 V |      4.55 V |      2 |
      | `EXTERNAL` (DA pin PD7)                 | VREF pin|        VREF |      6 |
        */
    // VREF mode (magnitude)
    analogReference(INTERNAL1V024);
}


#define SAMPLE_NUMBER 128
void sample() {
  int adc_value, sample_index;
  double avg = 0;

  for (sample_index = 0; sample_index < SAMPLE_NUMBER; sample_index++) {
    adc_value = analogRead(POS_PIN);
    avg = avg + adc_value;
  }
  int out = (avg/sample_index);
  da_Serial.printf("\tACTUAL ADC value  : %d", out);
  da_Serial.println();
  
}

void printExpectedOutput() {
  // Voltage calculations [-512,512] (pg 484)
    double expectedOutput = -1;
    if (getAnalogReadConfig().resolution == 10) {
      expectedOutput = (((VAINP - VAINN) / VADCREF) * 512); // [-512,512]
    } else {
      expectedOutput = (((VAINP - VAINN) / VADCREF) * 2048); // [-2048,2047]
    }
    da_Serial.printf("\tEXPECTED ADC value: ");
    da_Serial.println(expectedOutput);
}


void printSeperator() {
  da_Serial.println("-------------------------------------------------");
}
