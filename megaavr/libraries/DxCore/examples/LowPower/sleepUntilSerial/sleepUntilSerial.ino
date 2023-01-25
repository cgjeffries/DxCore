#define da_Serial Serial1

void setup(){
  da_Serial.begin(9600);
}

void loop() {
  delay(2000);
  da_Serial.printf("waiting for the character '~'\n\r");
  delay(1000);
  //while(da_Serial.peek() == -1){}
  sleepUntilSerial(0xBF , da_Serial);
  if(da_Serial.read() == 0xbf){
    da_Serial.print("character recieved!\n\r");
  }
  else{
    da_Serial.print("wrong!\n\r");
  }
}
