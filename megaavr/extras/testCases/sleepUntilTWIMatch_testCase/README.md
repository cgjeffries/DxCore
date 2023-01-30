# `sleepUntilTWIMatch` Test Case
This test case validates the ability for the system to wake when the correct address is received over TWI

## Instructions
1. Connect the I2C connections of the Curiosity nano board and an Arduino uno compatible board, such as an arduino nano, arduino uno, or atmega328p Xplained mini. No external pull-up resistors are required. Ensure that the Ground pins of each board are connected,
2. Connect the Curiosity nano board to your computer
3. Connect the curiosity nano power supply in series with an ammeter such as a multimeter or AVR power debugger (recommended)
4. Download the "slave" sketch to the Curiosity nano board.
5. Connect the Arduino uno compatible board to your computer
6. Download the "master" sketch to the uno compatible board.
7. Open a serial console in the COM port that the Curiosity nano is on, either using the built-in serial console in the Arduino IDE or using a separate program like PuTTY. Set the Baud rate to **115200**.
8. Observe that the curiosity nano sends messages when entering various sleep modes, as well as when the system receives a valid address over TWI.
9. Open a serial console in the COM port that the Arduino uno compatible board is on. Set the Baud rate to **57600**.
10. Observe that the Arduino uno compatible board sends "Sending message to slave!" every 2 seconds.
11. Verify using the ammeter that the system enters sleep, and then exits sleep upon the receipt of a valid TWI address, by default every 2 seconds. 
Example:
![right_address.png](right_address.png)
12. Revise the `twiAddress` in the Master sketch to a valid value other than 0x08, such as 0x0A.
13. Download the master sketch to the arduino uno compatible board.
14. Observe using the ammeter and the Curiosity nano board's serial output that it no longer wakes from sleep, as teh address is not correct. If the ammeter is sufficiently fast reacting, you may see small power spikes as the system received the invalid address. 
Example:
![right_address.png](wrong_address.png)