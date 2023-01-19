/*
  Program demonstrating getAnalogEnableDifferential
*/

#define da_Serial Serial1

int POS_PIN = A0;   // select the input pin POSITIVE (PD0)
int NEG_PIN = A1;   // select the input pin NEGATIVE (PD1 - Signal Noise Generator) 

void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {  
    ADCConfig defaultConfig = ADCConfig_default;
    analogReadConfig(defaultConfig);

    da_Serial.printf("Single Ended Mode: (ConvMode = %d)", getAnalogReadConfig().convMode);
    da_Serial.println();
    sample(getAnalogReadConfig().convMode);

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

  da_Serial.println("begin:");
  for (sample_index = 0; sample_index < SAMPLE_NUMBER; sample_index++) {
    adc_value = analogRead(POS_PIN);
	
    da_Serial.printf(" %d\t%d", sample_index, adc_value/4);
    da_Serial.println();
  }

  da_Serial.println("end:\n\n");
}

void printSeperator() {
  da_Serial.println("-------------------------------------------------");
}
