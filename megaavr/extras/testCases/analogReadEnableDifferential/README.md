# ADC Sample Delay Test Case
This test case demonstrates changing the usage of analogReadEnableDifferential 
and demonstrates the output to serial monitor.

## Instructions
1. Connect 5v (VTG) to Positive input (PD0)
2. Connect signal generator with DC input to negative pin (PD1)
3. Upload the `analogReadEnableDifferential.ino` sketch to your AVRDA board.
4. Open a serial monitor to view the recorded readings.

## Expected Output
Single Ended Mode
 - `(Default)` output will be 0 indicating the ADC is in single-ended mode.
 - Average sample output is ~5v
Differential Mode
 - `(Enabled)` output should be 1 indicating the analogReadEnableDifferential function 
executed sucessfully and enabled differential mode on the ADC.
 - Average sample output is ~5v minus negative pin input

## Results
Result sample output demonstrates the single ended mode outputting 5v and the 
analogReadEnableDifferential function sucessfully enabling differential mode and 
outputting the differential voltage (positive minus negative).
