# ADC Sample Delay Test Case
This test case demonstrates changing the usage of analogReadEnableDifferential 
and demonstrates the output to serial monitor.

## Instructions
1. Upload the `analogReadEnableDifferential.ino` sketch to your AVRDA board.
2. Open a serial monitor to view the recorded readings.

## Expected Output
 - `(Default)` output will be 0 indicating the ADC is in single-ended mode.
 - `(Enabled)` output should be 1 indicating the analogReadEnableDifferential function 
executed sucessfully and enabled differential mode on the ADC.

## Results
...
