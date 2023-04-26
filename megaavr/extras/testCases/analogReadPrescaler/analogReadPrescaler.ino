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
  printSample(2);
  delay(100);
  printSample(4);
  delay(100);
  printSample(8);
  delay(100);
  printSample(12);
  delay(100);
  printSample(16);
  delay(100);
  printSample(20);
  delay(100);
  printSample(24);
  delay(100);
  printSample(28);
  delay(100);
  printSample(32);
  delay(100);
  printSample(48);
  delay(100);
  printSample(64);
  delay(100);
  printSample(96);
  delay(100);
  printSample(128);
  delay(100);
  printSample(256);
  delay(100);
  printSample(190); //Invalid argument
  delay(1000);
}

void printSample(uint8_t prescValue) {
  analogReadPrescaler(prescValue);
  int adc_value = analogRead(A0);
  while((ADC0.COMMAND & 0b00000001) > 0){} //Wait for conversion to finish
  da_Serial.print("Result with ");
  da_Serial.print(prescValue);
  da_Serial.print(" as the prescaler: ");
  da_Serial.println(adc_value);
}
