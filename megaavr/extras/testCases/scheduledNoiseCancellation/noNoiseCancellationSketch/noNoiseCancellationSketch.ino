/*
  Program testing periodic noise
*/

#define da_Serial Serial1

long int startTime;
long int currentTime;
int hertz = 100;
int frequency;

void setup() {
  da_Serial.begin(38400);     //Data transmission rate

  //ADC Set-up
  analogReference(0x05);      //Setting reference voltage

  startTime = millis() % 1000;
  frequency = 1000/hertz;
  da_Serial.println(startTime);
}

void loop() {
    //No Noise
    analogReadSampleNum(4);
    int adc_value = analogRead(A0)/4;
    while((ADC0.COMMAND & 0b00000001) > 0){} //Wait for conversion to finish
    da_Serial.println(adc_value);
}