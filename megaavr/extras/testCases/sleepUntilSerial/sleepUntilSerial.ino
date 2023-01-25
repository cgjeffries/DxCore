#define da_Serial Serial1

void setup(){
  da_Serial.begin(9600);
}

void loop() {
  delay(2000);
  da_Serial.printf("waiting for the character 'c'\n\r");
  delay(1000);
  sleepUntilSerial('c' , da_Serial);
  if(da_Serial.read() == 'c'){
    da_Serial.print("character received!\n\r");
  }
  else{
    da_Serial.print("wrong!\n\r");
  }
}
