/*
  Program demonstrating getAnalogEnableDifferential
*/

#define da_Serial Serial1
#define neg_pin A1 // select the input pin NEGATIVE (PD1) 


void setup() {
  da_Serial.begin(38400); // Baud rate
}

void loop() {  
    da_Serial.println("Initial get Config (Saved):");
    ADCConfig defaultConfig = ADCConfig_default;
    analogReadConfig(defaultConfig);

    printConvMode("convMode (Default)", getAnalogReadConfig());

    da_Serial.println("get config after updating to arbitrary config:");
    analogReadEnableDifferential(neg_pin);
	
    printConvMode("convMode (Enabled)", getAnalogReadConfig());
	
	#TODO: Read some input to test neg_pin input

    printSeperator();

    delay(5000);
  }

void printConvMode(String msg, ADCConfig config) {
  da_Serial.printf("%s: %d", msg, config.convMode);
}

void printSeperator() {
  da_Serial.print("-------------------------------------------------");
  da_Serial.println("------------------------------------------------");
}
