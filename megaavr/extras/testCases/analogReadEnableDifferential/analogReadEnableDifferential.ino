/*
  Program demonstrating getAnalogEnableDifferential
*/

#define da_Serial Serial1

int POS_PIN = A0;   // select the input pin POSITIVE (PD0)
int NEG_PIN = ADC_DAC0;   // select the input pin NEGATIVE (DAC) 

void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {  
    // megaavr\extras\Ref_Analog.md
    da_Serial.printf("VREF: %d\n", getAnalogReference());
    da_Serial.printf("DAC: %d\n", getDACReference());
    analogReference(INTERNAL1V024);
    // Set DAC to 2.5 v
    DACReference(INTERNAL2V500);  // 2.5v
    // DACReference(INTERNAL1V024); // 1.024 v
    da_Serial.printf("DAC: %d\n", getDACReference());

    ADCConfig defaultConfig = ADCConfig_default;
    analogReadConfig(defaultConfig);
    

    //da_Serial.printf("Single Ended Mode: (ConvMode = %d)", getAnalogReadConfig().convMode);
    //da_Serial.println();
    //sample(getAnalogReadConfig().convMode);

    analogReadEnableDifferential(NEG_PIN);
    da_Serial.printf("Differential Mode: (ConvMode = %d)", getAnalogReadConfig().convMode);
    da_Serial.println();
    sample(getAnalogReadConfig().convMode);


    printSeperator();

    delay(5000);
  }

#define SAMPLE_NUMBER 128

void sample(int convMode) {
  int adc_value, sample_index;

  for (sample_index = 0; sample_index < SAMPLE_NUMBER; sample_index++) {
    adc_value = analogRead(POS_PIN);

    da_Serial.printf(" %d\t%d", sample_index, adc_value);
    da_Serial.println();
  }
}

void printSeperator() {
  da_Serial.println("-------------------------------------------------");
}
