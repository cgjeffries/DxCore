/*
  Program testing the results of analogReadSampleNum
*/

#define da_Serial Serial1

void setup() {
  da_Serial.begin(38400);     //Data transmission rate

  //ADC Set-up
  analogReference(0x05);      //Setting reference voltage
}

void loop() {
  printSample(1);
  delay(250);
  printSample(4);
  delay(250);
  printSample(16);
  delay(250);
  printSample(64);
  delay(250);
  printSample(190); //Invalid argument
  delay(1000);
}

void printSample(uint8_t accumValue) {
  analogReadSampleNum(accumValue);
  int adc_value = analogRead(A0);
  while((ADC0.COMMAND & 0b00000001) > 0){} //Wait for conversion to finish
  da_Serial.print("Result with ");
  da_Serial.print(accumValue);
  da_Serial.print(" samples accumulated: ");
  da_Serial.println(adc_value);
}
