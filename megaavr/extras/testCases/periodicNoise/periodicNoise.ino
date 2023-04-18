/*
  Program testing periodic noise
*/

#define da_Serial Serial1

void setup() {
  da_Serial.begin(38400);     //Data transmission rate

  //ADC Set-up
  analogReference(0x05);      //Setting reference voltage
}

void loop() {

  da_Serial.println("4 samples being accumulated");

  for(int i = 0; i < 30; i++){
    analogReadSampleNum(4);
    int adc_value = analogRead(A0);
    while((ADC0.COMMAND & 0b00000001) > 0){} //Wait for conversion to finish
    da_Serial.println(adc_value);
  }

  delay(500);


  da_Serial.println("16 samples being accumulated");

  for(int i = 0; i < 30; i++){
    analogReadSampleNum(16);
    int adc_value = analogRead(A0);
    while((ADC0.COMMAND & 0b00000001) > 0){} //Wait for conversion to finish
    da_Serial.println(adc_value);
  }

  delay(500);


  da_Serial.println("64 samples being accumulated");

  for(int i = 0; i < 30; i++){
    analogReadSampleNum(64);
    int adc_value = analogRead(A0);
    while((ADC0.COMMAND & 0b00000001) > 0){} //Wait for conversion to finish
    da_Serial.println(adc_value);
  }

  delay(500);
}
