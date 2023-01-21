/*
  Program demonstrating getAnalogEnableDifferential
*/

#define da_Serial Serial1

int POS_PIN = A0;   // Positive pin (PD0)
int NEG_PIN = ADC_DAC0; //ADC_DACREF0;//A1;// select the input pin NEGATIVE (DAC) 

// Calculate Expected Value
double VAINP = 2.5; // Positive pin (input from PD0)
double VAINN = 2.5; // NEGATIVE <- DAC
double VADCREF = 1.024; // VREF; 

void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {  
    da_Serial.println("POSITIVE: PD0 external pin");

    // DxCore Refrence Voltage modes at `megaavr\extras\Ref_Analog.md`
    /*| AVR Dx/Ex-series (all)                  | Voltage | Minimum Vdd | Mode # |
      |-----------------------------------------|---------|-------------|--------|
      | `VDD` (default)                         | Vcc/Vdd |             |      5 |
      | `INTERNAL1V024`                         | 1.024 V |      2.5* V |      0 |
      | `INTERNAL2V048`                         | 2.048 V |      2.5  V |      1 |
      | `INTERNAL4V096`                         | 4.096 V |      4.55 V |      2 |
      | `INTERNAL2V500`                         | 2.500 V |      2.7  V |      3 |
      | `INTERNAL4V1` (alias of INTERNAL4V096)  | 4.006 V |      4.55 V |      2 |
      | `EXTERNAL`                              | VREF pin|        VREF |      6 |*/
    // NEGATIVE DAC mode (midpoint)
    DACReference(INTERNAL2V500);  
    // VREF mode (magnitude)
    analogReference(INTERNAL1V024);
    
    
    // Midpoint of expected input voltage range
    da_Serial.printf("NEGATIVE: DAC mode = %d", getDACReference());
    //da_Serial.print("NEGATIVE: VTG 3.3v");
    da_Serial.println();
    // Magnitude of variance
    da_Serial.printf("VREF    : %d", getAnalogReference());
    da_Serial.println();
    
    ADCConfig defaultConfig = ADCConfig_default;
    analogReadConfig(defaultConfig);

    analogReadEnableDifferential(NEG_PIN);
    da_Serial.printf("convMode = %d, resolution = ", getAnalogReadConfig().convMode) ;
    da_Serial.println(getAnalogReadConfig().resolution);
    sample(getAnalogReadConfig().convMode);

    printSeperator();

    delay(5000);
  }

#define SAMPLE_NUMBER 128

void sample(int convMode) {
  int adc_value, sample_index;
  double avg = 0;

  for (sample_index = 0; sample_index < SAMPLE_NUMBER; sample_index++) {
    adc_value = analogRead(POS_PIN);
    avg = avg + adc_value;
  }
  int out = (avg/sample_index);
  da_Serial.printf("ACTUAL ADC value  : %d", out);
  da_Serial.println();
  double diff10bit = (((VAINP - VAINN) / VADCREF) * 512);
  // int diff12bit = (((VAINP - VAINN) / VADCREF) * 2048);
  da_Serial.print("EXPECTED ADC value: ");
  da_Serial.println(diff10bit);
}


void printSeperator() {
  da_Serial.println("-------------------------------------------------");
}
