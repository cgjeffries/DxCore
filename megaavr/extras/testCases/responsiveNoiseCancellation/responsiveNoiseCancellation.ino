/*
  Program testing responsive noise cancellation
*/

#define da_Serial Serial1

int previousReading = -1;
double marginOfError = 0.05;
bool recentNoise = false;
int numNoisyReadings = 0;

void setup() {
  da_Serial.begin(38400);     //Data transmission rate

  //ADC Set-up
  analogReference(0x05);      //Setting reference voltage
}

void loop() {
  if(recentNoise == false){
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

  if(recentNoise == true){
    numNoisyReadings++;
    if(numNoisyReadings > 500){
      recentNoise = false;
      numNoisyReadings = 0;
    }
  }
  else if((adc_value > (previousReading + previousReading * marginOfError) || adc_value < (previousReading - previousReading * marginOfError)) && previousReading != -1){
    recentNoise = true;
  }
  previousReading = adc_value;
}