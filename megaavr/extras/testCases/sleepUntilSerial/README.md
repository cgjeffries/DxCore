# Sleep Until Serial Test
This test sketch demonstrates the use of the sleepUntilSerial function to sleep the system
until a matching byte is received by the hardware serial interface.

## Instructions
1. Connect the Curiosity nano board to your computer
2. Connect the curiosity nano power supply in series with an ammeter such as a multimeter or AVR power debugger (recommended)
3. Download the sketch to the board.
4. Open a serial console in the COM port that the arduino is on, either using the built in serial console
int he arduino IDE, or using a separate program like PuTTY. Set the Baud rate to 9600.
5. Verify using the ammeter that the system has entered sleep mode (power should be below 100uA)
6. Using the serial console, send various characters other than 'c' to the device. You may see very brief
power spikes in the ammeter, but the system should not fully wake.
7. Send the 'c' character. You should see the system awake and draw normal power using the ammeter,
and the message "character received!" should appear in the console. If any other message appears, the test case is failed.
