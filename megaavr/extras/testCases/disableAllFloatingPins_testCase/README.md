# `disableAllFloatingPins` Test Case
This test case validates the `disableAllFloatingPins` function. 

## Instructions
1. Connect the Curiosity nano board to your computer
2. Connect the curiosity nano power supply in series with an ammeter such as a multimeter or AVR power debugger (recommended)
3. Download the sketch to the board.
4. Observe using the ammeter that for the first 1000ms of the program's runtime, the system draws full running power, however for the following 2000ms (the first delaySleep call) the system enters sleep and draws much less, although still >100uA. After another 1000ms awake, the system will enter sleep again. That sleep and all subsequent sleeps will have much reduced power draw even compared to the first sleep. Power should be < 10uA.