/*
  Program getting a baseline reading with one sample
*/

#define da_Serial Serial1

void setup() {
  da_Serial.begin(38400);     //Data transmission rate

  //ADC Set-up
  analogReference(0x05);      //Setting reference voltage
}

void loop() {
  readADC(1);
}

void readADC (int numSamples){
  analogReadSampleNum(numSamples);
  int adc_value = analogRead(A0)/numSamples;
  while((ADC0.COMMAND & 0b00000001) > 0){} //Wait for conversion to finish
  da_Serial.println(adc_value);
}