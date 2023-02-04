/*
  Program testing periodic noise
*/

#define da_Serial Serial1

int previousReading = -1;
double marginOfError = 0.1;
bool noiseFlag = false;
int numNoisyReadings = 0;

void setup() {
  da_Serial.begin(38400);     //Data transmission rate

  //ADC Set-up
  analogReference(0x05);      //Setting reference voltage
}

void loop() {
  if(noiseFlag == false){
    readADC(1);
  }
  else{
    readADC(64);
  }
}

void readADC (int numSamples){
  analogReadSampleNum(numSamples);
  int adc_value = analogRead(A0)/numSamples;
  while((ADC0.COMMAND & 0b00000001) > 0){} //Wait for conversion to finish
  da_Serial.println(adc_value);

  if(noiseFlag == true){
    numNoisyReadings++;
    if(numNoisyReadings > 500){
      noiseFlag = false;
    }
  }
  else if((adc_value > (previousReading + previousReading * marginOfError) || adc_value < (previousReading - previousReading * marginOfError)) && previousReading != -1){
    noiseFlag = true;
  }
  previousReading = adc_value;
}