#define da_Serial Serial1

void setup(){
  da_Serial.begin(9600);
}

void loop() {
  //delay(5000);
  da_Serial.print("waiting for the character 'c'\n\r");
  //while(da_Serial.peek() == -1){}
  sleepUntilSerial('c', da_Serial);
  if(da_Serial.read() == 'c'){
    da_Serial.print("character recieved!\n\r");
  }
  else{
    da_Serial.print("wrong!\n\r");
  }
  delay(2000);
}
