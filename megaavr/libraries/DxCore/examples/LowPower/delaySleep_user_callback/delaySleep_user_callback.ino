void myFunction(){
  Serial1.print("Got to the custom handler!\n\r");
}

void setup() {
  Serial1.begin(9600);
  // put your setup code here, to run once:
  attachRTCCNTInterrupt(myFunction);
}

void loop() {
  delay(2000);
  delaySleep(2000);
}
