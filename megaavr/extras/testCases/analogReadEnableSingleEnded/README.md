# `analogReadEnableSingleEnded` Test Case
This test case validates the `analogReadEnableSingleEnded` function. 

## Instructions
1. Connect the signal generator board to your Curiosity Nano, with the signal output
connected to A0 (PD0)
2. Configure the signal generator to output 1.25v constant DC voltage
3. Connect A1 (PD1) to A3 (PD3)
4. Upload the `analogReadEnableSingleEnded.ino` sketch to your AVRDA board.
5. Open a serial monitor to view the recorded readings.

## Expected Output
This test case will alternate between single-ended and differential mode and display
readings taken in each mode. When the hardware is configured as described, the voltage
inputs and analog reference will be as follows:
- Voltage input positive = 1.25V
- Voltage input negative = 3.3V
- ADC voltage reference = 2.5V

Under these conditions, the expected results are as follows:
- Expected single-ended reading = (1.25V / 2.5V) * 1024 = 512
- Expected differential reading = ((1.25V - 3.3V) / 2.5V) * 512 = -419.84

## Results
Example results are recorded in `results-1v25-3v3.log` and analyzed in `results.xlsx`.
These results show that changing the sample delay is functioning as expected, with the
average readings in each mode as follows:
- Average single-ended reading: 518.1
- Average differential reading: -416.8
