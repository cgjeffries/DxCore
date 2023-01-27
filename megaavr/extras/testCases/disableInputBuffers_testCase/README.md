# `disableInputBuffers` Test Case
This test case validates the `disableInputBuffers` and `enableInputBuffers` functions. 

## Instructions
1. Connect the Curiosity nano board to your computer
2. Connect the curiosity nano power supply in series with an ammeter such as a multimeter or AVR power debugger (recommended)
3. Download the sketch to the board.
4. Open a serial console in the COM port that the arduino is on, either using the built in serial console int he arduino IDE, or using a separate program like PuTTY. Set the Baud rate to **38400**.
5. Observe that the system sends messages tot he serial console describing what state it is in.
5. Verify using the ammeter that the system draws less power and has a more consistent power draw when the input buffers are disabled than when enabled. When in standby mode with input buffers off, the average power draw should read around 1uA.
