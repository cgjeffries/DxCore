# `disableAllPeripherals` Test Case
This test case validates the `disableAllPeripheralsDuringSleep` and `enableAllPeripheralsDuringSleep` functions. 

## Instructions
1. Connect the Curiosity nano board to your computer
2. Connect the curiosity nano power supply in series with an ammeter such as a multimeter or AVR power debugger (recommended)
3. Download the sketch to the board.
4. Verify using the ammeter that the system enters sleep in cycles of 1000 ms running then 2000ms of sleep. The sleep with all peripherals on should pull significantly more power than the sleep with all peripherals disabled.
- Expected Results:
  - Disable, Standby: 0.35 mA
  - Enable, Standby: 2.75 mA
