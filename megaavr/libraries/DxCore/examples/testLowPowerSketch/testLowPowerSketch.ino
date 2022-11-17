#define da_Serial Serial1

/*
Defined Sleep Modes in megaavr/extras/ioheaders/ioavr128da48.h:
  SLEEP_MODE_IDLE
  SLEEP_MODE_STANDBY
  SLEEP_MODE_PWR_DOWN
*/

void setup() {
  da_Serial.begin(38400);
  setSleepMode(SLEEP_MODE_PWR_DOWN);
  enableSleepMode();
  setSleepMode(SLEEP_MODE_STANDBY);
  // disableSleepMode();

  da_Serial.begin(9600);
}

void loop() {
  delay(2000);

  // When the board goes to sleep, da_Serial stops printing
  // da_Serial.write(45);
  // da_Serial.println(555);
  // enterSleep(true);
  // sleepSimple(SLEEP_MODE_IDLE, false);

  da_Serial.print("SLPCTRL.CTRLA in decimal: ");
  da_Serial.println(SLPCTRL.CTRLA);
}
