/*
  Program demonstrating getAnalogEnableDifferential
*/

#define da_Serial Serial1

int POS_PIN = A0;   // select the input pin POSITIVE (PD0)
int NEG_PIN = A1;   // select the input pin NEGATIVE (PD1 - Signal Noise Generator) 
int ledPin = 20;      // select the pin for the LED


void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {  
    da_Serial.println("Initial get Config (Saved):");
    ADCConfig defaultConfig = ADCConfig_default;
    analogReadConfig(defaultConfig);

    sample(getAnalogReadConfig().convMode);

    analogReadEnableDifferential(NEG_PIN);

    sample(getAnalogReadConfig().convMode);

    printSeperator();

    delay(5000);
  }

#define SAMPLE_NUMBER 128

void sample(int convMode) {
  int adc_value, sample_index;

  digitalWrite(ledPin, HIGH);
  da_Serial.println("begin:");
  for (sample_index = 0; sample_index < SAMPLE_NUMBER; sample_index++) {
    adc_value = analogRead(POS_PIN);
    /*
	  if (convMode == 0) {
      adc_value = analogReadEnh(POS_PIN, 12, 0);
    } else {
      adc_value = analogReadDiff(POS_PIN, NEG_PIN, 12, 0);
    }
    */
	
    da_Serial.print(sample_index);
    da_Serial.print(" ");
    da_Serial.println(adc_value);
    da_Serial.print(" ");
  }

  da_Serial.println("end:\n\n");
  digitalWrite(ledPin, LOW);  
}

void printSeperator() {
  da_Serial.print("-------------------------------------------------");
  da_Serial.println("------------------------------------------------");
}
